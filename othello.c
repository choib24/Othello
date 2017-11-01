#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define EMPTY 0
#define BLACK 1
#define WHITE -1
#define BOARD_SIZE 8

int board[8][8] = {0};
int black = 2; //number of black token
int white = 2; //number of white token

void clearBoard()
{
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = 0;
    }
}

void initGame()
{
    board[3][3] = BLACK;
    board[4][4] = BLACK;

    board[3][4] = WHITE;
    board[4][3] = WHITE;
}

void printMap(int turn)
{
    system("clear");
    printf("┌───┬───┬───┬───┬───┬───┬───┬───┬───┐\n");
    printf("│   │ A │ B │ C │ D │ E │ F │ G │ H │\n");
    printf("├───┼───┼───┼───┼───┼───┼───┼───┼───┤\n");

    for (int i = 0; i < 8; i++)
    {
        printf("│%3d│", i + 1);
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] == EMPTY)
                printf("   │");

            if (board[i][j] == WHITE)
                printf(" ● │");

            if (board[i][j] == BLACK)
                printf(" ○ │");
        }
        printf("\n├───┼───┼───┼───┼───┼───┼───┼───┼───┤\n");
    }
    if (turn == 1)
        printf(" ●:%d        ○:%d    TURN : BLACK  \n\n", white, black);
    else
        printf(" ●:%d        ○:%d    TURN : WHITE  \n\n", white, black);
}

int isValidInput(const char *input)
{
    char ptr[4];
    strcpy(ptr, input);
    char *xCor = strtok(ptr, "-");
    char *yCor = strtok(NULL, "-");

    if (*xCor >= '1' && *xCor <= '8' && *yCor >= 'A' && *yCor <= 'H')
        return 1;
    else
        return 0;
}

void reverseLeft(int posX, int posY, int amount)
{
    int count = 0;
    int i = posY - 1;

    while (count < amount)
    {
        board[posX][i] *= -1;
        i--;
        count++;
    }
}

void reverseRight(int posX, int posY, int amount)
{
    int count = 0;
    int i = posY + 1;

    while (count < amount)
    {
        board[posX][i] *= -1;
        i++;
        count++;
    }
}

void reverseUp(int posX, int posY, int amount)
{
    int count = 0;
    int i = posX - 1;

    while (count < amount)
    {
        board[i][posY] *= -1;
        i--;
        count++;
    }
}

void reverseDown(int posX, int posY, int amount)
{
    int count = 0;
    int i = posX + 1;

    while (count < amount)
    {
        board[i][posY] *= -1;
        i++;
        count++;
    }
}

void reverseLeftUp(int posX, int posY, int amount)
{
    int count = 0;
    int i = posX - 1;
    int j = posY - 1;

    while (count < amount)
    {
        board[i][j] *= -1;
        i--;
        j--;
        count++;
    }
}

void reverseLeftDown(int posX, int posY, int amount)
{
    int count = 0;
    int i = posX + 1;
    int j = posY - 1;

    while (count < amount)
    {
        board[i][j] *= -1;
        i++;
        j--;
        count++;
    }
}

void reverseRightUp(int posX, int posY, int amount)
{
    int count = 0;
    int i = posX - 1;
    int j = posY + 1;

    while (count < amount)
    {
        board[i][j] *= -1;
        i--;
        j++;
        count++;
    }
}

void reverseRightDown(int posX, int posY, int amount)
{
    int count = 0;
    int i = posX + 1;
    int j = posY + 1;

    while (count < amount)
    {
        board[i][j] *= -1;
        i++;
        j++;
        count++;
    }
}

int checkLeft(int turn, int posX, int posY, int doAction)
{
    int count = 1;
    int i;

    if (board[posX][posY - 1] != turn * -1)
        return 0;

    for (i = posY - 1; i > 0; i--)
    {
        if (board[posX][i - 1] == EMPTY)
            return 0;

        if (board[posX][i - 1] == board[posX][i] * -1)
        {
            if (doAction)
            {
                reverseLeft(posX, posY, count);

                if (turn == 1)
                {
                    black += count;
                    white -= count;
                }
                else
                {
                    white += count;
                    black -= count;
                }
            }
            return 1;
        }

        count++;
    }

    return 0;
}

