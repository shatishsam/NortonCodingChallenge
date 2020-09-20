#include <stdlib.h>

/*This file contains all the required constants for the application 
* author- Shathish A
*/

/*File related constants*/
const enum FILE_STATE{UNOPENED, OPENED, CLOSED}; //file state

const enum FILE_TYPE{READ_TYPE, WRITE_TYPE}; //type of file operation

const char FILE_READ_TYPE[]="r"; //read type

const char FILE_WRITE_TYPE[]="w"; //write type. this creates file if doesnot exists

/*Buffer related constants*/
const unsigned int CACHE_SIZE = 1024; //size of the buffer used while reading input from user.

/*user input related constants*/
const char EXIT_INPUT[]="exit\n"; //compare this with user input to see if they want to exit.

const enum USER_INPUT {EXIT, WRITE_FILE, READ_FILE, DELETE_FILE}; //user input to be compared in switch case