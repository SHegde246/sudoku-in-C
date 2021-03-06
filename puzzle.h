void rules();
int safeSqr(int s[9][9],int rstart,int cstart,int n);
int safeRow(int s[9][9],int row,int n);
int safeCol(int s[9][9],int col,int n);
void fillSqr(int s[9][9],int row,int col);
void fillDiag(int s[9][9]);
int fillRest(int s[9][9],int row,int col);
void storeSol(int s[9][9],int p[9][9]);
void removeDigits(int p[9][9],int emptycells[9][9]);
void displayGrid(int grid[9][9],int emptycells[9][9]);
void solveSudoku(int p[9][9],int s[9][9],int emptycells[9][9]);
int checkSolution(int p[9][9],int s[9][9]);