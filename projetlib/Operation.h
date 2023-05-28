#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

class Operation{
private:
    string p_date;
    string p_name;
    float p_sum;

protected:
    //

public:
    //Constructeurs
    Operation() = default;
    Operation(string date, string name, float sum);

    //Destructeur
    ~Operation();

    //Getters
    string getDate();
    string getName();
    float getSum();

    //Setter
    void setDate(string date);
    void setName(string name);
    void setSum(float sum);

    //Methode
    string toString();

};