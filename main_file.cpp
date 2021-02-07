#include<iostream>
#include<math.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>

using namespace std;

bool gameOver;

const int width=20;
const int height=20;

int x, y, fruitX, fruitY, score;
int ntail;
int tailX[200], tailY[200];
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN} ;

eDirection dir;

void setup()
{
    gameOver=false;
    dir = STOP;

    x= width / 2;
    y = height / 2;

    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void draw()
{
        system("cls");
       // sleep(20);
        for(int i=0;i< width+2;i++)
            cout <<"#";
        cout << endl;

        for(int i=0;i<height;i++)
        {
            for(int j=0;j<width+2;j++)
            {
                if(j==0)
                    cout<<"#";
                if(j==width)
                    cout<<"#";
                if(i== y && j ==x)
                    cout<<"O";
                else if(i == fruitY && j == fruitX)
                    cout<<"F";
                else
                {
                    bool print = false;
                    for(int k=0;k<ntail;k++)
                    {
                        if(tailX[k] == j && tailY[k] == i)
                        {
                            cout<<"o";
                            print = true;
                        }

                    }
                    if(!print)
                        cout<<" ";
                }

            }
            cout<<endl;
        }


        for(int i=0;i<width+2;i++)
            cout<<"#";
        cout << endl;
        cout<<" Score Is: "<<score<<endl;
}

void input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
        }
    }

}

void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];

    int prev2X, prev2Y;
    tailX[0]=x;
    tailY[0]=y;
    for(int i=1;i<ntail;i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(dir)
    {

    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;

    }

    //if(x>width || x<0 || y>height || y<0)
      //
      //  gameOver = true;

    if(x>=width) x = 0; else if(x<0) x = width-1;
    if(y>=height) y = 0; else if(y<0) y = height-1;

    for(int i=0;i<ntail;i++)
    {
        if(tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }
    if(x == fruitX && y == fruitY)
    {
        score+=10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        ntail++;
    }

}

int main()
{
    setup();
    while(!gameOver)
    {
        draw();
        input();
        logic();
        Sleep(50);
    }
}
