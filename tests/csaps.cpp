#include <iostream>

#include "csaps.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"


TEST_CASE("Univariate auto smoothing", "[csaps]")
{
  const size_t pcount = 21;

  csaps::DoubleArray xdata(pcount);
  xdata <<
    0, 0.314159265358979, 0.628318530717959, 0.942477796076938, 1.25663706143592,
    1.5707963267949, 1.88495559215388, 2.19911485751286, 2.51327412287183,
    2.82743338823081, 3.14159265358979, 3.45575191894877, 3.76991118430775,
    4.08407044966673, 4.39822971502571, 4.71238898038469, 5.02654824574367,
    5.34070751110265, 5.65486677646163, 5.96902604182061, 6.28318530717959;

  csaps::DoubleArray ydata(pcount);
  ydata <<
    -0.0308480549621108, 0.321227871478931, 0.581558026193185, 0.837552852746324,
    0.979054097107034, 0.977259260528264, 0.928702941809463, 0.839204212128449,
    0.633599187660844, 0.346610257849157, -0.0142182730042132, -0.308917481822601,
    -0.569438958775259, -0.787746791676657, -0.964031440816114, -0.993880381393437,
    -0.950748199764373, -0.857640149415879, -0.560502590131236, -0.270752875311336,
    -0.013511401609863;

  const size_t xi_pcount = 120;

  csaps::UnivariateCubicSmoothingSpline sp(xdata, ydata);
  csaps::DoubleArray xidata;
  csaps::DoubleArray yidata = sp(xi_pcount, xidata);

  REQUIRE(xidata.size() == xi_pcount);
  REQUIRE(yidata.size() == xi_pcount);
}


TEST_CASE("Univariate two points", "[csaps]")
{
  const size_t pcount = 2;

  csaps::DoubleArray xdata(pcount); xdata << 1., 2.;
  csaps::DoubleArray ydata(pcount); ydata << 3., 4.;
  csaps::DoubleArray xidata(pcount + 1); xidata << 1., 1.5, 2.;

  csaps::UnivariateCubicSmoothingSpline sp(xdata, ydata);

  csaps::DoubleArray yidata = sp(xidata);

  csaps::DoubleArray desired_yidata(pcount + 1); desired_yidata << 3., 3.5, 4.;

  REQUIRE(yidata.size() == pcount + 1);
  REQUIRE(yidata.isApprox(desired_yidata));
}
