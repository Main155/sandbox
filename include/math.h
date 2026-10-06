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

    static std::vector<std::string> g_tokens;
    static size_t g_pos = 0;
    static long double expr();
    static void tokenize(const std::string& s) 
    {
        g_tokens.clear();
        std::string cur;
        for (char c : s) 
        {
            if (c == ' ') { if (!cur.empty()) { g_tokens.push_back(cur); cur.clear(); } }
            else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')')
            {
                if (!cur.empty()) { g_tokens.push_back(cur); cur.clear(); }
                g_tokens.push_back(std::string(1, c));
            }
            else cur += c;
        }
        if (!cur.empty()) g_tokens.push_back(cur);
    }

    static bool has_next() { return g_pos < g_tokens.size(); }
    static std::string peek() { return has_next() ? g_tokens[g_pos] : ""; }
    static void advance() { if (has_next()) ++g_pos; }

    static long double factor() 
    {
        std::string tok = peek();

        if (tok == "r")  {                  //root operation
            advance();  
            if (peek() != "(") {
                std::cerr << "ERR: expected '(' after 'r'\n";
                return 0;
            }       
            advance();  
            long double val = expr();  
            if (peek() != ")") {
                std::cerr << "ERR: missing ')' in r()\n";
                return 0;
            }
            advance(); 

            if (val < 0) {
                std::cerr << "ERR: sqrt of negative number\n";
                return 0;
            }
            if (!No_overflow(val)) return 0; //overfiow
            return sqrtl(val);
        }

        if (tok == "(")
        {
            advance();                    
            long double val = expr();
            if (peek() == ")") advance(); 
            else { std::cerr << "ERR: missing ')'\n"; return 0; }
            return val;
        }

        if (tok == "-"){ advance(); return -factor(); }

        if (tok == "+"){ advance(); return factor(); }

        advance();
        try { return std::stold(tok); }
        catch (...) { std::cerr << "ERR: bad number '" << tok << "'\n"; return 0; }
    }

    static long double power()
    {
        long double left = factor();
        if (peek() == "^") 
        {
            advance();
            long double right = power();  
            return powl(left, right);
        }
        if (!No_overflow(left)) return 0;
        return left;
    }

    
    static long double term() 
    {
        long double left = power();
        while (has_next()) 
        {
            std::string op = peek();

            if (op == "(" || (op != "*" && op != "/" && op != "+" && op != "-" && op != ")"))
            {
                 //implicit multiplication
                long double right = factor();
                left *= right;
                continue;
            }

            if (op != "*" && op != "/") break;
            advance();
            long double right = power();
            if (op == "*") left *= right;
            else { if (right == 0) { std::cerr << "ERR: /0\n"; return 0; } left /= right; }
        }
        if (!No_overflow(left)) return 0;
        return left;
    }


    static long double expr() 
    {
        long double left = term();
        while (has_next()) 
        {
            std::string op = peek();
            if (op != "+" && op != "-") break;
            advance();
            long double right = term();
            if (op == "+") left += right;
            else left -= right;
        }
        if (!No_overflow(left)) return 0;
        return left;
    }

    inline void Process(const std::string& write_) 
    {
        if (write_.empty()) { std::cerr << "ERR: empty\n"; return; }
        tokenize(write_);
        g_pos = 0;
        long double result = expr();
        if (!No_overflow(result)) return;
        if (g_pos < g_tokens.size()) 
        {
            std::cerr << "ERR: extra token  '" << g_tokens[g_pos] << "'  \n";
            return;
        }
        std::cout << "\n----------Result\n";
        std::cout << "Scientific notation:" << result<<'\n';
        std::string max = std::to_string(result);
        std::cout << "Normal display:     ";
        if (result == static_cast<long long>(result))
        {
            if (max.size() >= 25)
            {
                std::cerr << "ERR : Data anomaly & Accuracy anomaly\n";
                return;
            }
            std::cout << std::fixed << std::setprecision(0) << result << '\n';
        }
        else
        {
            if (max.size() >= 17)
            {
                std::cerr << "ERR : Data anomaly & Accuracy anomaly\n";
                return;
            }
            std::cout << std::fixed << std::setprecision(result == static_cast<long long>(result) ? 0 : 5) << result << '\n';
        }
        std::cout << std::defaultfloat;
    }
}
