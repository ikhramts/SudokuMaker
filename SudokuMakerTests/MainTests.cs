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

    }
}
