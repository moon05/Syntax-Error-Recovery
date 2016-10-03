# Syntax-Error-Recovery
Implementing Niklaus Wirth's recovery mechanism in a extended grammar of a calculator language in C++

Abdullah Al Mamun
CSC 254
Project 2: Syntax Error Recovery
Github Directory: https://github.com/moon05/Syntax-Error-Recovery
** Github directory is currently private. In case it counts as extra credit and also for version
control I created the repository **

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

My program currently does what the basic requirements are including  converting existing code base to C++, extending the given grammar, implementing Nilaus Wirth's Error Recovery mechanishm and printing the Synatx Tree.

For EXTRA CREDIT I have also implemented Immediate Error Detection.
I tried doing a Python version of this program but only managed to very little because of not having enough time, but the directory is here.

The directory named "c++" contains all my main work. It has the files:
	parse.cpp
	scan.cpp
	scan.h
	test.txt <this contains the original code block given in the assignment>
	test2.txt <this contains extra code block to show error recovery and Immediate Error Detection>
	Makefile

To RUN it:

make test
^^This will run the test cases provided

	>> parse will be created
	For trying out from terminal
	>>./parse
	and then the user can test out the program



