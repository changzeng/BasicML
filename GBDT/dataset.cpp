//
// Created by pc-20171125 on 2019/1/20.
//

#include "dataset.h"

using namespace std;

Sample::Sample(int dim){
    this->dim = dim;
    for(int i=0; i<dim; i++)
        this->data.push_back(rand()%1000 - 500);
}

DataSet::DataSet(int sample_num, int dim, int label_num){
    default_random_engine randint;
    this->sample_num = sample_num;
    this->dim = dim;
    this->label_num = label_num;
    for(int i=0; i<sample_num; i++){
        auto tmp_ptr = make_shared<Sample>(dim);
        this->sample_list.push_back(tmp_ptr);
        this->label_list.push_back(randint()%label_num);
    }
    this->make_feature_list();
}

void DataSet::add_sample(shared_ptr<Sample> &ptr){
    this->sample_list.push_back(ptr);
    for(int i=0; i<this->dim; i++){
        this->feature_list[i].insert(ptr->get(i));
    }
}

void DataSet::add_sample(shared_ptr<Sample> &ptr, int label){
    this->add_sample(ptr);
    this->label_list.push_back(label);
}
