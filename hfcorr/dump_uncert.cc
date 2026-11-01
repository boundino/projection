#include "xjjanauti.h"

int macro(const std::string& inputname, float scale = 1.) {
  std::ifstream getdata(inputname.c_str());
  std::vector<double> ys, yerrs;
  while (true) {
    double tmp, y, yerr;
    getdata >> tmp;
    if (getdata.eof()) break;
    getdata >> y >> tmp >> yerr;
    ys.push_back(y * scale);
    yerrs.push_back(std::abs(yerr - y) * scale);
  }
  auto print_array = [](const std::vector<double>& vs, const std::string& name) {
    std::cout << "const std::vector<double> " << name << " = { ";
    for (int i=0; i<vs.size(); i++) {
      if (i) std::cout << ", ";
      std::cout << vs[i];
    }
    std::cout << " };" << std::endl;
  };

  print_array(ys, "ycenters");
  print_array(yerrs, "yerrs");

  return 0;
}

int main(int argc, char* argv[]) {
  if (argc == 3)
    return macro(argv[1], std::atof(argv[2]));
  if (argc == 2)
    return macro(argv[1]);
  return 1;
}
