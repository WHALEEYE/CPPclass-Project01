#include <iostream>
#include <cstring>
#include <cstdio>
#include <iomanip>
#include <ctime>
#include <chrono>
using namespace std;

struct Matrix
{
    float **matrix;
    int n, m, n0, m0;

    Matrix operator+(const Matrix &B)
    {
        Matrix C;
        C.n = n;
        C.m = m;
        C.matrix = new float *[n];
        for (int i = 0; i < n; i++)
        {
            C.matrix[i] = new float[m];
            for (int j = 0; j < n; j++)
            {
                C.matrix[i][j] = matrix[i][j] + B.matrix[i][j];
            }
        }
        return C;
    }

    Matrix operator-(const Matrix &B)
    {
        Matrix C;
        C.n = n;
        C.m = m;
        C.matrix = new float *[n];
        for (int i = 0; i < n; i++)
        {
            C.matrix[i] = new float[m];
            for (int j = 0; j < n; j++)
            {
                C.matrix[i][j] = matrix[i][j] - B.matrix[i][j];
            }
        }
        return C;
    }

    Matrix operator*(const Matrix &B)
    {
        Matrix C;
        C.n = n;
        C.m = B.m;
        C.matrix = new float *[n];
        for (int i = 0; i < n; i++)
        {
            C.matrix[i] = new float[m]();
            for (int j = 0; j < m; j++)
            {
                if (matrix[i][j] == 0)
                {
                    continue;
                }
                for (int k = 0; k < m; k++)
                {
                    C.matrix[i][k] += matrix[i][j] * B.matrix[j][k];
                }
            }
        }
        return C;
    }

    void optimize()
    {
        int sqn = 1;
        while (sqn < n)
        {
            sqn <<= 1;
        }
        while (sqn < m)
        {
            sqn <<= 1;
        }
        matrix = new float *[sqn];
        for (int i = 0; i < n; i++)
        {
            matrix[i] = new float[sqn];
            for (int j = m; j < sqn; j++)
            {
                matrix[i][j] = 0;
            }
        }
        for (int i = n; i < sqn; i++)
        {
            matrix[i] = new float[sqn]();
        }
        n0 = n;
        m0 = m;
        m = n = sqn;
    }

    void optimizeTest()
    {
        int sqn = 1;
        while (sqn < n)
        {
            sqn <<= 1;
        }
        while (sqn < m)
        {
            sqn <<= 1;
        }
        matrix = new float *[sqn];
        for (int i = 0; i < sqn; i++)
        {
            matrix[i] = new float[sqn]();
        }
        n0 = n;
        m0 = m;
        m = n = sqn;
    }

    void read()
    {
        cin >> n >> m;
        optimize();
        for (int i = 0; i < n0; i++)
        {
            for (int j = 0; j < m0; j++)
            {
                cin >> matrix[i][j];
            }
        }
    }

    Matrix split(int i1, int j1, int i2, int j2)
    {
        Matrix C;
        C.n = i2 - i1 + 1;
        C.m = j2 - j1 + 1;
        C.matrix = new float *[n];
        for (int i = i1 - 1; i < i2; i++)
        {
            C.matrix[i - i1 + 1] = new float[m];
            for (int j = j1 - 1; j < j2; j++)
            {
                C.matrix[i - i1 + 1][j - j1 + 1] = matrix[i][j];
            }
        }
        return C;
    }

    void merge(Matrix &B, int i1, int j1, int i2, int j2)
    {
        for (int i = i1 - 1; i < i2; i++)
        {
            for (int j = j1 - 1; j < j2; j++)
            {
                matrix[i][j] = B.matrix[i - i1 + 1][j - j1 + 1];
            }
        }
    }

    void print()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cout << setw(6) << matrix[i][j];
            }
            cout << endl;
        }
    }
} A, B;

Matrix Strassen(Matrix &X, Matrix &Y)
{
    if (X.n == 1)
    {
        return X * Y;
    }
    int n = X.n;
    Matrix A[2][2], B[2][2], S[10], P[7];
    A[0][0] = X.split(1, 1, n / 2, n / 2);
    A[0][1] = X.split(1, n / 2 + 1, n / 2, n);
    A[1][0] = X.split(n / 2 + 1, 1, n, n / 2);
    A[1][1] = X.split(n / 2 + 1, n / 2 + 1, n, n);
    B[0][0] = Y.split(1, 1, n / 2, n / 2);
    B[0][1] = Y.split(1, n / 2 + 1, n / 2, n);
    B[1][0] = Y.split(n / 2 + 1, 1, n, n / 2);
    B[1][1] = Y.split(n / 2 + 1, n / 2 + 1, n, n);
    S[0] = B[0][1] - B[1][1];
    S[1] = A[0][0] + A[0][1];
    S[2] = A[1][0] + A[1][1];
    S[3] = B[1][0] - B[0][0];
    S[4] = A[0][0] + A[1][1];
    S[5] = B[0][0] + B[1][1];
    S[6] = A[0][1] - A[1][1];
    S[7] = B[1][0] + B[1][1];
    S[8] = A[0][0] - A[1][0];
    S[9] = B[0][0] + B[0][1];
    P[0] = Strassen(A[0][0], S[0]);
    P[1] = Strassen(S[1], B[1][1]);
    P[2] = Strassen(S[2], B[0][0]);
    P[3] = Strassen(A[1][1], S[3]);
    P[4] = Strassen(S[4], S[5]);
    P[5] = Strassen(S[6], S[7]);
    P[6] = Strassen(S[8], S[9]);
    B[0][0] = P[4] + P[3] - P[1] + P[5];
    B[0][1] = P[0] + P[1];
    B[1][0] = P[2] + P[3];
    B[1][1] = P[4] + P[0] - P[2] - P[6];
    X.merge(B[0][0], 1, 1, n / 2, n / 2);
    X.merge(B[0][1], 1, n / 2 + 1, n / 2, n);
    X.merge(B[1][0], n / 2 + 1, 1, n, n / 2);
    X.merge(B[1][1], n / 2 + 1, n / 2 + 1, n, n);
    return X;
}

int main()
{
    Matrix C;
    // A.read();
    // B.read();
    int N, K, M;
    cout << "Enter N, K, M: ";
    cin >> N >> K >> M;
    A.n = N;
    A.m = K;
    A.optimizeTest();
    A.matrix[0][0] = 8.8;
    B.n = K;
    B.m = M;
    B.optimizeTest();
    B.matrix[0][0] = 9.8;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    C = Strassen(A, B);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Calculation took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds." << endl;
    // C.n = A.n0;
    // C.m = B.m0;
    // C.print();
}