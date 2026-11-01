#include "xjjanauti.h"
#include "xjjmypdf.h"

#include "constant.h"

// std::map<std::string, Color_t> colors = {  
// };

int macro() {
  std::map<std::string, TH1D*> herrs, hcenters, hs_2025, hs_run3;
  std::map<std::string, double> lumis;
  for (auto pf : std::vector<Perform>{ perf_ddbar, perf_phd, perf_phd_pp, perf_djet }) {
    herrs[pf.name] = make_h_scale(pf);
    lumis[pf.name] = pf.lumi;
  }
  xjjroot::print_tab(herrs, 0);
  for (auto pf : std::vector<Theory>{ curve_ddbar_jx, curve_ddbar_pythia, curve_phd_pythia, curve_phd_pp_pythia, curve_djet_pythia }) {
    hcenters[pf.name] = make_h_scale(pf);
    // xjjroot::setthgrstyle(hcenters[pf.name], -1, -1, -1, kGray+2, 2, 4);
    xjjroot::setthgrstyle(hcenters[pf.name], -1, -1, -1, xjjroot::mycolor_middle["green"], 2, 4, 0, 0, 0, 0.7);
    xjjana::sethminmax(hcenters[pf.name], 0., 1.7);
  }
  xjjroot::print_tab(hcenters, 0);

  auto project = [&herrs, &hcenters, &lumis](const std::string& key, double luminew, const std::string& namenew) -> TH1D* {
    auto* h = (TH1D*)herrs[key]->Clone(Form("h1_proj_%s_%s", key, namenew));
    for (int i=0; i<h->GetXaxis()->GetNbins(); i++) {
      h->SetBinContent(i+1, hcenters[key]->GetBinContent(i+1));
      h->SetBinError(i+1, herrs[key]->GetBinError(i+1) * std::sqrt(lumis[key] / luminew));
      // if (key == "ddbar") std::cout << h->GetBinCenter(i+1) << std::endl;
    }
    xjjroot::sethempty(h, 0, 0.3);
    xjjana::sethminmax(h, 0., 1.7);
    return h;
  };

  const auto lumi_run3 = lumi_MB_2023 + lumi_MB_2024 + lumi_MB_2025 + lumi_MB_2026;
  
  for (auto& [key, _] : herrs) {
    auto luminew = lumi_MB_2025;
    if (xjjc::str_contains(key, "pp")) luminew = lumi_Photon40_2024;
    hs_2025[key] = project(key, luminew, "2025");
    xjjroot::setthgrstyle(hs_2025[key], kGray+2, 21, 1.5, kGray+3, 1, 1);
    if (!xjjc::str_contains(key, "pp")) luminew = lumi_run3;
    hs_run3[key] = project(key, luminew, "run3");
    xjjroot::setthgrstyle(hs_run3[key], kBlack, 20, 1.5, kBlack, 1, 1);
  }

  const float xleft = 0.24, tsize = 0.038, lspace = 1.2, xright = 0.5;
  auto y_pos = [&tsize, &lspace](float n = 0) -> float {
    const float ytop = 0.85;
    return ytop - n*tsize*lspace;
  };
  
  xjjroot::setgstyle(1);
  auto* pdf = new xjjroot::mypdf("figspdf/hfcorr.pdf");

  xjjroot::setthgrstyle(hcenters["ddbar"], -1, -1, -1, xjjroot::mycolor_middle["red"], 1, 4, 0, 0, 0, 0.5);
  auto* leg_ddbar = new TLegend(xright, y_pos(5), xright+0.3, y_pos(2));
  xjjroot::setleg(leg_ddbar, tsize);
  leg_ddbar->AddEntry(hs_run3["ddbar"], Form("Run 3 PbPb (%.1f nb^{-1})", lumi_run3), "pe");
  leg_ddbar->AddEntry(hcenters["ddbar"], "EPOS4HQ (PbPb)", "l");
  leg_ddbar->AddEntry(hcenters["ddbar_pythia"], "P#scale[0.8]{YTHIA}8 (pp)", "l");
  pdf->prepare();
  hcenters["ddbar"]->Draw("axis");
  hcenters["ddbar_pythia"]->Draw("l same");
  hcenters["ddbar"]->Draw("l same");
  hs_run3["ddbar"]->Draw("pe1 same");
  xjjroot::drawCMS(xjjroot::CMS::other("Private Projection"), "PbPb (5.36 TeV)");
  xjjroot::drawtexgroup(xleft, y_pos(), {
      "#it{p}_{T}^{trig D} > 4 GeV, #it{p}_{T}^{asso D} > 2 GeV",
      "|y| < 1"
    }, tsize, 13, 42, 1.5);
  leg_ddbar->Draw();
  pdf->write();

  // xjjroot::setthgrstyle(hs_run3["phd_pp"], kGray+1, 21, 1.5, kGray+1, 1, 1);
  xjjroot::setthgrstyle(hs_run3["phd_pp"], xjjroot::mycolor_middle["blue"], 21, 1.5, xjjroot::mycolor_middle["blue"], 1, 1, 0, 0, 0, 0.6, 0.6);
  auto* leg_phd = new TLegend(xleft, y_pos(6.5), xleft+0.25, y_pos(3.5));
  xjjroot::setleg(leg_phd, tsize);
  leg_phd->AddEntry(hs_run3["phd"], Form("Run 3 PbPb (%.1f nb^{-1})", lumi_run3), "pe");
  leg_phd->AddEntry(hs_run3["phd_pp"], Form("2024 pp (%.0f pb^{-1})", lumi_Photon40_2024*1.e-3), "pe");
  leg_phd->AddEntry(hcenters["phd"], "P#scale[0.8]{YTHIA}8, isoR3", "l");
  pdf->prepare();
  hcenters["phd"]->Draw("axis");
  hcenters["phd_pp"]->Draw("l same");
  hs_run3["phd_pp"]->Draw("pe1 same");
  hs_run3["phd"]->Draw("pe1 same");
  xjjroot::drawCMS(xjjroot::CMS::other("Private Projection"), "PbPb (5.36 TeV)");
  xjjroot::drawtexgroup(xleft, y_pos(), {
      "#it{p}_{T}^{D} > 5 GeV, |y^{D}| < 1.2",
      "#it{p}_{T}^{#gamma} > 40 GeV",
      "|#eta^{#gamma}| < 1.442"
    }, tsize, 13, 42, 1.5);
  leg_phd->Draw();
  pdf->write();
  
  xjjroot::setthgrstyle(hs_2025["djet"], xjjroot::mycolor_middle["red"], 20, 1.5, xjjroot::mycolor_middle["red"], 1, 1);
  auto* gr_djet_run3 = xjjana::shifthistcenter(hs_run3["djet"], "", -0.02, "");
  auto* gr_djet_2025 = xjjana::shifthistcenter(hs_2025["djet"], "", 0.02, "X0");
  auto* leg_djet = new TLegend(xright, y_pos(5), xright+0.25, y_pos(2));
  xjjroot::setleg(leg_djet, tsize);
  leg_djet->AddEntry(gr_djet_run3, Form("Run 3 PbPb (%.1f nb^{-1})", lumi_run3), "pe");
  leg_djet->AddEntry(gr_djet_2025, Form("2025 PbPb (%.1f nb^{-1})", lumi_MB_2025), "pe");
  leg_djet->AddEntry(hcenters["djet"], "P#scale[0.8]{YTHIA}8", "l");
  pdf->prepare();
  hcenters["djet"]->Draw("axis");
  hcenters["djet"]->Draw("l same");
  gr_djet_2025->Draw("pe1 same");
  gr_djet_run3->Draw("pe1 same");
  // hs_2025["djet"]->Draw("pe1 same");
  // hs_run3["djet"]->Draw("pe1 same");
  xjjroot::drawCMS(xjjroot::CMS::other("Private Projection"), "PbPb (5.36 TeV)");
  xjjroot::drawtexgroup(xleft, y_pos(), {
      "4 < #it{p}_{T}^{D} < 20 GeV, |y^{D}| < 1",
      "#it{p}_{T}^{jet} > 60 GeV",
      "|#eta^{jet}| < 1.6"
    }, tsize, 13, 42, 1.5);
  leg_djet->Draw();
  pdf->write();
  
  // for (auto& [key, h] : herrs) {
  //   pdf->prepare();
  //   h->Draw("pe");
  //   hcenters[key]->Draw("l same");
  //   hs_2025[key]->Draw("pe1 same");
  //   // hs_run3[key]->Draw("pe1 same");
  //   pdf->write();
  // }

  
  pdf->close();  
  return 0;
}

int main() {
  return macro();
}
