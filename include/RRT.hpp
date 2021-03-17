#ifndef RRT_HPP
#define RRT_HPP

#include <random>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include <opencv2/opencv.hpp>

#include <NearestNeighbors.hpp>

using namespace std;
using namespace cv;
typedef vector<uint8_t> vi8;
typedef pair<double, double> pt;

class Sampler
{
public:
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

    double uniSO2()
    {
        return uniRealBound(-M_PI, M_PI);
    }

    pt uniSE2(const pt& x)
    {
        double d = uniRealBound(minStep, maxStep);
        double theta = uniSO2();
        pt ret = {x.first + cos(theta), x.second + sin(theta)};
        return ret;
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
private:
    std::random_device rd_;
    std::mt19937_64 generator_;
    std::uniform_real_distribution<double> uniDist_{0, 1};
    std::normal_distribution<double> normalDist_{0, 1};

    double minStep;
    double maxStep;
    
};


class RRT
{
public:
    RRT();

    // Constructor && Set Map
    RRT(int width=200, int height=200);

    inline double dist(const pt& a, const pt& b){
        return sqrt( pow(a.first-b.first, 2) + pow(a.second-b.second, 2) );
    }

    // Make 'n Random Obstacles' to Map
    void createRandomObstaclels(int n);

    void setGoal(const pt& x, const double& th=5.0);

    void solve(bool flag_visual=false);

    void printPath();
// k=cv2.waitKey(10) & 0XFF

private:
    vector<vi8>* mapPtr_;
    double w_, h_;
    pt start, goal;
    int goalThreshold;
    Sampler* spr;
    NearestNeighbors* nn;
    double minStep=5.0;
    double maxStep=100.0;
};

#endif