int checkRight(int turn, int posX, int posY, int doAction)
{
    int count = 1;
    int i;

    if (board[posX][posY + 1] != turn * -1)
        return 0;

    for (i = posY + 1; i < BOARD_SIZE - 1; i++)
    {
        if (board[posX][i + 1] == EMPTY)
            return 0;

        if (board[posX][i + 1] == board[posX][i] * -1)
        {
            if (doAction)
            {
                reverseRight(posX, posY, count);

                if (turn == 1)
                {
                    black += count;
                    white -= count;
                }
                else
                {
                    white += count;
                    black -= count;
                }
            }
            return 1;
        }

        count++;
    }

    return 0;
}

int checkUp(int turn, int posX, int posY, int doAction)
{
    int count = 1;
    int i;

    if (board[posX - 1][posY] != turn * -1)
        return 0;

    for (i = posX - 1; i > 0; i--)
    {
        if (board[i - 1][posY] == EMPTY)
            return 0;

        if (board[i - 1][posY] == board[i][posY] * -1)
        {
            if (doAction)
            {
                reverseUp(posX, posY, count);

                if (turn == 1)
                {
                    black += count;
                    white -= count;
                }
                else
                {
                    white += count;
                    black -= count;
                }
            }
            return 1;
        }

        count++;
    }

    return 0;
}

int checkDown(int turn, int posX, int posY, int doAction)
{
    int count = 1;
    int i;

    if (board[posX + 1][posY] != turn * -1)
        return 0;

    for (i = posX + 1; i < BOARD_SIZE - 1; i++)
    {
        if (board[i + 1][posY] == EMPTY)
            return 0;

        if (board[i + 1][posY] == board[i][posY] * -1)
        {
            if (doAction)
            {
                reverseDown(posX, posY, count);

                if (turn == 1)
                {
                    black += count;
                    white -= count;
                }
                else
                {
                    white += count;
                    black -= count;
                }
            }
            return 1;
        }

        count++;
    }

    return 0;
}

int checkLeftUp(int turn, int posX, int posY, int doAction)
{
    int i = posX - 1;
    int j = posY - 1;
    int count = 1;

    if (board[i][j] != turn * -1)
        return 0;

    while (1)
    {
        if (i <= 0 || j <= 0)
            break;

        if (board[i - 1][j - 1] == EMPTY)
            return 0;

        if (board[i - 1][j - 1] == board[i][j] * -1)
        {
            if (doAction)
            {
                reverseLeftUp(posX, posY, count);

                if (turn == 1)
                {
                    black += count;
                    white -= count;
                }
                else
                {
                    white += count;
                    black -= count;
                }
            }

            return 1;
        }

        count++;
        i--;
        j--;
    }

    return 0;
}

int checkLeftDown(int turn, int posX, int posY, int doAction)
{
    int i = posX + 1;
    int j = posY - 1;
    int count = 1;

    if (board[i][j] != turn * -1)
        return 0;

    while (1)
    {
        if (i >= BOARD_SIZE - 1 || j <= 0)
            break;

        if (board[i + 1][j - 1] == EMPTY)
            return 0;

        if (board[i + 1][j - 1] == board[i][j] * -1)
        {
            if (doAction)
            {
                reverseLeftDown(posX, posY, count);

                if (turn == 1)
                {
                    black += count;
                    white -= count;
                }
                else
                {
                    white += count;
                    black -= count;
                }
            }
            return 1;
        }

        count++;
        i++;
        j--;
    }

    return 0;
}

int checkRightUp(int turn, int posX, int posY, int doAction)
{
    int i = posX - 1;
    int j = posY + 1;
    int count = 1;

    if (board[i][j] != turn * -1)
        return 0;

    while (1)
    {
        if (i <= 0 || j >= BOARD_SIZE - 1)
            break;

        if (board[i - 1][j + 1] == EMPTY)
            return 0;

        if (board[i - 1][j + 1] == board[i][j] * -1)
        {
            if (doAction)
            {

                reverseRightUp(posX, posY, count);

                if (turn == 1)
                {
                    black += count;
                    white -= count;
                }
                else
                {
                    white += count;
                    black -= count;
                }
            }

            return 1;
        }

        count++;
        i--;
        j++;
    }

    return 0;
}

