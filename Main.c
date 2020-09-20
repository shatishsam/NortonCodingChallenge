#include <stdio.h>
#include <string.h>
#include "FileUtil.h"

/*This file is where the execution starts. user input is acquired and appropirate actions are taken.
* Kindly refer Read_Me.txt for code flow and additional info.
* author- Shathish A
*/

char *fileName; //file name
char *CACHE; //cache array to sore the input from user.

struct File *outfilePtr; //to write contents to file (pointer to file)
struct File *inFilePtr; //to read contents from file (pointer to struct)

/*this function initialises all the required variables for the program(name, cache, struct file pointer)
* arguments- none
* return- none
*/
void initializeVariables()
{
     fileName = "D:\\OUT_FILE"; //file name
     CACHE = malloc(sizeof(char) * CACHE_SIZE); //init the cache (1 MB cache size. can be changes in Constants.h)

     /*This pointer to struct will be used to write to file*/
     outfilePtr = malloc(sizeof(struct File)); //init the pointer to struct

     /*This pointer to struct will be used to read fromfile*/
     inFilePtr=malloc(sizeof(struct File)); //init the pointer
}

/*this function destructs all the variables to avoid memory leak (Cache, file pointers)
* arguments- none
* return- none
*/
void destructVariables()
{
     free(CACHE);
     free(inFilePtr);
     free(outfilePtr);
}

/*this function reads content from file and displays the content
* arguments- none
* return- none
*/
void displayConetentFromFile()
{
     if(initFile(inFilePtr, fileName, READ_TYPE)) //initialize file with read type
     {
          printf("reading contents from file:");
          readContentFromFile(inFilePtr, CACHE);
          closeFile(inFilePtr);
     }
}

/*this function gets the userinput and writes the content to file
* arguments- none
* return- none
*/
void putUserInputToFile()
{    
     if(initFile(outfilePtr, fileName, WRITE_TYPE)) //initilize file with write type
     {
          printf("enter the input to write to file. To quit give 'exit' as input\n");
          writeContentToFile(outfilePtr, CACHE);
          closeFile(outfilePtr);
     }    
}

/*this function displays the instructions to the user
* arguments- none
* return- none
*/
void displayInstructions()
{
     printf("\nWelcome Press 0 to exit\n");
     printf("Press 1 to create and write to file\n");
     printf("Press 2 to read from file\n");
     printf("press 3 to delete the file \n");
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
                    displayConetentFromFile();
                    break;
               }
               //delete file
               case DELETE_FILE:
               {
                    deleteIfFileExists(fileName);
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