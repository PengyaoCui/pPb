TGraphAsymmErrors *GetKstatMeanPtMB()
{
  int    p8420_d19x1y1_numpoints    = 7;

  double p8420_d19x1y1_xval[]       = { 45.0, 36.2, 30.5, 23.2, 16.1, 9.8, 4.4 };
  double p8420_d19x1y1_xerrminus[]  = { 1.0, 0.7999999999999972, 0.6999999999999993, 0.5, 0.40000000000000036, 0.1999999999999993, 0.09999999999999964 };
  double p8420_d19x1y1_xerrplus[]   = { 1.0, 0.7999999999999972, 0.6999999999999993, 0.5, 0.3999999999999986,  0.1999999999999993, 0.09999999999999964 };

  double p8420_d19x1y1_yval[]       = { 0.9434, 0.9363, 0.9239, 0.8963, 0.8569, 0.8, 0.7104 };
  double p8420_d19x1y1_ystatminus[] = { 0.0019, 0.002, 0.0016, 0.0014, 0.0015, 0.0017, 0.0023 };
  double p8420_d19x1y1_ystatplus[]  = { 0.0019, 0.002, 0.0016, 0.0014, 0.0015, 0.0017, 0.0023 };
//=============================================================================

  TGraphAsymmErrors *p8420_d19x1y1 = new TGraphAsymmErrors(p8420_d19x1y1_numpoints,
                                                           p8420_d19x1y1_xval,
                                                           p8420_d19x1y1_yval,
                                                           p8420_d19x1y1_xerrminus,
                                                           p8420_d19x1y1_xerrplus,
                                                           p8420_d19x1y1_ystatminus,
                                                           p8420_d19x1y1_ystatplus);
//=============================================================================

  p8420_d19x1y1->SetName("gKstatMeanPtMB");
  return p8420_d19x1y1;
}

//_____________________________________________________________________________
TGraphAsymmErrors *GetKsystMeanPtMB()
{
  int    p8420_d19x1y1_numpoints    = 7;

  double p8420_d19x1y1_xval[]       = { 45.0, 36.2, 30.5, 23.2, 16.1, 9.8, 4.4 };
  double p8420_d19x1y1_xerrminus[]  = { 1.0, 0.7999999999999972, 0.6999999999999993, 0.5, 0.40000000000000036, 0.1999999999999993, 0.09999999999999964 };
  double p8420_d19x1y1_xerrplus[]   = { 1.0, 0.7999999999999972, 0.6999999999999993, 0.5, 0.3999999999999986,  0.1999999999999993, 0.09999999999999964 };

  double p8420_d19x1y1_yval[]       = { 0.9434, 0.9363, 0.9239, 0.8963, 0.8569, 0.8, 0.7104 };
  double p8420_d19x1y1_yerrminus[]  = { 0.01468536686637416,  0.015414927829866736, 0.014819581640518735,
                                        0.014108508071373102, 0.014103545653487282, 0.013006536818077286, 0.015289865924853624 };
  double p8420_d19x1y1_yerrplus[]   = { 0.01468536686637416,  0.015414927829866736, 0.014819581640518735,
                                        0.014108508071373102, 0.014103545653487282, 0.013006536818077286, 0.015289865924853624 };
//=============================================================================

  TGraphAsymmErrors *p8420_d19x1y1 = new TGraphAsymmErrors(p8420_d19x1y1_numpoints,
                                                           p8420_d19x1y1_xval,
                                                           p8420_d19x1y1_yval,
                                                           p8420_d19x1y1_xerrminus,
                                                           p8420_d19x1y1_xerrplus,
                                                           p8420_d19x1y1_yerrminus,
                                                           p8420_d19x1y1_yerrplus);
//=============================================================================

  p8420_d19x1y1->SetName("gKsystMeanPtMB");
  return p8420_d19x1y1;
}

//_____________________________________________________________________________
TGraphAsymmErrors *GetLstatMeanPtMB()
{
  int    p8420_d17x1y1_numpoints   = 7;

  double p8420_d17x1y1_xval[]       = { 45.0, 36.2, 30.5, 23.2, 16.1, 9.8, 4.4 };
  double p8420_d17x1y1_xerrminus[]  = { 1.0, 0.7999999999999972, 0.6999999999999993, 0.5, 0.40000000000000036, 0.1999999999999993, 0.09999999999999964 };
  double p8420_d17x1y1_xerrplus[]   = { 1.0, 0.7999999999999972, 0.6999999999999993, 0.5, 0.3999999999999986,  0.1999999999999993, 0.09999999999999964 };

  double p8420_d17x1y1_yval[]       = { 1.378, 1.354, 1.324, 1.271, 1.197, 1.098, 0.9711 };
  double p8420_d17x1y1_ystatminus[] = { 0.005, 0.005, 0.004, 0.004, 0.004, 0.004, 0.0056 };
  double p8420_d17x1y1_ystatplus[]  = { 0.005, 0.005, 0.004, 0.004, 0.004, 0.004, 0.0056 };
//=============================================================================

  TGraphAsymmErrors *p8420_d17x1y1 = new TGraphAsymmErrors(p8420_d17x1y1_numpoints,
                                                           p8420_d17x1y1_xval,
                                                           p8420_d17x1y1_yval,
                                                           p8420_d17x1y1_xerrminus,
                                                           p8420_d17x1y1_xerrplus,
                                                           p8420_d17x1y1_ystatminus,
                                                           p8420_d17x1y1_ystatplus);
//=============================================================================

  p8420_d17x1y1->SetName("gLstatMeanPtMB");
  return p8420_d17x1y1;
}

//_____________________________________________________________________________
TGraphAsymmErrors *GetLsystMeanPtMB()
{
  int    p8420_d17x1y1_numpoints   = 7;
  double p8420_d17x1y1_xval[]       = { 45.0, 36.2, 30.5, 23.2, 16.1, 9.8, 4.4 };
  double p8420_d17x1y1_xerrminus[]  = { 1.0, 0.7999999999999972, 0.6999999999999993, 0.5, 0.40000000000000036, 0.1999999999999993, 0.09999999999999964 };
  double p8420_d17x1y1_xerrplus[]   = { 1.0, 0.7999999999999972, 0.6999999999999993, 0.5, 0.3999999999999986,  0.1999999999999993, 0.09999999999999964 };

  double p8420_d17x1y1_yval[]       = { 1.378, 1.354, 1.324, 1.271, 1.197, 1.098, 0.9711 };
  double p8420_d17x1y1_yerrminus[]  = { 0.051468436929831086, 0.04666904755831214, 0.04936598018878993,
                                        0.038483762809787714, 0.03385262175962152, 0.04578209256903838, 0.06073104642602496 };
  double p8420_d17x1y1_yerrplus[]   = { 0.051468436929831086, 0.04666904755831214, 0.04936598018878993,
                                        0.038483762809787714, 0.03385262175962152, 0.04578209256903838, 0.06073104642602496 };
//=============================================================================

  TGraphAsymmErrors *p8420_d17x1y1 = new TGraphAsymmErrors(p8420_d17x1y1_numpoints,
                                                           p8420_d17x1y1_xval,
                                                           p8420_d17x1y1_yval,
                                                           p8420_d17x1y1_xerrminus,
                                                           p8420_d17x1y1_xerrplus,
                                                           p8420_d17x1y1_yerrminus,
                                                           p8420_d17x1y1_yerrplus);
//=============================================================================

  p8420_d17x1y1->SetName("gLstatMeanPtMB");
  return p8420_d17x1y1;

}
