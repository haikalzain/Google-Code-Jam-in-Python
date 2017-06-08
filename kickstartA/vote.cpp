#include<iostream>
#include<fstream>
#include<algorithm>

using namespace std;
typedef long long int lint;

int T, N, M;
double dp[2010][2010] = {0};

int main(){
    ifstream infile;
    ofstream outfile;
    infile.open("A-large-practice.in");
    outfile.open("out.txt");

    infile >> T;
    for(int t=1;t<=T;t++){
        infile >> N >> M;
        fill_n(&dp[0][0], 2010 * 2010, 0);
        for(int i=0;i<=N;i++){
            for(int j=0;j<=M;j++){

                if(i==1 && j==0){
                    dp[i][j] = (double)N/(double)(N+M);
                }
                if(i==N && j==M){
                    break;
                }
                if(i > j){
                    dp[i+1][j] += dp[i][j] * (double)(N-i)/(double)((N-i) + (M-j));
                }
                if(i>j+1){
                    dp[i][j+1] += dp[i][j] * (double)(M-j) / (double)((N-i) + (M-j));
                }
            }
        }
        outfile.precision(6);
        //outfile << fixed;
        outfile << "Case #" << t << ": " << dp[N][M] << endl;
    }


    infile.close();
    outfile.close();
    return 0;
}
