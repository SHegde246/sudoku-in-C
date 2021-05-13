#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "puzzle.h"
#define cyan "\x1b[36m"
#define green "\x1b[32m"
#define white "\x1b[0m"
void rules()
{
        printf("\nHello there! Welcome to Sudoku!\n");
        printf("The rules are as follows:\n");
        printf("There will be a 9x9 grid, with 81 cells, grouped into 9 3x3 squares.\n");
        printf("To solve a sudoku puzzle, each number from 1-9 must be present\nin each square, row and column, with no repetit
ions.\n");
        printf("A certain number of cells will be filled by the computer. Based on\nthe positions of the given numbers, the pla
yer will deduce the positions of the remaining numbers.\n");
        printf("Conventionally, a game of sudoku is timed. The timer will start\nas soon as the player chooses to begin the gam
e, and will be displayed before each turn.\n");
        printf("The player may ask for hints at any point in the game. They will enter\na position, and the system will fill it
, if it is a valid one.\n");
        printf("For the first 5 hints, a penalty of 30 seconds will be added to the game time.\n");
        printf("For the next 5 hints, a penalty of 45 seconds will be added to the game time.\n");
        printf("For every 5 hints taken, the penalty increases by 15 seconds.\n");
        printf("That's everything! Enjoy your game!\n");
}
int safeSqr(int s[9][9],int rstart,int cstart,int n)
{
        for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
                        if(s[rstart+i][cstart+j]==n)
                                return 0;
        return 1;
}
int safeRow(int s[9][9],int row,int n)
{
        for(int col=0;col<9;col++)
                if(s[row][col]==n)
                        return 0;
        return 1;
}
int safeCol(int s[9][9],int col,int n)
{
        for(int row=0;row<9;row++)
                if(s[row][col]==n)
                        return 0;
        return 1;
}
void fillSqr(int s[9][9],int row,int col)
{
        int n;
        for(int i=0;i<3;i++)
        {
                for(int j=0;j<3;j++)
                {
                        do
                        {
                                n=(rand()%9)+1;
                        }while(!safeSqr(s,row,col,n));
                        s[row+i][col+j]=n;
                }
        }
}
void fillDiag(int s[9][9])
{
        for(int i=0;i<9;i+=3)
        {
                fillSqr(s,i,i);
        }
}
int fillRest(int s[9][9],int row,int col)
{
        if(col>=9 && row<8)
        {
                row++;
                col=0;
        }
        if(row>=9 && col>=9)
        {
                return 1;
        }
        if(row<3)
        {
                if(col<3)
                        col=3;
        }
        else if(row<6)
        {
                if(col==((int)(row/3))*3)
                        col+=3;
        }
        else
        {
                if(col==6)
                {
                        row++;
                        col=0;
                        if(row>=9)
                                return 1;
                }
        }
        for(int n=1;n<=9;n++)
        {
                if(safeSqr(s,row-row%3,col-col%3,n) && safeRow(s,row,n) && safeCol(s,col,n))
                {
                        s[row][col]=n;
                        if(fillRest(s,row,col+1))
                                return 1;

                        s[row][col]=0;
                }
        }
        return 0;
}
void storeSol(int s[9][9],int p[9][9])
{
        for(int i=0;i<9;i++)
        {
                for(int j=0;j<9;j++)
                {
                        p[i][j]=s[i][j];
                }
        }
}
void removeDigits(int p[9][9],int emptycells[9][9])
{
        int n,row,col,count=0;
        printf("\nNo. of elements to be removed: ");
        scanf("%d",&n);
        while(count<n)
        {
                row=rand()%9;
                col=rand()%9;
                if(p[row][col])
                {
                        emptycells[row][col]=1;
                        p[row][col]=0;
                        count++;
                }
        }
}
void displayGrid(int grid[9][9],int emptycells[9][9])
{
        int count=0;
        printf("\n");
        printf(cyan "    ");
        for(int i=1;i<=9;i++)
        {
                printf("%d  ",i);
                if(i%3==0)
                        printf("  ");
        }
        printf(white "\n\n");
        for(int row=0;row<9;row++)
        {
                printf(cyan "%d   ",row+1);
                printf(white);
                for(int col=0;col<9;col++)
                {
                        if(emptycells[row][col])
                                printf(green);
                        else
                                printf(white);

                        if(grid[row][col]==0)
                                printf("_  ");
                        else
                                printf("%d  ",grid[row][col]);

                        count++;
                        if(count%3==0)
                                printf("  ");
                }
                printf("\n");
                if(count%27==0)
                        printf("\n");
        }
        printf(white);
}
void solveSudoku(int p[9][9],int s[9][9],int emptycells[9][9])
{
        int start,current_time=0,min,sec,hint=0,penalty=15,add_time=0;
        int choice,row,col,n;
        char begin;
        printf("Enter any key to start game: ");
        scanf(" %c",&begin);
        displayGrid(p,emptycells);
        start=time(NULL);
        do
        {
                current_time=time(NULL)-start+add_time;
                min=current_time/60;
                sec=current_time%60;
                printf("\nTime: %02d:%02d\n",min,sec);
                printf("Hints taken: %d\n",hint);
                printf("\n1. Insert      2.Remove      3. Hint      4.End Game\n");
                printf("Enter your choice: ");
                scanf("%d",&choice);
                switch(choice)
                {
                        case 1:
                                printf("\nEnter row and column:\n");
                                printf("Row: "); scanf("%d",&row);
                                printf("Col: "); scanf("%d",&col);
                                if(!emptycells[row-1][col-1])
                                {
                                        printf("Invalid position. Please re-enter.\n");
//                                      current_time=time(NULL)-start+add_time;
                                        continue;
                                }
                                else if(row>9||row<1||col>9||col<1)
                                {
                                        printf("Invalid row/column. Please re-enter.\n");
        //                              current_time=time(NULL)-start+add_time;
                                        continue;
                                }
                                printf("\nEnter number to be placed: "); scanf("%d",&n);
                                if(n>9 || n<1)
                                {
                                        printf("Invalid number. Please re-enter.\n");
        //                              current_time=time(NULL)-start+add_time;
                                        continue;
                                }
                                p[row-1][col-1]=n;
                                break;
                        case 2:
                                printf("\nEnter row and column:\n");
                                printf("Row: "); scanf("%d",&row);
                                printf("Col: "); scanf("%d",&col);
                                if(emptycells[row-1][col-1])
                                {
                                        p[row-1][col-1]=0;
                                }
                                else
                                {
        //                              printf("Invalid position. Please re-enter.\n");
                                        current_time=time(NULL)-start+add_time;
                                        continue;
                                }
                                break;
                        case 3:
                                printf("\nEnter row and column:\n");
                                printf("Row: "); scanf("%d",&row);
                                printf("Col: "); scanf("%d",&col);
                                if(!emptycells[row-1][col-1])
                                {
                                        printf("That cell is already filled! Please re-enter.\n");
        //                              current_time=time(NULL)-start+add_time;
                                        continue;
                                }
                                hint++;
                                if((hint-1)%5==0)
                                {
                                        penalty+=15;
                                }
                                add_time+=penalty;
                                p[row-1][col-1]=s[row-1][col-1];
                                break;
                        case 4:
                                printf("End game?\n1.Yes\t2.No\n");
                                scanf("%d",&choice);
                                if(choice==1)
                                        choice=4;
                                else
                                {
        //                              current_time=time(NULL)-start+add_time;
                                        continue;
                                }
                                current_time=time(NULL)-start+add_time;
                                break;
                        default:
                                printf("Invalid choice. Please re-enter.\n");
                                current_time=time(NULL)-start+(hint*30);
                                continue;
                }
                printf("\n");
                displayGrid(p,emptycells);
                current_time=time(NULL)-start+add_time;
        }while(choice!=4);
        current_time=time(NULL)-start+add_time;
        min=current_time/60;
        sec=current_time%60;
        printf("\nTime: %02d:%02d\n",min,sec);
}
int checkSolution(int p[9][9],int s[9][9])
{
        for(int i=0;i<9;i++)
        {
                for(int j=0;j<9;j++)
                {
                        if(s[i][j]!=p[i][j])
                        {
                                printf("\nSorry! Your solution is incorrect.\n");
                                return 0;
                        }
                }
        }
        printf("\nWell played! Your solution is correct!\n");
        return 1;
}