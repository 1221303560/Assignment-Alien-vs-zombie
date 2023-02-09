// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT4L
// Names: ALVIN LIM JUN EN | LEW CHUN MEN | HOO JET YUNG
// IDs: 1221303560 | 1211104248 | 1221303540
// Emails: 1221303560@STUDENT.MMU.EDU.MY | 1211104248@STUDENT.MMU.EDU.MY | 1221303540@STUDENT.MMU.EDU.MY
// Phones: 0167883717 | 01113139039 | 0189854391
// *********************************************************

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
#include <cmath>
using namespace std;
class Zombie;

int mst = 0;        // alien movement state
int pst = 0;        // alien player state
int gst = 1;        // game state, 1 = player turn, 11-19 = zombie turn, 3 = alien wins, 4 = alien loses, 5 = quit game
int cst = 0;        // player command state
int load = 0;       // load call
int nzombie = 0;    // number of zombies (save)
int zombieLeft = 0; // number of zombie alive in game (save)
int nrow = 0;       // number of rows in board (save)
int ncolumn = 0;    // number of columns in board (save)

class Board
{
private:
    vector<vector<char>> map_; // convention to put trailing underscore
    int dimX_, dimY_;

public:
    Board(); // Defult Board Settings
    Board(int dimX, int dimY);

    void init(int dimX, int dimY); // Problems : how to change this value
    void display() const;

    int getDimX() const;
    int getDimY() const;

    char getObject(int x, int y) const;
    void setObject(int x, int y, char ch);

    bool isEmpty(int x, int y) const;
    bool isInsideBoard(int x, int y) const;
};

class Alien
{
private:
    char symbol;
    char trail;
    int x_, y_;
    int hp_, atk_;

public:
    Alien();
    Alien(int x, int y, char chAlien);

    int getX() const;
    int getY() const;
    int getHp() const;
    int getAtk() const;

    void setXY(int x, int y);
    void setHp(int hp);
    void setAtk(int atk);
    void setAlien(int x, int y, Board &game);

    void alienMovement(Board &game);
    void alienCheckNext(Board &game);
    void alienAction(Board &game);
};

class Zombie
{
private:
    char symbol;
    int x_, y_;
    int hp_, atk_, range_;

public:
    Zombie();

    char getSymbol() const;
    int getX() const;
    int getY() const;
    int getHp() const;
    int getAtk() const;
    int getRange() const;

    void setSymbol(char ch);
    void setX(int x);
    void setY(int y);
    void setHp(int hp);
    void setAtk(int atk);
    void setRange(int range);
    void setZombie(int x, int y, Board &game);

    void zombieUp(Board& game);
    void zombieDown(Board& game);
    void zombieLeft(Board& game);
    void zombieRight(Board& game);

    void movement(Board& game, Alien& alien);
    void attack(Alien& alien);
};

Zombie zombie[10];

Board::Board() // Default Game Settings Rows : 5 Columns : 9
{
    int dimX = 9;
    int dimY = 5;
    init(dimX, dimY);
}

Board::Board(int dimX, int dimY)
{
    init(dimX, dimY);
}

int Board::getDimX() const
{
    return dimX_;
}

int Board::getDimY() const
{
    return dimY_;
}

void Board::init(int dimX, int dimY)
{
    dimX_ = dimX;
    dimY_ = dimY;
    char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', '<', '>', '^', 'h', 'r', 'p', 'v'};
    int noOfObjects = 14; // number of objects in the objects array
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
}

