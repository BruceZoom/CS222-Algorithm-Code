#include <iostream>
#include <string>

#define min(x, y) (x<y?x:y)

using namespace std;

string str;
int **mem;
int a[100000];

bool check(int lo, int hi){
    int i, j;
    for(i=lo, j=hi-1; i<j; i++, j--){
        if(str[i] != str[j]) return 0;
    }
    return 1;
}

// the naive way
int solve(int lo, int hi){
    // cout << lo << " " << hi << endl;
    if(lo + 1 >= hi) return 0;
    if(mem[lo][hi-1] == -1)
    {
        if(check(lo, hi))
        {
            mem[lo][hi-1] = 0;
        }
        else{
            mem[lo][hi-1] = hi - lo - 1;
            for(int i=lo; i<hi-1; i++){
                mem[lo][hi-1] = min(mem[lo][hi-1], solve(lo,i+1) + solve(i+1,hi) + 1);
            }
        }
    }
    return mem[lo][hi-1];
}

int main()
{
    int n, m;
    int i, j, k;

    cin >> str;
    n = str.length();
    
    // AC
    a[0] = 0;
    for(i=1;i<=n;i++)
    {
        if(check(0, i)){
            a[i] = 0;
        }
        else{
            a[i] = i;
            for(j = 1; j < i; j++){
                if(check(j, i))
                    a[i] = min(a[i], a[j] + 1);
            }
        }
    }
    cout << a[n] << endl;

    // the naive way would result into T
    // mem = new int*[n];
    // for(i=0;i<n;i++)
    // {
    //     mem[i] = new int[n];
    //     for(j=0;j<n;j++) mem[i][j] = -1;
    // }
    // for(i=0;i<n-1;i++){
    //     mem[i][i+1] = 0;
    // }
    // cout << solve(0, n) << endl;
    // for(i=0;i<n;i++)
    // {
    //     delete mem[i];
    // }
    // delete mem;

    return 0;
}
