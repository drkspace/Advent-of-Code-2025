
#include <algorithm>
#include <print>
#include "../utils/utils.h"
#include "../utils/easyTimer.hpp"
#include <cstdio>
#include <cmath>
#include <numeric>
#include <unordered_map>
#include <unordered_set>


auto getInput(const std::string& fp)
{
    const auto lines = read_file(fp);
    std::unordered_map<int, std::string> shapes;
    std::vector<std::tuple<int, int, std::vector<int>>> regions;
    for (auto itr = lines.begin(); itr != lines.end(); ++itr)
    {
        const auto& line = *itr;
        if (itr->empty())
        {
            continue;
        }
        if ((itr+1)->contains('.') || (itr+1)->contains('#'))
        {
            auto parts = split(line, ':');
            const auto idx = std::stoi(parts[0]);
            const auto shape = *(itr+1)+"\n"+*(itr+2)+"\n"+*(itr+3);
            shapes[idx] = shape;
            itr += 3;
        }
        else
        {
            auto parts = split(line, ':');
            auto dims = split(parts.at(0), 'x');
            auto req_s = split(parts.at(1), ' ', true);
            std::vector<int> req(req_s.size());
            for (const auto [i, v]: enumerate(req_s))
            {
                req[i] = std::stoi(v);
            }
            regions.emplace_back(std::stoi(dims.at(0)), std::stoi(dims.at(1)), req);
        }
    }

    return std::make_tuple(shapes, regions);
}

int main(const int argc, char* argv[])
{
    easyTimer<std::chrono::milliseconds> _;
    if (!(argc == 2 || argc == 3))
    {
        std::println(stderr, "Invalid Args");
        return 1;
    }
    const auto [shapes, regions] = getInput(argv[1]);

    int c= 0;
    for (const auto& [h, w, need]: regions)
    {
        c += h*w>= 9*std::accumulate(need.begin(), need.end(), 0);
    }
    std::println("Part 1: {}", c);
    return 0;
}