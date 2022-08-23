#include <iostream>
using namespace std;

const int N = 50;

void inputMatrix(int A[][N], int& n, int& m) {
    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> A[i][j];
        }
    }
}

void print(int A[][N], int n, int m) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

bool mEqual(int A[][N], int n1, int m1, int B[][N], int n2, int m2) 
{
    if(n1 == n2)
    {
        if(m1 == m2)
        {
            for(int i = 0; i < n1; ++i)
            {
                for(int j = 0; j < m2; ++j)
                {
                    if(A[i][j] != B[i][j])
                    {
                        return false;
                    }
                }
            }
            return true;
        }
    }

    return false;
}

void sum(int A[][N], int B[][N], int C[][N], int n, int m) 
{
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}
void transpose(int A[][N], int B[][N], int n, int m) 
{
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            B[j][i] = A[i][j];
        }
    }
}
void sMult(int A[][N], int R[][N], int n, int m, int s)
{
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            R[i][j] = A[i][j] * s;
        }
    }
}

void sub(int A[][N], int B[][N], int C[][N], int n, int m)
{
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}
void matrixMult(int A[][N], int B[][N], int C[][N], int r1, int c1, int r2, int c2) {
    for(int i=0;i<r1;i++)
    {
        for(int j=0;j<c2;j++)
        {
            for(int k=0;k<c1;k++)
            {
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
}
int main() {
    int n1, m1, n2, m2;
    int A[N][N], B[N][N], C[N][N];
    char command;

    cin >> command;
    switch(command) {
    case 'e':
        inputMatrix(A, n1, m1);
        inputMatrix(B, n2, m2);
        cout << mEqual(A, n1, m1, B, n1, m2) << endl;
        break;
    case 's':
        inputMatrix(A, n1, m1);
        inputMatrix(B, n2, m2);
        sum(A, B, C, n1, m1);
        print(C, n1, m1);
        break;
    case 't':
        inputMatrix(A, n1, m1);
        transpose(A, B, n1, m1);
        print(B, m1, n1);
        break;
    case 'c':
        int s;
        cin>> s;
        inputMatrix(A, n1, m1);
        sMult(A, B, n1, m1, s);
        print(B, n1, m1);
        break;
    case 'u':
        inputMatrix(A, n1, m1);
        inputMatrix(B, n2, m2);
        sub(A, B, C, n1, m1);
        print(C, n1, m1);
        break;
    case 'm':
        inputMatrix(A, n1, m1);
        inputMatrix(B, n2, m2);
        matrixMult(A, B, C, n1, m1, n2, m2);
        print(C, n1, m2);
        break;
    }

    return 0;
}
