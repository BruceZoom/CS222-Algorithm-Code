#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> dig;
vector<char> sgn;

int cal(int i, int j, char c)
{
    switch(c)
    {
        case '+':
            return i + j;
        case '-':
            return i - j;
        default:
            return i * j;
    }
}

vector<int> find_res(int lo, int hi)
{
    vector<int> res;
    vector<int> tmp1, tmp2;
    int i, j, k;
    if(lo >= hi)
    {
        res.push_back(dig[lo]);
        return res;
    }
    for(i=lo;i<hi;i++)
    {
        tmp1.clear();
        tmp2.clear();
        tmp1 = find_res(lo, i);
        tmp2 = find_res(i+1, hi);
        for(j=0;j<tmp1.size();j++)
        {
            for(k=0;k<tmp2.size();k++)
            {
                res.push_back(cal(tmp1[j], tmp2[k], sgn[i]));
            }
        }
    }
    return res;
}

template<class T>
void printv(vector<T> v)
{
    for(int i=0;i<v.size();i++) cout << v[i] << " ";
    cout << endl;
}

int main()
{
    int n, m;
    int i, j, k;
    string str;
    char c;
    vector<int> res;

    cin >> str;
    j = 0;
    for(i=0; i<str.length(); i++)
    {
        if(str[i] == '+' || str[i] == '-' || str[i] == '*')
        {
            sgn.push_back(str[i]);
            dig.push_back(j);
            j = 0;
        }
        else
        {
            j = 10 * j + str[i] - '0';
        }
    }
    dig.push_back(j);
    res = find_res(0, sgn.size());
    sort(res.begin(), res.end());
    for(i=0;i<res.size();i++) cout << res[i] << " ";
    cout << endl;

    return 0;
}
