#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "time.h"
#include "schedule.h"

#include <string>
#include <vector>
#include <unordered_map>

using stop = size_t;

class Evaluator {
  using trip = std::tuple<stop, stop, ts>;

  struct trip_hash {
    size_t operator()(std::tuple<stop, stop, ts> const& x) const {
      const std::hash<stop> h1;
      const std::hash<ts> h2;
      return h1(std::get<0>(x)) ^ h1(std::get<1>(x)) ^ h2(std::get<2>(x));
    }
  };

  std::unordered_map<trip, duration, trip_hash> cache;
  std::vector<trip> trips;

private:
  duration shortest_route(Schedule& s, stop from, stop to, ts when);

public:
  Evaluator(std::string filename);
  duration eval(Schedule& s);
};

#endif
