#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include "SPConfig.h"
#define DELIM "="
#define MAXBUFF 1024
#define COMMENT '#'
#define BLANK " "
#define BLANK1 ' '
#define MODE "r"
int isspace(int c);
int isdigit(int c);
int lineError;
int numOL;
struct sp_config_t{
	char* spImagesDirectory;
	char* spImagesPrefix;
	char* spImagesSuffix;
	int spNumOfImages;
	int spPCADimension;
	char* spPCAFilename;
	int spNumOfFeatures;
	bool spExtractionMode;
	int spNumOfSimilarImages;
	spTreeSplit* spKDTreeSplitMethod;
	int spKNN;
	bool spMinimalGUI;
	int spLoggerLevel;
	char* spLoggerFilename;
	bool spNotDefined;//true if a non-default value is undefined
	int spCaseNum;//represent the first non-default system variable undefined
	int spFirstError;// will be 1 if first error was discovered and 0 o.w
};
bool spConfigIsExtractionMode(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(msg);
	if (config==NULL){
		*msg=SP_CONFIG_INVALID_ARGUMENT;
		return false;
	}
	*msg=SP_CONFIG_SUCCESS;
	return config->spExtractionMode;
}
bool spConfigMinimalGui(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(msg);
	if (config==NULL){
		*msg=SP_CONFIG_INVALID_ARGUMENT;
		return false;
	}
	*msg=SP_CONFIG_SUCCESS;
	return config->spMinimalGUI;
}
int spConfigGetNumOfImages(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(msg);
	if (config==NULL){
		*msg=SP_CONFIG_INVALID_ARGUMENT;
		return -1;
	}
	*msg=SP_CONFIG_SUCCESS;
	return config->spNumOfImages;
}
int spConfigGetNumOfFeatures(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(msg);
	if (config==NULL){
		*msg=SP_CONFIG_INVALID_ARGUMENT;
		return -1;
	}
	*msg=SP_CONFIG_SUCCESS;
	return config->spNumOfFeatures;
}
int spConfigGetPCADim(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(msg);
	if (config==NULL){
		*msg=SP_CONFIG_INVALID_ARGUMENT;
		return -1;
	}
	*msg=SP_CONFIG_SUCCESS;
	return config->spPCADimension;
}
char* GETspImagesDirectory(SPConfig config, SP_CONFIG_MSG* msg){
	assert(msg);
	if (config==NULL){
		*msg=SP_CONFIG_INVALID_ARGUMENT;
		return NULL;
	}
	*msg=SP_CONFIG_SUCCESS;
	return config->spImagesDirectory;
}
char* GETspImagesPrefix(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(msg);
	if (config==NULL){
		*msg=SP_CONFIG_INVALID_ARGUMENT;
		return NULL;
	}
	*msg=SP_CONFIG_SUCCESS;
	return config->spImagesPrefix;
}
char* GETspImagesSuffix(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(msg);
	if (config==NULL){
		*msg=SP_CONFIG_INVALID_ARGUMENT;
		return NULL;
	}
	*msg=SP_CONFIG_SUCCESS;
	return config->spImagesSuffix;
}
char* GETspPCAFilename(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(msg);
	if (config==NULL){
		*msg=SP_CONFIG_INVALID_ARGUMENT;
		return NULL;
	}
	*msg=SP_CONFIG_SUCCESS;
	return config->spPCAFilename;
}
int GETspNumOfSimilarImages(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(msg);
	if (config==NULL){
		*msg=SP_CONFIG_INVALID_ARGUMENT;
		return -1;
	}
	*msg=SP_CONFIG_SUCCESS;
	return config->spNumOfSimilarImages;
}
spTreeSplit* GETspKDTreeSplitMethod(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(msg);
	if (config==NULL){
		*msg=SP_CONFIG_INVALID_ARGUMENT;
		return NULL;
	}
	*msg=SP_CONFIG_SUCCESS;
	return config->spKDTreeSplitMethod;
}
int GETspKNN(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(msg);
	if (config==NULL){
		*msg=SP_CONFIG_INVALID_ARGUMENT;
		return -1;
	}
	*msg=SP_CONFIG_SUCCESS;
	return config->spKNN;
}
int GETspLoggerLevel(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(msg);
	if (config==NULL){
		*msg=SP_CONFIG_INVALID_ARGUMENT;
		return -1;
	}
	*msg=SP_CONFIG_SUCCESS;
	return config->spLoggerLevel;
}
char* GETspLoggerFilename(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(msg);
	if (config==NULL){
		*msg=SP_CONFIG_INVALID_ARGUMENT;
		return NULL;
	}
	*msg=SP_CONFIG_SUCCESS;
	return config->spLoggerFilename;
}
bool GETsNotDefined(const SPConfig config, SP_CONFIG_MSG* msg){
	if (config==NULL){
		*msg=SP_CONFIG_INVALID_ARGUMENT;
		return false;
	}
	*msg=SP_CONFIG_SUCCESS;
	return config->spNotDefined;
}
int GETspCaseNum(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(msg);
	if (config==NULL){
		*msg=SP_CONFIG_INVALID_ARGUMENT;
		return -1;
	}
	*msg=SP_CONFIG_SUCCESS;
	return config->spCaseNum;
}
int GETspFirstError(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(msg);
	if (config==NULL){
		*msg=SP_CONFIG_INVALID_ARGUMENT;
		return -1;
	}
	*msg=SP_CONFIG_SUCCESS;
	return config->spFirstError;
}
void SETspImagesDirectory(SPConfig conf,char* dir){
	strcpy(conf->spImagesDirectory,dir);
}
void SETspImagesPrefix(SPConfig conf, char* prefix){
	strcpy(conf->spImagesPrefix,prefix);
}
void SETspImagesSuffix(SPConfig conf, char* suff){
	strcpy(conf->spImagesSuffix,suff);
}
void SETspNumOfImages(SPConfig conf, int num){
	conf->spNumOfImages=num;
}
void SETspPCADimension(SPConfig conf, int dim){
	conf->spPCADimension=dim;
}
void SETspPCAFilename(SPConfig conf, char* file){
	strcpy(conf->spPCAFilename,file);
}
void SETspNumOfFeatures(SPConfig conf, int num){
	conf->spNumOfFeatures=num;
}
void SETspExtractionMode(SPConfig conf, bool val){
	conf->spExtractionMode=val;
}
void SETspNumOfSimilarImages(SPConfig conf, int num){
	conf->spNumOfSimilarImages=num;
}
void SETspKDTreeSplitMethod(SPConfig conf, spTreeSplit val){
	*conf->spKDTreeSplitMethod=val;
}
void SETspKNN(SPConfig conf, int val){
	conf->spKNN=val;
}
void SETspMinimalGUI(SPConfig conf, bool val){
	conf->spMinimalGUI=val;
}
void SETspLoggerLevel(SPConfig conf, int val){
	conf->spLoggerLevel=val;
}
void SETspLoggerFilename(SPConfig conf, char* val){
	strcpy(conf->spLoggerFilename,val);
}
void SETspNotDefined(SPConfig conf, bool val){
	conf->spNotDefined=val;
}
void SETspCaseNum(SPConfig conf,int val){
	conf->spCaseNum=val;
}
void SETspFirstError(SPConfig conf, int val){
	conf->spFirstError=val;
}

