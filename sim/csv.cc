#include "csv.h"

std::vector<std::string> split(const std::string& s) {
  static const char DELIM = ',';

	std::vector<std::string> res;
	size_t start = 0;
	size_t finish = -1;
	while ((finish = s.find(DELIM, start)) != std::string::npos) {
		res.push_back(s.substr(start, finish - start));
		start = finish + 1;
	}
	res.push_back(s.substr(start));
	return res;
}
