#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int _n;
    double s, c, d;
    int N;
    int i, j, k;
    double rest, cost;

    double dist[10000], prix[10000];
    int dst[10000];
    int head;

    ifstream infile;
    infile.open("test.in");
    ofstream outfile;
    outfile.open("test.out");

    infile >> _n;

    while (0 < _n--)
    {
        infile >> s >> c >> d >> N;
        head = 0;
        // cout << c * d << endl;
        for (i = 0; i < N+1; i++)
        {
            if(i<N)
            {
            infile >> dist[i] >> prix[i];
            }
            else
            {
                dist[i] = s;
                prix[i] = 0;
            }
            
            dst[i] = 0;
            for(j = head; j < i; j++)
            {
                // remove fully considered stations
                if(dist[j] + c * d < dist[i] || (dst[j] != 0 && j == head))
                {
                    if(dst[j] == 0)
                    {
                        dst[j] = j;
                    }
                    head++;
                }
                // set the closest cheaper
                else if(dst[j] == 0 && prix[i] < prix[j])
                {
                    dst[j] = i;
                }
            }
        }

        rest = 0;
        cost = 0;
        for(i = 0; i < N; i++){
            // cout << dst[i] << " ";
            if(dst[i] == i){
                cost += (c - rest / d) * prix[i];
                rest = c * d;
            }
            else if(dst[i] != 0 && dist[dst[i]] > dist[i] + rest){
                cost += (dist[dst[i]] - dist[i] - rest) / d * prix[i];
                rest = dist[dst[i]] - dist[i];
            }
            rest -= dist[i+1] - dist[i];
            if(rest < 0){
                break;
            }
        }
        // cout << endl;
        if(rest < 0){
            outfile << "fail\n";
        }
        else{
            outfile << cost << endl;
        }
    }

    infile.close();
    outfile.close();
    return 0;
}