class WhichAreIn
{
  public:
  static std::vector<std::string> inArray(std::vector<std::string> &array1, std::vector<std::string> &array2){

    std::vector<std::string> array3 = {};
    for (int i = 0; i < array1.size(); i++){
      for (int j = 0; j < array2.size(); j++){
        if (array2[j].find(array1[i]) != std::string::npos) array3.push_back(array1[i]);
      }
    }
    std::sort(array3.begin(), array3.end());
    array3.erase( unique(array3.begin(), array3.end()), array3.end());
    return array3;
  }
};
