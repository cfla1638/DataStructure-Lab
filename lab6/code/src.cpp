#include <iostream>
#include <fstream>  // ifstream
#include <cstring>  // memset
#include <queue>
#include <stack>
#include <vector>
#include <utility>  // pair
#include "graph.h"
using namespace std;

// 全局数据结构
int visited[graph_t::volume];
vector<int> visited_seq;
vector<pair<int, int> > visited_arc_set;

// 用于搜索路径的栈和标记
int path[1024];
int in_path[1024];
int top, start_vertex, dest_vertex, exclusion;

// 实验要求用到的函数
void read_file(graph_t & G, istream &);
void BFS(const graph_t & G, int start);
void DFS(const graph_t & G, int start);
void DFS_non_recursion(const graph_t & G, int start);
void build_spanning_tree(const graph_t & ori, graph_t & tree);
void print_tree(const graph_t &);
void show_result(const graph_t &);
void generate_path(const graph_t &, elem_t src, elem_t dst);

// 辅助函数
void do_DFS(const graph_t & G, int start);
void do_print_tree(const graph_t &, int, int);
void do_generate_path(const graph_t &, int);

// g++ src.cpp graph.cpp -o prog && prog.exe
int main(void)
{
    graph_t G, tree;
    ifstream in("data.txt");
    read_file(G, in);
    // DFS_non_recursion(G, 0);
    // show_result(G);
    // build_spanning_tree(G, tree);
    // print_tree(tree);
     generate_path(G, "北京", "广州");

    return 0;
}

void BFS(const graph_t & G, int start)
{
    // 预先设置好状态
    memset(visited, 0, sizeof(visited));
    visited_seq.clear();
    visited_arc_set.clear();

    // 初始化队列
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

void DFS_non_recursion(const graph_t & G, int start)
{
    memset(visited, 0, sizeof(visited));
    visited_seq.clear();
    visited_arc_set.clear();

    stack<int> S;
    // 回退的条件是所有的孩子都已经访问过
    // 结束的条件是所有的孩子已经访问过且栈为空
    
    int cur = start, prev = -1;
    while (!S.empty() || cur != prev) {
        if (cur == prev) {
            cur = S.top();
            S.pop();
        }
        if (!visited[cur]) {
            visited[cur] = 1;
            visited_seq.push_back(cur);
            if (prev != -1)
                visited_arc_set.push_back(pair<int, int>(prev, cur));
        }
        prev = cur;
        for (arc_t * i = G.base[cur].arc_set; i != nullptr; i = i->next)
            if (!visited[i->vertex_num]) {
                S.push(cur);
                cur = i->vertex_num;
                break;
            }
    }
}

// DFS包装函数
void DFS(const graph_t & G, int start)
{
    memset(visited, 0, sizeof(visited));
    visited_seq.clear();
    visited_arc_set.clear();
    do_DFS(G, start);
}

// DFS 递归版本
void do_DFS(const graph_t & G, int start)
{
    visited[start] = 1;
    visited_seq.push_back(start);
    for (arc_t * t = G.base[start].arc_set; t != nullptr; t = t->next)
        if (!visited[t->vertex_num]) {
            visited_arc_set.push_back(pair<int, int>(start, t->vertex_num));
            do_DFS(G, t->vertex_num);
        }
}

// 显示访问序列和边集
void show_result(const graph_t &G)
{
    cout << "访问序列:" << endl;
    for (auto i : visited_seq)
        cout << G.base[i].val << " ";
    cout << endl << "边集:" << endl;
    for (auto i : visited_arc_set)
        cout << G.base[i.first].val << " -> " << G.base[i.second].val << endl;
}

void read_file(graph_t & G, istream & in)
{
    int vertex_cnt, arc_cnt, weight;
    elem_t t, src_val, dst_val;

    in >> vertex_cnt;
    for (int i = 0; i < vertex_cnt; i++) {
        in >> t;
        G.add_vertex(t);
    }

    in >> arc_cnt;
    for (int i = 0; i < arc_cnt; i++) {
        in >> src_val >> dst_val >> weight;
        G.add_arc(G.index(src_val), G.index(dst_val), weight);
    }
}

void build_spanning_tree(const graph_t & ori, graph_t & tree)
{
    for (auto i : visited_seq)
        tree.add_vertex(ori.base[i].val);
    for (auto i : visited_arc_set)
        tree.add_arc(tree.index(ori.base[i.first].val), 
                     tree.index(ori.base[i.second].val), 0);
}

void print_tree(const graph_t & G)
{
    memset(visited, 0, sizeof(visited));
    do_print_tree(G, 0, 0);
}

void do_print_tree(const graph_t & G, int start, int cnt)
{
    visited[start] = 1;
    for (int i = 0; i < cnt; i++)
        cout << '*';
    cout << G.base[start].val << endl;
    for (arc_t * t = G.base[start].arc_set; t != nullptr; t = t->next)
        if (!visited[t->vertex_num])
            do_print_tree(G, t->vertex_num, cnt + 1);
}

void generate_path(const graph_t &G, elem_t src, elem_t dst)
{
    memset(path, 0, sizeof(path));
    memset(in_path, 0, sizeof(in_path));
    top = 0;
    start_vertex = G.index(src);
    dest_vertex = G.index(dst);
    exclusion = G.index("郑州");
    do_generate_path(G, G.index(src));
}

void do_generate_path(const graph_t & G, int cur)
{
    path[top++] = cur;
    in_path[cur] = 1;
    if (cur == dest_vertex) {
        cout << "发现路径 : ";
        for (int i = 0; i < top; i++)
            cout << G.base[path[i]].val << " ";
        cout << endl;
        in_path[cur] = 0;
        top--;
        return ;
    }
    for (arc_t * i = G.base[cur].arc_set; i != nullptr; i = i->next)
        if (!in_path[i->vertex_num]) {
            do_generate_path(G, i->vertex_num);
        }
    in_path[cur] = 0;
    top--;
}