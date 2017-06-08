#include<iostream>
#include<fstream>
#include<algorithm>
#include<map>
#include<vector>
#include<utility>
#include<cassert>

using namespace std;
typedef long long int lint;
int T, M, N;
ifstream infile;
ofstream outfile;
vector<lint> A[20];
vector<lint> C[20];
map<lint, lint> dict1;
map<lint,lint> dict2;

void create_map(map<lint,lint> &dict, vector<lint> &g, int N, int M){
    dict.clear();
    for(int i=0;i<A[g[0]].size();i++){
        for(int j=0;j<A[g[1]].size();j++){
            for(int k=0;k<A[g[2]].size();k++){
                for(int l=0;l<A[g[3]].size();l++){
                    lint attack = A[g[0]][i] + A[g[1]][j] + A[g[2]][k] + A[g[3]][l];
                    lint cost = C[g[0]][i] + C[g[1]][j] + C[g[2]][k] + C[g[3]][l];
                    if(cost<=M)dict[cost] = max(dict[cost], attack);
                }
             }
        }
    }


    map<lint,lint>::iterator prev;
    for(auto it=dict.begin();it!=dict.end();it++){
        if(it!= dict.begin()){
            dict[it->first] = max(it->second, prev->second);
        }
        prev = it;
    }
}

int solve(int N, int M){
    int best = 0;
    for(int i = 1;i < 1<<N; i++){
        if(__builtin_popcount(i) == 8){
            vector<lint> g1, g2;
            for(int j=0;j<N;j++){
                if((1 << j) & i){
                    if(g1.size()< 4){
                        g1.push_back(j);
                    }
                    else{
                        g2.push_back(j);
                    }
                }
            }
            //cout << "hey1" << endl;
            create_map(dict1, g1, N, M);

            create_map(dict2, g2, N, M);
            //cout << "hey";

            for(auto it=dict1.begin();it!=dict1.end();it++){
                int attack = it->second;
                int cost = it->first;
                auto it2 = dict2.upper_bound(M - cost);
                it2--;

                attack += it2->second;
                best = max(attack, best);

            }

        }
    }
    return best;

}


int main(){
    infile.open("D-large-practice.in");
    outfile.open("out.txt");
    infile >> T;
    for(int t=1;t<=T;t++){
        cout << t << endl;
        for(int i=0;i<20;i++){
            A[i].clear();C[i].clear();
        }
        infile >> M >> N;
        for(int i=0;i<N;i++){
            int K, L;
            infile >> K >> L;
            for(int l=1;l<=K;l++){
                int tmp;
                infile >> tmp;
                if(l>=L)A[i].push_back(tmp);
            }
            C[i].push_back(0);
            for(int l=1;l<=K-1;l++){
                int tmp;
                infile >> tmp;
                if(l>=L)C[i].push_back(C[i].back() + tmp);
            }
        }
        outfile << "Case #" << t << ": " << solve(N, M) << endl;

    }

}
