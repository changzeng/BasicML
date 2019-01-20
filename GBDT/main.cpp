#include <iostream>
#include <vector>
#include "dataset.cpp"
#include "gbdt.cpp"

using std::cout;

int main() {
    DataSet dataSet = DataSet(1000, 10, 10);
    GBDT model = GBDT();
    model.fit(dataSet);
    return 0;
}