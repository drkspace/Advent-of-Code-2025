
#include <algorithm>
#include <print>
#include "../utils/utils.h"
#include "../utils/easyTimer.hpp"
#include <cstdio>
#include <cmath>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Core>

#include "../utils/point.h"

struct Machine
{
    int n_lights = 0;
    std::vector<int> needed_on;
    std::vector<std::vector<int>> buttons;
    std::vector<int> joltage;
};

auto getInput(const std::string& fp)
{
    const auto lines =read_file(fp);
    std::vector<Machine> machines;
    for (const auto& line: lines)
    {
        if (line.empty())
        {
            break;
        }
        Machine m;
        auto parts = split(line, ' ');
        m.n_lights = parts[0].size()-2;
        for (const auto& [i,c]: enumerate(parts[0]))
        {
            if (c=='#')
            {
                m.needed_on.emplace_back(i-1);
            }
        }
        for (auto& btn: std::span{parts}.subspan(1, parts.size()-2))
        {
            m.buttons.emplace_back();
            const auto tmp = std::span{btn}.subspan(1, btn.size()-1);
            auto btn_nums = split(std::string{tmp.data()}, ',');

            for (const auto& b: btn_nums)
            {
                m.buttons.back().emplace_back(std::stoi(b));
            }
        }
        const auto j_part = parts[parts.size()-1];
        const auto tmp = std::span{j_part}.subspan(1, j_part.size()-1);
        for (const auto& n: split(std::string{tmp.data()}, ','))
        {
            m.joltage.emplace_back(std::stoi(n));
        }
        machines.emplace_back(m);
    }

    return machines;
}

void helper(const Machine& m, const std::vector<bool>& on_state, const int level, int last_pressed, int& lowest)
{
    if (level >= lowest)
    {
        return;
    }
    for (const auto& [i, btn]: enumerate(m.buttons))
    {
        if (i == last_pressed)
        {
            continue;
        }
        auto state_cpy = on_state;
        for (const auto& b: btn)
        {
            state_cpy[b] = !state_cpy[b];
        }
        bool has_needed = true;
        for (const auto& needed: m.needed_on)
        {
            has_needed = has_needed && state_cpy[needed];
        }
        if (has_needed && std::accumulate(state_cpy.begin(), state_cpy.end(), 0) == static_cast<int>(m.needed_on.size()))
        {
            if (level < lowest)
            {
                lowest = level;
            }
        }
        else
        {
            helper(m, state_cpy, level+1, i, lowest);
        }
    }
}

[[nodiscard]] int run(const Machine& m)
{
    int lowest = 2*m.buttons.size();
    helper(m, std::vector<bool>(m.n_lights), 1, -1, lowest);
    return lowest;
}

int run2(const Machine& m)
{
    const int M = m.buttons.size()+1;
    const int N = m.joltage.size();

    std::vector<std::vector<float>> mat;
    for (int i = 0; i< N; i++)
    {
        mat.emplace_back(M);
        std::ranges::fill(mat.at(i), 0);
    }

    for (auto [i, row]: enumerate(mat))
    {
        row.at(M-1) = m.joltage[i];
        for (const auto [j, b]: enumerate(m.buttons))
        {
            if (std::ranges::contains(b, i))
            {
                row.at(j) = 1;
            }
        }
    }
    print_arr(mat);
    // RowReduce(mat);

    return 0;
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
    //     int sum = 0;
    //     for (const auto& [i,m]: enumerate(inp))
    //     {
    //         sum += run(m);
    //     }
    //     std::println("Part 1: {}", sum);
    // }
    {
        int sum = 0;
        for (const auto& [i,m]: enumerate(inp))
        {
            run2(m);
            // const auto tmp = run2(m);
            // std::println("{} {}", i, tmp);
            // sum += tmp;
            break;;
        }
        std::println("Part 2: {}", sum);
    }
    return 0;
}