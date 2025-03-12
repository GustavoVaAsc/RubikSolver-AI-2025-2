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
        void mov1(bool right)
        {
            int aux;
            if(right)
            {
                for(int i=0;i<length;i++)
                {
                    aux=cube[faces-3][0][i];
                    for(int j=faces-3;j>0;j--)
                    {
                        cube[j][0][i]=cube[j-1][0][i];
                    }
                    cube[0][0][i]=aux;
                }
            }
            else
            {
                for(int i=0;i<length;i++)
                {
                    aux=cube[0][0][i];
                    for(int j=0;j<faces-3;j++)
                    {
                        cube[j][0][i]=cube[j+1][0][i];
                    }
                    cube[faces-3][0][i]=aux;
                }
            }
            //rotate(4,true);
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
        void rotate(int face,bool right)
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
    game.mov1(false);
    game.showCube();
    return 0;
}