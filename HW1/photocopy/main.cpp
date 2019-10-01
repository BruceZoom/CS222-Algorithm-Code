#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int weight[10000];
int time[10000];

bool cmp(int a, int b)
{
    return weight[a] * time[b] > weight[b] * time[a];
}

int main()
{
    int _n;
    int n;
    int idx[10000];
    int i, j, k;
    int s, t;

    ifstream infile;
    ofstream outfile;
    infile.open("test.in");
    outfile.open("test.out");

    infile >> _n;

    while(0 < _n--){
        infile >> n;
        for(i = 0; i < n; i++){
            infile >> time[i] >> weight[i];
            idx[i] = i;
        }
        sort(idx, idx+n, cmp);
        t = 0;
        s = 0;
        for(i = 0; i < n; i++){
            t += time[idx[i]];
            s += t * weight[idx[i]];
        }
        outfile << s << endl;
    }

    return 0;
}