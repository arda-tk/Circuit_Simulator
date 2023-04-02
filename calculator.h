#ifndef _calculator_c_
#define _calculator_c_

float power(float base, int pow); //calculate power
float calMag(int order); //calculate magnitude
void sortNodeID(int *nodeDataPtr, int numberOfData);
void print_matrix(float **matrix, int n);
void transform_matrix(float **matrix, int size);
void matrix_vector_multiply(float **matrix, float *vector, float *result, int size);
void inverse_matrix(float **matrix, float **result, int size);


//float nodeVoltage(int nodeID);

#endif // _calculator_c_
