#ifndef SPCONFIG_H_
#define SPCONFIG_H_

#include <stdbool.h>
#include <stdio.h>
#include "SPLogger.h"
extern int lineError;
extern int numOL;

/**
 * A data-structure which is used for configuring the system.
 */

typedef enum sp_config_msg_t {
	SP_CONFIG_INVALID_SUFFIX,
	SP_CONFIG_INVALID_BOOL,
	SP_CONFIG_INVALID_LINE,
	SP_CONFIG_MISSING_DIR,
	SP_CONFIG_MISSING_PREFIX,
	SP_CONFIG_MISSING_SPACE,
	SP_CONFIG_INVALID_SPTREESPLIT,
	SP_CONFIG_MISSING_SUFFIX,
	SP_CONFIG_MISSING_NUM_IMAGES,
	SP_CONFIG_CANNOT_OPEN_FILE,
	SP_CONFIG_ALLOC_FAIL,
	SP_CONFIG_INVALID_INTEGER,
	SP_CONFIG_INVALID_STRING,
	SP_CONFIG_INVALID_ARGUMENT,
	SP_CONFIG_INDEX_OUT_OF_RANGE,
	SP_CONFIG_SUCCESS
} SP_CONFIG_MSG;

typedef struct sp_config_t* SPConfig;
/**
 * A data-structure which is used for configuring the cut method for the kd-tree
 */

typedef enum sp_tree_split {
	RANDOM,
	MAX_SPREAD,
	INCREMENTAL
} spTreeSplit;

/**
 * Creates a new system configuration struct. The configuration struct
 * is initialized based on the configuration file given by 'filename'.
 * 
 * @param filename - the name of the configuration file
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return NULL in case an error occurs. Otherwise, a pointer to a struct which
 * 		   contains all system configuration.
 * 
 * The resulting value stored in msg is as follow:
 * - SP_CONFIG_INVALID_ARGUMENT - if filename == NULL
 * -	SP_CONFIG_INVALID_LINE - if line is invalid
 * - SP_CONFIG_INVALID_SPTREESPLIT - if tree split method is invalid
 * 	- SP_CONFIG_INVALID_BOOL is boolean value is invalid
 * - SP_CONFIG_CANNOT_OPEN_FILE - if the configuration file given by filename cannot be open
 * - SP_CONFIG_ALLOC_FAIL - if an allocation failure occurred
 * - SP_CONFIG_INVALID_INTEGER - if a line in the config file contains invalid integer or <=0
 * - SP_CONFIG_INVALID_STRING - if a line in the config file contains invalid string
 * - SP_CONFIG_MISSING_DIR - if spImagesDirectory is missing
 * - SP_CONFIG_MISSING_PREFIX - if spImagesPrefix is missing
 * - SP_CONFIG_MISSING_SUFFIX - if spImagesSuffix is missing 
 *  * - SP_CONFIG_INVALID_SUFFIX - if spImagesSuffix is invalid(not jpg or bmp or gif or png)
 * - SP_CONFIG_MISSING_NUM_IMAGES - if spNumOfImages is missing
 * - SP_CONFIG_SUCCESS - in case of success
 *
 *
 */
SPConfig spConfigCreate(const char* filename, SP_CONFIG_MSG* msg);

/*
 * Returns true if spExtractionMode = true, false otherwise.
 *
 * @param config - the configuration structure
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return true if spExtractionMode = true, false otherwise.
 *
 * - SP_CONFIG_INVALID_ARGUMENT - if config == NULL
 * - SP_CONFIG_SUCCESS - in case of success
 */
bool spConfigIsExtractionMode(const SPConfig config, SP_CONFIG_MSG* msg);

/*
 * Returns an initalized SPConfig file with updated default values if config!=NULL.
 *
 * @param config - the configuration structure to be iniatlized
 * @return an initalized SPConfig file
 *
 */
SPConfig initConfig(SPConfig config);

/*
 * Returns true if spMinimalGUI = true, false otherwise.
 *
 * @param config - the configuration structure
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return true if spMinimalGui = true, false otherwise.
 *
 * - SP_CONFIG_INVALID_ARGUMENT - if config == NULL
 * - SP_CONFIG_SUCCESS - in case of success
 */
