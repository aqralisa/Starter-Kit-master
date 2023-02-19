// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT8L
// Names: AQRA ALISA BINTI RASHIDI |  
// IDs: 1211103093 | 
// Emails: 1211103093@student.mmu.edu.my | 
// Phones: 0162205867  | 
// *********************************************************

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void Introduction()
{
    cout << endl;
    cout << "********** Welcome to Alien vs Zombie Game **********" << endl;
    cout << endl;

    cout << "Please type the following number." << endl;
    cout << "  1 --> Help Menu." << endl;
    cout << "  2 --> New Game." << endl;
    cout << "  3 --> Load Existing Game." << endl;
    cout << "  4 --> Quit." << endl;
    cout << "--> ";
}

void help()

{
    cout << "********** Further Information **********" << endl;
    cout << " The player plays the game by typing commands. The following shows the commands:" << endl;
    cout << " 1) up    --> Alien to move up." << endl;
    cout << " 2) down  --> Alien to move down." << endl;
    cout << " 3) left  --> Alien to move left." << endl;
    cout << " 4) right --> Alien to move right." << endl;
    cout << " 5) arrow --> Switch the direction of an arrow object in the game board." << endl;
    cout << " 6) help  --> List and describe the commands." << endl;
    cout << " 7) save  --> Save the current game to a file." << endl;
    cout << " 8) load  --> Load a saved game from a file." << endl;
    cout << " 9) quit  --> Quit the game while still in play." << endl;
    system("pause");
}

class board
{
private:
    vector<vector<char>> map_;
    int col_, row_, zom_, zom_x, zom_y;

public:
    board(int rows, int columns)
    {
        init(rows, columns);
    }

    int rows, columns, zombies;

    void init(int rows, int columns)
    {
        system("cls");
        cout << "Default game settings:" << endl;
        cout << "----------------------" << endl
             << endl;
        cout << "Board rows    :  5" << endl;
        cout << "Board columns : 15" << endl;
        cout << "Zombie count  :  1" << endl
             << endl;

        char yesno;
        cout << "Do you wish to change the game settings (y/n)? => ";
        cin >> yesno;
        cout << endl;

        if (yesno == 'y')
        {
            system("cls");
            int rows, columns, zombies;
            cout << "Game settings: \n";
            cout << "-------------\n";

            cout << "Insert number of rows: ";
            cin >> rows;

            if (rows % 2 != 0)
            {
                cout << "Insert number of columns: ";
                cin >> columns;

                if (columns % 2 != 0)
                {
                    cout << "Insert number of zombies (min 1, max 9): ";
                    cin >> zombies;

                    cout << endl;
                    col_ = columns;
                    row_ = rows;
                    zom_ = zombies;
                }
                else
                {
                    cout << "Please insert an odd number.";
                }
            }
            else
            {
                cout << "Please insert an odd number.";
            }
        }
        else if (yesno == 'n')
        {
            row_ = 5;
            col_ = 15;
            zom_ = 1;
        }
        else
        {
            cout << "Please enter y or n.\n";
        }

        char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', 'h', 'p', 'r', '>', '<', '^', 'v'};

        int noOfObjects = 13; // number of objects in the objects array

        // create dynamic 2D array using vector
        map_.resize(row_); // create empty rows
        for (int i = 0; i < row_; ++i)
        {
            map_[i].resize(col_); // resize each row
        }

        // put random characters into the vector array
        for (int i = 0; i < row_; ++i)
        {
            for (int j = 0; j < col_; ++j)
            {
                int objNo = rand() % noOfObjects;
                map_[i][j] = objects[objNo];
            }
        }

        // char zombies[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

        // // put zombies
        // for (int n = 0; n < zom_; ++n) // n = 49 = '1' ASCII code
        // {
        //     int zom_x = rand() % col_;
        //     int zom_y = rand() % row_;

        //     char z = zombies[n];
        //     map_[zom_y][zom_x] = z;
        // }
    }