void Board::display() const
{
    // comment this out during testing
    system("cls");
    cout << "   ";
    if (dimX_ > 9) // make title centered on game board
    {
        int x = dimX_ - 9;
        for (int i = 0; i < x; ++i)
        {
            cout << " ";
        }
    }
    cout << ".:Alien vs Zombie :." << endl;
    // for each row
    for (int i = 0; i < dimY_; ++i)
    {
        // display upper border of the row
        cout << "   ";
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;
        // display row number
        cout << setw(2) << (dimY_ - i) << " ";
        // display cell content and border of each column
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "|" << map_[i][j];
        }
        cout << "|" << endl;
    }
    // display lower border of the last row
    cout << "   ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;
    // display column number
    cout << "  ";
    if (dimX_ > 9)
    {
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
        cout << "   ";
        for (int j = 0; j < dimX_; ++j)
        {
            cout << " " << (j + 1) % 10;
        }
    }
    else
    {
        cout << " ";
        for (int j = 0; j < dimX_; ++j)
        {
            cout << " " << (j + 1) % 10;
        }
    }
    cout << endl
         << endl;
}

char Board::getObject(int x, int y) const
{
    return map_[dimY_ - y][x - 1];
}

void Board::setObject(int x, int y, char ch)
{
    map_[dimY_ - y][x - 1] = ch;
}

bool Board::isEmpty(int x, int y) const
{
    return map_[dimY_ - y][x - 1] == ' ';
}

bool Board::isInsideBoard(int x, int y) const
{
    return x && y && dimX_ - x + 1 && dimY_ - y + 1;
}

Alien::Alien()
{
}

Alien::Alien(int x, int y, char chAlien) // make object Alien and specify its coordinates
{
    symbol = chAlien;
    trail = '.';
    x_ = x;
    y_ = y;
    hp_ = 100;
    atk_ = 10;
}

int Alien::getX() const
{
    return x_;
}

int Alien::getY() const
{
    return y_;
}

int Alien::getHp() const
{
    return hp_;
}

void Alien::setHp(int hp)
{
    hp_ = hp;
}

int Alien::getAtk() const
{
    return atk_;
}

void Alien::setXY(int x, int y)
{
    x_ = x;
    y_ = y;
}

void Alien::setAtk(int atk)
{
    atk_ = atk;
}

void Alien::setAlien(int x, int y, Board &game)
{
    x_ = x;
    y_ = y;
    game.setObject(x, y, symbol);
}

void Alien::alienMovement(Board &game)
{
    game.setObject(x_, y_, trail);

    switch (mst)
    {
    case 1: // up
        y_++;
        setAlien(x_, y_, game);
        break;
    case 2: // down
        y_--;
        setAlien(x_, y_, game);
        break;
    case 3: // left
        x_--;
        setAlien(x_, y_, game);
        break;
    case 4: // right
        x_++;
        setAlien(x_, y_, game);
        break;
    }
}

void Alien::alienCheckNext(Board &game)
{
    int x = x_;
    int y = y_;

    switch (mst)
    {
    case 1: // up
        y++;
        break;
    case 2: // down
        y--;
        break;
    case 3: // left
        x--;
        break;
    case 4: // right
        x++;
        break;
    }

    if (game.isInsideBoard(x, y)) // if not out of bounds
    {
        char objNext = game.getObject(x, y);

        switch (objNext)
        {
        case ' ':
        case '.':
            pst = 11; // encounters space or trail
            break;
        case 'h':
            pst = 12; // encounters health
            break;
        case 'p':
            pst = 13; // encounters pod
            break;
        case 'r':
            pst = 14; // encounters rock
            break;
        case '^':
            pst = 15; // encounters arrow up
            break;
        case 'v':
            pst = 16; // encounters arrow down
            break;
        case '<':
            pst = 17; // encounters arrow left
            break;
        case '>':
            pst = 18; // encounters arrow right
            break;
        // encounters zombie 1-9
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            pst = 21;
            break;
        }
    }
    else // if out of bounds
    {
        pst = 19; // encounters border
    }
}

