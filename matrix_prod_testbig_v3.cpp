#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
using namespace std;
float dot_prod(int dim, float *v1, float *v2);
void calcthread(float **matrix, float **m1, float **m2, int rowst, int rowed, int colst, int coled, int D);

struct Matrix
{
    int rownum;
    int colnum;
    float **matrix;
};

int main()
{
    int N, K, M;
    cout << "Enter N, K, M: ";
    cin >> N >> K >> M;
    Matrix *m1 = new Matrix{N, K, new float *[N]}, *m2 = new Matrix{K, M, new float *[M]};
    Matrix *rst = new Matrix{N, M, new float *[N]};

    for (int i = 0; i < m1->rownum; i++)
    {
        m1->matrix[i] = new float[m1->colnum]();
        rst->matrix[i] = new float[m2->colnum];
    }
    m1->matrix[0][0] = 9.67;
    for (int i = 0; i < m2->colnum; i++)
    {
        m2->matrix[i] = new float[m2->rownum]();
    }
    m2->matrix[0][0] = 8.88;

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    thread ct01(calcthread, rst->matrix, m1->matrix, m2->matrix, 0, 2000, 0, 1000, K);
    thread ct02(calcthread, rst->matrix, m1->matrix, m2->matrix, 2000, 4000, 0, 1000, K);
    thread ct03(calcthread, rst->matrix, m1->matrix, m2->matrix, 0, 2000, 1000, 2000, K);
    thread ct04(calcthread, rst->matrix, m1->matrix, m2->matrix, 2000, 4000, 1000, 2000, K);
    thread ct05(calcthread, rst->matrix, m1->matrix, m2->matrix, 0, 2000, 2000, 3000, K);
    thread ct06(calcthread, rst->matrix, m1->matrix, m2->matrix, 2000, 4000, 2000, 3000, K);
    thread ct07(calcthread, rst->matrix, m1->matrix, m2->matrix, 0, 2000, 3000, 4000, K);
    for (int i = 2000; i < 4000; i++)
    {
        for (int j = 3000; j < 4000; j++)
        {
            rst->matrix[i][j] = dot_prod(K, m1->matrix[i], m2->matrix[j]);
        }
    }
    ct01.join();
    ct02.join();
    ct03.join();
    ct04.join();
    ct05.join();
    ct06.join();
    ct07.join();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Calculation took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds.";
    return 0;
}

inline float dot_prod(int dim, float *v1, float *v2)
{
    int vec1, vec2;
    long long sum = 0;
    for (int i = 0; i < dim; i++)
    {
        vec1 = (int)(v1[i] * 1e3);
        vec2 = (int)(v2[i] * 1e3);
        sum += (long long)vec1 * vec2;
    }
    double rst = sum / 1e6;
    return rst;
}

void calcthread(float **matrix, float **m1, float **m2, int rowst, int rowed, int colst, int coled, int M)
{
    for (int i = rowst; i < rowed; i++)
    {
        for (int j = colst; j < coled; j++)
        {
            matrix[i][j] = dot_prod(M, m1[i], m2[j]);
        }
    }
}