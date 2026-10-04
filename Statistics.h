#pragma once

#include "math.h"

namespace math
{
	static long double return_Result(const long double& result)
	{
        long double abs_val = fabsl(result);
        if(!math::No_overflow(abs_val))
        {
            return 0.0L;
        }
        if (abs_val >= 1e16 || (abs_val > 0 && abs_val < 1e-5))
        { std::cout << std::scientific   << std::setprecision(5) << result << '\n'; }
        else
        { std::cout << std::defaultfloat << std::setprecision(6) << result << '\n'; }
        return result;
    }

    inline void Statistics(const std::vector<long double>& Statistics_data)
    {
        if (Statistics_data.empty())
        {
            std::cerr << "ERR: Empty.\n";
            return;
        }
        long double total   = std::accumulate(Statistics_data.begin(), Statistics_data.end(), 0.0L); //total
        long double average = static_cast<long double>(total) / Statistics_data.size();//average
        long double max     = *std::max_element(Statistics_data.begin(), Statistics_data.end());   //max
        long double min     = *std::min_element(Statistics_data.begin(), Statistics_data.end());  //min
		long double range   = max - min; //range
        std::cout << "\nTotal:   ";
        if (!No_overflow(total)) { return; }
		return_Result(total);
		std::cout << "Max:     ";return_Result(max);
		std::cout << "Min:     ";return_Result(min);
		std::cout << "Range:   ";return_Result(range);
		std::cout << "Average: ";return_Result(average);
        //print
        std::vector <long double> one = Statistics_data;
        std::sort(one.begin(), one.end(), std::greater<long double>());
        //sort

        size_t n = one.size();
        if ((n % 2) == 0) { std::cout << "Median:  ";return_Result((static_cast<long double>(one[n / 2 - 1]) + static_cast<long double>(one[n / 2])) / 2.0L); }
        else {     std::cout << "Median:  ";return_Result(one[n / 2]); }
        long double variance = 0.0L;                   //variance
        for (const auto& var : one)
        {
            long double diff = static_cast <long double> (var) - average;
            variance        += diff * diff;
        }
        std::cout << "Variance:";
        if (!No_overflow(variance))return;
        variance = variance / n;
		return_Result(variance);

        long double sqrt_r = std::sqrtl(variance);
        std::cout << "Std Dev: ";
        if (!No_overflow(sqrt_r))return;
		return_Result(sqrt_r);
        std::unordered_map <long double, int> m;
        long double mode = 0.0L;
        int maxfreq = 0;
        for (auto val : one)
        {
            int freq = ++m[val];
            if (freq > maxfreq)
            {
                maxfreq = freq;
                mode    = val;
            }
        }
        if (maxfreq <= 1) {    std::cout <<  "Mode:   None (all values unique)\n"; }
        else {
			std::cout << "Mode:    ";
            return_Result(mode);
        std::cout << "                        ---- Max freq : " << maxfreq << '\n';
        }
        std::cout << "\nSorted as:\n";
        for (const auto& two : one)
        {
            return_Result(two);
         
        }
        std::cout    << "\nCount:  ";
        return_Result(Statistics_data.size());
    }
}