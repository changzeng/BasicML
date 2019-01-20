#include <iostream>
#include "kmeans.cpp"
#include <fstream>
#include <string>
#include <Python.h>

using namespace std;

bool gen_dataset(int dim, int point_num, vector<Point> & dataset){
    srand((unsigned)time(NULL));
    for(int i=0; i<point_num; i++) {
        vector<double> tmp;
        for (int j = 0; j < dim; j++) {
            tmp.push_back(rand()%100000);
        }
        dataset.emplace_back(dim, tmp);
    }
    return true;
}

void save_dataset(int dim, int point_num, vector<Point> & dataset,
        vector<int> & predict, const string & file_name){
    ofstream writer = ofstream(file_name);
    for(int i=0; i<point_num; i++){
        for(int j=0; j<dim; j++){
            writer<<dataset[i].get(j)<<" ";
        }
        writer<<predict[i]<<"\n";
    }
    writer.close();
}

int main(){
//    Py_Initialize();
//
//    if ( !Py_IsInitialized() ) {
//        cout<<"python initialize failed!"<<endl;
//        return -1;
//    }
//
//    PyRun_SimpleString("import sys");
//    // PyRun_SimpleString("sys.path.append('./')");
//    PyObject *pName,*pModule,*pDict,*show_func,*pArgs;
//
//    pName = PyUnicode_FromString("plot");
//    pModule = PyImport_Import(pName);
//    if ( !pModule ) {
//        printf("can't find plot.py");
//        return -1;
//    }
//
//    pDict = PyModule_GetDict(pModule);
//    show_func = PyDict_GetItemString(pDict, "show_cluster");

    int dim = 2, point_num = 100000, center_num=8;
    vector<int> test, predict;

//    pArgs = PyTuple_New(center_num);

    vector<Point> dataset;
    gen_dataset(dim, point_num, dataset);

    KMeans model = KMeans(center_num, dim, 10000);
    model.fit(point_num, dataset);
    model.predict(point_num, dataset, predict);

    save_dataset(dim, point_num, dataset, predict, "dataset");
    model.save_center("center_list");

//    PyObject_CallObject(show_func, pArgs);
//    Py_Finalize();

    return 0;
}