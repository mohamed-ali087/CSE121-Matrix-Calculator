// Lacking user input error handeling.
#include <stdio.h>

void inMatrix(unsigned int r, unsigned int c, int mat[r][c]); // input a matrix.
void outMatrix(unsigned int r, unsigned int c, int mat[r][c]); // output (print) a matrix.

// void inv(int imat[][], int omat[][]); // takes two matrix arguments, puts the inverse of the first into the second.
// void multiply(int i1mat[][], int i2mat[][], int omat[][]); // takes 3 matrix arguments, puts the product of the first and the second in the third.
// void devive(int i1mat[][], int i2mat[][], int omat[][]); // takes 3 matrix arguments, puts the devision of the first and the second in the third.
// void add(int i1mat[][], int i2mat[][], int omat[][]); // takes 3 matrix arguments, puts the sum of the first and the second in the third.
// void sub(int i1mat[][], int i2mat[][], int omat[][]); // substracts
// void transpose(int imat[][], int omat[][]) // takes 2 matrix arguments, puts the transpose of the first in the second.

int main(void)
{
    // Declaration
    
    // First array dimentions
    int in1Rows;
    int in1Cols;

    // Second array dimentions
    int in2Rows;
    int in2Cols;

    // operation    
    char op;
    
    
    printf("Enter First Matrix Dimentions (rows columns): ");
    scanf("%d %d", &in1Rows, &in1Cols);

    // declare first matrix
    int in1mat[in1Rows][in1Cols];
    // input first matrix   
    inMatrix(in1Rows, in1Cols, in1mat);

    
    // take the required calculation from the user
    printf("Input Operation\n(a -> addition)\n(m -> multiplication)\n(s -> subtraction)\n(i -> inverse)\n(t -> transpose)\n:");
    scanf("%s", &op);
    
    if(op == 'a' | op =='m' | op == 's')
    {
    // take the second matrix from the user

    printf("Enter second Matrix Dimentions (Like this rows columns): ");
    scanf("%d %d", &in2Rows, &in2Cols);

    int in2mat[in2Rows][in2Cols];
   
    inMatrix( in2Rows, in1Cols, in2mat);
    } 
    
    switch (op) {
        // perform calculation depending on op.
        // the output matrix dimentions rely on the operation.
        case 't':
            // int outmat[in1Rows][in1Cols];
            break;

        case 'i':
            break;

        case 'a':
            break;
        
        case 's':
            break;

        case 'm':
            break;

        // give improper usage message if op was not one of the operations.
        default:
            printf("Improper operation selected.\n");
    }

    
    return 0;
}

void inMatrix(unsigned int r, unsigned int c, int mat[r][c])
{

    for(int i = 0; i < r ; ++i)
    {
        for(int j = 0; j < c ; ++j)
        {
            printf("[%d][%d] (You can enter more than one element seperated by spaces): ", i+1, j+1);
            scanf("%d", &mat[i][j]);
        }
    }
}

void outMatrix(unsigned int r, unsigned int c, int mat[r][c])
{
    for(int i = 0; i < r ; ++i)
    {
        for(int j = 0; j < c ; ++j)
        {
            printf("%d  ", mat[i][j]);
        }
        printf("\n");
    }
}
