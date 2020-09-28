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

Changes Made on 28-09-2020

Features-
1.) Drag abd drop files to console to write them to out file.
2.) Fixed a bug (when folder is given as an input exit).
3.) File automation tests decoupled and moved to automation folder.
4.) File automation UI improved. more info added.

summary-
* Input is first received in application.exe file and the arguments is passed to Executables/main.exe. 
* There we will check if file has been given or normal input. and proceed from there on
* After file copyig is done sanity checking is done to ensure file copy is success
* File automation test moved to automation folder. More clean info is added.