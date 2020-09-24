#include <stdio.h>
#include <string.h>

#include "Util/FileUtil.h"
#include "Automation/FileAutomationTest.h"

/*This file is where the execution starts. user input is acquired and appropirate actions are taken.
* Kindly refer Read_Me.txt for code flow and additional info.
* author- Shathish A
*/

char *fileName; //file name
char *CACHE; //cache array to sore the input from user.

struct File *filePtr; //used to read and write file (pointer to file struct)

/*this function initialises all the required variables for the program(name, cache, struct file pointer)
* arguments- none
* return- none
*/
void initializeVariables()
{
     fileName = "OUT_FILE"; //file name
     CACHE = malloc(sizeof(char) * CACHE_SIZE); //init the cache (1 KB cache size. can be changes in Constants.h)

     /*This pointer to struct will be used to read and write to file*/
     filePtr = malloc(sizeof(struct File)); //init the pointer to struct
}

/*this function destructs all the variables to avoid memory leak (Cache, file pointers)
* arguments- none
* return- none
*/
void destructVariables()
{
     free(CACHE);
     free(filePtr);
}

/*this function reads content from file and displays the content
* arguments- none
* return- none
*/
void displayContentFromFile()
{
     if(initFile(filePtr, fileName, READ_TYPE)) //initialize file with read type
     {
          printf("reading contents from file:");
          readContentFromFile(filePtr, CACHE);
          closeFile(filePtr);
     }
}

/*this function gets the userinput and writes the content to file
* arguments- none
* return- none
*/
void putUserInputToFile()
{    
     if(initFile(filePtr, fileName, WRITE_TYPE)) //initilize file with write type
     {
          printf("enter the input to write to file. To quit give 'exit' as input\n");
          writeContentToFile(filePtr, CACHE);
          closeFile(filePtr);
     }    
}

/*this function copies file from user given source to OUT_FILE. sanity test is done later to check if file copy is success
* arguments- none
* return- none
*/
void parseFileAndStore()
{
     if(initFile(filePtr, fileName, WRITE_BINARY_TYPE))
     {
          char* userFileName = malloc(30 * sizeof(char)); //store user file name here max 30 characters.
          printf("Enter the file name along with path\n");
          scanf("%s", userFileName); //get file name
          
          if(copyContentsToFile(filePtr, userFileName)) //copy content and run sanity check
          {
               printf("\nFile written succesfuly \n");
          }
          //close file and free char array
          closeFile(filePtr);
          free(userFileName);
     }
}

/*this function displays the instructions to the user
* arguments- none
* return- none
*/
void displayInstructions()
{
     printf("\nHii!!! \nPress 0 to exit\n");
     printf("Press 1 to create and write to file\n");
     printf("Press 2 to read from file\n");
     printf("press 3 to delete the file \n");
     printf("press 4 to give file as an input | the content of this file will be written to OUT_FILE and the written file will be tested\n");
     printf("Press 5 to run File Automation TEST | Different types of files (txt, pedf, zip, bin etc) will be automatically written and will be tested\n");
}

int main()
{
     initializeVariables(); //init variables

     int input; //user input
     while(true)
     {   
          displayInstructions(); //display instructions for user
          scanf("%d", &input);

          switch(input)
          {
               //write content to file
               case WRITE_FILE:
               {
                    putUserInputToFile();
                    break;
               }
               //read content from file
               case READ_FILE:
               {
                    displayContentFromFile();
                    break;
               }
               //delete file
               case DELETE_FILE:
               {
                    deleteIfFileExists(fileName);
                    break;
               }
               //give file as an input
               case FILE_AS_INPUT:
               {
                    parseFileAndStore();
                    break;
               }
               //File automation test.
               case FILE_AUTOMATION_TEST:
               {
                    runFileCopyAutomation();
                    break;
               }
               //exit
               case EXIT:
               {
                    printf("Exiting.........\n");
                    destructVariables();
                    exit(0);
               }
               //wrong input option
               default:
               {
                    printf("Wrong input provided Exiting.........\n");
                    destructVariables();
                    exit(0);
               }
          }
     }    
}