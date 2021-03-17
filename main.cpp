#include <iostream>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>

#include <RRT.hpp>
#include <Map.hpp>

using namespace std;
using namespace cv;

typedef vector<uint8_t> vi8;

const int MAP_WIDTH = 1000;
const int MAP_HEIGHT = 1000;

void unitTest_Sampler();

int main()
{
    // Construct Map and Set Planner
    // RRT rrt(MAP_WIDTH, MAP_HEIGHT);
    // rrt.solve(true);
    
    
    return 0;
}







void unitTest_Sampler()
{
    Sampler A;
    for(int i=0; i<5; i++)
    {
        cout << A.uni01() << " ";
    }   cout << endl;

    int cnt[11]{};
    for(int i=0; i<10000; i++)
    {
        int x =  A.uniIntBound(0, 10);
        cnt[x]++;
    }

    for(int i=0; i <= 10; i++)
    {
        cout << i << ": " << cnt[i] << endl;
    }
}