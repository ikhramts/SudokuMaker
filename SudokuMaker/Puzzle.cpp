#include "stdafx.h"
#include "Puzzle.h"
#include <bitset>

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
    this->Raw &= ~(1 << number);
    UpdateSolvedState();

}

bool Cell::IsPenciledIn(int number) const {
    return (this->Raw & (1 << number)) != 0;
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
           return i;
       }

       position = position << 1;
    }

    return 0;
}

/***************************************\
*                Puzzle                 *
\***************************************/
Puzzle::Puzzle() {
}

Puzzle::Puzzle(const UCHAR* board) {
    this->Load(board);
}

void Puzzle::Load(const UCHAR* board) {
    for (int i = 0; i < kNumCells; i++) {
        Cells[i].SetValue(board[i]);
    }
}

bool Puzzle::IsValid() const {
    USHORT foundNumbers;
    
    // Check whether any rows have duplicates.
    for (int row = 0; row < kNumNumbers; row++) {
        foundNumbers = 0;
        auto rowOffset = row * kNumNumbers;

        for (int column = 0; column < kNumNumbers; column++) {
            if(CheckForDuplicate(foundNumbers, Cells[rowOffset + column])) {
                OutputDebugString(L"Found Duplicate in rows");
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
                OutputDebugString(L"Found Duplicate in columns");
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
                        OutputDebugString(L"Found Duplicate in segments");
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

// Returns: true if found a duplicate; false otherwise.
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

}