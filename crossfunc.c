#include "crossfunc.h" //include the header file

// initializes the board using nested for loops to set each value equal to the fill character
void boardInit(char board[BOARDSIZE][BOARDSIZE], char fill)
{
    int i, j;
    for (i = 0; i < BOARDSIZE; i++)
    {
        for (j = 0; j < BOARDSIZE; j++)
        {
            board[i][j] = fill;
        }
    }
}

// function gets input from the user and stores it in the words array, returning the size of the array
int getInput(char words[LISTSIZE][WORDSIZE])
{
    // print the header
    printf("\nAnagram Crossword Puzzle Generator\n");
    printf("----------------------------------\n\n");
    printf("Enter a list of words followed by a \".\":\n");
    // create a string to temporarily hold the input
    char input[WORDSIZE];
    // scan
    scanf("%s", input);
    int size = 0;
    // use a while loop to keep taking input until a '.' is input or the size is too great
    while ((strcmp(input, ".") != 0) && (size < LISTSIZE))
    {
        int i;
        // reset a flag variable
        int flag = 0;
        // use a for loop to check each char of the input and make sure it's a letter
        for (i = 0; i < strlen(input); i++)
        {
            if (!isalpha(input[i]))
            {
                // set the flag to 1 and print error
                flag = 1;
                printf("Error - incorrect character.\n");
                break;
            }
        }
        // check if the word is too short or too long
        if (strlen(input) < 2 || strlen(input) > WORDSIZE)
        {
            // print error and set the flag
            printf("Error - incorrect word size.\n");
            flag = 1;
        }
        // skip any words that have been flagged
        if (!flag)
        {
            // if the word was accepted, change it to uppercase and add it to the words array
            upperCase(input);
            strcpy(words[size], input);
            size += 1;
        }
        // scan input again
        scanf("%s", input);
    }
    // stop the loop if too many words are inputted
    if (size == LISTSIZE)
    {
        printf("Word limit reached.\n");
    }
    // return the size of the array
    return size;
}

// gets input from the file and stores it in words, returning the array size
int getFileInput(char words[LISTSIZE][WORDSIZE], char argv[])
{
    // create a file pointer and open the file
    FILE *fp;
    fp = fopen(argv, "r");
    // print an error if it can't be found
    if (!fp)
    {
        printf("File %s cannot be found.\n", argv);
        return;
    }
    // print the header
    printf("\nAnagram Crossword Puzzle Generator\n");
    printf("----------------------------------\n\n");
    printf("Retrieving words from %s.\n", argv);
    // create a string to hold the current word
    int size = 0;
    char line[WORDSIZE];
    // use an infinite loop to traverse the file
    while (1)
    {
        // get the line from the file
        fgets(line, WORDSIZE, fp);
        // if the end of the file is reached or a period then break the loop
        if (feof(fp) || strcmp(line, ".") == 0)
        {
            break;
        }
        int i;
        // reset a flag variable
        int flag = 0;
        // use a for loop to check every char in the line
        for (i = 0; i < strlen(line) - 1; i++)
        {
            // if it's not a letter set the flag so it will be skipped and print an error
            if (!isalpha(line[i]))
            {
                flag = 1;
                printf("Error - incorrect character. Not including word %s\n", line);
                break;
            }
        }
        // if the word is too long or too short then print an error and set the flag
        if (strlen(line) < 2 || strlen(line) > WORDSIZE)
        {
            printf("Error - incorrect word size. Not including word %s\n", line);
            flag = 1;
        }
        // if the flag hasn't been set add it to the words array
        if (!flag)
        {
            upperCase(line);
            strncpy(words[size], line, strlen(line) - 1);
            size += 1;
        }
    }
    // close the file
    fclose(fp);
    // return the size of the array to be used later
    return size;
}

