#ifndef BMPPROCESSING_H_INCLUDED
#define BMPPROCESSING_H_INCLUDED
#include <windef.h>
#include <wingdi.h>

void readInput(char *fileName);
void writeOutput(char *fileName);
int checkMethod(char *method);
void callMethod(char *method);
void getPixel(CHAR *pic, int x, int y, RGBTRIPLE *triple);
void setPixel(CHAR *pic, int x, int y, RGBTRIPLE *triple);
void processToGray();
void filterWithMatrix(double *matrix, int n);
void processFilter3x3();
void processGauss5x5();
void processCopy();
void methodError();


#endif // BMPPROCESSING_H_INCLUDED
