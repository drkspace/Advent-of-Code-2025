
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

struct RT{
    int need_neither = 0;
    int need_dac = 0;
    int need_fft = 0;
    int need_both = 0;
};

using CacheType = std::unordered_map<std::string, RT>;

[[nodiscard]] RT helper2(const std::unordered_map<std::string, std::vector<std::string>>& paths, const std::string& cur, CacheType& cache, int level)
{
    if(const auto& itr = cache.find(cur); itr != cache.end())
    {
        return itr->second;
    }
    // Prevents loops
    cache[cur] = {};
    if (cur == "out")
    {
        return RT(0, 0, 0, 1);
    }
    if (!paths.contains(cur))
    {
        return {};
    }

    const bool is_dac = cur == "dac";
    const bool is_fft = cur == "fft";

    RT children(0,0,0,0);
    for (const auto& next: paths.at(cur))
    {
        const auto& [c, nd, nf, nb] = helper2(paths, next, cache, level+1);

        children.need_neither += c;
        children.need_dac += nd;
        children.need_fft += nf;
        children.need_both += nb;
    }

    if(is_dac){
        children.need_neither += children.need_dac;
        children.need_dac = 0;
        children.need_fft += children.need_both;
        children.need_both = 0;
    }
    if(is_fft){
        children.need_neither += children.need_fft;
        children.need_fft = 0;
        children.need_dac += children.need_both;
        children.need_both = 0;
    }

    cache[cur] = children;
    // std::println("{}: {}", level, children.need_neither);
    return children;
}

[[nodiscard]] int count_paths2(const std::unordered_map<std::string, std::vector<std::string>>& paths)
{
    int count = 0;
    std::unordered_map<std::string, int> cache{};
    for (const auto& next: paths.at("svr"))
    {
        CacheType cache{};
        const auto& res = helper2(paths, next, cache, 1);
        count += res.need_neither;
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