#include "function.h"
#include <bits/stdc++.h>

using namespace std;

List_stack::List_stack()
    : head(NULL), tail(NULL){};

List_stack::~List_stack()
{
    for (ListNode *cur = head; cur != NULL;)
    {
        ListNode *tmp = cur;
        ListNode *next = cur->nextPtr;
        delete tmp;
        cur = next;
    }
}

void List_stack::push(const int &data)
{
    if (head == NULL)
    {
        head = new ListNode(data);
        tail = head;
    }
    else
    {
        tail->nextPtr = new ListNode(data);
        tail->nextPtr->prevPtr = tail;
        tail = tail->nextPtr;
    }
}

void List_stack::pop()
{
    if (tail)
    {
        if (tail == head)
        {
            delete head;
            head = NULL;
            tail = NULL;
        }
        else
        {
            ListNode *tmp = tail;
            tail->prevPtr->nextPtr = NULL;
            tail = tail->prevPtr;
            delete tmp;
        }
    }
}

void List_stack::print()
{
    for (auto cur = tail; cur != NULL; cur = cur->prevPtr)
    {
        cout << cur->data;
        if (cur->prevPtr != NULL)
            cout << " ";
    }
}