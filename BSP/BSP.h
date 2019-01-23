//
// Created by pc-20171125 on 2019/1/21.
//

#ifndef BSP_BSP_H
#define BSP_BSP_H

#include <vector>
#include <memory>

using namespace std;

class Point{
private:
    vector<int> data;
    int dim;
public:
    explicit Point(int);
};

class BSP{
private:
    vector<shared_ptr<Point>> left, right;
};

#endif //BSP_BSP_H
