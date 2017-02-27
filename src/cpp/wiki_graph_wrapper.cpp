#include "wiki_graph_wrapper.hpp"
#include <string>
#include <vector>

using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;
using v8::Array;
using std::string;
using std::vector;

Persistent<Function> WikiGraphWrapper::constructor;

WikiGraphWrapper::WikiGraphWrapper(string pages, string links) {
   wg_ = new WikiGraph(pages, links);
}

WikiGraphWrapper::~WikiGraphWrapper() {
    delete wg_;
}

void WikiGraphWrapper::Init(Local<Object> exports) {
    Isolate* isolate = exports->GetIsolate();

    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "WikiGraph"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Prototype
    NODE_SET_PROTOTYPE_METHOD(tpl, "path", Path);

    constructor.Reset(isolate, tpl->GetFunction());
    exports->Set(String::NewFromUtf8(isolate, "WikiGraph"), tpl->GetFunction());
}

void WikiGraphWrapper::New(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.IsConstructCall()) {
        // Invoked as constructor: `new MyObject(...)`
        string pages = string(*String::Utf8Value(args[0]->ToString()));
        string links = string(*String::Utf8Value(args[1]->ToString()));
        WikiGraphWrapper* obj = new WikiGraphWrapper(pages, links);
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    } else {
        // Invoked as plain function `MyObject(...)`, turn into construct call.
        const int argc = 2;
        Local<Value> argv[argc] = { args[0], args[1] };
        Local<Context> context = isolate->GetCurrentContext();
        Local<Function> cons = Local<Function>::New(isolate, constructor);
        Local<Object> result = cons->NewInstance(context, argc, argv).ToLocalChecked();
        args.GetReturnValue().Set(result);
    }
}

void WikiGraphWrapper::Path(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    WikiGraphWrapper* obj = ObjectWrap::Unwrap<WikiGraphWrapper>(args.Holder());
    
    string from = string(*String::Utf8Value(args[0]->ToString()));
    string to = string(*String::Utf8Value(args[1]->ToString()));

    vector<string> path = obj->wg_->path(from, to);

    Local<Array> arr = Array::New(isolate);
    for(int i = 0; i < (int) path.size(); i++)
        arr->Set(i, String::NewFromUtf8(isolate,  path[i].c_str()));

    args.GetReturnValue().Set(arr);
}


