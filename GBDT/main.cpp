#include <iostream>
#include <vector>
#include "dataset.h"
#include "cart.h"
#include "parameter.h"
#include "gbdt.h"

using namespace std;

int main() {
    shared_ptr<DataSet> dataset = make_shared<DataSet>(100, 2, 2);
    // shared_ptr<DataSet> dataset = make_shared<DataSet>("boston_house_prices.csv");
    shared_ptr<Parameter> parameters = make_shared<Parameter>();
    parameters->add("max_depth", 10.0);
    parameters->add("min_gain", 0.001);
    parameters->add("min_sample_num", 20);
    parameters->add("max_tree_num", 10);
    // Cart model(parameters);
    // cart.fit(dataset);
    GBDT model = GBDT(parameters);
    model.fit(dataset);

    vector<double> predict;
    model.predict(dataset, predict);
    for(int i=0; i<dataset->get_label_num(); i++){
        cout<<dataset->get_label(i)<<" "<<predict[i]<<endl;
    }
    return 0;
}
