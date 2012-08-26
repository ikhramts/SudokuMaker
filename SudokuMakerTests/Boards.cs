using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SudokuMakerTests {
    public class Boards {
        public static readonly byte[] EmptyBoard = new byte[SudokuMaker.NumCells] {
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,

            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
        };

        public static readonly byte[] Incorrect_DuplicateRow1 = new byte[SudokuMaker.NumCells] {
            1, 0, 0,   0, 1, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,

            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
        };

        public static readonly byte[] Incorrect_DuplicateRow2 = new byte[SudokuMaker.NumCells] {
            0, 0, 0,   0, 1, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,

            0, 3, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            
            0, 0, 5,   5, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
        };

        public static readonly byte[] Incorrect_DuplicateColumn1 = new byte[SudokuMaker.NumCells] {
            0, 0, 0,   0, 3, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,

            0, 3, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            
            0, 0, 5,   0, 3, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
        };

        public static readonly byte[] Incorrect_DuplicateColumn2 = new byte[SudokuMaker.NumCells] {
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,

            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 9,   0, 0, 0,   0, 0, 0,
            
            0, 0, 9,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
        };

        public static readonly byte[] Incorrect_DuplicateSegment1 = new byte[SudokuMaker.NumCells] {
            0, 0, 0,   0, 3, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,

            0, 3, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            
            0, 0, 5,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            5, 0, 0,   0, 0, 0,   0, 0, 0,
        };

        public static readonly byte[] Incorrect_DuplicateSegment2 = new byte[SudokuMaker.NumCells] {
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,

            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   6, 6, 0,
            
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
            0, 0, 0,   0, 0, 0,   0, 0, 0,
        };

        public static readonly byte[] Puzzle1 = new byte[SudokuMaker.NumCells] {
            3, 0, 0,   0, 0, 4,   9, 5, 1,
            0, 6, 9,   0, 0, 0,   0, 0, 0,
            0, 4, 0,   9, 0, 0,   0, 0, 0,

            6, 0, 5,   0, 2, 0,   0, 1, 0,
            8, 0, 0,   7, 0, 5,   0, 0, 9,
            0, 1, 0,   0, 4, 0,   8, 0, 5,
            
            0, 0, 0,   0, 0, 3,   0, 8, 0,
            0, 0, 0,   0, 0, 0,   1, 9, 0,
            7, 8, 2,   4, 0, 0,   0, 0, 6,
        };

        public static readonly byte[] Solution1 = new byte[SudokuMaker.NumCells] {
            3, 7, 8,   2, 6, 4,   9, 5, 1,
            5, 6, 9,   1, 3, 7,   2, 4, 8,
            2, 4, 1,   9, 5, 8,   6, 7, 3,

            6, 3, 5,   8, 2, 9,   7, 1, 4,
            8, 2, 4,   7, 1, 5,   3, 6, 9,
            9, 1, 7,   3, 4, 6,   8, 2, 5,
            
            1, 9, 6,   5, 7, 3,   4, 8, 2,
            4, 5, 3,   6, 8, 2,   1, 9, 7,
            7, 8, 2,   4, 9, 1,   5, 3, 6,
        };

        public static readonly byte[] NotSolution1_Incomplete = new byte[SudokuMaker.NumCells] {
            3, 7, 8,   2, 6, 4,   9, 5, 1,
            5, 6, 9,   1, 3, 7,   2, 4, 8,
            2, 4, 1,   9, 0, 8,   6, 7, 3,

            6, 3, 5,   8, 2, 9,   7, 1, 4,
            8, 2, 4,   7, 1, 5,   3, 6, 9,
            9, 1, 7,   3, 4, 6,   8, 2, 5,
            
            1, 9, 6,   5, 7, 3,   4, 8, 2,
            4, 5, 3,   6, 8, 2,   1, 9, 7,
            7, 8, 2,   4, 9, 1,   5, 3, 6,
        };

        public static readonly byte[] NotSolution1_HasDuplicate1 = new byte[SudokuMaker.NumCells] {
            3, 7, 8,   2, 6, 4,   9, 5, 1,
            5, 6, 9,   1, 3, 7,   2, 4, 8,
            2, 4, 1,   9, 5, 8,   6, 7, 3,

            6, 3, 5,   8, 2, 9,   9, 1, 4,
            8, 2, 4,   7, 1, 5,   3, 6, 7,
            9, 1, 7,   3, 4, 6,   8, 2, 5,
            
            1, 9, 6,   5, 7, 3,   4, 8, 2,
            4, 5, 3,   6, 8, 2,   1, 9, 7,
            7, 8, 2,   4, 9, 1,   5, 3, 6,
        };

        public static readonly byte[] NotSolution1_HasDuplicate2 = new byte[SudokuMaker.NumCells] {
            3, 7, 8,   2, 6, 4,   9, 5, 1,
            5, 6, 9,   1, 3, 7,   2, 4, 8,
            2, 4, 1,   9, 5, 8,   6, 7, 3,

            6, 3, 5,   8, 2, 7,   9, 1, 4,
            8, 2, 4,   7, 1, 5,   3, 6, 7,
            9, 1, 7,   3, 4, 6,   8, 2, 5,
            
            1, 9, 6,   5, 7, 3,   4, 8, 2,
            4, 5, 3,   6, 8, 2,   1, 9, 3,
            7, 8, 2,   4, 9, 1,   5, 3, 6,
        };

        public static readonly byte[] NotSolution1_WrongPuzzle = new byte[SudokuMaker.NumCells] {
            5, 6, 3,   1, 2, 8,   4, 7, 9,
            2, 4, 9,   7, 3, 5,   8, 6, 1,
            1, 7, 8,   9, 4, 6,   2, 3, 5,

            8, 9, 1,   3, 6, 4,   5, 2, 7,
            6, 2, 4,   5, 1, 7,   3, 9, 8,
            3, 5, 7,   8, 9, 2,   1, 4, 6,
            
            9, 3, 5,   4, 7, 1,   6, 8, 2,
            7, 8, 6,   2, 5, 3,   9, 1, 4,
            4, 1, 2,   6, 8, 9,   7, 5, 3,
        };

        public static readonly byte[] Puzzle2 = new byte[SudokuMaker.NumCells] {
            0, 0, 0,   0, 2, 8,   0, 0, 0,
            0, 4, 9,   7, 0, 0,   0, 0, 0,
            1, 7, 0,   0, 0, 0,   0, 0, 5,

            0, 9, 0,   0, 0, 4,   5, 2, 0,
            6, 0, 0,   0, 1, 0,   0, 0, 8,
            0, 5, 7,   8, 0, 0,   0, 4, 0,
            
            9, 0, 0,   0, 0, 0,   0, 8, 2,
            0, 0, 0,   0, 0, 3,   9, 1, 0,
            0, 0, 0,   6, 8, 0,   0, 0, 0,
        };

        public static readonly byte[] Solution2 = new byte[SudokuMaker.NumCells] {
            5, 6, 3,   1, 2, 8,   4, 7, 9,
            2, 4, 9,   7, 3, 5,   8, 6, 1,
            1, 7, 8,   9, 4, 6,   2, 3, 5,

            8, 9, 1,   3, 6, 4,   5, 2, 7,
            6, 2, 4,   5, 1, 7,   3, 9, 8,
            3, 5, 7,   8, 9, 2,   1, 4, 6,
            
            9, 3, 5,   4, 7, 1,   6, 8, 2,
            7, 8, 6,   2, 5, 3,   9, 1, 4,
            4, 1, 2,   6, 8, 9,   7, 5, 3,
        };

        public static byte[] LoadBoard(string boardName) {
            var boardField = typeof(Boards).GetField(boardName);
            var board = (byte[]) boardField.GetValue(null);
            return board;
        }
    }
}
