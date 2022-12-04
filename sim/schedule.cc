#include "schedule.h"
#include "csv.h"

#include <fstream>
#include <queue>

Schedule::Schedule(std::string filename) {
  static const std::hash<std::string> H;

  std::ifstream in(filename);
  std::string s;
  while (in >> s) {
    const auto parts = split(s);
    const stop from = H(parts[0]);
    const stop to = H(parts[1]);
    const ts departure = std::stoll(parts[2]);
    const ts arrival = std::stoll(parts[3]);

    stops_.insert(from);
    stops_.insert(to);
    edges[from][to].insert({departure, arrival});
  }
}

template <typename T>
using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

std::unordered_map<stop, duration> Schedule::dijkstra(stop from, ts start_time) {
  std::unordered_map<stop, ts> res;
  min_heap<std::pair<ts, stop>> q;
  q.emplace(start_time, from);
  while (!q.empty()) {
    const ts now = q.top().first;
    const stop cur = q.top().second;
    q.pop();

    if (res.find(cur) != res.end()) continue;
    res[cur] = now - start_time;

    for (const auto& [to, times] : edges[cur]) {
      const auto next = times.upper_bound({now, now});
      if (next == times.end()) continue;
      q.emplace(next->second, to);
    }
  }
  return res;
}

std::unordered_set<stop> Schedule::stops() { return stops_; }
