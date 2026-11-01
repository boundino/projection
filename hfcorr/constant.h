#pragma once

const double lumi_MB_2023 = 1.48, lumi_MB_2024 = 1.579, lumi_MB_2025 = 2.228, lumi_MB_2026 = 2.367, lumi_Photon40_2024 = 480405.638,
  lumi_MB_mtd = 7., lumi_Photon40_2018 = 1.697, lumi_Photon40_2017 = 300615.194, lumi_MB_2018 = 0.58;

struct Perform {
  double lumi;
  std::vector<double> bins;
  std::vector<double> ycenters;
  std::vector<double> yerrs;
  std::string name, xtitle, ytitle;
};

const std::string ytitle_common = "#frac{1}{N}#frac{#it{d}N}{#it{d}#Delta#phi} (rad^{-1})";
const double lumi_ddbar = lumi_MB_mtd;
const std::vector<double> bins_ddbar = { M_PI*0., M_PI/8., M_PI/8.*2, M_PI/8.*3, M_PI/8.*4, M_PI/8.*5, M_PI/8.*6, M_PI/8.*7, M_PI };
const std::vector<double> ycenters_ddbar = { 0.669928, 0.366581, 0.244737, 0.195766, 0.199264, 0.222584, 0.288461, 0.359002 };
const std::vector<double> yerrs_ddbar = { 0.123399, 0.0961926, 0.0874478, 0.0833669, 0.0833669, 0.0851159, 0.0909457, 0.0967756 };
Perform perf_ddbar = { .lumi = lumi_ddbar, .bins = bins_ddbar, .ycenters = ycenters_ddbar, .yerrs = yerrs_ddbar, .name = "ddbar",
  .xtitle = "#Delta#phi(" + xjjroot::CMS::Dz + ", " + xjjroot::CMS::Dzbar + ") (rad)", .ytitle = ytitle_common };

const double lumi_phd = lumi_Photon40_2018;
const std::vector<double> bins_phd = {  M_PI*0.,  M_PI*0.3,  M_PI*0.5,  M_PI*0.7,  M_PI*0.9,  M_PI };
const std::vector<double> ycenters_phd = { 0.00224878, -0.00967754, 0.0265961, 0.0384125, 0.0438535 };
const std::vector<double> yerrs_phd = { 0.0105523, 0.0136301, 0.0138499, 0.0147293, 0.0228634 };
Perform perf_phd = { .lumi = lumi_phd, .bins = bins_phd, .ycenters = ycenters_phd, .yerrs = yerrs_phd, .name = "phd",
  .xtitle = "#Delta#phi^{#gammaD} (rad)", .ytitle = ytitle_common };

const double lumi_phd_pp = lumi_Photon40_2017;
const std::vector<double> bins_phd_pp = {  M_PI*0.,  M_PI*0.1,  M_PI*0.2,  M_PI*0.3,  M_PI*0.4,  M_PI*0.5,  M_PI*0.6,  M_PI*0.7,  M_PI*0.8,  M_PI*0.9,  M_PI };
const std::vector<double> ycenters_phd_pp = { 0.00340954, 0.00356782, 0.00570466, 0.00491324, 0.0029083, 0.0070761, 0.0094577, 0.0137171, 0.0227855, 0.0511357 };
const std::vector<double> yerrs_phd_pp = { 0.00142456, 0.00166199, 0.00158285, 0.00158285, 0.0015114, 0.0016488, 0.0019236, 0.0024732, 0.0036182, 0.0053128 };
Perform perf_phd_pp = { .lumi = lumi_phd_pp, .bins = bins_phd_pp, .ycenters = ycenters_phd_pp, .yerrs = yerrs_phd_pp, .name = "phd_pp",
  .xtitle = "#Delta#phi^{#gammaD} (rad)", .ytitle = ytitle_common };

const double lumi_djet = lumi_MB_2018;
const std::vector<double> bins_djet = {  M_PI*0.,  M_PI*0.1,  M_PI*0.2,  M_PI*0.3,  M_PI*0.4,  M_PI*0.5,  M_PI*0.6,  M_PI*0.7,  M_PI*0.8,  M_PI*0.9,  M_PI };
const std::vector<double> ycenters_djet = { 1.22078, 0.558699, 0.168051, -0.000516892, 0.026848, 0.0750101, 0.0334155, 0.273132, 0.404483, 0.423091 };
const std::vector<double> yerrs_djet = { 0.0471284, 0.0547297, 0.0514459, 0.035027, 0.0361216, 0.0383108, 0.0394054, 0.0481622, 0.0503514, 0.045973 };
Perform perf_djet = { .lumi = lumi_djet, .bins = bins_djet, .ycenters = ycenters_djet, .yerrs = yerrs_djet, .name = "djet",
  .xtitle = "#Delta#phi^{jD} (rad)", .ytitle = ytitle_common };

struct Theory {
  std::vector<double> bins;
  std::vector<double> ys;
  std::string name, xtitle, ytitle;
};

