
#include <print>
#include "../utils/utils.h"
#include "../utils/easyTimer.hpp"
#include <cstdio>
#include <cmath>

auto getInput(const std::string& fp)
{
    const auto lines = read_file(fp);
    std::vector<std::vector<u64>> nums(split(lines.at(0), ' ', true).size());
    std::vector<char> ops;
    for (const auto& line: lines)
    {
        for (const auto& [i,num]: enumerate(split(line, ' ', true)))
        {
            if (num == "*" || num == "+")
            {
                ops.emplace_back(num[0]);
            }
            else
            {
                nums[i].emplace_back(std::stoull(num));
            }
        }
    }
    return std::make_tuple(nums, ops);

}

auto getInput2(const std::string& fp)
{
    const auto lines = read_file(fp);
    std::vector<char> ops;
    std::vector<size_t> idxs;
    for (const auto& [i,num]: enumerate(lines[lines.size()-2]))
    {
        if (num == '*' || num == '+')
        {
            ops.emplace_back(num);
            idxs.emplace_back(i);
        }
    }
    std::vector<std::vector<u64>> nums(ops.size());

    for (const auto& [i,idx]: enumerate(idxs))
    {
        size_t next = 0;
        if (static_cast<size_t>(i) == idxs.size()-1)
        {
            next = std::numeric_limits<size_t>::max();
        }
        else
        {
            next = idxs.at(i+1);
        }

        for (size_t j = idx; j<next; j++)
        {
            std::string num;
            bool all_too_long = true;
            for (size_t li = 0; li<lines.size()-2; li++)
            {
                if (j >= lines[li].size())
                {
                    continue;
                }
                all_too_long = false;
                if (lines[li][j] != ' ')
                {
                    num += lines[li][j];
                }
            }
            if (!num.empty())
            {
                nums[i].emplace_back(std::stoull(num));
            }
            if (all_too_long)
            {
                break;
            }
        }
    }

    return std::make_tuple(nums, ops);

}

[[nodiscard]] u64 calc(const auto& nums, const auto& ops)
{
    u64 sum = 0;
    for (const auto& [num, op]: std::views::zip(nums, ops))
    {
        if (op == '+')
        {

            u64 tmp = 0;
            for (const auto ele: num)
            {
                tmp += ele;
            }
            sum += tmp;
        }
        if (op == '*')
        {
            u64 tmp = 1;
            for (const auto ele: num)
            {
                tmp *= ele;
            }
            sum += tmp;
        }
    }
    return sum;
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
        const auto& [nums, ops] = getInput(argv[1]);
        std::println("Part 1: {}", calc(nums, ops));
    }

    {
        const auto& [nums, ops] = getInput2(argv[1]);
        std::println("Part 2: {}", calc(nums, ops));
    }
    return 0;
}