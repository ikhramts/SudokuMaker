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
            var board = new byte[SudokuMaker.NumCells] {
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

            var isBoardValid = SudokuMaker.IsBoardValid(board);
        }
        

    }
}
