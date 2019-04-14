//
// Created by vsmaxim on 14.04.2019.
//

#ifndef DYNAMIC_SOLVER_SOLVER_H
#define DYNAMIC_SOLVER_SOLVER_H

#include <math.h>
#include <vector>
#include <unordered_map>


double local_win(double s, double u) {
    return 12 + pow(u + 40, 1.0 / 3) + pow((s - u + 30), 1.0 / 3);
}


double local_state_change(double s, double u) {
    return 0.8 * u + 0.66 * (s - u);
}


class DynamicSolver {
private:
    long maxStage;
    double precision;
    std::vector<std::unordered_map<double, std::pair<double, double>>> cache;
public:
    DynamicSolver(long maxStage, double precision) : maxStage(maxStage), precision(precision) {
        cache.resize(static_cast<unsigned int>(maxStage + 1));
    }

    void setPrecision(double precision) {
        this->precision = precision;
        cache[0].clear();
    }

    std::pair<double, double> global_profit(int stage, double state) {
        if (stage >= maxStage) {
            return std::make_pair(0, 0);
        }

        if (cache[stage].find(state) != cache[stage].end()) {
            return cache[stage][state];
        }

        double stateDiff, profit;
        double maxProfit = 0, maxManagement;

        for (int managementStep = 0; managementStep * precision <= state; managementStep++) {
            stateDiff = local_state_change(state, managementStep * precision);
            profit = local_win(state, managementStep * precision) + global_profit(stage + 1, stateDiff).first;

            if (profit > maxProfit) {
                maxProfit = profit;
                maxManagement = managementStep * precision;
            }
        }
        cache[stage][state] = std::make_pair(maxProfit, maxManagement);
        return std::make_pair(maxProfit, maxManagement);
    }

    std::pair<double, double> solve(double initialState) {
        if (cache[0].find(initialState) != cache[0].end()) {
            cache[0].erase(cache[0].find(initialState));
        }
        return global_profit(0, initialState);
    }
};
#endif //DYNAMIC_SOLVER_SOLVER_H
