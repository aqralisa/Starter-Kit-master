#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
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
}

class board
{
private:
    vector<vector<char>> map_;
    int col_, row_, zom_;

public:
    board(int rows, int columns)
    {
        init(rows, columns);
    }

    int rows, columns, zombies;

    void init(int rows, int columns)
    {
        cout << endl;
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
            int rows, columns, zombies;
            cout << "Game settings: ";
            cout << endl;

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

        // put zombies
        for (int n = 49; n < zom_ + 49; ++n) // n = 49 = '1' ASCII code
        {
            char z = char(n);
            map_[rand() % row_][rand() % col_] = z;
        }
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

};

class alienturn
{
private:
    int aLife_{100}, aAttack{0};
    int zLife_, zAttack_, zRange_;

public:
    alienturn(){};

    void moveUp(board &b0ard, int &x, int &y)
    {
        b0ard.alienland(x, y, 'A');
        b0ard.display();
        int Old_y = y - 1;
        b0ard.alienland(x, Old_y, '.');
        b0ard.display();
        alienAttributes();
        zombieAttributes(b0ard);
    }

    void moveDown(board &b0ard, int &x, int &y)
    {
        b0ard.alienland(x, y, 'A');
        b0ard.display();
        int Old_y = y + 1;
        b0ard.alienland(x, Old_y, '.');
        b0ard.display();
        alienAttributes();
        zombieAttributes(b0ard);
    }

    void moveRight(board &b0ard, int &x, int &y)
    {
        b0ard.alienland(x, y, 'A');
        b0ard.display();
        int Old_x = x - 1;
        b0ard.alienland(Old_x, y, '.');
        b0ard.display();
        alienAttributes();
        zombieAttributes(b0ard);
    }

    void moveLeft(board &b0ard, int &x, int &y)
    {
        b0ard.alienland(x, y, 'A');
        b0ard.display();
        int Old_x = x + 1;
        b0ard.alienland(Old_x, y, '.');
        b0ard.display();
        alienAttributes();
        zombieAttributes(b0ard);
    }

    void changeArrows(board &b0ard)
    {
        int x, y;
        char arrow;
        char arr[] = {'v', '^', '>', '<'};
        cout << "Enter column: ";
        cin >> x;
        cout << "Enter row: ";
        cin >> y;
        cout << "Enter direction: ";
        cin >> arrow;
        char initialdir = b0ard.getObjects(x, y);

        if (initialdir == 'v' || initialdir == '^' || initialdir == '>' || initialdir == '<')
        {
            if (arrow == arr[0])
            {
                b0ard.alienland(x, y, 'v');
                b0ard.display();
                cout << "Arrow " << initialdir << " is switched to " << arr[0] << '.';
            }
            else if (arrow == arr[1])
            {
                b0ard.alienland(x, y, '^');
                b0ard.display();
                cout << "Arrow " << initialdir << " is switched to " << arr[1] << '.';
            }
            else if (arrow == arr[2])
            {
                b0ard.alienland(x, y, '>');
                b0ard.display();
                cout << "Arrow " << initialdir << " is switched to " << arr[2] << '.';
            }
            else if (arrow == arr[3])
            {
                b0ard.alienland(x, y, '<');
                b0ard.display();
                cout << "Arrow " << initialdir << " is switched to " << arr[3] << '.';
            }
        }
        else
        {
            b0ard.display();
            cout << "Selected object is not an arrow.\n";
            cout << "Try again.\n";
        }
    }

    void alienmovement(board &b0ard)
    {
        int x = b0ard.getcolumns() / 2 + 1;
        int y = b0ard.getrows() / 2 + 1; // old_y

        do
        {
            string command;
            cout << endl;
            cout << "Command: ";
            cin >> command;

            if (command == "up") // up
            {
                y = y + 1;
                objAlien(b0ard, x, y);
                cout << endl;
                system("pause");
                moveUp(b0ard, x, y);
                //objAlien(b0ard, x, y);
            }
            else if (command == "down") // down
            {
                y = y - 1;
                objAlien(b0ard, x, y);
                cout << endl;
                system("pause");
                moveDown(b0ard, x, y);
            }
            else if (command == "right") // right
            {
                x = x + 1;
                objAlien(b0ard, x, y);
                cout << endl;
                system("pause");
                moveRight(b0ard, x, y);
            }
            else if (command == "left") // left
            {
                x = x - 1;
                objAlien(b0ard, x, y);
                system("pause");
                moveLeft(b0ard, x, y);
            }
            else if (command == "arrow")
            {
                changeArrows(b0ard);
            }
        } while (x != b0ard.getcolumns() && x != 1 && y != b0ard.getrows() & y != 1);
        cout << endl;
        cout << "Alien hits a border.\n\n";
        system("pause");
        cout << "Alien's turn ends. The trail is reset.";
    }

