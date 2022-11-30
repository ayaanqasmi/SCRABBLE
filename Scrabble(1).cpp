#include <iostream>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>

static char board[16][16];
void red()
{
    printf("\033[1;31m");
}

void green()
{
    printf("\033[0;32m");
}
void yellow()
{
    printf("\033[0;33m");
}
void blue()
{
    printf("\033[0;34m");
}
void cyan()
{
    printf("\033[0;36m");
}

void magenta()
{
    printf("\033[1;35m");
}

void reset()
{
    printf("\033[0m");
}

void InitializeBoard()
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            board[i][j] = ' ';
        }
    }
    for (int i = 1; i < 16; i++)
    {
        char a = i + 96;
        char b = i + 64;
        board[0][i] = a;
        board[i][0] = b;
    }
    board[1][1] = '!';
    board[1][8] = '!';
    board[1][15] = '!';
    board[8][1] = '!';
    board[8][15] = '!';
    board[15][1] = '!';
    board[15][8] = '!';
    board[15][15] = '!';
    int x, y;
    for (x = 2, y = 2; x < 15; x++, y++)
    {
        board[x][y] = '*';
        board[x][16 - y] = '*';
    }
    board[2][6] = '3';
    board[2][10] = '3';
    board[6][2] = '3';
    board[6][6] = '3';
    board[6][10] = '3';
    board[6][14] = '3';
    board[10][2] = '3';
    board[10][6] = '3';
    board[10][10] = '3';
    board[10][14] = '3';
    board[14][6] = '3';
    board[14][10] = '3';

    board[1][4] = '2';
    board[1][12] = '2';
    board[3][7] = '2';
    board[3][9] = '2';
    board[4][1] = '2';
    board[4][8] = '2';
    board[4][15] = '2';
    board[7][3] = '2';
    board[7][7] = '2';
    board[7][9] = '2';
    board[7][13] = '2';
    board[8][4] = '2';
    board[8][12] = '2';
    board[9][3] = '2';
    board[9][7] = '2';
    board[9][9] = '2';
    board[9][13] = '2';
    board[12][1] = '2';
    board[12][8] = '2';
    board[12][15] = '2';
    board[13][7] = '2';
    board[13][9] = '2';
    board[15][4] = '2';
    board[15][12] = '2';
}

void DisplayBoard()
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (i == 0 && j == 0)
            {
                printf("     ");
                continue;
            }
            green();
            if (i == 0 || j == 0)
            {
                red();
                printf(" |");

                printf("%c", board[i][j]);

                printf("| ");
                reset();
                continue;
            }

            printf(" |");
            reset();
            if (board[i][j] == '!')
                magenta();
            else if (board[i][j] == '*')
                yellow();
            else if (board[i][j] == '2')
                cyan();
            else if (board[i][j] == '3')
                blue();
            printf("%c", board[i][j]);
            green();
            printf("| ");
            reset();
        }
        green();
        printf("\n-------------------------------------------------------------------------------\n");
        reset();
    }
}
void enterCharacterOnBoard(char ch, int x, int y)
{
    board[x][y] = ch;
}
enum Direction
{
    DOWN = 0,
    UP = 1,
    LEFT = 2,
    RIGHT = 3
};

struct Word
{
    int x;
    int y;
    enum Direction dire;
    char word[50];
};
void enterWordOnBoard(struct Word w)
{
    switch (w.dire)
    {
    case DOWN:
        for (int i = 0; i < strlen(w.word) - 1; i++)
        {
            enterCharacterOnBoard(w.word[i], w.x + i, w.y);
        }
        break;
    case UP:
        for (int i = strlen(w.word) - 1, j = 0; i >= 0 && j < strlen(w.word) - 1; i--, j++)
        {
            enterCharacterOnBoard(w.word[j], w.x - i, w.y);
        }
        break;
    case LEFT:
        for (int i = strlen(w.word) - 1, j = 0; i >= 0 && j < strlen(w.word) - 1; i--, j++)
        {
            enterCharacterOnBoard(w.word[j], w.x, w.y - i);
        }
        break;

    case RIGHT:
        for (int i = 0; i < strlen(w.word) - 1; i++)
        {
            enterCharacterOnBoard(w.word[i], w.x, w.y + i);
        }
        break;
    }
}
Word getWord()
{
    struct Word word;
    printf("Enter word: ");
    fgets(word.word, 50, stdin);
    

    printf("Enter x and y coordinates: ");
    scanf_s("%d", &word.x);
    scanf_s("%d", &word.y);

    printf("Enter 0 for down, 1 for up, 2 for left, 3 for right: ");
    scanf_s("%d", &word.dire);

    return word;
}
int main()
{
    printf("\n\n");
    InitializeBoard();
    DisplayBoard();
    struct Word w = getWord();
    enterWordOnBoard(w);
    system("CLS");
    DisplayBoard();
}