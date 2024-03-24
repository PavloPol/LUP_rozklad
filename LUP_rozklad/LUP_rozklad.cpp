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

void print_matrix(const vector<vector<int>>& matrix, int n)
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

void hand_fill(vector<vector<double>> &matrtix, int n) 
{
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            cout << "Enter " << i + 1 << ", " << j + 1 << " element\n";
            cin >> matrtix[i][j];
        }
    }
    cout << "\nEntered matrix\n";
    print_matrix(matrtix, n);
}

void random_fill(vector<vector<double>>& matrix, int n) 
{
    srand(time(NULL));
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            matrix[i][j] = rand() % 100 + 1;
        }
    }
    cout << "Random matrix\n";
    print_matrix(matrix, n);
}

void LUP_decompos(const vector<vector<double>>& matrix, vector<vector<double>> &lmatrix, vector<vector<double>>& umatrix, vector<vector<int>>& pmatrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        pmatrix[i][i] = 1;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) 
        {
            if (i >= j) 
            {
                int sum = 0;
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
                int sum = 0;
                for (int k = 0; k < i; k++)
                {
                    sum += umatrix[i][k] * umatrix[k][j];
                }
                umatrix[i][j] = (matrix[i][j] - sum) / lmatrix[i][i];
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        int max_index = i;
        for (int j = i + 1; j < n; j++)
        {
            if (abs(matrix[j][i]) > abs(matrix[max_index][i]))
            {
                max_index = j;
            }
        }
        if (max_index != i)
        {
            swap(pmatrix[i], pmatrix[max_index]);
        }
    }
}

int main()
{
    int n;
    cout << "Enter size of the matrix:\n";
    cin >> n;
    vector<vector<double>> matrix (n, vector<double>(n, 0));
    while(true) 
    {
        int choose = 0;
        cout << "Choose the way to fill matrix (1 - by hand, 2 - random):\n";
        cin >> choose;
        if (choose == 1) 
        {
            hand_fill(matrix, n);
            break;
        }
        if (choose == 2) 
        {
            random_fill(matrix, n);
            break;
        }
    }
    vector<vector<double>> lmatrix(n, vector<double>(n, 0));
    vector<vector<double>> umatrix(n, vector<double>(n, 0));
    vector<vector<int>> pmatrix(n, vector<int>(n, 0));

    LUP_decompos(matrix, lmatrix, umatrix, pmatrix, n);

    cout << "L\n";
    print_matrix(lmatrix, n);
    cout << "U\n";
    print_matrix(umatrix, n);
    cout << "P\n";
    print_matrix(pmatrix, n);

    system("pause");
}



//void LU_decompos(const vector<vector<double>>& matrix, vector<vector<double>>& lmatrix, vector<vector<double>>& umatrix, int n)
//{
//    for (int i = 0; i < n; i++)
//    {
//        for (int j = 0; j < n; j++)
//        {
//            if (i >= j)
//            {
//                int sum = 0;
//                for (int k = 0; k < j; k++)
//                {
//                    sum += lmatrix[i][k] * umatrix[k][j];
//                }
//                lmatrix[i][j] = matrix[i][j] - sum;
//                if (i == j)
//                {
//                    umatrix[i][j] = 1;
//                }
//            }
//            else
//            {
//                int sum = 0;
//                for (int k = 0; k < i; k++)
//                {
//                    sum += umatrix[i][k] * umatrix[k][j];
//                }
//                umatrix[i][j] = (matrix[i][j] - sum) / lmatrix[i][i];
//            }
//        }
//    }
//}

