#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "puzzle.h"
int main()
{
        srand(time(NULL));
        int time;
        int s[9][9]={0};
        int p[9][9],emptycells[9][9]={0};
        rules();
        fillDiag(s);
        fillRest(s,0,3);
        storeSol(s,p);
        removeDigits(p,emptycells);
        printf("\n\n");
        solveSudoku(p,s,emptycells);
        if(!checkSolution(p,s))
        {
                printf("The solution is: \n");
                displayGrid(s,emptycells);
        }
        return 0;
}