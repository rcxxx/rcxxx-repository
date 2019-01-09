
#ifndef MATCHANDGROUP_H
#define MATCHANDGROUP_H

#include <math.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "contourfeature.h"

using namespace cv;

bool Rect_different(const RotatedRect &r1, const RotatedRect &r2)
{
    bool is = 0;
    float w1,w2;
    float h1,h2;
    if (r1.size.height > r1.size.width)
    {
        h1 = r1.size.height;
        w1 = r1.size.width;
    }
    else
    {
        w1 = r1.size.height;
        h1 = r1.size.width;
    }
    if (r2.size.height > r2.size.width)
    {
        h2 = r2.size.height;
        w2 = r2.size.width;
    }
    else
    {
        w2 = r2.size.height;
        h2 = r2.size.width;
    }
    float x1 = r1.center.x + r1.size.width/2;
    float y1 = r1.center.y + r1.size.height/2;
    float x2 = r2.center.x + r2.size.width/2;
    float y2 = r2.center.y + r2.size.height/2;
    float slope = fabs((y1-y2)/(x1-x2));
    float distance = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
    float w = abs(w1-w2);
    float h = abs(h1-h2);
    if(slope<0.5)
    {
        if(distance > max(w1,w2)*6 || (max(w1,w2)*10.5 < distance && distance < max(w1,w2)*14.5))
        {
            if(h>w)
            {
                float ratio = h/max(h1,h2);
                if(ratio < 0.16)
                    is = 1;
            }
            else
            {
                float ratio = w/max(w1,w2);
                if(ratio < 0.16)
                    is = 1;
            }
        }
    }
    return is;
}

bool Light_filter(RotatedRect R_rect_1,RotatedRect R_rect_2)
{
    bool is = 0;
    int w1,w2;
    int h1,h2;
    if (R_rect_1.size.height > R_rect_1.size.width)
    {
        h1 = R_rect_1.size.height;
        w1 = R_rect_1.size.width;
    }
    else
    {
        w1 = R_rect_1.size.height;
        h1 = R_rect_1.size.width;
    }
    if (R_rect_2.size.height > R_rect_2.size.width)
    {
        h2 = R_rect_2.size.height;
        w2 = R_rect_2.size.width;
    }
    else
    {
        w2 = R_rect_2.size.height;
        h2 = R_rect_2.size.width;
    }
    float Area_1 = (float)w1*(float)h1;
    float Area_2 = (float)w2*(float)h2;
    float ratio;
    if(Area_1>Area_2)
    {
        ratio = Area_2/Area_1;
    }
    else
    {
        ratio = Area_1/Area_2;
    }
    if(0.4 < ratio && ratio < 1)
        is = 1;
    return is;
}

bool Distance_Height(RotatedRect R_rect_1, RotatedRect R_rect_2)
{
    float distence = CenterDistance(R_rect_1.center,R_rect_2.center);
    bool is = 0;
    //int w1,w2;
    int h1,h2;
    if (R_rect_1.size.height > R_rect_1.size.width)
    {
        h1 = R_rect_1.size.height;
        //w1 = R_rect_1.size.width;
    }
    else
    {
        //w1 = R_rect_1.size.height;
        h1 = R_rect_1.size.width;
    }
    if (R_rect_2.size.height > R_rect_2.size.width)
    {
        h2 = R_rect_2.size.height;
        //w2 = R_rect_2.size.width;
    }
    else
    {
        //w2 = R_rect_2.size.height;
        h2 = R_rect_2.size.width;
    }
    int h;
    if(h1>h2)
    {
        h = h1;
    }
    else
    {
        h = h2;
    }
    if((distence > h && distence < h*3) || (distence > h*3 && distence < h*6))
    {
        is = 1;
    }
    return is;
}

#endif // MATCHANDGROUP_H
