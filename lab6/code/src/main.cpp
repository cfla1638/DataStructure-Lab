#include <iostream>
#include <fstream>  // ifstream
#include <cstring>  // memset
#include <vector>
#include <utility>  // pair
#include "graph.h"  // graph_t
#include "stack.h"  // mystack::stack
#include "queue.h"  // myqueue::queue
using namespace std;
using myqueue::queue;
using mystack::stack;

// 全局数据结构
int visited[graph_t::volume];
vector<int> visited_seq;
vector<pair<int, int> > visited_arc_set;

// 用于搜索路径的栈和标记
int path[1024];
int in_path[1024];
int top, start_vertex, dest_vertex, exclusion, cur_length;

// 实验要求用到的函数
void read_file(graph_t & G, istream &);     // 读取数据，建立图
void BFS(const graph_t & G, int start);
void DFS(const graph_t & G, int start);
void DFS_non_recursion(const graph_t & G, int start);   // 非递归版本的DFS
// 根据全局的visited_seq和visited_arc_path建立生成树
void build_spanning_tree(const graph_t & ori, graph_t & tree);
void print_tree(const graph_t &);   // 凹入表打印生成树
void show_result(const graph_t &);  // 打印visited_seq和visited_arc_path
void generate_path(const graph_t &, elem_t src, elem_t dst);    // 生产路径

// 辅助函数
void do_DFS(const graph_t & G, int start);
void do_print_tree(const graph_t &, int, int);
void do_generate_path(const graph_t &, int, int);

int main(void)
{
    graph_t G, bfs_tree, dfs_tree;
    elem_t start;
    int start_index;

    ifstream in("../data/data.txt");    // 根据文件结构的不同采用不同的输入路径
    if (!in.is_open()) {
        cerr << "输入数据文件打开失败！" << endl;
        cerr << "没有找到 ../data/data.txt ,请检查输入文件路径" << endl;
        abort();

    }

    read_file(G, in);
    
    cout << "请输入遍历起点:" << endl;
    cin >> start;
    start_index = G.index(start);
    if (start_index == -1) {
        cerr << "不存在该结点! " << endl;
        abort();
    }

    cout << "--DFS--" << endl;
    DFS(G, start_index);
    show_result(G);
    cout << "--DFS without recursion--" << endl;
    DFS_non_recursion(G, start_index);
    show_result(G);
    cout << "--DFS spanning tree--" << endl;
    build_spanning_tree(G, dfs_tree);
    print_tree(dfs_tree);
    cout << "--BFS--" << endl;
    BFS(G, start_index);
    show_result(G);
    cout << "--BFS spanning tree--" << endl;
    build_spanning_tree(G, bfs_tree);
    print_tree(bfs_tree);
    cout << "--path--" << endl;
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
        if (visited[t])
            continue;
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
        G.add_edge(G.index(src_val), G.index(dst_val), weight);
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
    cur_length = 0;
    start_vertex = G.index(src);
    dest_vertex = G.index(dst);
    exclusion = G.index("郑州");    // 在此处配置不经过的城市结点
    do_generate_path(G, G.index(src), 0);
}

void do_generate_path(const graph_t & G, int cur, int length)
{
    path[top++] = cur;
    in_path[cur] = 1;
    cur_length += length;
    if (cur == dest_vertex) {
        cout << "发现路径 : ";
        for (int i = 0; i < top; i++)
            cout << G.base[path[i]].val << " ";
        cout << endl;
        cout << "路径长度为: " << cur_length << endl;
        cur_length -= length;
        in_path[cur] = 0;
        top--;
        return ;
    }
    for (arc_t * i = G.base[cur].arc_set; i != nullptr; i = i->next)
        if (!in_path[i->vertex_num] && i->vertex_num != exclusion) {
            do_generate_path(G, i->vertex_num, i->weight);
        }
    cur_length -= length;
    in_path[cur] = 0;
    top--;
}