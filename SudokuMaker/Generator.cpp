#include "stdafx.h"

#include "Generator.h"

namespace sudoku_maker {

int CountSolutions(PuzzlePtr puzzle, int limit, int foundSoFar) {
    // Proceed recursively.  This is very similar to SolveBruteForce(),
    // but combining a code into something that works for both functions
    // isn't really worth the effort.

    // Find an unsolved cell.
    int unsolvedCellIndex = 0;

    for (unsolvedCellIndex = 0; unsolvedCellIndex < Puzzle::kNumCells; unsolvedCellIndex++) {
        if (!puzzle->Cells[unsolvedCellIndex].IsSolved()) {
            break;
        }
    }

    // Base case: puzzle is solved.
    if (unsolvedCellIndex == Puzzle::kNumCells) {
        return 1;
    }

    // Recursive case: substitute a number in one
    // of the unsolved cells and invoke this function again.
    auto unsolvedCell = puzzle->Cells[unsolvedCellIndex];
    int totalSolutions = foundSoFar;

    for (int number = 1; number < Puzzle::kNumNumbers; number++) {
        // Skip numbers that aren't penciled in.
        USHORT pencilMark = (1 << (number - 1));
        
        if (!unsolvedCell.HasPencilMark(pencilMark)) {
            continue;
        }

        // Count the number of solutions if this number is 
        // substituted in the cell.
        PuzzlePtr guessedPuzzle(new Puzzle(*puzzle));
        guessedPuzzle->Cells[unsolvedCellIndex].SetValue(number);

        auto couldReduce = 
            guessedPuzzle->EliminateImpossiblePencilMarks(unsolvedCellIndex);

        if (couldReduce) {
            // The substitution does not introduce obvious
            // conflics.  Continue searching for solutions.
            int newSolutions = CountSolutions(guessedPuzzle, limit, totalSolutions);
            totalSolutions += newSolutions;

            if (totalSolutions >= limit) {
                break;
            }
        }
    }

    return totalSolutions;
}

bool HasUniqueSolution(PuzzlePtr puzzle) {
    // Scan possible puzzle pencil mark comninations until
    // two solutions are found or until there are no more combinations
    // left.
    PuzzlePtr reducedPuzzle(new Puzzle(*puzzle));

    if (!reducedPuzzle->EliminateImpossiblePencilMarks()) {
        // Not a valid puzzle.
        return false;
    }

    int numSolutions = CountSolutions(reducedPuzzle, 2 /* limit */, 0 /* none to start */);
    return (numSolutions == 1);
}

}