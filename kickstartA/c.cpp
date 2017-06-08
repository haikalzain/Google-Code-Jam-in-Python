#include<iostream>
#include<algorithm>
#include<fstream>
#include<cstdlib>

using namespace std;

ifstream infile;
ofstream outfile;

int x[2010], y[2010], z[2010], r[2010];
int x2[4010], y2[4010], z2[4010], r2[4010];
int minX, minY,minZ, maxX, maxY,maxZ;
int T, N, L[4];

int calc_length(int star, int x1, int y1, int z1){
    int xlen = abs(x[star] - x1) + r[star];
    int ylen = abs(y[star] - y1) + r[star];
    int zlen = abs(z[star]- z1) + r[star];
    return max({xlen, ylen, zlen});
}

int find_length(int x1, int y1, int z1, int x2, int y2, int z2){
    int best_length = 1000000000;
    for(int i=0;i<2*N;i++){
        //trying each star, choose the length
        int length;
        if(i < N)
            length = calc_length(i%N, x1, y1, z1);
        else
            length = calc_length(i%N, x2, y2, z2);
        if(length >= best_length)
            continue;
        bool bad = false;
        for(int j=0;j<N;j++){
            //Now see if each star fits in the length
            int l1 = calc_length(j, x1, y1, z1);
            int l2 = calc_length(j, x2, y2, z2);
            if(l1 > length && l2 > length){
                bad = true;
                break;
            }
        }
        if(!bad){
            best_length = length;
        }
    }
    return best_length;
}

int main(){
    infile.open("C-large-practice.in");
    outfile.open("out.txt");
    infile >> T;
    for(int t=1;t<=T;t++){
        infile >> N;
        for(int i=0;i<N;i++){
            infile >> x[i] >> y[i] >> z[i] >> r[i];
            x2[i] = x[i] - r[i];
            x2[i+N] = x[i] + r[i];
            y2[i] = y[i] - r[i];
            y2[i+N] = y[i] + r[i];
            z2[i] = z[i] - r[i];
            z2[i+N] = z[i] + r[i];
        }
        //should be including radius
        minX = *min_element(x2, x2+2*N);
        minY = *min_element(y2, y2+2*N);
        minZ = *min_element(z2, z2+2*N);
        maxX = *max_element(x2, x2+2*N);
        maxY = *max_element(y2, y2+2*N);
        maxZ = *max_element(z2, z2+2*N);

        //cout<<maxX<<maxY<<maxZ;

        L[0] = find_length(minX, minY, minZ, maxX, maxY, maxZ);
        L[1] = find_length(minX, minY, maxZ, maxX, maxY, minZ);
        L[2] = find_length(minX, maxY, minZ, maxX, minY, maxZ);
        L[3] = find_length(minX, maxY, maxZ, maxX, minY, minZ);
        int result = *min_element(L, L+4);
        outfile << "Case #" << t << ": " << result << endl;
    }


    infile.close();
    outfile.close();
}
