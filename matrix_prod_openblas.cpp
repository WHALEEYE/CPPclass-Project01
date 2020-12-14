// #include <iostream>
// #include <ctime>
// #include <chrono>
// #include <cblas.h>
// using namespace std;

// int main()
// {
//     int N, K, M;
//     cout << "Enter N, K, M: ";
//     cin >> N >> K >> M;
//     std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
//     const enum CBLAS_ORDER Order = CblasRowMajor;
//     const enum CBLAS_TRANSPOSE TransA = CblasNoTrans;
//     const enum CBLAS_TRANSPOSE TransB = CblasNoTrans;
//     const float alpha = 1;
//     const float beta = 0;
//     const int lda = K;
//     const int ldb = M;
//     const int ldc = M;
//     float *A = new float[N * K]();
//     float *B = new float[M * K]();
//     A[0] = 9.62;
//     B[0] = 8.88;
//     float *C = new float[M * N];
//     cblas_sgemm(Order, TransA, TransB, N, M, K, alpha, A, lda, B, ldb, beta, C, ldc);    
//     std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
//     cout << "Calculation took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds."<< endl;
//     return 0;
// }
