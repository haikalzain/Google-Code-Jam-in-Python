#include<iostream>
#include<fstream>
#include<algorithm>
#include<set>
#include<vector>
#include<unordered_map>
using namespace std;

int T, N;
int Amax, Dmax;

bool exists[4010][4010];
int mem[4010][4010];

int INF = 1000000000;

vector<int> A, D;
ifstream infile;
ofstream outfile;

void discretize(vector<int>& x){
    set<int> s(x.begin(), x.end());
    unordered_map<int, int> m;
    int i =0;
    for(auto item: s){
        m[item] = i;
        i++;
    }
    for(auto& item: x){
        item = m[item];
    }
}

int dp(int a, int d){
    if(a > Amax || d > Dmax) return 0;
    if(mem[a][d] != INF) return mem[a][d];

    int mychoices = max(dp(a, d+1), dp(a+1, d));
    if(exists[a][d]){
         mychoices = max(mychoices, 1 - mychoices);
    }
    mem[a][d] = mychoices;
    return mem[a][d];

}

int main(){
    infile.open("test.txt");
    outfile.open("out.txt");

    infile >> T;
    for(int t=1;t<=T;t++){
        infile >> N;
        A.clear();
        D.clear();
        Amax = 0;
        Dmax = 0;
        fill_n(&exists[0][0], 4010 * 4010, 0);
        fill_n(&mem[0][0], 4010 * 4010, INF);
        for(int i=0;i<N;i++){
            int a,d;
            infile >> a >> d;
            A.push_back(a);
            D.push_back(d);
        }
        discretize(A);
        discretize(D);
        Amax = *max_element(A.begin(), A.end());
        Dmax = *max_element(D.begin(), D.end());

        for(int i=0;i<N;i++){
            exists[A[i]][D[i]] = true;
        }

        int result = dp(0, 0);
        string printed = "NO";
        if(result>0){
            printed = "YES";
        }
        cout << "Case #" << t << ": " << printed << endl;
    }

}
