//
// Created by pc-20171125 on 2019/1/21.
//

#ifndef KD_TREE_KD_TREE_H
#define KD_TREE_KD_TREE_H

#include <memory>
#include <vector>
#include <random>

using namespace std;

class Point{
private:
    int dim;
    vector<double> values;
    default_random_engine randint;
public:
    explicit Point(int dim);
    double get(int i);
};

class Node{
public:
    shared_ptr<Node> left, right;
    vector<shared_ptr<Point>> point_list;
    int split_index, point_num;
    double split_value;
    Node(vector<shared_ptr<Point>> &dataset);
    int get_point_num(){return this->point_list.size();}
};

class KDTree{
private:
    int dim;
    shared_ptr<Node> root;
public:
    KDTree(int dim);
    void split(shared_ptr<Node> & node);
    void fit(vector<shared_ptr<Point>> &dataset, int point_num);
    void knn(Point & point, int k);
};

#endif //KD_TREE_KD_TREE_H
