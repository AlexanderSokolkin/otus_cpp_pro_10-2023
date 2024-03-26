#include <iostream>
#include "matrix.h"




int main(int, char**)
{
	Matrix<int, 0> matrix;

	for (int i = 0, j = 9; i < 10; ++i, --j) {
		matrix[i][i] = i;
		matrix[i][j] = j;
	}

	for (int i = 1; i < 9; ++i) {
		for (int j = 1; j < 9; ++j) {
			std::cout << matrix[i][j] << (j != 8 ? " " : "");
		}
		std::cout << std::endl;
	}

	std::cout << "matrix size = " << matrix.size() << std::endl;

	for (auto elem : matrix) {
		auto [row, col, val] = elem;
		std::cout << "[" << row << "," << col << "] = " << val << std::endl;
	}

	return 0;
}

