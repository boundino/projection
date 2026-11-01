#include "xjjanauti.h"

int macro(const std::string& inputname, const std::string& outputname) {

  auto* inf = xjjroot::openfile(inputname);
  if (!inf) return 2;
  
  std::map<std::string, xjjc::array2D<TH1D*>> h1ptys;
  auto read_hists = [&h1ptys](TFile* inf) {
    for (auto* h3 : xjjana::getobj_regexp<TH3D>(inf, "h3_.+")) {
      auto name = xjjc::str_eraseall(h3->GetName(), { "h3_" });
      auto ny = h3->GetXaxis()->GetNbins(), npt = h3->GetZaxis()->GetNbins();
      h1ptys[name] = xjjc::array2d<TH1D*>(npt, ny);
      for (int i=0; i<ny; i++) {
        for (int j=0; j<npt; j++) {
          auto* h1_mass = h3->ProjectionY(Form("h1_mass_%s__pt-%d__y-%d", name.c_str(), j, i),
                                          i+1, i+1, // y bin
                                          j+1, j+1, // pt bin
                                          "e");
          h1ptys.at(name)[j][i] = h1_mass;
        }
      }
    }
    return 0;
  };

  read_hists(inf);

  auto* outf = xjjroot::newfile("rootfiles/" + outputname + ".root");
  for (auto& [_, hhh] : h1ptys) {
    for (auto& hh : hhh)
      for (auto& h : hh)
        xjjroot::writehist(h);
  }
  xjjroot::closefile(outf);

  return 0;
}

int main(int argc, char* argv[]) {
  if (argc == 3)
    return macro(argv[1], argv[2]);

  return 1;
}
