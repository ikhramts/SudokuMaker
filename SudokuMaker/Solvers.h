#pragma once

#include "stdafx.h"
#include <memory>

#include "Puzzle.h"
#include "SolverConstants.h"

namespace sudoku_maker {
    PuzzlePtr SolveBruteForce(PuzzlePtr puzzle);
    
}