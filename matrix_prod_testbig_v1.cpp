#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;
float dot_prod(int dim, float *v1, float *v2);
void printLine(int lgh);

struct Matrix {
  int rownum;
  int colnum;
  float **matrix;
};

int main() {
  int N, K, M;
  cout << "Enter N, K, M: ";
  cin >> N >> K >> M;
  Matrix *m1 = new Matrix{N, K, new float *[N]},
         *m2 = new Matrix{K, M, new float *[M]};
  Matrix *rst = new Matrix{N, M, new float *[N]};

  for (int i = 0; i < m1->rownum; i++) {
    m1->matrix[i] = new float[m1->colnum]();
  }
  m1->matrix[0][0] = 9.67;
  for (int i = 0; i < m2->colnum; i++) {
    m2->matrix[i] = new float[m2->rownum]();
  }
  m2->matrix[0][0] = 8.88;

  std::chrono::steady_clock::time_point start =
      std::chrono::steady_clock::now();
  for (int i = 0; i < m1->rownum; i++) {
    rst->matrix[i] = new float[m2->colnum];
    for (int j = 0; j < m2->colnum; j++) {
      rst->matrix[i][j] = dot_prod(K, m1->matrix[i], m2->matrix[j]);
    }
  }
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  cout << "Calculation took "
       << std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
              .count()
       << " milliseconds.";
  return 0;
}

inline float dot_prod(int dim, float *v1, float *v2) {
  int vec1, vec2;
  long long sum = 0;
  for (int i = 0; i < dim; i++) {
    vec1 = (int)(v1[i] * 1e3);
    vec2 = (int)(v2[i] * 1e3);
    sum += (long long)vec1 * vec2;
  }
  double rst = sum / 1e6;
  return rst;
}
