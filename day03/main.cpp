
#include <print>
#include "../utils/utils.h"
#include <cstdio>
#include <cmath>

using dt = std::uint64_t;
auto getInput(const std::string& fp)
{
    const auto lines = read_file(fp);
    std::vector<std::vector<dt>> out;

    for (const auto& line: lines)
    {
        if (line.empty())
        {
            break;
        }
        out.emplace_back();
        for (const auto& c: line)
        {
            out.back().emplace_back(std::stoll(std::string({c})));
        }
    }

    return out;
}

int main(const int argc, char* argv[])
{
    if (!(argc == 2 || argc == 3))
    {
        std::println(stderr, "Invalid Args");
        return 1;
    }
    const auto inp = getInput(argv[1]);

    {
        dt sum = 0;
        for (const auto& bank: inp)
        {
            dt max = 0;
            dt max1 = 0;
            for (size_t i = 0; i< bank.size(); i++)
            {
                const auto tmp = bank[i]*10;
                if (tmp < max1)
                {
                    continue;
                }
                for (size_t j = i+1; j<bank.size(); j++)
                {
                    if (const auto tmp2 = tmp+bank[j]; tmp2 > max)
                    {
                        max = tmp2;
                        max1 = tmp;
                    }
                }
            }

            sum += max;
        }
        std::println("Part 1: {}", sum);
    }

    {

        dt sum = 0;
        for (const auto& bank: inp)
        {
            const auto len = bank.size();
            dt building = 0;

            // This will wrap to the max size_t value, but I will add 1 to it,
            // Which will overflow it back to 0
            size_t max_idx = -1;
            for (size_t i = 1; i<=12; i++)
            {
                dt max = 0;
                for (size_t j = max_idx+1; j < len-12+i; j++)
                {
                    if (bank.at(j) > max)
                    {
                        max = bank[j];
                        max_idx = j;
                    }
                }
                building = building*10 + max;
            }
            sum += building;
        }

        std::println("Part 2: {}", sum);
    }

    return 0;
}