
#include <print>
#include "../utils/utils.h"
#include "../utils/easyTimer.hpp"
#include <cstdio>
#include <cmath>
#include <ranges>
#include <algorithm>

auto getInput(const std::string& fp)
{
    const auto lines = read_file(fp);

    std::vector<std::pair<u64, size_t>> fresh_ingredients_min;
    std::vector<std::pair<u64, size_t>> fresh_ingredients_max;
    std::vector<std::pair<u64, u64>> fresh_ingredients;
    std::vector<u64> available_ingredients;
    bool first = true;
    size_t i = 0;
    for(const auto& line: lines)
    {
        if(line.empty()){
            first = false;
            continue;
        }
        if(first){
            const auto parts = split(line, '-');
            const u64 a = std::stoull(parts.at(0));
            const u64 b = std::stoull(parts.at(1));
            fresh_ingredients_min.emplace_back(a, i);
            fresh_ingredients_max.emplace_back(b, i);
            fresh_ingredients.emplace_back(a,b);
            i++;
        }
        else{
            available_ingredients.emplace_back(std::stoull(line));
        }

    }

    std::ranges::sort(fresh_ingredients_min);
    std::ranges::sort(fresh_ingredients_max);
    std::ranges::sort(fresh_ingredients);

    return std::make_tuple(fresh_ingredients, fresh_ingredients_min, fresh_ingredients_max, available_ingredients);

}

int main(const int argc, char* argv[])
{
    easyTimer<std::chrono::milliseconds> _;
    if (!(argc == 2 || argc == 3))
    {
        std::println(stderr, "Invalid Args");
        return 1;
    }
    auto [fresh_ingredients, fresh_min, fresh_max, avail] = getInput(argv[1]);

    {
        std::vector<u64> fmin_ni;
        for(const auto& ele : fresh_min | std::views::keys){
            fmin_ni.emplace_back(ele);
        }
        std::vector<u64> fmax_ni;
        for(const auto& ele : fresh_max | std::views::keys){
            fmax_ni.emplace_back(ele);
        }
        size_t n_fresh = 0;
        for(const auto ele: avail){

            const auto ub = std::ranges::upper_bound(fmin_ni, ele);
            const auto min_d = std::distance(fmin_ni.begin(), ub);
            if (min_d == 0){
                continue;
            }
            const auto lb = std::ranges::lower_bound(fmax_ni, ele);
            const auto max_d = std::distance(fmax_ni.begin(), lb);


            for(const auto& [v, i]: std::span(fresh_min.begin(), min_d)){
                bool to_break = false;
                for(const auto& [v2, j]: std::span(fresh_max.begin()+max_d, fresh_max.end())){
                    if(i==j){
                        n_fresh++;
                        to_break = true;
                        break;
                    }
                }
                if(to_break){
                    break;
                }

            }

        }
        std::println("Part 1: {}", n_fresh);
    }

    {
        size_t i = 0;
        u64 count = 0;
        while (i < fresh_ingredients.size())
        {
            auto [a,b] = fresh_ingredients[i];
            std::vector<size_t> to_drop;
            for (size_t j = i+1; j<fresh_ingredients.size(); j++)
            {
                if (auto [a2, b2] = fresh_ingredients[j]; a <= a2 && a2<= b)
                {
                    b = std::max(b, b2);
                    to_drop.emplace_back(j);
                }
            }
            for (const auto j: to_drop | std::views::reverse)
            {
                fresh_ingredients.erase(fresh_ingredients.begin()+j);
            }
            i++;
            count += b-a+1;
        }
        std::println("Part 2: {}", count);
    }

    return 0;
}