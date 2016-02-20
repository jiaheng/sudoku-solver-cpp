/*
 * Copyright (c) 2015 Jia Heng Eik
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * Sudoku.cpp
 *
 *  Created on: 6 Dec 2015
 *      Author: jiaheng
 */

#include "Sudoku.hpp"

#include <math.h>
#include <array>
#include <string>

Sudoku::Sudoku(int **const arr, int p_size) {
	size = p_size;
	sqr_size = static_cast<int>(sqrt(size));
	initCells();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			cells[i][j] = arr[i][j];
	}
}

Sudoku::Sudoku(std::string input) {
	rtrim(input, ' ');
	size = static_cast<int>(sqrt(input.length()));
	sqr_size = static_cast<int>(sqrt(size));
	initCells();
	switch(size) {
	case 4:
	case 9:
		fillSudokuCell(input);
		break;
	case 16:
		fillHexadokuCell(input);
		break;
	default:
		// Something wrong
		break;
	}
}

Sudoku::Sudoku(const Sudoku &other) {
	size = other.size;
	sqr_size = other.sqr_size;
	initCells();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			cells[i][j] = other.cells[i][j];
	}
}

Sudoku::~Sudoku() {
	for (int i = 0; i < size; ++i) {
		delete[] cells[i];
	}
	delete[] cells;
}

Sudoku& Sudoku::operator=(const Sudoku &rhs) {
	if (this != &rhs) {
		for (int i = 0; i < size; ++i) {
			delete[] cells[i];
		}
		delete[] cells;
		size = rhs.size;
		sqr_size = rhs.sqr_size;
		initCells();
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++)
				cells[i][j] = rhs.cells[i][j];
		}
	}
	return *this;
}

bool Sudoku::operator==(Sudoku &rhs) {
	if (size != rhs.size) return false;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (cells[i][j] != rhs.cells[i][j]) return false;
	return true;
}

void Sudoku::initCells() {
	cells = new int*[size] { };
	for (int i = 0; i < size; i++)
		cells[i] = new int[size] { };
}

void Sudoku::rtrim(std::string &s, char c) {
	if (s.empty())
		return;

	std::string::iterator p { };
	for (p = s.end(); p != s.begin() && *--p == c;);

	if (*p != c)
		p++;

	s.erase(p, s.end());
}

void Sudoku::fillSudokuCell(std::string &input) {
	int i { 0 }, j{ 0 };
	for(char& c : input) {
	    if (c == '.') cells[i][j] = 0;
	    else if (c > '1' && c <= '9') cells[i][j] = c - '0';
	    // next cell
	    j++;
	    if (j >= size) {
	    	i++;
	    	j = 0;
	    	if (i >= size) break;
	    }
	}
}

void Sudoku::fillHexadokuCell(std::string &input) {
	int i { 0 }, j{ 0 };
	for(char& c : input) {
	    if (c == '.') cells[i][j] = 0;
	    else if (c > '1' && c <= '9') cells[i][j] = c - '0';
	    else if (c >= 'A' && c <= 'F') cells[i][j] = c - 'A' + 10;
	    else if (c >= 'a' && c <= 'f') cells[i][j] = c - 'a' + 10;
	    // next cell
	    j++;
	    if (j >= size) {
	    	i++;
	    	j = 0;
	    	if (i >= size) break;
	    }
	}
}

std::string Sudoku::sudokuToString() {
	std::string string {"+-----------------------+\n"};
	for (int row = 0; row < size; row++) {
		if (row != 0 && row%3 == 0)
			string += "|-------+-------+-------|\n";
		for (int col = 0; col < size; col++) {
			if (col%3 == 0)
				string += "| ";
			int num { cells[row][col] };
			if (num != 0) string += std::to_string(num) + " ";
			else string += "X ";
		}
		string += "|\n";
	}
	string += "+-----------------------+\n";
	return string;
}

