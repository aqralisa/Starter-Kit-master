// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT3L 
// Names: AQRA ALISA BINTI RASHIDI | MEMBER_NAME_2 
// IDs: 1211103093 | MEMBER_ID_2 
// Emails: 1211103093@student..mu.edu.my | MEMBER_EMAIL_2 
// Phones: 0162205867 | MEMBER_PHONE_2  
// ********************************************************* 

// TODO: Fill in the missing information above and delete this line.

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()

using namespace std;

class board
{
private:
    vector<vector<char>> map_;
    int dimX_, dimY_;

public:
    board(void);

    void init(int rows, int collums);
    void display() const;
    int rows, collums, zombies;
    void alienland(int x, int y, char ch);
    int getrows() const;
    int getcollums() const;
    void charsattribute();
    char getObjects(int x, int y) const;
    int alienLife, alienAttack;
    int zLife, zAttack, zRange;
    void turn();
    
};

board::board()
{
    cout << endl;
    cout << "Please change the game settings: ";
    cout << endl;

    cout << "Choose Number of Rows (3/5/7/9/11/13/15): " << endl;
    cin >> rows;

    cout << "Insert Number of Collums (3/5/7/9/11/13/15): " << endl;
    cin >> collums;

    cout << "Insert Number of Zombies (min 1, max 9): " << endl;
    cin >> zombies;

    init(rows, collums);
}

void board::init(int rows, int collums)
{
    dimX_ = collums; //
    dimY_ = rows;    //

    char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', 'h', 'p', 'r', '>', '<', '^', 'v'};

    int noOfObjects = 13; // number of objects in the objects array

    // create dynamic 2D array using vector
    map_.resize(dimY_); // create empty rows
    for (int i = 0; i < dimY_; ++i)
    {
        map_[i].resize(dimX_); // resize each row
    }
    

    // put random characters into the vector array
    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }

    // put zombies
    for (int n = 49; n < zombies + 49; ++n) // n = 49 = '1' ASCII code
    {
        map_[rand() % dimY_][rand() % dimX_] = char(n);
    }

}

void board::display() const
{
    // comment this out during testing
    // system("cls"); // OR system("clear"); for Linux / MacOS

    cout << "********************************" << endl;
    cout << " =      Alien vs Zombie        =" << endl;
    cout << "********************************" << endl;

    // for each row
    for (int i = 0; i < dimY_; ++i)
    {
        // display upper border of the row
        cout << " ";
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;

        // display row number
        cout << setw(2) << (dimY_ - i);
        // display cell content and border of each column
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "|" << map_[i][j];
        }
        cout << "|" << endl;
    }

    // display lower border of the last row
    cout << " ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;

    // display column number
    cout << " ";
    for (int j = 0; j < dimX_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;

    cout << " ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl
         << endl;
}


void board::alienland(int x, int y, char ch)
{

    map_[dimY_ - x][y - 1] = ch;
}

int board::getrows() const
{
    return dimY_;
}

int board::getcollums() const
{
    return dimX_;
}

void board::charsattribute()
{

    int zombieLife[] = {100, 120, 150, 180, 200};
    int noOfzLife = 5; // number of life in zombieLife array

    int zombieAttack[] = {10, 15, 20, 25, 30, 35, 40};
    int noOfzAttack = 7; // number of attack in zombieAttack array

    int zombieRange[] = {1, 2, 3, 4, 5};
    int noOfzRange = 5; // number of range in zombieRange array

    int alienLife = 100;
    int alienAttack = 0;

    cout << "Alien   : ";
    cout << "Life --> " << alienLife << " ";
    cout << "Attack -->" << setw(3) << alienAttack << endl;
    cout << endl;

    for (int z = 1; z < zombies + 1; z++)
    {

        int ZomLife = rand() % noOfzLife;
        int ZomAttack = rand() % noOfzAttack;
        int ZomRange = rand() % noOfzRange;

        int zLife = zombieLife[ZomLife];
        int zAttack = zombieAttack[ZomAttack];
        int zRange = zombieRange[ZomRange];

        cout << "Zombie " << z << ": "
             << "Life --> " << setw(3) << zLife << " "
             << "Attack --> " << setw(3) << zAttack << " "
             << "Range --> " << zRange << endl;
    }
}

// get map after movement
char board::getObjects(int x, int y) const
{
    // return map_[dimY_ - x][y - 1];
    return map_[dimY_ - y][x - 1]; // [dimY-srow][scol-1]
}

