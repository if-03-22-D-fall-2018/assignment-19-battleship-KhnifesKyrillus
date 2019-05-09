/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		KHNIFES Kyrillus
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>

#include "battleship.h"

FILE* myFile;
FILE* opFile;
static CellContent myField[FIELDSIZE][FIELDSIZE];
static CellContent opField[FIELDSIZE][FIELDSIZE];
static CellContent myGuess[FIELDSIZE][FIELDSIZE];

/**
*** Loads the two files battleship.my and battleship.op which hold the fields
*** of the players. The files hold a stream of 10 times 10 values of type
*** CellContent.
*/
void load_game()
{
    myFile=fopen("battleship.my","r");
    opFile=fopen("battleship.op","r");
    for (int i = 0; i < FIELDSIZE; i++)
    {
        for (int j = 0; j < FIELDSIZE; j++)
        {
            fread(&opField[i][j],sizeof(CellContent),1,opFile);
            fread(&myField[i][j],sizeof(CellContent),1,myFile);
            myGuess[j][i]=Unknown;
        }
    }
}

/**
*** @param row The row where we get the shot.
*** @param col The col where we get the shot.
*** @return The value of cell indicated by row and column of the own field (filled
*** with the values of battleship.my). If row/col point outside the field the
*** value OutOfRange is returned.
*/
CellContent get_shot(int row, int col)
{
    if(row<0||row>=FIELDSIZE||col<0||col>=FIELDSIZE)return OutOfRange;
    return myField[row][col];
}

void FillAroundWater(int row, int col)
{
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (row+i>=0&&row+i<FIELDSIZE&&col+j>=0&&col+j<FIELDSIZE)
            { 
               myGuess[row+i][col+j]=Water;
            }
        }
    }
}

/**
*** Sets the row and column of the my guesses table to the value held in the
*** opponents field. If this is a boat all surrounding cells are marked as water.
*** @param row The row where we place the shot
*** @param col The columnt where we place the shot.
*** @return True if target field is valid, i.e., inside the field, False otherwise.
*/
bool shoot(int row, int col)
{
    if(row<0||row>=FIELDSIZE||col<0||col>=FIELDSIZE)return false;
    
    if (opField[row][col]==Boat)
    {
        FillAroundWater(row,col);
    }
    myGuess[row][col]= opField[row][col];
    return true;
}

/**
*** @param row The row where we want to get our own guess.
*** @param col The column where we want to get our own guess.
*** @return The value of the table with my guesses at row and column. If row/col
*** is outside the field OutOfRange is returned.
*/
CellContent get_my_guess(int row, int col)
{
    if(row<0||row>=FIELDSIZE||col<0||col>=FIELDSIZE)return OutOfRange;
    return myGuess[row][col];
}
