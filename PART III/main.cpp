#include <iostream>
#include <vector>
#include "CallOption.h"
#include "PutOption.h"
#include "DigitalCallOption.h"
#include "DigitalPutOption.h"
#include "AsianCallOption.h"
#include "AsianPutOption.h"
#include "BlackScholesMCPricer.h"


int main() {
    double S0(100), K(101), T(5), r(0.01), sigma(0.1);
    std::vector<Option*> opt_ptrs;
    opt_ptrs.push_back(new CallOption(T, K));
    opt_ptrs.push_back(new PutOption(T, K));
    opt_ptrs.push_back(new DigitalCallOption(T, K));
    opt_ptrs.push_back(new DigitalPutOption(T, K));

    std::vector<double> fixing_dates;
    for (int i = 1; i <= 5; i++) {
        fixing_dates.push_back(0.1 * i);
    }
    opt_ptrs.push_back(new AsianCallOption(fixing_dates, K));
    opt_ptrs.push_back(new AsianPutOption(fixing_dates, K));

    std::vector<double> ci;
    BlackScholesMCPricer* pricer;

    for (auto& opt_ptr : opt_ptrs) {
        pricer = new BlackScholesMCPricer(opt_ptr, S0, r, sigma);
        do {
            pricer->generate(10);
            ci = pricer->confidenceInterval();
        } while (ci[1] - ci[0] > 0.1);
        std::cout << "nb samples: " << pricer->getNbPaths() << std::endl;
        std::cout << "price: " << (*pricer)() << std::endl << std::endl;
        delete pricer;
        delete opt_ptr;
    }
}