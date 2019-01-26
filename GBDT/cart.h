//
// Created by pc-20171125 on 2019/1/27.
//

#ifndef GBDT_CART_H
#define GBDT_CART_H

#include "dataset.h"
#include <queue>

using namespace std;

class CartNode{
private:
    int fea_ind;
    double fea_val;
    CartNode *left= nullptr, *right= nullptr;
    shared_ptr<DataSet> dataset;
public:
    void split(queue<shared_ptr<CartNode>> &node_queue);
};

class Cart{
private:
    shared_ptr<CartNode> root;
public:
    void fit(shared_ptr<DataSet> &dataset);
    void predict(shared_ptr<DataSet> &dataset);
};

#endif //GBDT_CART_H
