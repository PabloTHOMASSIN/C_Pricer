#ifndef CRRPricer_H
#define CRRPricer_H

#include "BinaryTree.h"
#include <cmath>
#include "Option.h"
#include "BinaryTree.cpp"

class CRRPricer {
private:
    Option* option;
    int N;
    double S0;
    double U, D, R;
    BinaryTree<double> tree;

    void compute();

public:
    CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate);
    double get(int n, int i);
    double operator()(bool closed_form = false);

    ~CRRPricer() = default;
};

#endif