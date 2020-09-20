#include <stdio.h> 
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "Constants.h"

/*This file has the file pointer and realted methods. Exception are handled for files (ie writing into read files, reading unopened files etc) 
* author- Shathish A
*/

//file strucutre containing all the info about the file.
struct File
{
    FILE *file; //file
    char fileName [30] ; //file name along with location
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
    //check if file is already initialized
    if(filePtr && getFileState(filePtr)==OPENED)
    {
        printf("file already initialized \n");
        return true;
    }

    //delete existing file if write type. so we can create a new file
    if(fileType==WRITE_TYPE)
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
        if(getFileType(filePtr)==READ_TYPE)
        {
            printf("\nProblem in accesing the file: %s, check if file exists \n", getFileName(filePtr));
        }
        if(getFileType(filePtr)==WRITE_TYPE)
        {
            printf("\n %s Problem in creating the file check if file path is correct or memoryy is available | exit \n", getFileName(filePtr));
        }
        return false;
    }

    setFileState(filePtr, OPENED); //set file state
    return true;
}

/*this function checks if given file exists or not
* arguments- Filename
* return- boolean weather file exists
*/
bool checkIfFileExists(char *fileName)
{
    return access(fileName, F_OK) == 0;
}

/*this function deletes if the out file already exists
* arguments- file pointer
* return- none
*/
void deleteIfFileExists(char *fileName)
{
    if(checkIfFileExists(fileName))
    {
        printf("file present, deleting the outfile\n");
        remove(fileName);
    }    
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
    printf("data succesfuly written to file\n");
    return true;
}

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