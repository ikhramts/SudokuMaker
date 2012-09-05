#pragma once
#include "stdafx.h"
#include <vector>

#include "Puzzle.h"

namespace sudoku_maker {
    int CountSolutions(PuzzlePtr puzzle, int limit, int foundSoFar = 0);

    bool HasUniqueSolution(PuzzlePtr puzzle);

    // Generate numPuzzles Sudoku puzzles of indeterminate
    // difficulty.
    std::vector<PuzzlePtr> MakePuzzles(size_t numPuzzles = 1);
}