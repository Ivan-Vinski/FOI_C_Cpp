#include <vector>

int sum_of_minimums(const std::vector<std::vector<int>> &numbers)
{
    int sum = 0;
    for (int i = 0; i < numbers.size(); i++){
      sum += *min_element(numbers[i].begin(), numbers[i].end());
    }
    return sum;
}
