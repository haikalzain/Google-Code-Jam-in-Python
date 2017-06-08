#include<iostream>
#include<fstream>
#include<algorithm>

using namespace std;

int T, R, C, r, c;
int seats(int n, int mod){
    int x =0;
    for(int i =1;i<=n;i++){
        if(i%3 !=mod){
            x++;
        }
    }
    return x;
}

int solve(int R, int C){
    int result = 0;
    if(R==2){
        result = 2 * seats(C, 0);
    }
    else{
        for(int i=0;i<R;i++){
            result += seats(C, i % 3);
        }
    }
    return result;

}

int main(){
    ifstream infile;
    ofstream outfile;
    infile.open("B-large-practice.in");
    //infile.open("test.txt");
    outfile.open("out.txt");

    cout << seats(2, 0);
    cout << seats(1, 0);

    infile >> T;
    for(int t=1;t<=T;t++){
        infile >> r >> c;
        outfile << "Case #" << t << ": " << max(solve(r,c), solve(c, r)) << endl;
    }


    infile.close();
    outfile.close();
}
