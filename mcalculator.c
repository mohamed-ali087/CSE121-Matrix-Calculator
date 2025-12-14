#include <stdio.h>
#include <math.h>

#define MAX_SIZE 10

// Matrix Structure --- By Mohamed Khairy.
typedef struct {
    int rows;
    int cols;
    double data[MAX_SIZE][MAX_SIZE]; 
} Matrix;

// Functions Prototypes
void inMatrix(Matrix *m); 
void outMatrix(Matrix *m); 
int inverseGaussJordan(Matrix *src, Matrix *inv);
void summatrix(Matrix *a, Matrix *b, Matrix *result);
void subrtactmatrix(Matrix *a, Matrix *b, Matrix *result);
void multiplyscalarmatrix(Matrix *a, double scalar, Matrix *result);
void bitwise_multiplymatrix(Matrix *a, Matrix *b, Matrix *result);
void multiplyMatrix(Matrix *a, Matrix *b, Matrix *result); 
int solveLinearSystem(Matrix *A, Matrix *B, Matrix *X);
void transpose(Matrix *mat, Matrix *trans);
float det(Matrix mat);

/* All Team Participated in the main Function (user prompt) so it's messy :D */
int main(void)
{
    Matrix in1mat = {0}, in2mat = {0}, outMat = {0};
    char op;
    double scalar; 
    char sub_op; 
    // الشماريخ  
    
    printf("\033[32m"); 
    printf(" /$$       /$$            /$$                /$$                  /$$$$$$             /$$                      /$$            /$$                     \n");
    printf("| $$$     /$$$           | $$               |__/                 /$$__  $$            | $$                     |$$           | $$                     \n");
    printf("| $$$$   /$$$$  /$$$$$$ /$$$$$$    /$$$$$$  /$$ /$$   /$$       | $$  \\__/   /$$$$$$ | $$  /$$$$$$$ /$$   /$$| $$  /$$$$$$  /$$$$$$    /$$$$$$    /$$$$$$ \n");
    printf("| $$ $$/$$ $$ |____  $$|_  $$_/   /$$__  $$| $$|  $$ /$$/       | $$        |____  $$| $$ /$$_____/| $$  | $$| $$ |____  $$|_  $$_/   /$$__  $$ /$$__  $$\n");
    printf("| $$  $$$| $$  /$$$$$$$  | $$     | $$  \\__/| $$ \\  $$$$/       | $$         /$$$$$$$| $$|$$       | $$  | $$| $$  /$$$$$$$  | $$     | $$  \\ $$| $$  \\__/\n");
    printf("| $$\\  $ | $$ /$$__  $$  | $$ /$$| $$      | $$  >$$  $$        | $$    $$ /$$__  $$| $$| $$       | $$  | $$| $$ /$$__  $$  | $$ /$$| $$  | $$| $$      \n");
    printf("| $$ \\/  | $$|  $$$$$$$  |  $$$$/| $$      | $$ /$$/\\  $$       |  $$$$$$/|  $$$$$$$| $$|  $$$$$$$|  $$$$$$/| $$|  $$$$$$$   |  $$$$/|  $$$$$$/| $$      \n");
    printf("|__/     |__/ \\_______/   \\___/  |__/      |__/|__/  \\__/        \\______/  \\_______/|__/ \\_______/ \\______/ |__/ \\_______/   \\___/    \\______/ |__/      \n");
    printf("\n");
    printf("Made by:\n");
    printf("Mohamed Khairy.  Mohamed Ali.  Mohamed Walid.  Kamal Mashhour.\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("\n");
    printf("\033[0m"); 
    

    printf("Enter First Matrix Dimentions (rows columns): ");
    scanf("%d %d", &in1mat.rows, &in1mat.cols);
    inMatrix(&in1mat);

    // User prompt
    while(1) {
        printf("\n-------------------------\n");
        printf("Current Matrix:\n");
        outMatrix(&in1mat);
        printf("-------------------------\n");
        printf("Input Operation:\n");
        printf("(a -> addition)\n");
        printf("(s -> subtraction)\n");
        printf("(b -> bitwise multiplication [element by element])\n"); 
        printf("(m -> matrix multiplication \n"); 
        printf("(x -> scalar multiplication [multiply by number])\n");
        printf("(d -> matrix determinant\n"); 
        printf("(e -> solve linear equations system\n"); 
        printf("(i -> inverse)\n(t -> transpose)\n(q -> quit)\n: ");

        scanf(" %c", &op); 
        
        if (op == 'q') break; 


        if(op == 'a' || op == 's') 
        {
            printf("Enter second Matrix Dimentions (rows columns): ");
            scanf("%d %d", &in2mat.rows, &in2mat.cols);
            inMatrix(&in2mat);
        }
        
        int success = 1;

        switch (op) {
            case 'a': 
                if(in1mat.rows == in2mat.rows && in1mat.cols == in2mat.cols) {
                    summatrix(&in1mat, &in2mat, &outMat);
                    printf("\n--- Addition Result ---\n");
                    outMatrix(&outMat);
                } else { printf("Error: Dimension Mismatch!\n"); success = 0; }
                break;
            
            case 's': 
                if(in1mat.rows == in2mat.rows && in1mat.cols == in2mat.cols) {
                    subrtactmatrix(&in1mat, &in2mat, &outMat);
                    printf("\n--- Subtraction Result ---\n");
                    outMatrix(&outMat);
                } else { printf("Error: Dimension Mismatch!\n"); success = 0; }
                break;


            case 't': 
                transpose(&in1mat, &outMat);
                printf("\n--- Transposed Matrix ---\n");
                outMatrix(&outMat);
                break;
            case 'd':
                printf("Matrix Determenant = %0.4f", det(in1mat));
                break; 

            case 'i': 
                if (inverseGaussJordan(&in1mat, &outMat)) {
                    printf("\n--- Inverse Matrix ---\n");
                    outMatrix(&outMat);
                } else {
                    printf("\nError: Singular Matrix or Non-Square Matrix.\n");
                    success = 0;
                }
                break;
            
           case 'm':
                printf("\nSelect Multiplication Type:\n");
                printf("1. Standard Multiplication (Row x Col)\n");
                printf("2. Bitwise Multiplication (Element by Element)\n");
                printf("3. Scalar Multiplication (Matrix x Number)\n: ");
                scanf(" %c", &sub_op);

                if (sub_op == '1') {
                    printf("Enter second Matrix Dimentions (rows columns): ");
                    scanf("%d %d", &in2mat.rows, &in2mat.cols);
                    if(in1mat.cols == in2mat.rows) {
                        inMatrix(&in2mat);
                        multiplyMatrix(&in1mat, &in2mat, &outMat);
                        printf("\n--- Standard Multiplication Result ---\n");
                        outMatrix(&outMat);
                    } else { 
                        printf("Error: Matrix multiplication not possible (Columns of A must equal Rows of B)\n"); 
                        success = 0; 
                    }
                } else if (sub_op == '2') {
                    printf("Enter second Matrix Dimentions (rows columns): ");
                    scanf("%d %d", &in2mat.rows, &in2mat.cols);
                    if(in1mat.rows == in2mat.rows && in1mat.cols == in2mat.cols) {
                        inMatrix(&in2mat);
                        bitwise_multiplymatrix(&in1mat, &in2mat, &outMat);
                        printf("\n--- Bitwise Multiplication Result ---\n");
                        outMatrix(&outMat);
                    } else { 
                        printf("Error: Dimension Mismatch for Bitwise Multiplication!\n"); 
                        success = 0; 
                    }
                } else if (sub_op == '3') {
                    printf("Enter the scalar number: ");
                    scanf("%lf", &scalar);
                    multiplyscalarmatrix(&in1mat, scalar, &outMat);
                    printf("\n--- Scalar Multiplication Result ---\n");
                    outMatrix(&outMat);
                } else {
                    printf("Invalid Multiplication Option!\n");
                    success = 0;
                }
                break;
            
             case 'e': 
                if (in1mat.rows != in1mat.cols) {
                    printf("Error: Coefficient Matrix (A) must be Square (NxN) to solve system.\n");
                    success = 0;
                } else {
                    printf("Enter Constants Vector (B) Dimensions (Must be %d rows, 1 col):\n", in1mat.rows);
                    printf("The Vector Automatically set to %dx1 for you\n", in1mat.rows);
                    in2mat.rows = in1mat.rows;
                    in2mat.cols = 1;
                    inMatrix(&in2mat);

                    if (solveLinearSystem(&in1mat, &in2mat, &outMat)) {
                        printf("\n--- Solution Vector (X) ---\n");
                        outMatrix(&outMat);
                    } else {
                        printf("\nError: Singular Matrix (No unique solution).\n");
                        success = 0;
                    }
                }
                break;

            default:
                printf("Improper operation selected.\n");
                success = 0;
        }

        if (success && op!='d') {
            in1mat = outMat;
            printf(">>> Result Saved! You can use it in the next operation. <<<\n");
        }
    }

    return 0;
}

/*
   By Mohamed Walid.
    Adding Each element to the corresponding element.
*/
void summatrix(Matrix *a, Matrix *b, Matrix *result) { 
    result->rows = a->rows; 
    result->cols = a->cols;
    for(int i = 0; i < a->rows; i++) {
        for(int j = 0; j < a->cols; j++) {
            result->data[i][j] = a->data[i][j] + b->data[i][j]; 
        }
    }
}

/*
   By Mohamed Walid.
    Same as sum but substracting
*/
void subrtactmatrix(Matrix *a, Matrix *b, Matrix *result){ 
    result->rows = a->rows; 
    result->cols = a->cols;
    for(int i =0; i < a->rows ; i++){
        for(int j=0; j < a->cols ; j++){
            result->data[i][j]= a->data[i][j] - b->data[i][j]; 
        }
    }
}

/*
   By Mohamed Walid.
    Multiply a matrix by a number.
*/
void multiplyscalarmatrix (Matrix *a, double scalar, Matrix *result){
    result->rows = a->rows; 
    result->cols = a->cols;
    for(int i =0; i < a->rows ; i++){
        for(int j=0; j < a->cols ; j++){
            result->data[i][j]= a->data[i][j] * scalar; 
        }
    }
}

/*
   By Mohamed Walid.
    ElementWise Multiplication.
*/
void bitwise_multiplymatrix(Matrix *a, Matrix *b, Matrix *result){
    result->rows = a->rows; 
    result->cols = a->cols;
    for( int i=0; i < a->rows ; i++){
        for (int j=0; j < a->cols; j++){
            result->data[i][j] = a->data[i][j] * b->data[i][j]; 
        }
    }
}

/*
   By Kamal Mashhour.
    Transpose Function:
    simply transpose[i][j] = matrix[j][i] using nested For loops.

 */
void transpose(Matrix *mat, Matrix *trans){
    trans->rows = mat->cols; 
    trans->cols = mat->rows;
    for(int i=0; i < mat->rows; ++i){
        for(int j=0; j < mat->cols; ++j){
            trans->data[j][i] = mat->data[i][j];
        }
    }
}

/*
   By Mohamed Ali.
    Entering Matrix Function
        Nested For loop for scanning all matrix elements.
*/
void inMatrix(Matrix *m)
{
    printf("Enter elements for %dx%d matrix:\n", m->rows, m->cols);
    for(int i = 0; i < m->rows ; ++i){
        printf("Row %d: ", i+1); 
        for(int j = 0; j < m->cols ; ++j){
            scanf("%lf", &m->data[i][j]); 
        }
    }
}

/*
    By Mohamed Ali.
      Printing Matrix Function.
        Nested For loop for printing all matrix elements.
*/
void outMatrix(Matrix *m)
{
    for(int i = 0; i < m->rows ; ++i){
        for(int j = 0; j < m->cols ; ++j){
            printf("%.2f\t", m->data[i][j]);
        }
        printf("\n");
    }
}

/*
   By Mohamed Khairy.
    Calculating Matrix Inverse Using Gauss Jordan Method:

*/
int inverseGaussJordan(Matrix *src, Matrix *inv) {
    int n = src->rows;
    if (n != src->cols) return 0;
    Matrix temp = *src;
    inv->rows = n; inv->cols = n;

    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) inv->data[i][j] = (i == j) ? 1.0 : 0.0;

    for (int i = 0; i < n; i++) {
        if (temp.data[i][i] == 0) {
            int swapRow = i + 1;
            while (swapRow < n && temp.data[swapRow][i] == 0) swapRow++;
            if (swapRow == n) return 0; 
            for (int k = 0; k < n; k++) {
                double t = temp.data[i][k]; temp.data[i][k] = temp.data[swapRow][k]; temp.data[swapRow][k] = t;
                t = inv->data[i][k]; inv->data[i][k] = inv->data[swapRow][k]; inv->data[swapRow][k] = t;
            }
        }
        double pivot = temp.data[i][i]; 
        for (int j = 0; j < n; j++) { temp.data[i][j] /= pivot; inv->data[i][j] /= pivot; }
        for (int k = 0; k < n; k++) {
            if (k != i) { 
                double factor = temp.data[k][i]; 
                for (int j = 0; j < n; j++) {
                    temp.data[k][j] -= factor * temp.data[i][j];
                    inv->data[k][j] -= factor * inv->data[i][j];
                }
            }
        }
    }
    return 1;
}

