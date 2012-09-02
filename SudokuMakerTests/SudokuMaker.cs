using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace SudokuMakerTests {
    public enum SolutionOutcome {
        SOLUTION_OK, SOLUTION_CANNOT_SOLVE, SOLUTION_INVALID_PUZZLE
    };

    /// <summary>
    /// A class that wraps functionality of SudokuMaker.dll.
    /// </summary>
    public class SudokuMaker {
        public const int NumCells = 81;

        [DllImport("SudokuMaker.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool IsBoardValid(byte[] board);

        [DllImport("SudokuMaker.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool IsSolution(byte[] puzzle, byte[] solution);

        [DllImport("SudokuMaker.dll")]
        public extern static SolutionOutcome Solve(byte[] puzzle, [In, Out] byte[] solution);

    }
}
