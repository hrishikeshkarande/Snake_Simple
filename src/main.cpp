#include <iostream>
#include <conio.h>
#include <windows.h>

#define WIDTH 50
#define HEIGHT 25


#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void cls()
{
    // Get the Win32 handle representing standard output.
    // This generally only has to be done once, so we make it static.
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD topLeft = { 0, 0 };

    // std::cout uses a buffer to batch writes to the underlying console.
    // We need to flush that to the console because we're circumventing
    // std::cout entirely; after we clear the console, we don't want
    // stale buffered text to randomly be written out.
    std::cout.flush();

    // Figure out the current width and height of the console window
    if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
        // TODO: Handle failure!
        abort();
    }
    DWORD length = csbi.dwSize.X * csbi.dwSize.Y;
    
    DWORD written;

    // Flood-fill the console with spaces to clear it
    FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

    // Reset the attributes of every character to the default.
    // This clears all background colour formatting, if any.
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

    // Move the cursor back to the top left for the next sequence of writes
    SetConsoleCursorPosition(hOut, topLeft);
}

// x is the column, y is the row. The origin (0,0) is top-left.
void setCursorPosition(int x, int y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}


int x =10, y = 10;
void board(){
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            if(j == 0 || j == WIDTH-1 || i == 0 || i == HEIGHT-1) std::cout << '#';
            else std::cout << ' ';
        }
        std::cout << std::endl;
    }
}

void move(){
    switch (_getch())
    {
    case 'a':
        // dir = LEFT;
        x--;
        break;
    case 'd':
        // dir = RIGHT;
        x++;
        break;
    case 's':
        // dir = DOWN;
        y--;
        break;
    case 'w':
        // dir = UP;
        y++;
        break;
    
    default:
        break;
    }
}


int main() {
    while(1){
        board();
        if(_kbhit()){
            move();
        };
    }
}