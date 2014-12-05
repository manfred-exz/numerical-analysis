#include <stdio.h>
#define Max_size 10000
void Price( int n, double p[] );
int get_col(int n, int row, int col);
void print_matrix(int n, double *first, double *price);
double L(int n, double matrix[][3], double *last_row, int row, int col);
double U(int n, double matrix[][3], double *last_col, int row, int col);

int main()
{
    int n, i;
    double p[Max_size];

    while (scanf("%d", &n)!=EOF) {
        for (i=0; i<n; i++)
            scanf("%lf", &p[i]);
        Price(n, p);
        for (i=0; i<n; i++)
            printf("%.2f ", p[i]);
        printf("\n");
    }

    return 0;
}

#define MATRIX(matrix, row, col) (matrix[row][get_col(n, row, col)])

void Price( int n, double p[] ){
    int i, j;
    int last_index = n-1;
    double a[n][3]; // matrix for LU
    double temp;

    // init the array
    for(i = 0; i < n; i++){
        a[i][0] = 0.5;
        a[i][1] = 2.0;
        a[i][2] = 0.5;
    }

    printf("Init:\n");
    print_matrix(n, &a[0][0], p);

    // no need to set first row of U
    // set first col of L
    MATRIX(a, 1, 0) = MATRIX(a, 1, 0) / MATRIX(a, 0, 0);
    MATRIX(a, last_index, 0) = MATRIX(a, last_index, 0) / MATRIX(a, 0, 0);

    printf("After first row and col:\n");
    print_matrix(n, &a[0][0], p);

    // process the rest data
    double last_row[n], last_col[n];
    last_row[0] = 0.25;
    last_col[0] = 0.5;
    for(i = 1; i < n-1; i++){
        // set the pivot of U, U_ii
        printf("calculate pivot %d:\n", i);

        temp = MATRIX(a, i, i);
        MATRIX(a, i, i) -= MATRIX(a, i, i-1) * MATRIX(a, i-1, i);
        printf("a(%d, %d) -= a(%d, %d)*a(%d, %d)\n\tprevious: %.4lf after: %.4lf\n", i, i, i, i-1, i-1, i, temp, MATRIX(a, i, i));

        printf("calculate rest U and L:\n");
        if(i < n-2) {
            temp = MATRIX(a, i + 1, i);
            MATRIX(a, i + 1, i) /= MATRIX(a, i, i);
            printf("a(%d, %d) /= a(%d, %d)\n\tprevious: %.4lf after: %.4lf\n", i + 1, i, i, i, temp, MATRIX(a, i + 1, i));
        }
        // process the last element in this row and col specially
        if (i != last_index - 1) {
            last_row[i] = -MATRIX(a, i - 1, i) * last_row[i - 1];
            last_row[i] /= MATRIX(a, i, i);
            last_col[i] = -MATRIX(a, i, i - 1) * last_col[i - 1];
            MATRIX(a, last_index, last_index) -= last_row[i - 1] * last_col[i - 1];
            printf("sp_a(%d, %d) set to %.4lf\n", last_index, i, last_row[i]);
            printf("sp_b(%d, %d) set to %.4lf\n", i, last_index, last_col[i]);
        }
        else {
            MATRIX(a, last_index, last_index - 1) -= MATRIX(a, i - 1, i) * last_row[i - 1];
            MATRIX(a, last_index, last_index - 1) /= MATRIX(a, i, i);
            MATRIX(a, last_index - 1, last_index) -= MATRIX(a, i, i - 1) * last_col[i - 1];
            MATRIX(a, last_index, last_index) -= MATRIX(a, last_index, last_index - 1) * MATRIX(a, last_index - 1, last_index);
            last_row[i] = MATRIX(a, last_index, last_index - 1);
            last_col[i] = MATRIX(a, last_index - 1, last_index);

            printf("sp_a(%d, %d) set to %.4lf\n", last_index, last_index - 1, MATRIX(a, last_index, last_index - 1));
            printf("sp_b(%d, %d) set to %.4lf\n", last_index - 1, last_index, MATRIX(a, last_index - 1, last_index));
        }



        print_matrix(n, &a[0][0], p);

    }

    if(n == 3){
        a[0][0] = 0.5;  a[0][1] = 2;    a[0][2] = 0.5;
        a[1][0] = 0.25; a[1][1] = 1.875;a[1][2] = 0.375;
        a[2][0] = 0.2;  a[2][1] = 1.8;  a[2][2] = 0.25;
    }

    print_matrix(n, &a[0][0], p);

    // calculate y
    double y[n];
    y[0] = p[0];
    for(i = 1; i < last_index; i++){
        printf("y[%d] = p[%d] - L(%d, %d)*y[%d]: %0.4lf = %.4lf - %.4lf * %.4lf\n", i, i, i, i-1, i-1, y[i], p[i], L(n, a, last_row, i, i-1), y[i-1]);
        y[i] = p[i] - L(n, a, last_row, i, i-1) *y[i-1];
        printf("y[%d] = %.4lf\n", i, y[i]);

    }
    y[last_index] = p[last_index];
    for(j = 0; j < last_index; j++){
        printf("y[%d] -= L(%d, %d)*y[%d]: %0.4lf -= %.4lf * %.4lf\n", last_index, last_index, j, j, y[last_index], L(n, a, last_row, last_index, j), y[j]);
        y[last_index] -= L(n, a, last_row, last_index, j)*y[j];
        printf("y[%d] = %.4lf\n", last_index, y[last_index]);
    }

    printf("Y:\n");
    for(i = 0; i < n; i++)
        printf("%.2lf ", y[i]);
    putchar('\n');

    // calculate x
    printf("p[%d] = y[%d]/U(%d, %d): p[%d] -= %.4lf / %.4lf\n", n-1, n-1, n-1, n-1, n-1, y[n-1], U(n, a, last_col, n-1, n-1));
    p[n-1] = y[n-1]/ U(n, a, last_col, n-1, n-1);
    printf("p[%d] = %.4lf\n", n-1, p[n-1]);
    printf("p[%d] = (y[%d] - U(%d, %d)*p[%d])/U(%d, %d): %0.4lf = (%.4lf - %.4lf*%.4lf) / %.4lf\n", n-2, n-2, n-2, n-1, n-1, n-2, n-2, p[n-2], y[n-2], U(n, a, last_col, n-2, n-1), p[n-1], U(n, a, last_col, n-2, n-2));
    p[n-2] = (y[n-2] - U(n, a, last_col, n-2, n-1)*p[n-1])/ U(n, a, last_col, n-2, n-2);
    printf("p[%d] = %.4lf\n", n-2, p[n-2]);
    for(i = n-3; i >= 0; i--){
        p[i] = (y[i] - U(n, a, last_col, i, i+1)*p[i+1] - U(n, a, last_col, i, last_index)*p[last_index])/ U(n, a, last_col, i, i);
    }

    printf("X:\n");
    for(i = 0; i < n; i++)
        printf("%.2lf ", p[i]);
    putchar('\n');


    return;
}

