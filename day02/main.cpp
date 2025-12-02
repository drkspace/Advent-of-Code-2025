
#include <print>
#include "../utils/utils.h"
#include <cstdio>
#include <cmath>

using dt = std::uint64_t;
auto getInput(const std::string& fp)
{
    const auto lines = read_file(fp);
    std::vector<std::tuple<dt, dt>> out;

    const auto l = lines[0];

    for (const auto& id: split(l, ','))
    {
        const auto parts = split(id, '-');
        out.emplace_back(std::stoll(parts[0]), std::stoll(parts[1]));
    }
    return out;
}

[[nodiscard]] constexpr bool is_invalid(const dt val)
{
    const dt ndigits = static_cast<dt>(std::ceil(std::log10(val)));

    if (ndigits%2 == 1)
    {
        return false;
    }

    const int factor = std::pow(10, ndigits/2);
    return (val/factor) == (val % factor);

}

[[nodiscard]] constexpr bool is_invalid2(const dt val)
{
    const dt ndigits = static_cast<dt>(std::ceil(std::log10(val)));

    for (dt i = 1; i<=(ndigits/2);i++)
    {
        if (ndigits%i != 0)
        {
            continue;
        }
        const int factor = std::pow(10, i);
        dt val_cpy = val;
        const dt v = val%factor;
        bool miss = false;
        while (val_cpy > 0)
        {
            if ((val_cpy%factor) != v)
            {
                miss = true;
                break;
            }
            val_cpy = val_cpy / factor;

        }
        if (!miss)
        {
        return true;

        }
    }
    return false;


}

int main(const int argc, char* argv[])
{
    if (!(argc == 2 || argc == 3))
    {
        std::println(stderr, "Invalid Args");
        return 1;
    }
    const auto inp = getInput(argv[1]);

    {
        dt sum = 0;
        for (const auto& [a,b]: inp)
        {
            for (dt i=a; i<=b; i++)
            {
                if (is_invalid(i))
                {
                    sum += i;
                }
            }
        }
        std::println("part 1: {}", sum);
    }

    {
        dt sum = 0;
        for (const auto& [a,b]: inp)
        {
            for (dt i=a; i<=b; i++)
            {
                if (is_invalid2(i))
                {
                    sum += i;
                }
            }
        }
        std::println("part 2: {}", sum);
    }

    return 0;
}