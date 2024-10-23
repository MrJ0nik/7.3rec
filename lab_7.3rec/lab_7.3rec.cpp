#include <iostream>
#include <iomanip>
using namespace std;

void PrintMatrix(int** matrix, int rowCount, int colCount) {
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            cout << setw(4) << matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void SingleShift(int** matrix, int n) {
    int temp = matrix[0][0];

    for (int i = 0; i < n - 1; i++) {
        matrix[i][0] = matrix[i + 1][0];
    }

    for (int j = 0; j < n - 1; j++) {
        matrix[n - 1][j] = matrix[n - 1][j + 1];
    }

    for (int i = n - 1; i > 0; i--) {
        matrix[i][n - 1] = matrix[i - 1][n - 1];
    }

    for (int j = n - 1; j > 1; j--) {
        matrix[0][j] = matrix[0][j - 1];
    }
    matrix[0][1] = temp;
}

void CyclicShiftMatrixRecursive(int** matrix, int n, int k) {
    if (k == 0) return;
    SingleShift(matrix, n);
    CyclicShiftMatrixRecursive(matrix, n, k - 1);
}

int CountZerosInColRecursive(int** matrix, int rowCount, int colNo, int row = 0) {
    if (row == rowCount) return 0;
    int zeroCount = (matrix[row][colNo] == 0) ? 1 : 0;
    return zeroCount + CountZerosInColRecursive(matrix, rowCount, colNo, row + 1);
}

int FindLastColumnWithMaxZerosRecursive(int** matrix, int rowCount, int colCount, int col = 0, int maxZeros = 0, int lastCol = -1) {
    if (col == colCount) return lastCol;

    int zeroCount = CountZerosInColRecursive(matrix, rowCount, col);

    if (zeroCount >= maxZeros) {
        maxZeros = zeroCount;
        lastCol = col;
    }

    return FindLastColumnWithMaxZerosRecursive(matrix, rowCount, colCount, col + 1, maxZeros, lastCol);
}

int main() {
    int n, k;
    cout << "Enter the size of the matrix (n x n): ";
    cin >> n;
    cout << "Enter the number of positions to shift (k): ";
    cin >> k;

    int** matrix = new int* [n];
    for (int i = 0; i < n; i++)
        matrix[i] = new int[n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "matrix[" << i << "][" << j << "] = ";
            cin >> matrix[i][j];
        }
    }

    cout << "Original matrix:" << endl;
    PrintMatrix(matrix, n, n);

    CyclicShiftMatrixRecursive(matrix, n, k);

    cout << "Matrix after cyclic shift:" << endl;
    PrintMatrix(matrix, n, n);

    int lastCol = FindLastColumnWithMaxZerosRecursive(matrix, n, n);

    cout << "The last column with the most zeros is: " << lastCol << endl;

    for (int i = 0; i < n; i++)
        delete[] matrix[i];
    delete[] matrix;

    return 0;
}
