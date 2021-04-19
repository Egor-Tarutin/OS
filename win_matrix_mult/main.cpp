#include <iostream>
#include <queue>
#include <chrono>
#include "Multys.h"

void print_matrix(const Matrix& matrix, std::ostream& out) {
    for(int i = 0; i < matrix.matrix.size(); ++i) {
        for(int j = 0; j < matrix.matrix[i].size(); ++j) {
            out << matrix.matrix[i][j] << " ";
        }
        out << '\n';
    }
}

int main() {

    A = Matrix("simple_input.txt");
    B = Matrix("simple_input.txt");

    int streams = 10;

    std::cout << "Simple multiplying:\n";
    C = A.multiply(B);
    C.n = A.n;
    C.m = B.m;

    {
        auto begin = std::chrono::steady_clock::now();

        print_matrix(C, std::cout);

        auto end = std::chrono::steady_clock::now();
        std::cout << "Working time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms\n";

    }

    C = Matrix(A.n, B.m);


    std::cout << "Row by col multiplying:\n";
    {//===============================
        HANDLE* handle = new HANDLE[streams];

        auto begin = std::chrono::steady_clock::now();

        int count_of_threads = 0;
        std::queue< std::pair<int, int> > indices;

        int** inds = new int*[streams];

        for (int i = 0; i < A.n; i++) {
            for (int j = 0; j < B.m; j++)
                indices.push(std::make_pair(i, j));
        }

        for (int i = 0, j = 0; i < A.n * B.m; i++) {
            std::pair<int, int> tmp = indices.front();
            indices.pop();
            if(j >= streams)
                j = 0;

            inds[j] = new int[2]{tmp.first, tmp.second};
            if (count_of_threads < streams) {
                handle[i] = CreateThread(nullptr, 0, &multy_row_by_col, static_cast<void*>(inds[j]), 0, nullptr);
                ++count_of_threads;
            }
            else {
                WaitForSingleObject(handle[0], INFINITE);
                handle[0] = CreateThread(nullptr, 0, &multy_row_by_col, static_cast<void*>(inds[j]), 0, nullptr);
            }

        }

        WaitForMultipleObjects(streams, handle, TRUE, INFINITE);

        auto end = std::chrono::steady_clock::now();


    } //==============================

    print_matrix(C, std::cout);

    std::cout << "Col by row multiplying:\n";
    {
        HANDLE* handle = new HANDLE[streams];

        auto begin = std::chrono::steady_clock::now();

        int count_of_threads = 0;
        std::queue< std::pair<int, int> > indices;

        int** inds = new int*[streams];

        for (int i = 0; i < A.n; i++) {
            for (int j = 0; j < B.m; j++)
                indices.push(std::make_pair(i, j));
        }

        for (int i = 0, j = 0; i < A.n * B.m; i++) {
            std::pair<int, int> tmp = indices.front();
            indices.pop();
            if(j >= streams)
                j = 0;

            inds[j] = new int[2]{tmp.first, tmp.second};
            if (count_of_threads < streams) {
                handle[i] = CreateThread(nullptr, 0, &multy_col_by_row, static_cast<void*>(inds[j]), 0, nullptr);
                ++count_of_threads;
            }
            else {
                WaitForSingleObject(handle[0], INFINITE);
                handle[0] = CreateThread(nullptr, 0, &multy_col_by_row, static_cast<void*>(inds[j]), 0, nullptr);
            }

        }

        WaitForMultipleObjects(streams, handle, TRUE, INFINITE);

        auto end = std::chrono::steady_clock::now();

        std::cout << "Working time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms\n";

    }

    print_matrix(C, std::cout);

    std::cout << "By blocks multiplying:\n";
    {
        A_by_blocks = A.splitted_blocks(3,3);
        B_by_blocks = B.splitted_blocks(3,3);

        lockers = new std::mutex*[streams];
        for(int i = 0; i < streams; ++i)
            lockers[i] = new std::mutex[streams];

        HANDLE* handle = new HANDLE[streams];

        auto begin = std::chrono::steady_clock::now();

        int count_of_threads = 0;
        std::queue< std::pair<int, int> > indices;

        int** inds = new int*[streams];

        for (int i = 0; i < A_by_blocks.size(); i++) {
            for (int j = 0; j < B_by_blocks[0].size(); j++) {
                indices.push(std::make_pair(i,j));
            }
        }

        for (int i = 0, j = 0; i < A_by_blocks.size() * B_by_blocks[0].size(); i++) {
            std::pair<int, int> tmp = indices.front();
            indices.pop();
            if(j >= streams)
                j = 0;

            inds[j] = new int[2]{tmp.first, tmp.second};
            if (count_of_threads < streams) {
                handle[i] = CreateThread(nullptr, 0, &multy_blocks, static_cast<void*>(inds[j]), 0, nullptr);
                ++count_of_threads;
            }
            else {
                WaitForSingleObject(handle[0], INFINITE);
                handle[0] = CreateThread(nullptr, 0, &multy_blocks, static_cast<void*>(inds[j]), 0, nullptr);
            }

        }

        WaitForMultipleObjects(streams, handle, TRUE, INFINITE);

        auto end = std::chrono::steady_clock::now();

        std::cout << "Working time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms\n";
    }

    print_matrix(C, std::cout);

    return 0;
}
