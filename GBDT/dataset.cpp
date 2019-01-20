//
// Created by pc-20171125 on 2019/1/20.
//

#include <iostream>
#include <vector>
#include <string>
#include <random>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::default_random_engine;

class Sample{
private:
    int dim;
    vector<int> data;
public:
    Sample(int dim, vector<int> vec){
        for(int i=0; i<dim; i++)
            this->data.push_back(vec[i]);
    }
    Sample(int dim){
        for(int i=0; i<dim; i++)
            this->data.push_back(rand()%1000 - 500);
    }
};

class DataSet{
private:
    vector<Sample *> sample_list;
    vector<int> label_list;
    int sample_num, dim, label_num;
public:
    DataSet(const string & file_name){

    }
    DataSet(int sample_num, int dim, int label_num){
        default_random_engine randint;
        this->sample_num = sample_num;
        this->dim = dim;
        this->label_num = label_num;
        for(int i=0; i<sample_num; i++){
            this->sample_list.push_back(new Sample(dim));
            this->label_list.push_back(randint()%label_num);
        }
    }
    ~DataSet(){
        for(int i=0; i<this->sample_num; i++){
            delete this->sample_list[i];
        }
    }
};