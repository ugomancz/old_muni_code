#include <iostream>
#include <vector>

class Matrix {
	std::vector<std::vector<int>> _matrix;

public:
	Matrix(std::vector<std::vector<int>> vec);

	// try adding explicit here
	Matrix(int rows, int cols = -1);
};

Matrix::Matrix(std::vector<std::vector<int>> vec)
  : _matrix(std::move(vec)) {}

Matrix::Matrix(int rows, int cols)
  : _matrix(rows,
            std::vector<int>(cols == -1 ? rows : cols)) {}

void f(const Matrix& matrix) { /* ... */ }

int main() {
	std::vector<std::vector<int>> vec{
		{1, 2, 3}, {4, 5, 6} };
	f(vec);
	f(7);
}