void Alien::alienAction(Board &game)
{
    switch (pst)
    {
    case 11: // Alien encounters space or trail
    {
        cout << "Alien encounters nothing." << endl;

        switch (mst)
        {
        case 1: // up
            cout << "Alien continues up." << endl;
            break;
        case 2: // down
            cout << "Alien continues down." << endl;
            break;
        case 3: // left
            cout << "Alien continues left." << endl;
            break;
        case 4: // right
            cout << "Alien continues right." << endl;
            break;
        }
        alienMovement(game);
        break;
    }

    case 12: // Alien encounters health
    {
        cout << "Alien finds a health pack and proceeds to use it." << endl;
        cout << "Alien's life increased by 20." << endl;
        hp_ = hp_ + 20;
        alienMovement(game);
        break;
    }

    case 13: // Alien eccounters pod
    {
        cout << "Alien finds a pod." << endl;

        int closest = 1;
        float smallestDistance = 39.59797975; // max distance of max dimensions

        int x1, y1;
        for (int i = 1; i < nzombie; i++)
        {
            x1 = zombie[i].getX();
            y1 = zombie[i].getY();

            float distance = sqrt(pow((x1 - x_), 2.0) + pow((y1 - y_), 2.0));

            if (distance < smallestDistance)
            {
                smallestDistance = distance;
                closest = i;
            }
        }

        int previousHp = zombie[closest].getHp();
        int currentHp = previousHp - 10;
        cout << "Alien attacks zombie " << closest << " with 10 damage using pod." << endl
             << endl;

        if (currentHp > 0)
        {
            cout << "Zombie " << closest << " is still standing after the attack." << endl;
            zombie[closest].setHp(currentHp);
        }
        else
        {
            cout << "Zombie " << closest << " dies." << endl;
            zombie[closest].setHp(0);
            zombieLeft = zombieLeft - 1;
            // remove zombie from board
            game.setObject(x1, y1, ' ');
            zombie[closest].setX(100);
            zombie[closest].setY(100);
        }
        alienMovement(game);
        break;
    }

    case 14: // alien encounters rock
    {
        cout << "Alien encounters a rock and proceeds to uncover it." << endl
             << endl;

        char objects[] = {' ', ' ', '<', '>', '^', 'h', 'p', 'v'};
        int noOfObjects = 8;
        int objNo = rand() % noOfObjects;

        char obj = objects[objNo];

        if (obj == ' ')
        {
            cout << "Alien found nothing beneath the rock." << endl;
        }

        else if (obj == '<' || obj == '>' || obj == '^' || obj == 'v')
        {
            cout << "Alien discovers an arrow beneath the rock." << endl;
        }

        else if (obj == 'p')
        {
            cout << "Alien discovers a pod beneath the rock. " << endl;
        }

        else if (obj == 'h')
        {
            cout << "Alien discovers a health kit beneath the rock. " << endl;
        }

        int x = x_;
        int y = y_;

        switch (mst)
        {
        case 1: // up
            y = y + 1;
            break;
        case 2: // down
            y = y - 1;
            break;
        case 3: // left
            x = x - 1;
            break;
        case 4: // right
            x = x + 1;
            break;
        }
        game.setObject(x, y, obj);
        cout << "Alien stops in front of the object." << endl;
        pst = 20; // alien turn ends
        break;
    }

    case 15: // alien encounters up arrow
    {
        cout << "Alien finds an up arrow." << endl;
        atk_ = atk_ + 20;
        cout << "Alien's attack increased by 20 and movement direction is switched upwards." << endl;
        alienMovement(game);
        mst = 1; // alien up
        break;
    }

    case 16: // alien encounters down arrow
    {
        cout << "Alien finds a down arrow." << endl;
        atk_ = atk_ + 20;
        cout << "Alien's attack increased by 20 and movement direction is switched downwards." << endl;
        alienMovement(game);
        mst = 2; // alien down
        break;
    }

    case 17: // alien encounters left arrow
    {
        cout << "Alien finds a left arrow." << endl;
        atk_ = atk_ + 20;
        cout << "Alien's attack increased by 20 and movement direction is switched to the left." << endl;
        alienMovement(game);
        mst = 3; // alien left
        break;
    }

    case 18: // alien encounters right arrow
    {
        cout << "Alien find a right arrow." << endl;
        atk_ = atk_ + 20;
        cout << "Alien's attack increased by 20 and movement direction is switched to the right." << endl;
        alienMovement(game);
        mst = 4; // alien right
        break;
    }

    case 19: // alien hits border
    {
        cout << "Alien hits the border." << endl
             << endl;
        pst = 20; // alien turn ends
        break;
    }

    case 21: // alien hits zombie 1-9
    {
        int x = x_;
        int y = y_;

        switch (mst)
        {
        case 1: // up
            y = y + 1;
            break;
        case 2: // down
            y = y - 1;
            break;
        case 3: // left
            x = x - 1;
            break;
        case 4: // right
            x = x + 1;
            break;
        }
        char ch = game.getObject(x, y);
        int zNumber = ch - '0';

        cout << "Alien hits zombie " << zNumber << " ." << endl;
        cout << "Alien inficts " << atk_ << " damage to zombie " << zNumber << " . ";

        int zhp = zombie[zNumber].getHp();
        zhp = zhp - atk_;

        if (zhp > 0)
        {
            cout << "Zombie " << zNumber << " is still standing after the attack." << endl;
            zombie[zNumber].setHp(zhp);
        }
        else
        {
            cout << "Zombie " << zNumber << " dies." << endl;
            zombie[zNumber].setHp(0);
            zombieLeft = zombieLeft - 1;
            // remove zombie from board
            game.setObject(x, y, ' ');
            zombie[zNumber].setX(100);
            zombie[zNumber].setY(100);
        }

        pst = 20; // alien turn ends
        gst = 2;
        break;
    }
    }
    if (zombieLeft = 0) // win condition
    {
        gst = 3; // alien wins
    }
}

