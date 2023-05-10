#include "Operation.h"

Operation::Operation(string date, string name, float sum){
    this->p_date = date;
    this->p_name = name;
    this->p_sum = sum;
}

string Operation::getDate(){ return this-> p_date; }
string Operation::getName(){ return this-> p_name; }
float Operation::getSum(){ return this-> p_sum;    }

void Operation::setDate(string date){
    this-> p_date = date;
}

void Operation::setName(string name){
    this-> p_name = name;
}

void Operation::setSum(float sum){
    this-> p_sum = sum;
}

string Operation::toString(){
    stringstream ss;

    if (getSum() > 0){
        ss << getName() << " (" << getDate() << ") : +" << getSum() << "EUR" << endl;
    } else {
        ss << getName() << " (" << getDate() << ") : " << getSum() << "EUR" << endl;
    }

    return ss.str();
}

Operation::~Operation(){}