const std::vector<double> bins_ddbar_pythia = { M_PI*0., M_PI/8., M_PI/8.*2, M_PI/8.*3, M_PI/8.*4, M_PI/8.*5, M_PI/8.*6, M_PI/8.*7, M_PI };
const std::vector<double> ys_ddbar_pythia = { 2.10769, 1.15165, 0.771429, 0.613187, 0.624176, 0.701099, 0.907692, 1.12747 };
Theory curve_ddbar_pythia = { .bins = bins_ddbar_pythia, .ys = ys_ddbar_pythia, .name = "ddbar_pythia",
  .xtitle = "#Delta#phi(" + xjjroot::CMS::Dz + ", " + xjjroot::CMS::Dzbar + ") (rad)", .ytitle = ytitle_common };

const std::vector<double> bins_ddbar_jx = { M_PI*0., M_PI/8., M_PI/8.*2, M_PI/8.*3, M_PI/8.*4, M_PI/8.*5, M_PI/8.*6, M_PI/8.*7, M_PI };
const std::vector<double> ys_ddbar_jx = { 0.556005, 0.489607, 0.394342, 0.306774, 0.241339, 0.197075, 0.18264, 0.183603 };
Theory curve_ddbar_jx = { .bins = bins_ddbar_jx, .ys = ys_ddbar_jx, .name = "ddbar",
  .xtitle = "#Delta#phi(" + xjjroot::CMS::Dz + ", " + xjjroot::CMS::Dzbar + ") (rad)", .ytitle = ytitle_common };

const std::vector<double> bins_phd_pythia = {  M_PI*0.,  M_PI*0.3,  M_PI*0.5,  M_PI*0.7,  M_PI*0.9,  M_PI };
const std::vector<double> ys_phd_pythia = { 0.0148231, 0.0145402, 0.0179351, 0.0456603, 0.150903 };
Theory curve_phd_pythia = { .bins = bins_phd_pythia, .ys = ys_phd_pythia, .name = "phd",
  .xtitle = "#Delta#phi^{#gammaD} (rad)", .ytitle = ytitle_common };

const std::vector<double> bins_phd_pp_pythia = {  M_PI*0.,  M_PI*0.1,  M_PI*0.2,  M_PI*0.3,  M_PI*0.4,  M_PI*0.5,  M_PI*0.6,  M_PI*0.7,  M_PI*0.8,  M_PI*0.9,  M_PI };
const std::vector<double> ys_phd_pp_pythia = { 0.0104751, 0.0149774, 0.0152503, 0.0149774, 0.0142953, 0.0153867, 0.0202984, 0.0301216, 0.0610922, 0.151139 };
Theory curve_phd_pp_pythia = { .bins = bins_phd_pp_pythia, .ys = ys_phd_pp_pythia, .name = "phd_pp",
  .xtitle = "#Delta#phi^{#gammaD} (rad)", .ytitle = ytitle_common };

const std::vector<double> bins_djet_pythia = {  M_PI*0.,  M_PI*0.1,  M_PI*0.2,  M_PI*0.3,  M_PI*0.4,  M_PI*0.5,  M_PI*0.6,  M_PI*0.7,  M_PI*0.8,  M_PI*0.9,  M_PI };
const std::vector<double> ys_djet_pythia = { 0.85874, 0.171772, 0.12974, 0.120545, 0.127113, 0.148129, 0.191475, 0.278167, 0.435789, 0.711626 };
Theory curve_djet_pythia = { .bins = bins_djet_pythia, .ys = ys_djet_pythia, .name = "djet",
  .xtitle = "#Delta#phi^{jD} (rad)", .ytitle = ytitle_common };

TH1D* make_h_scale(Perform& pf) {
  auto* h_scale = new TH1D(Form("h1_perform_%s", pf.name.c_str()), Form(";%s;%s", pf.xtitle.c_str(), pf.ytitle.c_str()),
                           pf.bins.size()-1, pf.bins.data());
  for (int i=0; i<pf.bins.size()-1; i++) {
    h_scale->SetBinContent(i+1, pf.ycenters[i]);
    h_scale->SetBinError(i+1, pf.yerrs[i]);
  }
  xjjroot::sethempty(h_scale, 0, 0.3);
  xjjroot::setthgrstyle(h_scale, kGray+2, 24, 1.5, kGray+2, 1, 1);
  h_scale->Scale(1./h_scale->Integral("width"));
  return h_scale;
}

TH1D* make_h_scale(Theory& pf) {
  auto* h_scale = new TH1D(Form("h1_theory_%s", pf.name.c_str()), Form(";%s;%s", pf.xtitle.c_str(), pf.ytitle.c_str()),
                           pf.bins.size()-1, pf.bins.data());
  for (int i=0; i<pf.bins.size()-1; i++) {
    h_scale->SetBinContent(i+1, pf.ys[i]);
    h_scale->SetBinError(i+1, 0);
  }
  xjjroot::sethempty(h_scale, 0, 0.3);
  xjjroot::setthgrstyle(h_scale, kGray+2, 24, 1.5, kGray+2, 1, 1);
  h_scale->Scale(1./h_scale->Integral("width"));
  return h_scale;
}

