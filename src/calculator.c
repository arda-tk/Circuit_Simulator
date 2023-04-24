#include <math.h>
#include <stdio.h>
#include "../include/calculator.h"

/*
 * input: base, power
 * output: base to the power of "power"
 *
 * given a base and its power, calculates base^(power)
 */
float power(float base, int pow)
{
    float retVal = 1.0;
    if(pow == 1)
        return base;
    if(pow) //if power is positive
    {
        for(int i=0; i<pow; i++)
        retVal = retVal * base;
    }
    for(int i=0; i>pow; i--) //if power is negative
        retVal = retVal / base;
    return retVal;
}

/*
 * input: order of magnitude
 * output: 10 to the power of "order of magnitude"
 *
 * for a given order, calculates 10 to the power of "order",
 * can be thought of a modified version of the "power" function
 */
float calMag(int order)
{
    float retVal = 1.0;
    if(order == 1)
        return 1;
    if(order) //if power is positive
    {
        for(int i=0; i<order; i++)
        retVal = retVal * 10;
    }
    for(int i=0; i>order; i--) //if power is negative
        retVal = retVal / 10;
    return retVal;
}

/*
 * input: list of node IDs, length of the list
 * output: void
 *
 * applies bubble sort on a given array, in ascending order
 */
void sortNodeID(int *nodeDataPtr, int numberOfData)
{
    int swapVar;

    for(int i=0; i<numberOfData-1; i++)
    {
        for(int j=0; j<numberOfData-i-1; j++)
        {
            if(*(nodeDataPtr+j) > *(nodeDataPtr+j+1))
            {
                swapVar = *(nodeDataPtr+j);
                *(nodeDataPtr+j) = *(nodeDataPtr+j+1);
                *(nodeDataPtr+j+1) = swapVar;
            }
        }
    }
}

/*
 * input: n by n matrix, the size "n"
 * output: void
 *
 * prints the elements of an n by n matrix
 */
void print_matrix(float **matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

/*
 * input: n by n matrix, the size "n"
 * output: void
 *
 * performs forward and backward Gauss Elimination on
 * the input matrix, only leaving the diagonal and zeroing
 * the upper and lower triangles
 */
void transform_matrix(float **matrix, int size)
{
    // Perform forward elimination
    for (int k = 0; k < size-1; k++)
    {
        for (int i = k+1; i < size; i++)
        {
            float factor = matrix[i][k] / matrix[k][k];

            for (int j = k; j < size; j++)
            {
                matrix[i][j] -= factor * matrix[k][j];
            }
        }
    }

    // Perform backward substitution
    for (int k = size-1; k >= 0; k--)
    {
        for (int i = k-1; i >= 0; i--)
        {
            float factor = matrix[i][k] / matrix[k][k];

            for (int j = k; j >= 0; j--)
            {
                matrix[i][j] -= factor * matrix[k][j];
            }
        }
    }
}

/*
 * input: n by n matrix, n by 1 input matrix, n by 1 output matrix,
 * the size "n"
 * output: void
 *
 * multiplies the n by n matrix and n by 1 input matrix, stores the
 * output in an n by 1 output matrix
 */
void matrix_vector_multiply(float **matrix, float *vector, float *result, int size)
{
    for (int i = 0; i < size; i++)
    {
        float sum = 0;

        for (int j = 0; j < size; j++)
        {
            sum += matrix[i][j] * vector[j];
        }
        result[i] = sum;
    }
}

/*
 * input: n by n input matrix, n by n output matrix, the size "n"
 * output: void
 *
 * calculates the inverse of an n by n input matrix, feeds the results
 * into another n by n output matrix
 */
void inverse_matrix(float **matrix, float **result, int size)
{
    // Initialize the result matrix as the identity matrix
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
            {
                result[i][j] = 1.0;
            }
            else
            {
                result[i][j] = 0.0;
            }
        }
    }

    // Perform forward elimination with partial pivoting
    for (int k = 0; k < size; k++)
    {
        // Find the pivot row
        int pivot_row = k;
        float max_val = fabs(matrix[k][k]);
        for (int i = k+1; i < size; i++)
        {
            if (fabs(matrix[i][k]) > max_val)
            {
                max_val = fabs(matrix[i][k]);
                pivot_row = i;
            }
        }

        // Swap the current row with the pivot row
        if (pivot_row != k)
        {
            for (int j = 0; j < size; j++)
            {
                float temp = matrix[k][j];
                matrix[k][j] = matrix[pivot_row][j];
                matrix[pivot_row][j] = temp;
                temp = result[k][j];
                result[k][j] = result[pivot_row][j];
                result[pivot_row][j] = temp;
            }
        }

        // Scale the pivot row to make the pivot element 1
        float pivot = matrix[k][k];

        for (int j = k; j < size; j++)
        {
            matrix[k][j] /= pivot;
        }

        for (int j = 0; j < size; j++)
        {
            result[k][j] /= pivot;
        }

        // Use the pivot row to eliminate the elements below the pivot
        for (int i = k+1; i < size; i++)
        {
            float factor = matrix[i][k];

            for (int j = k; j < size; j++)
            {
                matrix[i][j] -= factor * matrix[k][j];
            }

            for (int j = 0; j < size; j++)
            {
                result[i][j] -= factor * result[k][j];
            }
        }
    }

    // Perform back substitution
    for (int k = size-1; k >= 0; k--)
    {
        for (int i = k-1; i >= 0; i--)
        {
            float factor = matrix[i][k];

            for (int j = k; j < size; j++)
            {
                matrix[i][j] -= factor * matrix[k][j];
            }

            for (int j = 0; j < size; j++)
            {
                result[i][j] -= factor * result[k][j];
            }
        }
    }
}


