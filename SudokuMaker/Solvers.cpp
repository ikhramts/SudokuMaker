#include "stdafx.h"

#include "Solvers.h"

namespace sudoku_maker {
PuzzlePtr SolveBruteForce(PuzzlePtr puzzle) {
    // Eliminate irrelevant pencil marks.
    PuzzlePtr reducedPuzzle(new Puzzle(*puzzle));
    
    if (!reducedPuzzle->EliminateImpossiblePencilMarks()) {
        PuzzlePtr nullPuzzle;
        return nullPuzzle;
    }

    // Solve the puzzle.
    RandomEnginePtr randomEngine(new std::default_random_engine());
    auto solution =  SolveBruteForce(reducedPuzzle, randomEngine);

    return solution;
}

// Solve with some randomiztion in the solution to ensure
// that puzzles without unique solutions don't always produce
// the same result.
PuzzlePtr SolveBruteForce(PuzzlePtr puzzle, RandomEnginePtr randomEngine) {
    PuzzlePtr nullPuzzle(nullptr);
    
    // Solve recursively.
    
    // Find an unsolved cell.
    std::uniform_int_distribution<int> randomCell(0, Puzzle::kNumCells - 1);
    auto cellOffset = randomCell(*randomEngine);
    int firstUnsolvedCell = 0;
    int rawPosition = 0;

    while (rawPosition < Puzzle::kNumCells) {
        firstUnsolvedCell = (rawPosition + cellOffset) % Puzzle::kNumCells;

        if (!puzzle->Cells[firstUnsolvedCell].IsSolved()) {
            break;
        }

        rawPosition++;
    }

    // Base case: there are no unsolved cells left.
    // The puzzle is solved.
    if (rawPosition >= Puzzle::kNumCells) {
        return puzzle;
    }

    // Try every remaining penciled in value of this unsolved cell.
    // Start with a random pencil mark and proceed up, loopig around to
    // the lower-valued pencil marks.
    std::uniform_int_distribution<int> uniformDistribution(1, Puzzle::kNumNumbers);
    auto startingNumber = uniformDistribution(*randomEngine);

    Cell& unsolvedCell = puzzle->Cells[firstUnsolvedCell];

    for (int i = 0; i < Puzzle::kNumNumbers; i++) {
        //int number = (i + startingNumber) % Puzzle::kNumNumbers;
        int number = i + 1;
        USHORT pencilMark = ((short)1) << (number - 1);

        // Skip numbers that are not penciled in.
        if (!unsolvedCell.HasPencilMark(pencilMark)) {
            continue;
        }

        // Replace the cell value with this number and see whether this
        // leads to a condfict or a solution.
        PuzzlePtr guessedPuzzle(new Puzzle(*puzzle));
        guessedPuzzle->Cells[firstUnsolvedCell].SetValue(number);
        auto couldReduce = 
            guessedPuzzle->EliminateImpossiblePencilMarks(firstUnsolvedCell);

        if (couldReduce) {
            // No conflicts.  Try to solve the new puzzle.
            auto solvedResult = SolveBruteForce(guessedPuzzle, randomEngine);

            if (solvedResult.get() != nullptr) {
                // Found a solution!
                return solvedResult;
            }
        }
    }

    // Base case 2: Could not find a solution.
    return nullPuzzle;
}
}