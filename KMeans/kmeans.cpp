//
// Created by changzeng on 2019/1/17.
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
#include "dataset.cpp"
#include <sstream>

using namespace std;

class KMeans{
private:
    int center_num, dim, max_iteration;
    double threshold;
    vector<Point> center_list;
public:
    KMeans(int center_num, int dim, int max_iteration, double threshold=0.01){
        this->center_num = center_num;
        this->dim = dim;
        this->max_iteration = max_iteration;
        this->threshold = threshold;
    }

    double distance(Point & a, Point & b){
        double res = 0;
        for(int i=0; i<this->dim; i++){
            res += pow(a.get(i) - b.get(i), 2);
        }
        return sqrt(res);
    }

    void fit(int point_num, vector<Point> & dataset){
        // random select k center point
        vector<int> center_id_list;
        for(int i=0; i<this->center_num; i++) {
            int center_id;
            do {
                center_id = (int)(rand() % point_num);
                // cout<<center_id<<" "<<count(center_id_list.begin(), center_id_list.end(), center_id)<<endl;
            }while(count(center_id_list.begin(), center_id_list.end(), center_id) \
                != 0);
            center_id_list.push_back(center_id);
            this->center_list.push_back(dataset[center_id]);
        }

        // fit dataset
        int iter_num = 0;
        Cluster cluster(this->center_num);
        while(true){
            bool flag = true;
            cluster.refresh();
            for(int i=0; i<point_num; i++){
                double min_dist, dist;
                int center=0;
                for(int j=0; j<this->center_num; j++){
                    dist = this->distance(dataset[i], this->center_list[j]);
                    if(j==0 || dist<min_dist){
                        min_dist = dist;
                        center = j;
                    }
                }
                cluster.add(center, i);
            }

            for(int i=0; i<this->center_num; i++){
                int cluster_point_num = cluster.get_point_num(i);
                vector<double> center;
                for(int j=0; j<this->dim; j++)
                    center.push_back(0);
                for(int j=0; j<cluster_point_num; j++){
                    // cout<<i<<" "<<j<<" "<<cluster.get_point_num(i)<<endl;
                    int point = cluster.get(i, j);
                    for(int k=0; k<this->dim; k++){
                        center[k] += dataset[point].get(k);
                    }
                }
                for(int j=0 ; j<this->dim; j++){
                    center[j] = center[j] / cluster_point_num;
                }
                Point new_center = Point(this->dim, center);
                double shift = this->distance(new_center, this->center_list[i]);
                // cout<<shift<<endl;
                this->center_list[i] = new_center;
                if(shift >= this->threshold)
                    flag = false;
            }
            // cout<<iter_num<<endl;
            // cout<<flag<<endl;
            if(iter_num >= this->max_iteration || flag)
                break;
            iter_num += 1;
        }
    }

    void predict(int point_num, vector<Point> dataset, vector<int> & res){
        for(int i=0; i<point_num; i++){
            int center_id;
            double min_dist, dist;
            for(int j=0; j<this->center_num; j++){
                dist = this->distance(this->center_list[j], dataset[i]);
                if(j==0 || dist<min_dist){
                    min_dist = dist;
                    center_id = j;
                }
            }
            res.push_back(center_id);
        }
    }

    void save_center(const string & file_name){
        ofstream writer = ofstream(file_name);
        for(int i=0; i<this->center_num; i++){
            for(int j=0; j<this->dim; j++){
                writer<<this->center_list[i].get(j)<<" ";
            }
            writer<<"\n";
        }
        writer.close();
    }
};