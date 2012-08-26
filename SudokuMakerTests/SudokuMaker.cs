using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;


namespace SudokuMakerTests {
    /// <summary>
    /// A class that wraps functionality of SudokuMaker.dll.
    /// </summary>
    public class SudokuMaker {
        public const int NumCells = 81;

        [DllImport("SudokuMaker.dll")]
        public extern static bool IsBoardValid(byte[] board);


    }
}
