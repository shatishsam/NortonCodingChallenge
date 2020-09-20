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