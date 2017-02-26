#ifndef _WIKI_GRAPH_HPP
#define _WIKI_GRAPH_HPP

#include <vector>
#include <string>
#include <map>

class WikiGraph {
    private:
        int V;
        std::vector<int> *adj;
        std::map<std::string, int> id;
        std::string *name;
        void add_arc(int from, int to);
    public:
        WikiGraph(std::string pages_path, std::string links_path);
        ~WikiGraph();
        std::vector<std::string> path(std::string &from_name, std::string &to_name);
};

#endif

