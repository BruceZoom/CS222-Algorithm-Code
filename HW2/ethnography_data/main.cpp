#include <iostream>
#include <fstream>
#include <vector>

#define birth(x) (2*x)
#define death(x) (2*x+1)

using namespace std;

struct node{
    int dg;
    vector<int> succs;
    void clear()
    {
        dg = 0;
        succs.clear();
    }
};
node V[20000];

void add(int i, int j)
{
    V[i].succs.push_back(j);
    V[j].dg++;
}

void init(int n)
{
    for(int i=0; i<n; i++)
    {
        V[birth(i)].clear();
        V[death(i)].clear();
        add(birth(i), death(i));
    }
}

struct Node
{
    int idx;
    Node *succ;
    Node *pred;
};

class Queue
{
public:
    Node *head;
    Node *tail;
    Queue()
    {
        head = new Node();
        tail = new Node();
        head->succ = tail;
        head->pred = NULL;
        tail->pred = head;
        tail->succ = NULL;
    }
    ~Queue()
    {
        while (!IsEmpty())
        {
            int i = DeQueue();
        }
        delete head;
        delete tail;
    }
    bool IsEmpty()
    {
        return (head->succ == tail);
    }
    void EnQueue(int i)
    {
        Node *node = new Node();
        node->idx = i;
        tail->pred->succ = node;
        node->pred = tail->pred;
        tail->pred = node;
        node->succ = tail;
    }
    int DeQueue()
    {
        int i = head->succ->idx;
        Node* tmp = head->succ;
        tmp->succ->pred = head;
        head->succ = tmp->succ;
        delete tmp;
        return i;
    }
};

int main()
{
    int _n;
    int n, m;
    int i, j, k, l;
    Queue Q;
    ifstream infile;
    ofstream outfile;
    infile.open("test.in");
    outfile.open("test.out");

    infile >> _n;
    while(0 < _n--)
    {
        infile >> n >> m;
        init(n);
        for(i=0; i<m; i++)
        {
            infile >> j >> k >> l;
            k--;l--;
            if(j)
            {
                // overlap
                add(birth(k), death(l));
                add(birth(l), death(k));
            }            
            else
            {
                // k death before l birth
                add(death(k), birth(l));
            }
        }

        // find begin points
        i = 0;
        while(i < 2*n)
        {
            if(V[i].dg == 0)
            {
                Q.EnQueue(i);
            }
            i++;
        }
        // check inconsistency
        // WRONG! SHOULD CHECK CYCLE!
        // if(Q.IsEmpty()){
        //     outfile << "fail\n";
        //     continue;
        // }
        

        // topological sort
        k = 0;
        while(!Q.IsEmpty())
        {
            i = Q.DeQueue();
            V[i].dg = k++;
            for(j = 0; j<V[i].succs.size(); j++)
            {
                l = V[i].succs[j];
                V[l].dg--;
                if(V[l].dg == 0)
                {
                    Q.EnQueue(l);
                }
            }
        }

        // check inconsistency
        if(k < 2*n){
            outfile << "fail\n";
            continue;
        }

        for(i=0;i<n;i++)
        {
            outfile << V[birth(i)].dg << " ";
        }
        outfile << endl;
        for(i=0;i<n;i++)
        {
            outfile << V[death(i)].dg << " ";
        }
        outfile << endl;
    }

    infile.close();
    outfile.close();

    return 0;
}
