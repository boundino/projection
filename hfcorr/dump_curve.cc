#include "xjjanauti.h"

int macro(const std::string& inputname, float scale = 1.) {
  std::ifstream getdata(inputname.c_str());
  std::vector<double> ys;
  while (true) {
    double tmp, y;
    getdata >> tmp;
    if (getdata.eof()) break;
    getdata >> y;
    ys.push_back(y * scale);
  }
  auto print_array = [](const std::vector<double>& vs, const std::string& name) {
    std::cout << "const std::vector<double> " << name << " = { ";
    for (int i=0; i<vs.size(); i++) {
      if (i) std::cout << ", ";
      std::cout << vs[i];
    }
    std::cout << " };" << std::endl;
  };

  print_array(ys, "ys");

  return 0;
}

int main(int argc, char* argv[]) {
  if (argc == 3)
    return macro(argv[1], std::atof(argv[2]));
  if (argc == 2)
    return macro(argv[1]);
  return 1;
}
