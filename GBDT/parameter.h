//
// Created by pc-20171125 on 2019/1/27.
//

#ifndef GBDT_PARAMETER_H
#define GBDT_PARAMETER_H

#include <unordered_map>
#include <string>

using namespace std;

class Parameter{
private:
    unordered_map<string, double> parameters;
public:
    void add(string name, double val){parameters[name] = val;}
    double get(string name){
        if(parameters.find(name) == parameters.end())
            return -1;
        return parameters[name];
    }
};

#endif //GBDT_PARAMETER_H
