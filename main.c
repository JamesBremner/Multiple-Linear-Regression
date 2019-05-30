#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "matrix.h"


double * readData(FILE * fp, int * numVarPtr, int * sampleSizePtr, char variableNames[10][25]);
Matrix loadX(int numVar, int sampleSize, double * data);
Matrix loadY(int numVar, int sampleSize, double * data);
void regress(Matrix x, Matrix y, int numVar, int sampleSize, double modelMetrics[17], double * coefficientMetrics);

int main(void) {
  FILE* text = fopen("test.txt", "r");
  if(text == NULL) printf("oops");

  int i, j;
  char varNames[10][25];
  double modelMetrics[17];
  double * coefficientMetrics;
  int numVar = 0;
  int * numVarPtr = &numVar;
  int sampleSize = 0;
  int * sampleSizePtr = &sampleSize;
  double errStdDev;
  double * errStdDevPtr = &errStdDev;
  
  double * data = readData(text, numVarPtr, sampleSizePtr, varNames);
  coefficientMetrics = (double*)malloc(sizeof(double) * 5 * (numVar + 1));
  Matrix x = loadX(numVar, sampleSize, data);
  Matrix y = loadY(numVar, sampleSize, data);
  free(data);

  Matrix B = genCoefficients(x, y);

  printf("\nRegression Equation:\n%s = %.2lf ", varNames[0], B.data[0]);
  for(i = 1; i < B.rows; i++) {
    printf("%+.2lf %s ",B.data[i], varNames[i]);
  }
  printf("\n");

  regress(x, y, numVar, sampleSize, modelMetrics, coefficientMetrics);

  for(i = 0; i < 17; i++) {
    printf("%.1lf\t\t%d\n", modelMetrics[i], i+1);
  }
  for(i = 0; i < (numVar + 1) * 5; i++) {
    printf("%.1lf\t\t%d\n", coefficientMetrics[i], i);
  }
  free(x.data);
  free(y.data);
  free(B.data);
  return 0;
}

double * readData(FILE * fp, int * numVarPtr, int * sampleSizePtr, char variableNames[10][25])
{
  char varString[100];
  fscanf(fp, "%[^\n]", varString);
  varString[99] = '\0';

  int i, j, ctr;
  j = 0; 
  ctr = 0;
  for(i = 0; i <= (strlen(varString)); i++){
    if(varString[i] == ','||varString[i] == '\0') {
        variableNames[ctr][j]='\0';
        ctr++;
        j = 0;
    }
    else {
      variableNames[ctr][j]=varString[i];
      j++;
    }
  }
  int size = 100;
  double tempDouble;
  double * data = malloc(sizeof(double) * size);
  if(data == NULL) exit(1);
  i = 0;
  while(fscanf(fp,"%lf,", &tempDouble) != EOF) {
    if(i >= size - 1) {
      //printf("Approaching data limit - increasing buffer size to %d bytes\n", (size + 100)*(int)sizeof(double));
      size += 100;
      data = realloc(data, size * sizeof(double));
      if(data == NULL) exit(1);
    }
    if(i == 0 || (i % (ctr + 1)) == 0 ) {
      data[i] = 1.0;
      i++;
    }
    data[i] = tempDouble;
    i++;
  }
  *sampleSizePtr = i/(ctr + 1);
  *numVarPtr = ctr;

  return data;
}

Matrix loadX(int numVar, int sampleSize, double * data)
{
  Matrix result;
  result.rows = sampleSize;
  result.cols = numVar;
  result.data = (double *)calloc(result.rows * result.cols, sizeof(double));
  int i,j;
  for(i = 0, j = 0; i < (numVar + 1) * sampleSize; i++) {
    if((i - 1) % (numVar + 1) != 0) {
      result.data[j] = data[i];
      j++;
    }
  }

  return result;
}

Matrix loadY(int numVar, int sampleSize, double * data)
{
  Matrix result;
  result.rows = sampleSize;
  result.cols = 1;
  result.data = (double *)calloc(result.rows * result.cols, sizeof(double));
  int i,j;
  for(i = 0, j = 0; i < (numVar + 1) * sampleSize; i++) {
    if((i - 1) % (numVar + 1) == 0) {
      result.data[j] = data[i];
      j++;
    }
  }

  return result;
}

void regress(Matrix x, Matrix y, int numVar, int sampleSize, double modelMetrics[15], double * coefficientMetrics)
{
  int i;
  double errStdDev = 0;
  double * errStdDevPtr = &errStdDev;
  double sum = 0;
  double yMean = 0;
  for(i = 0; i < y.rows; i++) {
    sum+= y.data[i];
  }
  yMean = sum / y.rows;
  sum = 0;

  //set metrics to increasing numbers for testing
  for(i = 0; i < 17; i++) {
    modelMetrics[i] = 0;
  }

  for(i = 0; i < (numVar + 1) * 5; i++) {
    coefficientMetrics[i] = i;
  }


  Matrix B = genCoefficients(x, y);
  Matrix residuals = calcResiduals(x, y, B, errStdDevPtr);
  Matrix stdErrMatrix = stdErr(x, errStdDev);
  Matrix Yhat = initMatrix(y.rows, 1);
  Yhat = multiMatrix(x, B);

  modelMetrics[0] = sampleSize;
  modelMetrics[1] = numVar - 1;
  modelMetrics[2] = sampleSize - numVar;
  
  for(i = 0; i < y.rows; i++) {
    sum += (Yhat.data[i] - yMean) * (Yhat.data[i] - yMean);
  }
  modelMetrics[4] = sum;
  sum = 0;
  modelMetrics[5] = numVar - 1;
  modelMetrics[6] = modelMetrics[4] / modelMetrics[5];

  for(i = 0; i < y.rows; i++) {
    sum += (y.data[i] - Yhat.data[i]) * (y.data[i] - Yhat.data[i]);
  }
  modelMetrics[8] = sum;
  sum = 0;
  modelMetrics[9] = sampleSize - numVar;
  modelMetrics[10] = modelMetrics[8] / modelMetrics[9];

  for(i = 0; i < y.rows; i++) {
    sum += (y.data[i] - yMean) * (y.data[i] - yMean);
  }
  modelMetrics[12] = sum;
  sum = 0;
  modelMetrics[13] = sampleSize - 1;
  modelMetrics[14] = modelMetrics[12] / modelMetrics[13];

  modelMetrics[3] = modelMetrics[6] / modelMetrics[10];




  /*printf("\nRegression Equation:\n = %.2lf ", B.data[0]);
  for(i = 1; i < B.rows; i++) {
    printf("%+.2lf ",B.data[i]);
  }*/

  free(B.data);
  free(residuals.data);
  free(stdErrMatrix.data);
  free(Yhat.data);
}