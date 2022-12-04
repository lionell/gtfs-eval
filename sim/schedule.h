#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "time.h"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>

using stop = size_t;

class Schedule {
  std::unordered_map<stop, std::unordered_map<stop, std::set<std::pair<ts, ts>>>> edges;
  std::unordered_set<stop> stops_;

public:
  Schedule(std::string filename);
  std::unordered_map<stop, duration> dijkstra(stop from, ts start_time);
  std::unordered_set<stop> stops();
};

#endif
