bool isAscOrder(std::vector<int> arr)
{
    for (auto i = arr.begin(); i != arr.end() - 1; i++){
      if (*i > *(i + 1)) return false;
    }
    return true;
}
