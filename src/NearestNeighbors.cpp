#include <NearestNeighbors.hpp>

pt NearestNeighbors::nearest(const pt& x)
{
    int sz = nn.size();
    pt near;
    double minDist(numeric_limits<double>::max());

    for(int i=0; i<sz; i++)
    {
        double d = dist(x, nn[i]);
        if(minDist > d)
        {
            minDist = d;
            near = nn[i];
        }
    }
    
    return near;
}