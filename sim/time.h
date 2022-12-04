#ifndef TIME_H
#define TIME_H

#include <string>

typedef size_t ts;
typedef size_t duration;

std::string pretty_d(duration d);
std::string pretty_ts(ts t);

#endif
