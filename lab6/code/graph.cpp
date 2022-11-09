#include "graph.h"

bool graph_t::add_vertex(const elem_t & elem)
{
    if (size < volume) {
        base[size++].val = elem;
        return true;
    }
    return false;
}

bool graph_t::add_arc(int src, int dst)
{
    if (src < 0 || src >= size || dst < 0 || dst >= size)
        return false;
    arc_t * t = new arc_t;
    t->vertex_num = dst;
    t->next = base[src].arc_set;
    base[src].arc_set = t;
    return true;
}

bool graph_t::add_edge(int v1, int v2)
{
    return (add_arc(v1, v2) && add_arc(v2, v1));
}

int graph_t::index(elem_t val)
{
    for (int i = 0; i < size; i++)
        if (base[i].val == val)
            return i;
    return -1;
}