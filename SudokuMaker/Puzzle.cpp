#include "stdafx.h"
#include <bitset>
#include <deque>
#include <vector>

#include "Puzzle.h"

namespace sudoku_maker {
/***************************************\
*                Cell                   *
\***************************************/
Cell::Cell() {
    this->Raw = 0;
}

Cell::Cell(int number) {
    this->SetValue(number);
}

Cell::Cell(const Cell& other) {
    this->Raw = other.Raw;
}

void Cell::Erase(int number) {
    this->Raw &= ~(1 << (number - 1));
    UpdateSolvedState();

}

void Cell::ErasePencilMark(unsigned short pencilMark) {
    unsigned short mask = (~pencilMark) | (~kNumbers);
    this->Raw &= mask;
    UpdateSolvedState();
}

bool Cell::HasPencilMark(unsigned short pencilMark) const {
    return (Raw & pencilMark) != 0;
}

bool Cell::IsPenciledIn(int number) const {
    return (this->Raw & (1 << (number - 1))) != 0;
}

bool Cell::IsSolved() const {
    return (this->Raw & kSolvedFlag) != 0;
}

void Cell::PencilIn(int number) {
    this->Raw |= ~(1 << number);
    UpdateSolvedState();
}

void Cell::PencilInAll() {
    this->Raw = kNumbers;
    this->Raw &= ~kSolvedFlag;
}

unsigned short Cell::PencilMarks() const {
    return this->Raw & kNumbers;
}

Cell& Cell::operator= (const Cell& other) {
    Raw = other.Raw;
    return *this;
}

bool Cell::operator== (const Cell& other) const {
    return other.Raw == this->Raw;
}

bool Cell::operator!= (const Cell& other) const {
    return other.Raw != this->Raw;
}

bool Cell::UpdateSolvedState() {
    bool foundPencilMark = false;
    USHORT position = 1;

    for (int i = 1; i <= kNumNumbers; i++) {
        if ((Raw & position) > 0) {
            if (foundPencilMark) {
                // More than one pencil mark.  Not solved.
                Raw &= ~kSolvedFlag;
                return false;

            } else {
                foundPencilMark = true;
            }
        }

        position = position << 1;
    }

    if (foundPencilMark) {
        // This cell has exactly one pencil mark and therefore
        // has been solved.
        Raw |= kSolvedFlag;
        return true;

    } else {
        // This cell has no pencil marks and is not solved.
        Raw &= ~kSolvedFlag;
        return false;
    }
}

void Cell::SetValue(int number) {
    if (number > 0) {
        this->Raw = (1 << (number - 1));
        this->Raw |= kSolvedFlag;

    } else {
        this->PencilInAll();
    }
}

// Return the first number penciled into this cell.
// Return 0 if there are no numbers penciled in.
UCHAR Cell::Value() const {
    int position = 1;

    for (int i = 0; i < kNumNumbers; i++) {
       if ((this->Raw & position) != 0) {
           return i + 1;
       }

       position = position << 1;
    }

    return 0;
}

/***************************************\
*                Puzzle                 *
\***************************************/
//****************** Public Functions *******************//
Puzzle::Puzzle() {
}

Puzzle::Puzzle(const UCHAR* board) {
    this->Load(board);
}

Puzzle::Puzzle(const Puzzle& other) {
    for (int i = 0; i < kNumCells; i++) {
        Cells[i] = other.Cells[i];
    }
}

Puzzle::Puzzle(Puzzle&& other) {
    for (int i = 0; i < kNumCells; i++) {
        Cells[i] = other.Cells[i];
    }
}

bool Puzzle::EliminateImpossiblePencilMarks() {
    // Examine the effect of all solved cells on unsolved cells.
    std::vector<int> solvedCells;
    solvedCells.reserve(kNumCells);

    for (int i = 0; i < kNumCells; i++) {
        if (Cells[i].IsSolved()) {
            solvedCells.push_back(i);
        }
    }

    return EliminateImpossiblePencilMarks(solvedCells);
}

bool Puzzle::EliminateImpossiblePencilMarks(const std::vector<int>& modifiedCells) {
    // For each solved cell, eliminate the cell's value
    // in each row, column and 3x3 segment.
    std::deque<int> solvedCells;
    
    // Start with the cells that have been provided.
    // Cells that will be solved while eliminating pencil marks
    // will be added later.
    for (auto cellPosition : modifiedCells) {
        solvedCells.push_back(cellPosition);
    }

    while (!solvedCells.empty()) {
        int cellPosition = solvedCells.front();
        solvedCells.pop_front();

        auto solvedCell = Cells[cellPosition];
        auto value = solvedCell.PencilMarks();

        // Eliminate the value in all other cells in the row.
        auto rowStart = (cellPosition / kNumNumbers) * kNumNumbers;
        auto rowEnd = rowStart + kNumNumbers;

        for (int position = rowStart; position < rowEnd; position++) {
            auto couldEliminate = 
                EliminateConflictsAtCell(position, cellPosition, value, solvedCells);

            if (!couldEliminate) {
                return false;
            }
        }
        
        // Eliminate the value in all other cells in the column.
        auto columnStart = cellPosition % kNumNumbers;

        for (int position = columnStart; position < kNumCells; position += kNumNumbers) {
            auto couldEliminate = 
                EliminateConflictsAtCell(position, cellPosition, value, solvedCells);

            if (!couldEliminate) {
                return false;
            }
        }

        // Eliminate the value in all other cells in the 3x3 segment.
        auto topRow = cellPosition / (kNumNumbers * kSegmentWidth) * kSegmentWidth;
        auto leftColumn = ((cellPosition % kNumNumbers) / kSegmentWidth)
                            * kSegmentWidth;

        for (int row = 0; row < kSegmentWidth; row++) {
            auto offset = (row + topRow) * kNumNumbers + leftColumn;

            for (int column = 0; column < kSegmentWidth; column++) {
                auto position = offset + column;
                auto couldEliminate = 
                    EliminateConflictsAtCell(position, cellPosition, value, solvedCells);

                if (!couldEliminate) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool Puzzle::EliminateImpossiblePencilMarks(int solvedCellPosition) {
    std::vector<int> solvedCells;
    solvedCells.push_back(solvedCellPosition);
    return EliminateImpossiblePencilMarks(solvedCells);
}

void Puzzle::Load(const UCHAR* board) {
    for (int i = 0; i < kNumCells; i++) {
        Cells[i].SetValue(board[i]);
    }
}

bool Puzzle::IsSolutionFor(const Puzzle& other) const {
    if (!this->IsSolved()) {
        return false;
    }

    // Check whether solved cells in the other puzzle match
    // cells in this puzzle.
    for (int i = 0; i < kNumCells; i++) {
        auto& otherCell = other.Cells[i];
        auto& cell = Cells[i];

        if (otherCell.IsSolved() && (otherCell != cell)) {
            return false;
        }
    }

    return true;
}

bool Puzzle::IsSolved() const {
    if (!this->IsValid()) {
        return false;
    }

    // Check whether this puzzle has unsolved cells.
    for (auto& cell : Cells) {
        if (!cell.IsSolved()) {
            return false;
        }
    }

    return true;
}

bool Puzzle::IsValid() const {
    USHORT foundNumbers;
    
    // Check whether any rows have duplicates.
    for (int row = 0; row < kNumNumbers; row++) {
        foundNumbers = 0;
        auto rowOffset = row * kNumNumbers;

        for (int column = 0; column < kNumNumbers; column++) {
            if(CheckForDuplicate(foundNumbers, Cells[rowOffset + column])) {
                return false;
            }
        }
    }

    // Check for duplicates in any columns.
    for (int column = 0; column < kNumNumbers; column++) {
        foundNumbers = 0;

        for (int row = 0; row < kNumNumbers; row++) {
            int position = row * kNumNumbers + column;
            if(CheckForDuplicate(foundNumbers, Cells[position])) {
                return false;
            }
        }
    }

    // Check for duplicates in any 3x3 segments.
    // Outer two loops: iterate over segments.
    for (int outerRow = 0; outerRow < kSegmentWidth; outerRow++) {
        for (int outerColumn = 0; outerColumn < kSegmentWidth; outerColumn++) {
            foundNumbers = 0;

            // Inner loops: loop through cells of each segment.
            for (int innerRow = 0; innerRow < kSegmentWidth; innerRow++) {
                int rowOffset = (outerRow * kSegmentWidth + innerRow) * kNumNumbers;

                for (int innerColumn = 0; innerColumn < kSegmentWidth; innerColumn++) {
                    int position = rowOffset + outerColumn * kSegmentWidth + innerColumn;

                    if (CheckForDuplicate(foundNumbers, Cells[position])) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

Puzzle& Puzzle::operator= (const Puzzle& other) {
    for (int i = 0; i < kNumCells; i++) {
        Cells[i] = other.Cells[i];
    }

    return *this;
}

// Returns: true if found a duplicate; false otherwise.
void Puzzle::ToByteArray(BYTE* byteArray) const {
    for (int i = 0; i < kNumCells; i++) {
        byteArray[i] = Cells[i].Value();
    }
}

//****************** Private Functions *******************//
bool Puzzle::CheckForDuplicate(USHORT& foundNumbers, const Cell& cell) const {
    if (cell.IsSolved()) {
        if ((foundNumbers & Cell::kNumbers & cell.Raw) != 0) {
            // Found a duplicate.
            return true;
                
        } else {
            // Record that we found this number.
            foundNumbers |= Cell::kNumbers & cell.Raw;
        }
    }

    return false;
}

bool Puzzle::EliminateConflictsAtCell(int position, 
                                      int sourcePosition, 
                                      unsigned short value, 
                                      std::deque<int>& solvedQueue) {
    
    if (position != sourcePosition) {
        Cell& targetCell = Cells[position];

        if (!targetCell.IsSolved()) {
            // Remove the pencil mark.
            targetCell.ErasePencilMark(value);

            if (targetCell.IsSolved()) {
                solvedQueue.push_back(position);
            }
                
        } else {
            // Check for a conflict.
            if (targetCell.HasPencilMark(value)) {
                // Found a conflict.
                return false;
            }
        }
    }

    return true;
}


}