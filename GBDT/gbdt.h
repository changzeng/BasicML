//
// Created by pc-20171125 on 2019/1/27.
//

#ifndef GBDT_GBDT_H
#define GBDT_GBDT_H

#include "cart.h"

class GBDT{
private:
    vector<shared_ptr<Cart>> forest;
public:
    void fit(shared_ptr<DataSet> &dataset);
    void predict(shared_ptr<DataSet> &dataset);
};

#endif //GBDT_GBDT_H
