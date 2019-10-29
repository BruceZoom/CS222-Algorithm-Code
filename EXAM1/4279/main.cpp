#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, m;
    int i, j, k;
    int prix, tmp, tot = 0;
    int last = 0;
    tmp = 0;
    cin >> n;
    cin >> prix;
    tmp = last = prix;
    for(i = 1; i < n; i++)
    {
        cin >> prix;
        if(last > prix)
        {
            tot += last - tmp;
            tmp = prix;
        }
        last = prix;
    }
    tot += last - tmp;
    cout << tot << endl;
    return 0;
}
