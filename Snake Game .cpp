/**
  Project Name : Snake Game
  Developed by: Mehedi Hasan Robin

  Control:
  Up -> w
  Down -> s
  Left -> a
  Right -> d

*/
#include<iostream>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <time.h>
using namespace std;
#define SnakeMxSize 100
HANDLE console= GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
void gotoxy(int x,int y)
{
    CursorPosition.X=x;
    CursorPosition.Y=y;
    SetConsoleCursorPosition(console,CursorPosition);
}

class Point
{
private:
    int x,y;
public:
    Point()
    {
        x=y=10;
    }
    Point(int x,int y)
    {
        this->x=x;
        this->y=y;
    }
    void SetPoint(int x,int y)
    {
        this->x=x;
        this->y=y;
    }
    int GetX()
    {
        return x;
    }
    int GetY()
    {
        return y;
    }
    void MoveUp()
    {
        y--;
    }
    void MoveDown()
    {
        y++;
    }
    void MoveLeft()
    {
        x--;
    }
    void MoveRight()
    {
        x++;
    }
    void Draw()
    {
        gotoxy(x,y);
        cout<<"*";
    }
    void Erase()
    {
        gotoxy(x,y);
        cout<<" ";
    }
    void CopyPos(Point * p)
    {
        p->x=x;
        p->y=y;
    }
    void Debug()
    {
        cout<<"("<<x<<","<<y<<")";
    }
};

class Snake
{
private:
    Point * cell[SnakeMxSize]; //array of point to represent snake
    int siz; // current size of snake
    char dir; // current direction of snake
    Point fruit;
public:
    Snake()
    {
        siz=1; //default size
        Point a;
        cell[0]=new Point(20,20);//20,20 is default position
        for(int i=1; i<SnakeMxSize; i++)
        {
            cell[i]=NULL;
        }
        fruit.SetPoint(rand()%50,rand()%25);
    }

    void AddCell(int x,int y)
    {
        cell[siz++]= new Point(x,y);
    }
    void TurnUp()
    {
        dir='w'; // 'w' is control key for turning Upward
    }
    void TurnDown()
    {
        dir='s'; // 's' is control key for turning Downward
    }
    void TurnLeft()
    {
        dir='a'; // 'a' is control key for turning left
    }
    void TurnRight()
    {
        dir='d'; // 'd' is control key for turning Right
    }
    void Move()
    {
        //clear screen
         system("cls");

        //making snake body follow its head
        //cout<<siz<<endl;
        for(int i=siz-1; i>0; i--)
        {
            // cout<<"*"<<endl;
            cell[i-1]->CopyPos(cell[i]);
          // cell[i-1]->Debug();
           //cout<<endl;
        }

        // Turnig snake's head
        switch(dir)
        {
        case 'w':
            cell[0]->MoveUp();
            break;
        case 's':
            cell[0]->MoveDown();
            break;
        case 'a':
            cell[0]->MoveLeft();
            break;
        case 'd':
            cell[0]->MoveRight();
            break;
        }

        if(fruit.GetX()==cell[0]->GetX()&&fruit.GetY()==cell[0]->GetY())
        {
            AddCell(0,0);
            fruit.SetPoint(rand()%50,rand()%25);
        }
        // Drawing snake

        for(int i=0; i<siz; i++)
        {
            cell[i]->Draw();
            //cell[i]->Debug();
        }
        fruit.Draw();
        Sleep(100);
    }
    void Debug()
    {
        for(int i=0; i<siz; i++)
        {
            cell[i]->Debug();
        }
    }
};

int main()
{
    // Random no generation
    srand((unsigned) time(NULL));

    //Testing sanke
    Snake snake;
    char po='1';
    int a=1;
    do
    {
        // cout<<a<<endl;
        if(kbhit())
        {

            po=getch();
            // a=getch();
            // cout<<po<<endl;
        }
        //cout<<1<<endl;
        //cout<<po<<endl;
        switch(po)
        {
        case 'w':
        case 'W':
            snake.TurnUp();
            break;
        case 's':
        case 'S':
            snake.TurnDown();
            break;
        case 'a':
        case 'A':
            snake.TurnLeft();
            break;
        case 'd':
        case 'D':
            snake.TurnRight();
            break;
        }
        snake.Move();
    }
    while(po!='e');
    return 0;
}
