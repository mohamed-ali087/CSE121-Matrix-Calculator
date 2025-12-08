#include <stdio.h>
#include <math.h>

#define MAX_SIZE 10

typedef struct {
    int rows;
    int cols;
    double data[MAX_SIZE][MAX_SIZE]; 
} Matrix;

void inMatrix(Matrix *m); 
void outMatrix(Matrix *m); 
int inverseGaussJordan(Matrix *src, Matrix *inv);
void summatrix(Matrix *a, Matrix *b, Matrix *result);
void subrtactmatrix(Matrix *a, Matrix *b, Matrix *result);
void multiplyscalarmatrix(Matrix *a, double scalar, Matrix *result);
void bitwise_multiplymatrix(Matrix *a, Matrix *b, Matrix *result);
void transpose(Matrix *mat, Matrix *trans);

int main(void)
{
    Matrix in1mat, in2mat, outMat;
    char op;
    double scalar; 
    
    printf("Enter First Matrix Dimentions (rows columns): ");
    scanf("%d %d", &in1mat.rows, &in1mat.cols);
    inMatrix(&in1mat);

    while(1) {
        printf("\n-------------------------\n");
        printf("Current Matrix:\n");
        outMatrix(&in1mat);
        printf("-------------------------\n");
        printf("Input Operation:\n");
        printf("(a -> addition)\n");
        printf("(s -> subtraction)\n");
        printf("(m -> bitwise multiplication [element by element])\n"); 
        printf("(x -> scalar multiplication [multiply by number])\n");
        printf("(i -> inverse)\n(t -> transpose)\n(q -> quit)\n: ");

        scanf(" %c", &op); 
        
        if (op == 'q') break; 

        if(op == 'a' || op =='m' || op == 's') 
        {
            printf("Enter second Matrix Dimentions (rows columns): ");
            scanf("%d %d", &in2mat.rows, &in2mat.cols);
            inMatrix(&in2mat);
        }
        else if (op == 'x') {
            printf("Enter the scalar number: ");
            scanf("%lf", &scalar);
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

            case 'm': 
                if(in1mat.rows == in2mat.rows && in1mat.cols == in2mat.cols) {
                    bitwise_multiplymatrix(&in1mat, &in2mat, &outMat);
                    printf("\n--- Bitwise Multiplication Result ---\n");
                    outMatrix(&outMat);
                } else { printf("Error: Dimension Mismatch!\n"); success = 0; }
                break;

            case 'x': 
                multiplyscalarmatrix(&in1mat, scalar, &outMat);
                printf("\n--- Scalar Multiplication Result ---\n");
                outMatrix(&outMat);
                break;

            case 't': 
                transpose(&in1mat, &outMat);
                printf("\n--- Transposed Matrix ---\n");
                outMatrix(&outMat);
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

            default:
                printf("Improper operation selected.\n");
                success = 0;
        }

        if (success) {
            in1mat = outMat;
            printf(">>> Result Saved! You can use it in the next operation. <<<\n");
        }
    }

    return 0;
}

void summatrix(Matrix *a, Matrix *b, Matrix *result) { 
    result->rows = a->rows; 
    result->cols = a->cols;
    for(int i = 0; i < a->rows; i++) {
        for(int j = 0; j < a->cols; j++) {
            result->data[i][j] = a->data[i][j] + b->data[i][j]; 
        }
    }
}

void subrtactmatrix(Matrix *a, Matrix *b, Matrix *result){ 
    result->rows = a->rows; 
    result->cols = a->cols;
    for(int i =0; i < a->rows ; i++){
        for(int j=0; j < a->cols ; j++){
            result->data[i][j]= a->data[i][j] - b->data[i][j]; 
        }
    }
}

void multiplyscalarmatrix (Matrix *a, double scalar, Matrix *result){
    result->rows = a->rows; 
    result->cols = a->cols;
    for(int i =0; i < a->rows ; i++){
        for(int j=0; j < a->cols ; j++){
            result->data[i][j]= a->data[i][j] * scalar; 
        }
    }
}

void bitwise_multiplymatrix(Matrix *a, Matrix *b, Matrix *result){
    result->rows = a->rows; 
    result->cols = a->cols;
    for( int i=0; i < a->rows ; i++){
        for (int j=0; j < a->cols; j++){
            result->data[i][j] = a->data[i][j] * b->data[i][j]; 
        }
    }
}

void transpose(Matrix *mat, Matrix *trans){
    trans->rows = mat->cols; 
    trans->cols = mat->rows;
    for(int i=0; i < mat->rows; ++i){
        for(int j=0; j < mat->cols; ++j){
            trans->data[j][i] = mat->data[i][j];
        }
    }
}

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

void outMatrix(Matrix *m)
{
    for(int i = 0; i < m->rows ; ++i){
        for(int j = 0; j < m->cols ; ++j){
            printf("%.2f\t", m->data[i][j]);
        }
        printf("\n");
    }
}

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
