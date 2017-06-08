#include<iostream>
#include<fstream>
#include<algorithm>

using namespace std;
typedef long long int lint
int T, N;
lint M = 1000000000000000000;


int main(){
    ifstream infile;
    ofstream outfile;
    infile >> T;
    for(int t=1;t<T+1;t++){
        infile >> N;
        for(int k=59;k>=1;k--){
            lint lo=2,mid,hi=M;
            while(lo<hi){
                mid = (lo + hi)/2;

                if( (pow(mid, k+1) - 1)/(mid - 1) == N){

                }

            }
        }
        cout<<"Case #"<<t<<": "<< endl;
    }


}
