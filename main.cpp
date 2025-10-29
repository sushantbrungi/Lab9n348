#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;

using Matrix = vector<vector<int>>;

int cellWidth(const Matrix &M) {
    int mx = 0;
    for (const auto &row : M)
        for (int v : row)
            mx = max(mx, abs(v));
    int w = 1;
    while (mx >= 10) { mx /= 10; ++w; }
    return max(2, w + 1); 
}

void printMatrix(const Matrix &matrix) {
    if (matrix.empty()) { cout << "(empty)\n\n"; return; }
    int w = cellWidth(matrix);
    for (const auto &row : matrix) {
        for (int val : row) cout << setw(w) << val;
        cout << '\n';
    }
    cout << '\n';
}

Matrix readMatrix(ifstream &input, int n) {
    Matrix M(n, vector<int>(n));
    for (int r = 0; r < n; ++r)
        for (int c = 0; c < n; ++c)
            input >> M[r][c];
    return M;
}

Matrix addMatrices(const Matrix &A, const Matrix &B) {
    int n = (int)A.size();
    Matrix C(n, vector<int>(n));
    for (int r = 0; r < n; ++r)
        for (int c = 0; c < n; ++c)
            C[r][c] = A[r][c] + B[r][c];
    return C;
}

Matrix multiplyMatrices(const Matrix &A, const Matrix &B) {
    int n = (int)A.size();
    Matrix C(n, vector<int>(n, 0));
    for (int r = 0; r < n; ++r)
        for (int k = 0; k < n; ++k) {
            int aik = A[r][k];
            for (int c = 0; c < n; ++c)
                C[r][c] += aik * B[k][c];
        }
    return C;
}

pair<long long,long long> diagonalSums(const Matrix &M) {
    int n = (int)M.size();
    long long d1 = 0, d2 = 0;
    for (int i = 0; i < n; ++i) {
        d1 += M[i][i];
        d2 += M[i][n - 1 - i];
    }
    return {d1, d2};
}

bool swapRows(Matrix &M, int r1, int r2) {
    int n = (int)M.size();
    if (r1 < 0 || r2 < 0 || r1 >= n || r2 >= n) return false;
    swap(M[r1], M[r2]);
    return true;
}

bool swapCols(Matrix &M, int c1, int c2) {
    int n = (int)M.size();
    if (c1 < 0 || c2 < 0 || c1 >= n || c2 >= n) return false;
    for (int r = 0; r < n; ++r) swap(M[r][c1], M[r][c2]);
    return true;
}

bool updateCell(Matrix &M, int r, int c, int val) {
    int n = (int)M.size();
    if (r < 0 || c < 0 || r >= n || c >= n) return false;
    M[r][c] = val;
    return true;
}

int main() {
    string fileName;
    cout << "Enter the input file name: ";
    cin >> fileName;

    ifstream inputFile(fileName);
    if (!inputFile) {
        cout << "Error: Could not open the file.\n";
        return 1;
    }

    int n;
    if (!(inputFile >> n) || n <= 0) {
        cout << "Error: First value must be a positive integer N.\n";
        return 1;
    }

    Matrix A = readMatrix(inputFile, n);
    Matrix B = readMatrix(inputFile, n);

    cout << "Matrix A:\n"; printMatrix(A);
    cout << "Matrix B:\n"; printMatrix(B);

    cout << "A + B:\n"; printMatrix(addMatrices(A, B));

    cout << "A * B:\n"; printMatrix(multiplyMatrices(A, B));

    auto [d1A, d2A] = diagonalSums(A);
    cout << "diagonal sums of A main: " << d1A << ", secondary: " << d2A << "\n";
    auto [d1B, d2B] = diagonalSums(B);
    cout << "diagonal sums of B main: " << d1B << ", secondary: " << d2B << "\n\n";

    if (n >= 2) {
        Matrix Arows = A;
        if (swapRows(Arows, 0, 1)) {
            cout << "A after swapping rows 0 and 1:\n";
            printMatrix(Arows);
        }

        Matrix Acols = A;
        if (swapCols(Acols, 0, 1)) {
            cout << "A after swapping cols 0 and 1:\n";
            printMatrix(Acols);
        }
    } else {
        cout << "(Skipping row/col swaps: N < 2)\n\n";
    }

    Matrix Aupd = A;
    if (updateCell(Aupd, 0, 0, 999)) {
        cout << "A after updating A[0][0] = 999:\n";
        printMatrix(Aupd);
    } else {
        cout << "(Skipping update: invalid indices)\n\n";
    }

    return 0;
}
