#pragma once
#include <stdio.h> 
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "../SanityChecker/FileSanityChecker.h"
#include "../Constants/Constants.h"

/*This file has the file pointer and realted methods. Exception are handled for files (ie writing into read files, reading unopened files etc) 
* author- Shathish A
*/

//file strucutre containing all the info about the file.
struct File
{
    FILE *file; //file
    char fileName [100]; //file name along with location
    char fileOpenType [5]; //file open type string (r, w, o).
    enum FILE_TYPE fileType;  //file type
    enum FILE_STATE fileState; //file state
};

/*this function returns the file name*/
char* getFileName(struct File *filePtr)
{
    return filePtr->fileName;
}

/*this function returns the file open type*/
char* getFileOpenType(struct File *filePtr)
{
    return filePtr->fileOpenType;
}

/*this function returns the file type*/
enum FILE_TYPE getFileType(struct File *filePtr)
{
    return filePtr->fileType;
}

/*this function gets the file state*/
enum FILE_STATE getFileState(struct File *filePtr)
{
    return filePtr->fileState;
}

/*this function sets the file name*/
void setFileName(struct File *filePtr, char fileName[])
{
    strcpy(filePtr->fileName, fileName); //set file name
}

/*this function sets the file open type*/
void setFileOpenType(struct File *filePtr, char fileOpenType[])
{
    strcpy(filePtr->fileOpenType, fileOpenType);
}

/*this function sets the file type*/
void setFileType(struct File *filePtr, enum FILE_TYPE fileType)
{
    filePtr->fileType=fileType;
}

/*this function sets the file state*/
void setFileState(struct File *filePtr, enum FILE_STATE fileState)
{
    filePtr->fileState=fileState;
}

/*this function creates the file and checks if its valid
* arguments- Filename, File type
* return- boolean which states if the out file is valid
*/
bool initFile(struct File *filePtr, char fileName[], enum FILE_TYPE fileType)
{
    //delete existing file if write type. so we can create a new file
    if(fileType==WRITE_TYPE || fileType==WRITE_BINARY_TYPE)
    {
        deleteIfFileExists(fileName);//remove if the out file already exists
    }
    
    setFileState(filePtr, UNOPENED);//init the pointer to file struct and set the state
    setFileName(filePtr, fileName);//set file name
    setFileType(filePtr, fileType);//set file type

    //set file type string (r, w, w+, a etc)
    switch (fileType)
    {
        case READ_TYPE:
        {
            //set read type string 'r'
            setFileOpenType(filePtr, FILE_READ_TYPE);
            break;
        }

        case WRITE_TYPE:
        {
            //set write type string 'w'
            setFileOpenType(filePtr, FILE_WRITE_TYPE);
            break;
        }

        case READ_BINARY_TYPE:
        {
            //set binary read type string 'rb'
            setFileOpenType(filePtr, FILE_BINARY_READ_TYPE);
            break;
        }

        case WRITE_BINARY_TYPE:
        {
            //set binary read type string 'rb'
            setFileOpenType(filePtr, FILE_BINARY_WRITE_TYPE);
            break;
        }
       
        default:
        {
            return false;   
        }
    }
    //create the file and return true if its valid
    filePtr->file = fopen(getFileName(filePtr), getFileOpenType(filePtr)); 
    
    //file not valid
    if(!filePtr->file) 
    {
        if(getFileType(filePtr)==READ_TYPE || getFileType(filePtr)==READ_BINARY_TYPE)
        {
            printf("\nProblem in accesing the file: %s, check if file exists \n", getFileName(filePtr));
        }
        if(getFileType(filePtr)==WRITE_TYPE || getFileType(filePtr)==WRITE_BINARY_TYPE)
        {
            printf("\n %s Problem in creating the file check if file path is correct or memoryy is available | exit \n", getFileName(filePtr));
        }
        return false;
    }

    setFileState(filePtr, OPENED); //set file state
    return true;
}

/*this function deletes if the out file already exists
* arguments- file pointer
* return- none
*/
void deleteIfFileExists(char *fileName)
{
    if(checkIfFileExists(fileName))
    {
        printf("\nOUT_File present, deleting the outfile\n");
        remove(fileName);
    }    
}

/*this function closes the file if its opened
* arguments- pointer to struct file
* return- boolean weather if file is closed
*/
bool closeFile(struct File *filePtr)
{
    //check if file is not opened return false if so
    if(!filePtr || getFileState(filePtr)==UNOPENED)
    {
        printf("File not opened yet \n");
        return false;
    }

    //check if file is not opened return false if so
    if(getFileState(filePtr)==CLOSED)
    {
        printf("File already closed \n");
        return false;
    }

    //close the file and change the state
    fclose(filePtr->file);
    setFileState(filePtr, CLOSED);
    return true;
}

/*this function dumps takes input from user and dumps the data to the file
* arguments- pointer to file struct, char array to be dumped
* return- boolean weather data is written successfuly
*/
bool writeContentToFile(struct File *filePtr, char *CACHE)
{
    //file not initilized
    if(!filePtr || !filePtr->file || getFileState(filePtr)==UNOPENED)
    {
        printf("File not initiliazied cannot write exiting\n");
        return false;
    }

    //file not opened in write type
    if(getFileType(filePtr)!=WRITE_TYPE)
    {
        printf("File is not initialized with write type cannot write to this file\n");
        return false;
    }

    //keep getting users input until buffer is full. when buffer is full dump data to file
    while(fgets(CACHE, CACHE_SIZE, stdin)) //fgets is used to avoid buffer overflow
    {
        //check if used wants to exit
        if(strcmp(CACHE, EXIT_INPUT)==0)
        {
            return true;
        }

        //cache overflow notify the user
        if(strlen(CACHE)==CACHE_SIZE-1)
        {
            printf("Cache filled dumping data to file data: %s \n", CACHE);
        }

        if(fputs(CACHE, filePtr->file)==EOF)
        {
            printf("\n File write failed check the file directory and available memory space \n");
            return false;
        }
    }     
    
    return true;
}

