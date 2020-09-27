#include <stdlib.h>

/*This file contains all the required constants for the application 
* author- Shathish A
*/

/*File related constants*/
const enum FILE_STATE{UNOPENED, OPENED, CLOSED}; //file state

const enum FILE_TYPE{READ_TYPE, WRITE_TYPE, READ_BINARY_TYPE, WRITE_BINARY_TYPE}; //type of file operation

const char FILE_READ_TYPE[] = "r"; //read type. only reads file of text format

const char FILE_WRITE_TYPE[] = "w"; //write type only writes file of text format. this creates file if doesnot exists

const char FILE_BINARY_READ_TYPE[] = "rb"; //read binary type. reads binary format files

const char FILE_BINARY_WRITE_TYPE[] = "wb"; //writes binary data to the file.

/*Buffer related constants*/
const unsigned int CACHE_SIZE = 1024; //size of the buffer used while reading input from user.

/*user input related constants*/
const char EXIT_INPUT[] = "exit\n"; //compare this with user input to see if they want to exit.

const char INPUT_ENTER_KEY = '\n';

const enum USER_INPUT {EXIT, WRITE_FILE, READ_FILE, DELETE_FILE, FILE_AS_INPUT, FILE_AUTOMATION_TEST}; //user input to be compared in switch case

/*Automation test realted constants*/
const enum AUTOMATION_FILE_TYPE {TEXT, PDF, IMAGE, BINARY, ZIP, VIDEO}; //file types

const char AUTOMATION_FILE_WORDDOCUMENT_SOURCE[] = "Automation\\TestCases\\Source\\sample.docx"; //text source

const char AUTOMATION_FILE_WORDDOCUMENT_DESTINATION[] = "Automation\\TestCases\\Destination\\sample.docx"; //text destination

const char AUTOMATION_FILE_PDF_SOURCE[] = "Automation\\TestCases\\Source\\sample.pdf"; //pdf source

const char AUTOMATION_FILE_PDF_DESTINATION[] = "Automation\\TestCases\\Destination\\sample.pdf"; //pdf destination

const char AUTOMATION_FILE_IMAGE_SOURCE[] = "Automation\\TestCases\\Source\\sample.png"; //image source

const char AUTOMATION_FILE_IMAGE_DESTINATION[] = "Automation\\TestCases\\Destination\\sample.png"; //image destination

const char AUTOMATION_FILE_BINARY_SOURCE[] = "Automation\\TestCases\\Source\\sample.bin"; //binary source

const char AUTOMATION_FILE_BINARY_DESTINATION[] = "Automation\\TestCases\\Destination\\sample.bin"; //binary destination

const char AUTOMATION_FILE_ZIP_SOURCE[] = "Automation\\TestCases\\Source\\sample.zip"; //zip source

const char AUTOMATION_FILE_ZIP_DESTINATION[] = "Automation\\TestCases\\Destination\\sample.zip"; //zip destination

const char AUTOMATION_FILE_VIDEO_SOURCE[] = "Automation\\TestCases\\Source\\sample.mp4"; //video source

const char AUTOMATION_FILE_VIDEO_DESTINATION[] = "Automation\\TestCases\\Destination\\sample.mp4"; //video destination