bool spConfigMinimalGui(const SPConfig config, SP_CONFIG_MSG* msg);

/*
 * Returns the number of images set in the configuration file, i.e the value
 * of spNumOfImages.
 *
 * @param config - the configuration structure
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return positive integer in success, negative integer otherwise.
 *
 * - SP_CONFIG_INVALID_ARGUMENT - if config == NULL
 * - SP_CONFIG_SUCCESS - in case of success
 */
int spConfigGetNumOfImages(const SPConfig config, SP_CONFIG_MSG* msg);

/*
 * Returns the number of features to be extracted. i.e the value
 * of spNumOfFeatures.
 *
 * @param config - the configuration structure
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return positive integer in success, negative integer otherwise.
 *
 * - SP_CONFIG_INVALID_ARGUMENT - if config == NULL
 * - SP_CONFIG_SUCCESS - in case of success
 */
int spConfigGetNumOfFeatures(const SPConfig config, SP_CONFIG_MSG* msg);

/*
 * Returns the path for the images. i.e the value
 * of spImagesDirectory
 *
 * @param config - the configuration structure
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return valid char* in success,MULL otherwise.
 *
 * - SP_CONFIG_INVALID_ARGUMENT - if config == NULL
 * - SP_CONFIG_SUCCESS - in case of success
 */
char* GETspImagesDirectory(SPConfig config, SP_CONFIG_MSG* msg);

/*
 * Returns the prefix for the images. i.e the value
 * of spImagesPrefix.
 *
 * @param config - the configuration structure
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return valid char* in success,MULL otherwise.
 *
 * - SP_CONFIG_INVALID_ARGUMENT - if config == NULL
 * - SP_CONFIG_SUCCESS - in case of success
 */
char* GETspImagesPrefix(const SPConfig config, SP_CONFIG_MSG* msg);
/*
 * Returns the suffix for the images. i.e the value
 * of spImagesSuffix.
 *
 * @param config - the configuration structure
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return valid char* in success,MULL otherwise.
 *
 * - SP_CONFIG_INVALID_ARGUMENT - if config == NULL
 * - SP_CONFIG_SUCCESS - in case of success
 */
char* GETspImagesSuffix(const SPConfig config, SP_CONFIG_MSG* msg);

/*
 * Returns the name of the PCA file. i.e the value
 * of spPCAFilename.
 *
 * @param config - the configuration structure
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return valid char* in success,MULL otherwise.
 *
 * - SP_CONFIG_INVALID_ARGUMENT - if config == NULL
 * - SP_CONFIG_SUCCESS - in case of success
 */
char* GETspPCAFilename(const SPConfig config, SP_CONFIG_MSG* msg);

/*
 * Returns the number of similar images to be presented. i.e the value
 * of spNumOfSimilarImages.
 *
 * @param config - the configuration structure
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return positive integer in success, negative integer otherwise.
 *
 * - SP_CONFIG_INVALID_ARGUMENT - if config == NULL
 * - SP_CONFIG_SUCCESS - in case of success
 */
int GETspNumOfSimilarImages(const SPConfig config, SP_CONFIG_MSG* msg);

/*
 * Returns the number k to be used in search algorithm. i.e the value
 * of spKNN.
 *
 * @param config - the configuration structure
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return positive integer in success, negative integer otherwise.
 *
 * - SP_CONFIG_INVALID_ARGUMENT - if config == NULL
 * - SP_CONFIG_SUCCESS - in case of success
 */
int GETspKNN(const SPConfig config, SP_CONFIG_MSG* msg);

/*
 * Returns the way to represent the cut method for kd-tree i.e the value
 * of spKDTreeSplitMethod.
 *
 * @param config - the configuration structure
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return valid spTreeSplit value in sucess, NULL otherwise.
 *
 * - SP_CONFIG_INVALID_ARGUMENT - if config == NULL
 * - SP_CONFIG_SUCCESS - in case of success
 */
spTreeSplit* GETspKDTreeSplitMethod(const SPConfig config, SP_CONFIG_MSG* msg);

/*
 * Returns the active level of the logger. i.e the value
 * of spLoggerLevel.
 *
 * @param config - the configuration structure
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return positive integer in success, negative integer otherwise.
 *
 * - SP_CONFIG_INVALID_ARGUMENT - if config == NULL
 * - SP_CONFIG_SUCCESS - in case of success
 */

