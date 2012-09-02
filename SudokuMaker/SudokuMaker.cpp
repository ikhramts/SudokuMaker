// SudokuMaker.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "SudokuMaker.h"
#include "Puzzle.h"
#include "Solvers.h"

namespace sudoku_maker {

    // Assign a difficulty level to a sudoku puzzle.
    SolutionOutcome FindPuzzleDifficulty(const SudokuCell* puzzle, SolutionStrategy& difficulty) {
        return SOLUTION_OK;
    }

    // Check whether a solution is valid.
    bool IsBoardValid(const SudokuCell* board) {
        Puzzle puzzle(board);
        bool isValid = puzzle.IsValid();
        return isValid;
    }

    // Check whether a solution is a valid solution to the puzzle.
    bool IsSolution(const SudokuCell* puzzle, const SudokuCell* solution) {
        Puzzle puzzleBoard(puzzle);
        Puzzle solutionBoard(solution);
        return solutionBoard.IsSolutionFor(puzzleBoard);
    }

    // Make a single sudoku puzzle.
    // Argument "puzzle" must contain at least 81 char-sized elements.
    void MakeSudoku(SudokuCell* puzzle) {
    }

    // Solve a sudoku puzzle.
    // Returns true if a solution is found, false otherwise.
    SolutionOutcome Solve(const SudokuCell* puzzle, SudokuCell* solution) {
        PuzzlePtr puzzleBoard(new Puzzle(puzzle));
        auto solutionBoard = SolveBruteForce(puzzleBoard);

        if (solutionBoard.get() != nullptr) {
            solutionBoard->ToByteArray(solution);
            return SOLUTION_OK;
        
        } else {
            return SOLUTION_INVALID_PUZZLE;
        }
    }

    // Solve a puzzle with a strategy up to a certain difficulty.
    // Returns true if a solution is found, false otherwise.
    SolutionOutcome SolveWithStrategy(const SudokuCell* puzzle, SolutionStrategy maxDifficulty) {
        return SOLUTION_OK;
    }

}

