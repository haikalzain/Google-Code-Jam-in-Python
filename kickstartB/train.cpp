#include<iostream>
#include<fstream>
#include<algorithm>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef pair<int,int> ii;

struct Trip{
    int city, cost;
    Trip(int x, int y):city(x),cost(y){}
};

int T;
int N, M, K;
vector<Trip> graph[600][30];
priority_queue<ii> pq;
ifstream infile;
ofstream outfile;
int INF = 1000000000;
int best[30][600];

int main(){
    infile.open("A-large-practice.in");
    outfile.open("out.txt");
    infile >> T;
    for(int t=1;t<=T;t++){
        infile >> N >> M >> K;
        for(int i=0;i<600;i++){
            for(int j=0;j<30;j++){
                graph[i][j].clear();
                best[j][i] = INF;
            }
        }

        for(int i=0;i<M;i++){
            int x, y;
            infile >> x >> y;
            for(int j=0;j<24;j++){
                int val;
                infile >> val;
                graph[x][j].push_back(Trip(y, val));
                graph[y][j].push_back(Trip(x, val));
            }
        }
        for(int start=0;start<24;start++){
            //cout << "Start " << start << endl;
            best[start][1] = 0;
            pq.push(ii(0, 1));
            while(!pq.empty()){
                ii top = pq.top();
                pq.pop();
                int timetaken = -top.first; int city = top.second;
                //cout << timetaken << " " << city << endl;
                for(auto trip: graph[city][(timetaken + start)%24]){
                    //cout << "Trip: " << (timetaken + start) % 24 << " "<< trip.city << " " << trip.cost << endl;
                    //cout << best[start][trip.city] << endl;
                    //cout << timetaken + trip.cost;
                    if(best[start][trip.city] > timetaken + trip.cost){
                        best[start][trip.city] = timetaken + trip.cost;
                        pq.push(ii(-timetaken - trip.cost, trip.city));
                    }
                }
            }

        }
        outfile << "Case #" << t << ": ";
        for(int i=0;i<K;i++){
            int D, S;
            infile >> D >> S;
            int result = best[S][D];
            if(result == INF) result = -1;
            outfile << result << " ";
        }
        outfile << endl;
    }
    infile.close();
    outfile.close();
}
