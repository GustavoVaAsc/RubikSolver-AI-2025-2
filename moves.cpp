#include<iostream>
#include<vector>
#include<queue>
#define X first 
#define Y second
using namespace std;
typedef long long ll;
class Cube
{
    public:
    int faces,length,sides,sz;
    vector<vector<vector<int>>> cube;
    vector<char> faceNames;
    
        Cube()
        {
            length=3;
            faces=6;
            sides=4;
            cube=vector<vector<vector<int>>> (faces,vector<vector<int>> (length,vector<int> (length)));
            faceNames={'N','G','R','A','B','Y'};
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
                    cube[5][i][columna]=cube[3][length-1-i][length-1-columna];
                    cube[3][length-1-i][length-1-columna]=aux;
                }
            }
            else
            {
                for(int i=0;i<length;i++)
                {
                    aux=cube[5][i][columna];
                    cube[5][i][columna]=cube[1][i][columna];
                    cube[1][i][columna]=cube[4][i][columna];
                    cube[4][i][columna]=cube[3][length-1-i][length-1-columna];
                    cube[3][length-1-i][length-1-columna]=aux;
                }
            }
            if(columna==0)
            {
                rotateFace(0,!up);
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
                    cube[0][length-1-i][depth]=cube[5][length-1-depth][length-1-i];
                    cube[5][length-1-depth][length-1-i]=cube[2][i][length-1-depth];
                    cube[2][i][length-1-depth]=aux;
                }
            }
            else{
                for(int i=0;i<length;i++)
                {
                    aux=cube[4][depth][i];
                    cube[4][depth][i]=cube[2][i][length-1-depth];
                    cube[2][i][length-1-depth]=cube[5][length-1-depth][length-1-i];
                    cube[5][length-1-depth][length-1-i]=cube[0][length-1-i][depth];
                    cube[0][length-1-i][depth]=aux;
                }
            }
            if(depth==length-1)
            {
                rotateFace(1,right);
            }
            if(depth==0)
            {
                rotateFace(3,!right);
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
                    cout<<faceNames[cube[j/length][i][j%length]]<<"  ";
                }
                cout<<endl;
            }
            showFace(5,"\t ");
        }
        void rotateFace(int face,bool right)
        {
            int aux;
            pair<int,int> cor,pastCor;
            for(int i=0;i<(length+1)/2;i++)
            {
                aux=cube[face][0][i];
                cor.X=0; cor.Y=i;
                for(int j=0;j<sides-1;j++)
                {
                    pastCor=getCoord(!right,cor);
                    cube[face][cor.X][cor.Y]=cube[face][pastCor.X][pastCor.Y];
                    cor=pastCor;
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
                    cout<<faceNames[cube[id][i][j]]<<"  ";
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
                    return newCord;
                }
                else{
                    newCord.X=length-1-actualcoord.Y;
                    newCord.Y=0;
                    return newCord;
                }
            }
            if(actualcoord.Y==0)
            {
                if(right)
                {
                    newCord.X=0;
                    newCord.Y=actualcoord.X;
                    return newCord;
                }
                else{
                    newCord.X=length-1;
                    newCord.Y=actualcoord.X;
                    return newCord;
                }
            }
            if(actualcoord.X==length-1)
            {
                if(right)
                {
                    newCord.Y=0;
                    newCord.X=actualcoord.Y;
                    return newCord;
                }
                else
                {
                    newCord.X=length-1-actualcoord.Y;
                    newCord.Y=length-1;
                    return newCord;
                }
            }
            if(actualcoord.Y==length-1)
            {
                if(right)
                {
                    newCord.X=length-1;
                    newCord.Y=length-1-actualcoord.X;
                    return newCord;
                }
                else{
                    newCord.X=0;
                    newCord.Y=actualcoord.X;
                    return newCord;
                }
            }
            return newCord;
            
        }
        vector<ll> getH()
        {
            vector<ll> h(faces);
            ll base,sum;
            for(int i=0;i<faces;i++)
            {
                base=1;
                for(int j=0;j<length;j++)
                {
                    for(int k=0;k<length;k++)
                    {
                        h[i]+=base*cube[i][j][k];
                        base*=faces;
                    }
                }
            }
            return h;
        } 
        void reconstruct(vector<ll> h)
        {
            for(int i=0;i<faces;i++)
            {
                for(int j=0;j<length;j++)
                {
                    for(int k=0;k<length;k++)
                    {
                        cube[i][j][k]=h[i]%faces;
                        h[i]/=faces;
                    }
                }
            }
        }
};



/*int main()
{
    Cube game;
    int t=0; cin>>t;
    while(t--)
    {
        game.showCube();
        cout<<"1 Para movimiento horizontal\n2 Para vertical\n3 Para rotar\n";
        int opt;bool flag;
        cin>>opt;
        switch(opt)
        {
            case 1:
                int fila;
                cin>>fila>>flag;
                game.horizontal(flag,fila);
                break;

            case 2:
                int columna;
                cin>>columna>>flag;
                game.vertical(flag,columna);
                break;
            case 3:
                int depth;
                cin>>depth>>flag;
                game.rotar(flag,depth);
                break;
        }
    }
    return 0;
}*/