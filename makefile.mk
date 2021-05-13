a.out:sudoku.o puzzle.o
        gcc sudoku.o puzzle.o
puzzle.o:puzzle.c puzzle.h
        gcc -c puzzle.c
sudoku.o:sudoku.c puzzle.h
        gcc -c sudoku.c