/*this function takes content from the file reads into cache and displays. cache is reused incase of overflow
* arguments- pointer to file struct, cache string to store the data
* return- boolean weather data is read succesfuly
*/
bool readContentFromFile(struct File *filePtr, char * CACHE)
{
    //check if file is not opened return false if so
    if(!filePtr || !filePtr->file || getFileState(filePtr)==UNOPENED)
    {
        printf("File not opened or initialized yet \n");
        return false;
    }

    //file not opened in read type
    if(getFileType(filePtr)!=READ_TYPE)
    {
        printf("File is not initialized with read type cannot read this file exiting \n");
        return false;
    }

    //check if the file exists
    if(!checkIfFileExists(getFileName(filePtr)))
    {
        printf("File is not present cannot read exiting \n");
        return false;
    }

    //all the exception checks are cleared read content from the file now
    while(fgets(CACHE, CACHE_SIZE, filePtr->file))
    {
        printf("%s", CACHE);
    }
    return true;
}

/*this function takes takes content from the file name and writes to the given file pointer. Sanity test is also run to make sure the file copy is sucess
* arguments- pointer to file struct initialized with where data to be stored, name of file to be copied
* return- boolean weather file is copied sucessfuly.
*/
bool copyContentsToFile(struct File *writeFilePtr, char* userFileName)
{
    //user file is invalid
    if(!checkIfFileExists(userFileName))
    {
        printf("Invalid file entered");
        return false;
    }

    //file not initilized
    if(!writeFilePtr || !writeFilePtr->file || getFileState(writeFilePtr)==UNOPENED)
    {
        printf("File not initiliazied cannot write exiting\n");
        return false;
    }

    //file not opened in write type
    if(getFileType(writeFilePtr)!=WRITE_BINARY_TYPE)
    {
        printf("File is not initialized with write type cannot write to this file\n");
        return false;  
    }

    //file struct pointer to read data from user file
    struct File *readFilePtr = malloc(sizeof(struct File)); //init the pointer to struct 
    wchar_t* inputBuffer = malloc(CACHE_SIZE * sizeof(wchar_t)); //read in wchar_t so we can read binary strings as well.
    size_t bytesRead, bytesWritten; //to check the bytes of data read and written

    if(initFile(readFilePtr, userFileName, READ_BINARY_TYPE)) //init read file
    {   
        while(bytesRead=fread(inputBuffer, 1, CACHE_SIZE, readFilePtr->file)) //read from file
        {
            bytesWritten = fwrite(inputBuffer, 1, bytesRead, writeFilePtr->file);//write to file
            if(bytesWritten==FILE_WRITE_FAILED)
            {
                printf("\n File write failed check the file directory and available memory space \n");
                return false;
            }
            fflush(writeFilePtr->file); //flush contents
        }
    }
    else //read file failed
    {
        printf("problem with given file Exiting ... \n");
        return false;
    }

    //run sanity checker to make sure if file is written correctly.
    printf("contents copied sucessfuly \nrunning sanity checker to ensure if file is copied correctly\n");
    sleep(2);
    bool fileCopyResult = isFileCopySuccess(readFilePtr->file, writeFilePtr->file);
    if(fileCopyResult)
    {
        printf("Sanity test sucess \n");
    }
    else
    {
        printf("Sanity test failed\n");
    }
    //close and free read pointer, input buffer
    closeFile(readFilePtr);
    free(readFilePtr);
    free(inputBuffer);
    return fileCopyResult;
}

/* This function writes the piped content to the application to a file
* arguments- initialised write pointer
* return- boolean weather operation is success
*/
bool writePipedContentToFile(struct File *writeFilePtr)
{
    //file not initilized
    if(!writeFilePtr || !writeFilePtr->file || getFileState(writeFilePtr)==UNOPENED)
    {
        printf("File pointer not initiliazied cannot write exiting\n");
        return false;
    }

    //file not opened in write type
    if(getFileType(writeFilePtr)!=WRITE_BINARY_TYPE)
    {
        printf("File is not initialized with write type cannot write to this file\n");
        return false;  
    }

    //write the piped content to file and return
    char *CACHE = malloc(sizeof(char) * CACHE_SIZE); //init the cache (1 KB cache size. can be changes in Constants.h)
    size_t bytesRead, bytesWritten, totalBytes=0; //keep track of the bytes read from user.

    while( bytesRead = fread(CACHE, 1, CACHE_SIZE, stdin))
    {   
        totalBytes+=bytesRead;

        bytesWritten = fwrite(CACHE, 1, bytesRead, writeFilePtr->file);//write to file
        if(bytesWritten==FILE_WRITE_FAILED)
        {
            printf("\n File write failed check the file directory and available memory space \n");
            return false;
        }

        fflush(writeFilePtr->file); //flush contents
    }

    printf("Piped data write success Bytes written=%d\n", totalBytes);
    free(CACHE);
    sleep(3);
    return true;
}

/* (TESTER DEBUG FUNCTION) this function prints the summary of the file ie(name, open type)
* arguments- pointer to struct file
* return- none
*/
void printFileSummary(struct File *filePtr)
{
    //check if file is not opened. if not summary cannot be printed
    if(!filePtr || getFileState(filePtr)==UNOPENED)
    {
        printf("File not opened yet cannot print summary");
        return;
    }

    printf("Printing file summary \n");
    printf("file name is %s \n", getFileName(filePtr));
    printf("file open type is %s \n", getFileOpenType(filePtr));
}