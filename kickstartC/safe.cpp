#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;

typedef long long int lint;

int T, R, C, K;
int monsters[3010][3010];
int prefix[3010][3010];

int countMonsters(int r1, int c1, int r2, int c2){//inclusive
    return monsters[r2][c2] - monsters[r2][c1-1] - monsters[r1-1][c2] + monsters[r1-1][c1-1];
}

int main(){
    ifstream infile;ofstream outfile;
    infile.open("B-large-practice.in");
    outfile.open("out.txt");

    infile >> T;
    for(int t=1;t<=T;t++){
        //initialize
        infile >> R >> C >> K;
        fill_n(&monsters[0][0], 3010 *3010, 0);
        //fill_n(&prefix[0][0], (R+10) * (C+10), 0);
        for(int i=0;i<K;i++){
            int rx,cx;
            infile >> rx >> cx;
            monsters[rx+1][cx+1] = 1;
        }
        for(int i=1;i<=R;i++){
            for(int j=1;j<=C;j++){
                monsters[i][j] += monsters[i-1][j] + monsters[i][j-1] - monsters[i-1][j-1];
            }
        }
        lint total = 0;
        for(int i=1;i<=R;i++){
            for(int j=1;j<=C;j++){
                int lo = 1, mid, hi=min(R-i+1,C-j+1);
                int best = 0;
                while(hi>=lo){
                    mid = (hi + lo)/2;
                    if(countMonsters(i, j, i + mid -1, j+mid-1)){
                        hi = mid - 1;
                    }
                    else{
                        best = max(best, mid);
                        lo = mid + 1;
                    }

                }
                //cout << i << " " << j << " best: " << best << endl;
                total += best;
            }
        }
       /* for(int i=1;i<=R;i++){
            for(int j=1;j<=C;j++){
                cout << monsters[i][j] << " ";
            }
            cout << endl;
        }*/
        outfile<< "Case #" << t << ": " << total << endl;


    }
    return 0;
}
