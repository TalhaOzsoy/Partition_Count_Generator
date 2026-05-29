#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
 
std::vector<int> getDivisors(int n) 
{
    std::vector<int> divs;
    for (int i = 1; i * i <= n; i++) 
    {
        if (n % i == 0) 
        {
            divs.push_back(i);
            if (i != n / i) divs.push_back(n / i);
        }
    }
    std::sort(divs.begin(), divs.end());
    return divs;
}
 
long long countPartitions(int target, const std::vector<int>& parts) 
{
    std::vector<long long> dp(static_cast<size_t>(target) + 1, 0LL);
    dp[0] = 1;
    for (int p : parts) 
    {
        for (int i = p; i <= target; i++) 
            dp[static_cast<size_t>(i)] += dp[static_cast<size_t>(i - p)];
        
    }
    return dp[static_cast<size_t>(target)];
}
 
long long f(int n) 
{
    std::vector<int> divs = getDivisors(n);
    long long total = countPartitions(n, divs);
    std::vector<int> divsNo1(divs.begin() + 1, divs.end()); // skip 1
    long long without1 = countPartitions(n, divsNo1);
    return total - without1;
}
 
// Generate f(1), f(2), ..., f(n)
void generateUpTo(int n) 
{
    for (int i = 1; i <= n; i++) 
        std::cout << f(i) << "\n";

}
 
// Compute f for a specific set of values
void computeSpecific(const std::vector<int>& values) 
{
    for (int v : values) 
    {
        if (v < 1) 
        {
            std::cerr << "Skipping invalid value: " << v << "\n";
            continue;
        }
        std::cout << "f(" << v << ") = " << f(v) << "\n";
    }
}
 
void printUsage(const char* prog) {
    std::cerr << "Usage:\n";
    std::cerr << "  " << prog << " -n <limit>          Generate f(1) through f(limit)\n";
    std::cerr << "  " << prog << " -v <v1> <v2> ...    Compute f for specific values\n";
}
 
int main(int argc, char* argv[]) 
{
    if (argc < 3) 
    {
        printUsage(argv[0]);
        return 1;
    }
 
    std::string mode = argv[1];
 
    if (mode == "-n") 
    {
        int limit = std::stoi(argv[2]);
        if (limit < 1) { std::cerr << "limit must be >= 1\n"; return 1; }
        generateUpTo(limit);
    } 
    else if (mode == "-v") 
    {
        std::vector<int> values;
        for (int i = 2; i < argc; i++) {
            values.push_back(std::stoi(argv[i]));
        }
        computeSpecific(values);
    } 
    else 
    {
        printUsage(argv[0]);
        return 1;
    }
 
    return 0;
}