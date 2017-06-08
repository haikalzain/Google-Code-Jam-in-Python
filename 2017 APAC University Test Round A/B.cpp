#include<iostream>
#include<fstream>
#include<algorithm>
#include<utility>

using namespace std;
typedef pair<int, int> ii;
int T;
int R, C;
int dr[] = {0, 0, -1, 1};
int dc[] = {1, -1, 0, 0};
int grid[60][60];
int best[60][60];
bool vis[60][60];
int INF = 1000000000;
ifstream infile;
ofstream outfile;
vector<ii> candidates;

bool dfs(int r, int c, int h){
    //cout << r << " " << c << " " << h << endl;
    vis[r][c] = true;
    candidates.push_back(ii(r, c));
    bool flag = true;
    for(int i=0;i<4;i++){
        int newr = r + dr[i];int newc = c + dc[i];
        if(vis[newr][newc] or best[newr][newc] >= h) continue;
        if(grid[newr][newc] == 0 or not dfs(newr, newc, h)){
            flag = false;
        }
    }
    return flag;
}

int main(){
    infile.open("B-large-practice.in");
    outfile.open("out.txt");
    infile >> T;
    for(int t =1;t<=T;t++){
        fill_n(&grid[0][0], 60 * 60, 0);
        fill_n(&best[0][0], 60 * 60, 0);
        infile >> R >> C;
        for(int i=1;i<=R;i++){
            for(int j=1;j<=C;j++){
                infile >> grid[i][j];
                best[i][j] = grid[i][j];
            }
        }
        for(int h = 1000; h>= 1;h--){
            fill_n(&vis[0][0], 60*60, false);
            for(int r=1;r<=R;r++){
                for(int c=1;c<=C;c++){
                    if(not vis[r][c] and h > best[r][c]){
                        candidates.clear();
                        if(dfs(r, c, h)){
                            for(auto c: candidates){
                                best[c.first][c.second] = h;
                            }
                        }
                    }
                }
            }
        }
        int total = 0;
        for(int i=1;i<=R;i++){
            for(int j=1;j<=C;j++){
                total += best[i][j] - grid[i][j];
                //cout << best[i][j] << " ";
            }
            //cout << endl;

        }
        outfile << "Case #" << t << ": " << total << endl;

    }
    infile.close();
    outfile.close();
    return 0;
}
