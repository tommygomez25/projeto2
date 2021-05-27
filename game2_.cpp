// game2_.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "Game.h"
#include "LeaderBoard.h"

using namespace std;
void menu();

void ctrlzexit() {
    if (cin.eof())
    {
        cout << "bye ...";
        exit(0);
    }
}
void playagain() {
    int selection;
    cout << "1)Go back \n0)Exit" << endl; cin >> selection;
    while (!cin || selection < 0 || selection > 1) {
        ctrlzexit();
        cin.clear();
        cin.ignore(9999, '\n');
        cout << "Enter a correct input.\n1)Go back \n0)Exit" << endl; cin >> selection;
    }
    if (selection == 1) {
        menu();
    }
    else if (selection == 0) {
        exit(0);

    }
}

void save(Game g1, LeaderBoard l1) {
    string name;
    cout << "Enter your name: "; cin.ignore(); getline(cin, name);
    while (name.size()>15){
        ctrlzexit();
        cin.clear();
        cout << "Enter a correct input.\nEnter your name: "; cin.ignore(); getline(cin, name);
    }
    l1.addLine(name, g1.getscore());
    l1.display();
}


void saveselect(Game g1, LeaderBoard l1) {
    int saveselect;
    cout << "1)Save score \n2)Go back \n0)Exit" << endl; cin >> saveselect;
    while (!cin || saveselect < 0 || saveselect > 2) {
        ctrlzexit();
        cin.clear();
        cin.ignore(9999, '\n');
        cout << "Enter a correct input.\n1)Save score \n2)Go back \n0)Exit" << endl; cin >> saveselect;
    }
    if (saveselect == 1) {
        save(g1, l1);
        playagain();
    }
    else if (saveselect == 2)
        menu();
    else if (saveselect == 0)
        exit(0);
}


void clear()
{
    cout << "\x1B[2J\x1B[H";
}

void rules() {
    int value;
    clear();
    vector<string> vec;
    int i = 0;
    string lines;
    ifstream infile("RULES.txt");
    while (getline(infile, lines)) {
        if (lines.size() > 0)
            vec.push_back(lines);
    }
    infile.close();
    for (string& line : vec)
        cout << line << endl;
    cout << "Press 0 if you want to go to the menu again. "; cin >> value;
    while (value != 0) {
        ctrlzexit();
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Press 0 if you want to go to the menu again. "; cin >> value;
    }
    menu();
}

bool verifyfile(string maze_value) {
    ifstream infile("MAZE_" + maze_value + ".txt"); // abrir stream para ler o ficheiro 
    if (infile) 
        return true;
    return false;
}

bool verifysavefile(string maze_value) {
    ifstream infile("MAZE_" + maze_value + "_WINNERS.txt"); // abrir stream para ler o ficheiro 
    if (infile)
        return true;
    return false;
}

void menu()
{
    clear();

    int selection;
    cout << "1)Rules \n2)Play \n3)Winners \n0)Exit" << endl;
    cin >> selection;
    while (!cin || selection < 0 || selection > 3) {
        ctrlzexit();
        cin.clear();
        cin.ignore(99999, '\n');
        cout << "1)Rules \n2)Play \n3)Winners \n0)Exit" << endl;
        cin >> selection;
    }
    if (selection == 0) {
        exit(0);
    }
    else if (selection == 1) {
        rules();
    }
    else if (selection == 2) {
        Game g1;
        LeaderBoard l1;
        string maze_value;
        cout << "What's the maze number you want to play? " << endl; cin >> maze_value;
        while (!cin) {
            ctrlzexit();
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "Enter a correct input.\nWhat's the maze number you want to play?" << endl; cin >> maze_value;
        }

        if (verifyfile(maze_value)){
            g1 = Game(maze_value);
            l1 = LeaderBoard(maze_value);
            g1.play();
            if (g1.player_wins()) {
                saveselect(g1, l1);
            }
            else
                playagain();
        }
        else {
            cout << "File doesn't exist" << endl;
            playagain();
        }
    }
    else if (selection == 3) {
        LeaderBoard l1;
        string maze_value;
        cout << "What's the maze number? " << endl; cin >> maze_value;
        while (!cin) {
            ctrlzexit();
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "Enter a correct input.\nWhat's the maze number you want to play?" << endl; cin >> maze_value;
        }

        if (verifysavefile(maze_value)) {
            l1 = LeaderBoard(maze_value);
            l1.display();
            playagain();
        }
        else{
            cout << "file doesn't exist" << endl;
            playagain();
        }

    }
}
int main() {
    menu();
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
