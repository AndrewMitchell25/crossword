# Crossword
This program is designed to take in a list of words and output a crossword puzzle using as many of those words as it can.

# Running the Project
This project is designed to run in the Linux terminal. To run the project, download the files from this repo onto your local machine. Open the terminal and move to the folder containing the project files. Use the command `make` to build the project files. Then, use the command `./crossword` to run the program. The program will prompt the user to enter a list of words, followed by a `.` which will signify the end of the list. Alternatively, you can write this list of words to a file and include it when calling the function, (ex. `./crossword words.txt`). The program will then output first the crossword key, with the words visible, the crossword itself, with the words hidden, and hints for the coordinates of each word (the word scrambled). If the user enters two file names when running the program, it will write the output to the second file (ex. `./crossword words.txt output.txt`).

Have fun!