/*
   By Mohamed Ali.
    A Function For Swapping Rows Required by the determinant function.
        Basic variable swapping for each element.
    ( This Function is maybe Unnecessary but there is no time to overthink :D )
*/
void swap_rows(Matrix *src, int row1, int row2)
{
    double temp;
    for(int c = 0; c < src->cols; ++c)
    {
        temp = src->data[row1][c];
        src->data[row1][c] = src->data[row2][c];
        src->data[row2][c] = temp;
    }

    /* Note
        In this function i used passing by reference because i want to modify the given matrix.
    */
}

/*
   By Mohamed Ali.
    Calculating Determinant Using Gauss Elemination Method.
        in this method we need to transform the matrix into the upper triangle form.
*/

float det(Matrix mat)
{
                      
    int dim, s;  // dim is dimension, s is a counter for row swapping
    float det = 1; // declaring & initializing determinant variable

    if(mat.rows != mat.cols) // handle if the matrix was non square.
    {
        printf("Only Square Matrix Allowed.");
        return 1;
    }
    dim = mat.rows; // Just a shortcut :D.

    for(int c = 0; c < dim; ++c)  // main for loop (c represents current row mainly but used depending on context :D (Absolute Confusion :D ...) ), this is responsable for transforming the matrix into the upper triangle form.
    {
        // This Statement is for avoiding deviving by 0, by swapping rows until there is no 0 in the principle diameter.
        if(mat.data[c][c] == 0)  
        {
            s = c + 1;
            while(s < dim && mat.data[s][c] == 0) // طول ما s أقل من عدد الصفوف (معديش آخر صف ) والصف اللي هبدل بيه مش هيديني صفر في القطر الرئيسي هفضل انزل
                s++;

            if(s == dim) // (Avoid infinite loop) if swapped all rows with each other there will be a 0 in the principle diameter which will lead the determinant to equal 0.
                return 0;

            swap_rows(&mat, c, s); // swap rows.
        }

        // making the upper triangle form. 
        for(int i = c + 1; i < dim; ++i) // The iteration started from row c + 1, working on the row under the row c.
        {
            double factor = mat.data[i][c] / mat.data[c][c]; // المعامل اللي هنضرب فيه عشان نطرح الصف من الصف اللي تحته ويدي 0
                                                               
            // (j represents columns.)
            for(int j = c; j < dim; ++j) // doing the substraction, starting from col c.
            {
                mat.data[i][j] -= factor * mat.data[c][j];
            }
        }
    }

    for(int i = 0; i < dim; ++i)
        det *= mat.data[i][i];

    return det * pow(-1, s); // multipling by -1^s as each row swap multiplies the determinant by -1.

    /* Note
        In this function i passed the matrix by value instead of passing by reference like other functions because we don't want to modify the matrix itself. 
    */
}

/*
   By Mohamed Walid.
    Regular Matrix Multiplication.
    صف في عامود يعني
*/
void multiplyMatrix(Matrix *a, Matrix *b, Matrix *result) {
    result->rows = a->rows;
    result->cols = b->cols;

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            result->data[i][j] = 0; 
            for (int k = 0; k < a->cols; k++) {
                result->data[i][j] += a->data[i][k] * b->data[k][j];
            }
        }
    }
}


/*
   By Mohamed Khairy.
    Solving Linear Systems Function.
        Using X = B * inv(A) Formula. 

*/
int solveLinearSystem(Matrix *A, Matrix *B, Matrix *X) {
    Matrix invA;
    if (A->rows != A->cols || B->rows != A->rows || B->cols != 1) return 0;

    if (inverseGaussJordan(A, &invA) == 0) return 0;
    
    multiplyMatrix(&invA, B, X);
    return 1; 
}

// Mohamed Ali is the only one responsible for the bad comments :D.
