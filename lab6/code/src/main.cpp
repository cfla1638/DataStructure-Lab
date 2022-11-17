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

// ȫ�����ݽṹ
int visited[graph_t::volume];
vector<int> visited_seq;
vector<pair<int, int> > visited_arc_set;

// ��������·����ջ�ͱ��
int path[1024];
int in_path[1024];
int top, start_vertex, dest_vertex, exclusion, cur_length;

// ʵ��Ҫ���õ��ĺ���
void read_file(graph_t & G, istream &);     // ��ȡ���ݣ�����ͼ
void BFS(const graph_t & G, int start);
void DFS(const graph_t & G, int start);
void DFS_non_recursion(const graph_t & G, int start);   // �ǵݹ�汾��DFS
// ����ȫ�ֵ�visited_seq��visited_arc_path����������
void build_spanning_tree(const graph_t & ori, graph_t & tree);
void print_tree(const graph_t &);   // ������ӡ������
void show_result(const graph_t &);  // ��ӡvisited_seq��visited_arc_path
void generate_path(const graph_t &, elem_t src, elem_t dst);    // ����·��

// ��������
void do_DFS(const graph_t & G, int start);
void do_print_tree(const graph_t &, int, int);
void do_generate_path(const graph_t &, int, int);

int main(void)
{
    graph_t G, bfs_tree, dfs_tree;
    elem_t start;
    int start_index;

    ifstream in("../data/data.txt");    // �����ļ��ṹ�Ĳ�ͬ���ò�ͬ������·��
    if (!in.is_open()) {
        cerr << "���������ļ���ʧ�ܣ�" << endl;
        cerr << "û���ҵ� ../data/data.txt ,���������ļ�·��" << endl;
        abort();

    }

    read_file(G, in);
    
    cout << "������������:" << endl;
    cin >> start;
    start_index = G.index(start);
    if (start_index == -1) {
        cerr << "�����ڸý��! " << endl;
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
    generate_path(G, "����", "����");

    return 0;
}

void BFS(const graph_t & G, int start)
{
    // Ԥ�����ú�״̬
    memset(visited, 0, sizeof(visited));
    visited_seq.clear();
    visited_arc_set.clear();

    // ��ʼ������
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
    // ���˵����������еĺ��Ӷ��Ѿ����ʹ�
    // ���������������еĺ����Ѿ����ʹ���ջΪ��
    
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

// DFS��װ����
void DFS(const graph_t & G, int start)
{
    memset(visited, 0, sizeof(visited));
    visited_seq.clear();
    visited_arc_set.clear();
    do_DFS(G, start);
}

// DFS �ݹ�汾
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

// ��ʾ�������кͱ߼�
void show_result(const graph_t &G)
{
    cout << "��������:" << endl;
    for (auto i : visited_seq)
        cout << G.base[i].val << " ";
    cout << endl << "�߼�:" << endl;
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
    exclusion = G.index("֣��");    // �ڴ˴����ò������ĳ��н��
    do_generate_path(G, G.index(src), 0);
}

void do_generate_path(const graph_t & G, int cur, int length)
{
    path[top++] = cur;
    in_path[cur] = 1;
    cur_length += length;
    if (cur == dest_vertex) {
        cout << "����·�� : ";
        for (int i = 0; i < top; i++)
            cout << G.base[path[i]].val << " ";
        cout << endl;
        cout << "·������Ϊ: " << cur_length << endl;
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