////////////////////////////////////////////////////////////////////////////
// 
// SimpleFireGen.cpp 
// @Al.exe
// 
////////////////////////////////////////////////////////////////////////////
// 
// This program creates a 2D array to represent the fire display,
// and starts by filling the bottom row with fire particles.
// 
// It then simulates the fire spreading upwards by randomly 
// spreading particles from each cell to neighboring cells.
// 
// Finally, it displays the fire using a special ANSI escape 
// sequence to change the color of the fire particles to orange.
// 
////////////////////////////////////////////////////////////////////////////



#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>



using namespace std;


const int WIDTH = 32;
const int HEIGHT = 32;
const int NUM_SYMBOLS = 16;



int fire[HEIGHT][WIDTH] = { 0 };
char symbolsArr[NUM_SYMBOLS] = { ' ', '.', ':', '\'', '\"', ';', '^', '*', '+', '=', 'x', '%', '&', '@', '$', '#' };



////////////////////////////////////////////////////////////////////////////
// check your OS
////////////////////////////////////////////////////////////////////////////
int defOS()
{
    /* Windows OS is selected as default */
    int os = 0;
    ofstream f_wind("/usr/lib/systemd");
    /* if OS is Unix based */
    if (f_wind.is_open())
    {
        os = 1;
    }
    /* if OS is Windows */
    else
    {
        os = 0;
    }
    return os;
}



void initializeFire()
{
    // Fill the bottom row with maximum intensity
    for (int i = 0; i < WIDTH; i++)
    {
        fire[HEIGHT - 1][i] = NUM_SYMBOLS - 1;
    }
}



void updateFire()
{
    for (int y = 0; y < HEIGHT - 1; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            int decay = rand() % 3;
            int spread = rand() % 3 - 1;
            int newIntensity = fire[y + 1][x - spread] - decay;
            if (newIntensity < 0)
            {
                newIntensity = 0;
            }
            fire[y][x] = newIntensity;
        }
    }
}



void renderFire()
{
    ////////////////////////////////////////////////////////////////////////////
    // simple rendering
    ////////////////////////////////////////////////////////////////////////////
    //for (int y = 0; y < HEIGHT; y++)
    //{
    //    for (int x = 0; x < WIDTH; x++)
    //    {
    //        cout << symbolsArr[fire[y][x]];
    //    }
    //    cout << endl;
    //}

    ////////////////////////////////////////////////////////////////////////////
    // colored rendering
    ////////////////////////////////////////////////////////////////////////////
    int intensityLevels = HEIGHT / 4;
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            int intensity = fire[y][x];
            if (intensity == 0) {
                // Dark Red
                cout << "\033[31m";
            }
            else if (intensity < intensityLevels/2) {
                // Light Yellow
                cout << "\033[93m";
            }
            else if (intensity < intensityLevels) {
                // Dark Yellow
                cout << "\033[33m";
            }
            else if (intensity < intensityLevels * 1.5) {
                // Light Red
                cout << "\033[91m";
            }
            else if (intensity < intensityLevels * 2) {
                // Dark Red
                cout << "\033[31m";
            }
            else {
                // White
                cout << "\033[97m";
            }
            cout << symbolsArr[intensity];
        }
        cout << "\033[0m" << endl; // Reset color
    }
}



////////////////////////////////////////////////////////////////////////////
// initialize application 
////////////////////////////////////////////////////////////////////////////
int main()
{
    system("Color 06");
    initializeFire();

    if (defOS() == 0)
    {
        while (true)
        {
            updateFire();
            renderFire();
            this_thread::sleep_for(chrono::milliseconds(50));
            system("cls"); // Clear the console
        }
    }
    else
    {
        while (true)
        {
            updateFire();
            renderFire();
            this_thread::sleep_for(chrono::milliseconds(50));
            system("clear"); // Clear the console
        }
    }

    return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
