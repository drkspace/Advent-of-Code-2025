
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
            i++;
        }
        else{
            available_ingredients.emplace_back(std::stoull(line));
        }

    }

    std::sort(fresh_ingredients_min.begin(), fresh_ingredients_min.end());
    std::sort(fresh_ingredients_max.begin(), fresh_ingredients_max.end());

    return std::make_tuple(fresh_ingredients_min, fresh_ingredients_max, available_ingredients);

}

int main(const int argc, char* argv[])
{
    easyTimer<std::chrono::milliseconds> _;
    if (!(argc == 2 || argc == 3))
    {
        std::println(stderr, "Invalid Args");
        return 1;
    }
    const auto& [fresh_min, fresh_max, avail] = getInput(argv[1]);

    {
        std::vector<u64> fmin_ni;
        for(const auto& [ele, i]: fresh_min){
            fmin_ni.emplace_back(ele);
        }
        std::vector<u64> fmax_ni;
        for(const auto& [ele, i]: fresh_max){
            fmax_ni.emplace_back(ele);
        }
        size_t n_fresh = 0;
        for(const auto ele: avail){

            const auto ub = std::upper_bound(fmin_ni.begin(), fmin_ni.end(), ele);
            const auto min_d = std::distance(fmin_ni.begin(), ub);
            if (min_d == 0){
                continue;
            }
            const auto lb = std::lower_bound(fmax_ni.begin(), fmax_ni.end(), ele);
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
        std::vector<u64> fmin_ni;
        for(const auto& [ele, i]: fresh_min){
            fmin_ni.emplace_back(ele);
        }
        std::vector<u64> fmax_ni;
        for(const auto& [ele, i]: fresh_max){
            fmax_ni.emplace_back(ele);
        }
        size_t n_fresh = 0;
        std::println("Part 2: {}", n_fresh);
    }

    return 0;
}