std::string Sudoku::hexadokuToString() {
	std::string string {"+-------------------------------------------------------+\n"};
	for (int row = 0; row < size; row++) {
		if (row != 0 && row%4 == 0)
			string += "|-------------+-------------+-------------+-------------|\n";
		for (int col = 0; col < size; col++) {
			if (col%4 == 0)
				string += "| ";
			int num { cells[row][col] };
			if (num < 10) string += " ";
			if (num != 0) string += std::to_string(num) + " ";
			else string += "X ";
		}
		string += "|\n";
	}
	string += "+-------------------------------------------------------+\n";
	return string;
}

std::string Sudoku::otherToString() {
	std::string str { };
	for (int row = 0; row < size; ++row) {
		for (int col = 0; col < size; ++col) {
			int num { cells[row][col] };
			if (num != 0) str += std::to_string(num) + " ";
			else str += "X ";
		}
		str += "\n";
	}
	return str;
}

std::string Sudoku::toString() {
	switch(size) {
	case 9:
		return sudokuToString();
	case 16:
		return hexadokuToString();
	default:
		return otherToString();
	}
}

std::string Sudoku::toSimpleString() {
	std::string string { "" };
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			if (cells[row][col] == 0) string += ".";
			else string += std::to_string(cells[row][col]);
		}
	}
	return string;
}

bool Sudoku::isIncomplete() {
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			if (cells[i][j] == 0) return true;
	return false;
}

bool Sudoku::isComplete() {
	return !isIncomplete();
}

bool Sudoku::safeInRow(int row, int num) {
	for (int i = 0; i < size; ++i)
		if (cells[row][i] == num) return false;
	return true;
}

bool Sudoku::safeInCol(int col, int num) {
	for (int i = 0; i < size; ++i)
		if (cells[i][col] == num) return false;
	return true;
}

bool Sudoku::safeInSqr(int startRow, int startCol, int num) {
	int endRow { startRow + sqr_size },
		endCol { startCol + sqr_size };
	for (int i = startRow; i < endRow; i++)
		for (int j = startCol; j < endCol; j++)
			if (cells[i][j] == num) return false;
	return true;
}

bool Sudoku::isSafe(int row, int col, int num) {
	if (!cellIsEmpty(row, col)) return false;
	return (safeInRow(row, num) &&
			safeInCol(col, num) &&
			safeInSqr(row - row%sqr_size, col - col%sqr_size, num));
}

bool Sudoku::cellIsEmpty(int row, int col) {
	return cells[row][col] == 0;
}

bool Sudoku::correctInSqr(int startRow, int startCol) {
	int endRow { startRow + sqr_size },
		endCol { startCol + sqr_size };
	for (int val = 1; val <= size; val++) {
		bool num_exist { false };
		for (int i = startRow; i < endRow; i++)
			for (int j = startCol; j < endCol; j++){
				int check_val { cells[i][j] };
				if (check_val <= 0 || check_val > size) return false;
				if (check_val == val) num_exist = true;
				if (num_exist) break;
			}
		if (num_exist) break;
	}
	return true;
}

bool Sudoku::isCorrect() {
	for (int i = 0; i < size; i++) {
		if (!correctInRow(i) || !correctInCol(i)) return false;
	}
	for (int i = 0; i < size; i+=sqr_size) {
		for (int j = 0; j < size; j+=sqr_size) {
			if (!correctInSqr(i,j)) return false;
		}
	}
	return true;
}

bool Sudoku::correctInRow(int row) {
	for (int val = 1; val <= size; val++)
		for (int i = 0; i < size; i++) {
			int check_val { cells[row][i] };
			if (check_val <= 0 || check_val > size) return false;
			if (check_val == val) break;
		}
	return true;
}

bool Sudoku::correctInCol(int col) {
	for (int val = 1; val <= size; val++)
		for (int i = 0; i < size; i++) {
			int check_val { cells[i][col] };
			if (check_val <= 0 || check_val > size) return false;
			if (check_val == val) break;
		}
	return true;
}
