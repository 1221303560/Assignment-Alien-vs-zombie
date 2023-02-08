// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT2L 
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

class Board
{
private:
    vector< vector<char> > map_; // convention to put trailing underscore
    int dimX_, dimY_;
public:
    Board(); //Defult Board Settings
    Board(int dimX, int dimY);  
    
    void init(int dimX, int dimY);            // Problems : how to change this value 
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

    void alienUp(int &CState, int nzombie, Board &game, Zombie *zombie);
    void alienDown(int &CState, int nzombie, Board &game, Zombie *zombie);
    void alienLeft(int &CState, int nzombie, Board &game, Zombie *zombie);
    void alienRight(int &CState, int nzombie, Board &game, Zombie *zombie);
    
};

class Zombie
{
private:
    char symbol;
    int x_, y_;
    int hp_, atk_, range;

public:
    Zombie();

    int getSymbol() const;
    int getX() const;
    int getY() const;
    int getHp() const;
    int getAtk() const;
    int getRange() const;
    int getZombieX() const;
    int getZombieY() const;

    void setHp(int hp);
    void setSymbol(char ch);
    void setZombie(int x, int y, Board &game);

    void zombieUp(Board& game);
    void zombieDown(Board& game);
    void zombieLeft(Board& game);
    void zombieRight(Board& game);

    void action(Board& game, Alien& alien);
};

// zombie* Zombie[9];

