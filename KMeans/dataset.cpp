//
// Created by pc-20171125 on 2019/1/19.
//

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Point{
private:
    int dim;
    vector<double > values;
public:
    Point(int dim, vector<double > & values){
        for(int i=0; i<dim; i++)
            this->values.push_back(values[i]);
    }
    double get(int i){
        return this->values[i];
    }
};

class Cluster{
private:
    int K;
    vector<vector<int>> _container;
    vector<int> point_num;
public:
    Cluster(int K){
        this->K = K;
        for(int i=0; i<K; i++){
            this->_container.emplace_back();
            this->point_num.push_back(0);
        }
    }
    void refresh(){
        for(int i=0; i<this->K; i++){
            this->_container[i].clear();
            this->point_num[i] = 0;
        }
    }
    void add(int i, int point){
        this->_container[i].push_back(point);
        this->point_num[i] += 1;
    }
    int get(int i, int j){
        return this->_container[i][j];
    }
    int get_point_num(int i){
        return this->point_num[i];
    }
};

class DataSet{
private:
    vector<Point> data_list;
public:
    void random_init(int point_num, int dim){
        srand((unsigned)time(NULL));
        for(int i=0; i<point_num; i++) {
            vector<double> tmp;
            for (int j = 0; j < dim; j++) {
                tmp.push_back(rand()%10000);
            }
            this->data_list.emplace_back(dim, tmp);
        }
    }
};