Zombie::Zombie()
{
    hp_ = (rand() % 5 + 2) * 50;
    atk_ = (rand() % 5 + 1) * 5;
    range_ = rand() % 3 + 1;
}

char Zombie::getSymbol() const
{
    return symbol;
}

int Zombie::getX() const
{
    return x_;
}

int Zombie::getY() const
{
    return y_;
}

int Zombie::getHp() const
{
    return hp_;
}

int Zombie::getAtk() const
{
    return atk_;
}

int Zombie::getRange() const
{
    return range_;
}

void Zombie::setSymbol(char ch)
{
    symbol = ch;
}

void Zombie::setX(int x)
{
    x_ = x;
}

void Zombie::setY(int y)
{
    y_ = y;
}

void Zombie::setHp(int hp)
{
    hp_ = hp;
}

void Zombie::setAtk(int atk)
{
    atk_ = atk;
}

void Zombie::setRange(int range)
{
    range_ = range;
}

void Zombie::setZombie(int x, int y, Board &game)
{
    x_ = x;
    y_ = y;
    game.setObject(x, y, symbol);
}

void Zombie::zombieUp(Board &game)
{
    int y = y_ + 1;

    setZombie(x_, y, game); // set zombie
}

void Zombie::zombieDown(Board &game)
{
    int y = y_ - 1;

    setZombie(x_, y, game); // set zombie
}

void Zombie::zombieLeft(Board &game)
{
    int x = x_ - 1;

    setZombie(x, y_, game); // set zombie
}

void Zombie::zombieRight(Board &game)
{
    int x = x_ + 1;

    setZombie(x, y_, game); // set zombie
}

