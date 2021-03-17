#include <RRT.hpp>

RRT::RRT(int width, int height) 
{
    w_ = (double)width, h_ = (double)height;
    start = {w_/2, h_/2};

    spr = new Sampler();
    nn = new NearestNeighbors();
    mapPtr_ = new vector<vi8>(height, vi8(width, 0));
    
    for(uint j = 0; j < w_; j++)
    {
        (*mapPtr_)[0][j] = 1;
        (*mapPtr_)[h_-1][j] = 1;
    }
    
    for(uint i = 1; i < h_ - 1; i++)
        (*mapPtr_)[i][0] = (*mapPtr_)[i][w_-1] = 1; 
}

void RRT::setGoal(const pt& x, const double& th=5.0)
    {
        goal = x;
        goalThreshold = th;
    }

void RRT::solve(bool flag_visual)
{
    bool notSolved = true;
    nn->add(start);

    while(notSolved)
    {
        pt x_rnd = {spr->uniRealBound(0.0, w_), spr->uniRealBound(0.0, h_)};
        pt x_near = nn->nearest(x_rnd);
        pt x_new;
        double d = dist(x_near, x_rnd);
        
        if(d < minStep) 
            continue;
        
        if(d > maxStep)
        {
            pt ref = {x_rnd.first - x_near.first, x_rnd.second - x_near.second};
            ref = {ref.first*maxStep/d, ref.second*maxStep/d};
            x_new = {x_near.first + ref.first, x_near.second + ref.second};
        }
        else
        {
            x_new = x_rnd;
        }


        // Validity Check
        if(x_new.first < 1.0 || x_new.first >= w_ || x_new.second < 1.0 || x_new.second >= h_)
            continue;

        // TODO : ADD Obstacles Process

        if(dist(x_new, goal) <= goalThreshold){
            notSolved = false;
            printPath();
        }
        
        // Visualize
        if(!flag_visual)
            continue;

        Mat img(Size(w_, h_), CV_8UC3, {255, 255, 255});
        imshow("image",img);
        if ((waitKey(10) & 0xFF) == 27)
            break;
    }
}
