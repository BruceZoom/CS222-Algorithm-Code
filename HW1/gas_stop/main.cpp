#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int _n;
    double s, c, d;
    int N;
    int i, j, k;
    int cnt;
    double dist, curr, tmpd;

    ifstream infile;
    infile.open("test.in");
    ofstream outfile;
    outfile.open("test.out");

    infile >> _n;

    while (0 < _n--)
    {
        infile >> s >> c >> d >> N;
        curr = 0;
        tmpd = 0;
        cnt = 1;
        // cout << c * d << endl;
        for (i = 0; i < N; i++)
        {
            if (i < N - 1)
            {
                infile >> dist;
            }
            else
            {
                dist = s;
            }
            if (dist > curr + c * d)
            {
                if (tmpd > curr + c * d)
                {
                    cnt = -1;
                    break;
                }
                curr = tmpd;
                cnt++;
            }
            tmpd = dist;
        }
        if (tmpd > curr + c * d)
        {
            cnt = -1;
        }
        if (cnt < 0)
        {
            outfile << "fail" << endl;
        }
        else
        {
            outfile << cnt << endl;
        }
    }

    infile.close();
    outfile.close();
    return 0;
}