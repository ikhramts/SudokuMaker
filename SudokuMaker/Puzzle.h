#pragma once
#include "stdafx.h"

namespace sudoku_maker {
/***************************************\
*                Cell                   *
\***************************************/
class Cell {
public:
    //=============== Constants ===============//
    const static int kPositionOf1 = 1;
    const static int kPositionOf2 = 2;
    const static int kPositionOf3 = 4;
    const static int kPositionOf4 = 8;
    const static int kPositionOf5 = 16;
    const static int kPositionOf6 = 32;
    const static int kPositionOf7 = 64;
    const static int kPositionOf8 = 128;
    const static int kPositionOf9 = 256;

    const static int kNumbers = 1023;
        
    const static int kSolvedFlag = 1024;

    const static int kNumNumbers = 9;

    //=============== Constructors ===============//
    Cell();
    Cell(int number);
    Cell(const Cell& other);
        
        
    //=============== Methods ===============//
    void Erase(int number);
    bool IsPenciledIn(int number) const;
    bool IsSolved() const;
    void PencilIn(int number);
    void PencilInAll();

    void SetValue(int number);

    // Force the cell to check whether it shoudl be in the solved state.
    // A cell is in the solved state iff it has exactly one number penciled
    // in.
    bool UpdateSolvedState();
    
    UCHAR Value() const;
        
    bool operator== (const Cell& other);
    Cell& operator= (const Cell& other);

    //=============== Fields ===============//
    unsigned short Raw;


};

/***************************************\
*                Puzzle                 *
\***************************************/
class Puzzle {
public:
    //=============== Constants ===============//
    const static int kNumCells = 81;
    const static int kSegmentWidth = 3;
    const static int kNumNumbers = Cell::kNumNumbers;

    //=============== Constructors ===============//
    Puzzle();
    Puzzle(const UCHAR* board);

    //=============== Methods ===============//
    void Load(const UCHAR* board);
    bool IsValid() const;

    //=============== Fields ===============//
    std::array<Cell, kNumCells> Cells;

private:
    bool CheckForDuplicate(USHORT& foundNumbers, const Cell& cell) const;
};
}