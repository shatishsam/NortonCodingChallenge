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

const int FILE_WRITE_FAILED=0; //used to check if file write is success

/*Buffer related constants*/
const unsigned int CACHE_SIZE = 1024; //size of the buffer used while reading input from user.

/*user input related constants*/
const char EXIT_INPUT[] = "exit\n"; //compare this with user input to see if they want to exit.

const char INPUT_ENTER_KEY = '\n';

const enum USER_INPUT {EXIT, WRITE_FILE, READ_FILE, DELETE_FILE, FILE_AS_INPUT, FILE_AUTOMATION_TEST}; //user input to be compared in switch case

/*Automation test realted constants*/
const enum AUTOMATION_FILE_TYPE {TEXT, PDF, IMAGE, BINARY, ZIP, VIDEO}; //file types

const char AUTOMATION_FILE_WORDDOCUMENT_SOURCE[] = "TestCases\\Source\\sample.docx"; //text source

const char AUTOMATION_FILE_WORDDOCUMENT_DESTINATION[] = "TestCases\\Destination\\sample.docx"; //text destination

const char AUTOMATION_FILE_PDF_SOURCE[] = "TestCases\\Source\\sample.pdf"; //pdf source

const char AUTOMATION_FILE_PDF_DESTINATION[] = "TestCases\\Destination\\sample.pdf"; //pdf destination

const char AUTOMATION_FILE_IMAGE_SOURCE[] = "TestCases\\Source\\sample.png"; //image source

const char AUTOMATION_FILE_IMAGE_DESTINATION[] = "TestCases\\Destination\\sample.png"; //image destination

const char AUTOMATION_FILE_BINARY_SOURCE[] = "TestCases\\Source\\sample.bin"; //binary source

const char AUTOMATION_FILE_BINARY_DESTINATION[] = "TestCases\\Destination\\sample.bin"; //binary destination

const char AUTOMATION_FILE_ZIP_SOURCE[] = "TestCases\\Source\\sample.zip"; //zip source

const char AUTOMATION_FILE_ZIP_DESTINATION[] = "TestCases\\Destination\\sample.zip"; //zip destination

const char AUTOMATION_FILE_VIDEO_SOURCE[] = "TestCases\\Source\\sample.mp4"; //video source

const char AUTOMATION_FILE_VIDEO_DESTINATION[] = "TestCases\\Destination\\sample.mp4"; //video destination

const char AUTOMATION_PIPE_7ZIP_COMMAND[] = "TestCases\\Util\\7z e TestCases\\Source\\sample.zip -so| ..\\Application.exe"; //provide binary data to application using 7zip and PIPE

const char AUTOMATION_PIPE_IMAGE_BINARY_COMMAND[]= "TYPE TestCases\\Source\\sample.png | ..\\Application.exe"; //provide image binary content as input using PIPE

const char AUTOMATION_PIPE_TEXT_COMMAND[] = "echo Hello World | ..\\Application.exe"; //provide text as input to application using PIPE