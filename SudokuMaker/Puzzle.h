#pragma once
#include "stdafx.h"

#include "SolutionOutcome.h"

namespace sudoku_maker {

/***************************************\
*                Cell                   *
\***************************************/
class Cell {
public:
    //=============== Constants ===============//
    const static unsigned short kPositionOf1 = 1;
    const static unsigned short kPositionOf2 = 2;
    const static unsigned short kPositionOf3 = 4;
    const static unsigned short kPositionOf4 = 8;
    const static unsigned short kPositionOf5 = 16;
    const static unsigned short kPositionOf6 = 32;
    const static unsigned short kPositionOf7 = 64;
    const static unsigned short kPositionOf8 = 128;
    const static unsigned short kPositionOf9 = 256;

    const static unsigned short kNumbers = 511;
        
    const static unsigned short kSolvedFlag = 512;

    const static int kNumNumbers = 9;

    //=============== Constructors ===============//
    Cell();
    Cell(int number);
    Cell(const Cell& other);
        
        
    //=============== Methods ===============//
    void Erase(int number);
    void ErasePencilMark(unsigned short pencilMark);
    bool IsPenciledIn(int number) const;
    bool IsSolved() const;
    void PencilIn(int number);
    void PencilInAll();
    unsigned short PencilMarks() const;

    void SetValue(int number);

    // Force the cell to check whether it shoudl be in the solved state.
    // A cell is in the solved state iff it has exactly one number penciled
    // in.
    bool UpdateSolvedState();
    
    UCHAR Value() const;
        
    bool operator== (const Cell& other) const;
    bool operator!= (const Cell& other) const;
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
    void EliminateImpossiblePencilMarks();

    void EliminateImpossibleMarksForSolvedCell();

    void Load(const UCHAR* board);
	
	// This puzzle is a solution for other puzzle iff
	//  * this board is valid,
	//  * solved cells in other match solved cells in this puzzle,
	//  * this puzzle has no empty cells.
	bool IsSolutionFor(const Puzzle& other) const;
    
	// Check whether a board is valid.
	// A board is valid if among all solved cells there are
	// no duplicate numbers in rows, columns and 3x3 segments.
	bool IsValid() const;

    SolutionOutcome Solve();

    void ToByteArray(BYTE* byteArray) const;

    //=============== Fields ===============//
    std::array<Cell, kNumCells> Cells;

private:
    bool CheckForDuplicate(USHORT& foundNumbers, const Cell& cell) const;
};
}