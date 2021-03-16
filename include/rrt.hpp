#ifndef RRT_
#define RRT_

#include <random>
#include <iostream>
#include <cassert>

class Sampler
{
    Sampler() : generator_(rd_()) {}
    
    double uni01() 
    {
        return uniDist_(generator_);
    }

    double uniRealBound(double lower, double upper)
    {
        assert(lower <= upper);
        return (upper-lower) * uniDist_(generator_) + lower;
    }

    int uniIntBound(int lower, int upper)
    {
        auto r = static_cast<int>( round( uniRealBound( (double)lower, (double)upper ) ) );
        
        if(r > upper)
        {
            std::cout << "Realy Strange... You Should fix Sampler::uniIntBound." << std::endl;
            r = upper;
        }
        
        return r;
    }

    std::random_device rd_;
    std::mt19937_64 generator_;
    std::uniform_real_distribution<double> uniDist_{0, 1};
    std::normal_distribution<double> normalDist_{0, 1};
    
};

#endif