int checkRightDown(int turn, int posX, int posY, int doAction)
{
    int i = posX + 1;
    int j = posY + 1;
    int count = 1;

    if (board[i][j] != turn * -1)
        return 0;

    while (1)
    {
        if (i >= BOARD_SIZE - 1 || j >= BOARD_SIZE - 1)
            break;

        if (board[i + 1][j + 1] == EMPTY)
            return 0;

        if (board[i + 1][j + 1] == board[i][j] * -1)
        {
            if (doAction)
            {
                reverseRightDown(posX, posY, count);

                if (turn == 1)
                {
                    black += count;
                    white -= count;
                }
                else
                {
                    white += count;
                    black -= count;
                }
            }
            return 1;
        }

        count++;
        i++;
        j++;
    }

    return 0;
}

int isValidLocation(char *input, int turn)
{
    int flag = 0;
    int posX, posY;

    char *xCor = strtok(input, "-");
    char *yCor = strtok(NULL, "-");

    posX = *xCor - '1';
    posY = *yCor - 'A';

    if (board[posX][posY] != EMPTY)
        return 0;

    if (checkRight(turn, posX, posY, 1))
        flag = 1;

    if (checkLeft(turn, posX, posY, 1))
        flag = 1;

    if (checkUp(turn, posX, posY, 1))
        flag = 1;

    if (checkDown(turn, posX, posY, 1))
        flag = 1;

    if (checkLeftUp(turn, posX, posY, 1))
        flag = 1;

    if (checkLeftDown(turn, posX, posY, 1))
        flag = 1;

    if (checkRightUp(turn, posX, posY, 1))
        flag = 1;

    if (checkRightDown(turn, posX, posY, 1))
        flag = 1;

    if (flag)
    {
        board[posX][posY] = turn;
        return 1;
    }
    else
        return 0;
}

void getUserInput(int turn)
{
    char input[4] = {'\0'};
    printf("Enter X and Y coordinate. ex)2-B: ");
    scanf("%s", input);
    while (!isValidInput(input))
    {
        printf("Invalid input. Enter valid coordinate: ");
        scanf("%s", input);
    }

    while (!isValidLocation(input, turn))
    {
        printf("Invalid input. Enter valid coordinate: ");
        scanf("%s", input);
    }
}

int isAble(int player)
{
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if (checkLeft(player, i, j, 0))
                return 1;
            if (checkRight(player, i, j, 0))
                return 1;
            if (checkUp(player, i, j, 0))
                return 1;
            if (checkDown(player, i, j, 0))
                return 1;
            if (checkLeftUp(player, i, j, 0))
                return 1;
            if (checkLeftDown(player, i, j, 0))
                return 1;
            if (checkRightUp(player, i, j, 0))
                return 1;
            if (checkRightDown(player, i, j, 0))
                return 1;
        }
    }

    return 0;
}

int isOver()
{
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == EMPTY)
                return 0;
        }
    }

    return 1;
}

int playAgain()
{
    char input;
    printf("\nPlay again? y:Yes n:No: ");
    scanf("%c", &input);

    while (1)
    {
        if (input == 'y')
            return 1;

        else if (input == 'n')
            return 0;

        else
        {
            printf("Invalid input. Enter valid action: ");
            scanf("%c", &input);
        }
    }
}

int main(void)
{
    int turn = BLACK;

    initGame();

    while (1)
    {
        printMap(turn);

        if (!isAble(turn))
        {
            printf("Player cannnot place token. Turn automatically skipped. \n");
            turn *= -1;
            sleep(2);
            continue;
        }

        getUserInput(turn);

        //player placed his/her token, so value should be increased by 1
        if (turn == BLACK)
            black++;
        else
            white++;

        sleep(1);

        if (!isOver())
        {
            turn *= -1;
            continue;
        }
        else
        {
            printMap(turn);

            if (black > white)
                printf("Black wins!! \n\n");
            else if (black < white)
                printf("White wins!! \n\n");
            else
                printf("Draw \n");

            if (playAgain())
            {
                clearBoard();
                initGame();
                continue;
            }
            else
                return 0;
        }
    }

    return 0;
}
