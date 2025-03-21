#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#define X first 
#define Y second
#define all(v) v.begin(),v.end()
using namespace std;
typedef long long ll;

class Cell
{
    public:
        int color,face,x,y;
        Cell()
        {

        }
        Cell(int color, int face,int x,int y)
        {
            this->color=color;
            this->face=face;
            this->x=x;
            this->y=y;
        }
};


class Cube
{
    public:
    int faces,length,sides,sz;
    vector<vector<vector<Cell>>> cube;
    vector<char> faceNames; 
        Cube()
        {
            length=3;
            faces=6;
            sides=4;
            cube=vector<vector<vector<Cell>>> (faces,vector<vector<Cell>> (length,vector<Cell> (length)));
            faceNames={'N','B','R','A','G','Y'};
            reset();
        }

        void horizontal(bool right, int fila) {
            // Add center protection
            if (fila == 1) {  // Middle layer
                // Only swap edge pieces, keep centers fixed
                for(int i = 0; i < length; i++) {
                    if (i == 1) continue; // Skip center column
                    Cell aux;
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
            } else {
                // Original horizontal move logic
                Cell aux;
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
        }
        /*
        void horizontal(bool right,int fila)
        {
            Cell aux;
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
        */
        void vertical(bool up,int columna)
        {
            Cell aux;
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
            Cell aux;
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
                        cube[i][j][k].color=i;
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
                    cout<<faceNames[cube[j/length][i][j%length].color]<<"  ";
                }
                cout<<endl;
            }
            showFace(5,"\t ");
        }

        void rotateFace(int face, bool right) {
            Cell aux;
            pair<int,int> cor,pastCor;
            // Add center protection for 3x3 cubes
            if (length == 3) {
                // Preserve center color
                Cell center = cube[face][1][1];
                // Perform rotation
                for(int i = 0; i < (length+1)/2; i++) {
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
                // Restore center position
                cube[face][1][1] = center;
            } else {
                // Original rotation logic
                for(int i = 0; i < (length+1)/2; i++) {
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
        }
         /**
        void rotateFace(int face,bool right)
        {
            Cell aux;
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
            */
        void showFace(int id,string stline) 
        {
            for(int i=0;i<length;i++)
            {
                cout<<stline;
                for(int j=0;j<length;j++)
                {
                    cout<<faceNames[cube[id][i][j].color]<<"  ";
                }
                cout<<endl;
            }
        }
        

        pair<int,int> getCoord(bool right, pair<int,int> actualcoord) {
            pair<int,int> newCord;
            
            // Handle center cell (1,1) for 3x3 cube
            if (length == 3 && actualcoord.X == 1 && actualcoord.Y == 1) {
                return actualcoord; // Center never moves
            }
    
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
        /*
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
        */
        vector<ll> getH() const
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
                        h[i]+=base*cube[i][j][k].color;
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
                        cube[i][j][k].color=h[i]%faces;
                        h[i]/=faces;
                    }
                }
            }
        }
        
        bool operator==(Cube& other) 
        {
            vector<ll> a=getH(),b=other.getH();
            sort(all(a));
            sort(all(b));
            return a==b;
        }

        bool operator!=(const Cube& other) const
        {
            return this->getH()!=other.getH();
        }
        bool operator<(const Cube& other) const 
        {
            return this->getH()<other.getH();
        }
    
        // Sobrecargar el operador <=
        bool operator<=(const Cube& other) const 
        {
            return this->getH()<=other.getH();
        }
    
        // Sobrecargar el operador >
        bool operator>(const Cube& other) const {
            return !(this->getH() <= other.getH());
        }
    
        // Sobrecargar el operador >=
        bool operator>=(const Cube& other) const 
        {
            return !(this->getH() < other.getH());
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