#include <iostream>
#include <vector>
#include "dataset.h"
#include "cart.cpp"

using namespace std;

int main() {
    shared_ptr<DataSet> dataset = make_shared<DataSet>(1000, 10, 2);
    Cart cart;
    cart.fit(dataset);
//    GBDT model = GBDT();
//    model.fit(dataSet);
    return 0;
}