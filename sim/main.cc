#include "schedule.h"
#include "evaluator.h"
#include "time.h"

#include <iostream>

int main(int argc, char** argv) {
  std::string sched = "sched.csv";
  std::string trips = "trips.csv";
  if (argc > 1) sched = std::string(argv[1]);
  if (argc > 2) trips = std::string(argv[2]);
  Schedule s(sched);
  Evaluator e(trips);
  std::cout << pretty_d(e.eval(s)) << std::endl;
}