void Zombie::movement(Board &game, Alien &alien)
{
    int alienX, alienY;

    bool left = false;
    bool right = false;
    bool up = false;
    bool bottom = false;

    alienX = alien.getX();
    alienY = alien.getY();

    // Check zombie is beside border and beside alien
    if (x_ == 1 || alienX == x_ - 1 && alienY == y_)
    {
        // Border or alien at left
        left = true;
    }
    else if (x_ == game.getDimX() || alienX == x_ + 1 && alienY == y_)
    {
        // Border or alien at right
        right = true;
    }
    else if (y_ == 1 || alienX == x_ && alienY == y_ + 1)
    {
        // Border or alien at top
        up = true;
    }
    else if (y_ == game.getDimY() || alienX == x_ && alienY == y_ - 1)
    {
        // Border or alien at bottom
        bottom = true;
    }

    // Random zombie behaviour to chase or randomly walk
    int random = rand() % 10;
    if (random < 2)
    {
        // Zombie randomly walk
        int random = rand() % 4;
        bool flag = false;

        if (random == 0 && !up)
        {
            zombieUp(game);
            cout << "Zombie " << symbol << "moves up." << endl;
            flag = true;
        }
        else if (random == 1 && !bottom)
        {
            zombieDown(game);
            cout << "Zombie " << symbol << " moves down." << endl;
            flag = true;
        }
        else if (random == 2 && !left)
        {
            zombieLeft(game);
            cout << "Zombie " << symbol << " moves left." << endl;
            flag = true;
        }
        else if (random == 3 && !right)
        {
            zombieRight(game);
            cout << "Zombie " << symbol << " moves right." << endl;
            flag = true;
        }
    }
    else if (random > 2)
    {
        random = rand() % 2;
        if (random == 1)
        {
            // Vertical
            if (alienY > y_)
            {
                zombieUp(game);
                cout << "Zombie " << symbol << " moves up." << endl;
            }
            else if (alienY < y_)
            {
                zombieDown(game);
                cout << "Zombie " << symbol << " moves down." << endl;
            }
        }
        else
        {
            // Horizontal
            if (alienX > x_)
            {
                zombieRight(game);
                cout << "Zombie " << symbol << " moves right." << endl;
            }
            else if (alienX < x_)
            {
                zombieLeft(game);
                cout << "Zombie " << symbol << " moves left." << endl;
            }
        }
    }
    cout << endl;
}

void Zombie::attack(Alien &alien)
{
    int alienX = alien.getX();
    int alienY = alien.getY();

    // Check if alien is in range
    if (alienX >= x_ - range_ && alienX <= x_ + range_ && alienY >= y_ - range_ && alienY <= y_ + range_)
    {
        // Attack Alien
        cout << "Zombie " << symbol << " attacks Alien." << endl;
        int alienHp = alien.getHp();
        alienHp -= atk_;
        if (alienHp <= 0)
        {
            alien.setHp(0);
            cout << "Alien dies." << endl;
            gst = 4;
        }
        else
        {
            alien.setHp(alienHp);
            cout << "Alien survives the attack." << endl;
        }
    }
    else
    {
        cout << "Zombie " << symbol << " is unable to attack alien." << endl
             << "Alien not within range of zombie " << symbol << "." << endl;
    }
    cout << endl;
}

