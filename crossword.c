#include "crossfunc.h" //include the header file

int main(int argc, char *argv[])
{
    // create two 2D arrays to hold the board and the solution
    char board[BOARDSIZE][BOARDSIZE];
    char solution[BOARDSIZE][BOARDSIZE];
    // call the boardInit function on both boards to fill them with their fill characters
    boardInit(board, '.');
    boardInit(solution, '#');
    // create a 2D array to store the words
    char words[LISTSIZE][WORDSIZE];
    int size = 0;
    // if there is only one argument, run in interactive mode
    if (argc == 1)
    {
        // call the getInput function on the words list and store it in size
        size = getInput(words);
        // if there are two or three arguments
    }
    else if (argc == 2 || argc == 3)
    {
        // get input from the file that is named in argument 1
        size = getFileInput(words, argv[1]);
        if (size == 0)
        {
            return 1;
        }
    }
    // if there are too many arguments print an error and end
    else
    {
        printf("Error - too many arguments\n");
        return 1;
    }
    // create 2D arrays to store the hints, coordinates, and directions
    char hints[size][WORDSIZE];
    int coords[size][2];
    char dir[size][WORDSIZE];
    // call the sortWords function, passing in the words array and size variable
    sortWords(words, size);
    // set a variable ind equal to calling placeAll and passing in the arrays we created before
    int ind = placeAll(board, hints, words, size, dir, coords);
    // call createSolution with the board and solution
    createSolution(board, solution);
    // if there are three arguments, then write the output to the file passed in
    if (argc == 3)
    {
        write(board, argv[2]);
        write(solution, argv[2]);
        writeClues(ind, hints, dir, coords, argv[2]);
    }
    else
    {
        // otherwise just display to the console using these functions
        display(board);
        display(solution);
        printClues(ind, hints, dir, coords);
    }
    return 0;
}