// objects for alien
void objFuncAlien()
{
    board b0ard;

    // rows and collums after movement
    int x1 = 2, y1 = 3;

    if (b0ard.getObjects(x1, y1) == 'h')
    {
        cout << "Alien founds a health pack." << endl;
        cout << "Alien's life increase by 20.";
        b0ard.alienLife += 20;
    }

    else if (b0ard.getObjects(x1, y1) == 'r')
    {

        int objUnderRock[] = {'h', 'p', ' '};
        int numOfOURock = 3; // number of objects under rock

        int randRock = rand() % numOfOURock;
        int Rock = objUnderRock[randRock];

        if (Rock == 'h')
        {
            cout << "Alien founds a health pack." << endl;
            cout << "Alien's life increase by 20.";
            b0ard.alienLife += 20;
        }
    }

}

void objFuncZombie()
{
    board b0ard;

    int x1 = 2, y1 = 3;

    if (b0ard.getObjects(x1, y1) == 'p')
    {
        b0ard.zLife -= 10;
    }

    else if (b0ard.getObjects(x1, y1) == 'r')
    {

        int objUnderRock[] = {'h', 'p', ' '};
        int numOfOURock = 3; // number of objects under rock

        int randRock = rand() % numOfOURock;
        int Rock = objUnderRock[randRock];

        if (Rock == 'p')
        {
            cout << "Alien founds a pod pack." << endl;
            cout << "Nearest Zombie life decrease by 10.";
            b0ard.zLife -= 20;
        }
    }
}

// void board::alienland(int x, int y, char ch)
//{                     //screen coord (x, y)

// map_[dimY_ - x][y - 1] = ch;
// map_[dimY_ - y][x - 1] = ch; // map coord [row][col]
//}

void board::turn()
{

    int x = getcollums() / 2 + 1;
    int y = getrows() / 2 + 1;

    // do
    //{
    string command;
    cout << endl;
    cout << "Command: ";
    cin >> command;

    if (command == "up") // up
    {
        alienland(x, y, '.');
        display();
        y = y + 1;
        alienland(x, y, 'A');
        display();
    }
    else if (command == "down") // down
    {
        alienland(x, y, '.');
        display();
        y = y - 1;
        alienland(x, y, 'A');
        display();
    }
    else if (command == "right") // right
    {
        alienland(x, y, '.');
        display();
        x = x + 1;
        alienland(x, y, 'A');
        display();
    }
    else if (command == "left") // left
    {
        alienland(x, y, '.');
        display();
        x = x - 1;
        alienland(x, y, 'A');
        display();
    }
    //}while (x!= dimX_ || x!= 1 || y!= dimY_ || y!= 1);
}

void Introduction()
{
    cout << endl;
    cout << "**********Welcome to Alien vs Zombie Game **********" << endl;
    cout << endl;
    cout << " Instructions " << endl;
    cout << " 1) Player must key in the desired number of ROWS, COLLUMS, and ZOMBIES." << endl;
    cout << " 2) Player can key in the 'help' to show lists of command. " << endl;
    cout << " 3) Number of Rows & Collums muat be in ODD number." << endl;
    cout << " 4) For better playing experience, the number of zombies must be less " << endl;
    cout << "    than the numbers of rows." << endl;
    cout << " 5) Number of zombies, minimum : 1, maximum : 9.";
    cout << endl;

    cout << "Please Type the Following Number." << endl;
    cout << "  1 --> Help Menu." << endl;
    cout << "  2 --> New Game." << endl;
    cout << "  3 --> Load Existing Game." << endl;
    cout << "  4 --> Quit." << endl;
    cout << "--> " << endl;
    
    
}

void help()
{
    cout << "**********Further Information.**********" << endl;
    cout << " The player plays the game by typing commands. The following shows the commands:" << endl;
    cout << " 1). up   --> Alien to move up." << endl;
    cout << " 2) down  --> Alien to move down." << endl;
    cout << " 3) left  --> Alien to move left." << endl;
    cout << " 4) right --> Alien to move right." << endl;
    cout << " 5) arrow --> Switch the direction of an arrow object in the game board." << endl;
    cout << " 6) help  --> List and describe the commands." << endl;
    cout << " 7) save  --> Save the current game to a file." << endl;
    cout << " 8) load  --> Load a saved game from a file." << endl;
    cout << " 9) quit  --> Quit the game while still in play." << endl;

}

void alien()
{

    board b0ard;

    cout << "rows = " << b0ard.getrows() << endl;

    cout << "collums = " << b0ard.getcollums() << endl;

    b0ard.alienland(b0ard.getrows() / 2 + 1, b0ard.getcollums() / 2 + 1 , 'A');
    b0ard.display();
    b0ard.charsattribute();
    b0ard.turn();
    

}



int main()
{
    cout << "Assignment (Part 1)" << endl;
    cout << "Let's Get Started!" << endl;

    Introduction();
    char playerscommand;
    cin >> playerscommand;

    switch (playerscommand)
    {
    case '1':
        cout << endl;
        help();
        cout << endl;
       
    
    case '2':
        alien();
        break;

    case '3':
        cout << "Not Finished yet." << endl;
        break;

    case '4':
        exit(0);
    }
    cout << endl;

    
}