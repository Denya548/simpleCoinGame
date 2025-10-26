#include "Functions.hpp"

float Functions::length(int x, int y, int x1, int y1){
	return sqrt(pow(x1 - x, 2) + pow(y1 - y, 2));
};