int get_col(int n, int row, int col){
    if(row == 0 && col == n-1)
        return 0;
    if(row == n-1 && col == 0)
        return 2;
    int result = col - row + 1;
    if(result > 2) {
        printf("Col index out of range!!!\n");
        return -1;
    }
    return result;
}
double L(int n, double matrix[][3], double *last_row, int row, int col){
    if(row == col)
        return 1;
    if(col > row){
        printf("col out of range");
        return -1;
    }
    // last line
    if(row == n-1)
        return last_row[col];
    else {
        if(get_col(n, row, col) == -1)
            return 0;
        return MATRIX(matrix, row, col);
    }
}

double U(int n, double matrix[][3], double *last_col, int row, int col){
    if(row > col){
        printf("row out of range");
        return -1;
    }
    // last line but not last element
    if(col == n-1 && row != n-1)
        return last_col[row];
    else {
        if(get_col(n, row, col) == -1)
            return 0;
        return MATRIX(matrix, row, col);
    }
}


void print_matrix(int n, double *first, double *price) {
    int i, j;

    // print first line
    printf("%10.6lf", *(first+1));
    printf("%10.6lf", *(first+2));
    for(i = 0; i < n-3; i++)
        printf("%10.6lf", 0.0);
    printf("%10.6lf", *(first+0));
    putchar('|');
    printf("%10.6lf", *(price+0));
    putchar('\n');

    for(i = 1; i < n-1;i++){
        for(j = 0; j < i-1; j++)
            printf("%10.2lf", 0.0);
        printf("%10.6lf", *(first+i*3+0));
        printf("%10.6lf", *(first+i*3+1));
        printf("%10.6lf", *(first+i*3+2));
        for(j = 0; j < n-2-i; j++)
            printf("%10.6lf", 0.0);
        putchar('|');
        printf("%10.6lf", *(price+i));
        putchar('\n');
    }

    // print the last line
    printf("%10.6lf", *(first+(n-1)*3+2));
    for(i = 0; i < n-3; i++)
        printf("%10.2lf", 0.0);
    printf("%10.6lf", *(first+(n-1)*3+0));
    printf("%10.6lf", *(first+(n-1)*3+1));
    putchar('|');
    printf("%10.6lf", *(price+i));
    putchar('\n');
    putchar('\n');



}