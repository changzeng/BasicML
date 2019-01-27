//
// Created by pc-20171125 on 2019/1/27.
//

#ifndef GBDT_GBDT_H
#define GBDT_GBDT_H

#include "cart.h"
#include "parameter.h"

class GBDT{
private:
    vector<shared_ptr<Cart>> forest;
    shared_ptr<Parameter> parameters;
public:
    GBDT(shared_ptr<Parameter> &parameters):parameters(parameters){};
    void fit(shared_ptr<DataSet> &dataset);
    void predict(shared_ptr<DataSet> &dataset, vector<double> &res);
};

#endif //GBDT_GBDT_H
