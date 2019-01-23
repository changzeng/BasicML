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

DataSet::DataSet(){
    this->sample_num = 0;
    this->label_num = 0;
}

void DataSet::make_feature_list() {
    for(int i=0; i<this->dim; i++)
        this->feature_list.emplace_back();
    for(auto &sample : this->sample_list){
        for(int i=0; i<this->dim; i++)
            this->feature_list[i].insert(sample->get(i));
    }
}

void DataSet::add_sample(shared_ptr<Sample> ptr){
    this->sample_list.push_back(ptr);
    this->sample_num += 1;
}

void DataSet::split(int fea_index, double fea_val, shared_ptr<DataSet> & left, shared_ptr<DataSet> & right){
    int i=0;
    for(auto &sample : this->sample_list){
        if(sample->get(fea_index) < fea_val){
            left->add_sample(sample);
            left->label_list.push_back(this->label_list[i]);
            left->label_num += 1;
        }else{
            right->add_sample(sample);
            right->label_list.push_back(this->label_list[i]);
            right->label_num += 1;
        }
        i += 1;
    }
    left->make_feature_list();
    right->make_feature_list();
}
