#include<iostream>
#include "moves.cpp"
#include<stdlib.h>
#include<time.h>
#include<cmath>
#include<map>
#include<algorithm>
#include<stack>
#include<set>
#include<fstream>

#define all(v) v.begin(),v.end()
#define X first 
#define Y second
class Graph
{
    public:
        priority_queue<pair<ll,Cube>> q;
        Cube game;
        map<Cube,Cube> path;
        set<Cube> visited;      
        map<Cube,vector<int>> mov;
        map<Cube,ll> dist;
        Cube f,s;
        Graph()
        {
            game.reset();
            randomize();
        }
        void randomize()
        {
            srand(time(NULL));
            int possibleMovs;
            int t=rand()%18,opt;
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
        
        bool finalPhase1(vector<ll> h)
        {
            if(h[1]==(pow(game.faces,game.length*game.length))-1/(game.faces-1)){
                return true;
            }
        }       

        ll heuPhase1(Cube v)
        {
            return 0;
        }

        void Astar()
        {
            Cube aux=game;
            s=aux;
            q.push({0,aux});
            visited.insert(aux);
            if(finalState(aux.getH()))
            {
                f=aux;
                return;
            }
            Cube neighbor;
            while(!q.empty())
            {
                aux=q.top().Y;
                q.pop();
                for(int i=1;i<=3;i++)
                {
                    for(int j=0;j<2;j++)
                    {
                        for(int k=0;k<3;k++)
                        {
                            if((i<3 && k==1) || (i==3 && k==0))
                            {
                                continue;
                            }
                            neighbor=aux;
                            switch(i)
                            {   
                                case 1:
                                    neighbor.horizontal(j,k);
                                    break;
                                case 2:
                                    neighbor.vertical(j,k);
                                    break;
                                case 3:
                                    neighbor.rotar(j,k);
                                    break;
                            }
                            if(visited.find(neighbor)==visited.end())
                            {
                                path[neighbor]=aux;
                                mov[aux]={i,j,k};
                                visited.insert(neighbor);
                                if(finalState(neighbor.getH()))
                                {
                                    f=neighbor;
                                    return;
                                }
                                q.push({0,neighbor});
                            }
                            
                        }
                    }
                }
            }
        }


        void printPath()
        {
            stack<vector<int>> pile;
            while(f!=s)
            {
                f=path[f];
                pile.push(mov[f]);
                
            }
            while(!pile.empty())
            {
                for(auto a:pile.top())
                {
                    cout<<a<<" ";
                }
                cout<<endl;
                pile.pop();
            }
        }
    };

int main()
{
    Graph g;
    g.game.showCube();
    clock_t start, end;
    double cpu_time_used;
    start=clock();
    g.Astar();
    end=clock();
    g.game.showCube();
    g.printPath();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout<<cpu_time_used<<endl;
    return 0;    
}