void getSettings(char settings)
{
    while (!cin.good() && settings != 'Y' && settings != 'N')
    {
        cout << "Please enter in only a character." << endl;
        cin.clear();
        cin.ignore();
        cout << "Do you wish to change the game settings (y/n)? => ";
        cin >> settings;
        settings = toupper(settings);
    }
    
    if (settings == 'Y')
    {
        cout << "Board Settings  " << endl;
        cout << "----------------" << endl;

        // Change board Rows //
        cout << "Enter rows => ";
        cin >> nrow;
        while (!cin.good() || nrow % 2 == 0 || nrow < 3 || nrow > 29)
        {
            if (!cin.good())
            {
                cout << "Please enter odd numbers only" << endl;
                cin.clear();
                cin.ignore();
                cout << "Enter rows => ";
                cin >> nrow;
            }
            if (nrow % 2 == 0)
            {
                cout << "Please enter odd numbers only" << endl;
                cin.clear();
                cin.ignore();
                cout << "Enter rows => ";
                cin >> nrow;
            }
            if (nrow < 3)
            {
                cout << "Please enter odd numbers greater or equal to 3" << endl;
                cin.clear();
                cin.ignore();
                cout << "Enter rows => ";
                cin >> nrow;
            }
            if (nrow > 29)
            {
                cout << "Maximum number of rows is 29" << endl;
                cin.clear();
                cin.ignore();
                cout << "Enter rows => ";
                cin >> nrow;
            }
            else
                break;
        }

        // Change board Columns //
        cout << endl << "Enter columns => ";
        cin >> ncolumn;
        while (!cin.good() || ncolumn % 2 == 0 || ncolumn < 3 || ncolumn > 29)
        {
            if (!cin.good())
            {
                cout << "Please enter odd numbers only" << endl;
                cin.clear();
                cin.ignore();
                cout << "Enter columns => ";
                cin >> ncolumn;
            }
            if (ncolumn % 2 == 0)
            {
                cout << "Please enter odd numbers only" << endl;
                cin.clear();
                cin.ignore();
                cout << "Enter columns => ";
                cin >> ncolumn;
            }
            if (ncolumn < 8)
            {
                cout << "Please enter odd numbers greater or equal to 9" << endl;
                cin.clear();
                cin.ignore();
                cout << "Enter columns => ";
                cin >> ncolumn;
            }
            if (ncolumn > 29)
            {
                cout << "Maximum number of columns is 29" << endl;
                cin.clear();
                cin.ignore();
                cout << "Enter columns => ";
                cin >> ncolumn;
            }
            else
                break;
        }

        // Change the Zombies //
        cout << endl << "Enter number of zombies => ";
        cin >> nzombie;
        while (!cin.good() || nzombie <= 0 || nzombie > 9)
        {
            if (!cin.good())
            {
                cout << "Please enter numbers only" << endl;
                cin.clear();
                cin.ignore();
                cout << "Enter number of zombies => ";
                cin >> nzombie;
            }
            if (nzombie <= 0)
            {
                cout << "Please enter positive numbers only and greater than 0" << endl;
                cin.clear();
                cin.ignore();
                cout << "Enter number of zombies => ";
                cin >> nzombie;
            }
            if (nzombie > 9)
            {
                cout << "Maximum number of zombies is 9" << endl;
                cin.clear();
                cin.ignore();
                cout << "Enter number of zombie => ";
                cin >> nzombie;
            }
            else
                break;
        }
        zombieLeft = nzombie;
    }
    else
    {
        ncolumn = 9;
        nrow = 5;
        nzombie = 1;
        zombieLeft = 1;
    }
}

void command()
{
    string command;
    cout << "Command => ";
    cin >> command;
    
    while (!cin.good() && command != "up" && command != "down" && command != "left" && command != "right" 
           && command != "arrow" && command != "help" && command != "save" && command != "load" && command != "quit")
        {
            cout << "Please enter a correct selection." << endl;
            cin.clear();
            cin.ignore();
            cout << "Command => ";
            cin >> command;
            continue;
        }

    if (command == "up")
    {        
        cst = 1;
        mst = 1;
        cout << "Player decides to move up." << endl;
    }

    else if (command == "down")
    {
        cst = 2;
        mst = 2;
        cout << "Player decides to move down." << endl;
    }

    else if (command == "left")
    {
        cst = 3;
        mst = 3;
        cout << "Player decides to move left." << endl;
    }

    else if (command == "right")
    {
        cst = 4;
        mst = 4;
        cout << "Player decides to move right." << endl;
    }

    else if (command == "arrow")
    {
        cst = 5; // change direction of arrow
    }

    else if (command == "help")
    {
        cst = 6; // user asks for help
    }

    // else if (command == "save")
    // {
        // cst = 7;
    // }

    // else if (command == "load")
    // {
        // cst = 8;
    // }

    else if (command == "quit")
    {
        cst = 9;
    }

}

