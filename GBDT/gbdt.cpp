//
// Created by pc-20171125 on 2019/1/20.
//

#include "cart.h"
#include "gbdt.h"

using namespace std;

void GBDT::fit(shared_ptr<DataSet> &dataset){
    dataset->hide_label();
    int sample_num = dataset->get_sample_num();
    vector<double> predict_val(sample_num);
    vector<double> residual(sample_num);
    for(int i=0; i<this->parameters->get("max_tree_num"); i++){
        predict_val.clear();
        residual.clear();
        shared_ptr<Cart> tree = make_shared<Cart>(this->parameters);
        tree->fit(dataset);
        this->forest.push_back(tree);
        this->predict(dataset, predict_val);
        for(int i=0; i<dataset->get_sample_num(); i++)
            residual.push_back(dataset->get_label(i) - predict_val[i]);
        dataset->update_label(residual);
    }
    dataset->show_label();
}

void GBDT::predict(shared_ptr<DataSet> &dataset, vector<double> &res){
    res.clear();
    int sample_num = dataset->get_sample_num();
    vector<double> tmp_res(sample_num);
    for(int i=0; i<sample_num; i++)
        res.push_back(0.0);
    for(auto tree : this->forest){
        tmp_res.clear();
        tree->predict(dataset, tmp_res);
        for(int i=0; i<sample_num; i++)
            res[i] += tmp_res[i];
    }
}
