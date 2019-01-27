//
// Created by pc-20171125 on 2019/1/20.
//

#include "cart.h"
#include <iostream>
#include <math.h>
#include <float.h>

using namespace std;

void CartNode::set_as_leaf(){
    this->_is_leaf = true;
    double tmp_fea_val = 0.0;
    int label_num = this->dataset->get_label_num();
    for(int i=0; i<label_num; i++){
        tmp_fea_val += this->dataset->get_label(i);
    }
    this->fea_val = tmp_fea_val / label_num;
}

double CartNode::mse_score(){
    if(this->_mse_score != -1)
        return this->_mse_score;
    if(this->get_sample_num() == 0)
        return 0.0;
    this->_mse_score = 0;
    double _avg = 0;
    int sample_num = this->get_sample_num();
    int label_num = this->get_label_num();
    if(sample_num != label_num){
        cout<<"sample_num not equal label_num"<<endl;
    }
    for(int i=0; i<label_num; i++){
        _avg += this->dataset->get_label(i);
    }
    _avg /= label_num;
    for(int i=0; i<label_num; i++){
        this->_mse_score += pow(this->dataset->get_label(i) - _avg, 2);
    }
    this->_mse_score = sqrt(this->_mse_score / label_num);
    return this->_mse_score;
}

void CartNode::split_by_fea_val(int ind, double val, shared_ptr<CartNode> &left, shared_ptr<CartNode> &right){
    bool has_label = this->get_label_num()>0;
    shared_ptr<Sample> sample;
    shared_ptr<CartNode> tmp_node;
    for(int i=0; i<this->get_sample_num(); i++){
        sample = this->get_sample(i);
        if(sample->get(ind) < val){
            tmp_node = left;
        }else{
            tmp_node = right;
        }
        if(has_label){
            tmp_node->add_sample(sample, this->dataset->get_label(i));
        }else{
            tmp_node->add_sample(sample);
        }
    }
}

void CartNode::split_by_mse(queue<shared_ptr<CartNode>> &node_queue, shared_ptr<Parameter> &parameters){
    if(this->dataset->get_sample_num() <= (int)parameters->get("min_sample_num") ||
    this->get_depth() >= (int)parameters->get("max_depth")) {
        this->set_as_leaf();
    }else{
        double best_score = DBL_MAX, best_val = 0.0;
        int best_ind=0;
        shared_ptr<CartNode> best_left, best_right;
        for (int i = 0; i < this->get_dim(); i++) {
            const set<double> &val_set = this->dataset->get_val_set(i);
            for (auto val : val_set) {
                shared_ptr<CartNode> left = make_shared<CartNode>(this->get_dim());
                shared_ptr<CartNode> right = make_shared<CartNode>(this->get_dim());
                this->split_by_fea_val(i, val, left, right);
                double total_score = left->mse_score() + right->mse_score();
                if (total_score < best_score) {
                    best_score = total_score;
                    best_ind = i;
                    best_val = val;
                    best_left = left;
                    best_right = right;
                }
            }
        }
        this->mse_gain = this->mse_score() - best_score;
        if(this->mse_gain > parameters->get("min_gain")) {
            int cur_depth = this->get_depth();
            if (best_left->get_sample_num() > 0) {
                best_left->set_depth(cur_depth + 1);
                this->left = best_left;
                node_queue.push(best_left);
            }
            if (best_right->get_sample_num() > 0) {
                best_right->set_depth(cur_depth + 1);
                this->right = best_right;
                node_queue.push(best_right);
            }
            this->fea_ind = best_ind;
            this->fea_val = best_val;
        }else{
            this->set_as_leaf();
        }
    }
     this->release_dataset();
}

void Cart::fit(shared_ptr<DataSet> &dataset){
    this->root = make_shared<CartNode>(dataset);
    queue<shared_ptr<CartNode>> node_queue;
    node_queue.push(this->root);
    int node_ind = 0;
    while(! node_queue.empty()){
        cout<<node_ind<<endl;
        node_ind++;
        shared_ptr<CartNode> tmp_node = node_queue.front();
        node_queue.pop();
        tmp_node->split_by_mse(node_queue, this->parameters);
    }
}

void Cart::predict(shared_ptr<DataSet> &dataset, vector<double> &res){
    for(int i=0; i<dataset->get_sample_num(); i++) {
        shared_ptr<CartNode> cur_node = this->root;
        while (!cur_node->is_leaf()) {
            int fea_ind = cur_node->get_fea_ind();
            double fea_val = cur_node->get_fea_val();
            if(dataset->get_sample(i)->get(fea_ind) < fea_val){
                cur_node = cur_node->get_left();
            }else{
                cur_node = cur_node->get_right();
            }
        }
        res.push_back(cur_node->get_fea_val());
    }
}

void Cart::show_sample_num(){
    queue<shared_ptr<CartNode>> traverse_queue;
    traverse_queue.push(this->root);
}