int GETspLoggerLevel(const SPConfig config, SP_CONFIG_MSG* msg);

/*
 * Returns the logger's filename. i.e the value
 * of spLoggerFilename.
 *
 * @param config - the configuration structure
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return valid char* in success,MULL otherwise.
 *
 * - SP_CONFIG_INVALID_ARGUMENT - if config == NULL
 * - SP_CONFIG_SUCCESS - in case of success
 */
char* GETspLoggerFilename(const SPConfig config, SP_CONFIG_MSG* msg);

/*
 * Returns true if spNotDefined is true, false o.w.
 * @param config - the configuration structure
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return true if spNotDefined = true, false otherwise.
 * - SP_CONFIG_INVALID_ARGUMENT - if config == NULL
 * - SP_CONFIG_SUCCESS - in case of success
 */
bool GETsNotDefined(const SPConfig config, SP_CONFIG_MSG* msg);

/*
 * Returns the case num reffering to an undefined not-default variable. i.e the value
 * of spCaseNum.
 *
 * @param config - the configuration structure
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return positive integer in success, negative integer otherwise.
 *
 * - SP_CONFIG_INVALID_ARGUMENT - if config == NULL
 * - SP_CONFIG_SUCCESS - in case of success
 */
int GETspCaseNum(const SPConfig config, SP_CONFIG_MSG* msg);

/*
 * Returns the state of the first error. i.e the value
 * of spFirstError.
 *
 * @param config - the configuration structure
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return positive integer in success, negative integer otherwise.
 *
 * - SP_CONFIG_INVALID_ARGUMENT - if config == NULL
 * - SP_CONFIG_SUCCESS - in case of success
 */
int GETspFirstError(const SPConfig config, SP_CONFIG_MSG* msg);

/**
 * Returns the dimension of the PCA. i.e the value of spPCADimension.
 *
 * @param config - the configuration structure
 * @assert msg != NULL
 * @param msg - pointer in which the msg returned by the function is stored
 * @return positive integer in success, negative integer otherwise.
 *
 * - SP_CONFIG_INVALID_ARGUMENT - if config == NULL
 * - SP_CONFIG_SUCCESS - in case of success
 */
int spConfigGetPCADim(const SPConfig config, SP_CONFIG_MSG* msg);

/**
 * Given an index 'index' the function stores in imagePath the full path of the
 * ith image.
 *
 * For example:
 * Given that the value of:
 *  spImagesDirectory = "./images/"
 *  spImagesPrefix = "img"
 *  spImagesSuffix = ".png"
 *  spNumOfImages = 17
 *  index = 10
 *x`
 * The functions stores "./images/img10.png" to the address given by imagePath.
 * Thus the address given by imagePath must contain enough space to
 * store the resulting string.
 *
 * @param imagePath - an address to store the result in, it must contain enough space.
 * @param config - the configuration structure
 * @param index - the index of the image.
 *
 * @return
 * - SP_CONFIG_INVALID_ARGUMENT - if imagePath == NULL or config == NULL
 * - SP_CONFIG_INDEX_OUT_OF_RANGE - if index >= spNumOfImages
 * - 	SP_CONFIG_MISSING_SPACE if imagePath doesnt contain enough space
 *  * - SP_CONFIG_SUCCESS - in case of success
 */
SP_CONFIG_MSG spConfigGetImagePath(char* imagePath, const SPConfig config,
		int index);

/**
 * Given an index 'index' the function stores in FeatsPath the full path of the
 * ith feat.
 *
 * For example:
 * Given that the value of:
 *  spImagesDirectory = "./images/"
 *  spImagesPrefix = "img"
 *  spImagesSuffix = ".png"
 *  spNumOfImages = 17
 *  index = 10
 *x`
 * The functions stores "./images/img10.feat" to the address given by FeatsPath.
 * Thus the address given by FeatsPath must contain enough space to
 * store the resulting string.
 *
 * @param FeatsPath - an address to store the result in, it must contain enough space.
 * @param config - the configuration structure
 * @param index - the index of the image.
 *
 * @return
 * - SP_CONFIG_INVALID_ARGUMENT - if FeatsPath == NULL or config == NULL
 * - SP_CONFIG_INDEX_OUT_OF_RANGE - if index >= spNumOfImages
 * - 	SP_CONFIG_MISSING_SPACE if FeatsPath doesnt contain enough space
 *  * - SP_CONFIG_SUCCESS - in case of success
 */

