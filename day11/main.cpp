
#include <algorithm>
#include <print>
#include "../utils/utils.h"
#include "../utils/easyTimer.hpp"
#include <cstdio>
#include <cmath>
#include <numeric>
#include <unordered_map>
#include <unordered_set>

#include "../utils/point.h"


auto getInput(const std::string& fp)
{
    const auto lines =read_file(fp);
    std::unordered_map<std::string, std::vector<std::string>> paths;
    for (const auto& line: lines)
    {
        if (line.empty())
        {
            break;
        }
        const auto parts = split(line, ':');
        const auto key = parts.at(0);
        for (const auto& outputs: split(parts.at(1), ' ', true))
        {
            paths[key].emplace_back(outputs);
        }
    }

    return paths;
}

[[nodiscard]] int helper(const std::unordered_map<std::string, std::vector<std::string>>& paths, const std::string& cur, int depth)
{
    if (cur == "out")
    {
        return 1;
    }
    if (!paths.contains(cur))
    {
        return 0;
    }
    int count = 0;
    for (const auto& next: paths.at(cur))
    {
        count += helper(paths, next, depth+1);
    }
    return count;
}

[[nodiscard]] int count_paths(const std::unordered_map<std::string, std::vector<std::string>>& paths)
{
    int count = 0;
    for (const auto& next: paths.at("you"))
    {
        count += helper(paths, next, 1);
    }
    return count;
}

[[nodiscard]] int helper2(const std::unordered_map<std::string, std::vector<std::string>>& paths, const std::string& cur, bool found_dac, bool found_fft)
{

    if (cur == "out")
    {
        return found_dac && found_fft;
    }
    if (!paths.contains(cur))
    {
        return 0;
    }

    if (!found_dac && cur == "dac")
    {
        found_dac = true;
    }
    if (!found_fft && cur == "fft")
    {
        found_fft = true;
    }

    int count = 0;
    for (const auto& next: paths.at(cur))
    {
        count += helper2(paths, next, found_dac, found_fft);
    }
    return count;
}

[[nodiscard]] int count_paths2(const std::unordered_map<std::string, std::vector<std::string>>& paths)
{
    int count = 0;
    std::unordered_map<std::string, int> cache{};
    for (const auto& next: paths.at("svr"))
    {
        count += helper2(paths, next, false, false);
        std::println("{}", count);
    }
    return count;
}

int main(const int argc, char* argv[])
{
    easyTimer<std::chrono::milliseconds> _;
    if (!(argc == 2 || argc == 3))
    {
        std::println(stderr, "Invalid Args");
        return 1;
    }
    const auto inp = getInput(argv[1]);


    // {
    //     auto npaths = count_paths(inp);
    //     std::println("Part 1: {}", npaths);
    // }

    {
        auto npaths = count_paths2(inp);
        std::println("Part 2: {}", npaths);
    }
    return 0;
}