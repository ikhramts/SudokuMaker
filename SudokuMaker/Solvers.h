#pragma once

#include "stdafx.h"
#include <memory>
#include <random>

#include "Puzzle.h"
#include "SolverConstants.h"

namespace sudoku_maker {
    typedef std::shared_ptr<std::default_random_engine> RandomEnginePtr;

    PuzzlePtr SolveBruteForce(PuzzlePtr puzzle);

    // Solve with some randomiztion in the solution to ensure
    // that puzzles with non-unique solutions don't always produce
    // the same result.
    PuzzlePtr SolveBruteForce(PuzzlePtr puzzle, RandomEnginePtr randomEngine);
}