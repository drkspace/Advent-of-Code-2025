
#include "../utils/utils.h"
#include <string>

#include <iostream>
#include <print>

struct Rotations {
  const bool is_left;
  const int amount;
};

auto getInput(const std::string& fp)
{
  auto lines = read_file(fp);
  std::vector<Rotations> out;

  for (auto& l : lines)
  {
    if (l.empty())
    {
      break;
    }

    const auto is_left = l[0] == 'L';
    l.erase(0, 1);
    const auto amount = std::stoi(l);
    out.emplace_back(is_left, amount);
  }
  return out;
}


int main(const int argc, char* argv[]) {

  if (!(argc == 2 || argc == 3))
  {
    std::cerr << "Invalid args" << std::endl;
    return 1;
  }
  constexpr int MAX = 100;
  const auto inp = getInput(argv[1]);

  {
    size_t zero_count = 0;
    int pos = 50;

    for (const auto& [is_left, amount]: inp)
    {
      pos = pmod(pos + (is_left?-1:1)*amount, MAX);
      zero_count += pos == 0;
    }

    std::println("Part 1: {}", zero_count);
  }

  {

    size_t zero_count = 0;
    int pos = 50;
    for (const auto& [is_left, amount]: inp)
    {
      const auto p_full = pos + (is_left?-1:1)*amount;

      if (p_full == 0) {
        zero_count++;
      }
      else if (p_full < 0) {
        zero_count += 1 + -1*p_full / MAX;
        if (pos == 0) {
          zero_count--;
        }
      }
      else {
        zero_count += p_full / MAX;
      }
      pos = pmod(p_full, MAX);
    }

    std::println("Part 2: {}", zero_count);
  }

}