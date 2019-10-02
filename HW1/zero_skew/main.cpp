#include <iostream>
#include <fstream>
#include <cmath>

#define lc(x) (2 * x + 1)
#define rc(x) (2 * x + 2)
#define pr(x) ((x - 1) / 2)
#define max(x, y) (x > y ? x : y)
#define min(x, y) (x < y ? x : y)

using namespace std;

int n;
int w[1048576];

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
    int i, j, k;
    int tmp;
    int ans;
    Queue Q;
    bool flag;

    ifstream infile;
    ofstream outfile;
    infile.open("test.in");
    outfile.open("test.out");

    infile >> _n;

    while (0 < _n--)
    {
        ans = 0;

        infile >> n;
        tmp = pow(2, log2((double)n) + 1) - 2;
        for (i = 0; i < tmp; i++)
        {
            infile >> w[i + 1];
            ans += w[i + 1];
        }
        for (i = 0; i < n / 2; i++)
        {
            Q.EnQueue(tmp - n - i);
        }

        flag = true;
        while (!Q.IsEmpty())
        {
            i = Q.DeQueue();
            ans += max(w[lc(i)], w[rc(i)]) - min(w[lc(i)], w[rc(i)]);
            if (i == 0)
                break;
            w[i] += max(w[lc(i)], w[rc(i)]);
            if (flag)
            {
                Q.EnQueue(pr(i));
            }
            flag = !flag;
        }
        outfile << ans << endl;
    }

    return 0;
}
