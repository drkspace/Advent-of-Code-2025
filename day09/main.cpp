
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
    std::vector<Point2d<i64>> points;
    for (const auto& line: lines)
    {
        if (line.empty())
        {
            break;
        }
        auto parts = split(line, ',');
        points.emplace_back(std::stoll(parts.at(0)), std::stoll(parts.at(1)));
    }

    return points;
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
    {
        i64 area = 0;
        for (const auto& [i, v]: enumerate(inp))
        {
            for (const auto& v2: std::span{inp}.subspan(i+1))
            {
                const auto tmp = v-v2;
                const auto a = std::abs((tmp.x+1)*(tmp.y+1));
                if (a > area)
                {
                    area = a;
                }
            }
        }
        std::println("Part 1: {}", area);
    }
    {
        i64 area = 0;
        bool left_handed = false;
        // for (const auto& [i, v]: enumerate(inp))
        // {
        //     auto prev = i-1;
        //     if (prev < 0)
        //     {
        //         prev = inp.size()-1;
        //     }
        //     auto next = i+1;
        //     if (next >= inp.size())
        //     {
        //         next = 0;
        //     }
        //
        // }

        for (const auto& [i, v]: enumerate(inp))
        {
            Point2d<int> curl_dir1{0,0};
            auto prev = i-1;
            if (prev < 0)
            {
                prev = inp.size()-1;
            }
            auto next = i+1;
            if (next >= inp.size())
            {
                next = 0;
            }
            if (inp[prev].x==v.x && inp[next].y == v.y)
            {
                curl_dir1 = {-1,-1};
            }
            else if (inp[prev].y==v.y && inp[next].x == v.x)
            {
                curl_dir1 = {-1,-1};
            }
            else if (inp[prev].y==v.y && inp[next].x > v.x)
            {
                curl_dir1 = {-1,1};
            }
            else
            {
                curl_dir1 = {-1,-1};

            }
            for (const auto& [_i, v2]: enumerate(std::span{inp}.subspan(i+1)))
            {
                const auto j = i+_i;
                const auto tmp = v-v2;
                const auto a = std::abs((tmp.x+1)*(tmp.y+1));
                // if (a <= area)
                // {
                //     continue;
                // }

                const auto min_x = std::min(v.x, v2.x);
                const auto max_x = std::max(v.x, v2.x);
                const auto min_y = std::min(v.y, v2.y);
                const auto max_y = std::max(v.y, v2.y);
                bool bad = false;
                for (const auto& v3: inp)
                {

                    if (((min_x < v3.x && v3.x < max_x) && (min_y <= v3.y && v3.y <= max_y)) ||
                        ((min_x <= v3.x && v3.x <= max_x) && (min_y < v3.y && v3.y < max_y)))
                    {
                        bad = true;
                        break;
                    }

                }
                if (bad)
                {
                    continue;
                }
                std::println("{} {}", v, v2);
                area = a;
            }
        }
        std::println("Part 2: {}", area);
    }
    return 0;
}