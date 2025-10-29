#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

vector<vector<int>> readMatrix(ifstream &input, int size) {
    vector<vector<int>> matrix(size, vector<int>(size));
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            input >> matrix[row][col];
        }
    }
    return matrix;
}

void printMatrix(const vector<vector<int>> &matrix) {
    for (int row = 0; row < matrix.size(); row++) {
        for (int col = 0; col < matrix[row].size(); col++) {
            cout << matrix[row][col] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<int>> addMatrices(const vector<vector<int>> &A, const vector<vector<int>> &B) {
    int size = A.size();
    vector<vector<int>> result(size, vector<int>(size));
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            result[row][col] = A[row][col] + B[row][col];
        }
    }
    return result;
}

vector<vector<int>> multiplyMatrices(const vector<vector<int>> &A, const vector<vector<int>> &B) {
    int size = A.size();
    vector<vector<int>> result(size, vector<int>(size, 0));
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            for (int k = 0; k < size; k++) {
                result[row][col] += A[row][k] * B[k][col];
            }
        }
    }
    return result;
}

int main() {
    string fileName;
    cout << "Enter the input file name: ";
    cin >> fileName;

    ifstream inputFile(fileName);
    if (!inputFile) {
        cout << "Error: Could not open the file." << endl;
        return 1;
    }

    int size;
    inputFile >> size;

    vector<vector<int>> matrixA = readMatrix(inputFile, size);
    vector<vector<int>> matrixB = readMatrix(inputFile, size);

    cout << "Matrix A:" << endl;
    printMatrix(matrixA);

    cout << "Matrix B:" << endl;
    printMatrix(matrixB);

    cout << "Sum of A and B:" << endl;
    printMatrix(addMatrices(matrixA, matrixB));

    cout << "Product of A and B:" << endl;
    printMatrix(multiplyMatrices(matrixA, matrixB));

    return 0;
}
