#include "function.h"
#include <bits/stdc++.h>

using namespace std;

Darray::~Darray()
{
    capacity = 0;
    size = 0;
    delete[] data;
}

int &Darray::operator[](int idx)
{
    return data[idx];
}

void Darray::pushback(int x)
{
    if (size == capacity)
        this->resize();
    data[size++] = x;
}

void Darray::clear(void)
{
    size = 0;
}

int Darray::length(void)
{
    return this->size;
}

void Darray::resize(void)
{
    int *arr = new int[capacity * 2];
    for (int i = 0; i < this->size; ++i)
        arr[i] = data[i];

    this->capacity *= 2;
    delete[] this->data;
    this->data = arr;
}