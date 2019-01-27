//
// Created by pc-20171125 on 2019/1/20.
//

#ifndef GBDT_DATASET_H
#define GBDT_DATASET_H

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <memory>
#include <set>
#include <string>

using namespace std;

class Sample{
private:
    int dim;
    vector<double> data;
public:
    explicit Sample(int dim);
    explicit Sample(vector<double> &data){
        this->dim = data.size();
        this->data = move(data);
    }
    double get(int i){
        return this->data[i];
    }
};

class DataSet{
private:
    vector<shared_ptr<Sample>> sample_list;
    vector<set<double>> fea_val_set;
    vector<double> label_list, hide_label_list;
    int dim;
public:
    explicit DataSet(int dim);
    explicit DataSet(string dataset_name);
    DataSet(int sample_num, int dim, int label_num);
    void add_sample(shared_ptr<Sample> &ptr);
    void add_sample(shared_ptr<Sample> &ptr, double label);
    void init_fea_val_set();
    shared_ptr<Sample> get_sample(int i){return this->sample_list[i];}
    int get_sample_num(){return this->sample_list.size();}
    int get_label_num(){return this->label_list.size();}
    int get_dim(){return this->dim;}
    // 这个函数的返回值设置是否合理?
    const set<double> &get_val_set(int i){
        const set<double> &tmp = fea_val_set[i];
        return tmp;
    }
    double get_label(int i){return this->label_list[i];}
    void hide_label();
    void show_label();
    void update_label(const vector<double> &new_label);
};

#endif //GBDT_DATASET_H
