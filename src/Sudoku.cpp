/*
 * Sudoku.cpp
 *
 *  Created on: 6 Dec 2015
 *      Author: jiaheng
 */

#ifndef SRC_SUDOKU_CPP_
#define SRC_SUDOKU_CPP_

#include <array>
#include <string>
#include "Sudoku.h"

template<size_t N>
Sudoku<N>::Sudoku(std::array<std::array<int,N>,N> const &arr) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			cells[i][j] = arr[i][j];
	}
}

template<>
inline std::string Sudoku<9>::toString()
{
	std::string string {"+-----------------------+\n"};
	for (int row = 0; row < size; row++) {
		if (row != 0 && row%3 == 0)
			string += "|-------+-------+-------|\n";
		for (int col = 0; col < size; col++) {
			if (col%3 == 0)
				string += "| ";
			string += std::to_string(cells[row][col]) + " ";
		}
		string += "|\n";
	}
	string += "+-----------------------+\n";
	return string;
}

template<>
inline std::string Sudoku<16>::toString()
{
	std::string string {"+-------------------------------------------------------+\n"};
	for (int row = 0; row < size; row++) {
		if (row != 0 && row%4 == 0)
			string += "|-------------+-------------+-------------+-------------|\n";
		for (int col = 0; col < size; col++) {
			if (col%4 == 0)
				string += "| ";
			if (cells[row][col] < 10) string += " ";
			string += std::to_string(cells[row][col]) + " ";
		}
		string += "|\n";
	}
	string += "+-------------------------------------------------------+\n";
	return string;
}

template<size_t N>
bool Sudoku<N>::isIncomplete() {
	for (const auto &row : cells) {
		for (const auto &val : row)
			if (val == 0) return true;
	}
	return false;
}

template<size_t N>
bool Sudoku<N>::isComplete() {
	return !isIncomplete();
}

template<size_t N>
bool Sudoku<N>::safeInRow(int row, int num) {
	for (const auto &val : cells[row]) {
		if (val == num) return false;
	}
	return true;
}

template<size_t N>
bool Sudoku<N>::safeInCol(int col, int num) {
	for (const auto &row : cells) {
		if (row[col] == num) return false;
	}
	return true;
}

template<>
inline bool Sudoku<9>::safeInSqr(int startRow, int startCol, int num) {
	int endRow { startRow + 3 },
		endCol { startCol + 3 };
	for (int i = startRow; i < endRow; i++)
		for (int j = startCol; j < endCol; j++)
			if (cells[i][j] == num) return false;
	return true;
}

template<>
inline bool Sudoku<16>::safeInSqr(int startRow, int startCol, int num) {
	int endRow { startRow + 4 },
		endCol { startCol + 4 };
	for (int i = startRow; i < endRow; i++)
		for (int j = startCol; j < endCol; j++)
			if (cells[i][j] == num) return false;
	return true;
}

template<>
inline bool Sudoku<9>::isSafe(int row, int col, int num) {
	return (safeInRow(row, num) &&
			safeInCol(col, num) &&
			safeInSqr(row - row%3, col - col%3, num));
}

template<>
inline bool Sudoku<16>::isSafe(int row, int col, int num) {
	return (safeInRow(row, num) &&
			safeInCol(col, num) &&
			safeInSqr(row - row%4, col - col%4, num));
}

template<size_t N>
bool Sudoku<N>::cellIsEmpty(int row, int col) {
	return cells[row][col] == 0;
}

template<>
inline bool Sudoku<9>::isCorrect() {
	for (int i = 0; i < 9; i++) {
		if (!correctInRow(i) || !correctInCol(i)) return false;
	}
	for (int i = 0; i < 9; i+=3) {
		for (int j = 0; j < 9; j+=3) {
			if (!correctInSqr(i,j)) return false;
		}
	}
	return true;
}

template<>
inline bool Sudoku<16>::isCorrect() {
	for (int i = 0; i < 16; i++) {
		if (!correctInRow(i) || !correctInCol(i)) return false;
	}
	for (int i = 0; i < 16; i+=4) {
		for (int j = 0; j < 16; j+=4) {
			if (!correctInSqr(i,j)) return false;
		}
	}
	return true;
}

template<size_t N>
bool Sudoku<N>::correctInRow(int row) {
	for (int val = 1; val <= size; val++)
		for (int i = 0; i < size; i++) {
			int check_val = cells[row][i];
			if (check_val <= 0 || check_val > size) return false;
			if (check_val == val) break;
		}
	return true;
}

template<size_t N>
bool Sudoku<N>::correctInCol(int col) {
	for (int val = 1; val <= size; val++)
		for (int i = 0; i < size; i++) {
			int check_val = cells[i][col];
			if (check_val <= 0 || check_val > size) return false;
			if (check_val == val) break;
		}
	return true;
}

template<size_t N>
bool Sudoku<N>::correctInSqr(int startRow, int startCol) {
	int endRow { startRow + 3 },
		endCol { startCol + 3 };
	for (int i = startRow; i < endRow; i++)
		for (int j = startCol; j < endCol; j++){
			//TODO: incomplete check
		}
	return true;
}

#endif /* SRC_SUDOKU_CPP_ */
