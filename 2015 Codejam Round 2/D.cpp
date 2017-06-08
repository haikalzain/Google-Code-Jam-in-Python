#include<algorithm>
#include<iostream>
#include<cstdio>
#include<utility>
#include<fstream>
#include<set>
#include<vector>

using namespace std;
typedef long long int lint;
int T, R, C;
set<vector<int> > s;
int grid[40][40]={0};
int dr[] = {0, 0, 1, -1};
int dc[] = {-1, 1, 0, 0};

int grid2[40][40] = {0};

bool compare_grids(){
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            if(grid[i][j]!=grid2[i][j])return false;
        }
    }
    return true;
}

bool shift_grid(int x){
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            grid2[i][(j+x)%C] = grid[i][j];
        }
    }
}

void count_shifts(){
    int total = 1;
    vector<int> v;
    for(int i=0;i<C;i++){
        shift_grid(i);
        v.clear();
        for(int j=0;j<R;j++)for(int k=0;k<C;k++)v.push_back(grid2[j][k]);
        if(s.find(v)!=s.end())return;
    }
    s.insert(v);
}

bool check_bad(int r, int c){
    if(r == R or r == -1)return false;
    if(c==C)c=0;if(c==-1)c=C-1;
    if(grid[r][c]==0)return false;
    int zeros=0;
    int samenum=0;
    for(int i=0;i<4;i++){
        int newr = r + dr[i]; int newc = c + dc[i];
        if(newc == C)newc=0;if(newc==-1)newc=C-1;
        if(newr < 0 or newr==R)continue;
        if(grid[newr][newc]==0)zeros++;
        if(grid[newr][newc]==grid[r][c])samenum++;
    }
    if(samenum > grid[r][c] or samenum + zeros < grid[r][c]) return true;
    return false;

}

lint backtrack(int r, int c){
    //cout << r << " " << c << endl;
    lint total = 0;
    for(int i=1;i<=3;i++){
        grid[r][c] = i;


        //check if any errors

        if(check_bad(r,c) or check_bad(r-1, c) or check_bad(r+1, c) or check_bad(r,c-1) or check_bad(r, c+1)){
            continue;
        }

        //check if solved

        if(r == R - 1 and c == C - 1){
            count_shifts();
            total++;
            /*for(int x=0;x<R;x++){
                for(int y=0;y<C;y++){
                    cout << grid[x][y];
                }
                cout << endl;
            }
            cout << endl;*/
        }

        //go on t
        else{
            if(c < C-1){
                total += backtrack(r, c+1);
            }
            else{
                total += backtrack(r+1, 0);
            }

        }
    }
    grid[r][c] = 0;
    return total;
}

ifstream infile;
ofstream outfile;
int main(){
    infile.open("test.txt");
    //infile.open("D-small-practice.in");
    outfile.open("out.txt");
    infile >> T;
    for(int t=1;t<=T;t++){
        s.clear();
        infile >> R >> C;
        backtrack(0, 0);
        outfile << "Case #" << t << ": " << s.size()<<endl;

    }

}
