#pragma once
#include <stdio.h>
#include <string.h>

/*This file checks the sanity of files. check if file exists or if file is written sucesfuly
* author- Shathish A
*/

/*this function checks if given file exists or not
* arguments- Filename
* return- boolean weather file exists
*/
bool checkIfFileExists(char *fileName)
{
    return access(fileName, F_OK) == 0;
}

/*this function checks if a file is sucessfuly copied to destination
* arguments- source file pointer, destination file pointer
* return- boolean weather file copy is success
*/
bool isFileCopySuccess(FILE *sourceFile, FILE* destinationFile)
{
    if(!sourceFile || !destinationFile)
    {
        printf("\n Invalid files cannot compare \n");
        return false;
    }

    fseek(sourceFile, 0, SEEK_END);
    long sourceFileSize = ftell(sourceFile);

    fseek(sourceFile, 0, SEEK_END);
    long destinationFileSize = ftell(sourceFile);

    printf("source size is %d bytes destnation size is %d bytes\n", sourceFileSize, destinationFileSize);
    return sourceFileSize==destinationFileSize;
}

