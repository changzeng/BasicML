//
// Created by pc-20171125 on 2019/1/27.
//

#ifndef GBDT_CART_H
#define GBDT_CART_H

#include "parameter.h"
#include "dataset.h"
#include <queue>

using namespace std;

class CartNode{
private:
    bool _is_leaf = false;
    int fea_ind, depth = 0;
    double fea_val, _mse_score = -1, mse_gain = 0;
    shared_ptr<CartNode> left= nullptr, right= nullptr;
    shared_ptr<DataSet> dataset;
public:
    explicit CartNode(int dim){this->dataset = make_shared<DataSet>(dim);}
    explicit CartNode(shared_ptr<DataSet> &dataset):dataset(dataset){};
    void split_by_fea_val(int ind, double val, shared_ptr<CartNode> &left, shared_ptr<CartNode> &right);
    void split_by_mse(queue<shared_ptr<CartNode>> &node_queue, shared_ptr<Parameter> &parameters);
    void release_dataset(){this->dataset.reset();}
    void add_sample(shared_ptr<Sample> &sample){this->dataset->add_sample(sample);}
    void add_sample(shared_ptr<Sample> &sample, double label){this->dataset->add_sample(sample, label);}
    void set_depth(int h){this->depth=h;}
    void set_as_leaf();
    int get_fea_ind(){return this->fea_ind;}
    int get_dim(){return this->dataset->get_dim();}
    int get_depth(){return this->depth;}
    int get_sample_num(){return this->dataset->get_sample_num();}
    int get_label_num(){return this->dataset->get_label_num();}
    bool is_leaf(){return this->_is_leaf;}
    double mse_score();
    double get_fea_val(){return this->fea_val;}
    shared_ptr<Sample> get_sample(int i){return this->dataset->get_sample(i);}
    shared_ptr<CartNode> get_left(){return this->left;}
    shared_ptr<CartNode> get_right(){return this->right;}
};

class Cart{
private:
    shared_ptr<CartNode> root;
    shared_ptr<Parameter> parameters;
public:
    explicit Cart(shared_ptr<Parameter> &parameters):parameters(parameters){};
    void fit(shared_ptr<DataSet> &dataset);
    void predict(shared_ptr<DataSet> &dataset, vector<double> &res);
    void show_sample_num();
};

#endif //GBDT_CART_H
