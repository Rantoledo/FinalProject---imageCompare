/*
 * auxiliaryfunc.h
 *
 *  Created on: 19 בספט׳ 2016
 *      Author: E5430
 */


#include "SPPoint.h"

#include "SPLogger.h"
#include "SPConfig.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXBUFF 1024

/*
 * this function gets bestimgArray that will contain the best matches indexes,
 * bingo array - which we used to increment each image index, and their sizes.
 * the function calculate the best matches and put the in bestimgArray,
 * when at the 0 place we have the best match
 */
void FindBestImages(int* bestimgArray, int* bingo, int numOfImages,
		int numOfSimilarImages);


/*
 * this function reads all feats from file
 * the function gets a file, and a number of feats needs to be readen
 * the function return a SPPoint* that contain the feats that it read from the file.
 */
SPPoint* ReadAllFeatsFromFile(FILE* Readfile, int* numOfFeatsPerImage);

/*
 * this function writes all feats to file
 * the function gets a file, and a number of feats needs to be written, and a SPPoint p
 * the function returns nothing, just writing the feats to the file.
 */
void WriteAllFeatsToFile(FILE* WriteFile,SPPoint* p ,int numOfFeats);


