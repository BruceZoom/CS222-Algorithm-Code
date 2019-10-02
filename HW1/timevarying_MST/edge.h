#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct Edge
{
    int v1;
    int v2;
    double a;
    double b;
    double c;
    double Delta()
    {
        return b * b - 4 * a * c;
    }
    double getValue(double t)
    {
        return a * t * t + b * t + c;
    }
    double getDerive(double t)
    {
        return 2 * a * t + b;
    }
    void clear(){
        a = 0;
        b = 0;
        c = 0;
    }
    double argMin(){
        return -b / 2 / a;
    }
    void print(){
        cout << a << " " << b << " " << c << endl;
    }
};

struct Intersection
{
    double t;
    int right_upper; // when generating intersection, return 1 when the first edge is above the second at right of t, return 0 otherwise
    int right_lower;
    // void operator=(const Intersection& its){
    //     t = its.t;
    //     right_upper = its.right_upper;
    //     right_lower = its.right_lower;
    // }
};

Edge operator+(const Edge &e1, const Edge &e2)
{
    Edge e;
    e.a = e1.a + e2.a;
    e.b = e1.b + e2.b;
    e.c = e1.c + e2.c;
    return e;
}

Edge operator-(const Edge &e1, const Edge &e2)
{
    Edge e;
    e.a = e1.a - e2.a;
    e.b = e1.b - e2.b;
    e.c = e1.c - e2.c;
    return e;
}

vector<Intersection> intersect(const Edge &e1, const Edge &e2)
{
    vector<Intersection> ps;
    Edge e = e1 - e2;
    Intersection its;
    double delta = e.Delta();
    if (delta > 0)
    {
        if (e.a != 0)
        {
            delta = sqrt(delta);
            its.t = (-e.b - delta) / 2 / e.a;
            its.right_upper = e.getDerive(its.t) > 0;
            ps.push_back(its);
            its.t = (-e.b + delta) / 2 / e.a;
            its.right_upper = !its.right_upper;
            ps.push_back(its);
        }
        else{
            its.t = -e.c / e.b;
            its.right_upper = e.getDerive(its.t) > 0;
            ps.push_back(its);
        }
    }
    return ps;
}

#endif