bool spCheckFields(SPConfig config,SP_CONFIG_MSG* msg){
	SP_CONFIG_MSG* msg2=(SP_CONFIG_MSG*) malloc(sizeof(SP_CONFIG_MSG));
	char* dir=GETspImagesDirectory(config,msg2);
	char* prefix=GETspImagesPrefix(config,msg2);
	char* suffix=GETspImagesSuffix(config,msg2);
	int numOI=spConfigGetNumOfImages(config,msg2);
	if(((strcmp(dir,""))==0)||((strcmp(dir," "))==0)){
		free(msg2);
		*msg=SP_CONFIG_MISSING_DIR;
		SETspCaseNum(config,0);
		return false;
	}
	if(((strcmp(prefix,""))==0)||((strcmp(prefix," "))==0)){
		free(msg2);
		*msg=SP_CONFIG_MISSING_PREFIX;
		SETspCaseNum(config,1);
		return false;
	}
	if(((strcmp(suffix,""))==0)||((strcmp(suffix," "))==0)){
		free(msg2);
		*msg=SP_CONFIG_MISSING_SUFFIX;
		SETspCaseNum(config,2);
		return false;
	}
	if(numOI==0){
		*msg=SP_CONFIG_MISSING_NUM_IMAGES;
		free(msg2);
		SETspCaseNum(config,3);
		return false;
	}
	free(msg2);
	return true;
}

