//
// Created by pc-20171125 on 2019/1/20.
//

#include "dataset.h"
#include <memory>
#include <math.h>
#include <queue>
#include <string>

using namespace std;

class Node{
private:
    shared_ptr<DataSet> dataset;
public:
    shared_ptr<Node> left, right, parent;
    int best_split_fea;
    double best_split_val, best_score;
    string son_type;
    int height;
    Node(shared_ptr<DataSet> & dataset){
        this->dataset = dataset;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        this->height = 0;
    }

    double split(shared_ptr<DataSet> & left, shared_ptr<DataSet> & right){
        double cur_score = this->score(this->dataset);
        double best_score = 0.0, best_split_val = 0.0;
        int fea_index = 0, best_split_fea=0;
        for(auto fea : dataset->feature_list){
            for(auto val : fea){
                auto tmp_left = make_shared<DataSet>();
                auto tmp_right = make_shared<DataSet>();
                dataset->split(fea_index, val, tmp_left, tmp_right);
                double score = this->score(tmp_left) + this->score(tmp_right);
                if(fea_index == 1 || score < best_score){
                    best_score = score;
                    best_split_fea = fea_index;
                    best_split_val = val;
                }
            }
            fea_index += 1;
        }
        this->best_score = best_score;
        this->best_split_fea = best_split_fea;
        this->best_split_val = best_split_val;
        dataset->split(best_split_fea, best_split_val, left, right);
        return cur_score - best_score;
    }

    double score(shared_ptr<DataSet> & data){
        if(data->get_sample_num() == 0)
            return 0.0;
        double _sum = 0.0, _avg = 0.0, _score = 0.0;
        int _count = 0;
        for(auto val : data->label_list){
            _sum += val;
            _count += 1;
        }
        _avg = _sum / _count;
        for(auto val : data->label_list){
            _score += pow(val-_avg, 2.0);
        }
        return sqrt(_score / _count);
    }
};

class Cart{
private:
    shared_ptr<Node> root;
    double threshold = 0.01;
public:
    void predict(shared_ptr<DataSet> & dataset, vector<double> & res){

    }

    void fit(shared_ptr<DataSet> & dataset){
        this->root = make_shared<Node>(dataset);
        queue<shared_ptr<Node>> node_queue;
        node_queue.push(this->root);

        while (! node_queue.empty()){
            shared_ptr<Node> cur_node_ptr = node_queue.front();
            cout<<cur_node_ptr->height<<endl;
            node_queue.pop();

            shared_ptr<DataSet> left=make_shared<DataSet>();
            shared_ptr<DataSet> right=make_shared<DataSet>();
            double score = cur_node_ptr->split(left, right);
            cout<<"hello"<<endl;
            if(score <= this->threshold)
                continue;
            if(cur_node_ptr->height != 0){
                shared_ptr<Node> parent = cur_node_ptr->parent;
                if(cur_node_ptr->son_type == "left")
                    parent->left = cur_node_ptr;
                else
                    parent->right = cur_node_ptr;
            }

            auto left_ptr = make_shared<Node>(left);
            auto right_ptr = make_shared<Node>(right);
            left_ptr->parent = right_ptr->parent = cur_node_ptr;
            left_ptr->height = right_ptr->height = cur_node_ptr->height + 1;
            left_ptr->son_type = "left";
            right_ptr->son_type = "right";

            node_queue.push(left_ptr);
            node_queue.push(right_ptr);
        }
    }
};