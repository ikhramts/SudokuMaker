#pragma once
#include <string>
#include <vector>
#include <windows.h>

#include "SolutionOutcome.h"

// Define the main export symbol.
#ifndef SUDOKU_MAKER_API
    #ifdef SUDOKUMAKER_EXPORTS
        #define SUDOKUMAKER_API __declspec(dllexport)
    #else
        #define SUDOKUMAKER_API __declspec(dllimport)
    #endif
#endif

namespace sudoku_maker {
    // Useful typedefs.
    #ifndef SudokuCell
        typedef unsigned char SudokuCell;
    #endif

    // Constants.
    unsigned short kSudokuNumCells = 81; 
    
    enum Difficulty {
        ELIMINATION = 1,
        HIDDEN_SINGLE = 2,         // Only possible place in a row/column.
        ELIMINATE_LINE = 4,
        HIDDEN_DOUBLES = 8,
        HIDDEN_TRIPLES = 16,
        X_WING = 32,
        BRUTE_FORCE = 64
    };

extern "C" {
    // Assign a difficulty level to a sudoku puzzle.
    SolutionOutcome FindPuzzleDifficulty(const SudokuCell* puzzle, Difficulty& difficulty);

    // Check whether a solution is valid.
    bool IsBoardValid(const SudokuCell* puzzle);

    // Check whether a solution is a valid solution to the puzzle.
    bool IsSolution(const SudokuCell* puzzle, const SudokuCell* solution);

    // Make a single sudoku puzzle.
    // Argument "puzzle" must contain at least 81 char-sized elements.
    void MakeSudoku(SudokuCell* puzzle);

    // Solve a sudoku puzzle.
    // Returns true if a solution is found, false otherwise.
    SolutionOutcome Solve(const SudokuCell* puzzle, SudokuCell* solution);

    // Solve a puzzle with a strategy up to a certain difficulty.
    // Returns true if a solution is found, false otherwise.
    SolutionOutcome SolveWithStrategy(const SudokuCell* puzzle, Difficulty maxDifficulty);

}
}


