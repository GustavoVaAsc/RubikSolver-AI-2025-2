#include<iostream>
#include "moves.cpp"
#include<stdlib.h>
#include<time.h>
#include<cmath>
#include<map>
#include<algorithm>
#include<stack>
#define all(v) v.begin(),v.end()
class Graph
{
    public:
        queue<vector<ll>> q;
        Cube game;
        map<vector<ll>,vector<ll>> path;
        map<vector<ll>,vector<ll>> moves;
        Graph()
        {
            game.reset();
            randomize();
        }
        void randomize()
        {
            srand(time(NULL));
            int t=rand()%10,opt;
            bool flag;
            int fila,columna,depth;
            while(t--)
            {
                opt=1+rand()%3;
                
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
        void bfs()
        {
            vector<ll> aux=game.getH();
            q.push(aux);
            path[aux]={-1};
            if(finalState(aux))
            {
                return;
            }
            vector<ll> neighbor;
            while(!q.empty())
            {
                aux=q.front();
                q.pop();
                for(int i=1;i<=3;i++)
                {
                    for(int j=0;j<2;j++)
                    {
                        for(int k=0;k<3;k++)
                        {
                            game.reconstruct(aux);
                            switch(i)
                            {   
                                case 1:
                                    game.horizontal(j,k);
                                    break;
                                case 2:
                                    game.vertical(j,k);
                                    break;
                                case 3:
                                    game.rotar(j,k);
                            }
                            neighbor=game.getH();
                            path[neighbor]=aux;
                            sort(all(neighbor));
                            if(finalState(neighbor))
                            {
                                return;
                            }
                            if(path.count(neighbor)==0)
                            {
                                q.push(game.getH());
                            }
                            
                        }
                    }
                }
            }
        }

        void printPath()
        {
            vector<ll> p=path[game.getH()];
            vector<int> s;
            while(p[0]!=-1)
            {
                p=path[p];
                
            }
        }
    };

int main()
{
    Graph g;
    g.game.showCube();
    g.bfs();
    g.game.showCube();
    g.printPath();
    
    return 0;    
}