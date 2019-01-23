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
    int sample_num, dim, label_num;
public:
    vector<set<double>> feature_list;
    vector<double> label_list;

    DataSet(int sample_num, int dim, int label_num);
    DataSet();
    void add_sample(shared_ptr<Sample> ptr);
    void make_feature_list();
    void split(int fea_index, double fea_val, shared_ptr<DataSet> & left, shared_ptr<DataSet> & right);
    int get_sample_num(){ return this->sample_num;}
};

#endif //GBDT_DATASET_H
