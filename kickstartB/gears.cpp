#include<iostream>
#include<fstream>
#include<utility>
#include<set>
#include<algorithm>

using namespace std;
typedef long long int lint;
typedef pair<lint,lint> ii;

int T, Np, Ne, Nt;
ifstream infile;
ofstream outfile;

int gear1[2010];
int gear2[2010];
int extra[2010];
lint P, Q, M;


lint gcd(lint a, lint b){
    if(a==0) return b;
    if(b==0) return a;
    return gcd(b, a%b);
}

ii reduce(ii frac){
    lint d = gcd(frac.first, frac.second);
    return ii(frac.first/d, frac.second/d);
}

ii make_frac(lint first, lint second){
    return reduce(ii(first, second));
}
set<ii> extra_ratios;

int main(){
    infile.open("B-large-practice.in");
    //infile.open("test.txt");
    outfile.open("out.txt");
    infile >> T;
    for(int t=1;t<=T;t++){
        infile >> Np >> Ne >> Nt;
        for(int i=0;i<Np;i++){
            infile >> gear1[i];
        }
        for(int i=0;i<Ne;i++){
            infile >> extra[i];
        }
        for(int i=0;i<Nt;i++){
            infile >> gear2[i];
        }


        extra_ratios.clear();
        for(int i=0;i<Ne;i++){
            for(int j=0;j<Ne;j++){
                if(i!=j){
                    extra_ratios.insert(make_frac(extra[i], extra[j]));
                }
            }
        }

        infile >> M;
        outfile << "Case #" << t << ":" << endl;
        for(int m=0;m<M;m++){
            infile >> P >> Q;
            bool found = false;
            for(int i=0;i<Np;i++){
                for(int j=0;j<Nt;j++){
                    ii test = make_frac(gear1[i] * Q, gear2[j] * P);
                    if(extra_ratios.count(test)){
                        found = true;
                        break;
                    }

                }
                if(found) break;
            }
            outfile << (found ? "YES": "NO") << endl;
        }

    }
    infile.close();
    outfile.close();

}
