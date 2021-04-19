#ifndef MULTY_MATRIX_MULTYS_H
#define MULTY_MATRIX_MULTYS_H

#include "matrix.h"
#include <windows.h>
#include <vector>
#include <mutex>

Matrix A, B, C;
std::vector< std::vector<Matrix> > A_by_blocks;
std::vector< std::vector<Matrix> > B_by_blocks;

DWORD WINAPI multy_row_by_col(CONST LPVOID lpParam) {

    int* row_and_col = (int*)lpParam;
    int row = row_and_col[0];
    int col = row_and_col[1];

    double sum = 0;
    for (int i = 0; i < A.m; i++)
        sum += A.matrix[row][i] * B.matrix[i][col];
    C.matrix[row][col] = sum;

    ExitThread(0);

}

std::mutex locker;
DWORD WINAPI multy_col_by_row(CONST LPVOID lpParam) {

    int* col_and_row = (int*)lpParam;
    int col = col_and_row[0];
    int row = col_and_row[1];
    Matrix tmp(A.n, B.m);

    for (int i = 0; i < A.n; i++) {
        for (int j = 0; j < B.m; j++)
            tmp.matrix[i][j] = A.matrix[i][col] * B.matrix[row][j];
    }

    locker.lock();
    for (int i = 0; i < C.n; i++) {
        for (int j = 0; j < C.m; j++)
            C.matrix[i][j] += tmp.matrix[i][j];
    }
    locker.unlock();

    ExitThread(0);

}

std::mutex** lockers;
DWORD WINAPI multy_blocks(CONST LPVOID lpParam) {

    int* row_and_col = (int*)lpParam;
    int row = row_and_col[0];
    int col = row_and_col[1];
    std::vector<Matrix> B_blocks_tmp;

    for (auto & B_by_block : B_by_blocks)
        B_blocks_tmp.push_back(B_by_block[col]);

    Matrix result(A_by_blocks[row][0].n, B_blocks_tmp[0].m);
    for (int i = 0; i < A_by_blocks[row].size(); i++) {
        Matrix tmp = A_by_blocks[row][i].multiply(B_blocks_tmp[i]);
        for (int k = 0; k < tmp.n; k++) {
            for (int l = 0; l < tmp.m; l++)
                result.matrix[k][l] += tmp.matrix[k][l];
        }
    }

    lockers[row][col].lock();
    for (int i = 0; i < result.n; i++) {
        for (int j = 0; j < result.m; j++)
            C.matrix[row * result.n + i][col * result.m + j] = result.matrix[i][j];
    }
    lockers[row][col].unlock();

    ExitThread(0);

}

#endif //MULTY_MATRIX_MULTYS_H
