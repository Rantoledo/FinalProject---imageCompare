/** SPHelpFunctions will contain several functions
 *  that will be used in main.cpp.
 */


/**
 *  * Will be called from 'checkArgs' function.
 * Recives msg of type SP_CONFIG_MSG and returns a valid unique int corresponding
 * to the message recieved. the int will then be used in a 'switch' statement
 *
 * @param msg - SP_CONFIG_MSG to be transformed
 * @param defaultCon - weather or not the default config file was used
 * @return a valid int of values 0-7 if msg is indeed a valid SP_CONFIG_MSG; -1 o.w
 *
 */
int hashMsg(SP_CONFIG_MSG* msg,bool defaultCon);

/*
 * Will be called from 'checkArgs' function.
 * Displays relevant error based on SP_CONFIG_MSG recieved, frees relevant resources
 * and exits in case of any errors

 * @param type - valid int of values 0-7
 * @param filename - the config file name
 * @param - msg SP_CONFIG_MSG to be freed in case of errors
 * @pre - type is in the range 0,7. o.w - function exists without printing anything to stdout
 * @return The function doesnt return anything
 */

void RErrorDispaly(int type, char* filename,SP_CONFIG_MSG* msg);

/*
 * Recives spLoggerLevel value and returns corresponding SP_LOGGER_LEVEL

 * @param num - valid int of values 0-3
 * @pre - num is in the range 0,3. o.w - function returns SP_LOGGER_ERROR_LEVEL
 * @return SP_LOGGER_ERROR_LEVEL if num=0; SP_LOGGER_WARNING_ERROR_LEVEL if num =1;
 * 			SP_LOGGER_INFO_WARNING_ERROR_LEVEL if num=2; SP_LOGGER_DEBUG_INFO_WARNING_ERROR_LEVEL if num=3;
 * 			SP_LOGGER_ERROR_LEVEL o.w
 */
SP_LOGGER_LEVEL intToLvl(int num);

/*
 * Functions checks command line arguments recieved from user, and initalized the
 * relevant config file in case they were legit, functions will terminate the program
 * in case of illeagal command-line arguments as defined, or in case of illegal config file.

 * @param argc - command line int representing the number of aruments recieved by user
 * @param argv - an array of strings representing the filename and arguments recieved by user
 * @param defaultCon - a pointer to a boolean. will be set true if no filename was recieved by user
 * @param filename - the filename that will be created. "spcbir.config" in case no filename is recieved by user
 * @param msg - SP_CONFIG_MSG representing the state of config.
 * @param configFile - a pointer to the configFile that will be created in case of success
 * @return the function returns nothing, but the pointer configFile, will point to a
 * valid config-file in case of success. in any case of errors program will be terminated
 * displaying the relevant information to the user
 */

void checkArgs(int argc,char** argv,bool* defaultCon,char* filename,SP_CONFIG_MSG* msg,SPConfig* configFile);

