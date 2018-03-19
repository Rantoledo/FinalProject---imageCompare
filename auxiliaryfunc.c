/*
 * auxiliaryfunc.c
 *
 *  Created on: 19 בספט׳ 2016
 *      Author: E5430
 */


#include "SPPoint.h"
#include "auxiliaryfunc.h"
#include "SPLogger.h"
#include "SPConfig.h"
#include <string.h>
#define MAXBUFF 1024


struct image
{
	int index;
	int hits;
};

void FindBestImages(int* bestimgArray, int* bingo, int numOfImages,
		int numOfSimilarImages){

	int maxIndex;
	int max;
	int i = 0;
	int j = 0;

	for (i = 0; i < numOfSimilarImages; i++){
		max = 0;
		maxIndex = 0;
		for (j = 0; j < numOfImages; j++){
			if (*(bingo+j) > max){
				max = *(bingo+j);
				maxIndex = j;
			}
		}
		*(bingo+maxIndex) = -1;
		*(bestimgArray+i) = maxIndex;
	}
}

void WriteAllFeatsToFile(FILE* WriteFile,SPPoint* p ,int numOfFeats){

	char* strPrint = (char*)malloc(sizeof(char)*MAXBUFF);
	int imageIndex,imageDim;
	imageIndex = spPointGetIndex(p[0]);
	imageDim = spPointGetDimension(p[0]);

	sprintf(strPrint,"%s%d%s%d%s%d%s", "Image Index: ",imageIndex, " Image dimension: ",imageDim,
			" Number of features: ",numOfFeats,"\n");

	fputs(strPrint,WriteFile);
	int i,j;
	for (i = 0; i < numOfFeats ; i++){
		for (j = 0; j < imageDim; j++){
			sprintf(strPrint,"%f%s",spPointGetAxisCoor(p[i],j),"\n");
			fputs(strPrint,WriteFile);
		}
	}
	free(strPrint);
}


SPPoint* ReadAllFeatsFromFile(FILE* Readfile, int* numOfFeatsPerImage){

	char* strRead = (char*)malloc(sizeof(char)*MAXBUFF);
	int imageIndex,imageDim,numOfFeats;
	double currentVal = 0;

	fscanf(Readfile,"%s %s %d %s %s %d %s %s %s %d",strRead,strRead,&imageIndex,strRead,strRead,&imageDim,
			strRead,strRead,strRead,&numOfFeats);

	*numOfFeatsPerImage = numOfFeats;
	double* featsOfImages = malloc(imageDim * sizeof(double));
	SPPoint* res = (SPPoint*) malloc(numOfFeats * sizeof(SPPoint));
	int i,j;
	for (i = 0; i < numOfFeats; i++){
		for (j = 0; j < imageDim; j++){
			fscanf(Readfile, "%lf",&currentVal);
			featsOfImages[j] = currentVal;
		}
		*(res+i) = spPointCreate(featsOfImages,imageDim,imageIndex);
	}
	free(strRead);
	free(featsOfImages);

	return res;
}
