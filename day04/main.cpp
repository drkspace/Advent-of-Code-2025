
#include <print>
#include "../utils/utils.h"
#include "../utils/easyTimer.hpp"
#include <cstdio>
#include <cmath>

auto getInput(const std::string& fp)
{
    return read_file(fp);
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
        int tot = 0;
        for (size_t i = 0; i< inp.size(); i++)
        {
            for (size_t j = 0; j<inp[i].size(); j++)
            {
                if (inp[i][j] == '.')
                {
                    continue;
                }
                int c = 0;
                for (const auto& ele: around(inp, i, j))
                {
                    c += ele=='@';
                }
                if (c<4)
                {
                    tot++;
                }
            }
        }
        std::println("Part 1 {}", tot);
    }

    {

        int tot = 0;
        int prev = 1;
        int cur = 0;
        while (prev != cur)
        {
            prev = cur;
            int this_count = 0;
            for (size_t i = 0; i< inp.size(); i++)
            {
                for (size_t j = 0; j<inp[i].size(); j++)
                {
                    if (inp[i][j] == '.')
                    {
                        continue;
                    }
                    int c = 0;
                    for (const auto& ele: around(inp, i, j))
                    {
                        c += ele=='@';
                    }
                    if (c<4)
                    {
                        this_count++;
                        inp[i][j] = '.';
                    }
                }
            }

            tot += this_count;

            cur = 0;
            for (const auto& row: inp)
            {
                for (const auto& c: row)
                {
                    cur += c == '@';
                }
            }

        }
        std::println("Part 2 {}", tot);
    }
    return 0;
}