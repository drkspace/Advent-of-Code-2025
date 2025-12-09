
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

        std::vector<Point2d<i64>> dirs;

        int prev_dir = 1;
        for (const auto& [i, v]: enumerate(inp))
        {
            auto prev = i-1;
            if (prev < 0)
            {
                prev = inp.size()-1;
            }
            auto next = i+1;
            if (next >= static_cast<int>(inp.size()))
            {
                next = 0;
            }

            const auto& prev_corner = inp[prev];
            const auto& next_corner = inp[next];

            if(prev_corner.x == v.x){
                if(next_corner.x > v.x){
                    dirs.emplace_back(prev_dir, 1);
                    prev_dir = 1;
                }
                else{
                    dirs.emplace_back(prev_dir, -1);
                    prev_dir = -1;
                }
            }
            else{
                if(next_corner.y > v.y){
                    dirs.emplace_back(-1, prev_dir);
                    prev_dir = -1;
                }
                else{
                    dirs.emplace_back(1, prev_dir);
                    prev_dir = 1;
                }
            }
        }

        for (const auto& [i, z]: enumerate(std::ranges::views::zip(inp, dirs)))
        {
            const auto& [v, dir] = z;
            std::println("{} {}", v, dir);
        }
        // return 0;
        std::println("\n\n");

        for (const auto& [i, z]: enumerate(std::ranges::views::zip(inp, dirs)))
        {
            const auto& [v, dir] = z;


            for (const auto& [_i, v2]: enumerate(std::span{inp}.subspan(i+1)))
            {
                const auto j = i+_i+1;

                const auto& dir2 = dirs[j];

                const auto tmp = v-v2;

                const auto sign = tmp.sign();
                // std::println("{} {} {} {}", v, v2, sign, sign*-1);
                // std::println("{} {} {} {}", dir, dir2, dir2==sign, dir2==sign*-1);
                if(!(dir == sign || dir2 == sign || dir == sign*-1 || dir2 == sign*-1)){
                    continue;
                }

                const auto a = std::abs((tmp.x+1)*(tmp.y+1));

                // std::println("{} {}", v, v2);

                const auto min_x = std::min(v.x, v2.x);
                const auto max_x = std::max(v.x, v2.x);
                const auto min_y = std::min(v.y, v2.y);
                const auto max_y = std::max(v.y, v2.y);
                bool bad = false;
                for (const auto [k, v3]: enumerate(inp))
                {

                    auto prev = k-1;
                    if (prev < 0)
                    {
                        prev = inp.size()-1;
                    }
                    auto next = k+1;
                    if (next >= static_cast<int>(inp.size()))
                    {
                        next = 0;
                    }

                    const auto& prev_corner = inp[prev];
                    const auto& next_corner = inp[next];


                    if(v3 == v || v3 == v2){
                        continue;
                    }
                    // if (((min_x < v3.x && v3.x < max_x) && (min_y <= v3.y && v3.y <= max_y)) ||
                    //     ((min_x <= v3.x && v3.x <= max_x) && (min_y < v3.y && v3.y < max_y)))
                    if((min_x < v3.x && v3.x < max_x) && (min_y < v3.y && v3.y < max_y))
                    {
                        bad = true;
                        break;
                    }

                    if((min_x == v3.x || max_x == v3.x) && (max_y > v3.y && min_y < v3.y)){
                        // On a vertical edge of the rectangle

                        if(prev_corner.x == v3.x){
                            if(v3.x == min_x && (next_corner.x > v3.x)){
                                bad = true;
                                break;
                            }
                            else if(v3.x == max_x && (next_corner.x < v3.x)){
                                bad = true;
                                break;
                            }
                        }
                        else if(next_corner.x == v3.x){
                            if(v3.x == min_x && (prev_corner.x > v3.x)){
                                bad = true;
                                break;
                            }
                            else if(v3.x == max_x && (prev_corner.x < v3.x)){
                                bad = true;
                                break;
                            }
                        }

                        bad = true;
                        break;
                    }
                    if((min_y == v3.y || max_y == v3.y) && (max_x > v3.x && min_x < v3.x)){
                        // On a horizontal edge of the rectangle
                        if(prev_corner.y == v3.y){
                            if(v3.y == min_y && (next_corner.y > v3.y)){
                                bad = true;
                                break;
                            }
                            else if(v3.y == max_y && (next_corner.y < v3.y)){
                                bad = true;
                                break;
                            }
                        }
                        else if(next_corner.y == v3.y){
                            if(v3.y == min_y && (prev_corner.y > v3.y)){
                                bad = true;
                                break;
                            }
                            else if(v3.y == max_y && (prev_corner.y < v3.y)){
                                bad = true;
                                break;
                            }
                        }

                    }


                }
                if (bad)
                {
                    continue;
                }
                if (a > area)
                {
                std::println("{} {} {}", v, v2, a);
                    area = a;
                }
            }
        }
        // != 4633585821
        // != 4518297360
        // != 4509636086
        // != 4508133502
        
        std::println("Part 2: {}", area);
    }
    return 0;
}