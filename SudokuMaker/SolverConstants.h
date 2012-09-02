#pragma once
#include "stdafx.h"

namespace sudoku_maker {
enum SolutionOutcome {
    SOLUTION_OK, SOLUTION_CANNOT_SOLVE, SOLUTION_INVALID_PUZZLE
};

enum SolutionStrategy {
    ELIMINATION = 1,
    HIDDEN_SINGLE = 2,         // Only possible place in a row/column/segment.
    ELIMINATE_LINE = 4,
    HIDDEN_DOUBLES = 8,
    HIDDEN_TRIPLES = 16,
    X_WING = 32,
    BRUTE_FORCE = 64
};

}