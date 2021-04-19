#ifndef MULTY_MATRIX_MATRIX_H
#define MULTY_MATRIX_MATRIX_H

#include <vector>
#include <fstream>
#include <string>

class Matrix {
public:
    std::vector< std::vector<double> > matrix;
    int n;
    int m;

    explicit Matrix(const std::string& file_name) {
        std::ifstream fin(file_name);
        fin >> n >> m;
        matrix = std::vector< std::vector<double> >(n, std::vector<double>(m));
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j)
                fin >> matrix[i][j];
        }
    }
    Matrix() : matrix(std::vector< std::vector<double> >(0)), n(0), m(0) {};
    Matrix(int n, int m) : n(n), m(m) {
        matrix = std::vector< std::vector<double> >(n, std::vector<double>(m));
    };

    Matrix multiply(const Matrix& m2) {
        Matrix m3(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m2.m; j++) {
                double sum = 0;
                for (int k = 0; k < m; k++) {
                    sum += matrix[i][k] * m2.matrix[k][j];
                }
                m3.matrix[i][j] = sum;
            }
        }
        return m3;
    }

    std::vector< std::vector<Matrix> > splitted_blocks(int rows, int cols) {
        int rows_count = n / rows;
        int cols_count = m / cols;
        std::vector< std::vector<Matrix> > blocks(rows_count);
        for (int i = 0; i < rows_count; i++) {
            for (int j = 0; j < cols_count; j++) {
                Matrix tmp(rows, cols);
                for (int k = i * rows; k < (i + 1) * rows; k++) {
                    for (int l = j * cols; l < (j + 1) * cols; l++) {
                        tmp.matrix[k - i * rows][l - j * cols] = matrix[k][l];
                    }
                }
                blocks[i].push_back(tmp);
            }
        }
        return blocks;
    }

};

#endif //MULTY_MATRIX_MATRIX_H
