
#include <stdio.h>
#include <string.h>

#include "FileAutomationTest.h"

/*This file is used for automation testing. diff types of files are passed as input and tested.
* Kindly refer Read_Me.txt for code flow and additional info.
* author- Shathish A
*/

int main(int argc, char* argv[])
{
    runFileCopyAutomation();

    printf("\n File Automation test completed\n");
    sleep(2);
    return 0;
}