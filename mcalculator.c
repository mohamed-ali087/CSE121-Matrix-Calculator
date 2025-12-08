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

int main(void)
{
    Matrix in1mat, in2mat, outMat;
    
    char op;
    
    printf("Enter First Matrix Dimentions (rows columns): ");
    scanf("%d %d", &in1mat.rows, &in1mat.cols);

    inMatrix(&in1mat);

    
    printf("Input Operation\n(a -> addition)\n(m -> multiplication)\n(s -> subtraction)\n(i -> inverse)\n(t -> transpose)\n: ");
    scanf(" %c", &op); 
    
    if(op == 'a' || op =='m' || op == 's') 
    {
        printf("Enter second Matrix Dimentions (Like this rows columns): ");
        scanf("%d %d", &in2mat.rows, &in2mat.cols);
       
        inMatrix(&in2mat);
    } 
    
    int success = 1;

    switch (op) {
        case 't':
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

        case 'a':
            break;
        
        case 's':
            break;

        case 'm':
            break;

        default:
            printf("Improper operation selected.\n");
            success = 0;
    }

    return 0;
}

void inMatrix(Matrix *m)
{
    printf("Enter elements for %dx%d matrix:\n", m->rows, m->cols);
    for(int i = 0; i < m->rows ; ++i)
    {
        printf("Row %d: ", i+1); 
        for(int j = 0; j < m->cols ; ++j)
        {
            scanf("%lf", &m->data[i][j]); 
        }
    }
}

void outMatrix(Matrix *m)
{
    for(int i = 0; i < m->rows ; ++i)
    {
        for(int j = 0; j < m->cols ; ++j)
        {
            printf("%.2f\t", m->data[i][j]);
        }
        printf("\n");
    }
}


int inverseGaussJordan(Matrix *src, Matrix *inv) {
    int n = src->rows;
    if (n != src->cols) return 0;
    
    Matrix temp = *src;
    inv->rows = n; 
    inv->cols = n;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            
            if (i == j) {
                inv->data[i][j] = 1.0; 
            } else {
                inv->data[i][j] = 0.0;  
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (temp.data[i][i] == 0) {
            int swapRow = i + 1;
            while (swapRow < n && temp.data[swapRow][i] == 0) swapRow++;
            if (swapRow == n) return 0; 

            for (int k = 0; k < n; k++) {
                double t = temp.data[i][k];
                temp.data[i][k] = temp.data[swapRow][k]; 
                temp.data[swapRow][k] = t;
                t = inv->data[i][k]; 
                inv->data[i][k] = inv->data[swapRow][k]; 
                inv->data[swapRow][k] = t;
            }
        }

        double pivot = temp.data[i][i]; 
        for (int j = 0; j < n; j++) {
            temp.data[i][j] = temp.data[i][j] / pivot;
            inv->data[i][j]  = inv->data[i][j]  / pivot;
        }

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
void summatrix(int c , int r,int a[r][c], int b[r][c], int result[r][c]) { //sum of two matrix
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            result[i][j] = a[i][j] + b[i][j]; 
        }
    }
}
void subrtactmatrix(int c , int r,int a[r][c], int b[r][c], int result[r][c]){ 
    for(int i =0; i<r ; i++){
        for(int j=0; j<c ; j++){
            result[i][j]= a[i][j]-b[i][j]; // subtraction of two matrix
        }
    }
}
void multiplyscalarmatrix (int c , int r , int a[r][c], int result[r][c], int scalar){
    for(int i =0; i<r ; i++){
        for(int j=0; j<c ; j++){
            result[i][j]= a[i][j]*scalar; // multiplication of matrix with scalar 
        }
    }
}
void bitwise_multiplymatrix(int c , int r , int a[r][c], int b [r][c], int result[r][c]){
    for( int i=0; i<r ; i++){
        for (int j=0; j<c; j++){
            result[i][j]=a[i][j] * b[i][j]; // multplication to each elment in matrix to corresponding elment in the other matrix  
        }
    }
}
