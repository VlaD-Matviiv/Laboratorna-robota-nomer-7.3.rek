// Lab 7.3.rek

#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void PrintRow(int** a, const int rowNo, const int colCount, int colNo) {
    cout << setw(4) << a[rowNo][colNo];
    if (colNo < colCount - 1)
        PrintRow(a, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

void PrintRows(int** a, const int rowCount, const int colCount, int rowNo) {
    PrintRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        PrintRows(a, rowCount, colCount, rowNo + 1);
    else
        cout << endl;
}

void InputRow(int** a, const int rowNo, const int colCount, int colNo) {
    cout << "a[" << rowNo << "][" << colNo << "] = ";
    cin >> a[rowNo][colNo];
    if (colNo < colCount - 1)
        InputRow(a, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

void InputRows(int** a, const int rowCount, const int colCount, int rowNo) {
    InputRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        InputRows(a, rowCount, colCount, rowNo + 1);
    else
        cout << endl;
}

void CreateRow(int** a, const int rowNo, const int colCount, const int Low, const int High, int colNo) {
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < colCount - 1)
        CreateRow(a, rowNo, colCount, Low, High, colNo + 1);
}

void CreateRows(int** a, const int rowCount, const int colCount, const int Low, const int High, int rowNo) {
    CreateRow(a, rowNo, colCount, Low, High, 0);
    if (rowNo < rowCount - 1)
        CreateRows(a, rowCount, colCount, Low, High, rowNo + 1);
}

void Part1_ZeroCol(int** a, const int rowCount, bool& result, int colNo, int rowNo, int& k_zero) {
    if (a[rowNo][colNo] == 0) {
        result = true;
        k_zero++;
    }
    else if (rowNo < rowCount - 1)
        Part1_ZeroCol(a, rowCount, result, colNo, rowNo + 1, k_zero);
}

void Part1_CountCol(int** a, const int rowCount, int& count, int colNo, int rowNo) {
    if (a[rowNo][colNo] > 0)
        count++;
    if (rowNo < rowCount - 1)
        Part1_CountCol(a, rowCount, count, colNo, rowNo + 1);
}

void Part1_CountCols(int** a, const int rowCount, const int colCount, int& count, bool& result, int colNo) {
    int k_zero = 0;
    Part1_ZeroCol(a, rowCount, result, colNo, 0, k_zero);
    if (k_zero > 0)
        Part1_CountCol(a, rowCount, count, colNo, 0);
    if (colNo < colCount - 1)
        Part1_CountCols(a, rowCount, colCount, count, result, colNo + 1);
}

bool IsMaxInRowN(int** a, const int rowNo, const int max, const int colCount, int colNo) {
    if (a[rowNo][colNo] > max)
        return false;
    if (colNo < colCount - 1)
        return IsMaxInRowN(a, rowNo, max, colCount, colNo + 1);
    else
        return true;
}

bool IsMinInColK(int** a, const int colNo, const int min, const int rowCount, int rowNo) {
    if (a[rowNo][colNo] < min)
        return false;
    if (rowNo < rowCount - 1)
        return IsMinInColK(a, colNo, min, rowCount, rowNo + 1);
    else
        return true;
}

void Part2_SaddlePointRow(int** a, const int rowCount, const int colCount, int& No, const int rowNo, int colNo) {
    if (IsMaxInRowN(a, rowNo, a[rowNo][colNo], colCount, 0) && IsMinInColK(a, colNo, a[rowNo][colNo], rowCount, 0)) {
        cout << setw(4) << ++No << setw(6) << rowNo << setw(6) << colNo << endl;
    }
    if (colNo < colCount - 1)
        Part2_SaddlePointRow(a, rowCount, colCount, No, rowNo, colNo + 1);
}

void Part2_SaddlePointRows(int** a, const int rowCount, const int colCount, int& No, int rowNo) {
    Part2_SaddlePointRow(a, rowCount, colCount, No, rowNo, 0);
    if (rowNo < rowCount - 1)
        Part2_SaddlePointRows(a, rowCount, colCount, No, rowNo + 1);
}

void SortColumnsByCharacteristic(int** a, const int rowCount, const int colCount) {
    int* characteristics = new int[colCount];

    // Calculate the characteristic for each column
    for (int j = 0; j < colCount; j++) {
        characteristics[j] = 0;
        for (int i = 0; i < rowCount; i++) {
            if (a[i][j] < 0 && a[i][j] % 2 != 0) { // Check for negative odd elements
                characteristics[j] += abs(a[i][j]);
            }
        }
    }

    // Sort the columns based on their characteristics using bubble sort
    for (int j = 0; j < colCount - 1; j++) {
        for (int k = 0; k < colCount - j - 1; k++) {
            if (characteristics[k] > characteristics[k + 1]) {
                // Swap characteristics
                swap(characteristics[k], characteristics[k + 1]);
                // Swap the columns in the matrix
                for (int i = 0; i < rowCount; i++) {
                    swap(a[i][k], a[i][k + 1]);
                }
            }
        }
    }

    delete[] characteristics;
}

int SumColumnsWithNegative(int** a, const int rowCount, const int colCount) {
    int sum = 0;
    for (int j = 0; j < colCount; j++) {
        bool hasNegative = false;
        for (int i = 0; i < rowCount; i++) {
            if (a[i][j] < 0) {
                hasNegative = true;
                break;
            }
        }
        if (hasNegative) {
            for (int i = 0; i < rowCount; i++) {
                sum += a[i][j];
            }
        }
    }
    return sum;
}

int main() {
    srand((unsigned)time(NULL));
    int Low = -7;
    int High = 7;
    int rowCount, colCount;
    cout << "rowCount = "; cin >> rowCount;
    cout << "colCount = "; cin >> colCount;

    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    InputRows(a, rowCount, colCount, 0);
    PrintRows(a, rowCount, colCount, 0);

    int count = 0;
    bool result = false;
    Part1_CountCols(a, rowCount, colCount, count, result, 0);
    if (result)
        cout << "count = " << count << endl;
    else
        cout << "there are no zero elements" << endl;

    cout << endl;

    cout << "Saddle points: max in row & min in col" << endl;
    cout << setw(4) << "No" << setw(6) << "Row" << setw(6) << "Col" << endl;
    int No = 0;
    Part2_SaddlePointRows(a, rowCount, colCount, No, 0);
    cout << endl;

    // Sort the columns based on their characteristics
    SortColumnsByCharacteristic(a, rowCount, colCount);
    cout << "Matrix after sorting columns by characteristic:" << endl;
    PrintRows(a, rowCount, colCount, 0);

    // Calculate and print the sum of columns with negative elements
    int sum = SumColumnsWithNegative(a, rowCount, colCount);
    cout << "Sum of elements in columns with at least one negative element: " << sum << endl;

    // Cleanup
    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}
