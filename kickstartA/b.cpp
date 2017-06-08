#include<iostream>
#include<fstream>
#include<string>
#include<unordered_map>
#include<algorithm>
#include<regex>

using namespace std;

typedef long long int lint;
ifstream infile;
ofstream outfile;
bool dp[8010][8010] = {0};
string test ="test.txt";
string small="B-small-practice.in";

int main(){
    int T;
    string pattern1, pattern2;
    infile.open("B-large-practice.in");
    infile >> T;
    outfile.open("out.txt");
    for(int t=1;t<=T;t++){
        fill_n(&dp[0][0], 8010 * 8010, 0);
        infile >> pattern1;
        infile >> pattern2;
        regex e("\\*");
        //cout<<pattern1.length();
        pattern1 = regex_replace(pattern1, e, "####");
        pattern2 = regex_replace(pattern2, e, "####");
        //cout<<pattern1[pattern1.length()]<<endl;
        //cout<<pattern2[pattern2.length()]<<endl;
        for(int i=0; i<=pattern1.length();i++ ){
            for(int j=0; j<=pattern2.length();j++){
                if(i==0 && j==0){
                    dp[i][j] = true;
                }
                if(!dp[i][j])
                    continue;

                if(pattern1[i]!='#' && pattern2[j]!='#'){
                    dp[i+1][j+1] = (pattern1[i] == pattern2[j]);
                }
                if(pattern1[i] == '#'){
                    dp[i+1][j] = true;
                    dp[i+1][j+1] = true;
                }
                if(pattern2[j] == '#'){
                    dp[i][j+1] = true;
                    dp[i+1][j+1] = true;
                }
            }
        }

        bool result = dp[pattern1.length()][pattern2.length()];
        outfile << "Case #" << t << ": " << (result ? "TRUE" : "FALSE") << endl;
    }
    infile.close();
    outfile.close();

    return 0;
}
