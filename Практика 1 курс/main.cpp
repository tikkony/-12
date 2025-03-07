#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Функция для вычисления минорной матрицы
vector<vector<double>> getMinor(const vector<vector<double>>& matrix, int row, int col) {
    int n = matrix.size();
    vector<vector<double>> minorMatrix(n - 1, vector<double>(n - 1));

    for (int i = 0, minorRow = 0; i < n; ++i) {
        if (i == row) continue; // Пропустить указанную строку

        for (int j = 0, minorCol = 0; j < n; ++j) {
            if (j == col) continue; // Пропустить указанный столбец

            minorMatrix[minorRow][minorCol] = matrix[i][j];
            ++minorCol;
        }
        ++minorRow;
    }
    return minorMatrix;
}

// Рекурсивная функция для вычисления определителя
double determinant(const vector<vector<double>>& matrix) {
    int n = matrix.size();

    if (n == 1) return matrix[0][0];

    if (n == 2) return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

    double det = 0.0;

    for (int col = 0; col < n; ++col) {
        vector<vector<double>> minorMatrix = getMinor(matrix, 0, col);
        det += (col % 2 == 0 ? 1 : -1) * matrix[0][col] * determinant(minorMatrix);
    }

    return det;
}

// Функция для безопасного ввода числа с проверкой
double safeInput() {
    double value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cin.clear(); // Сбросить состояние потока
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорировать неверный ввод
            cout << "Некорректный ввод. Пожалуйста, введите число: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорировать оставшиеся символы в строке
            return value;
        }
    }
}

int main() {
    int n;

    cout << "Введите размер матрицы (положительное целое число): ";
    while (true) {
        cin >> n;
        if (cin.fail() || n <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некорректный ввод. Пожалуйста, введите положительное целое число: ";
        } else {
            break;
        }
    }

    vector<vector<double>> matrix(n, vector<double>(n));

    cout << "Введите элементы матрицы построчно:" << endl;
    
    for (int i = 0; i < n; ++i) {
        cout << "Строка " << i + 1 << ": ";
        for (int j = 0; j < n; ++j) {
            cout << "Элемент [" << i + 1 << "][" << j + 1 << "]: ";
            matrix[i][j] = safeInput();
        }
    }

    double result = determinant(matrix);

    cout << "Определитель матрицы: " << result << endl;

    return 0;
}