#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <chrono>
#include <Personne.h>
#include <Operation.h>

using namespace std;

class RecurrentOperation : public Operation {
private:
    chrono::seconds p_recurrence;
    bool p_active;
    int p_count;
    static inline bool p_activeThread;

protected:
    //

public:
    // Constructeurs
    RecurrentOperation();
    RecurrentOperation(string date, string name, float sum, chrono::seconds recurrence, bool active);

    // Destructeur
    ~RecurrentOperation() = default;

    // Methodes
    string toString();
    void incrCount();

    // Getters
    chrono::seconds getRecurrence();
    bool getActive();
    int getCount();
    bool getActiveThread();

    // Setters
    void setReccurence(chrono::seconds recurrence);
    void setActive(bool active);
    void setCount(int count);
    void setActiveThread(bool active);

};