SP_CONFIG_MSG spConfigGetFeatsPath(char* featsPath, const SPConfig config,int index);

/**
 * The function stores in pcaPath the full path of the pca file.
 * For example given the values of:
 *  spImagesDirectory = "./images/"
 *  spPcaFilename = "pca.yml"
 *
 * The functions stores "./images/pca.yml" to the address given by pcaPath.
 * Thus the address given by pcaPath must contain enough space to
 * store the resulting string.
 *
 * @param imagePath - an address to store the result in, it must contain enough space.
 * @param config - the configuration structure
 * @return
 *  - SP_CONFIG_INVALID_ARGUMENT - if imagePath == NULL or config == NULL
 *  - SP_CONFIG_SUCCESS - in case of success
 */


SP_CONFIG_MSG spConfigGetPCAPath(char* pcaPath, const SPConfig config);

/**
 * Frees all memory resources associate with config. 
 * If config == NULL nothig is done.
 */
void spConfigDestroy(SPConfig config);

/*
 *Sets the value of spImagesDirectory.
 * @param conf - the configuration structure
 * @param dir - the dir of the images
 * @pre conf is a valid SPConfig structure.
 * @pre dir is a valid char* by all constrains
 * @post conf->spImagesDirectory=dir
 */
void SETspImagesDirectory(SPConfig conf,char* dir);

/*
 *Sets the value of spImagesPrefix.
 * @param conf - the configuration structure
 * @param prefix - the prefix of the images
 * @pre conf is a valid SPConfig structure.
 * @pre prefix is a valid char* by all constrains
 * @post conf->spImagesPrefix=prefix
 */
void SETspImagesPrefix(SPConfig conf, char* prefix);

/*
 *Sets the value of spImagesSuffix.
 * @param conf - the configuration structure
 * @param suff - the suffix of the images
 * @pre conf is a valid SPConfig structure.
 * @pre suff is a valid char* by all constrains
 * @post conf->spImagesSuffix=suf
 */
void SETspImagesSuffix(SPConfig conf, char* suff);

/*
 *Sets the value of spNumOfImages.
 * @param conf - the configuration structure
 * @param num - the number of the images
 * @pre conf is a valid SPConfig structure.
 * @pre num is a valid int by all constrains
 * @post conf->spNumOfImages=num
 */
void SETspNumOfImages(SPConfig conf, int num);

/*
 *Sets the value of spPCADimension.
 * @param conf - the configuration structure
 * @param dim - the dimension of the PCA
 * @pre conf is a valid SPConfig structure.
 * @pre dim is a valid int by all constrains
 * @post conf->spPCADimension=dim
 */
void SETspPCADimension(SPConfig conf, int dim);

/*
 *Sets the value of spPCAFilename.
 * @param conf - the configuration structure
 * @param file - the filename of the PCA
 * @pre conf is a valid SPConfig structure.
 * @pre file is a valid char* by all constrains
 * @post conf->spPCAFilename=file
 */
void SETspPCAFilename(SPConfig conf, char* file);

/*
 *Sets the value of spNumOfFeatures.
 * @param conf - the configuration structure
 * @param num - the numer of features to be extracted.
 * @pre conf is a valid SPConfig structure.
 * @pre num is a valid int by all constrains
 * @post conf->spNumOfFeatures=num
 */
void SETspNumOfFeatures(SPConfig conf, int num);

/*
 *Sets the value of spExtractionMode.
 * @param conf - the configuration structure
 * @param val - the state of Extraction mode - on or off.
 * @pre conf is a valid SPConfig structure.
 * @pre val is a valid boolean by all constrains
 * @post conf->spExtractionMode=val
 */
void SETspExtractionMode(SPConfig conf, bool val);

/*
 *Sets the value of spNumOfSimilarImages.
 * @param conf - the configuration structure
 * @param num - the numer of similar images.
 * @pre conf is a valid SPConfig structure.
 * @pre num is a valid int by all constrains
 * @post conf->spNumOfSimilarImages=num
 */
