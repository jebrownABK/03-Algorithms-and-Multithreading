// Ch03Multithreading.cpp : This file contains the 'main' function. Program execution begins and ends there.
// TODO: try adding a couple threads. Another thread updating a number and when you display display both and see if they are in sync (they shouldn't be)

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

static int HeapInt = 0;

bool DidQuit = false; //important to use this variable in both threads
//int ThreadVar = 0;
//int ThreadVar2 = 0;

bool ShouldDecrementLife = false;

struct Character
{
    float Position = 0.0f;
    int Score = 0;
    int Lives = 1;

    void DisplayStats()
    {
        cout << "Lives: " << Lives << endl;
    }
};

Character Player; //shared between all threads

void UpdateCharacter1()
{
    while (!DidQuit)
    {
        if (ShouldDecrementLife)
        {
            if (Player.Lives > 0) //at this point, PL > 0
            {
                //this_thread::sleep_for(chrono::milliseconds(500)); //will cause PL to be -1 if we decrement once. Nothing is locked, so the other function will also sleep and decrement. fix this by using a lock
                //this_thread::yield(); //yield causes same result as above
                --Player.Lives;
            }
        }
    }
}

void UpdateCharacter2()
{
    while (!DidQuit)
    {
        if (ShouldDecrementLife)
        {
            if (Player.Lives > 0)
            {
                //this_thread::sleep_for(chrono::milliseconds(500));
                //this_thread::yield();
                --Player.Lives;
            }
        }
    }
}

void ProcessInput()
{
    while (!DidQuit)
    {
        cout << "'a' to decrement player life" << endl;
        cout << "'d' to display player stats" << endl;
        cout << "'q' to quit" << endl;
        char UserInput;
        cin >> UserInput;
        switch (UserInput)
        {
        case 'a':
            ShouldDecrementLife = true;
            break;
        case 'd':
            Player.DisplayStats();
            break;
        case 'q':
            DidQuit = true;
            break;
        default:
            break;
        }
        DidQuit = (UserInput == 'q');
    }
}

/*void HelloWorldThread()
{
    //one off threads are fine, but normally we want something always running in the background
    //cout << "hello world thread" << endl;
    while (!DidQuit)
    {
        ThreadVar++;
        if (ThreadVar > 1000)
        {
            ThreadVar = 0;
        }
    }
}

void UpdateNumberThread()
{
    while (!DidQuit)
    {
        ThreadVar2++;
        if (ThreadVar2 > 1000)
        {
            ThreadVar2 = 0;
        }
    }
}
*/

int main()
{
    //HeapInt = 5; // now HeapInt has a memory address
    /*
    cout << "Hello world!" << endl;
    char UserInput;
    thread Hello(HelloWorldThread);
    thread UpdateNumber(UpdateNumberThread);

    while (!DidQuit)
    {
        cout << "enter any key to display counter" << endl;
        cout << "q to quit" << endl;
        cin >> UserInput; // thing will execute beyond this point until we get this input
        DidQuit = (UserInput == 'q');
        cout << "ThreadVar: " << ThreadVar << endl;
        cout << "ThreadVar2: " << ThreadVar2 << endl;
    }

    Hello.join(); //you cannot go beyond this line of code until HEllo() is done
    // .joim() is conterintuitive to multithreading because you're always waiting
    // rather than always doing something when possible
    */
    //UpdateNumber.join();

    thread InputHandler(ProcessInput);
    thread CharacterUpdate1(UpdateCharacter1);
    thread CharacterUpdate2(UpdateCharacter2);

    InputHandler.join();
    CharacterUpdate1.join();
    CharacterUpdate2.join();

    return 0;
}
