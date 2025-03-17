#include<iostream>
#include "moves.cpp"
#include<stdlib.h>
#include<time.h>
#include<cmath>
#include<map>
#include<algorithm>
#include<stack>
#include<set>
#define all(v) v.begin(),v.end()
class Graph
{
    public:
        queue<vector<ll>> q;
        Cube game;
        map<vector<ll>,vector<ll>> path;
        set<vector<ll>> visited;
        map<vector<ll>,vector<int>> mov;
        vector<ll> f,s;
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
            s=aux;
            q.push(aux);
            path[aux]={-1};
            visited.insert(aux);
            if(finalState(aux))
            {
                f=aux;
                return;
            }
            vector<ll> neighbor,c;
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
                            /*if((i<3 && k==1) || (i==3 && k==0))
                            {
                                continue;
                            }*/
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
                                    break;
                            }
                            neighbor=game.getH();
                            c=neighbor;
                            sort(all(neighbor));
                            if(visited.find(neighbor)==visited.end())
                            {
                                path[c]=aux;
                                mov[aux]={i,j,k};
                                visited.insert(neighbor);
                                if(finalState(neighbor))
                                {
                                    f=c;
                                    return;
                                }
                                q.push(game.getH());
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
    g.bfs();
    end=clock();
    g.game.showCube();
    g.printPath();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout<<cpu_time_used<<endl;
    return 0;    
}