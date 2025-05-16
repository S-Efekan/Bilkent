#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 100

int main ( void ) {
    char word1[SIZE], word2[SIZE];
    char ch;
    int count;
    char lastChar;
    int gameOver = 0;

    printf ( "Player 1, enter a word ending with '.': " );
    count = 0;

    while (scanf ( " %c", &ch ) && ch != '.')
    {
        word1[count++] = ch;
    }

    if (word1[0] != 'a' && word1[0] != 'A')
    {
        printf ( "Word does not start with 'a' or 'A'.\n" );
        printf ( "Game over: Player 2 wins.\n" );
        gameOver = 1;
    }

    lastChar = word1[count - 1];

    while (!gameOver) {


        printf ( "Player 2, enter a word starting with '%c' and ending with '.': ", lastChar );
        count = 0;
        while (scanf ( " %c", &ch ) && ch != '.') {
            word2[count++] = ch;
        }

        if (word2[0] != lastChar) {
            printf ( "Word does not start with '%c'.\n", lastChar );
            printf ( "Game over: Player 1 wins.\n" );
            gameOver = 1;
        }
        else {
            lastChar = word2[count - 1];
        }


        if (!gameOver) {
            printf ( "Player 1, enter a word starting with '%c' and ending with '.': ", lastChar );
            count = 0;
            while (scanf ( " %c", &ch ) && ch != '.') {
                word1[count++] = ch;
            }

            if (word1[0] != lastChar) {
                printf ( "Word does not start with '%c'.\n", lastChar );
                printf ( "Game over: Player 2 wins.\n" );
                gameOver = 1;
            }
            else {
                lastChar = word1[count - 1];
            }
        }
    }

    return 0;
}