    void alienAttributes()
    {
        cout << "Alien   : ";
        cout << "Life --> " << aLife_ << " ";
        cout << "Attack --> " << setw(3) << aAttack << endl;
        cout << endl;
    }

    void zombieAttributes(board &b0ard)
    {
        for (int z = 1; z < b0ard.getzom() + 1; ++z)
        {
            int zombieLife[] = {100, 120, 150, 180, 200};
            int noOfzLife = 5; // number of life in zombieLife array

            int zombieAttack[] = {5, 10, 15, 20};
            int noOfzAttack = 4; // number of attack in zombieAttack array

            int zombieRange[] = {1, 2, 3, 4, 5};
            int noOfzRange = 5; // number of range in zombieRange array

            zLife_ = rand() % noOfzLife;
            zAttack_ = rand() % noOfzAttack;
            zRange_ = rand() % noOfzRange;

            int zLife = zombieLife[zLife_];
            int zAttack = zombieAttack[zAttack_];
            int zRange = zombieRange[zRange_];

            cout << "Zombie " << z << ": "
                 << "Life --> " << setw(3) << zLife << " "
                 << "Attack --> " << setw(3) << zAttack << " "
                 << "Range --> " << zRange << endl;
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
        else if (b0ard.getObjects(x, y) == 'r')
        {
            rock(b0ard, x, y);
        }
        else if (b0ard.getObjects(x, y) == '^')
        {
            cout << "Alien collects an arrow.\n";
            cout << "Alien's attack is increased by 20.\n";
            system("pause");
            b0ard.alienland(x, y, '.');
            y = y + 1;
            //system("pause");
            b0ard.alienland(x, y, 'A');
            //b0ard.display();
            //y = y -1;
            //b0ard.alienland(x, y, '.');
            alienAttributes();
            zombieAttributes(b0ard);
            //moveUp(b0ard, x, y);
            //y = y - 1;
            //b0ard.alienland(x, y, '.');
            //moveUp(b0ard, x, y);
            b0ard.display();
            alienAttributes();
            zombieAttributes(b0ard);
        }

        else if (b0ard.getObjects(x, y) == 'v')
        {
            
            cout << "Alien collects an arrow.\n";
            cout << "Alien's attack is increased by 20.\n";
            system("pause");
            moveDown(b0ard, x, y);
            y = y - 1;
            b0ard.alienland(x, y, 'A');
            b0ard.display();
            y = y + 1;
            b0ard.alienland(x, y, '.');
            b0ard.display();
        }

        else if (b0ard.getObjects(x, y) == '>')
        {
            // x = x - 1;
            b0ard.display();
            alienAttributes();
            zombieAttributes(b0ard);
            cout << "Alien collects an arrow.\n";
            cout << "Alien's attack is increased by 20.\n";
            system("pause");
            x = x + 1;
            b0ard.alienland(x, y, 'A');
            b0ard.display();
            x = x - 1;
            b0ard.alienland(x, y, '.');
            b0ard.display();
        }

        else if (b0ard.getObjects(x, y) == '<')
        {
            // x = x + 1;
            b0ard.display();
            alienAttributes();
            zombieAttributes(b0ard);
            cout << "Alien collects an arrow.\n";
            cout << "Alien's attack is increased by 20.\n";
            system("pause");
            x = x - 1;
            b0ard.alienland(x, y, 'A');
            //b0ard.display();
            x = x + 1;
            b0ard.alienland(x, y, '.');
            b0ard.display();
            

        }
    }

    void health(board &b0ard)
    {
        if (aLife_ < 100)
        {
            aLife_ += 20;
        }

        b0ard.display();
        alienAttributes();
        zombieAttributes(b0ard);
        cout << "Alien found a health pack." << endl;
        cout << "Alien's life increase by 20.";
        cout << endl;
    }

    void pod(board &b0ard)
    {
        b0ard.display();
        alienAttributes();
        zombieAttributes(b0ard);
        cout << "Alien found a pod." << endl;
        cout << "Nearest zombie's life is decreased by 10.";
        cout << endl;
    }

    void rock(board &b0ard, int &x, int &y)
    {
        int objUnderRock[] = {'h', 'p', ' '};
        int numOfOURock = 3; // number of objects under rock

        int randRock = rand() % numOfOURock;
        int Rock = objUnderRock[randRock];

        if (Rock == 'h')
        {
            cout << "Alien hits a rock." << endl;
            cout << "Alien discover a health pack." << endl;
            system("pause");
            b0ard.alienland(x, y, 'h');
            b0ard.display();
            alienAttributes();
            zombieAttributes(b0ard);
        }
        else if (Rock == 'p')
        {
            cout << "Alien hits a rock." << endl;
            cout << "Alien discover a pod." << endl;
            system("pause");
            b0ard.alienland(x, y, 'p');
            b0ard.display();
            alienAttributes();
            zombieAttributes(b0ard);
        }
        else if (Rock == ' ')
        {
            cout << "Alien hits a rock." << endl;
            cout << "Alien found a white space.";
            system("pause");
            b0ard.alienland(x, y, ' ');
            b0ard.display();
            alienAttributes();
            zombieAttributes(b0ard);
        }
    }
};

class zombieturn
{

public:
    zombieturn(){};

