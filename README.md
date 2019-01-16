This program will goto the website of a particular case and search the page for updates.
Depending on the flags used, it can update a file or print to stdout (the console).

It might be useful to make a batch/bash script to autorun the program

execution requires command line arguements
usages:
  1: prog_name case-file
  2: prog_name -i case-number ...
  3: prog_name -a case-file case-number ...
  4: prog_name -r case-file case-number ...

1) case-file is the name of the file containing all of the cases to be checked, as well as the case data.
2) case-number is the case to be checked (supports multiple cases).
   This usage simply prints the most recent row of the table to the console.
3) This usage checks all cases in case-file, then adds case-number to case-file (supports multiple cases).
   This usage can also be used with a new file to initialize it with case-number (and additional cases).
4) This usage removes case-number and its data from case-file


TODO: Decide file format and structure
TODO: Add additional flags (optional)
TODO: Add HTML parser
TODO: Complete functions: updateFile, getRecent, addToFile, removeFromFile
TODO: Create URL generating function
