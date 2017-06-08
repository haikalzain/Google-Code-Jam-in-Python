#include<iostream>
#include<fstream>
#include<deque>
#include<set>
#include<algorithm>

using namespace std;

struct SlidingWindow{

    int n;
    deque<int> d;
    multiset<int> s;

    SlidingWindow(int n){
        this->n = n;
    }

    void push(int value){
        if(d.size() == n){
            int rem = d.back();
            d.pop_back();
            multiset<int>::iterator it = s.find(rem);
            if(it != s.end()){
                s.erase(it);
            }
        }
        s.insert(value);
        d.push_front(value);
    }

    int minVal(){
        return *s.begin();
    }


};

int cost[1010][10010];
int A, B, P;
int N, M, L;
int T;
int INF = 1000000007;

int main(){
    ifstream infile;
    ofstream outfile;

    infile.open("D-large-practice.in");
    outfile.open("out.txt");

    infile >> T;
    for(int t=1;t<=T;t++){
        infile >> N >> M >> L;

        fill_n(&cost[0][0], L+5, INF);
        cost[0][0] = 0;

        for(int i=1;i<=N;i++){
            copy(&cost[i-1][0], &cost[i-1][L+5], &cost[i][0]);
            infile >> A >> B >> P;
            int k = B - A + 1;
            SlidingWindow sliding(k);

            for(int j=0; j<=L - A;j++){

                sliding.push(cost[i-1][j]);
                cost[i][j+A] = min(cost[i][j+A], sliding.minVal() + P);
            }
        }
        outfile << "Case #" << t << ": ";

        cout << t << endl;

        /*for(int i=0;i<=L;i++){
            cout<<cost[N][i]<<" ";
        }
        cout << endl;*/

        if(cost[N][L] <= M)
            outfile << cost[N][L] << endl;
        else
            outfile << "IMPOSSIBLE" << endl;
    }
    return 0;
}
