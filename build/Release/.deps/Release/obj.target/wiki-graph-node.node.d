cmd_Release/obj.target/wiki-graph-node.node := g++ -shared -pthread -rdynamic -m64  -Wl,-soname=wiki-graph-node.node -o Release/obj.target/wiki-graph-node.node -Wl,--start-group Release/obj.target/wiki-graph-node/src/cpp/wiki_graph_node.o Release/obj.target/wiki-graph-node/src/cpp/wiki_graph_wrapper.o Release/obj.target/wiki-graph-node/src/cpp/wiki_graph.o -Wl,--end-group 
