//
// !!!!!!!!!!!!! IMPORTANT !!!!!!!!!!!!!
//
// When testing a 32-bit SudokuMaker.dll on a 64-bit computer,
// make sure to use x86 version of NUnit instead of default one.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

using NUnit.Framework;

namespace SudokuMakerTests {
    [TestFixture]
    public class MainTests {
        [Test]
        public void LoadDll() {
            var isBoardValid = SudokuMaker.IsBoardValid(Boards.EmptyBoard);
        }

        [Test]
        [TestCase("EmptyBoard", true)]
        [TestCase("Puzzle1", true)]
        [TestCase("Solution1", true)]
        [TestCase("NotSolution1_WrongPuzzle", true)]
        [TestCase("Puzzle2", true)]
        [TestCase("Solution2", true)]
        [TestCase("Incorrect_DuplicateColumn1", false)]
        [TestCase("Incorrect_DuplicateColumn2", false)]
        [TestCase("Incorrect_DuplicateRow1", false)]
        [TestCase("Incorrect_DuplicateRow2", false)]
        [TestCase("Incorrect_DuplicateSegment1", false)]
        [TestCase("Incorrect_DuplicateSegment2", false)]
        public void IsBoardValid(string boardName, bool expected) {
            var board = Boards.LoadBoard(boardName);
            var isBoardValid = SudokuMaker.IsBoardValid(board);
            Assert.AreEqual(expected, isBoardValid);
        }

        [Test]
        [TestCase("Puzzle1", "Solution1", true)]
        [TestCase("Puzzle2", "Solution2", true)]
        [TestCase("Puzzle1", "Solution2", false)]
        [TestCase("Puzzle2", "Solution1", false)]
        [TestCase("Puzzle1", "NotSolution1_Incomplete", false)]
        [TestCase("Puzzle1", "NotSolution1_HasDuplicate1", false)]
        public void IsSolution(string puzzleName, string solutionName, bool expected) {
            var puzzle = Boards.LoadBoard(puzzleName);
            var solution = Boards.LoadBoard(solutionName);
            var isSolution = SudokuMaker.IsSolution(puzzle, solution);
            Assert.AreEqual(expected, isSolution);
        }

        [Test]
        [TestCase("Puzzle1", "Solution1", SolutionOutcome.SOLUTION_OK)]
        [TestCase("Puzzle1_AlmostSolved", "Solution1", SolutionOutcome.SOLUTION_OK)]
        [TestCase("Solution1", "Solution1", SolutionOutcome.SOLUTION_OK)]
        [TestCase("Puzzle2", "Solution2", SolutionOutcome.SOLUTION_OK)]
        [TestCase("Solution2", "Solution2", SolutionOutcome.SOLUTION_OK)]
        [TestCase("EmptyBoard", "none", SolutionOutcome.SOLUTION_OK)]
        [TestCase("Incorrect_DuplicateRow1", "EmptyBoard", SolutionOutcome.SOLUTION_INVALID_PUZZLE)]
        [TestCase("Incorrect_DuplicateColumn2", "EmptyBoard", SolutionOutcome.SOLUTION_INVALID_PUZZLE)]
        public void Solve(string puzzleName, string solutionName, SolutionOutcome expectedOutcome) {
            var puzzle = Boards.LoadBoard(puzzleName);
            var expectedSolution = Boards.LoadBoard(solutionName);
            var solution = new byte[SudokuMaker.NumCells];
            var outcome = SudokuMaker.Solve(puzzle, solution);

            Assert.AreEqual(expectedOutcome, outcome);

            if (expectedOutcome == SolutionOutcome.SOLUTION_OK) {
                if (expectedSolution != null) {
                    Assert.AreEqual(expectedSolution, solution);

                } else {
                    Assert.IsTrue(SudokuMaker.IsSolution(puzzle, solution));
                }
            }
        }
    }
}
