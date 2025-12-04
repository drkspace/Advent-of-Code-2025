
#include <print>
#include "../utils/utils.h"
#include <cstdio>
#include <cmath>

auto getInput(const std::string& fp)
{
    const auto lines = read_file(fp);
    std::vector<std::vector<u64>> out;

    for (const auto& line: lines)
    {

    }

    return out;
}

int main(const int argc, char* argv[])
{
    if (!(argc == 2 || argc == 3))
    {
        std::println(stderr, "Invalid Args");
        return 1;
    }
    const auto inp = getInput(argv[1]);


    return 0;
}