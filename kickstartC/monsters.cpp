#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<utility>
#include<cassert>
#include<set>
#include<cmath>

using namespace std;

typedef pair<int,int> ii;
ifstream infile;
ofstream outfile;
//vector<ii> visited;
int visited[30][30];

int T;
int R, C, Rs, Cs, S;
double P, Q;
double best = 0;

char squares[30][30];

int rx[4] = {0, 0, -1, 1};
int cx[4] = {1, -1, 0, 0};

void dfs(int r, int c, int step, double total){
    if(step == S){
        best = max(best, total);
        return;
    }

    for(int i=0;i<4;i++){
        int newr = r + rx[i];
        int newc = c + cx[i];
        if(newr >=0 && newr < R && newc >=0 &&newc < C){
            double prob;
            if(squares[newr][newc] == 'A') prob = P;
            else prob = Q;
            double value = prob * pow(1-prob, visited[newr][newc]);
            visited[newr][newc]++;
            dfs(newr, newc, step+1, total + value);
            visited[newr][newc]--;
        }

    }

}

int main(){
    infile.open("A-large-practice.in");
    //infile.open("test.txt");
    outfile.open("out.txt");
    outfile << fixed;
    infile >> T;
    for(int t=1;t<=T;t++){
        fill_n(&visited[0][0], 30*30, 0);
        best = 0;
        infile >> R >> C >> Rs >> Cs >> S;
        infile >> P >> Q;
        cout<< R << C<< Rs<<Cs<<S<<endl;
        cout << P << " " << Q << endl;
        for(int i=0;i<R;i++){
            for(int j=0;j<C;j++){
                infile >> squares[i][j];
                cout << squares[i][j];
            }
            cout<<endl;
        }
        if(S!=0)
            dfs(Rs, Cs, 0, 0);
        outfile << "Case #" << t << ": " << best << endl;
    }


}


