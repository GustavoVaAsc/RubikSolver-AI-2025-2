#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Cube
{
    int faces=6;
    int length=3;
    vector<vector<vector<int>>> cube;
    vector<int> aux; 
    vector<char> faceNames;
    queue<string> q;  
    public:
        Cube()
        {
            cube=vector<vector<vector<int>>> (faces,vector<vector<int>> (length,vector<int> (length)));
            aux=vector<int> (3);
            faceNames={'B','W','Y','O','R','G'};
            reset();
        }
        void mov1(int dir)
        {
            int f,start;
            if(dir>0)
            {
                start=0;
                f=1;
            }
            else{
                start=faces-3;
                f=-1;
            }
            for(int j=0;j<length;j++)
            {
                aux=cube[start][length];
            }
            for(int i=0;i<faces-2;i++)
            {
                for(int j=0;j<length;j++)
                {
                    //cube[i]
                }
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

        
    private:
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
};



int main()
{
    Cube game;
    game.reset();
    game.showCube();
    return 0;
}