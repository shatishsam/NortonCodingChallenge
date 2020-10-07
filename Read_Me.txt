Summary- Application to create and write arbitary data to file, read from file and delete file. 

Time Complexity- 
1.) Write File- O(N) where n is the size of input string.
2.) Read File- O(N) where n is the size of input string.
3.) Delete File- O(1) constant.

Space Complexity- 
1.) Write_File- O(1) constant time as we keep reusing the CACHE.
2.) Read_File- O(1) constant time as we keep reusing the CACHE.

Features-
1.) File struct created to keep track of the file state, name, and the type of file.
2.) Exception handling for files. Read type file cannot be written and file of write type cannot be written. All the Exception are handled in FileUtil.h
3.) CACHE string used to get input and flush to file instead of writing each character to file to reduce I/O operations.
4.) User friendly and easy to maintain code.


Changes Made on 24-09-2020

Features-
1.) Added File input from user so user can give any kind of file as an input.
2.) Sanity checker added so when file is written from user. we can make sure the contentes are copied correctly
4.) File automation tester, This feature takes different file types(Text, PDF, image, video, zip, binary) writes it to the destination and does sanity testing to check if the files are copied correctly

Changes Made on 6-10-2020
1,) Piped Binary stream data accepted. example command- "type filename | Application.exe", "7z e filename -so| Application.exe".
2.) Inital check to find if the Application is started from STDIN or PIPED.
3.) If application is started from STDIN, users can drag and drop files to application or give text input using STDIN.
4.) If application is piped we set the STDIN in binary mode and get binary stream data from STDIN.
5.) Automation tests done both for file copy and piped content.

NOTE: For piped automation 7Z must be installed as one of the commands uses 7z to unzip a compressed file and provides binary data to the application.
