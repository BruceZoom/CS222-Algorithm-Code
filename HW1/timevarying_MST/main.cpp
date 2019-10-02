#include <iostream>
#include <fstream>
#include <algorithm>
#include "edge.h"

using namespace std;

Edge E[1000];
int eIdx[1000];
int eIdxInv[1000];
Intersection its[1000000];
int itsIdx[1000000];
int itsCnt;

bool itsCmp(int i, int j)
{
    return its[i].t < its[j].t;
}

bool cmp_minus_inf(int i, int j)
{
    if (E[i].a == E[j].a)
    {
        return E[i].c < E[j].c;
    }
    return E[i].a < E[j].a;
}

// disjoint set
int parent[1000000];
void Init(int n)
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
    }
}
int Find(int i)
{
    // cout << "Find" << endl;
    if (parent[i] != i)
    {
        parent[i] = Find(parent[i]);
    }
    return parent[i];
}
void Union(int i, int j)
{
    parent[Find(i)] = Find(j);
}

int main()
{
    int _n;
    int n, m;
    int i, j, k;
    vector<Intersection> tmpIts;
    Intersection tmpIt;
    int tmp;
    Edge MST;
    double t, mint, minf;

    ifstream infile;
    ofstream outfile;
    infile.open("test.in");
    outfile.open("test.out");

    infile >> _n;

    while (0 < _n--)
    {
        itsCnt = 0;

        infile >> n >> m;
        for (i = 0; i < m; i++)
        {
            infile >> E[i].v1 >> E[i].v2 >> E[i].a >> E[i].b >> E[i].c;
            E[i].v1--;
            E[i].v2--;
            eIdx[i] = i;
        }
        // find all intersections and sort them
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < i; j++)
            {
                tmpIts = intersect(E[i], E[j]);
                for (k = 0; k < tmpIts.size(); k++)
                {
                    if (tmpIts[k].right_upper)
                    {
                        tmpIts[k].right_upper = i;
                        tmpIts[k].right_lower = j;
                    }
                    else
                    {
                        tmpIts[k].right_upper = j;
                        tmpIts[k].right_lower = i;
                    }
                    itsIdx[itsCnt] = itsCnt;
                    its[itsCnt++] = tmpIts[k];
                }
            }
        }
        sort(itsIdx, itsIdx + itsCnt, itsCmp);
        // for(i=0;i<itsCnt;i++)cout << its[itsIdx[i]].t << " "; cout << endl;
        // cout << "Intersections found" << endl;

        // initialize the order of edges on the boundary
        sort(eIdx, eIdx + m, cmp_minus_inf);
        for (i = 0; i < m; i++)
        {
            eIdxInv[eIdx[i]] = i;
            // cout << E[eIdx[i]]
        }

        // find t minimizing the MST
        k = 0;
        while (true)
        {
            // find MST
            Init(n);
            MST.clear();
            tmp = 0;
            i = 0;
            while (tmp < n - 1)
            {
                if (Find(E[eIdx[i]].v1) != Find(E[eIdx[i]].v2))
                {
                    MST = MST + E[eIdx[i]];
                    tmp++;
                    Union(E[eIdx[i]].v1, E[eIdx[i]].v2);
                }
                i++;
            }
            // find and clip t_opt
            t = MST.argMin();
            // cout << t << endl;
            if (k > 0 && t < its[itsIdx[k - 1]].t)
            {

                t = its[itsIdx[k - 1]].t;
            }
            if (k < itsCnt && t > its[itsIdx[k]].t)
            {
                t = its[itsIdx[k]].t;
            }
            // cout << "One TMST solved: " << t << endl;
            // compare t_opt
            if (k == 0 || MST.getValue(t) < minf)
            {
                minf = MST.getValue(t);
                mint = t;
            }
            // check
            if (k >= itsCnt)
            {
                break;
            }
            // update order
            do
            {
                tmpIt = its[itsIdx[k]];
                // clear inversions
                if (eIdxInv[tmpIt.right_upper] < eIdxInv[tmpIt.right_lower])
                {
                    t = eIdx[eIdxInv[tmpIt.right_upper]];
                    eIdx[eIdxInv[tmpIt.right_upper]] = eIdx[eIdxInv[tmpIt.right_lower]];
                    eIdx[eIdxInv[tmpIt.right_lower]] = t;
                    t = eIdxInv[tmpIt.right_upper];
                    eIdxInv[tmpIt.right_upper] = eIdxInv[tmpIt.right_lower];
                    eIdxInv[tmpIt.right_lower] = t;
                }
                k++;
            } while (k < itsCnt && its[itsIdx[k - 1]].t == its[itsIdx[k]].t);
            // for(j=0;j<m;j++)E[eIdx[j]].print();
            // cout << "Intersections updated" << endl;
        }
        outfile << mint << " " << minf << endl;
    }

    infile.close();
    outfile.close();
    return 0;
}
