#include "xjjanauti.h"
#include "xjjstruct.h"
#include "xjjmypdf.h"
#include "dfitter.h"

#include "constant.h"

int macro(const std::string& inputname_data, const std::string& inputname_template, const std::string& outputname) {

  const std::vector<double> ptbins = { 1.5, 2.4, 3.0, 3.5, 4.2, 5.0, 6.0, 7.0, 8.0 };
  const std::vector<double> ybins = { -1, 1 };
  auto* h2_bins = new TH2D("h2_bins", ";#it{p}_{T} (GeV);y",
                           ptbins.size() - 1, ptbins.data(),
                           ybins.size() - 1, ybins.data());
  const xjjroot::bintex tbins(h2_bins, 1, 0);
  for (int i=0; i<tbins.npt(); i++) {
    std::cout<<h2_bins->GetXaxis()->GetBinCenter(i+1)<<std::endl;
  }
  const std::vector<double> raa_wy_0_10 = { 0.675272, 0.690062, 0.690841, 0.686170, 0.677608, 0.668267, 0.662818, 0.659704 };

  auto* inf_template = xjjroot::openfile(inputname_template);
  // auto hmass = xjjana::getobj_regexp<TH1D>(inf_data, "ptBin.+/hmass_ptBin.+");

  std::map<std::string, TH1D*> hmass_mc;
  for (const std::string t : { "match", "swap", "kk", "pipi"}) {
    hmass_mc[t] = xjjana::getobj<TH1D>(inf_template, "h1_mass_mc-" + t + "__pt-0__y-0");
  }

  auto make_h1_pt = [&tbins](const std::string& name, const std::string& ytitle) -> TH1D* {
    auto* h1 = tbins.make_h1_pt<TH1D>(Form("h1_%s_pt", name.c_str()));
    h1->GetYaxis()->SetTitle(ytitle.c_str());
    xjjroot::setthgrstyle(h1, kBlack, 20, 1.7, kBlack, 1, 1);
    xjjroot::sethempty(h1);
    return h1;
  };
  auto* h1_yield = make_h1_pt("yield", "Raw Yield");
  auto* h1_raa = make_h1_pt("raa", "#it{R}_{AA}");
  auto* h1_raa_syst = make_h1_pt("raa_syst", "#it{R}_{AA}");
  
  auto* inf_data = xjjroot::openfile(inputname_data);
  xjjroot::setgstyle(1);
  auto* pdf = new xjjroot::mypdf("figspdf/" + outputname + ".pdf");
  for (int i=0; i<tbins.npt(); i++) {
    auto* h = xjjana::getobj<TH1D>(inf_data, Form("ptBin%d/hmass_ptBin%d", i, i));

    pdf->prepare();
    auto* df = new xjjroot::dfitter("3G-Peaky-Fwidth");
    df->set_range(1.73, 2.0);
    df->fit(h, hmass_mc.at("match"), hmass_mc.at("swap"), hmass_mc.at("kk"), hmass_mc.at("pipi"));
    xjjroot::drawtexgroup(0.24, 0.86, { tbins.label_pt(i), tbins.label_y() }, 0.035, 13);
    df->draw_leg();
    df->draw_result(0.24, 0.86-2*0.035*1.15, 0.035);
    xjjroot::drawCMS(xjjroot::CMS::internal, "OO (5.36 TeV)");

    const auto nsig = df->yield(), nsig_err = df->yieldErr();
    h1_yield->SetBinContent(i+1, nsig);
    h1_yield->SetBinError(i+1, nsig_err);
    h1_raa->SetBinContent(i+1, raa_wy_0_10[i]);
    h1_raa->SetBinError(i+1, raa_wy_0_10[i]*nsig_err/nsig);
    h1_raa_syst->SetBinContent(i+1, raa_wy_0_10[i]);
    h1_raa_syst->SetBinError(i+1, raa_wy_0_10[i]*0.05);

    gPad->RedrawAxis();
    pdf->write();
  }

  for (TH1D* h : { h1_yield }) {  
    pdf->prepare();
    h->Draw("pe1");
    xjjroot::drawtexgroup(0.24, 0.86, { tbins.label_y() }, 0.035, 13);
    xjjroot::drawCMS(xjjroot::CMS::internal, "OO (5.36 TeV)");
    pdf->write();
  }
  
  auto* gr_raa_syst = xjjana::shifthistcenter(h1_raa_syst, "gr_raa_syst");
  xjjroot::setthgrstyle(gr_raa_syst, kBlack, 20, 1.5, 0, 0, 0, kBlack, 0.1, 1001);
  auto* gr_rad = wy::gr_OO_cent010_rad();
  auto* gr_radcol = wy::gr_OO_cent010_radcol();

  const float xleft = 0.22, tsize = 0.037, lspace = 1.2;
  auto y_pos = [&tsize, &lspace](float n = 0) -> float {
    const float ytop = 0.42;
    return ytop - n*tsize*lspace;
  };
  auto* leg = new TLegend(xleft, y_pos(3), xleft+0.3, y_pos(1));
  xjjroot::setleg(leg, tsize);
  leg->AddEntry(gr_rad, "Rad. E_{loss}", "l");
  leg->AddEntry(gr_radcol, "Rad. + Col. E_{loss}", "l");
  auto* leg2 = new TLegend(xleft+0.4, y_pos(2), xleft+0.7, y_pos(1));
  xjjroot::setleg(leg2, tsize);
  leg2->AddEntry(gr_raa_syst, "|y| < 1", "pf");
  auto* hempty_raa = new TH2D("hempty_raa", ";#it{p}_{T} (GeV);#it{R}_{AA}", 10, 1, 10, 10, 0.3, 1);
  xjjroot::sethempty(hempty_raa, 0, 0.3);
  pdf->prepare();
  hempty_raa->Draw("axis");
  xjjroot::drawbox(hempty_raa->GetXaxis()->GetXmin(), 1, hempty_raa->GetXaxis()->GetXmin()+0.4, 1-0.05, kBlack, 0.1);
  xjjroot::drawtex(0.225, 0.86, "Lumi uncert.", 0.035, 13, 62, kBlack, 0.3);
  xjjroot::drawtex(0.88, 0.86, "Cent. 0-10\%", 0.04, 33);
  // xjjroot::drawline_horizon(1, hempty_raa, kBlack, 2, 2);
  xjjroot::drawCMS(xjjroot::CMS::other("Private Projection"), "OO (5.36 TeV)");
  gr_rad->Draw("c same");
  gr_radcol->Draw("c same");
  gr_raa_syst->Draw("2 same");
  h1_raa->Draw("pe1 same");
  leg->Draw();
  leg2->Draw();
  xjjroot::drawtex(xleft, y_pos(0.5), "W. Ke, I. Vitev (7 TeV)", tsize);
  xjjroot::drawtex(xleft+0.4, y_pos(0.5), "Data performance", tsize);
  pdf->write();
  
  pdf->close();

  
  return 0;
}

int main(int argc, char* argv[]) {
  if (argc == 4)
    return macro(argv[1], argv[2], argv[3]);
  return 1;
}
