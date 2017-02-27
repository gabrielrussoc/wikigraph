#ifndef _WIKI_GRAPH_WRAPPER_HPP
#define _WIKI_GRAPH_WRAPPER_HPP
    
#include <node.h>
#include <node_object_wrap.h>
#include <string>
#include "wiki_graph.hpp"

class WikiGraphWrapper : public node::ObjectWrap {
    private:
        explicit WikiGraphWrapper(std::string pages = "", std::string links = "");
        ~WikiGraphWrapper();
        
        static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        static void Path(const v8::FunctionCallbackInfo<v8::Value>& args);
        static v8::Persistent<v8::Function> constructor;
        WikiGraph *wg_;
    public:
        static void Init(v8::Local<v8::Object> exports);
};

#endif

