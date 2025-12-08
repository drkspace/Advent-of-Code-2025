
#include <algorithm>
#include <print>
#include "../utils/utils.h"
#include "../utils/easyTimer.hpp"
#include <cstdio>
#include <cmath>
#include <numeric>
#include <unordered_map>
#include "../utils/point.h"

using i64 = std::int64_t;

auto getInput(const std::string& fp)
{
    auto lines =read_file(fp);
    std::vector<Point3d<i64>> points;
    for (const auto& line: lines)
    {
        if (line.empty())
        {
            break;
        }
        // std::println("{}", line);
        auto parts = split(line, ',');
        points.emplace_back(std::stoll(parts.at(0)), std::stoll(parts.at(1)), std::stoll(parts.at(2)));
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
    auto inp = getInput(argv[1]);

    {
        std::unordered_map<int, int> idx_to_cn;
        std::unordered_map<int, i64> cn_count;
        int cn = 0;
        std::vector<std::tuple<i64, int, int>> distances;
        // print_arr(inp);
        for (const auto [i, p1]: enumerate(inp))
        {
            for (const auto [j, p2]: enumerate(inp))
            {
                if (j <= i)
                {
                    continue;
                }
                distances.emplace_back((p1-p2).radicand(), i, j);
            }
        }
        std::ranges::sort(distances);
        int n_pairs = 0;
        // constexpr int max_pairs = 500-1;
        for (const auto&[i, parts]: enumerate(distances))
        {
            if (i >= 1000)
            {
                break;
            }
            const auto& [dist, i1, i2] = parts;
            // if (n_pairs >= max_pairs)
            // {
            //     continue;
            // }
            if (idx_to_cn.contains(i1) && idx_to_cn.contains(i2) && idx_to_cn[i1] == idx_to_cn[i2])
            {
                continue;
            }
            if (idx_to_cn.contains(i1) && idx_to_cn.contains(i2))
            {

                // Move all of i2's circuit to i1
                const auto i2_cn = idx_to_cn[i2];
                const auto i1_cn = idx_to_cn[i1];
                cn_count[i1_cn] += cn_count[i2_cn];
                cn_count.erase(idx_to_cn[i2]);

                for (const auto& [j, cn]: idx_to_cn)
                {
                    if (cn == i2_cn)
                    {
                        idx_to_cn[j] = i1_cn;
                    }
                }
                n_pairs++;
            }
            else if (idx_to_cn.contains(i1))
            {
                idx_to_cn[i2] = idx_to_cn[i1];
                cn_count[idx_to_cn[i1]]++;
                n_pairs++;
            }
            else if (idx_to_cn.contains(i2))
            {
                idx_to_cn[i1] = idx_to_cn[i2];
                cn_count[idx_to_cn[i1]]++;
                n_pairs++;
            }
            else
            {
                cn++;
                idx_to_cn[i1] = idx_to_cn[i2] = cn;
                cn_count[cn] = 2;
                n_pairs++;
            }
        }

        i64 prod = 1;
        const auto tmp = cn_count | std::views::values;
        std::vector<i64> vals{tmp.begin(), tmp.end()};
        std::ranges::sort(vals, std::greater<i64>{});
        for (const auto [i, v] : enumerate(vals))
        {
            if (i == 3)
            {
                break;
            }
            std::println("{}", v);
            prod *= v;
        }
        std::println("Part 1: {}", prod);
    }

        {
        std::unordered_map<int, int> idx_to_cn;
        std::unordered_map<int, i64> cn_count;
        int cn = 0;
        std::vector<std::tuple<i64, int, int>> distances;

        for (const auto [i, p1]: enumerate(inp))
        {
            for (const auto [j, p2]: enumerate(inp))
            {
                if (j <= i)
                {
                    continue;
                }
                distances.emplace_back((p1-p2).radicand(), i, j);
            }
        }
        std::ranges::sort(distances);
        int n_pairs = 0;
        for (const auto&[dist, i1, i2]: distances)
        {
            if (idx_to_cn.contains(i1) && idx_to_cn.contains(i2) && idx_to_cn[i1] == idx_to_cn[i2])
            {
                continue;
            }
            if (idx_to_cn.contains(i1) && idx_to_cn.contains(i2))
            {

                // Move all of i2's circuit to i1
                const auto i2_cn = idx_to_cn[i2];
                const auto i1_cn = idx_to_cn[i1];
                cn_count[i1_cn] += cn_count[i2_cn];
                cn_count.erase(idx_to_cn[i2]);

                for (const auto& [j, cn]: idx_to_cn)
                {
                    if (cn == i2_cn)
                    {
                        idx_to_cn[j] = i1_cn;
                    }
                }
                n_pairs++;
            }
            else if (idx_to_cn.contains(i1))
            {
                idx_to_cn[i2] = idx_to_cn[i1];
                cn_count[idx_to_cn[i1]]++;
                n_pairs++;
            }
            else if (idx_to_cn.contains(i2))
            {
                idx_to_cn[i1] = idx_to_cn[i2];
                cn_count[idx_to_cn[i1]]++;
                n_pairs++;
            }
            else
            {
                cn++;
                idx_to_cn[i1] = idx_to_cn[i2] = cn;
                cn_count[cn] = 2;
                n_pairs++;
            }
            if (cn_count.size() == 1 && cn_count.begin()->second == static_cast<int>(inp.size()))
            {
                std::println("Part 2: {}", inp[i1].x * inp[i2].x);

                break;
            }
        }
    }
    return 0;
}