    void zombiesmovement(board &b0ard, alienturn &alien)
    {
        int x, y;
        char obj;

        for (int n = 49; n < b0ard.getzom() + 49; ++n)
        {
            char z = char(n);
            for (y = 1; y < b0ard.getrows() + 1; ++y)
            {
                for (x = 1; x < b0ard.getcolumns() + 1; ++x)
                {
                    obj = b0ard.getObjects(x, y);
                    if (obj == z)
                    {
                        int move[] = {x - 1, x + 1, y - 1, y + 1};
                        int numofmove = 4;
                        int randmove = rand() & 4;
                        int dir = move[randmove]; // direction

                        if (dir == move[0])
                        {
                            b0ard.alienland(move[0], y, z);
                            b0ard.display();
                            b0ard.alienland(x, y, ' ');
                            b0ard.display();
                            alien.alienAttributes();
                            alien.zombieAttributes(b0ard);
                            cout << "Zombie " << z << " moves left.";
                        }
                        else if (dir == move[1])
                        {
                            b0ard.alienland(move[1], y, z);
                            b0ard.display();
                            b0ard.alienland(x, y, ' ');
                            b0ard.display();
                            alien.alienAttributes();
                            alien.zombieAttributes(b0ard);
                            cout << "Zombie " << z << " moves right.";
                        }
                        else if (dir == move[2])
                        {
                            b0ard.alienland(move[2], y, z);
                            b0ard.display();
                            b0ard.alienland(x, y, ' ');
                            b0ard.display();
                            alien.alienAttributes();
                            alien.zombieAttributes(b0ard);
                            cout << "Zombie " << z << " moves down.";
                        }
                        else if (dir == move[3])
                        {
                            b0ard.alienland(move[3], y, z);
                            b0ard.display();
                            b0ard.alienland(x, y, ' ');
                            b0ard.display();
                            alien.alienAttributes();
                            alien.zombieAttributes(b0ard);
                            cout << "Zombie " << z << " moves up.";
                        }
                    }
                }
            }
        }
    }
};

void start()
{
    int rows, columns;
    board b0ard = board(rows, columns);
    cout << "rows = " << b0ard.getrows() << endl;

    cout << "columns = " << b0ard.getcolumns() << endl;

    b0ard.alienland(b0ard.getcolumns() / 2 + 1, b0ard.getrows() / 2 + 1, 'A');
    b0ard.display();

    alienturn alien;
    zombieturn zombie;

    alien.alienAttributes();
    alien.zombieAttributes(b0ard);

    alien.alienmovement(b0ard);
    zombie.zombiesmovement(b0ard, alien);
}

// void load()
// {
//     std::ofstream outfile;
//     outfile.open("example.txt");
//     outfile << "Hello, World!" << std::endl;
//     outfile.close();

// }

int main()
{
    srand(time(NULL));
    cout << "                   Assignment Part 1" << endl;
    cout << "                   Let's Get Started!" << endl;

    Introduction();
    char yesno;
    char playerscommand;
    cin >> playerscommand;

    switch (playerscommand)
    {
    case '1': //help menu
        cout << endl;
        help();

    case '2': //start game
        start();
        cout << endl;
        Introduction();
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
