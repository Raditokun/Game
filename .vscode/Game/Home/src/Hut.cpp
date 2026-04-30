#include <graphics.h>
#include <conio.h>
#include <iostream>

using namespace std;

int main() {
    int gd = DETECT, gm;
    initwindow(800, 600, "Image Test Debugger");

    // We are going to print some text first so you know it's running
    outtextxy(10, 10, "Attempting to load image...");
    outtextxy(10, 30, "If the screen stays black behind this text, the path is wrong.");
    
    // --- TEST PATH 1: The Relative Path (What we tried before) ---
    // readimagefile("../media/dia_1.bmp", 0, 0, 800, 600);

    // --- TEST PATH 2: The VS Code Root Path ---
    // (If VS Code is running from the 'Home' folder instead of 'src')
    // readimagefile("media/dia_1.bmp", 0, 0, 800, 600);

    // --- TEST PATH 3: The "Sanity Check" Absolute Path ---
    // This tells the computer EXACTLY where the file is on your hard drive.
    // If this fails, the issue isn't the path; it's the image file itself.
    readimagefile("D:/RADIT Files/code/prolanvs/.vscode/Game/Home/media/dia_1.bmp", 0, 0, 800, 600);

    outtextxy(10, 50, "Press any key to exit.");

    getch(); // Waits for you to press a keyboard key
    closegraph();
    return 0;
}