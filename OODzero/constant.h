#include <fstream>
#include "xjjanauti.h"

TGraph* curve(const std::string& inputname, const std::string& name) {
  std::ifstream getdata(inputname.c_str());
  std::vector<double> xs, ys;
  while (true) {
    double x, y;
    getdata >> x;
    if (getdata.eof()) break;
    getdata >> y;
    xs.push_back(x);
    ys.push_back(y);
  }
  auto* gr = new TGraph(xs.size(), xs.data(), ys.data());
  gr->SetName(Form("gr_%s", name.c_str()));
  return gr;
}

namespace wy {
  const auto cc_charm = static_cast<Color_t>(TColor::GetColor("#336699"));
  TGraph* gr_OO_cent010_rad() {
    auto* gr = curve("datas/D-RAA-OO-010-rad.dat", "OO_cent010_rad");
    xjjroot::setthgrstyle(gr, -1, -1, -1, cc_charm, 9, 4);
    return gr;
  }
  TGraph* gr_OO_cent010_radcol() {
    auto* gr = curve("datas/D-RAA-OO-010-radcol.dat", "OO_cent010_radcol");
    xjjroot::setthgrstyle(gr, -1, -1, -1, cc_charm, 1, 4);
    return gr;
  }
}
