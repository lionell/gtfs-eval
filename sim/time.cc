#include "time.h"

#include <sstream>
#include <iomanip>

std::string pretty_d(duration d) {
  const int seconds = d % 60; d /= 60;
  const int minutes = d % 60; d /= 60;
  const int hours   = d % 24; d /= 24;
  const int days    = d % 7;  d /= 7;
  int weeks   = d % 52; d /= 52;
  const int months  = int(weeks / 4.3);
  weeks = weeks - int(months * 4.3);
  const int years   = d;

  std::ostringstream ss;
  ss.fill('0');

  if (years > 0) ss << years << "y ";
  if (months > 0) ss << months << "m ";
  if (weeks > 0) ss << weeks << "w ";
  if (days > 0)  ss << days << "d ";
  ss << std::setw(2) << hours   << "h "
     << std::setw(2) << minutes << "m "
     << std::setw(2) << seconds << "s";
  return ss.str();
}

std::string pretty_ts(ts t) {
  static const ts EPOCH = 1669852800; // 2022-12-01 00:00:00 UTC
  return pretty_d(t - EPOCH);
}
