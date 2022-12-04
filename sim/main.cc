#include "schedule.h"
#include "evaluator.h"
#include "time.h"

#include <iostream>

int main(int argc, char** argv) {
  std::string sched = "sched.csv";
  std::string prof = "profile.csv";
  if (argc > 1) sched = std::string(argv[1]);
  if (argc > 2) prof = std::string(argv[2]);
  Schedule s(sched);
  Evaluator e(prof);
  std::cout << pretty_d(e.eval(s)) << std::endl;
}
