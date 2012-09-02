#include "stdafx.h"

#include "Solvers.h"

namespace sudoku_maker {
PuzzlePtr SolveBruteForce(PuzzlePtr puzzle) {
    // Solve recursively.
    PuzzlePtr reducedPuzzle(new Puzzle(*puzzle));
    PuzzlePtr nullPuzzle(nullptr);
    
    auto couldReduce = reducedPuzzle->EliminateImpossiblePencilMarks();

    // Base case: hit a dead end or solved the puzzle.
    if (!couldReduce) {
        return nullPuzzle;

    } else if (reducedPuzzle->IsSolved()) {
        return reducedPuzzle;
    }

    // Recursive case: try each possible value for the first 
    // unsolved cell.
    int firstUnsolvedCell = 0;

    while (firstUnsolvedCell < Puzzle::kNumCells) {
        if (!reducedPuzzle->Cells[firstUnsolvedCell].IsSolved()) {
            break;
        }

        firstUnsolvedCell++;
    }

    if (firstUnsolvedCell == 81) {
        int x =2;
    }

    // Try every remaining penciled in value of this unsolved cell.
    Cell& unsolvedCell = reducedPuzzle->Cells[firstUnsolvedCell];
    unsigned short& rawCell = unsolvedCell.Raw;
    unsigned short pencilMark = 1;

    for (int number = 1; number <= Puzzle::kNumNumbers; number++) {
        // Skip impossible values.
        if ((rawCell & pencilMark) == 0) {
            pencilMark = pencilMark << 1;
            continue;
        }

        // Replace the cell value with this number and see whether this
        // leads to a solution.
        unsigned short oldRawCell = rawCell;
        unsolvedCell.SetValue(number);

        if (!reducedPuzzle->IsValid()) {
            int x = 2;
        }

        auto solvedResult = SolveBruteForce(reducedPuzzle);

        if (solvedResult.get() != nullptr) {
            // Found a solution!
            return solvedResult;

        } else {
            // Restore the old value and keep going.
            rawCell = oldRawCell;
        }

        pencilMark = pencilMark << 1;
    }

    // Could not find a solution.
    return nullPuzzle;
}
}