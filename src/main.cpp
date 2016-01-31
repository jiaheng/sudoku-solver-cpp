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

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "Sudoku.hpp"
#include "SudokuSolver.hpp"

int main(int argc, char* argv[]) {
	std::cout << "argc = " << argc << std::endl;
	for(int i = 0; i < argc; i++)
		std::cout << "argv[" << i << "] = " << argv[i] << std::endl;

	std::ifstream infile("sample");
	if (!infile.good()) {
		std::cout << "File does not exists! Exiting program" << std::endl;
		return 0;
	}

	// reading 9x9 sudoku
	std::string line { };
	std::vector<Sudoku<9>> puzzles { };
	while (std::getline(infile, line)) {
		// read file line by line
		std::istringstream iss(line);
		puzzles.push_back(Sudoku<9>(line));
	}
	int index {0};
	unsigned int time {0};
	for (auto &sudoku: puzzles) {
		std::cout << "Solving 9x9 puzzle #" << ++index << "..." << std::endl;
		std::cout << sudoku.toString() << std::endl << std::endl;
		SudokuSolver<9> solver(sudoku);
		clock_t start = clock();
		Sudoku<9> solution = solver.getSolution();
		std::cout << "Solution: " << std::endl << solution.toString() << std::endl;
		clock_t end = clock();
		time += static_cast<unsigned int>(end - start);
		std::string msg {"Solution for puzzle #"};
		msg += index;
		msg += " is not correct.";
	}
	std::cout << "it took " << time << "ticks, or "
				<< ((float)time)/CLOCKS_PER_SEC
				<< "seconds to solve all " << index << " 9x9 sudoku." << std::endl;
	return 0;
}