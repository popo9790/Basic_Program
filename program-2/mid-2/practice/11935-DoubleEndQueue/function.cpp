#include "function.h"
#include <bits/stdc++.h>

using namespace std;

void _stack::push(const _node N)
{
    End->next = new _node(N.data);
    End->next->prev = End;
    End = End->next;
}

void _stack::pop()
{
    if (!this->Empty())
    {
        _node *tmp = End;
        End->prev->next = NULL;
        End = End->prev;
        delete tmp;
    }
}

_node *_stack::get_data()
{
    if (!this->Empty())
        return End;
    return NULL;
}

void _queue::push(const _node N)
{
    End->next = new _node(N.data);
    End->next->prev = End;
    End = End->next;
}

void _queue::pop()
{
    if (!this->Empty())
    {
        _node *head = Begin->next->next;
        _node *pre = head->prev;
        _node *nex = head->next;
        pre->next = nex;
        if (head == End) // Begin tmp End
            End = pre;
        else // Begin tmp tmp End
            nex->prev = pre;
        delete head;
    }
}

_node *_queue::get_data()
{
    if (!this->Empty())
        return Begin->next->next;
    return NULL;
}