#pragma once

#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <unordered_map>

namespace math
{
    [[nodiscard]] inline bool No_overflow(const long double& judge)
    {

		if (std::isinf(judge)) // Check for overflow
        {
            std::cerr << "ERR: Result overflow \n";
            return false;
        }
		if (std::isnan(judge)) 
        {
            std::cerr << "ERR: Invalid operation \n";
            return false;
        }
        return true;
    }
    inline void Process(std::string write_) //data
    {
        std::vector<std::string> data;
        std::vector <long double > sum;
        std::vector <std::string> symbol;
        //
        std::replace(write_.begin(), write_.end(), '\xa0', ' ');

        std::stringstream iss_data(write_);
        std::string read;
        while (iss_data >> read) data.push_back(read);

        if (data.empty())
        {
            std::cerr << "ERR : empty\n";
            return;
        }

        for (size_t A = 0;A < data.size();++A)
        {
            if ((A % 2) == 0)
            {   //Data extraction
                if (data[A].size() >= 19)
                {                                  //Check accuracy
                    std::cerr << "ERR:   '" << data[A] << "'   is out of calculation range.   \n    Location: " << A << " Parameters \n";
                    return;
                }
                try
                {
                    long double data_num = std::stold(data[A]);
                    sum.push_back(data_num);
                }
                catch (const std::exception& ec) {
                    std::cerr << "ERR : Invalid   '" << data[A] << "'   " << ec.what() << ".\n    Location: " << A << " Parameters \n";
                    return;
                }
            }

            else
            {  //Symbol extraction
                if (A >= data.size()) break;
                std::string symbol_data = data[A];
                symbol.push_back(symbol_data);
            }
        }


        for (const auto& sym : symbol) {
            if (sym != "^" && sym != "*" && sym != "/" && sym != "+" && sym != "-")
            {
                std::cerr << "ERR: Unrecognized operator '" << sym << "'\n";
                return;
            }
        }
        long double return_Result = sum.empty() ? 0.0L : sum[0];

        for (size_t A = 0;A < symbol.size();)
        {
            if (A + 1 >= sum.size()) { std::cerr << "ERR: Operand missing.\n"; return; }

            if (symbol[A] == "^")
            {
                return_Result = powl(sum[A], sum[A + 1]);
                sum[A] = return_Result;
                sum.erase(sum.begin() + A + 1);
                symbol.erase(symbol.begin() + A);
                if (!No_overflow(return_Result))return;
            }
            else { ++A; }
        }
        for (size_t B = 0;B < symbol.size();)
        {

            if (symbol[B] == "*")
            {
                return_Result = sum[B] * sum[B + 1];
                sum[B] = return_Result;
                sum.erase(sum.begin() + B + 1);
                symbol.erase(symbol.begin() + B);
                if (!No_overflow(return_Result))return;
            }
            else if (symbol[B] == "/")
            {
                if (sum[B + 1] == 0)
                {
                    std::cerr << "ERR: Division by zero.\n";
                    return;
                }
                return_Result = sum[B] / sum[B + 1];
                sum[B] = return_Result;
                sum.erase(sum.begin() + B + 1);
                symbol.erase(symbol.begin() + B);
                if (!No_overflow(return_Result))return;
            }
            else { ++B; }
        }
        for (size_t C = 0;C < symbol.size();)
        {
            if (symbol[C] == "+")
            {
                return_Result = sum[C] + sum[C + 1];
                sum[C] = return_Result;
                sum.erase(sum.begin() + C + 1);
                symbol.erase(symbol.begin() + C);
                if (!No_overflow(return_Result))return;
            }
            else if (symbol[C] == "-")
            {
                return_Result = sum[C] - sum[C + 1];
                sum[C] = return_Result;
                sum.erase(sum.begin() + C + 1);
                symbol.erase(symbol.begin() + C);
                if (!No_overflow(return_Result))return;
            }
            else { ++C; }
        }

        std::cout << "\n----------Result\n";
        std::cout << "Scientific notation:" << return_Result;
        std::cout << "\nNormal display:     ";
        std::string max = std::to_string(return_Result);
        if (return_Result == static_cast<long long> (return_Result))
        {
            if (max.size() >= 25)
            {
                std::cerr << "ERR : Data anomaly & Accuracy anomaly\n";
                return;
            }
            std::cout << std::fixed << std::setprecision(0) << return_Result << '\n';
        }
        else
        {
            if (max.size() >= 17)
            {
                std::cerr << "ERR : Data anomaly & Accuracy anomaly\n";
                return;
            }
            std::cout << std::fixed << std::setprecision(5) << return_Result << '\n';
        }
        std::cout << std::defaultfloat << std::setprecision(6);
        return;
    }

    inline void Statistics(const std::vector<long double>& Statistics_data)
    {
        if (Statistics_data.empty())
        {
            std::cerr << "ERR: Empty.\n";
            return;
        }
		long double total = std::accumulate(Statistics_data.begin(), Statistics_data.end(), 0.0L); //total
        long double average = static_cast<long double>(total) / Statistics_data.size();//average
        long double max = *std::max_element(Statistics_data.begin(), Statistics_data.end());   //max
        long double min = *std::min_element(Statistics_data.begin(), Statistics_data.end());  //mim

        std::cout << "\nTotal:   ";  
        if (!No_overflow(total)) { return; }
        std::cout << total << '\n';
        std::cout << "Max:     " << max << '\n';
        std::cout << "Min:     " << min << '\n';
        std::cout << "Range:   " << max - min << '\n';
        std::cout << "Average: " << average << '\n';
        //print
        std::vector <long double> one = Statistics_data;
        std::sort(one.begin(), one.end(), std::greater<long double>());
        //sort
        size_t n = one.size();
        if ((n % 2) == 0) { std::cout << "Median:  " << (static_cast<long double>(one[n / 2 - 1]) + static_cast<long double>(one[n / 2])) / 2.0L << '\n'; }
        else { std::cout << "Median:  " << one[n / 2] << '\n'; }
		long double variance = 0.0L;                   //variance
        for (const auto& var : one)
        {
            long double diff = static_cast <long double> (var) - average;
            variance += diff * diff;
        }
        std::cout << "Variance:";
        if (!No_overflow(variance))return;
        variance = variance / n;
        std::cout << variance << '\n';

        long double sqrt_r = std::sqrtl(variance);
        std::cout << "Std Dev: ";  
        if (!No_overflow(sqrt_r))return;
        std::cout << sqrt_r << '\n';
        std::unordered_map <long double, int> m;
        long double mode = 0.0L;
        int maxfreq = 0;
        for (auto val : one)
        {
            int freq = ++m[val];
            if (freq > maxfreq)
            {
                maxfreq = freq;
                mode = val;
            }
        }
        if (maxfreq <= 1) { std::cout << "Mode:   None (all values unique)\n"; }
        else { std::cout << "Mode:    " << mode << " ---- Max freq : " << maxfreq << '\n'; }
        std::cout << "Sorted as:\n";
        for (const auto& two : one) std::cout << two << '\n';
        std::cout << "Count:  " << Statistics_data.size() << '\n';
    }
}