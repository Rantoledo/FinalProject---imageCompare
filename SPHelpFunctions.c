#include "SPConfig.h"
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <stdarg.h>
#include "SPConfig.h"
#include "SPPoint.h"
#include "SPHelpFunctions.h"
#define MAXBUFF 1024
#define DEFAULT "spcbir.config"

int hashMsg(SP_CONFIG_MSG* msg,bool defaultCon){

	if (*msg==SP_CONFIG_SUCCESS){
		return 0;
	}
	if (*msg==SP_CONFIG_CANNOT_OPEN_FILE){
		if (defaultCon){
			return 7;
		}
		else{
			return 8;}}
	if (*msg==SP_CONFIG_INVALID_LINE){
		return 1;
	}
	if ((*msg==SP_CONFIG_INDEX_OUT_OF_RANGE)||(*msg=SP_CONFIG_INVALID_INTEGER)||
			(*msg==SP_CONFIG_INVALID_BOOL)||(*msg==SP_CONFIG_INVALID_SUFFIX)||
			(*msg==SP_CONFIG_INVALID_SPTREESPLIT)){
		return 2;
	}
	if (*msg==SP_CONFIG_MISSING_DIR){
		return 3;
	}
	if (*msg==SP_CONFIG_MISSING_PREFIX){
		return 4;
	}
	if (*msg==SP_CONFIG_MISSING_SUFFIX){
		return 5;
	}
	if (*msg==SP_CONFIG_MISSING_NUM_IMAGES){
		return 6;
	}
	return -1;
	}


void checkArgs(int argc,char** argv,bool* defaultCon,char* filename,SP_CONFIG_MSG* msg,SPConfig* configFile){
	int caseNum=0;
	if (argc>1){
		if (strcmp(argv[1],"-c")==0){
			if (argc>2){
				filename=argv[2];
			}
			else{
				printf("Invalid command line: use -c <config_filename>");
				exit(0);
			}
		}
		else{
			printf("Invalid command line: use -c <config_filename>");
			exit(0);
	}}
	else{
		*defaultCon=true;
		filename=(char*) DEFAULT;
	}
	*configFile=spConfigCreate(filename,msg);
	caseNum=hashMsg(msg,defaultCon);
	RErrorDispaly(caseNum,filename,msg);

}

void RErrorDispaly(int type, char* filename,SP_CONFIG_MSG* msg){
	switch (type){
			case 0:
				return;
			case 1:
				printf("File: %s\n", filename);
				printf("Line: %d\n", lineError);
				printf("Message: Invalid configuration line\n");
				break;
			case 2:
				printf("File: %s\n", filename);
				printf("Line: %d\n", lineError);
				printf("Message: Invalid value - constraint not met\n");
				break;
			case 3:
				printf("File: %s\n", filename);
				printf("Line: %d\n", lineError);
				printf("Message: Parameter spImagesDirectory is not set\n");
				break;
			case 4:
				printf("File: %s\n", filename);
				printf("Line: %d\n", lineError);
				printf("Message: Parameter spImagesPrefix is not set\n");
				break;
			case 5:
				printf("File: %s\n", filename);
				printf("Line: %d\n", lineError);
				printf("Message: Parameter spImagesSuffix is not set\n");
				break;
			case 6:
				printf("File: %s\n", filename);
				printf("Line: %d\n", lineError);
				printf("Message: Parameter spNumOfImages is not set\n");
				break;
			case 7:
				printf("The default configuartion file spcbir.config couldn't be open\n");

				break;
			case 8:
				printf("The configuartion file %s couldn't be open\n",filename);
				break;
		}
	free(msg);
	exit(0);
}


SP_LOGGER_LEVEL intToLvl(int num){
	switch(num){
	case 0:
		return SP_LOGGER_ERROR_LEVEL;
	case 1:
		return SP_LOGGER_WARNING_ERROR_LEVEL;
	case 2:
		return SP_LOGGER_INFO_WARNING_ERROR_LEVEL;
	case 3:
		return SP_LOGGER_DEBUG_INFO_WARNING_ERROR_LEVEL;
	}
	return SP_LOGGER_ERROR_LEVEL;
}

