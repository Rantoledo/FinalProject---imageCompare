#include <cstdlib>
#include <cstdbool>
#include <cstring>
#include <cstdio>
#include <climits>
#include <cassert>
#include "SPImageProc.h"
#define MAXBUFF 1024
#define MODER "r"
#define MODEW "w"
#define DELIM ","
#define BLANK1 ' '
int totalNumOfFeats;
using namespace sp;
using namespace std;

extern "C"{
#include "SPConfig.h"
#include "SPPoint.h"
#include "SPLogger.h"
#include "SPHelpFunctions.h"
#include "KD-tree.h"
#include "SPListElement.h"
#include "auxiliaryfunc.h"
}
/*
 * This functions extracts features from all images and returns them in an array of SPPoints
 * where every SPPoints represent a valid feature: SPPoint's index will be the corresponding image's
 * index. and data array will contain the feature's relevant values.
 * @param imgProc - a valid ImageProc object for configFile
 * @param configFile - a valid configFile object after iniatlization
 * @param msg an SP_CONFIG_MSG pointer.
 * @param filename - the filename that will be created. "spcbir.config" in case no filename is recieved by user
 * @param defaultCon - boolean representing weather or not the default config file was used
 * @param configFile - a pointer to the configFile that will be created in case of success
 * @return the function returns an array of SPPoints containing all features extracted from images
 * relevant messages will be printed out to logger. in case of failure - all resources will be freed
 * and program will be terminated.
 */


SPPoint* extractionHandle(ImageProc imgProc, SPConfig* configFile,SP_CONFIG_MSG* msg){

	int NumOfImages = spConfigGetNumOfImages(*configFile,msg);
	int NumOfExtFeats;
	totalNumOfFeats = 0;

	char* path = (char*)malloc(sizeof(char)*MAXBUFF);
	SPPoint** ImagesPoints2dArr = (SPPoint**)malloc(NumOfImages*sizeof(SPPoint*));
	int* NumOfFeatsPerImage = (int*)malloc(NumOfImages*sizeof(int));

	FILE* writingFile = NULL;
	FILE* readingFile = NULL;

	SPPoint* ImagesPoints1dArray = NULL;
	int counter=0;

	//Check if we are in extraction mode
	if (spConfigIsExtractionMode(*configFile,msg)) {

		spLoggerPrintDebug("Entered extraction mode\n","main.c",__func__,__LINE__);

		// writing the feats file
		for (int i = 0; i < NumOfImages; i++){

			*msg = spConfigGetImagePath(path,*configFile,i);
			if (*msg != SP_CONFIG_SUCCESS){
				free(path);
				for (int j=0; j < NumOfImages; j++){
					free(*(ImagesPoints2dArr+j));
				}
				free(NumOfFeatsPerImage);
				return NULL;
			}

			//extracting the image features
			*(ImagesPoints2dArr+i) = imgProc.getImageFeatures(path,i,&NumOfExtFeats);
			totalNumOfFeats += NumOfExtFeats;
			*(NumOfFeatsPerImage+i) = NumOfExtFeats;

			*msg = spConfigGetFeatsPath(path,*configFile,i);
			if (*msg != SP_CONFIG_SUCCESS){
				free(path);
				for (int j=0; j < i; j++){
					free(*(ImagesPoints2dArr+j));
				}
				free(NumOfFeatsPerImage);
				return NULL;
			}

			writingFile = fopen(path,"w");

			if (writingFile == NULL){
				spLoggerPrintError("Failed opening file for writing feats","main.c",__func__,__LINE__);
				free(path);
				for (int j=0; j < i; j++){
					free(*(ImagesPoints2dArr+j));
				}
				free(NumOfFeatsPerImage);
				return NULL;
			}

			// Writes the feats to file
			WriteAllFeatsToFile(writingFile,*(ImagesPoints2dArr+i),NumOfExtFeats);
		}
		fclose(writingFile);
	}
	else{ // We're in Non-Extraction mode

		spLoggerPrintDebug("Entered Non-Extraction mode\n","main.c",__func__,__LINE__);

		for (int i = 0; i < NumOfImages; i++){

			// Gets feats path of each image
			*msg = spConfigGetFeatsPath(path,*configFile,i);
			if (*msg != SP_CONFIG_SUCCESS){
				free(path);
				for (int j=0; j < NumOfImages; j++){
					free(*(ImagesPoints2dArr+j));
				}
				free(NumOfFeatsPerImage);
				return NULL;
			}

			readingFile = fopen(path,"r");
			if (readingFile == NULL){
				spLoggerPrintError("Failed opening file for writing feats","main.c",__func__,__LINE__);
				return NULL;
			}

			// Reads the feats from file
			*(ImagesPoints2dArr+i) = ReadAllFeatsFromFile(readingFile,(NumOfFeatsPerImage+i));
			totalNumOfFeats += *(NumOfFeatsPerImage+i);
		}
		fclose(readingFile);
	}

	// all images will be moved to ImagesPoints1dArray
	spLoggerPrintDebug("Start loading all points to ImagesPoints1dArray\n","main.c",__func__,__LINE__);
	ImagesPoints1dArray = (SPPoint*)malloc(sizeof(SPPoint)*totalNumOfFeats);
	for (int i = 0; i < NumOfImages; i++){
		for (int j = 0; j < *(NumOfFeatsPerImage+i); j++){
			*(ImagesPoints1dArray+counter) = spPointCopy(ImagesPoints2dArr[i][j]);
			counter++;
		}
	}

	for (int i=0 ; i < NumOfImages ; i++){
		DestroySPPointarr(*(ImagesPoints2dArr+i),*(NumOfFeatsPerImage+i));
	}
	free(path);
	free(NumOfFeatsPerImage);
	return ImagesPoints1dArray;
}


