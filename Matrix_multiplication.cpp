#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

void matrix_mult(double** A, int A_lines, int A_columns, double** B, int B_lines, int B_columns, double** res);
int min_index(double* arr, int length);
int max_index(double* arr, int length);

//C:\\Users\\Daria\\CLionProjects\\Matrix_multiplication\\sellers.txt
int main() {
    string path;
    cin >> path;
    ifstream sellers(path);
    if(!sellers.is_open()) {
        cout << "Can not find file with path: " << path;
        return 0;
    }
    int A_lines, A_columns, B_lines, B_columns;
    sellers >> A_lines >> A_columns >> B_lines >> B_columns;
    double **A = new (double* [A_lines]);
    for (int i = 0; i < A_lines; i++) {
        A[i] = new double [A_columns];
        for (int j = 0; j < A_columns; j++) {
            sellers >> A[i][j];
        }
    }
    double **B = new (double* [B_lines]);
    for (int i = 0; i < B_lines; i++) {
        B[i] = new double [B_columns];
        for (int j = 0; j < B_columns; j++) {
            sellers >> B[i][j];
        }
    }
    double **C = new (double* [A_lines]);
    for(int i = 0; i < A_lines; i++) {
        C[i] = new double[B_columns];
        for (int j = 0; j < B_columns; j++) {
            C[i][j] = 0;
        }
    }
    cout << "Table A" << endl;
    for(int i = 0; i < A_lines; i ++) {
        for (int j = 0; j < A_columns; j++) {
            cout << A[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl << "Table B" << endl;;
    for(int i = 0; i < B_lines; i ++) {
        for (int j = 0; j < B_columns; j++) {
            cout << B[i][j] << "\t";
        }
        cout << endl;
    }
    matrix_mult(A, A_lines, A_columns, B, B_lines, B_columns, C);
    cout << endl << "Result Table" << endl;
    for(int i = 0; i < A_lines; i ++) {
        for (int j = 0; j < B_columns; j++) {
            cout << C[i][j] << "\t";
        }
        cout << endl;
    }
    double *income = new (double [A_lines]), total_income = 0;
    double *commission = new (double [A_lines]), total_commission = 0;
    for(int i = 0; i < A_lines; i ++) {
        income[i] = 0;
        commission[i] = 0;
        for (int j = 0; j < B_columns; j++) {
            income[i] += C[i][j];
            commission[i] = C[i][j];
        }
        total_income += income[i];
        total_commission += commission[i];
    }
    cout << endl << "1) max: " << max_index(income, A_lines) + 1 << " min: " << min_index(income, A_lines) + 1 << endl;
    cout << "2) max: " << max_index(commission, A_lines) + 1 << " min: " << min_index(commission, A_lines) + 1 << endl;
    cout << "3) " << total_income << endl << "4) " << total_commission << endl << "5) " <<  total_income - total_commission;

    sellers.close();
    for (int i = 0; i < A_lines; i++) {
        delete[](A[i]);

    }
    for (int i = 0; i < B_lines; i++) {
        delete[](B[i]);
    }
    for (int i = 0; i < A_lines; i++) {
        delete[](C[i]);
    }
    delete[](A);
    delete[](B);
    delete[](C);
    delete[](income);
    delete[](commission);
    return 0;
}

void matrix_mult(double** A, int A_lines, int A_columns, double** B, int B_lines, int B_columns, double** res) {
    double **buf;
    if(A_columns != B_lines) {
        cout << "Can not do multiplication!";
        return;
    }
    buf = new (double* [A_lines]);
    for(int i = 0; i < A_lines; i++) {
        buf[i] = new double [B_columns];
        for(int j = 0; j < B_columns; j++) {
            buf[i][j] = 0;
            for(int n = 0; n < A_columns; n++) {
                buf[i][j] += A[i][n] * B[n][j];
            }
        }
    }
    for(int i = 0; i < A_lines; i++) {
        for(int j = 0; j < B_columns; j++) {
            res[i][j] = buf[i][j];
        }
        delete[](res[i]);
    }
    delete(res);
    return;
}

int min_index(double* arr, int length) {
    double min = arr[0];
    int index = 0;
    for(int i = 1; i < length; i++) {
        if(arr[i] < min) {
            min = arr[i];
            index = i;
        }
    }
    return index;
}

int max_index(double* arr, int length) {
    double max = arr[0];
    int index = 0;
    for(int i = 1; i < length; i++) {
        if(arr[i] > max) {
            max = arr[i];
            index = i;
        }
    }
    return index;
}