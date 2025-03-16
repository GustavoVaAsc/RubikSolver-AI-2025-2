#include<iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;
int main()
{
    srand(time(NULL));
    int numTests=5;
    cout<<numTests<<endl;
    for(int i=0;i<numTests;i++)
    {
        cout<<1+rand()%3<<" "<<rand()%3<<" "<<rand()%2<<endl;
    }
}