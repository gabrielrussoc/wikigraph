#include <cstdio>
#include <string>
#include <iostream>
#include <thread>
#include "wiki_graph.hpp"
using namespace std;

int main(int argc, char **argv){
    double st, en;
    st = (double) clock() / CLOCKS_PER_SEC;
    WikiGraph *g = new WikiGraph("data/wiki_pages_compressed.txt", "data/wiki_links_compressed.txt");
    en = (double) clock() / CLOCKS_PER_SEC;
    printf("Grafo montado (%.2lf)\n\n", en-st);
    while(true) {
        puts("Insira dois artigos");
        st = (double) clock() / CLOCKS_PER_SEC;
        string a, b;
        if(!getline(cin, a)) break;
        if(!getline(cin, b)) break;
        vector<string> path = g->path(a, b);
        en = (double) clock() / CLOCKS_PER_SEC;
        puts("--------");
        printf("%d (%.2lf)\n", path.size()-1, en-st);
        for(string s : path) {
            cout << s << endl;
        }
        puts("--------");
    }
    delete g;
    return 0;
}


