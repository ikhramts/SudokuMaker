// SudokuMaker.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "SudokuMaker.h"
#include "Puzzle.h"

namespace sudoku_maker {

    // Assign a difficulty level to a sudoku puzzle.
    SolutionOutcome FindPuzzleDifficulty(const SudokuCell* puzzle, Difficulty& difficulty) {
        return SOLUTION_OK;
    }

    // Check whether a solution is valid.
    bool IsBoardValid(const SudokuCell* board) {
        Puzzle puzzle(board);
        return puzzle.IsValid();
    }

    // Check whether a solution is a valid solution to the puzzle.
    bool IsSolution(const SudokuCell* puzzle, const SudokuCell* solution) {
        return true;
    }

    // Make a single sudoku puzzle.
    // Argument "puzzle" must contain at least 81 char-sized elements.
    void MakeSudoku(SudokuCell* puzzle) {
    }

    // Solve a sudoku puzzle.
    // Returns true if a solution is found, false otherwise.
    SolutionOutcome Solve(const SudokuCell* puzzle, SudokuCell* solution) {
        return SOLUTION_OK;
    }

    // Solve a puzzle with a strategy up to a certain difficulty.
    // Returns true if a solution is found, false otherwise.
    SolutionOutcome SolveWithStrategy(const SudokuCell* puzzle, Difficulty maxDifficulty) {
        return SOLUTION_OK;
    }

}

