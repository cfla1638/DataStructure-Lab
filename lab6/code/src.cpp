#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <utility>
#include "graph.h"
using namespace std;

int visited[graph_t::volume];
vector<int> visited_seq;
vector<pair<int, int> > visited_arc_set;

void BFS(const graph_t & G, int start);
void DFS(const graph_t & G, int start);
void show_result();

void do_DFS(const graph_t & G, int start);

int main(void)
{
    graph_t G;
    G.add_vertex("0");
    G.add_vertex("1");
    G.add_vertex("2");
    G.add_vertex("3");
    G.add_vertex("4");
    G.add_vertex("5");
    G.add_vertex("6");
    G.add_vertex("7");

    G.add_edge(G.index("0"), G.index("1"));
    G.add_edge(G.index("0"), G.index("2"));
    G.add_edge(G.index("1"), G.index("3"));
    G.add_edge(G.index("1"), G.index("4"));
    G.add_edge(G.index("2"), G.index("5"));
    G.add_edge(G.index("2"), G.index("6"));

    DFS(G, 0);
    show_result();

    return 0;
}

void BFS(const graph_t & G, int start)
{
    memset(visited, 0, sizeof(visited));
    visited_seq.clear();
    visited_arc_set.clear();
    queue<int> Q;
    Q.push(start);

    while (!Q.empty()) {
        int t = Q.front();
        Q.pop();
        visited[t] = 1;
        visited_seq.push_back(t);
        for (arc_t * i = G.base[t].arc_set; i != nullptr; i = i->next)
            if (!visited[i->vertex_num]) {
                Q.push(i->vertex_num);
                visited_arc_set.push_back(pair<int, int>(t, i->vertex_num));
            }
    }
}

void DFS(const graph_t & G, int start)
{
    memset(visited, 0, sizeof(visited));
    visited_seq.clear();
    visited_arc_set.clear();
    do_DFS(G, start);
}

void do_DFS(const graph_t & G, int start)
{
    visited[start] = 1;
    visited_seq.push_back(start);
    for (arc_t * t = G.base[start].arc_set; t != nullptr; t = t->next)
        if (!visited[t->vertex_num]) {
            visited_arc_set.push_back(pair<int, int>(start, t->vertex_num));
            DFS(G, t->vertex_num);
        }
}

void show_result()
{
    cout << "·ÃÎÊÐòÁÐ:" << endl;
    for (auto i : visited_seq)
        cout << i << " ";
    cout << endl << "±ß¼¯:" << endl;
    for (auto i : visited_arc_set)
        cout << i.first << " -> " << i.second << endl;
}