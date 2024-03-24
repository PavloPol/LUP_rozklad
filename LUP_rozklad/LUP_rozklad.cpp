// LUP_rozklad.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
using namespace std;

void print_matrix(const vector<vector<double>>& matrix, int n) 
{
    for (int i = 0; i < n; i++)
    {
        cout << "[" << matrix[i][0];
        for (int j = 1; j < n; j++)
        {
            cout << ", " << matrix[i][j];
        }
        cout << "]" << endl;
    }
    cout << endl << endl;
}

void print_vector(const vector<double>& matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "[";
        cout << matrix[i];
        cout << "]" << endl;
    }
    cout << endl;
}


void hand_fill(vector<vector<double>> &matrtix, int n) 
{
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            cout << "Enter " << i + 1 << ", " << j + 1 << " coefficient\n";
            cin >> matrtix[i][j];
        }
    }
    cout << "\nEntered matrix of coefficients\n";
    print_matrix(matrtix, n);
}

void hand_fill(vector<double>& matrtix, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "Enter " << i + 1 << " b element\n";
        cin >> matrtix[i];
    }
    cout << "\nEntered b vector\n";
    print_vector(matrtix, n);
}

void LU_decompos(const vector<vector<double>>& matrix, vector<vector<double>>& lmatrix, vector<vector<double>>& umatrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i >= j)
            {
                double sum = 0;
                for (int k = 0; k < j; k++)
                {
                    sum += lmatrix[i][k] * umatrix[k][j];
                }
                lmatrix[i][j] = matrix[i][j] - sum;
                if (i == j)
                {
                    umatrix[i][j] = 1;
                }
            }
            else
            {
                double sum = 0;
                for (int k = 0; k < i; k++)
                {
                    sum += umatrix[i][k] * umatrix[k][j];
                }
                umatrix[i][j] = (matrix[i][j] - sum) / lmatrix[i][i];
            }
        }
    }
}

vector<double> LU_linear(const vector<vector<double>> L, const vector<vector<double>> U, const vector<double> b, int n) 
{
    vector<double> x(n, 0);
    vector<double> y(n, 0);

    y[0] = b[0] / L[0][0];
    for (int i = 1; i < n; i++) 
    {
        double sum = 0;
        for (int k = 0; k < i; k++)
        {
            sum += L[i][k] * y[k];
        }
        y[i] = (b[i] - sum) / L[i][i];
    }

    x[n - 1] = y[n - 1];
    for (int i = n - 2; i >= 0; i--) 
    {
        double sum = 0;
        for (int k = i + 1; k < n; k++)
        {
            sum += U[i][k] * x[k];
        }
        x[i] = y[i] - sum;
    }

    return x;
}

int main()
{
    int n;
    cout << "Enter number of x:\n";
    cin >> n;

    vector<vector<double>> matrix (n, vector<double>(n, 0));
    vector<double> b(n, 0);

    hand_fill(matrix, n);
    hand_fill(b, n);

    vector<vector<double>> lmatrix(n, vector<double>(n, 0));
    vector<vector<double>> umatrix(n, vector<double>(n, 0));

    LU_decompos(matrix, lmatrix, umatrix, n);

    vector<double> x;
    x = LU_linear(lmatrix, umatrix, b, n);
    cout << "X vector\n";
    print_vector(x, n);

    system("pause");
}

