#ifndef H_GRAPH
#define H_GRAPH
#include <string>

typedef std::string elem_t;
typedef struct arc_t
{
    int vertex_num = 0;
    int weight = 0;
    struct arc_t * next = nullptr;
}arc_t;

typedef struct 
{
    elem_t val;
    arc_t * arc_set = nullptr; 
}vertex_t;

class graph_t
{
public:
    graph_t() { base = new vertex_t[volume]; }
    graph_t(const graph_t &) = delete;  // TODO
    graph_t & operator=(const graph_t &) = delete;  // TODO
    ~graph_t() {delete[] base;}

    bool add_vertex(const elem_t &);
    bool add_arc(int src, int dst, int weight);
    bool add_edge(int v1, int v2, int weight);
    int index(elem_t);

    vertex_t * base = nullptr;
    int size = 0;
    static const int volume = 100;
};

#endif