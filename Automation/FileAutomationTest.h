#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Util/FileUtil.h"

/*This file contains code to run test automation. takes all types of files write it and makes sure the write is success
* author- Shathish A
*/

struct File *writePtr; //file struct pointer to write content

/*this function takes filename and filetype as input. writes content of source to destination
* arguments- source file name, file type
* return- boolean weather file copy is success
*/
void runAutomationForFile(char* fileName, enum AUTOMATION_FILE_TYPE fileType)
{
    switch(fileType)
    {
        case TEXT:
        {
            initFile(writePtr, AUTOMATION_FILE_WORDDOCUMENT_DESTINATION, WRITE_BINARY_TYPE);
            printf("write file content to %s \n", getFileName(writePtr));
            copyContentsToFile(writePtr, fileName);
            closeFile(writePtr);
            break;
        }
        case PDF:
        {
            initFile(writePtr, AUTOMATION_FILE_PDF_DESTINATION, WRITE_BINARY_TYPE);
            printf("write file content to %s \n", getFileName(writePtr));
            copyContentsToFile(writePtr, fileName);
            closeFile(writePtr);
            break;
        }
        case IMAGE:
        {
            initFile(writePtr, AUTOMATION_FILE_IMAGE_DESTINATION, WRITE_BINARY_TYPE);
            printf("write file content to %s \n", getFileName(writePtr));
            copyContentsToFile(writePtr, fileName);
            closeFile(writePtr);
            break;
        }
        case BINARY:
        {
            initFile(writePtr, AUTOMATION_FILE_BINARY_DESTINATION, WRITE_BINARY_TYPE);
            printf("write file content to %s \n", getFileName(writePtr));
            copyContentsToFile(writePtr, fileName);
            closeFile(writePtr);
            break;
        }
        case ZIP:
        {
            initFile(writePtr, AUTOMATION_FILE_ZIP_DESTINATION, WRITE_BINARY_TYPE);
            printf("write file content to %s \n", getFileName(writePtr));
            copyContentsToFile(writePtr, fileName);
            closeFile(writePtr);
            break;
        }
        case VIDEO:
        {
            initFile(writePtr, AUTOMATION_FILE_VIDEO_DESTINATION, WRITE_BINARY_TYPE);
            printf("write file content to %s \n", getFileName(writePtr));
            copyContentsToFile(writePtr, fileName);
            closeFile(writePtr);
            break;
        }
    }
}

/*this function takes different types of files and tests if the data are sucessfuly written.
* arguments- none
* return- none
*/
void runFileCopyAutomation()
{
    writePtr = malloc(sizeof(struct File));

    printf("\nTesting Word Document file type containing Foreign language \n");
    runAutomationForFile(AUTOMATION_FILE_WORDDOCUMENT_SOURCE, TEXT);
    sleep(2);

    printf("\nTesting PDF file type \n");
    runAutomationForFile(AUTOMATION_FILE_PDF_SOURCE, PDF);
    sleep(2);

    printf("\nTesting IMAGE file type \n");
    runAutomationForFile(AUTOMATION_FILE_IMAGE_SOURCE, IMAGE);
    sleep(2);

    printf("\nTesting BINARY file type \n");
    runAutomationForFile(AUTOMATION_FILE_BINARY_SOURCE, BINARY);
    sleep(2);

    printf("\nTesting ZIP file type \n");
    runAutomationForFile(AUTOMATION_FILE_ZIP_SOURCE, ZIP);
    sleep(2);

    printf("\nTesting VIDEO file type \n");
    runAutomationForFile(AUTOMATION_FILE_VIDEO_SOURCE, VIDEO);
    sleep(2);

    free(writePtr);
}

/*this function runs different commands and pipes various inputs to the application.
* arguments- none
* return- none
*/
void runPipeAutomation()
{
    //unzip compressed file with 7zip and provide it as an input to application
    printf("\nPiping binary input from compressed file using 7zip to Application\n");
    system(AUTOMATION_PIPE_7ZIP_COMMAND);
    sleep(2);

    //provide binary content of an image file to application
    printf("\nPiping Image file as binary content to the application\n");
    system(AUTOMATION_PIPE_IMAGE_BINARY_COMMAND);
    printf("\nRunning file sanity test\n");
    FILE *source = fopen("TestCases\\Source\\sample.png", "rb");
    FILE *destination = fopen("OUT_FILE", "rb");
    isFileCopySuccess(source, destination);
    sleep(2);

    //unzip compressed file with 7zip and provide it as an input to application
    printf("\nPiping text input to application using echo command\n");
    system(AUTOMATION_PIPE_TEXT_COMMAND);
    sleep(2);

    fclose(source);
    fclose(destination);
}