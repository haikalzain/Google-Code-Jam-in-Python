#include<iostream>
#include<algorithm>
#include<set>
#include<fstream>
#include<cstdlib>

using namespace std;

int T, N, M ,Q;
int V[1010];
int P[110], H[110];
int INF = 1000000000;
int dp[110][10010];
int bestV[110][110];
ifstream infile;
ofstream outfile;

int main(){
    infile.open("B-large-practice.in");
    outfile.open("out.txt");
    infile >> T;
    for(int t=1;t<=T;t++){
        infile >> N >> M >> Q;
        fill_n(&bestV[0][0], 110 * 110, INF);
        fill_n(&dp[0][0], 110 * 10010, INF);
        for(int i=0;i<M;i++)infile >> V[i];
        for(int i=0;i<N;i++)infile >> P[i] >> H[i];
        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++){
                if(P[i] * V[j] < 0){
                    bestV[i][abs(V[j])] = min(bestV[i][abs(V[j])], abs(j - H[i]));
                }
            }
        }
        for(int n=N; n>=0; n--){
            for(int q=0; q<=Q;q++){
                if(n == N){
                    dp[n][q] = 0;
                }
                else{
                    if(P[n] == 0){
                        dp[n][q] = dp[n+1][q];
                    }
                    else for(int v=1;v<=100;v++){
                        int qi = bestV[n][v];
                        int p = abs(P[n]);
                        if(q >= qi){
                            dp[n][q] = min(dp[n][q], max(dp[n+1][q-qi], p/v + (p%v !=0) ));
                        }
                    }
                }
            }
        }
        outfile << "Case #" << t << ": ";
        if(dp[0][Q] == INF) outfile << "IMPOSSIBLE" << endl;
        else outfile << dp[0][Q] << endl;
    }
    infile.close();
    outfile.close();
    return 0;
}
