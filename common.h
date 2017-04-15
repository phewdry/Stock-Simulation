#ifndef COMMON_H
#define COMMON_H

#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

class NormDstSampler {

public:

	double operator()(){
		do{
			x = 2.0*rand() / static_cast<double>(RAND_MAX)-1;
			y = 2.0*rand() / static_cast<double>(RAND_MAX)-1;
			xysquare = x*x + y*y;
		} while (xysquare >= 1.0);
		result = x*sqrt(-2 * log(xysquare) / xysquare);
		return result;
	}

private:

	double result;
	double x;
	double y;
	double xysquare;
};

// Definition of a simple matrix using vectors:

template <class T>
using matrix = std::vector<std::vector<T>>;

using size_t = unsigned int;

template <class T>
inline void
matrix_resize(T& u, size_t N, size_t M)
{
	// to make number of rows = N

	u.resize(N);

	// to make number of columns = M

	for (auto& row : u)
		row.resize(M);
}

#endif