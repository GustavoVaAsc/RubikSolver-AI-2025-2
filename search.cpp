#include<iostream>
#include "moves.cpp"
#include<stdlib.h>
#include<time.h>
#include<cmath>
class Graph
{
    public:
        queue<vector<ll>> q;
        Cube game;
        Graph()
        {
            game.reset();
            //randomize();
        }
        void randomize()
        {
            srand(time(NULL));
            int t=rand()%100,opt=1+rand()%3;
            bool flag;
            int fila,columna,depth;
            while(t--)
            {
                switch(opt)
                {
                    case 1:
                        fila=rand()%3;
                        flag=rand()%2;
                        game.horizontal(flag,fila);
                        break;

                    case 2:
                        columna=rand()%3;
                        flag=rand()%2;
                        game.vertical(flag,columna);
                        break;
                    case 3:
                        depth=rand()%3;
                        flag=rand()%2;
                        game.rotar(flag,depth);
                        break;
                }
            }
        }
        bool finalState(vector<ll> h)
        {
            for(int i=0;i<game.faces;i++)
            {
                if(h[i]!=i*((pow(game.faces,game.length*game.length))-1)/(game.faces-1))
                {
                    return false;
                }
            }
            return true;
        }
        
    };

int main()
{
    Graph g;
    return 0;    
}