void displayStatus(Alien player, int j)
{
    if (gst == 1)
    {
        cout << "->  Alien       : Life " 
             << player.getHp() << ", Attack " << player.getAtk() << endl;
        
        for (int i = 1; i <= nzombie; i++)
        { 
            cout << "    Zombie " << i << "    : Life " << zombie[i].getHp() << ", Attack " 
                 << zombie[i].getAtk() << ", Range " << zombie[i].getRange() << endl;
        }
        cout << endl;
    }
    else if (gst == 2)
    {
        cout << "    Alien       : Life " 
             << player.getHp() << ", Attack " << player.getAtk() << endl;
        
        for (int i = 1; i <= nzombie; i++)
        {
            if (i == j)
            {
                cout << "->  Zombie " << i << "    : Life " << zombie[i].getHp() << ", Attack " 
                     << zombie[i].getAtk() << ", Range " << zombie[i].getRange() << endl;
            }
            else
            {
                cout << "    Zombie " << i << "    : Life " << zombie[i].getHp() << ", Attack " 
                     << zombie[i].getAtk() << ", Range " << zombie[i].getRange() << endl;
            }
        }
        cout << endl;
    }
}

void maingame()
{
    char settings;

    cout << "Default Game Settings" << endl;
    cout << "---------------------" << endl;
    cout << "Board Rows   : 5" << endl;
    cout << "Board Colums : 9" << endl;
    cout << "Zombie Count : 1" << endl << endl;
    
    cout << "Do you wish to change the game settings (y/n)? => ";
    cin >> settings;
    settings = toupper(settings);
    getSettings(settings);

    // initial alien position
    int x1 = ncolumn/2 + 1;
    int y1 = nrow/2 + 1;
    char ch1 = 'A';
    
    // declaring game objects
    Board game(ncolumn, nrow);
    Alien player(x1, y1, ch1);
    player.setAlien(x1, y1, game);

    for (int i = 1; i <= nzombie; i++) // puts zombies into the board
    {
        char ch = i + '0';
        zombie[i].setSymbol(ch);

        int x = rand() % ncolumn + 1;
        int y = rand() % nrow + 1;
        
        char chZombie = game.getObject(x, y);

        while (x == x1 && y == y1 || chZombie > 48 && chZombie < 57)
        {
            x = rand() % (ncolumn + 1);
            y = rand() % (nrow + 1);
        }
        zombie[i].setZombie(x, y, game);
    }

    do
    {
        if (gst == 1) // player turn
        {
            game.display();
            displayStatus(player, 0);
            cout << "Alien turn." << endl << endl;
            system("pause");

            game.display();
            displayStatus(player, 0);
            command();
            
            switch (cst)
            {
                case 1: // player enter command up
                case 2: // player enter command down
                case 3: // player enter command left
                case 4: // player enter command right
                {
                    pst = 0;
                    while (pst != 20 && gst != 3)
                    {
                        game.display();
                        displayStatus(player, 0);
                        player.alienCheckNext(game);
                        player.alienAction(game);
                        cout << endl;
                        system("pause");
                        if (zombieLeft == 0)
                        {
                            gst = 3;
                            break;
                        }
                    }
                    if (pst == 20) // alien stopped by object
                    {
                        game.display();
                        displayStatus(player, 0);
                        cout << "Alien turn ends." << endl << endl;
                        system("pause");
                        gst = 2; // zombies turn
                    }
                    break;
                }

                case 5: // player enter command arrow
                {
                    int x, y;
                    string arrow;
                    cout << "Please enter coordinates and direction of arrow (x y direction)." << endl
                        << "-> ";
                    cin >> x >> y >> arrow;

                    while (!cin.good() || x <= 0 || x > ncolumn || y <= 0 || y > nrow ||
                        arrow != "up" || arrow != "down" || arrow != "left" || arrow != "right")
                    {
                        cin.clear();
                        cin.ignore();
                        cout << "Please enter correct coordinates and directions." << endl;
                    }

                    char ch = game.getObject(x, y);

                    if (ch == '^' || ch == 'v' || ch == '<' || ch == '<')
                    {
                        if (arrow == "up")
                        {
                            game.setObject(x, y, '^');
                        }
                        else if (arrow == "down")
                        {
                            game.setObject(x, y, 'v');
                        }
                        else if (arrow == "left")
                        {
                            game.setObject(x, y, '<');
                        }
                        else if (arrow == "right")
                        {
                            game.setObject(x, y, '>');
                        }
                        cout << "Arrow set." << endl;
                    }
                    else
                    {
                        cout << "Arrow not found." << endl;
                    }
                    system("pause");
                    break;
                }

                case 6: // player asks for help
                {
                    cout << endl
                        << "Commands:" << endl
                        << "1. up      - Move up." << endl
                        << "2. down    - Move down." << endl
                        << "3. left    - Move left." << endl
                        << "4. right   - Move right." << endl
                        << "5. arrow   - Change the direction of the arrow." << endl
                        << "6. help    - Display this user commands." << endl
                        << "7. save    - Save the game." << endl
                        << "8. load    - Load a game." << endl
                        << "9. quit    - Quit the game." << endl;
                    system("pause");
                    break;
                }

                // case 7: // player enter save
                // {
                    
                // }

                // case 8: // player enter load
                // {

                // }

                case 9: // player enter quit
                {
                    char input;
                    cout << "Any unsaved progress will be lost." << endl
                        << "Are you sure to quit game y/n ?" << endl;
                    cin >> input;
                    input = toupper(input);
                    
                    while (!cin.good() && input != 'Y' && input != 'N')
                    {
                        cout << "Please enter in only a character." << endl;
                        cin.clear();
                        cin.ignore();
                        cout << "Are you sure to quit game (y/n)? => ";
                        cin >> input;
                        input = toupper(input);
                    }

                    if (input == 'Y')
                    {
                        gst = 5;
                    }         
                    else 
                    {
                        break;
                    }
                }    
            }
        }

        else if (gst == 2)
        {
            // remove alien trail
            for (int i = 1; i <= game.getDimY(); i++)
            {
                    for (int j = 1; j <= game.getDimX(); j++)
                    {
                        if (game.getObject(j, i) == '.')
                        {
                            game.setObject(j, i, ' ');
                        }
                    }
            }
            // zombie action
            for (int i = 1; i <= nzombie; i++)
            {
                game.display();
                displayStatus(player, i);
                cout << "Zombie " << i << " turn." << endl << endl;
                system("pause");

                if (zombie[i].getHp() != 0) // zombie alive
                {
                    game.display();
                    displayStatus(player, i);
                    zombie[i].movement(game, player);
                    system("pause");

                    game.display();
                    displayStatus(player, i);
                    zombie[i].attack(player);
                    system("pause");
                }
                else // zombie dead
                {
                    cout << "Zombie " << i << " is still dead." << endl;
                }
                game.display();
                displayStatus(player, i);
                cout << "Zombie " << i << " turn ends." << endl << endl;
                system("pause");
            }
            gst = 1;
        }
    }while (gst != 3 && gst != 4 && gst != 5);
}


int main()
{
    srand(1); // use this for fixed map during testing
    // srand(time(NULL)); // try this for random map

    int flag = 1;
    while (flag == 1)
    {
        maingame(); // gst = 1, gst = 2
        
        if (gst == 3 || gst == 4)
        {
            if (gst == 3)
            {
                cout << "Alien wins the game." << endl
                    << "Victory!" << endl << endl;
            }
            else if (gst == 4)
            {
                cout << "You lose." << endl
                    << "Game Over" << endl << endl;
            }

            char input;
            cout << "Do you want to play again (y/n) ?" << endl
                 << "-> ";
                cin >> input;
                input = toupper(input);
                
            while (!cin.good() && input != 'Y' && input != 'N')
            {
                cout << "Please enter in only a character." << endl;
                cin.clear();
                cin.ignore();
                cout << "Do you want to play again (y/n)? => ";
                cin >> input;
                input = toupper(input);
            }
            if (input == 'Y')
            {
            }
            else
            {
                cout << "See you next time!" << endl;
                flag = 0;
            }
        }
        else
        {
            cout << "See you next time!" << endl;
            flag = 0;
        }
        continue;
    }
    return 0;
}
