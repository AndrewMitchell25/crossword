#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define WORDSIZE 15
#define LISTSIZE 20
#define BOARDSIZE 16

// Function prototypes
void boardInit(char[BOARDSIZE][BOARDSIZE], char);
int getInput(char[LISTSIZE][WORDSIZE]);
int getFileInput(char[LISTSIZE][WORDSIZE], char[]);
void display(char[BOARDSIZE][BOARDSIZE]);
void sortWords(char[LISTSIZE][WORDSIZE], int);
void placeFirst(char[BOARDSIZE][BOARDSIZE], char[LISTSIZE][WORDSIZE], char[LISTSIZE][WORDSIZE], int, char[][WORDSIZE], int coords[][2]);
void placeSecond(char[BOARDSIZE][BOARDSIZE], char[LISTSIZE][WORDSIZE], char[LISTSIZE][WORDSIZE], int, char[][WORDSIZE], int coords[][2]);
void createSolution(char[BOARDSIZE][BOARDSIZE], char[BOARDSIZE][BOARDSIZE]);
void upperCase(char[WORDSIZE]);
void addHint(char[WORDSIZE], char[LISTSIZE][WORDSIZE], int, int, int, char[][WORDSIZE], int, int[][2]);
void addDir(char[][WORDSIZE], int, int);
void addLoc(int[][2], int, int, int);
void printClues(int, char[LISTSIZE][WORDSIZE], char[][WORDSIZE], int[][2]);
int placeNext(char[BOARDSIZE][BOARDSIZE], char[LISTSIZE][WORDSIZE], char[WORDSIZE], char[][WORDSIZE], int coords[][2], int);
int placeAll(char[BOARDSIZE][BOARDSIZE], char[LISTSIZE][WORDSIZE], char[LISTSIZE][WORDSIZE], int, char[][WORDSIZE], int coords[][2]);
void writeClues(int, char[LISTSIZE][WORDSIZE], char[][WORDSIZE], int[][2], char[WORDSIZE]);
void write(char[BOARDSIZE][BOARDSIZE], char[WORDSIZE]);
