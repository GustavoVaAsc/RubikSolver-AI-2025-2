#include<iostream>
#include<vector>
#include<queue>
#define X first 
#define Y second
using namespace std;

class Cube
{
    int faces=6;
    int length=3;
    int sides=4;
    vector<vector<vector<int>>> cube;
    vector<char> faceNames;
    queue<string> q;  
    public:
        Cube()
        {
            cube=vector<vector<vector<int>>> (faces,vector<vector<int>> (length,vector<int> (length)));
            faceNames={'B','W','Y','O','R','G'};
            reset();
        }
        void horizontal(bool right,int fila)
        {
            int aux;
            if(right)
            {
                for(int i=0;i<length;i++)
                {
                    aux=cube[faces-3][fila][i];
                    for(int j=faces-3;j>0;j--)
                    {
                        cube[j][fila][i]=cube[j-1][fila][i];
                    }
                    cube[0][fila][i]=aux;
                }
            }
            else
            {
                for(int i=0;i<length;i++)
                {
                    aux=cube[0][fila][i];
                    for(int j=0;j<faces-3;j++)
                    {
                        cube[j][fila][i]=cube[j+1][fila][i];
                    }
                    cube[faces-3][fila][i]=aux;
                }
            }
            if(fila==0)
                rotateFace(4,right);
            if(fila==length-1)
                rotateFace(5,right);
        }
        
        void vertical(bool up,int columna)
        {
            int aux;
            if(up)
            {
                for(int i=0;i<length;i++)
                {
                    aux=cube[4][i][columna];
                    cube[4][i][columna]=cube[1][i][columna];
                    cube[1][i][columna]=cube[5][i][columna];
                    cube[5][i][columna]=cube[3][i][length-1-columna];
                    cube[3][i][length-1-columna]=aux;
                }
            }
            else
            {
                for(int i=0;i<length;i++)
                {
                    aux=cube[5][i][columna];
                    cube[5][i][columna]=cube[1][i][columna];
                    cube[1][i][columna]=cube[4][i][columna];
                    cube[4][i][columna]=cube[3][i][length-1-columna];
                    cube[3][i][length-1-columna]=aux;
                }
            }
            if(columna==0)
            {
                rotateFace(0,up);
            }
            if(columna==length-1){
                rotateFace(2,up);
            }
        }

        void rotar(bool right,int depth)
        {
            int aux;
            if(right)
            {
                for(int i=0;i<length;i++)
                {
                    aux=cube[4][depth][i];
                    cube[4][depth][i]=cube[0][length-1-i][depth];
                    cube[0][length-1-i][depth]=cube[5][length-1-depth][length-i];
                    cube[5][length-1-depth][length-i]=cube[2][i][length-1-depth];
                    cube[2][i][length-1-depth]=aux;
                }
            }
            else{
                for(int i=0;i<length;i++)
                {
                    aux=cube[4][depth][i];
                    cube[4][depth][i]=cube[2][i][length-1-depth];
                    cube[2][i][length-1-depth]=cube[5][depth][i];
                    cube[5][depth][i]=cube[0][i][length-1-depth];
                    cube[0][i][length-1-depth]=aux;
                }
            }
            if(depth==length-1)
            {
                rotateFace(right,1);
            }
            if(depth==0)
            {
                rotateFace(!right,3);
            }
        }

        void reset()
        {
            for(int i=0;i<faces;i++)
            {
                for(int j=0;j<length;j++)
                {
                    for(int k=0;k<length;k++)
                    {
                        cube[i][j][k]=i;
                    }
                }
            }
        }
        void showCube()
        {
            showFace(4,"\t ");
            for(int i=0;i<length;i++)
            {
                for(int j=0;j<length*(faces-2);j++)
                {
                    cout<<cube[j/length][i][j%length]<<"  ";
                }
                cout<<endl;
            }
            showFace(5,"\t ");
        }
        void rotateFace(int face,bool right)
        {
            int aux;
            pair<int,int> cor,newCor;
            for(int i=0;i<length;i++)
            {
                aux=cube[face][0][i];
                cor.X=0; cor.Y=i;
                for(int j=0;j<sides-1;j++)
                {
                    newCor=getCoord(right,cor);
                    cube[face][cor.X][cor.Y]=cube[face][newCor.X][newCor.Y];
                    cor=newCor;
                }
                cube[face][cor.X][cor.Y]=aux;
            }
        }
        void showFace(int id,string stline)
        {
            for(int i=0;i<length;i++)
            {
                cout<<stline;
                for(int j=0;j<length;j++)
                {
                    cout<<cube[id][i][j]<<"  ";
                }
                cout<<endl;
            }
        }
        pair<int,int> getCoord(bool right,pair<int,int> actualcoord)
        {
            pair<int,int> newCord;
            if(actualcoord.X==0)
            {
                
                if(right)
                {
                    newCord.X=actualcoord.Y;
                    newCord.Y=length-1;
                }
                else{
                    newCord.X=length-1-actualcoord.Y;
                    newCord.Y=0;
                }
            }
            if(actualcoord.Y==0)
            {
                if(right)
                {
                    newCord.X=0;
                    newCord.Y=actualcoord.X;
                }
                else{
                    newCord.X=length-1;
                    newCord.Y=actualcoord.X;
                }
            }
            if(actualcoord.X==length-1)
            {
                if(right)
                {
                    newCord.Y=length-1;
                    newCord.X=length-1-actualcoord.Y;
                }
                else
                {
                    newCord.X=actualcoord.Y;
                    newCord.Y=0;
                }
            }
            if(actualcoord.Y==length-1)
            {
                if(right)
                {
                    newCord.X=length-1;
                    newCord.Y=length-1-actualcoord.X;
                }
                else{
                    newCord.X=0;
                    newCord.Y=actualcoord.X;
                }
            }
            return newCord;
            
        }
};



int main()
{
    Cube game;
    while(true)
    {
        game.showCube();
        cout<<"1 Para movimiento horizontal\n2 Para vertical\n3Para ";
        int opt;
        cin>>opt;
        if(opt)
        {
            bool flag;
            int fila;
            cin>>fila>>flag;
            game.horizontal(flag,fila);
        }
        else{
            bool flag;
            int columna;
            cin>>columna>>flag;
            game.vertical(flag,columna);
        }
    }
    return 0;
}