//
// Created by pc-20171125 on 2019/1/20.
//

#include "dataset.h"
#include <fstream>
#include <sstream>

using namespace std;

void split(const string &s, char sep_char, vector<string> &res) {
    res.clear();
    stringstream ss(s);
    string item;
    while(getline(ss, item, sep_char)) {
        res.push_back(item);
    }
}

Sample::Sample(int dim){
    this->dim = dim;
    for(int i=0; i<dim; i++)
        this->data.push_back(rand()%1000 - 500);
}

void DataSet::init_fea_val_set(){
    for(int i=0; i<this->dim; i++){
        this->fea_val_set.emplace_back();
    }
}

DataSet::DataSet(int dim){
    this->dim = dim;
    this->init_fea_val_set();
}

DataSet::DataSet(string file_name){
    ifstream file_read_fd(file_name);
    string line;
    getline(file_read_fd, line);
    vector<string> cols;
    split(line, ',', cols);
    this->dim = stoi(cols[1]);
    this->init_fea_val_set();
    getline(file_read_fd, line);    // read head
    while(getline(file_read_fd, line)){
        split(line, ',', cols);
        int ind;
        vector<double> tmp_vec;
        for(ind=0; ind<this->dim; ind++)
            tmp_vec.push_back(stod(cols[ind]));
        shared_ptr<Sample> sample_ptr = make_shared<Sample>(tmp_vec);
        this->add_sample(sample_ptr, stod(cols[ind]));
    }
}

DataSet::DataSet(int sample_num, int dim, int label_num){
    this->dim = dim;
    this->init_fea_val_set();
    for(int i=0; i<sample_num; i++){
        auto tmp_ptr = make_shared<Sample>(dim);
        auto label = rand()%label_num;
        this->add_sample(tmp_ptr, label);
    }
}

void DataSet::add_sample(shared_ptr<Sample> &ptr){
    this->sample_list.push_back(ptr);
    for(int i=0; i<this->dim; i++){
        this->fea_val_set[i].insert(ptr->get(i));
    }
}

void DataSet::add_sample(shared_ptr<Sample> &ptr, double label){
    this->add_sample(ptr);
    this->label_list.push_back(label);
}

void DataSet::hide_label(){
    for(auto val : this->label_list)
        this->hide_label_list.push_back(val);
}

void DataSet::show_label(){
    this->label_list.clear();
    for(auto val : this->hide_label_list)
        this->label_list.push_back(val);
}

void DataSet::update_label(const vector<double> &new_label){
    if(this->label_list.size() != new_label.size()){
        cout<<"size not math"<<endl;
        return ;
    }
    this->label_list.clear();
    for(auto val : new_label)
        this->label_list.push_back(val);
}
