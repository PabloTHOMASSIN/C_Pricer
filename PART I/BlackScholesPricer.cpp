#include "BlackScholesPricer.h"
#include <cmath>
#include "stdexcept"
using namespace std;

BlackScholesPricer::BlackScholesPricer(VanillaOption* option, double asset_price, double interest_rate, double volatility) : option_(option), asset_price_(asset_price), interest_rate_(interest_rate), volatility_(volatility){
    if(option_ == nullptr){throw invalid_argument("Option must be initialize as it's a pointer");}
}
double BlackScholesPricer::operator()() const{
    double S = asset_price_;
    double K = option_ -> GetStrike();
    double T = option_ -> GetExpiry();
    double r = interest_rate_;
    double sigma = volatility_;

    double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);

    if (option_->GetOptionType() == OptionType::Call) {
        return S * std::erfc(-d1 / sqrt(2)) - K * exp(-r * T) * std::erfc(-d2 / sqrt(2));
    } else {
        return K * exp(-r * T) * std::erfc(d2 / sqrt(2)) - S * std::erfc(d1 / sqrt(2));
    }
}
double BlackScholesPricer::delta() const {
    double S = asset_price_;
    double K = option_->GetStrike();
    double T = option_->GetExpiry();
    double r = interest_rate_;
    double sigma = volatility_;

    double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));

    if (option_->GetOptionType() == OptionType::Call) {
        return std::erfc(-d1 / sqrt(2));
    } else {
        return -std::erfc(-d1 / sqrt(2));
    }
}
BlackScholesPricer::~BlackScholesPricer()
{
    // Release any dynamically allocated memory
    if (option_ != nullptr)
    {
        delete option_;
        option_ = nullptr; // Set the pointer to null to prevent double deletion.
    }
}

