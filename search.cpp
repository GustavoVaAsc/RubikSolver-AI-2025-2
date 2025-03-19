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

class CubeItem
{
    public:
        vector<vector<int>> v;
        int faces=0;
        CubeItem(){}
        CubeItem(vector<vector<int>> v,int faces)
        {
            this->faces=faces;
            this->v=v;
        }
        int getH(Cube a)
        {
            int sum=0,base=1;
            for(int i=0;i<v.size();i++)
            {
                sum+=(a.cube[v[i][0]][v[i][1]][v[i][2]].color)*base;
                base*=faces;
            }
            return sum;
        }
        
};

class Graph
{
    public:
        priority_queue<pair<ll,Cube>> q;
        Cube game;
        map<Cube,Cube> path;
        set<Cube> visited; 
        map<vector<ll>,ll> visitedC;     
        map<Cube,vector<int>> mov;
        map<Cube,ll> dist;
        vector<CubeItem> corners;
        vector<CubeItem> edges;
        
        int num_corners;
        int num_edges;
        Graph()
        {
            num_corners=8;
            game.reset();
            corners=vector<CubeItem> (num_corners);
            corners[0]=CubeItem({{0,0,2},{4,2,0},{1,0,0}},game.faces);
            corners[1]=CubeItem({{1,0,2},{4,2,2},{2,0,0}},game.faces);
            corners[2]=CubeItem({{0,2,2},{1,2,0},{5,0,0}},game.faces);
            corners[3]=CubeItem({{1,2,2},{2,2,0},{5,0,2}},game.faces);
            corners[4]=CubeItem({{0,0,0},{4,0,0},{3,0,2}},game.faces);
            corners[5]=CubeItem({{4,0,2},{2,0,2},{3,0,0}},game.faces);
            corners[6]=CubeItem({{5,2,2},{2,2,2},{3,2,0}},game.faces);
            corners[7]=CubeItem({{5,2,0},{3,2,2},{0,2,0}},game.faces);
            randomize();
        }
        void randomize()
        {
            srand(time(NULL));
            int possibleMovs;
            int t=rand()%8,opt;
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
        
        vector<ll> getCorners(Cube a)
        {
            int div=2;
            vector<ll> h(div);
            int i;
            for(int j=0;j<div;j++)
            {
                ll base=1;
                for(i=j*num_corners/div;i<(j+1)*num_corners/div;i++)
                {
                    h[j]+=corners[i].getH(a)*base;
                    base*=pow(game.faces,3);
                }
            }
            return h;
        }
        
        void printCor(Cube a)
        {
            for(auto c:getCorners(a))
            {
                cout<<c<<" ";
            }
        }

        void  bfsCor()
        {
            queue<Cube> p;
            game.reset();
            Cube s=game,aux,neighbor;
            p.push(s);
            //s.showCube();
            visitedC[getCorners(s)]=0;
            printCor(s);
            cout<<0<<endl;
            while(!p.empty())
            {
                aux=p.front();
                p.pop();
                for(int i=1;i<=3;i++)
                {
                    for(int j=0;j<2;j++)
                    {
                        for(int k=0;k<3;k++)
                        {
                            if(k==1) continue;
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
                            Cube c=neighbor;
                            if(visitedC.find(getCorners(neighbor))==visitedC.end())
                            {
                                int x=0;
                                x=visitedC[getCorners(aux)]+1;
                                visitedC[getCorners(neighbor)]=x;
                                printCor(neighbor);
                                cout<<x<<endl;
                                p.push(neighbor);
                            }
                            
                            
                        }
                    }
                }
            }
        }

        void Astar(Cube s,Cube f,int lookPattern)
        {
            q.push({0,s});
            visited.insert(s);
            if(f==s)
            {
                return;
            }
            Cube neighbor,aux;
            int d=0;
            while(!q.empty())
            {
                aux=q.top().Y;
                d++;
                q.pop();
                for(int i=1;i<=3;i++)
                {
                    for(int j=0;j<2;j++)
                    {
                        for(int k=0;k<3;k++)
                        {
                            if(k==1) continue;
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
                            Cube c=neighbor;
                            if(visited.find(neighbor)==visited.end())
                            {
                                if(lookPattern==1)
                                {
                                    for(ll c:getCorners(neighbor))
                                    {
                                        cout<<c<<" ";
                                    }
                                    cout<<d<<endl;;
                                }
                                path[neighbor]=aux;
                                mov[aux]={i,j,k};
                                visited.insert(neighbor);
                                if(neighbor==f)
                                {
                                    return;
                                }
                                q.push({0,neighbor});
                            }
                            
                        }
                    }
                }
            }
        }


        void printPath(Cube f,Cube s)
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
    int lookP=1;
    if(lookP==0)
        g.game.showCube();
    clock_t start, end;
    double cpu_time_used;
    start=clock();
    Cube f,s;
    switch(lookP)
    {
        case 0:
            g.randomize();
            s=g.game;
            g.game.reset();
            f=g.game;
            break;
        case 1:
            g.randomize();
            f=g.game;
            g.game.reset();
            s=g.game;
            break;
    }
    g.bfsCor();
    //g.Astar(f,s,1);
    end=clock();
    if(lookP==0)
    {
        g.game.showCube();
        g.printPath(f,s);
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout<<cpu_time_used<<endl;
    }
    return 0;    
}