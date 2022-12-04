#include "evaluator.h"
#include "time.h"
#include "csv.h"

#include <stdexcept>
#include <fstream>

Evaluator::Evaluator(std::string filename) {
  static const std::hash<std::string> H;

  std::ifstream in(filename);
  std::string s;
  while (in >> s) {
    const auto parts = split(s);
    const stop from = H(parts[0]);
    const stop to = H(parts[1]);
    const ts departure = std::stoll(parts[2]);

    trips.push_back({from, to, departure});
  }
}

duration Evaluator::shortest_route(Schedule& s, stop from, stop to, ts when) {
  static const duration PENALTY = 12 * 60 * 60; // 12 hours

  const trip t = {from, to, when};
  if (cache.find(t) != cache.end())
    return cache[t];
  auto routes = s.dijkstra(from, when);
  for (stop n : s.stops()) {
    cache[{from, n, when}] = routes.find(n) == routes.end() ? PENALTY : routes[n];
  }
  return cache[t];
}

duration Evaluator::eval(Schedule& s) {
  duration res = 0;
  for (const auto& [from, to, when] : trips) {
    duration d = shortest_route(s, from, to, when);
    if (res + d < res) throw std::out_of_range("Total duration overflow");
    res += d;
  }
  return res;
}