int main(int argc, char* argv[]){

	//will be true if default config file is used
	bool *defaultCon=(bool*) malloc(sizeof(bool));
	*defaultCon=false;

	char* filename=NULL;
	SPPoint* allFeatures=NULL;

	SP_CONFIG_MSG* msg=(SP_CONFIG_MSG*) malloc(sizeof(SP_CONFIG_MSG));
	SPConfig* configFile=(SPConfig*) malloc(sizeof(SPConfig));

	//check Arguments, filename will contain the config file name if arguments are legal
	checkArgs(argc,argv,defaultCon,filename,msg,configFile);
	//Creates SPLogger

	SP_LOGGER_MSG msgL = spLoggerCreate(GETspLoggerFilename(*configFile,msg),intToLvl(GETspLoggerLevel((const SPConfig) *configFile, msg)));

	if((msgL!=SP_LOGGER_SUCCESS)&(msgL!=SP_LOGGER_DEFINED)){  // logger wasn't initialized
			printf("Error during initialization of SPLogger\n");
			printf("Exiting...");
			fflush(stdout);
			exit(0);
	}

	int numOfSimilarImages = GETspNumOfSimilarImages(*configFile, msg);

	// initialize imgproc
	ImageProc *imgProc=new ImageProc(*configFile);

	//extractionHandle extracts all features from images/.feats files
	allFeatures=extractionHandle(*imgProc,configFile,msg);
	if (allFeatures == NULL){
		spLoggerPrintError("failed to create allFeatures SPPoints array. Exiting program...","main.c", __func__, __LINE__);
		free(msg);
		free(defaultCon);
		spConfigDestroy(*configFile);
		spLoggerDestroy();
		return 0;
	}

	spTreeSplit* SplitMethod =  GETspKDTreeSplitMethod(*configFile, msg);

	// build the KDTree
	spLoggerPrintDebug("Creating KDTree...\n","main.c", __func__, __LINE__);
	KDTreeNode treeHead = CreateTree(allFeatures, totalNumOfFeats, SplitMethod);

	//checking if KDTree is NULL
	if (treeHead == NULL){
		spLoggerPrintError("KD Tree initialization failed. Exiting program...","main.c", __func__, __LINE__);
		free(msg);
		free(defaultCon);
		spConfigDestroy(*configFile);
		DestroySPPointarr(allFeatures,totalNumOfFeats);
		spLoggerDestroy();
		return 0;
	}

	// as long as bye is false, while is running
	bool bye = false;

	while (!bye){

		char queryPath[1024];
		printf("Please enter an image path:\n");
		fflush(stdout);
		scanf("%s" , queryPath);

		// if user decides to exit
		if (strcmp(queryPath, "<>") == 0){
			printf("Exiting...\n");
			fflush(stdout);
			bye = true;
			break;
		}

		// Number of images from config
		int NumOfImages = spConfigGetNumOfImages(*configFile, msg);

		// bingo array will contain number of "matches" for each image
		int i=0;
		int* bingo = (int*)malloc(sizeof(int)*NumOfImages);
		// check if bingo allocation failed
		if (bingo == NULL){
			spLoggerPrintError("bingo initialization failed. Exiting program...","main.c", __func__, __LINE__);
			bye = true;
			break;
		}
		spLoggerPrintDebug("setting bingo...\n","main.c", __func__, __LINE__);
		for (i=0 ; i < NumOfImages ; i++){
			*(bingo+i) = 0;
		}

		// bestImgArray will contain the closest images when at index 0 we will have the best match
		int* bestImgArray = (int*)malloc(sizeof(int)*numOfSimilarImages);
		// check if bestImgArray allocation failed
		if (bestImgArray == NULL){
			spLoggerPrintError("bestImgArray initialization failed. Exiting program...","main.c", __func__, __LINE__);
			free(bingo);
			bye = true;
			break;
		}
		int querysNumOfFeatures;


		// pulling the features out of the image chosen by the user
		spLoggerPrintDebug("Getting queryFeatures...\n","main.c", __func__, __LINE__);
		SPPoint* queryFeatures =  imgProc->getImageFeatures(queryPath, NumOfImages, &querysNumOfFeatures);
		// check if queryFeatures initialization failed
		if (queryFeatures == NULL){
			spLoggerPrintError("queryFeatures initialization failed. Exiting program...","main.c", __func__, __LINE__);
			free(bingo);
			free(bestImgArray);
			bye = true;
			break;
		}

		// spKNN from config
		int spkNN = GETspKNN(*configFile, msg);

		// updating the bingo array according to the matches found by KDTreeSearch
		spLoggerPrintDebug("updating the bingo array according to the matches found by KDTreeSearch...\n","main.c", __func__, __LINE__);
		for (i=0 ; i < querysNumOfFeatures ; i++){
			SPBPQueue bpq;
			bpq = KDTreeSearch(treeHead, *(queryFeatures+i), spkNN);
			if (bpq == NULL){
				spLoggerPrintError("failed to create bpq. Exiting program...","main.c", __func__, __LINE__);
				free(bingo);
				free(bestImgArray);
				DestroySPPointarr(queryFeatures, querysNumOfFeatures);
				bye = true;
				break;
			}
			while(!(spBPQueueIsEmpty(bpq))){
				SPListElement tempElm;
				tempElm = spBPQueuePeek(bpq);
				bingo[spListElementGetIndex(tempElm)]++;
				spListElementDestroy(tempElm);
				spBPQueueDequeue(bpq);
			}
			spBPQueueDestroy(bpq);
		}

		// calculate the best images out of the bingo array, updating bestImgArray
		FindBestImages(bestImgArray, bingo, NumOfImages, numOfSimilarImages);

		char* tempImgPath = (char*)malloc(sizeof(char)*1024);
		if (tempImgPath == NULL){
			spLoggerPrintError("tempImgPath initialization failed. Exiting program...","main.c", __func__, __LINE__);
			free(bingo);
			free(bestImgArray);
			DestroySPPointarr(queryFeatures, querysNumOfFeatures);
			bye = true;
			break;
		}

		// showing the images
		spLoggerPrintDebug("showing results...\n","main.c", __func__, __LINE__);
		if (spConfigMinimalGui(*configFile, msg)){
			for (i = 0; i < numOfSimilarImages; i++){
				spConfigGetImagePath(tempImgPath, *configFile, *(bestImgArray+i));
				imgProc->showImage(tempImgPath);
			}
		}
		else{
			printf("Best candidates for - %s - are:\n", queryPath);
			for (i = 0; i < numOfSimilarImages; i++){
				spConfigGetImagePath(tempImgPath, *configFile, *(bestImgArray+i));
				printf("%s\n", tempImgPath);
			}
		}
		free(bingo);
		free(bestImgArray);
		free(tempImgPath);
		DestroySPPointarr(queryFeatures, querysNumOfFeatures);

	}
	free(msg);
	free(defaultCon);
	spConfigDestroy(*configFile);
	DestroySPPointarr(allFeatures,totalNumOfFeats);
	spLoggerDestroy();
	DestroyNode(treeHead);
	return 0;

}
