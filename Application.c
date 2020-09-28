#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <unistd.h>
#include <windows.h>
#include <sys/types.h>

#include "Constants/Constants.h"
#include "SanityChecker/FileSanityChecker.h"

/*This file reads the input from user and executes another program. input can be file or string
* author- Shathish A
*/

int bufferIndex=0; //index of input buffer from user
char buffer[256]; //input buffer to store the input from user
bool isInputReceived=false; //to check if user has given file or anyother input

/*this takes input from the user and flushes into the buffer
* arguments- none
* return- none
*/
DWORD WINAPI getUserInput(LPVOID Param)
{
    printf("Drag and drop file or Press any key to type input \n"); //display instruction
    while(true)
    {
        char c = getch(); //get input from user 
        if(!isInputReceived) isInputReceived=true; //user has given input maybe a file or string
        if(c == '\n') break; //if enter is pressed no need to get anymore input
        buffer[bufferIndex++]=c; //flush the input to buffer
    }
}

/*main function. we wait for the user to give a file or anyother input and proceed from there on.*/
int main() 
{
     /* create the thread and wait for user input*/
    DWORD ThreadId;
    HANDLE ThreadHandle = CreateThread(NULL, 0, getUserInput, NULL, 0, &ThreadId);

    if (ThreadHandle != NULL)
    {
        while(true)
        {
            if(isInputReceived) //wait for child thread to receive input
            {
                sleep(1); //input received from user in child thread. 
                CloseHandle(ThreadHandle); //join the thread
                break;
            }
        }

        /*spawn another process and send the user input as arguments*/
        //spawnl(P_NOWAIT, "Executables/main.exe", "Executables/main.exe", buffer, NULL);
        execl("Executables/main.exe", "main", buffer, NULL);
    }

   return 0;
}