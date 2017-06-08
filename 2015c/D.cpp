#include<iostream>
#include<fstream>
#include<algorithm>

using namespace std;
int T;
int N, K, C, X;
int A[3010], B[3010];
int mat[3010][3010];
int new_mat[3010][3010];
int sparse[3010][30];


ifstream infile;
ofstream outfile;

void build_sparse(int (&values)[3010]){
    for(int i=0;i<N;i++){
        sparse[i][0] = values[i];
    }
    //cout << "a1" << endl;
    int pow = 1;
    for(int j=1;j<14;j++){
        pow *= 2; // 2 power j
        //cout << "building j " << j << " " << pow << endl;
        for(int i=0;i<N;i++){
            //cout << i << endl;
            if(i+pow/2 < N){
                //cout << "i + pow/2: " << i + pow/2 << endl;
                sparse[i][j] = max(sparse[i][j-1], sparse[i + pow/2][j-1]);
            }
            else
                sparse[i][j] = sparse[i][j-1];
        }
    }
}
int query_sparse(int x, int L){
    int ans=0;
    int two_j;
    int j;
    for(j=0;j<15;j++){
        if(j==0){
            two_j = 1;
        }
        else{
            two_j *= 2;
        }
        if(two_j>L){
            two_j /=2;
            j--;
            break;
        }
    }
    //cout << "entering loop" << x << " " << L << " " << two_j << " " << endl;
    while(L > 0){
        if(two_j <= L){
            ans = max(sparse[x][j], ans);
            x += two_j;
            L -= two_j;
        }
        j--;
        two_j /= 2;

    }
    //cout << "exiting Loop" << endl;
    return ans;
}

int main(){
    infile.open("D-large-practice.in");
    outfile.open("out.txt");
    infile >> T;
    for(int t=1;t<=T;t++){
        infile >> N >> K >> C >> X;
        //cout << N << K << C << X << endl;
        for(int i=0;i<N;i++)infile >> A[i];
        for(int i=0;i<N;i++)infile >> B[i];
        for(int i=0;i<N;i++)for(int j=0;j<N;j++) mat[i][j] = (C + (i+1)*A[i] + (j+1)*B[j]) % X;

        for(int i=0;i<N;i++){
            //cout << "building sparse " << i << endl;
            build_sparse(mat[i]);
            //cout << "finished" << endl;
            for(int j=0;j<N-K+1;j++){
                new_mat[j][i] = query_sparse(j, K);
            }
        }
        //cout << "built sparse" << endl;
        long long int sum = 0;
        for(int i=0;i<N-K+1;i++){
            build_sparse(new_mat[i]);
            for(int j=0;j<N-K+1;j++)
                sum += query_sparse(j, K);
        }
        outfile << "Case #" << t << ": " << sum << endl;

    }
    infile.close();
    outfile.close();
    return 0;
}