Board::Board()      // DEMO !!! Default Game Settings Rows : 5 Columns : 9
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
    cout << "      .:Alien vs Zombie :.       "<< endl;
    // for each row
    for (int i = 0; i < dimY_; ++i)
    {
        // display upper border of the row
        cout << "  ";
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
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;
    // display column number
    cout << "  ";
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
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << " " << (j + 1) % 10;
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

void Alien::alienUp(int &CState, int nzombie, Board &game, Zombie *zombie)
{
    int y = y_ - 1;
    char next = game.getObject(x_, y);
    system("pause");
    
    if (game.isInsideBoard(x_, y))
    {
        if (next == ' ')
        {
            game.setObject(x_, y_, '.');
            setAlien(x_, y, game);
            game.display();
            cout << "Alien encounters nothing." << endl;
            system("pause");
        }
        else if (next == '.')
        {
            game.setObject(x_, y_, '.');
            setAlien(x_, y, game);
            game.display();
            cout << "Alien encounters nothing." << endl;
            system("pause");
        }
        else if (next == 'h')
        {
            game.setObject(x_, y_, '.');
            setAlien(x_, y, game);
            game.display();
            cout << "Alien picks up health pack." << endl
                 << "Alien's health increased from " << hp_;
            hp_ = hp_ + 20;
            cout << "to " << hp_ << "." << endl;
            system("pause");

            game.display();
            system("pause");
        }
        else if (next == 'p')
        {
            game.setObject(x_, y_, '.');
            setAlien(x_, y, game);
            int closest = 1;
            float smallestDistance = 39.59797975;

            for (int i = 1; i < nzombie; i++)
            {
                int x1 = zombie[i].getX();
                int y1 = zombie[i].getY();

                float distance = sqrt(pow((x1 - x_), 2.0) + pow((y1 - y_), 2.0));
                
                if (distance < smallestDistance)
                {
                    closest = i;
                }
            }
            
            int previousHp = zombie[closest].getHp();
            int zHp = previousHp - 10;
            cout << "Alien attacks zombie" << closest << ". " << endl
                 << "Zombie " << closest << "hp drops to " << zHp << ". " << endl;
            system("pause");

            game.display();
            system("pause");
        } 
        else if (next == 'r')
        {
            char objects[] = {' ', ' ', '<', '>', '^', 'h', 'p', 'v'};
            int noOfObjects = 8;
            int objNo = rand() % noOfObjects;
            game.display();
            cout << "Alien encounters a rock." << endl
                 << "Alien proceeds to uncover the rock." << endl;
            system("pause");

            game.setObject(x_, y_, objects[objNo]);
            game.display();

            if (objects[objNo] == ' ')
            {
                cout << "Alien found nothing beneath the rock." << endl;
            }

            else if (objects[objNo] == '<' || objects[objNo] == '>' || objects[objNo] == '^' || objects[objNo] == 'v')
            {
                cout << "Alien discovers an arrow beneath the rock." << endl;
            }

            else if (objects[objNo] == 'p')
            {
                cout << "Alien discovers a pod beneath the rock. " << endl;
            }

            else if (objects[objNo] == 'h')
            {
                cout << "Alien discovers a health kit beneath the rock. " << endl;
            }

            system("pause");

            game.display();
            cout << "Alien move ends." << endl;
            system("pause");

            CState = 5; //stop
        }

        else if (next == '^')
        {
            game.display();
            cout << "Aliens finds an arrow." << endl;
            cout << "Alien's attack is increased by 20." << endl;
            atk_ = atk_ + 20;
            system("pause");
        }

        else if (next == 'v')
        { 
            cout << "Aliens finds an arrow." << endl;
            cout << "Alien's attack is increased by 20." << endl;
            atk_ = atk_ + 20;
            CState = 2; //down
            system("pause");
        }

        else if (next == '<')
        {
            cout << "Aliens finds an arrow." << endl;
            cout << "Alien's attack is increased by 20." << endl;
            atk_ = atk_ + 20;
            CState = 3; //left
            system("pause");
        }

        else if (next == '>')
        {
            cout << "Aliens finds an arrow." << endl;
            cout << "Alien's attack is increased by 20." << endl;
            atk_ = atk_ + 20;
            CState = 4; //right
            system("pause");
        }
    }
        
    else
    {
        game.display();
        cout << "Alien hits the border." << endl;
        CState = 5; //stop
        system("pause");
    }  
}

void Alien::alienDown(int &CState, int nzombie, Board &game, Zombie *zombie)
{
    int y = y_ - 1;
    char next = game.getObject(x_, y);
    system("pause");
    
    if (game.isInsideBoard(x_, y))
    {
        if (next == ' ')
        {
            game.setObject(x_, y_, '.');
            setAlien(x_, y, game);
            game.display();
            cout << "Alien encounters nothing." << endl;
            system("pause");
        }
        else if (next == '.')
        {
            game.setObject(x_, y_, '.');
            setAlien(x_, y, game);
            game.display();
            cout << "Alien encounters nothing." << endl;
            system("pause");
        }
        else if (next == 'h')
        {
            game.setObject(x_, y_, '.');
            setAlien(x_, y, game);
            game.display();
            cout << "Alien picks up health pack." << endl
                 << "Alien's health increased from " << hp_;
            hp_ = hp_ + 20;
            cout << "to " << hp_ << "." << endl;
            system("pause");

            game.display();
            system("pause");
        }
        else if (next == 'p')
        {
            game.setObject(x_, y_, '.');
            setAlien(x_, y, game);
            int closest = 1;
            float smallestDistance = 39.59797975;

            for (int i = 1; i < nzombie; i++)
            {
                int x1 = zombie[i].getX();
                int y1 = zombie[i].getY();

                float distance = sqrt(pow((x1 - x_), 2.0) + pow((y1 - y_), 2.0));
                
                if (distance < smallestDistance)
                {
                    closest = i;
                }
            }
            
            int previousHp = zombie[closest].getHp();
            int zHp = previousHp - 10;
            cout << "Alien attacks zombie" << closest << ". " << endl
                 << "Zombie " << closest << "hp drops to " << zHp << ". " << endl;
            system("pause");

            game.display();
            system("pause");
        } 
        else if (next == 'r')
        {
            char objects[] = {' ', ' ', '<', '>', '^', 'h', 'p', 'v'};
            int noOfObjects = 8;
            int objNo = rand() % noOfObjects;
            game.display();
            cout << "Alien encounters a rock." << endl
                 << "Alien proceeds to uncover the rock." << endl;
            system("pause");

            game.setObject(x_, y_, objects[objNo]);
            game.display();

            if (objects[objNo] == ' ')
            {
                cout << "Alien found nothing beneath the rock." << endl;
            }

            else if (objects[objNo] == '<' || objects[objNo] == '>' || objects[objNo] == '^' || objects[objNo] == 'v')
            {
                cout << "Alien discovers an arrow beneath the rock." << endl;
            }

            else if (objects[objNo] == 'p')
            {
                cout << "Alien discovers a pod beneath the rock. " << endl;
            }

            else if (objects[objNo] == 'h')
            {
                cout << "Alien discovers a health kit beneath the rock. " << endl;
            }

            system("pause");

            game.display();
            system("pause");

            CState = 5; //stop
        }

        else if (next == '^')
        {
            game.display();
            cout << "Aliens finds an arrow." << endl;
            cout << "Alien's attack is increased by 20." << endl;
            atk_ = atk_ + 20;
            system("pause");
        }

        else if (next == 'v')
        { 
            cout << "Aliens finds an arrow." << endl;
            cout << "Alien's attack is increased by 20." << endl;
            atk_ = atk_ + 20;
            CState = 2; //down
            system("pause");
        }

        else if (next == '<')
        {
            cout << "Aliens finds an arrow." << endl;
            cout << "Alien's attack is increased by 20." << endl;
            atk_ = atk_ + 20;
            CState = 3; //left
            system("pause");
        }

        else if (next == '>')
        {
            cout << "Aliens finds an arrow." << endl;
            cout << "Alien's attack is increased by 20." << endl;
            atk_ = atk_ + 20;
            CState = 4; //right
            system("pause");
        }
    }
        
    else
    {
        game.display();
        cout << "Alien hits the border." << endl;
        CState = 5; //stop
        system("pause");
    }  
}

void Alien::alienLeft(int &CState, int nzombie, Board &game, Zombie *zombie)
{
    int x = x_ - 1;
    char next = game.getObject(x, y_);
    system("pause");
    
    if (game.isInsideBoard(x, y_))
    {
        if (next == ' ')
        {
            game.setObject(x_, y_, '.');
            setAlien(x, y_, game);
            game.display();
            cout << "Alien encounters nothing." << endl;
            system("pause");
        }
        else if (next == '.')
        {
            game.setObject(x_, y_, '.');
            setAlien(x, y_, game);
            game.display();
            cout << "Alien encounters nothing." << endl;
            system("pause");
        }
        else if (next == 'h')
        {
            game.setObject(x_, y_, '.');
            setAlien(x, y_, game);
            game.display();
            cout << "Alien picks up health pack." << endl
                 << "Alien's health increased from " << hp_;
            hp_ = hp_ + 20;
            cout << "to " << hp_ << "." << endl;
            system("pause");

            game.display();
            system("pause");
        }
        else if (next == 'p')
        {
            game.setObject(x_, y_, '.');
            setAlien(x, y_, game);
            int closest = 1;
            float smallestDistance = 39.59797975;

            for (int i = 1; i < nzombie; i++)
            {
                int x1 = zombie[i].getX();
                int y1 = zombie[i].getY();

                float distance = sqrt(pow((x1 - x_), 2.0) + pow((y1 - y_), 2.0));
                
                if (distance < smallestDistance)
                {
                    closest = i;
                }
            }
            
            int previousHp = zombie[closest].getHp();
            int zHp = previousHp - 10;
            cout << "Alien attacks zombie" << closest << ". " << endl
                 << "Zombie " << closest << "hp drops to " << zHp << ". " << endl;
            system("pause");

            game.display();
            system("pause");
        } 
        else if (next == 'r')
        {
            char objects[] = {' ', ' ', '<', '>', '^', 'h', 'p', 'v'};
            int noOfObjects = 8;
            int objNo = rand() % noOfObjects;
            game.display();
            cout << "Alien encounters a rock." << endl
                 << "Alien proceeds to uncover the rock." << endl;
            system("pause");

            game.setObject(x_, y_, objects[objNo]);
            game.display();

            if (objects[objNo] == ' ')
            {
                cout << "Alien found nothing beneath the rock." << endl;
            }

            else if (objects[objNo] == '<' || objects[objNo] == '>' || objects[objNo] == '^' || objects[objNo] == 'v')
            {
                cout << "Alien discovers an arrow beneath the rock." << endl;
            }

            else if (objects[objNo] == 'p')
            {
                cout << "Alien discovers a pod beneath the rock. " << endl;
            }

            else if (objects[objNo] == 'h')
            {
                cout << "Alien discovers a health kit beneath the rock. " << endl;
            }

            system("pause");

            game.display();
            cout << "Alien move ends." << endl;
            system("pause");

            CState = 5; //stop
        }

        else if (next == '^')
        {
            game.display();
            cout << "Aliens finds an arrow." << endl;
            cout << "Alien's attack is increased by 20." << endl;
            atk_ = atk_ + 20;
            CState = 3;
        }

        else if (next == 'v')
        { 
            game.display();
            cout << "Aliens finds an arrow." << endl;
            cout << "Alien's attack is increased by 20." << endl;
            atk_ = atk_ + 20;
            CState = 2; //down
            system("pause");
        }

        else if (next == '<')
        {
            game.display();
            cout << "Aliens finds an arrow." << endl;
            cout << "Alien's attack is increased by 20." << endl;
            atk_ = atk_ + 20;
            CState = 3; //left
            system("pause");
        }

        else if (next == '>')
        {
            game.display();
            cout << "Aliens finds an arrow." << endl;
            cout << "Alien's attack is increased by 20." << endl;
            atk_ = atk_ + 20;
            CState = 4; //right
            system("pause");
        }
    }
        
    else
    {
        game.display();
        cout << "Alien hits the border." << endl;
        CState = 5; //stop
        system("pause");
    }  
}

void Alien::alienRight(int &CState, int nzombie, Board &game, Zombie *zombie)
{
    int x = x_ + 1;
    char next = game.getObject(x, y_);
    system("pause");
    
    if (game.isInsideBoard(x, y_))
    {
        if (next == ' ')
        {
            game.setObject(x_, y_, '.');
            setAlien(x, y_, game);
            game.display();
            cout << "Alien encounters nothing." << endl;
            system("pause");
        }
        else if (next == '.')
        {
            game.setObject(x_, y_, '.');
            setAlien(x, y_, game);
            game.display();
            cout << "Alien encounters nothing." << endl;
            system("pause");
        }
        else if (next == 'h')
        {
            game.setObject(x_, y_, '.');
            setAlien(x, y_, game);
            game.display();
            cout << "Alien picks up health pack." << endl
                 << "Alien's health increased from " << hp_;
            hp_ = hp_ + 20;
            cout << "to " << hp_ << "." << endl;
            system("pause");
        }
        else if (next == 'p')
        {
            game.setObject(x_, y_, '.');
            setAlien(x, y_, game);
            int closest = 1;
            float smallestDistance = 39.59797975;

            for (int i = 1; i < nzombie; i++)
            {
                int x1 = zombie[i].getX();
                int y1 = zombie[i].getY();

                float distance = sqrt(pow((x1 - x_), 2.0) + pow((y1 - y_), 2.0));
                
                if (distance < smallestDistance)
                {
                    closest = i;
                }
            }
            
            int previousHp = zombie[closest].getHp();
            int zHp = previousHp - 10;
            cout << "Alien attacks zombie" << closest << ". " << endl
                 << "Zombie " << closest << "hp drops to " << zHp << ". " << endl;
            system("pause");

            game.display();
            system("pause");
        } 
        else if (next == 'r')
        {
            char objects[] = {' ', ' ', '<', '>', '^', 'h', 'p', 'v'};
            int noOfObjects = 8;
            int objNo = rand() % noOfObjects;
            game.display();
            cout << "Alien encounters a rock." << endl
                 << "Alien proceeds to uncover the rock." << endl;
            system("pause");

            game.setObject(x_, y_, objects[objNo]);
            game.display();

            if (objects[objNo] == ' ')
            {
                cout << "Alien found nothing beneath the rock." << endl;
            }

            else if (objects[objNo] == '<' || objects[objNo] == '>' || objects[objNo] == '^' || objects[objNo] == 'v')
            {
                cout << "Alien discovers an arrow beneath the rock." << endl;
            }

            else if (objects[objNo] == 'p')
            {
                cout << "Alien discovers a pod beneath the rock. " << endl;
            }

            else if (objects[objNo] == 'h')
            {
                cout << "Alien discovers a health kit beneath the rock. " << endl;
            }

            system("pause");

            CState = 5; //stop
        }

        else if (next == '^')
        {
            game.display();
            cout << "Aliens finds an arrow." << endl;
            cout << "Alien's attack is increased by 20." << endl;
            atk_ = atk_ + 20;
            system("pause");
        }

        else if (next == 'v')
        { 
            game.display();
            cout << "Aliens finds an arrow." << endl;
            cout << "Alien's attack is increased by 20." << endl;
            atk_ = atk_ + 20;
            CState = 2; //down
            system("pause");
        }

        else if (next == '<')
        {
            game.display();
            cout << "Aliens finds an arrow." << endl;
            cout << "Alien's attack is increased by 20." << endl;
            atk_ = atk_ + 20;
            CState = 3; //left
            system("pause");
        }

        else if (next == '>')
        {
            game.display();
            cout << "Aliens finds an arrow." << endl;
            cout << "Alien's attack is increased by 20." << endl;
            atk_ = atk_ + 20;
            CState = 4; //right
            system("pause");
        }
    }
        
    else
    {
        game.display();
        cout << "Alien hits the border." << endl;
        CState = 5; //stop
        system("pause");
    }
}


Zombie::Zombie()
{
    hp_ = (rand() % 5 + 2) * 50; 
    atk_ = (rand() % 5 + 1) * 5;
    range = rand() % 3 + 1;
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
    return range;
}

int Zombie::getZombieX() const
{
    return x_;
}

int Zombie::getZombieY() const
{
    return y_;
}

void Zombie::setHp(int hp)
{
    hp_ = hp;
}

void Zombie::setSymbol(char ch)
{
    symbol = ch;
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

void Zombie::movement(Board& game, Alien& alien)
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

void Zombie::attack(Alien& alien)
{
    int alienX = alien.getX();
    int alienY = alien.getY();

    // Check if alien is in range
    if (alienX >= x_ - range && alienX <= x_ + range && alienY >= y_ - range && alienY <= y_ + range)
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

void command(int &cst, int nzombie, Board &game, Alien &alien, Zombie *zombie)
{
    string command;
    cout << "Command => ";
    cin >> command;

    if (command == "up")
    {        
        game.display();
        cout << "Alien decides to move up." << endl;
        alien.alienUp(cst, nzombie, game, zombie);
        system("pause");

    }

    else if (command == "down")
    {
        game.display();
        cout << "Alien decides to move down." << endl;
        alien.alienDown(cst, nzombie, game, zombie);
        system("pause");
    }

    else if (command == "left")
    {
        game.display();
        cout << "Alien decides to move left." << endl;
        alien.alienLeft(cst, nzombie, game, zombie);
        system("pause");
    }

    else if (command == "right")
    {
        game.display();
        cout << "Alien decides to move right." << endl;
        alien.alienRight(cst, nzombie, game, zombie);
        system("pause");
    }

    // else if (command == "arrow")
    // {

    // }

    else if (command == "help")
    {
        cout << endl
             << "Commands" << endl
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
    }

    // else if (command == "save")
    // {

    // }

    // else if (command == "load")
    // {

    // }

    else if (command == "quit")
    {
    }

    else
    {
        cout << "Please enter a correct selection!" << endl
             << endl;
    }
}

int maingame()
{
    int ncolumn, nrow, nzombie;
    char settings;

    cout << "Default Game Settings" << endl;
    cout << "---------------------" << endl;
    cout << "Board Rows   : 5" << endl;
    cout << "Board Colums : 9" << endl;
    cout << "Zombie Count : 1" << endl;
    
    cout << "Do you wish to change the game settings (y/n)? => ";
    cin >> settings;

    while (true)
    {
    if (settings == 'y' | settings == 'Y')
    {
        cout << "Board Settings  " << endl;
        cout << "----------------" << endl;

        // Change the rows //
        cout << "Enter rows => ";
        cin >> nrow;
        while (true)
        {
            if (!cin)
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

        // Change the Columns //
        cout << "Enter columns => ";
        cin >> ncolumn;
        while (true)
        {
            if (!cin)
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
        cout << "" << endl;
        cout << "Enter number of zombies => ";
        cin >> nzombie;
        while (true)
        {
            if (!cin)
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
        break;
    }

    else if (settings == 'n' | settings == 'N')
    {
        ncolumn = 9;
        nrow = 5;
        nzombie = 1;
        break;
    }

    else
    {
        cout << "Please enter in only a character." << endl;
        cout << "Do you wish to change the game settings (y/n)? => ";
        cin >> settings;
        continue;
    }
    }

    int x1 = ncolumn/2 + 1;
    int y1 = nrow/2 + 1;
    char ch1 = 'A';
    
    Board game(ncolumn, nrow);
    Alien player(x1, y1, ch1);
    player.setAlien(x1, y1, game);
    Zombie zombie[9];

    // cout << "nzombie = " << nzombie;
    for (int i = 1; i <= nzombie; i++)
    {
        char ch = i + '0';
        zombie[i].setSymbol(ch);

        int x = rand() % ncolumn + 1;
        int y = rand() % nrow + 1;

        while (x == x1)
        {
            x = rand() % (ncolumn + 1);
        }

        while (y == y1)
        {
            y = rand() % (nrow + 1);
        }

        zombie[i].setZombie(x, y, game);
    }

    game.display();
    
    int cst = 0;

    cout << "Alien       : Life " 
         << player.getHp() << ", Attack" << player.getAtk() << endl;
    
    for (int i = 1; i <= nzombie; i++)
    { 
    cout << "Zombie " << i << "     : Life " 
         << zombie[i].getHp() << ", Range " << zombie[i].getRange() << endl << endl;
    }
    

    while (true)
    {
        command(cst, nzombie, game, player, zombie);
    if (cst == 1) // move up
    {
            cout << "Alien continues to move up." << endl;
            game.display();
            player.alienUp(cst, nzombie, game, zombie);
    }

    else if (cst == 2) // move down
    {
            cout << "Alien continues to move down." << endl;
            game.display();
            player.alienDown(cst, nzombie, game, zombie);
    }

    else if (cst == 3) // move left
    {
            cout << "Alien continues to move left." << endl;
            game.display();
            player.alienLeft(cst, nzombie, game, zombie);
    }

    else if (cst == 4) // move right
    {
            cout << "Alien continues to move right." << endl;
            game.display();
            player.alienRight(cst, nzombie, game, zombie);
    }

    else if (cst == 5) // stop
    {
            cout << "Alien move ends." << endl;
            for (int i = 1; i <= nzombie; i++)
            {
                zombie[i].action(game, player);
            }
    }

    continue;
    }
        
    
}


int main()
{
    srand(1); // use this for fixed map during testing
    // srand(time(NULL)); // try this for random map

    maingame();
    
}



