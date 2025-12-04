
#include <print>
#include "../utils/utils.h"
#include "../utils/easyTimer.hpp"
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

[[nodiscard]] constexpr auto find_max(const auto& bank, const size_t battery_size)
{
    const auto len = bank.size();
    dt building = 0;

    // This will wrap to the max size_t value, but I will add 1 to it,
    // Which will overflow it back to 0
    size_t max_idx = -1;
    for (size_t i = 1; i<=battery_size; i++)
    {
        dt max = 0;
        for (size_t j = max_idx+1; j < len-battery_size+i; j++)
        {
            if (bank.at(j) > max)
            {
                max = bank[j];
                max_idx = j;
            }
        }
        building = building*10 + max;
    }
    return building;
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
        easyTimer<std::chrono::milliseconds> _;
        dt sum = 0;
        for (const auto& bank: inp)
        {
            sum += find_max(bank, 2);
        }
        std::println("Part 1: {}", sum);
    }

    {
        easyTimer<std::chrono::milliseconds> _;
        dt sum = 0;
        for (const auto& bank: inp)
        {
            sum += find_max(bank, 12);
        }

        std::println("Part 2: {}", sum);
    }

    return 0;
}