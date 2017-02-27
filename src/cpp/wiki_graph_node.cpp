#include <node.h>
#include "wiki_graph_wrapper.hpp"

using v8::Local;
using v8::Object;

void InitAll(Local<Object> exports) {
    WikiGraphWrapper::Init(exports);
}

NODE_MODULE(wiki_graph_node, InitAll)