    void display() const
    {
        // comment this out during testing
        system("cls"); // OR system("clear"); for Linux / MacOS

        cout << "  ********************************" << endl;
        cout << "  =       Alien vs Zombie        =" << endl;
        cout << "  ********************************" << endl;

        // for each row
        for (int i = 0; i < row_; ++i)
        {
            // display upper border of the row
            cout << "  ";
            for (int j = 0; j < col_; ++j)
            {
                cout << "+-";
            }
            cout << "+" << endl;

            // display row number
            cout << setw(2) << (row_ - i);
            // display cell content and border of each column
            for (int j = 0; j < col_; ++j)
            {
                cout << "|" << map_[i][j];
            }
            cout << "|" << endl;
        }

        // display lower border of the last row
        cout << "  ";
        for (int j = 0; j < col_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;

        // display column number
        cout << "  ";
        for (int j = 0; j < col_; ++j)
        {
            int digit = (j + 1) / 10;
            cout << " ";
            if (digit == 0)
                cout << " ";
            else
                cout << digit;
        }
        cout << endl;

        cout << "  ";
        for (int j = 0; j < col_; ++j)
        {
            cout << " " << (j + 1) % 10;
        }
        cout << endl
             << endl;
    }

    void zombieland()
    {
        char zombies[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

        // put zombies
        for (int n = 0; n < zom_; ++n) // n = 49 = '1' ASCII code
        {
            int zom_x = rand() % col_ + 1;
            int zom_y = rand() % row_ + 1;

            char z = zombies[n];
            alienland(zom_x, zom_y, z);
        }
    }

    int getrows() const
    {
        return row_;
    }

    int getcolumns() const
    {
        return col_;
    }

    int getzom()
    {
        return zom_;
    }

    char getObjects(int x, int y)
    {
        return map_[row_ - y][x - 1]; // [dimY-srow][scol-1]
    }

    void alienland(int x, int y, char ch)
    {
        map_[row_ - y][x - 1] = ch;
    }

    bool insideMap(int x, int y)
    {
        return (x > 0 && x < col_ && y > 0 && y < row_);
    }

    int getzom_x() const
    {
        return zom_x;
    }

    int getzom_y() const
    {
        return zom_y;
    }
};

class alienturn
{
private:
    int aLife_{100}, aAttack_{0}, x_, y_;
    int zLife_, zAttack_, zRange_;
    bool moves_{1};
    int l1, l2, l3, l4, l5, l6, l7, l8, l9;
    int a1, a2, a3, a4, a5, a6, a7, a8, a9;
    int r1, r2, r3, r4, r5, r6, r7, r8, r9;

public:
    alienturn()
    {
        int zombieLife[] = {100, 120, 150, 180, 200};
        int noOfzLife = 5; // number of life in zombieLife array

        int zombieAttack[] = {5, 10, 15, 20};
        int noOfzAttack = 4; // number of attack in zombieAttack array

        int zombieRange[] = {1, 2, 3, 4, 5};
        int noOfzRange = 5; // number of range in zombieRange array

        l1 = zombieLife[rand() % noOfzLife], a1 = zombieAttack[rand() % noOfzAttack], r1 = zombieRange[rand() % noOfzRange];
        l2 = zombieLife[rand() % noOfzLife], a2 = zombieAttack[rand() % noOfzAttack], r2 = zombieRange[rand() % noOfzRange];
        l3 = zombieLife[rand() % noOfzLife], a3 = zombieAttack[rand() % noOfzAttack], r3 = zombieRange[rand() % noOfzRange];
        l4 = zombieLife[rand() % noOfzLife], a4 = zombieAttack[rand() % noOfzAttack], r4 = zombieRange[rand() % noOfzRange];
        l5 = zombieLife[rand() % noOfzLife], a5 = zombieAttack[rand() % noOfzAttack], r5 = zombieRange[rand() % noOfzRange];
        l6 = zombieLife[rand() % noOfzLife], a6 = zombieAttack[rand() % noOfzAttack], r6 = zombieRange[rand() % noOfzRange];
        l7 = zombieLife[rand() % noOfzLife], a7 = zombieAttack[rand() % noOfzAttack], r7 = zombieRange[rand() % noOfzRange];
        l8 = zombieLife[rand() % noOfzLife], a8 = zombieAttack[rand() % noOfzAttack], r8 = zombieRange[rand() % noOfzRange];
        l9 = zombieLife[rand() % noOfzLife], a9 = zombieAttack[rand() % noOfzAttack], r9 = zombieRange[rand() % noOfzRange];
    };

    void changeArrows(board &b0ard)
    {
        int x, y;
        string arrow;
        char arr[] = {'v', '^', '>', '<'};
        cout << "\nEnter column: ";
        cin >> x;
        cout << "Enter row: ";
        cin >> y;
        cout << "Enter direction: ";
        cin >> arrow;
        char initialdir = b0ard.getObjects(x, y);

        if (initialdir == 'v' || initialdir == '^' || initialdir == '>' || initialdir == '<')
        {
            if (arrow == "down")
            {
                b0ard.alienland(x, y, 'v');
                b0ard.display();
                alienAttributes();
                displayzombieAttributes(b0ard);
                cout << "\nArrow " << initialdir << " is switched to " << arr[0] << ".";
            }
            else if (arrow == "up")
            {
                b0ard.alienland(x, y, '^');
                b0ard.display();
                alienAttributes();
                displayzombieAttributes(b0ard);
                cout << "\nArrow " << initialdir << " is switched to " << arr[1] << ".";
            }
            else if (arrow == "right")
            {
                b0ard.alienland(x, y, '>');
                b0ard.display();
                alienAttributes();
                displayzombieAttributes(b0ard);
                cout << "\nArrow " << initialdir << " is switched to " << arr[2] << ".";
            }
            else if (arrow == "left")
            {
                b0ard.alienland(x, y, '<');
                b0ard.display();
                alienAttributes();
                displayzombieAttributes(b0ard);
                cout << "\nArrow " << initialdir << " is switched to " << arr[3] << ".";
            }
        }
        else
        {
            b0ard.display();
            alienAttributes();
            displayzombieAttributes(b0ard);
            cout << "\nSelected object is not an arrow.\n";
            cout << "Try again.\n";
        }
    }

    void alienUp(board &b0ard, int &x, int &y)
    {
        while (moves_)
        {
            y = y + 1;
            objAlien(b0ard, x, y);
            char getarrow = b0ard.getObjects(x, y);

            if (moves_)
            {
                b0ard.alienland(x, y, 'A');
                b0ard.display();
                b0ard.alienland(x, y - 1, '.');
                b0ard.display();
                alienAttributes();
                displayzombieAttributes(b0ard);

                if (getarrow == '>' || getarrow == '<' || getarrow == '^' || getarrow == 'v')
                {
                    moveArrow(b0ard, getarrow, x, y);
                }
            }
        }

        // else
        // {
        //     y = y - 1;
        // }
    }

    void alienDown(board &b0ard, int &x, int &y)
    {
        while (moves_)
        {
            y = y - 1;
            objAlien(b0ard, x, y);
            char getarrow = b0ard.getObjects(x, y);

            if (moves_)
            {
                b0ard.alienland(x, y, 'A');
                b0ard.display();
                // int Old_y = y + 1;
                b0ard.alienland(x, y + 1, '.');
                b0ard.display();
                alienAttributes();
                displayzombieAttributes(b0ard);

                if (getarrow == '>' || getarrow == '<' || getarrow == '^' || getarrow == 'v')
                {
                    moveArrow(b0ard, getarrow, x, y);
                }
            }
        }

        // else
        // {
        //     y = y + 1;
        // }
    }

    void alienRight(board &b0ard, int &x, int &y)
    {
        while (moves_)
        {
            x = x + 1;
            objAlien(b0ard, x, y);
            char getarrow = b0ard.getObjects(x, y);

            if (moves_)
            {
                b0ard.alienland(x, y, 'A');
                b0ard.display();
                // int Old_x = x - 1;
                b0ard.alienland(x - 1, y, '.');
                b0ard.display();
                alienAttributes();
                displayzombieAttributes(b0ard);

                if (getarrow == '>' || getarrow == '<' || getarrow == '^' || getarrow == 'v')
                {
                    moveArrow(b0ard, getarrow, x, y);
                }
            }
        }

        // else
        // {
        //     x = x - 1;
        // }
    }

    void alienLeft(board &b0ard, int &x, int &y)
    {
        while (moves_)
        {
            x = x - 1;
            objAlien(b0ard, x, y);
            char getarrow = b0ard.getObjects(x, y);

            if (moves_)
            {
                b0ard.alienland(x, y, 'A');
                b0ard.display();
                // int Old_x = x + 1;
                b0ard.alienland(x + 1, y, '.');
                b0ard.display();
                alienAttributes();
                displayzombieAttributes(b0ard);

                if (getarrow == '>' || getarrow == '<' || getarrow == '^' || getarrow == 'v')
                {
                    moveArrow(b0ard, getarrow, x, y);
                }
            }
        }

        // else
        // {
        //     x = x + 1;
        // }
    }

    void alienmovement(board &b0ard, const string &command)
    {
        int x = b0ard.getcolumns() / 2 + 1;
        int y = b0ard.getrows() / 2 + 1; // old_y

        // do
        // {
        if (command == "up") // up
        {
            alienUp(b0ard, x, y);
        }
        else if (command == "down") // down
        {
            alienDown(b0ard, x, y);
        }
        else if (command == "right") // right
        {
            alienRight(b0ard, x, y);
        }
        else if (command == "left") // left
        {
            alienLeft(b0ard, x, y);
        }
        // else if (command == "arrow")
        // {
        //     changeArrows(b0ard);
        // }

        // } while (x != b0ard.getcolumns() && x != 1 && y != b0ard.getrows() & y != 1);
        // cout << endl;
        // cout << "Alien hits a border.\n\n";
        // system("pause");
        // b0ard.display();
        // alienAttributes();
        // zombieAttributes(b0ard);
        // cout << "Alien's turn ends. The trail is reset.\n";
    }

    void alienAttributes()
    {
        cout << "Alien   : ";
        cout << "Life --> " << aLife_ << " ";
        cout << "Attack --> " << setw(3) << aAttack_ << endl;
        cout << endl;
    }

    int getAlife()
    {
        return aLife_;
    }

    int getaAttack()
    {
        return aAttack_;
    }

    int getzlife()
    {
        return zLife_;
    }

    int getzattack()
    {
        return zAttack_;
    }

    int getzrange()
    {
        return zRange_;
    }

    void displayzombieAttributes(board &b0ard)
    {

        int numberofzombies = b0ard.getzom();

        switch (numberofzombies)
        {
        case 1:
            cout << "Zombie 1 : Life --> " << setw(3) << l1 << ", Attack --> " << setw(3) << a1 << ", Range --> " << r1 << endl;
            break;

        case 2:
            cout << "Zombie 1 : Life --> " << setw(3) << l1 << ", Attack --> " << setw(3) << a1 << ", Range --> " << r1 << endl;
            cout << "Zombie 2 : Life --> " << setw(3) << l2 << ", Attack --> " << setw(3) << a2 << ", Range --> " << r2 << endl;
            break;

        case 3:
            cout << "Zombie 1 : Life --> " << setw(3) << l1 << ", Attack --> " << setw(3) << a1 << ", Range --> " << r1 << endl;
            cout << "Zombie 2 : Life --> " << setw(3) << l2 << ", Attack --> " << setw(3) << a2 << ", Range --> " << r2 << endl;
            cout << "Zombie 3 : Life --> " << setw(3) << l3 << ", Attack --> " << setw(3) << a3 << ", Range --> " << r3 << endl;
            break;

        case 4:
            cout << "Zombie 1 : Life --> " << setw(3) << l1 << ", Attack --> " << setw(3) << a1 << ", Range --> " << r1 << endl;
            cout << "Zombie 2 : Life --> " << setw(3) << l2 << ", Attack --> " << setw(3) << a2 << ", Range --> " << r2 << endl;
            cout << "Zombie 3 : Life --> " << setw(3) << l3 << ", Attack --> " << setw(3) << a3 << ", Range --> " << r3 << endl;
            cout << "Zombie 4 : Life --> " << setw(3) << l4 << ", Attack --> " << setw(3) << a4 << ", Range --> " << r4 << endl;
            break;

        case 5:
            cout << "Zombie 1 : Life --> " << setw(3) << l1 << ", Attack --> " << setw(3) << a1 << ", Range --> " << r1 << endl;
            cout << "Zombie 2 : Life --> " << setw(3) << l2 << ", Attack --> " << setw(3) << a2 << ", Range --> " << r2 << endl;
            cout << "Zombie 3 : Life --> " << setw(3) << l3 << ", Attack --> " << setw(3) << a3 << ", Range --> " << r3 << endl;
            cout << "Zombie 4 : Life --> " << setw(3) << l4 << ", Attack --> " << setw(3) << a4 << ", Range --> " << r4 << endl;
            cout << "Zombie 5 : Life --> " << setw(3) << l5 << ", Attack --> " << setw(3) << a5 << ", Range --> " << r5 << endl;
            break;

        case 6:
            cout << "Zombie 1 : Life --> " << setw(3) << l1 << ", Attack --> " << setw(3) << a1 << ", Range --> " << r1 << endl;
            cout << "Zombie 2 : Life --> " << setw(3) << l2 << ", Attack --> " << setw(3) << a2 << ", Range --> " << r2 << endl;
            cout << "Zombie 3 : Life --> " << setw(3) << l3 << ", Attack --> " << setw(3) << a3 << ", Range --> " << r3 << endl;
            cout << "Zombie 4 : Life --> " << setw(3) << l4 << ", Attack --> " << setw(3) << a4 << ", Range --> " << r4 << endl;
            cout << "Zombie 5 : Life --> " << setw(3) << l5 << ", Attack --> " << setw(3) << a5 << ", Range --> " << r5 << endl;
            cout << "Zombie 6 : Life --> " << setw(3) << l6 << ", Attack --> " << setw(3) << a6 << ", Range --> " << r6 << endl;
            break;

        case 7:
            cout << "Zombie 1 : Life --> " << setw(3) << l1 << ", Attack --> " << setw(3) << a1 << ", Range --> " << r1 << endl;
            cout << "Zombie 2 : Life --> " << setw(3) << l2 << ", Attack --> " << setw(3) << a2 << ", Range --> " << r2 << endl;
            cout << "Zombie 3 : Life --> " << setw(3) << l3 << ", Attack --> " << setw(3) << a3 << ", Range --> " << r3 << endl;
            cout << "Zombie 4 : Life --> " << setw(3) << l4 << ", Attack --> " << setw(3) << a4 << ", Range --> " << r4 << endl;
            cout << "Zombie 5 : Life --> " << setw(3) << l5 << ", Attack --> " << setw(3) << a5 << ", Range --> " << r5 << endl;
            cout << "Zombie 6 : Life --> " << setw(3) << l6 << ", Attack --> " << setw(3) << a6 << ", Range --> " << r6 << endl;
            cout << "Zombie 7 : Life --> " << setw(3) << l7 << ", Attack --> " << setw(3) << a7 << ", Range --> " << r7 << endl;
            break;

        case 8:
            cout << "Zombie 1 : Life --> " << setw(3) << l1 << ", Attack --> " << setw(3) << a1 << ", Range --> " << r1 << endl;
            cout << "Zombie 2 : Life --> " << setw(3) << l2 << ", Attack --> " << setw(3) << a2 << ", Range --> " << r2 << endl;
            cout << "Zombie 3 : Life --> " << setw(3) << l3 << ", Attack --> " << setw(3) << a3 << ", Range --> " << r3 << endl;
            cout << "Zombie 4 : Life --> " << setw(3) << l4 << ", Attack --> " << setw(3) << a4 << ", Range --> " << r4 << endl;
            cout << "Zombie 5 : Life --> " << setw(3) << l5 << ", Attack --> " << setw(3) << a5 << ", Range --> " << r5 << endl;
            cout << "Zombie 6 : Life --> " << setw(3) << l6 << ", Attack --> " << setw(3) << a6 << ", Range --> " << r6 << endl;
            cout << "Zombie 7 : Life --> " << setw(3) << l7 << ", Attack --> " << setw(3) << a7 << ", Range --> " << r7 << endl;
            cout << "Zombie 8 : Life --> " << setw(3) << l8 << ", Attack --> " << setw(3) << a8 << ", Range --> " << r8 << endl;
            break;

        case 9:
            cout << "Zombie 1 : Life --> " << setw(3) << l1 << ", Attack --> " << setw(3) << a1 << ", Range --> " << r1 << endl;
            cout << "Zombie 2 : Life --> " << setw(3) << l2 << ", Attack --> " << setw(3) << a2 << ", Range --> " << r2 << endl;
            cout << "Zombie 3 : Life --> " << setw(3) << l3 << ", Attack --> " << setw(3) << a3 << ", Range --> " << r3 << endl;
            cout << "Zombie 4 : Life --> " << setw(3) << l4 << ", Attack --> " << setw(3) << a4 << ", Range --> " << r4 << endl;
            cout << "Zombie 5 : Life --> " << setw(3) << l5 << ", Attack --> " << setw(3) << a5 << ", Range --> " << r5 << endl;
            cout << "Zombie 6 : Life --> " << setw(3) << l6 << ", Attack --> " << setw(3) << a6 << ", Range --> " << r6 << endl;
            cout << "Zombie 7 : Life --> " << setw(3) << l7 << ", Attack --> " << setw(3) << a7 << ", Range --> " << r7 << endl;
            cout << "Zombie 8 : Life --> " << setw(3) << l8 << ", Attack --> " << setw(3) << a8 << ", Range --> " << r8 << endl;
            cout << "Zombie 9 : Life --> " << setw(3) << l9 << ", Attack --> " << setw(3) << a9 << ", Range --> " << r9 << endl;
            break;
        }
    }

    void moveArrow(board &b0ard, char &getarrow, int &x, int &y)
    {
        switch (getarrow)
        {
        case '^':
            alienUp(b0ard, x, y);
            break;

        case 'V':
            alienDown(b0ard, x, y);
            break;

        case '>':
            alienRight(b0ard, x, y);
            break;

        case '<':
            alienLeft(b0ard, x, y);
            break;
        }
    }

    void objAlien(board &b0ard, int &x, int &y)
    {
        // rows and columns after movement

        if (b0ard.getObjects(x, y) == 'h')
        {
            health(b0ard);
        }
        else if (b0ard.getObjects(x, y) == 'p')
        {
            pod(b0ard);
        }
        else if (b0ard.getObjects(x, y) == '^' || b0ard.getObjects(x, y) == 'v' || b0ard.getObjects(x, y) == '>' || b0ard.getObjects(x, y) == '<')
        {
            aAttack_ += 20;
            b0ard.display();
            alienAttributes();
            displayzombieAttributes(b0ard);
            cout << "\nAlien collects an arrow.\n";
            cout << "Alien's attack is increased by 20.\n\n";
            system("pause");
        }
        else if (b0ard.getObjects(x, y) == 'r')
        {
            rock(b0ard, x, y);
        }
        else if (b0ard.getObjects(x, y) == '1' || b0ard.getObjects(x, y) == '2' || b0ard.getObjects(x, y) == '3' ||
                 b0ard.getObjects(x, y) == '4' || b0ard.getObjects(x, y) == '5' || b0ard.getObjects(x, y) == '6' ||
                 b0ard.getObjects(x, y) == '7' || b0ard.getObjects(x, y) == '8' || b0ard.getObjects(x, y) == '9')
        {
            string line;
            ifstream file("zombie_life.txt");
            getline(file, line);
            int zlife = stoi(line);

            b0ard.display();
            alienAttributes();
            zlife = zlife - aAttack_;
            displayzombieAttributes(b0ard);
            cout << "\nAlien hit Zombie " << b0ard.getObjects(x, y) << endl
                 << endl;
            system("pause");
        }
        else if (!b0ard.insideMap(x, y))
        {
            outsidemap(b0ard);
        }
    }

    void outsidemap(board &b0ard)
    {
        cout << "\nAlien hits a border.\n\n";
        system("pause");
        b0ard.display();
        alienAttributes();
        displayzombieAttributes(b0ard);
        cout << "\nAlien's turns end. Trail is reset.\n";
        moves_ = 0;
    }

    void health(board &b0ard)
    {
        if (aLife_ < 100)
        {
            aLife_ += 20;
        }

        b0ard.display();
        alienAttributes();
        displayzombieAttributes(b0ard);
        cout << "\nAlien found a health pack." << endl;
        cout << "Alien's life increase by 20.\n";
        cout << endl;
        system("pause");
    }

    void pod(board &b0ard)
    {
        b0ard.display();
        alienAttributes();
        displayzombieAttributes(b0ard);
        cout << "\nAlien found a pod." << endl;
        cout << "Nearest zombie's life is decreased by 10.\n";
        cout << endl;
        system("pause");
    }

    void rock(board &b0ard, int &x, int &y)
    {
        int objUnderRock[] = {'h', 'p', ' ', '>', '<', '^', 'v'};
        int numOfOURock = 7; // number of objects under rock

        int randRock = rand() % numOfOURock;
        int Rock = objUnderRock[randRock];

        if (Rock == 'h')
        {
            cout << "\nAlien hits a rock." << endl;
            cout << "Alien discover a health pack.\n"
                 << endl;
            system("pause");
            b0ard.alienland(x, y, 'h');
            b0ard.display();
            alienAttributes();
            displayzombieAttributes(b0ard);
            // moves_ = 0;
        }
        else if (Rock == 'p')
        {
            cout << "\nAlien hits a rock." << endl;
            cout << "Alien discover a pod.\n"
                 << endl;
            system("pause");
            b0ard.alienland(x, y, 'p');
            b0ard.display();
            alienAttributes();
            displayzombieAttributes(b0ard);
            // moves_ = 0;
        }
        else if (Rock == ' ')
        {
            cout << "\nAlien hits a rock." << endl;
            cout << "Alien found a white space.\n\n";
            system("pause");
            b0ard.alienland(x, y, ' ');
            b0ard.display();
            alienAttributes();
            displayzombieAttributes(b0ard);
            // moves_ = 0;
        }
        else if (Rock == '>' || '<' || '^' || 'v')
        {
            cout << "\nAlien hits a rock.\n";
            cout << "Alien found an arrow.\n\n";
            system("pause");
            b0ard.alienland(x, y, Rock);
            b0ard.display();
            alienAttributes();
            displayzombieAttributes(b0ard);
        }

        moves_ = 0;
    }
};

class zombieturn
{
private:
    bool moves_{0};
    int zomPosX_, zomPosY_;

public:
    zombieturn(){};

    int zombiePosX() const
    {
        return zomPosX_;
    }

    int zombiePosY() const
    {
        return zomPosY_;
    }

    void zombieAttack(board &b0ard)
    {
        int aLife_{100};
        int z_x = zomPosX_;
        int z_y = zomPosY_;

        string line2;
        ifstream file2("zombie_range.txt");
        string line1;
        ifstream file1("zombie_attack.txt");

        getline(file2, line2);
        int zrange = stoi(line2);
        int attack = stoi(line1);

        if (b0ard.getObjects(z_x + zrange, z_y) == 'A' || b0ard.getObjects(z_x - zrange, z_y) == 'A' || b0ard.getObjects(z_x, z_y + zrange) == 'A' || b0ard.getObjects(z_x, z_y - zrange) == 'A')
        {
            aLife_ = aLife_ - attack;
        }

        moves_ = 1;
    }

    void zombieUp(board &b0ard, alienturn &alien, int &zombieNum)
    {
        int zomPosX_ = b0ard.getzom_x();
        int zomPosY_ = b0ard.getzom_y() + 1;

        if (b0ard.getObjects(zomPosX_, zomPosY_) != 'A' || b0ard.getObjects(zomPosX_, zomPosY_) != zombieNum)
        {
            b0ard.alienland(zomPosX_, zomPosY_, zombieNum);
            b0ard.display();
            alien.alienAttributes();
            alien.displayzombieAttributes(b0ard);
            cout << "\n Zombie " << zombieNum << " moves up.\n\n";
            system("pause");
        }
        else
        {
            randMove(b0ard, alien, zombieNum);
        }
    }

    void zombieDown(board &b0ard, alienturn &alien, int &zombieNum)
    {
        int zomPosX = b0ard.getzom_x();
        int zomPosY = b0ard.getzom_y() - 1;

        if (b0ard.getObjects(zomPosX, zomPosY) != 'A' || b0ard.getObjects(zomPosX_, zomPosY_) != zombieNum)
        {
            b0ard.alienland(zomPosX, zomPosY, zombieNum);
            b0ard.display();
            alien.alienAttributes();
            alien.displayzombieAttributes(b0ard);
            cout << "\n Zombie " << zombieNum << " moves down.\n\n";
            system("pause");
        }
        else
        {
            randMove(b0ard, alien, zombieNum);
        }
    }

    void zombieRight(board &b0ard, alienturn &alien, int &zombieNum)
    {
        int zomPosX = b0ard.getzom_x() + 1;
        int zomPosY = b0ard.getzom_y();

        if (b0ard.getObjects(zomPosX, zomPosY) != 'A' || b0ard.getObjects(zomPosX_, zomPosY_) != zombieNum)
        {
            b0ard.alienland(zomPosX, zomPosY, zombieNum);
            b0ard.display();
            alien.alienAttributes();
            alien.displayzombieAttributes(b0ard);
            cout << "\n Zombie " << zombieNum << " moves right.\n\n";
            system("pause");
        }
        else
        {
            randMove(b0ard, alien, zombieNum);
        }
    }

    void zombieLeft(board &b0ard, alienturn &alien, int &zombieNum)
    {
        int zomPosX = b0ard.getzom_x() - 1;
        int zomPosY = b0ard.getzom_y();

        if (b0ard.getObjects(zomPosX, zomPosY) != 'A' || b0ard.getObjects(zomPosX_, zomPosY_) != zombieNum)
        {
            b0ard.alienland(zomPosX, zomPosY, zombieNum);
            b0ard.display();
            alien.alienAttributes();
            alien.displayzombieAttributes(b0ard);
            cout << "\n Zombie " << zombieNum << " moves left.\n\n";
            system("pause");
        }
        else
        {
            randMove(b0ard, alien, zombieNum);
        }
    }

    void randMove(board &b0ard, alienturn &alien, int &zombieNum)
    {
        int NumofMove = 4;
        int randMove = rand() % 4 + 1;

        switch (randMove)
        {
        case '1':
            zombieUp(b0ard, alien, zombieNum);
            break;
        case '2':
            zombieDown(b0ard, alien, zombieNum);
            break;
        case '3':
            zombieRight(b0ard, alien, zombieNum);
            break;
        case '4':
            zombieLeft(b0ard, alien, zombieNum);
            break;
        }
    }

    void zombiesmovement(board &b0ard, alienturn &alien)
    {
        char objZombie[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

        while (moves_)
        {
            for (int i = 0; i < b0ard.getzom(); ++i)
            {
                int zombieNum = objZombie[i];

                randMove(b0ard, alien, zombieNum);
                zombieAttack(b0ard);
            }
        }
    }
};

string getfillename()
{
    string newfile;

    cout << "Name your file -> ";
    cin >> newfile;
    cout << endl;
    return newfile;
}

void savefile(string file)
{

    int rows, colums;
    board b0ard = board(rows, colums);
    alienturn alien;
    zombieturn zombie;
    fstream gamefile;
    string file1;

    int srows = b0ard.getrows();
    int scols = b0ard.getcolumns();
    int szoms = b0ard.getzom();

    file1 = ".\\alienzombiefiles" + getfillename();
    gamefile.open(file1, ios::out);

    if (gamefile.is_open())
    {
        gamefile << "\nEH" << srows << "\nEA" << scols << "\nEB" << szoms;

        int currentaLife = alien.getAlife();
        int currentaAttack = alien.getaAttack();
        gamefile << "\nEH" << currentaLife << "\nEA" << currentaAttack;

        gamefile.close();
        cout << "Game saved successfully." << endl;
    }
}

void start();

void gameCommand(board &b0ard, alienturn &alien, zombieturn &zombie)
{
    // do
    // {
    string command;
    cout << "\nCommand> ";
    cin >> command;

    if (command == "up" || "down" || "right" || "left")
    {
        alien.alienmovement(b0ard, command);
        zombie.zombiesmovement(b0ard, alien);
    }
    else if (command == "arrow")
    {
        alien.changeArrows(b0ard);
    }
    else if (command == "help")
    {
        help();
    }
    else if (command == "load")
    {
        /* code */
    }
    else if (command == "save")
    {
        getfillename();
        string newfile;
        savefile(newfile);
    }
    else if (command == "quit")
    {
        char yesno;
        cout << "Exit the game? (y/n) --> ";
        cin >> yesno;

        if (yesno == 'y')
        {
            exit(0);
        }
        else if (yesno == 'n')
        {
            start();
        }
    }
}

void start()
{
    int rows, columns;
    board b0ard = board(rows, columns);
    cout << "rows = " << b0ard.getrows() << endl;

    cout << "columns = " << b0ard.getcolumns() << endl;

    b0ard.alienland(b0ard.getcolumns() / 2 + 1, b0ard.getrows() / 2 + 1, 'A');
    b0ard.zombieland();
    b0ard.display();

    alienturn alien;
    zombieturn zombie;

    alien.alienAttributes();
    alien.displayzombieAttributes(b0ard);

    // alien.alienmovement(b0ard, command);
    // zombie.zombiesmovement(b0ard, alien);

    while (true)
    {
        gameCommand(b0ard, alien, zombie);
    }
}

int main()
{
    bool done = false;
    srand(time(NULL));
    cout << "                   Assignment Part 1" << endl;
    cout << "                   Let's Get Started!" << endl;

    Introduction();
    char yesno;
    char playerscommand;
    cin >> playerscommand;

    switch (playerscommand)
    {
    case '1': // help menu
        cout << endl;
        help();

    case '2': // start game
        start();
        cout << endl;
        // Introduction();
        break;

    case '3': // load existing game
        cout << "Not Finished yet." << endl;
        break;

    case '4':
        cout << "Exit the game? (y/n) --> ";
        cin >> yesno;

        if (yesno == 'y')
        {
            exit(0);
        }
        else if (yesno == 'n')
        {
            start();
        }
    }
    cout << endl;
}
