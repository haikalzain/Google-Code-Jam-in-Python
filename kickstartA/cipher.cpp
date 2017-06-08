#include<iostream>
#include<fstream>
#include<algorithm>
#include<string>
#include<cassert>

using namespace std;
typedef long long int lint;

int T, V, S;
int MOD = 1000000007;
ifstream infile;
ofstream outfile;

string vocab[410];
string input;

lint mem[4010];

lint dp(int index){
    if(index == input.length()){
        return 1;
    }
    assert(index < input.length());

    if(mem[index] != -1){
        return mem[index];
    }

    lint total = 0;
    for(int i=0;i<V;i++){
        string word = vocab[i];
        //cout << word << " " << i << endl;
        if(index + word.length() <= input.length()){
            string sub = input.substr(index, word.length());
            sort(sub.begin(), sub.end());
            //cout << sub<< " " << word << endl;
            if(word.compare(sub) == 0){
                total += dp(index + word.length());
                total %= MOD;
            }
        }
    }
    mem[index] = total;
    return mem[index];

}


int main(){
    infile.open("C-large-practice.in");
    outfile.open("out.txt");
    infile >> T;
    for(int t=1;t<=T;t++){
        infile >> V >> S;
        for(int v=0;v<V;v++){
            infile >> vocab[v];
            sort(vocab[v].begin(), vocab[v].end());
            //cout << vocab[v] << " " << vocab[v].length()<<endl;
        }
        outfile << "Case #" << t << ": ";
        for(int i=0;i<S;i++){
            fill_n(mem, 4010, -1);
            infile >> input;
            //cout<< input << endl;
            outfile<<dp(0)<<" ";
        }
        outfile << endl;
    }

}