int hashit(char *str){
	if((strcmp(str,"spImagesDirectory"))==0){
		return 0;
	}
	else if((strcmp(str,"spImagesPrefix"))==0){
		return 1;
	}
	else if((strcmp(str,"spImagesSuffix"))==0){
		return 2;
	}
	else if((strcmp(str,"spNumOfImages"))==0){
		return 3;
	}
	else if((strcmp(str,"spPCADimension"))==0){
		return 4;
	}
	else if((strcmp(str,"spPCAFilename"))==0){
		return 5;
	}
	else if((strcmp(str,"spNumOfFeatures"))==0){
		return 6;
	}
	else if((strcmp(str,"spExtractionMode"))==0){
		return 7;
	}
	else if((strcmp(str,"spNumOfSimilarImages"))==0){
		return 8;
	}
	else if((strcmp(str,"spKDTreeSplitMethod"))==0){
		return 9;
	}
	else if((strcmp(str,"spKNN"))==0){
		return 10;
	}
	else if((strcmp(str,"spMinimalGUI"))==0){
		return 11;
	}
	else if((strcmp(str,"spLoggerLevel"))==0){
		return 12;
	}
	else if((strcmp(str,"spLoggerFilename"))==0){
		return 13;
	}
	else {
		return 14;
	}
}

