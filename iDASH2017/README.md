# a Good Way To Import the project IDASH2017  
First of all, download the IDASH2017-master.zip file from IDASH2017 github page, select "Clone or download" | "Download ZIP"  
  
Unzip the IDASH2017-master.zip file, that will create directory: /IDASH2017-master/{IDASH2017/, LICENSE, README.md}  
  
Start Eclipse IDE, File >> New >> Project... >> C/C++ >> C++ Project  
C++ Project--------------------------------------------------------------------------------  
Project name: iDASH2017  
[ ] Use default location  
Location: /home/tree/Downloads/IDASH2017-master/IDASH2017  
Project type: Makefile project >> Empty Project  
Toolchains: Linux GCC  
Next  
Finish  
  
## Configure this IDASH2017 project  
Right Click on the IDASH2017 project, choose "Properties":  
Properties---------------------------------------------------------------------------------  
If "C/C++ Build" >> "Settings" is missing "Tool Settings" : 
    Select "C/C++ Build" | "Makefile generation" >> "Generate Makefiles automatically" and Click "Apply".  
 
"C/C++ Build" >> "Settings" >> "Tool Settings" >> "GCC C++ Linker"-------------------------  
"Libraries" >> "Libraries(-l)" : ntl, gmp, HEAAN, m (the order is important, otherwise will end in error)
"Libraries" >> "Library search path(-L)" : directories in which we can find the above libraries (ntl, gmp,...)
                                          /usr/local/lib (libntl.a, libgmp.a, libgmpxx.a ...)
                                          /home/tree/Downloads/HEAAN/HEAAN/lib  (libHEAAN.a)  
"Miscellaneous" | "Linker flags" : -pthread  
  
"C/C++ General" >> "Paths and Symbols" >> "Includes" >> "Languages"-------------------------  
"GNU C++" >> "Include directories" : directories in which we can find the .h files (gmp.h,gmpxx.h,HEAAN.h ...)
                                     /home/tree/Downloads/HEAAN/HEAAN/src  
                                     /usr/local/include  
Make sure "GNU C" and "Assembly" both have the same "Include directories".  
  
Now, build this project, and it probably success with finished building target: iDASH2017.
Remeber: "Run as" | "Local C/C++ Application" will not run the finished building target, 
         it need to run on command line: ./IDASH2017 "../data/data103x1579.txt" 1 7 5 1 -1 1 5 1  
         





# Not a Good Way To Import the project IDASH2017
First of all, download the .zip file from IDASH2017 github page, select "Clone or download" | "Download ZIP"  

File >> Import... >> General >> Projects from Folder or Archive  

Import Projects from File System or Archive-------------------------------------------------  
Import source: /home/tree/Downloads/IDASH2017-master.zip  
Do not select the box  Working sets | Add project to working sets!  
Just click Finish.  

# Not a Good Way To Export the project IDASH2017  
Right Click on the project IDASH2017, choose "Export..."  
Export--------------------------------------------------------------------------------------  
General >> Archive File  
Next  
  
To archive file: /home/tree/IDASH2017.zip  
[Y] Save in zip format                            [Y] Create directory structure for files  
[Y] Compress the contents of the file    
Finish
