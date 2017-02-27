#include <queue>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "wiki_graph.hpp"

WikiGraph::WikiGraph(std::string pages_path, std::string links_path) {
    std::ifstream pages(pages_path);
    std::ifstream links(links_path);
    std::map<std::string, int> id;
    std::string line;

    int c = 1;
    if(pages.is_open()) {
        while(std::getline(pages, line)) id[line] = c++;
    } else {
        throw std::runtime_error(std::string("Falha na leitura das paginas"));
    }

    this->V = c;
    this->adj = new std::vector<int>[c];
    this->id = id;
    this->name = new std::string[c];
    for(auto kv : id) this->name[kv.second] = kv.first; 

    if(links.is_open()) {
        int u, v;
        while(links >> u >> v) add_arc(u, v);
    } else {
        throw std::runtime_error(std::string("Falha na leitura dos links"));
    }

    pages.close();
    links.close();
}

WikiGraph::~WikiGraph() {
    delete[] adj;
    delete[] name;
}

std::vector<std::string> WikiGraph::path(std::string &from_name, std::string &to_name) {
    std::vector<int> dist(V);
    std::vector<int> parent(V);
    std::fill(dist.begin(), dist.end(), V);
    std::fill(parent.begin(), parent.end(), -1);
    std::queue<int> q;
    int from = id[from_name];
    int to = id[to_name];
    q.push(from);
    dist[from] = 0;
    bool has_path = false;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        if(u == to) { 
            has_path = true;
            break;
        }
        for(int v : adj[u]) {
            if(dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }
    int u = to;
    std::vector<std::string> ret;
    if(!has_path) return ret;
    ret.push_back(name[u]);
    while(parent[u] != -1) {
        u = parent[u];
        ret.push_back(this->name[u]);
    }
    std::reverse(ret.begin(), ret.end());
    return ret;
} 

void WikiGraph::add_arc(int from, int to) {
    adj[from].push_back(to);
}

