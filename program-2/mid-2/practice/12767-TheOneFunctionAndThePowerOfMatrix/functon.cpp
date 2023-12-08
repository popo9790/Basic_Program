#include "function.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// TODO: Construct a matrix
Matrix constructMatrix(int n)
{
    Matrix CreateNew(n);
    return CreateNew;
}

// TODO: The Destructor
Matrix::~Matrix()
{
    for (int i = 0; i < this->n; ++i)
        delete[] this->matrix[i];
    delete this->matrix;
    this->n = 0;
}

// TODO: The Customize Constructor
Matrix::Matrix(int n)
{
    this->n = n;
    this->matrix = new ll *[n];
    for (int i = 0; i < this->n; ++i)
        this->matrix[i] = new ll[n];
    this->toIdentity();
}

// TODO: Copy contructor
// Will be trigger when the following condition:
// Matrix m = ref; -> Call copy contructor to copy from 'ref' to 'm'
Matrix::Matrix(const Matrix &ref)
{
    this->n = ref.n;
    this->matrix = new ll *[ref.n];
    for (int i = 0; i < this->n; ++i)
        this->matrix[i] = new ll[ref.n];

    for (int i = 0; i < this->n; ++i)
        for (int j = 0; j < this->n; ++j)
            this->matrix[i][j] = ref.matrix[i][j];
}

// TODO: Overload operator *
Matrix Matrix::operator*(const Matrix &rhs) const
{
    Matrix sum(rhs.n);
    for (int i = 0; i < this->n; ++i)
    {
        for (int j = 0; j < rhs.n; ++j)
        {
            sum.matrix[i][j] = 0;
            for (int k = 0; k < this->n; ++k)
                sum.matrix[i][j] += ((this->matrix[i][k] % mod) * (rhs.matrix[k][j] % mod) % mod);
            sum.matrix[i][j] %= mod;
        }
    }
    return sum;
}

// TODO: Return the matrix power of 'k'
Matrix Matrix::power(int k) const
{
    Matrix ret(this->n);
    Matrix init(this->n);
    for (int i = 0; i < this->n; ++i)
    {
        for (int j = 0; j < this->n; ++j)
        {
            if (i == this->n - 1)
                ret.matrix[i][j] = 1;
            else
                ret.matrix[i][j] = ret.matrix[i + 1][j];
        }
    }

    while (k > 1)
    {
        if (k % 2 == 1)
            init = ret * init;
        ret = ret * ret;
        k = k / 2;
    }
    init = ret * init;
    return init;
}

// TODO: copy assignment,
// Will be trigger when the following condition:
// Matrix a;
// a = ref; -> Call copy assignment to copy from 'ref' to 'a'
Matrix &Matrix::operator=(const Matrix &ref)
{
    this->~Matrix();
    this->n = ref.n;
    this->matrix = new ll *[ref.n];
    for (int i = 0; i < this->n; ++i)
        this->matrix[i] = new ll[ref.n];

    for (int i = 0; i < this->n; ++i)
        for (int j = 0; j < this->n; ++j)
            this->matrix[i][j] = ref.matrix[i][j];

    return *this;
}

// TODO: Overload operator()
// This operator allow the following code
// This operator can help you access the data easily
// 1. cout << m(1, 2) << endl; -> Shorthand of `cout << m.matrix[1, 2] << endl;`
// 2. m(1, 2) = 100; -> Shorthand of `m.matrix[1, 2] = 100`
long long &Matrix::operator()(const int &row, const int &column) const
{
    return this->matrix[row][column];
}

// Utilities functions
// TODO: Make the matrix identity matrix
void Matrix::toIdentity()
{
    for (int i = 0; i < this->n; ++i)
        for (int j = 0; j < this->n; ++j)
        {
            if (i == j)
                this->matrix[i][j] = 1;
            else
                this->matrix[i][j] = 0;
        }
}