char* spacesClear(char* str){//clears legit spaces
	int len = strlen(str);
	int i=0,j=0,maxlen=0;
	char* newstring=(char*) malloc(MAXBUFF);
	if (len > 0 && str[len-1] == '\n'){
	    str[len-1] = 0;}
	maxlen=strlen(str);
	if (maxlen==0){
		str[0]=' ';
		free(newstring);
		return str;
	}
	while((isspace(str[i]))&&(i<maxlen)){
		i++;
	}
	j=maxlen-1;
	while((isspace(str[j]))&&(j>i)){
			str[j]='\0';
			j--;
		}
	memset(newstring,0,MAXBUFF);
	if (i<maxlen){
		memcpy(newstring,str+i,maxlen-i);
	}
	else{//the empty string;
		newstring[0]=' ';
	}
	free(str);
	return newstring;
}
bool spacesCheck(char* str){//checks config inputs for spaces
	int i=0;
	int charlen = strlen(str);
	for(i=0; i< charlen; i++){
		if (isspace(str[i])){
			return false;
		}
	}
	return true;
}
bool intCheck(char* str, int rangeL, int rangeR, SP_CONFIG_MSG* msg){//checks config inputs for spaces
	int i=0,check=0;
	int maxlen=strlen(str);
	if (!spacesCheck(str)){
		*msg=SP_CONFIG_INVALID_LINE;
		return false;
	}

	for (i=0; i<maxlen;i++){
		if(!isdigit(str[i])){
			*msg=SP_CONFIG_INVALID_INTEGER;
			return false;
		}
	}
	check = atoi(str);
	if (check<=0){
		*msg=SP_CONFIG_INVALID_INTEGER;
	}
	if ((check<=rangeR)&(check>=rangeL)){
		return true;
	}
	*msg=SP_CONFIG_INDEX_OUT_OF_RANGE;
	return false;
}
void spConfigDestroy(SPConfig config){
	free(config->spImagesSuffix);
	free(config->spImagesPrefix);
	free(config->spKDTreeSplitMethod);
	free(config->spLoggerFilename);
	free(config->spPCAFilename);
	free(config->spImagesDirectory);
	free(config);
}
SPConfig initConfig(SPConfig config){
	if (config==NULL){
		return NULL;
	}
	config->spImagesDirectory=(char*) malloc(MAXBUFF);
	if (config->spImagesDirectory==NULL){
		spConfigDestroy(config);
		return NULL;
	}
	memset(config->spImagesDirectory,0,MAXBUFF);
	config->spImagesPrefix=(char*) malloc(MAXBUFF);
	if (config->spImagesPrefix==NULL){
		spConfigDestroy(config);
		return NULL;
	}
	memset(config->spImagesPrefix,0,MAXBUFF);
	config->spImagesSuffix=(char*) malloc(MAXBUFF);
	if (config->spImagesSuffix==NULL){
		spConfigDestroy(config);
		return NULL;
	}
	memset(config->spImagesSuffix,0,MAXBUFF);

	config->spNumOfImages=0;
	config->spPCADimension=20;
	config->spPCAFilename=(char*) malloc(MAXBUFF);
	if (config->spPCAFilename==NULL){
		spConfigDestroy(config);
		return NULL;
	}
	*config->spPCAFilename=*"pca.yml";
	config->spNumOfFeatures=100;
	config->spExtractionMode=true;
	config->spNumOfSimilarImages=1;
	config->spKDTreeSplitMethod=(spTreeSplit*) malloc(sizeof(*config->spKDTreeSplitMethod));
	if (config->spKDTreeSplitMethod==NULL){
		spConfigDestroy(config);
		return NULL;
	}
	*config->spKDTreeSplitMethod=MAX_SPREAD;
	config->spKNN=1;
	config->spMinimalGUI=false;
	config->spLoggerLevel=3;
	config->spLoggerFilename=(char*) malloc(MAXBUFF);
	if (config->spLoggerFilename==NULL){
		spConfigDestroy(config);
		return NULL;
	}
	*config->spLoggerFilename=*"stdout";
	config->spNotDefined=false;
	config->spCaseNum=INT_MAX;
	config->spFirstError=0;
	return config;
}
SPConfig spConfigCreate(const char* filename, SP_CONFIG_MSG* msg){
	SPConfig configDS = (SPConfig) malloc(sizeof(*configDS));
	initConfig(configDS);
	if (configDS==NULL){
		*msg=SP_CONFIG_ALLOC_FAIL;
		return NULL;
	}
	FILE *configFile = fopen(filename, MODE);
	if (configFile==NULL){
		*msg=SP_CONFIG_CANNOT_OPEN_FILE;
		spConfigDestroy(configDS);
		return NULL;
	}
	int hashedline;//will be used to store the number fitting the system variable
	char* lineRead=(char*) malloc(MAXBUFF);//will store the line read from config file
	if (lineRead==NULL){
		*msg=SP_CONFIG_ALLOC_FAIL;
		spConfigDestroy(configDS);
		fclose(configFile);
		return NULL;
	}
	char* newline=(char*) malloc(MAXBUFF);
	if (newline==NULL){
		*msg=SP_CONFIG_ALLOC_FAIL;
		spConfigDestroy(configDS);
		free(lineRead);
		fclose(configFile);
		return NULL;
	}
	char* newline1=NULL;
	int lineCounter=0; //will be usesd to specify error's line
	SP_CONFIG_MSG *msg2 = (SP_CONFIG_MSG*) malloc(sizeof(SP_CONFIG_MSG));
	if (msg2==NULL){
		*msg=SP_CONFIG_ALLOC_FAIL;
		spConfigDestroy(configDS);
		free(lineRead);
		free(newline);
		fclose(configFile);
		return NULL;
	}
	while (fgets(lineRead, MAXBUFF, configFile)!=NULL){ //comment might be over 1024
		newline1=NULL;
		lineCounter++;
		newline1=strtok(lineRead,DELIM);//seperate var name from var value
		memset(newline,0,MAXBUFF);
		memcpy(newline,newline1,strlen(newline1));
			if (newline!=NULL){
				newline=spacesClear(newline);//clear spaces from begining and end of word
				if ((newline[0]!=COMMENT)&&
						(*newline!=BLANK1)){ //discards comments or empty lines
					hashedline=hashit(newline);//hash to use switch
					switch(hashedline){
						case 0: //"spImagesDirectory"
							newline1=strtok(NULL,DELIM);
							if (newline1==NULL){
								newline1=" ";
							}
							memset(newline,0,MAXBUFF);
							memcpy(newline,newline1,strlen(newline1));
							newline=spacesClear(newline);
							if (newline[0]!=BLANK1){//if it has a val
									if (spacesCheck(newline)){//if the val is legit
										SETspImagesDirectory(configDS,newline);
							}
									else{//"Constraint not met"
										if (GETspFirstError(configDS,msg2)==0){
											*msg=SP_CONFIG_INVALID_LINE;
											lineError=lineCounter;
											spConfigDestroy(configDS);
											fclose(configFile);
											free(lineRead);
											free(newline);
											free(msg2);
											return NULL;
									}}}
							else{//Dir not set
								if (0<GETspCaseNum(configDS,msg2)){
									SETspNotDefined(configDS, true);
									SETspCaseNum(configDS, 0);
								}
								if (GETspFirstError(configDS,msg2)==0){//if its the first error
									SETspFirstError(configDS,1);
									*msg=SP_CONFIG_MISSING_DIR;
								}
							}
							break;
						case 2: //"spImageSuffix"
							newline1=strtok(NULL,DELIM);
							if (newline1==NULL){
								newline1=" ";
							}
							memset(newline,0,MAXBUFF);
							memcpy(newline,newline1,strlen(newline1));
							newline=spacesClear(newline);
							if (newline[0]!=BLANK1){
									if (spacesCheck(newline)){
										if ((strcmp(newline,".jpg")==0)||(strcmp(newline,".png")==0)||(strcmp(newline,".bmp")==0)||(strcmp(newline,".gif")==0)){
												SETspImagesSuffix(configDS,newline);
										}
										else{//incorrect format for suffix
											if (GETspFirstError(configDS,msg2)==0){//if its the first error
												*msg=SP_CONFIG_INVALID_SUFFIX;//check why his mother is such a mother fucking ass hole slut
												lineError=lineCounter;
												spConfigDestroy(configDS);
												fclose(configFile);
												free(lineRead);
												free(newline);
												free(msg2);
												return NULL;
										}
									}}
									else{//constraint not met
										if (GETspFirstError(configDS,msg2)==0){
											*msg=SP_CONFIG_INVALID_LINE;
											lineError=lineCounter;
											spConfigDestroy(configDS);
											fclose(configFile);
											free(lineRead);
											free(newline);
											free(msg2);
											return NULL;									}
							}}
							else{//Missing Suffix
									if (2<GETspCaseNum(configDS,msg2)){
										SETspNotDefined(configDS, true);
										SETspCaseNum(configDS, 2);
										}
									if (GETspFirstError(configDS,msg2)==0){//if its the first error
										SETspFirstError(configDS,1);
										*msg=SP_CONFIG_MISSING_SUFFIX;
										}
									}
							break;

						case 1: //"spImagePrefix"
							newline1=strtok(NULL,DELIM);
							if (newline1==NULL){
								newline1=" ";
							}
							memset(newline,0,MAXBUFF);
							memcpy(newline,newline1,strlen(newline1));
							newline=spacesClear(newline);
							if (newline[0]!=BLANK1){
									if (spacesCheck(newline)){
										SETspImagesPrefix(configDS,newline);
									}

									else{//constraint not met
										if (GETspFirstError(configDS,msg2)==0){
										*msg=SP_CONFIG_INVALID_LINE;
										lineError=lineCounter;
										spConfigDestroy(configDS);
										fclose(configFile);
										free(lineRead);
										free(newline);
										free(msg2);
										return NULL;									}
									}}

							else{//Missing prefix
									if (1<GETspCaseNum(configDS,msg2)){
										SETspNotDefined(configDS, true);
										SETspCaseNum(configDS, 1);
										}
									if (GETspFirstError(configDS,msg2)==0){//if its the first error
										SETspFirstError(configDS,1);
										*msg=SP_CONFIG_MISSING_PREFIX;
										}
									}

							break;

						case 3: //"spNumOfImages"
							newline1=strtok(NULL,DELIM);
							if (newline1==NULL){
								newline1=" ";
							}
							memset(newline,0,MAXBUFF);
							memcpy(newline,newline1,strlen(newline1));
							newline=spacesClear(newline);
							if (newline[0]!=BLANK1){
								if (intCheck(newline,1,INT_MAX,msg)){
									SETspNumOfImages(configDS,atoi(newline));

							}
								else{//constraint not met
									*msg=SP_CONFIG_INVALID_LINE;
									if (GETspFirstError(configDS,msg2)==0){
									lineError=lineCounter;
									spConfigDestroy(configDS);
									fclose(configFile);
									free(lineRead);
									free(newline);
									free(msg2);
									return NULL;									}
								}
							}
							else{//Missing numOfImages
									if (3<GETspCaseNum(configDS,msg2)){
										SETspNotDefined(configDS, true);
										SETspCaseNum(configDS, 3);
										}
									if (GETspFirstError(configDS,msg2)==0){//if its the first error
										SETspFirstError(configDS,1);
										*msg=SP_CONFIG_MISSING_NUM_IMAGES;
										}
									}
							break;
						case 4: //"spPCADimension"
							newline1=strtok(NULL,DELIM);
							if (newline1==NULL){
								newline1=" ";
							}
							memset(newline,0,MAXBUFF);
							memcpy(newline,newline1,strlen(newline1));
							newline=spacesClear(newline);
							if (newline[0]!=BLANK1){
								if (intCheck(newline,10,28,msg)){
									SETspPCADimension(configDS,atoi(newline));
							}
								else{//constraint not met
									if (GETspFirstError(configDS,msg2)==0){
										lineError=lineCounter;
										spConfigDestroy(configDS);
										fclose(configFile);
										free(lineRead);
										free(newline);
										free(msg2);
										return NULL;									}
								}
							}
							break;
						case 5: //"spPCAFilename"
							newline1=strtok(NULL,DELIM);
							if (newline1==NULL){
								newline1=" ";
							}
							memset(newline,0,MAXBUFF);
							memcpy(newline,newline1,strlen(newline1));
							newline=spacesClear(newline);
							if (newline[0]!=BLANK1){
								if (spacesCheck(newline)){
								SETspPCAFilename(configDS,newline);
							}
								else{//constraint not met
									if (GETspFirstError(configDS,msg2)==0){
									*msg=SP_CONFIG_INVALID_LINE;
									lineError=lineCounter;
									spConfigDestroy(configDS);
									fclose(configFile);
									free(lineRead);
									free(newline);
									free(msg2);
									return NULL;									}
								}}
							break;
						case 6: //"spNumOfFeatures"
							newline1=strtok(NULL,DELIM);
							if (newline1==NULL){
								newline1=" ";
							}
							memset(newline,0,MAXBUFF);
							memcpy(newline,newline1,strlen(newline1));
							newline=spacesClear(newline);
							if (newline[0]!=BLANK1){
								if (intCheck(newline,1,INT_MAX, msg)){
									SETspNumOfFeatures(configDS,atoi(newline));
							}
								else{//constraint not met
									if (GETspFirstError(configDS,msg2)==0){
									lineError=lineCounter;
									spConfigDestroy(configDS);
									fclose(configFile);
									free(lineRead);
									free(newline);
									free(msg2);
									return NULL;									}
								}}

							break;
						case 7: //"spExtractionMode"
							newline1=strtok(NULL,DELIM);
							if (newline1==NULL){
								newline1=" ";
							}
							memset(newline,0,MAXBUFF);
							memcpy(newline,newline1,strlen(newline1));
							newline=spacesClear(newline);
							if (newline[0]!=BLANK1){
								if (strcmp(newline,"true")==0){
									SETspExtractionMode(configDS,true);

								}
								else if (strcmp(newline,"false")==0){
									SETspExtractionMode(configDS,false);
								}
									else{//constraint not met
										if (GETspFirstError(configDS,msg2)==0){
										*msg=SP_CONFIG_INVALID_BOOL;
										if (!spacesCheck(newline)){
											*msg=SP_CONFIG_INVALID_LINE;
										}
										lineError=lineCounter;
										spConfigDestroy(configDS);
										fclose(configFile);
										free(lineRead);
										free(newline);
										free(msg2);
										return NULL;									}
									}}
							break;
						case 8: //"spNumOfSimilarImages"
							newline1=strtok(NULL,DELIM);
							if (newline1==NULL){
								newline1=" ";
							}
							memset(newline,0,MAXBUFF);
							memcpy(newline,newline1,strlen(newline1));
							newline=spacesClear(newline);
							if (newline[0]!=BLANK1){
								if (intCheck(newline,1,INT_MAX,msg)){
								SETspNumOfSimilarImages(configDS,atoi(newline));
							}
								else{//constraint not met
									if (GETspFirstError(configDS,msg2)==0){
									lineError=lineCounter;
									spConfigDestroy(configDS);
									fclose(configFile);
									free(lineRead);
									free(newline);
									free(msg2);
									return NULL;									}
								}}
							break;
						case 9: //"spKDTreeSplitMethod"
							newline1=strtok(NULL,DELIM);
							if (newline1==NULL){
								newline1=" ";
							}
							memset(newline,0,MAXBUFF);
							memcpy(newline,newline1,strlen(newline1));
							newline=spacesClear(newline);
							if (newline[0]!=BLANK1){
								if (strcmp(newline,"RANDOM")==0){
									SETspKDTreeSplitMethod(configDS,RANDOM);
								}
								else if (strcmp(newline,"MAX_SPREAD")==0){
									SETspKDTreeSplitMethod(configDS,MAX_SPREAD);
								}
								else if (strcmp(newline,"INCREMENTAL")==0){
									SETspKDTreeSplitMethod(configDS,INCREMENTAL);
								}
								else{//constraint not met
									if (GETspFirstError(configDS,msg2)==0){
									*msg=SP_CONFIG_INVALID_SPTREESPLIT;
									if (!spacesCheck(newline)){
										*msg=SP_CONFIG_INVALID_LINE;
									}
									lineError=lineCounter;
									spConfigDestroy(configDS);
									fclose(configFile);
									free(lineRead);
									free(newline);
									free(msg2);
									return NULL;									}
								}}
							break;
						case 10: //"spKNN"
							newline1=strtok(NULL,DELIM);
							if (newline1==NULL){
								newline1=" ";
							}
							memset(newline,0,MAXBUFF);
							memcpy(newline,newline1,strlen(newline1));
							newline=spacesClear(newline);
							if (newline[0]!=BLANK1){
								if (intCheck(newline,1,INT_MAX,msg)){
									SETspKNN(configDS,atoi(newline));
							}
								else{//constraint not met
									if (GETspFirstError(configDS,msg2)==0){
									lineError=lineCounter;
									spConfigDestroy(configDS);
									fclose(configFile);
									free(lineRead);
									free(newline);
									free(msg2);
									return NULL;									}
								}}
							break;
						case 11: //"spMinimalGUI"
							newline1=strtok(NULL,DELIM);
							if (newline1==NULL){
								newline1=" ";
							}
							memset(newline,0,MAXBUFF);
							memcpy(newline,newline1,strlen(newline1));
							newline=spacesClear(newline);
							if (newline[0]!=BLANK1){
								if (strcmp(newline,"true")==0){//checking boolean statement
									SETspMinimalGUI(configDS,true);
								}
								else if (strcmp(newline,"false")==0){
									SETspMinimalGUI(configDS,false);
								}
								else{//constraint not met
									if (GETspFirstError(configDS,msg2)==0){
									*msg=SP_CONFIG_INVALID_BOOL;
									if (!spacesCheck(newline)){
										*msg=SP_CONFIG_INVALID_LINE;
									}
									lineError=lineCounter;
									spConfigDestroy(configDS);
									fclose(configFile);
									free(lineRead);
									free(newline);
									free(msg2);
									return NULL;									}
								}}
							break;
						case 12: //"spLoggerLevel"
							newline1=strtok(NULL,DELIM);
							if (newline1==NULL){
								newline1=" ";
							}
							memset(newline,0,MAXBUFF);
							memcpy(newline,newline1,strlen(newline1));
							newline=spacesClear(newline);
							if (newline[0]!=BLANK1){
								if (intCheck(newline,1,4,msg)){
								SETspLoggerLevel(configDS,atoi(newline));
							}
								else{//constraint not met
									if (GETspFirstError(configDS,msg2)==0){
									lineError=lineCounter;
									spConfigDestroy(configDS);
									fclose(configFile);
									free(lineRead);
									free(newline);
									free(msg2);
									return NULL;									}
								}}
							break;
						case 13: //"spLoggerFilename"
							newline1=strtok(NULL,DELIM);
							if (newline1==NULL){
								newline1=" ";
							}
							memset(newline,0,MAXBUFF);
							memcpy(newline,newline1,strlen(newline1));
							newline=spacesClear(newline);
							if (newline[0]!=BLANK1){
								if (spacesCheck(newline)){
									SETspLoggerFilename(configDS,newline);
							}
								else{//constraint not met
									if (GETspFirstError(configDS,msg2)==0){
									*msg=SP_CONFIG_INVALID_LINE;
									lineError=lineCounter;
									spConfigDestroy(configDS);
									fclose(configFile);
									free(lineRead);
									free(newline);
									free(msg2);
									return NULL;									}
								}}
							break;
						case 14: //default
							if (GETspFirstError(configDS,msg2)==0){
							*msg=SP_CONFIG_INVALID_LINE;
							lineError=lineCounter;
							spConfigDestroy(configDS);
							fclose(configFile);
							free(lineRead);
							free(newline);
							free(msg2);
							return NULL;				}
				}
		}
	}}
	numOL=lineCounter;
	if(spCheckFields(configDS,msg)){
		*msg=SP_CONFIG_SUCCESS;
		fclose(configFile);
		free(lineRead);
		free(newline);
		free(msg2);
		return configDS;
	}
		lineError=lineCounter;
		spConfigDestroy(configDS);
		fclose(configFile);
		free(lineRead);
		free(newline);
		free(msg2);
		return NULL;
}

