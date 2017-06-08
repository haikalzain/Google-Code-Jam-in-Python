#include<iostream>
#include<fstream>
#include<algorithm>

using namespace std;
int T, N, D;
ifstream infile;
ofstream outfile;
int main(){
    infile.open("C-large-practice (1).in");
    //infile.open("test.txt");
    outfile.open("out.txt");
    infile >> T;
    for(int t=1;t<=T;t++){
        infile >> N >> D;
        long long int result = 0;
        for(int k=D;k<=N;k+=D){
            for(int x=1;x<=N/k;x++){
                int n = N - k * x;
                int lowc = max(0, n - x + 1);
                int highc = n / 2;
                long long int add = max(highc - lowc + 1, 0);
                result += add;
                //cout<< k << " " << x << " left:" << n << " "<< add<<endl;
            }
        }

        outfile<<"Case #"<<t<<": "<< result<<endl;
    }
    infile.close();
    outfile.close();
    return 0;

}
