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

using namespace std;

class Sample{
private:
    int dim;
    vector<double> data;
public:
    explicit Sample(int dim);
    double get(int i){
        return this->data[i];
    }
};

class DataSet{
private:
    vector<shared_ptr<Sample>> sample_list;
    vector<set<double>> fea_val_set;
    vector<int> label_list;
    int dim;
public:
    explicit DataSet(int dim):dim(dim){};
    DataSet(int sample_num, int dim, int label_num);
    void add_sample(shared_ptr<Sample> &ptr);
    void add_sample(shared_ptr<Sample> &ptr, int label);
    shared_ptr<Sample> get_sample(int i){return this->sample_list[i];}
    int get_sample_num(){return this->sample_list.size();}
    int get_label(int i){return this->label_list[i];}
    int get_label_num(){return this->label_list.size();}
    int get_dim(){return this->dim;}
    void get_val_set(int i, const set<double> &val_set){val_set = fea_val_set[i];}
};

#endif //GBDT_DATASET_H