// formats and prints out a board to the console using loops
void display(char board[BOARDSIZE][BOARDSIZE])
{
    int i, j;
    for (i = 0; i < BOARDSIZE + 2; i++)
    {
        printf("-");
    }
    printf("\n");
    for (i = 0; i < BOARDSIZE; i++)
    {
        printf("|");
        for (j = 0; j < BOARDSIZE; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("|\n");
    }
    for (i = 0; i < BOARDSIZE + 2; i++)
    {
        printf("-");
    }
    printf("\n");
}

// like the above function but writes to a file instead of the console
void write(char board[BOARDSIZE][BOARDSIZE], char fileName[WORDSIZE])
{
    FILE *fp = fopen(fileName, "a");
    int i, j;
    for (i = 0; i < BOARDSIZE + 2; i++)
    {
        fprintf(fp, "-");
    }
    fprintf(fp, "\n");
    for (i = 0; i < BOARDSIZE; i++)
    {
        fprintf(fp, "|");
        for (j = 0; j < BOARDSIZE; j++)
        {
            fprintf(fp, "%c", board[i][j]);
        }
        fprintf(fp, "|\n");
    }
    for (i = 0; i < BOARDSIZE + 2; i++)
    {
        fprintf(fp, "-");
    }
    fprintf(fp, "\n");
    fclose(fp);
}

// function to sort the words array
void sortWords(char words[LISTSIZE][WORDSIZE], int size)
{
    int i, j;
    // create a temporary string variable
    char temp[WORDSIZE];
    // use a for loop to iterate through the words array
    for (i = 0; i < size; i++)
    {
        // set the max index to the current index
        int maxInd = i;
        // use another for loop to iterate through the rest of the array after the current index
        for (j = i + 1; j < size; j++)
        {
            // if the word is longer than the current max length
            if (strlen(words[j]) > strlen(words[maxInd]))
            {
                // set the max index to the current index
                maxInd = j;
            }
        }
        // once the longest word left is found swap the longest word with the current word using the temp variable
        strcpy(temp, words[maxInd]);
        strcpy(words[maxInd], words[i]);
        strcpy(words[i], temp);
    }
}

// place the first word and add its hint to the array
void placeFirst(char board[BOARDSIZE][BOARDSIZE], char hints[LISTSIZE][WORDSIZE], char words[LISTSIZE][WORDSIZE], int size, char dir[][WORDSIZE], int coords[][2])
{
    int i;
    // set the x so the word is centered by dividing by 2
    int x = (BOARDSIZE - strlen(words[0])) / 2;
    // set the y to half the boardsize to center vertically
    int y = BOARDSIZE / 2;
    // call the addhint function with these coordinates and pass in all the arrays
    addHint(words[0], hints, x, y, 0, dir, 0, coords);
    // use a for loop to put the word in the board
    for (i = 0; i < strlen(words[0]); i++)
    {
        board[y][x] = words[0][i];
        x++;
    }
}

// create the solution board
void createSolution(char board[BOARDSIZE][BOARDSIZE], char solution[BOARDSIZE][BOARDSIZE])
{
    int i, j;
    // use two for loops to iterate through the whole board
    for (i = 0; i < BOARDSIZE; i++)
    {
        for (j = 0; j < BOARDSIZE; j++)
        {
            // if there is not a '.' (is a letter) then change the corresponding location in the solution board to a space
            if (board[i][j] != '.')
            {
                solution[i][j] = ' ';
            }
        }
    }
}
// takes in a word and converts that word to uppercase
// pass by reference because it is a string so the original changes and don't need to return
void upperCase(char word[WORDSIZE])
{
    int i;
    for (i = 0; i < strlen(word); i++)
    {
        word[i] = toupper(word[i]);
    }
}

// takes in a bunch of arrays to add the scrambled word, direction, and coordinates
void addHint(char word[WORDSIZE], char hints[LISTSIZE][WORDSIZE], int x, int y, int i, char dir[][WORDSIZE], int direction, int coords[][2])
{
    // create a temporary copy of the word so that strfry doesn't affect the actualy word
    char temp[WORDSIZE];
    strcpy(temp, word);
    // add the scrambled word to the hints array
    strcpy(hints[i], strfry(temp));
    // add the correct direction to the direction array
    if (direction == 1)
    {
        strcpy(dir[i], "Down");
    }
    else
    {
        strcpy(dir[i], "Across");
    }
    // add the coordinates x and y to the coordinates array
    coords[i][0] = x;
    coords[i][1] = y;
}

// print the clues to the console, takes in all the arrays for the hints
void printClues(int size, char hints[LISTSIZE][WORDSIZE], char dir[][WORDSIZE], int coords[][2])
{
    printf("Clues:\n");
    int i;
    // use a for loop to print out all the hints by accessing the coordinates array, direction array, and scrambled word hints array
    for (i = 0; i < size; i++)
    {
        printf("%d,%d %s %s\n", coords[i][0], coords[i][1], dir[i], hints[i]);
    }
}

// same as above function but writes to the input file name instead of printing to console
void writeClues(int size, char hints[LISTSIZE][WORDSIZE], char dir[][WORDSIZE], int coords[][2], char fileName[WORDSIZE])
{
    // create a file pointer and open the file
    FILE *fp = fopen(fileName, "a");
    fprintf(fp, "Clues:\n");
    int i;
    // use a for loop to print the clues
    for (i = 0; i < size; i++)
    {
        fprintf(fp, "%d,%d %s %s\n", coords[i][0], coords[i][1], dir[i], hints[i]);
    }
    // close the file
    fclose(fp);
}

// places the word thats passed in on the board and adds the clues to the hint arrays
int placeNext(char board[BOARDSIZE][BOARDSIZE], char hints[LISTSIZE][WORDSIZE], char word[WORDSIZE], char dir[][WORDSIZE], int coords[][2], int count)
{
    int i, j, k, m, x, y;
    // create flag
    int flag = 0;
    // use a for loop to iterate through every letter in the current word
    for (i = 0; i < strlen(word); i++)
    {
        // use two more for loops to iterate through every char in the board
        for (j = 0; j < BOARDSIZE; j++)
        {
            for (k = 0; k < BOARDSIZE; k++)
            {
                // reset the flag variable
                flag = 0;
                // if the letter in the board equals the current letter of the word
                if (board[j][k] == word[i])
                {
                    // checks to see if the word on the board is horizontal by making sure the char on either side isn't a .
                    if (board[j][k + 1] != '.' || board[j][k - 1] != '.')
                    {
                        // check to see if the word can be placed vertically with if statements
                        // checks to see if the word is too big to fit on the board
                        if (j - i < 0 || j - i + strlen(word) > BOARDSIZE || board[j - i - 1][k] != '.' || board[j - i + strlen(word)][k] != '.')
                        {
                            // set the flag to 1 if it doesn't fit
                            flag = 1;
                        }
                        // use a for loop to check each space in the board where the word would go
                        for (m = j - i; m < strlen(word) + j - i; m++)
                        {
                            // if any of the spaces are not .'s then set the flag
                            if (board[m][k] != '.' && m != j)
                            {
                                flag = 1;
                                break;
                            }
                            // if any of the spaces to the left are letters then set the flag
                            if (board[m][k - 1] != '.' && m != j)
                            {
                                flag = 1;
                                break;
                            }
                            // if any of the spaces to the right are letters then set the flag
                            if (board[m][k + 1] != '.' && m != j)
                            {
                                flag = 1;
                                break;
                            }
                        }
                        // if the flag is zero, then the word fits, so place it in the board
                        if (flag == 0)
                        {
                            // set the x and y coordinates to the indexes in the loops
                            x = k;
                            y = j - i;
                            // call the addhint function to add all the info of the word to the arrays
                            addHint(word, hints, x, y, count, dir, 1, coords);
                            // use a for loop to put the word into the board by iterating through the word
                            for (m = 0; m < strlen(word); m++)
                            {
                                // set the position in the board to the letter of the word
                                board[y][x] = word[m];
                                y++;
                            }
                            // return 1 to show the word was placed in the board
                            return 1;
                        }
                    }
                    // same thing as before but if the word is vertical...
                    if (board[j + 1][k] != '.' || board[j - 1][k] != '.')
                    {
                        // then try to place it horizontally
                        if (k - i < 0 || k - i + strlen(word) > BOARDSIZE || board[j][k - i - 1] != '.' || board[j][k - i + strlen(word)] != '.')
                        {
                            flag = 1;
                        }
                        for (m = k - i; m < strlen(word) + k - i; m++)
                        {
                            if (board[j][m] != '.' && m != k)
                            {
                                flag = 1;
                                break;
                            }
                            if (board[j - 1][m] != '.' && m != k)
                            {
                                flag = 1;
                                break;
                            }
                            if (board[j + 1][m] != '.' && m != k)
                            {
                                flag = 1;
                                break;
                            }
                        }
                        // if the word fits then place it in the board
                        if (flag == 0)
                        {
                            x = k - i;
                            y = j;
                            addHint(word, hints, x, y, count, dir, 0, coords);
                            for (m = 0; m < strlen(word); m++)
                            {
                                board[y][x] = word[m];
                                x++;
                            }
                            // return 1 to signify that the word was placed
                            return 1;
                        }
                    }
                }
            }
        }
    }
    // if the word hasn't been placed yet print that it will be skipped and return 0 to show that it hasn't been placed
    printf("Skipping %s\n", word);
    return 0;
}

int placeAll(char board[BOARDSIZE][BOARDSIZE], char hints[LISTSIZE][WORDSIZE], char words[LISTSIZE][WORDSIZE], int size, char dir[][WORDSIZE], int coords[][2])
{
    // place the first word using the placeFirst method
    placeFirst(board, hints, words, size, dir, coords);
    // create variables
    int i;
    int res;
    int hintInd = 1;
    int skippedInd = 0;
    // create an array to hold the words that get skipped
    char skipped[LISTSIZE][WORDSIZE];
    // use a for loop to place all the rest of the words in the words array after the first one
    for (i = 1; i < size; i++)
    {
        // set result equal to placing the next word : 1 if the word is placed and 0 if it isn't
        res = placeNext(board, hints, words[i], dir, coords, hintInd);
        // if the word was placed
        if (res == 1)
        {
            // add one to the hint index which we'll return later so we can eventually print out the correct number of hints
            hintInd += 1;
        }
        else
        {
            // if the word wasn't placed add it to the skipped words array and increment the index of the skipped array
            strcpy(skipped[skippedInd], words[i]);
            skippedInd++;
        }
    }

    // go back over skipped words and try to place them
    // use an infinite loop
    while (1)
    {
        // create a variable that can be changed
        int var = 0;
        // print that it's trying again
        if (skippedInd > 0)
        {
            printf("Trying Again...\n");
        }
        // use a for loop to iterate through the skipped words
        for (i = 0; i < skippedInd; i++)
        {
            // skip the value in the skipped array if it has already been placed
            if (strcmp(skipped[i], "PLACED") == 0)
            {
                continue;
            }
            // try to place the word using placeNext
            res = placeNext(board, hints, skipped[i], dir, coords, hintInd);
            // if the word has been placed
            if (res == 1)
            {
                // add one to the hint index so that the hint will be printed
                hintInd += 1;
                // replace the word in the skipped array so it doesn't try to include the same word again
                strcpy(skipped[i], "PLACED");
                // change the variable so that it will loop again and try the words it couldn't place the first or second time
                var += 1;
            }
        }
        // if nothing has changed (aka no previously skipped word has been placed) break out of the loop and don't keep trying
        if (var == 0)
        {
            break;
        }
    }
    // return the size of the hints added so that we can print out hints only for the words we added
    return hintInd;
}