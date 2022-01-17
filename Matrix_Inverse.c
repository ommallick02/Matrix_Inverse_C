//C Program to calculate inverse of a matrix

//Header Files and Macros
#include <stdio.h>
#include <math.h>
#define maxsize 10

//Function Declarations
int Input_Size();
void Input_Array(float array[maxsize][maxsize], int size);
void Print_Array(float array[maxsize][maxsize], int size);
float Determinant(float array[maxsize][maxsize], int size);
void Copy_Array(float array[maxsize][maxsize], float array1[maxsize][maxsize], int size, int row, int col);
void Inverse(float array[maxsize][maxsize], float inverse[maxsize][maxsize], int size, float det);
void Minor(float array[maxsize][maxsize], float inverse[maxsize][maxsize], int size);
void Cofactor(float inverse[maxsize][maxsize], int size);
void Adjoint(float inverse[maxsize][maxsize], int size);

//Main Function
int main(void)
{
    //Initialising arrays
    float array[maxsize][maxsize], inverse[maxsize][maxsize], det;

    //Input Order of Matrix
    int size = Input_Size();

    //Input Matrix
    Input_Array(array, size);

    //Print Matrix
    Print_Array(array, size);

    //Calculate Determinant of Original Matrix
    det = Determinant(array, size);

    if(det == 0)
    {
        printf("Determinant of Matrix is 0\nInverse is not Possible\n");
        return 1;
    }

    //Calculate and Print Inverse Matrix
    Inverse(array, inverse, size, det);
    Print_Array(inverse, size);

    return 0;
}

//Function Definations
//Function to Input Order of Matrix
int Input_Size()
{
    int size;
    char ch;

    //Loops to take in only valid values
    do
    {
        do
        {
            printf("Enter the order of the matrix (max. %d): ", maxsize);
            scanf(" %d", &size);
            scanf("%c", &ch);
        }
        while (ch != '\n');
    }
    while (size < 1 || size > maxsize);

    //Return order of matrix
    return size;
}
//Function to Input Matrix
void Input_Array(float array[maxsize][maxsize], int size)
{
    int i, j;
    //Loops to intake matrix elements
    for (i = 0; i < size; ++i)
    {
        printf("\nEnter Elements of Row %d:\n", i + 1);
        for (j = 0; j < size; ++j)
        {
            printf("Element %d: ", j + 1);
            scanf(" %f", &array[i][j]);
        }
    }
}
//Function to Print Matrix
void Print_Array(float array[maxsize][maxsize], int size)
{
    int i, j;
    printf("\nMatrix:\n");
    //Loops to print matrix elements
    for (i = 0; i < size; ++i)
    {
        for (j = 0; j < size; ++j)
        {
            printf("%.2f\t", array[i][j]);
        }
        printf("\n");
    }
}
//Function to Calculate determinant
float Determinant(float array[maxsize][maxsize], int size)
{
    //Determinant of matrix of order 1, is the element itself
    if (size == 1)
    {
        return array[0][0];
    }

    int i, j;
    float sum = 0, temp_array[size - 1][size - 1], sign, det;

    //Loop to
    for (i = 0, j = 0; j < size; ++j)
    {
        sign = pow(-1, i + j);
        Copy_Array(array, temp_array, size, i, j);
        det = Determinant(temp_array, size - 1);
        sum += sign * array[i][j] * det;
    }

    //Return value of determinant
    return sum;
}
//Function to copy elements of one matrix to another
void Copy_Array(float array[maxsize][maxsize], float temp_array[maxsize][maxsize], int size, int row, int col)
{
    int i, j, k, l;
    //Loops to copy all elements of array ,not belonging to mentioned row and column,to temp_array
    for (i = 0, k = 0; i < size; ++i)
    {
        //Skips if the row is the mentioned row
        if (i == row)
        {
            continue;
        }
        for (j = 0, l = 0; j < size; ++j)
        {
            //Skips if the column is the mentioned column
            if (j == col)
            {
                continue;
            }
            temp_array[k][l] = array[i][j];
            ++l;
        }
        ++k;
    }
}
//Function to Calculate inverse of a matrix
void Inverse(float array[maxsize][maxsize], float inverse[maxsize][maxsize], int size, float det)
{
    //Calculate Minor Matrix
    Minor(array, inverse, size);

    //Convert Minor Matrix to Cofactor Matrix
    Cofactor(inverse, size);

    //Convert Cofactor Matrix to Adjoint Matrix
    Adjoint(inverse, size);

    //Loop to Convert Adjoint Matrix to Inverse Matrix
    int i, j;
    for (i = 0; i < size; ++i)
    {
        for (j = 0; j < size; ++j)
        {
            inverse[i][j] /= det;
            if (inverse[i][j] == -0.0)
            {
                inverse[i][j] = 0.0;
            }
        }
    }
}
//Function to Calculate minor matrix
void Minor(float array[maxsize][maxsize], float inverse[maxsize][maxsize], int size)
{
    //Special Case of Matrix of Order 1
    if (size == 1)
    {
        inverse[0][0] = 1;
        return;
    }

    int i, j;
    float temp_array[size - 1][size - 1];

    //Loops to calculate Minor Matrix
    for (i = 0; i < size; ++i)
    {
        for (j = 0; j < size; ++j)
        {
            Copy_Array(array, temp_array, size, i, j);
            inverse[i][j] = Determinant(temp_array, size - 1);
        }
    }
}
//Function to Calculate cofactor matrix
void Cofactor(float inverse[maxsize][maxsize], int size)
{
    int i, j;

    //Loops to calculate Cofactor Matrix
    for (i = 0; i < size; ++i)
    {
        for (j = 0; j < size; ++j)
        {
            if ((i + j) % 2 == 1)
            {
                inverse[i][j] *= -1;
            }
        }
    }
}
//Function to Calculate adjoint matrix
void Adjoint(float inverse[maxsize][maxsize], int size)
{
    int i, j, temp;
    //Loops to calculate Adjoint Matrix
    for (i = 0; i < size; ++i)
    {
        for (j = i + 1; j < size; ++j)
        {
            temp = inverse[j][i];
            inverse[j][i] = inverse[i][j];
            inverse[i][j] = temp;
        }
    }
}