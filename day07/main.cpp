
#include <print>
#include "../utils/utils.h"
#include "../utils/easyTimer.hpp"
#include <cstdio>
#include <cmath>
#include <numeric>
#include <unordered_map>

auto getInput(const std::string& fp)
{
    auto lines =read_file(fp);
    if (lines[lines.size()-1].empty())
    {
        lines.erase(lines.end());
    }
    return lines;
}

[[nodiscard]] u64 count_timelines(const std::vector<std::string>& grid,
                                  const int cur_line,
                                  const int cur_x,
                                  std::unordered_map<std::pair<int, int>, u64, hash_tuple>& cache)
{

    if (const auto& itr = cache.find({cur_line, cur_x}); itr != cache.end())
    {
        return itr->second;
    }

    const auto c = grid.at(cur_line).at(cur_x);
    u64 timelines = 0;
    if (c == '.')
    {
        if (cur_line+1 < static_cast<int>(grid.size()))
        {
            timelines = count_timelines(grid, cur_line+1, cur_x, cache);
        }
    }
    else if (c == '^')
    {
        const auto past_bottom = cur_line+1 >= static_cast<int>(grid.size());
        if (cur_x != 0)
        {
            timelines++;
            if (!past_bottom)
            {
                timelines += count_timelines(grid, cur_line+1, cur_x-1, cache);
            }
        }
        if (cur_x+1 < static_cast<int>(grid[cur_line].size()))
        {
            timelines++;
            if (!past_bottom)
            {
                timelines += count_timelines(grid, cur_line+1, cur_x+1, cache);
            }
        }
        timelines--;
    }
    cache[{cur_line, cur_x}] = timelines;
    return timelines;
}

int main(const int argc, char* argv[])
{
    easyTimer<std::chrono::milliseconds> _;
    if (!(argc == 2 || argc == 3))
    {
        std::println(stderr, "Invalid Args");
        return 1;
    }

    {
        auto inp = getInput(argv[1]);
        int nsplit = 0;
        for (auto [i, line]: enumerate(inp))
        {
            if (i==0)
            {
                continue;
            }
            for (auto [j,c]: enumerate(line))
            {
                if (inp[i-1][j] == 'S' || inp[i-1][j] == '|')
                {
                    if (c == '.')
                    {
                        line[j] = '|';
                    }
                    else if (c == '^')
                    {
                        nsplit++;
                        if (j!=0) line[j-1] = '|';
                        if (j<static_cast<long>(line.size()-1)) line[j+1] = '|';
                    }
                    else if (c == '|')
                    {
                        continue;
                    }
                    else
                    {
                        std::println("panic");
                    }
                }
            }
        }
        std::println("Part 1: {}", nsplit);
    }

    {
        auto inp = getInput(argv[1]);

        int s_col = 0;
        for (auto [i, c]: enumerate(inp[0]))
        {
            if (c=='S')
            {
                s_col = i;
                break;
            }
        }
        std::unordered_map<std::pair<int, int>, u64, hash_tuple> cache{};
        auto nsplit = 1+count_timelines(inp, 1, s_col, cache);
        std::println("Part 2: {}", nsplit);
    }
    return 0;
}