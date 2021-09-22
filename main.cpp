#include <iostream>
#include <windows.h>

#define SIZE 20

// Point class
class Point
{
public:
    int x, y;
    char c;
    bool shift;    
};

// Counting point neighbours
int countNeighbours(Point (*matrix)[SIZE], int x, int y)
{
    int neighbours = 0;

    if (matrix[y][x].c == 'O')
        neighbours -= 1;
    
    for (int i = y - 1; i <= y + 1; i++)
    {
        for (int j = x - 1; j <= x + 1; j++)
        {
            if (matrix[i][j].c == 'O')
                neighbours += 1;
        }
    }

    return neighbours;
}

// Printing matrix function
void printMatrix(Point (*matrix)[SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            std::cout << matrix[i][j].c;
        }
        std::cout << std::endl;
    }
}

int main()
{
    // Screen setup
    CONSOLE_FONT_INFOEX console_font = {0};
    console_font.cbSize = sizeof console_font;
    console_font.dwFontSize.X = 8;
    console_font.dwFontSize.Y = 8;
    wcscpy(console_font.FaceName, L"Terminal");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, &console_font);

    Point matrix[SIZE][SIZE];

    // Initializing matrix
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            matrix[i][j].c = ' ';
            matrix[i][j].shift = false;
        }
    }

    // Adding points
    matrix[4][5].c = 'O';
    matrix[4][6].c = 'O';
    matrix[4][7].c = 'O';
    matrix[3][7].c = 'O';
    matrix[2][6].c = 'O';

    while (true)
    {
        // Printing matrix
        printMatrix(matrix);

        // Updating field
        for (int i = 1; i < SIZE - 1; i++)
        {
            for (int j = 1; j < SIZE - 1; j++)
            {
                if (matrix[i][j].c == ' ' && countNeighbours(matrix, j, i) == 3)
                    matrix[i][j].shift = true;
                else if (matrix[i][j].c == 'O' && !(countNeighbours(matrix, j, i) == 2 || countNeighbours(matrix, j, i) == 3))
                    matrix[i][j].shift = true;
            }
        }

        for (int i = 1; i < SIZE - 1; i++)
        {
            for (int j = 1; j < SIZE - 1; j++)
            {
                if (matrix[i][j].c == ' ' && matrix[i][j].shift)
                {
                    matrix[i][j].c = 'O';
                    matrix[i][j].shift = false;
                }
                else if (matrix[i][j].c == 'O' && matrix[i][j].shift)
                {
                    matrix[i][j].c = ' ';
                    matrix[i][j].shift = false;
                }
            }
        }
        Sleep(1000);
        system("cls");
    }
}