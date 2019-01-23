//
// Created by pc-20171125 on 2019/1/21.
//

#include "kd_tree.h"
#include <random>
#include <queue>
#include <math>

Point::Point(int dim) {
    this->dim = dim;
    for(int i=0; i<dim; i++){
        this->values.push_back(this->randint());
    }
}

double Point::get(int i) {
    return this->values[i];
}

Node::Node(vector<shared_ptr<Point>> &dataset) {
    this->left = nullptr;
    this->right = nullptr;
    for(auto point_ptr : dataset){
        this->point_list.push_back(point_ptr);
    }
}

KDTree::KDTree(int dim) {
    this->dim = dim;
}

// 执行节点分割
void KDTree::split(shared_ptr<Node> &node) {
    int point_num = node->get_point_num();
    int split_index;
    double split_val;
    vector<double> total;
    double max_var;
    for(int i=0; i<this->dim; i++) {
        total.push_back(0);
    }
    for(int i=0; i<this->dim; i++){
        for(int j=0; j<point_num; j++){
            total[j] += node->point_list[j]->get(i);
        }
    }
    for(int i=0; i<this->dim; i++) {
        double avg = total[i] / point_num, var=0.0;
        for(int j=0; j<point_num; j++){
            var += pow(node->point_list[j]->get(i) - avg, 2.0);
        }
        var = sqrt(var) / point_num;
        if(i == 0 || var > max_var){
            max_var = var;
            split_index = i;
        }
    }
}

// 在数据集上构建kd-tree
void KDTree::fit(vector<shared_ptr<Point>> &dataset, int point_num) {
    this->root = make_shared<Node>(dataset);
    queue<shared_ptr<Node>> node_queue;
    node_queue.push(this->root);
    while (! node_queue.empty()){
        shared_ptr<Node> tmp_ptr = node_queue.front();
        node_queue.pop();
        this->split(tmp_ptr);
        if(tmp_ptr->left != nullptr)
            node_queue.push(tmp_ptr->left);
        if(tmp_ptr->right != nullptr)
            node_queue.push(tmp_ptr->right);
    }
}

// 使用kd-tree寻找k近邻
void KDTree::knn(Point &point, int k) {

}
