#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
using namespace std;
float dot_prod(int dim, float *v1, float *v2);
void printLine(int lgh);

struct Matrix
{
    int rownum;
    int colnum;
    float **matrix;
};

int main()
{
    Matrix *m1 = new Matrix, *m2 = new Matrix;
    do
    {
        cout << "Please enter the row numbers of matrix_1: ";
        cin >> m1->rownum;
        if (m1->rownum <= 0)
        {
            cout << "Error. Matrix_1 must have more than 0 rows." << endl;
        }
    } while (m1->rownum <= 0);
    m1->matrix = new float *[m1->rownum];
    do
    {
        cout << "Please enter the column numbers of matrix_1: ";
        cin >> m1->colnum;
        if (m1->colnum <= 0)
        {
            cout << "Error. Matrix_1 must have more than 0 columns." << endl;
        }
    } while (m1->colnum <= 0);
    do
    {
        cout << "Please enter the row numbers of matrix_2: ";
        cin >> m2->rownum;
        if (m2->rownum <= 0)
        {
            cout << "Error. Matrix_2 must have more than 0 rows." << endl;
        }
        else if (m2->rownum != m1->colnum)
        {
            cout << "Error. Matrix_2's row number must be equal to Matrix_1's column number." << endl;
        }
    } while (m2->rownum <= 0 || m2->rownum != m1->colnum);
    m2->matrix = new float *[m2->colnum];
    do
    {
        cout << "Please enter the column numbers of matrix_2: ";
        cin >> m2->colnum;
        if (m2->colnum <= 0)
        {
            cout << "Error. Matrix_2 must have more than 0 columns." << endl;
        }
    } while (m2->colnum <= 0);

    Matrix *rst = new Matrix{m1->rownum, m2->colnum, new float *[m1->rownum]};
    int dim = m1->colnum;

    cout << endl
         << "Please enter the elements of Matrix_1, from up to down, left to right:" << endl;
    for (int i = 0; i < m1->rownum; i++)
    {
        m1->matrix[i] = new float[m1->colnum];
        for (int j = 0; j < m1->colnum; j++)
        {
            cin >> m1->matrix[i][j];
        }
    }
    cout << "Please enter the elements of Matrix_2, from up to down, left to right:" << endl;
    for (int i = 0; i < m2->colnum; i++)
    {
        m2->matrix[i] = new float[m2->rownum];
    }
    for (int i = 0; i < m2->rownum; i++)
    {
        for (int j = 0; j < m2->colnum; j++)
        {
            cin >> m2->matrix[j][i];
        }
    }

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    printLine(m2->colnum);
    for (int i = 0; i < m1->rownum; i++)
    {
        rst->matrix[i] = new float[m2->colnum];
        cout << "|";
        for (int j = 0; j < m2->colnum; j++)
        {
            rst->matrix[i][j] = dot_prod(dim, m1->matrix[i], m2->matrix[j]);
        }
        printLine(m2->colnum);
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Calculation took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds.";
    return 0;
}

float dot_prod(int dim, float *v1, float *v2)
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
    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout.width(11);
    cout << rst << "|";
    return rst;
}

void printLine(int lgh)
{
    cout << endl
         << "+";
    for (int i = 0; i < lgh; i++)
    {
        cout << "-----------+";
    }
    cout << endl;
}