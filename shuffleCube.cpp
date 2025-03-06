#include<iostream>
#include<vector>

using namespace std;

class Cube
{
    int faces=6;
    int length=3;
    int cube[6][3][3];   
    char faceNames[6]={'B','W','Y','O','R','G'};
    public:
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
            cout<<"\t\t";
            showFace(4);
            for(int i=0;i<length;i++)
            {
                for(int j=0;j<length*length;j++)
                {
                    cout<<cube[j/length][i][j%length]<<" ";
                }
                cout<<endl;
            }
            cout<<"\t\t";
            showFace(5);
        }

        void mov1()
        {

        }
    private:
        void showFace(int id)
        {
            for(int i=0;i<length;i++)
            {
                for(int j=0;j<length;j++)
                {
                    cout<<cube[id][i][j]<<" ";
                }
                cout<<endl;
            }
        }
};



int main()
{
    return 0;
}