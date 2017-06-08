#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;

struct Point{
    int cost, city;
    Point(int x, int y):cost(x),city(y){}

    bool operator<(const Point& point2) const{
        return this->cost > point2.cost;
    }
};

int main(){
    priority_queue<Point> pq;
    for(int i=0;i<5;i++){
        pq.push(Point(i,1));
    }
    while(!pq.empty()){
        Point x = pq.top();pq.pop();
        cout << x.cost << endl;
    }
    //cout << (point1 < point2) << endl;

}