SP_CONFIG_MSG spConfigGetImagePath(char* imagePath, const SPConfig config,int index){
	SP_CONFIG_MSG* msg=(SP_CONFIG_MSG*) malloc(sizeof(SP_CONFIG_MSG));
	int numOI=spConfigGetNumOfImages(config,msg);
	if ((imagePath==NULL)||(config==NULL)){
		free(msg);
		return SP_CONFIG_INVALID_ARGUMENT;
	}
	if (index>=numOI){
		free(msg);
		return SP_CONFIG_INDEX_OUT_OF_RANGE;
	}
	char* imageDir=NULL;
	char* imagePrefix=NULL;
	char* imageSuffix=NULL;
	char* indexc=(char*) malloc(MAXBUFF);
	snprintf(indexc, MAXBUFF,"%d",index);
	imageDir=GETspImagesDirectory(config,msg);
	imagePrefix=GETspImagesPrefix(config,msg);
	imageSuffix=GETspImagesSuffix(config,msg);
	strcpy(imagePath,imageDir);
	strcat(imagePath,imagePrefix);
	strcat(imagePath,indexc);
	strcat(imagePath,imageSuffix);

	free(indexc);
	return SP_CONFIG_SUCCESS;
}

SP_CONFIG_MSG spConfigGetFeatsPath(char* featsPath, const SPConfig config,int index){
	SP_CONFIG_MSG* msg=(SP_CONFIG_MSG*) malloc(sizeof(SP_CONFIG_MSG));
	int numOF=spConfigGetNumOfImages(config,msg);
	if ((featsPath==NULL)||(config==NULL)){
		free(msg);
		return SP_CONFIG_INVALID_ARGUMENT;
	}
	if (index>=numOF){
		free(msg);
		return SP_CONFIG_INDEX_OUT_OF_RANGE;
	}
	char* featDir=NULL;
	char* featPrefix=NULL;
	char* featSuffix=NULL;
	char* indexc=(char*) malloc(MAXBUFF);
	snprintf(indexc, MAXBUFF,"%d",index);
	featDir=GETspImagesDirectory(config,msg);
	featPrefix=GETspImagesPrefix(config,msg);
	featSuffix=".feats";
	strcpy(featsPath,featDir);
	strcat(featsPath,featPrefix);
	strcat(featsPath,indexc);
	strcat(featsPath,featSuffix);

	free(indexc);
	return SP_CONFIG_SUCCESS;
}

SP_CONFIG_MSG spConfigGetPCAPath(char* pcaPath, const SPConfig config){
	SP_CONFIG_MSG* msg=(SP_CONFIG_MSG*) malloc(sizeof(SP_CONFIG_MSG));
	if ((pcaPath==NULL)||(config==NULL)){
		free(msg);
		return SP_CONFIG_INVALID_ARGUMENT;
	}
	char* imageDir=NULL;
	char* PCAname=NULL;
	imageDir=GETspImagesDirectory(config,msg);
	PCAname=GETspPCAFilename(config,msg);
	strcpy(pcaPath,imageDir);
	strcat(pcaPath,PCAname);
	free(msg);

	return SP_CONFIG_SUCCESS;
}
