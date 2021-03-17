#ifndef NEARESTNEIGHBORS_HPP
#define NEARESTNEIGHBORS_HPP

#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;
typedef pair<double, double> pt;

class NearestNeighbors
{
public:
    NearestNeighbors();

    void clear()
    {
        nn.clear();
    }

    void add(const pt& x)
    {
        nn.push_back(x);
    }

    inline double dist(const pt& a, const pt& b){
        return sqrt( pow(a.first-b.first, 2) + pow(a.second-b.second, 2) );
    }

    // Return Nearest Point from x
    pt nearest(const pt& x);

private:
    vector<pt> nn;

};









#endif