void SETspNumOfSimilarImages(SPConfig conf, int num);
/*
 *Sets the value of spKDTreeSplitMethod.
 * @param conf - the configuration structure
 * @param val - the method to be used.
 * @pre conf is a valid SPConfig structure.
 * @pre val is a valid spTreeSplit value by all constrains
 * @post conf->spNumOfSimilarImages=val
 */
void SETspKDTreeSplitMethod(SPConfig conf, spTreeSplit val);

/*
 *Sets the value of spKNN.
 * @param conf - the configuration structure
 * @param val - k to be used in the k nearest neighbor search algorithm .
 * @pre conf is a valid SPConfig structure.
 * @pre val is a valid int by all constrains
 * @post conf->spKNN=val
 */
void SETspKNN(SPConfig conf, int val);
/*
 *Sets the value of spMinimalGUI.
 * @param conf - the configuration structure
 * @param val - the state of Minimal GUI- on or off.
 * @pre conf is a valid SPConfig structure.
 * @pre val is a valid boolean by all constrains
 * @post conf->spMinimalGUI=val
 */
void SETspMinimalGUI(SPConfig conf, bool val);

/*
 *Sets the value of spLoggerLevel.
 * @param conf - the configuration structure
 * @param val -the active state of the logger.
 * @pre conf is a valid SPConfig structure.
 * @pre val is a valid int by all constrains
 * @post conf->spLoggerLevel=val
 */
void SETspLoggerLevel(SPConfig conf, int val);

/*
 *Sets the value of spLoggerFilename.
 * @param conf - the configuration structure
 * @param  val - the filename of the logger
 * @pre conf is a valid SPConfig structure.
 * @pre val is a valid char* by all constrains
 * @post conf->spLoggerFilename=val
 */
void SETspLoggerFilename(SPConfig conf, char* val);

/*
 *Sets the value of spNotDefined.
 * @param conf - the configuration structure
 * @param val - 1 or 0
 * @pre conf is a valid SPConfig structure.
 * @pre val is a valid int - 0 or 1
 * @post conf->spNotDefined=val
 */
void SETspNotDefined(SPConfig conf, bool val);

/*
 *Sets the value of spCaseNum.
 * @param conf - the configuration structure
 * @param val - the case of a non-default value undefined
 * @pre conf is a valid SPConfig structure.
 * @pre val is a valid int in {0,1,2,3,MAX_INT}
 * @post conf->spCaseNum=val
 */
void SETspCaseNum(SPConfig conf,int val);

/*
 *Sets the value of spFirstError.
 * @param conf - the configuration structure
 * @param val - mentions if the first error was already spotted
 * @pre conf is a valid SPConfig structure.
 * @pre val is a valid int in {0,1}
 * @post conf->spFirstError=val
 */
void SETspFirstError(SPConfig conf, int val);
/*
 *Calculates a distinct hash value for each of the system variables.
 * @param str - a string representing one of the system variables
 * @pre str is a valid char*
 * @return an int representing that system variable
 */
int hashit(char *str);

/*
 * @param config - the configuration structure
 * @pre config is not NULL
 * @return true if all non-default fields are defined. false otherwise.
 */

bool spCheckFields(SPConfig config, SP_CONFIG_MSG* msg);

/*
 *Clears all spaces before and after a string.
 *EXample: "   value   "-> "value"
 * @param str - a string to be cleared of spaces
 * @pre str is a valid char*
 * @return the same str without spaces in beginning and end
 */
char* spacesClear(char* str);

/*
 *Determines weather a string meets its constrains
 * @param str - a string to be chcked for spaces in mid-word
 * @pre str is a valid char*
 * @return true if str is valid by constrains, false o.w
 */
bool spacesCheck(char* str);

/*
 *Determines if str represents a valid int in the range [rangeL,rangeR]
 * @param str - a string representing an int
 * @param rangeL - a string to be chcked for spaces in mid-word
 * @param rangeR - a string to be chcked for spaces in mid-word
 * @pre str is a valid char*
 * @pre rangeL and rangeR are valid ints
 * @return true if str is valid by constrains, false o.w
 */
bool intCheck(char* str, int rangeL, int rangeR, SP_CONFIG_MSG* msg);

#endif /* SPCONFIG_H_ */
