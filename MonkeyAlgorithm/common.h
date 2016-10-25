#pragma once
#include <valarray>
#include <iostream>

using vec = std::valarray<double>;

extern int NFunCalls;

template <class T> 
void print(T const& v) {
	for (const auto& e : v)
		std::cout << e << '\n';
}

template <class T>
inline T sq(T const& x) {
	return x*x;
}

double scp(vec const& l, vec const& r)
{
	return (l*r).sum();
}

double norm(vec const& v)
{
	return sqrt((v*v).sum());
}

template <class Gen>
vec randVec(int n, Gen& d)
{
	vec v(n);

	for (int i = 0; i < n; ++i)
		v[i] = d();
	return v;
}

template <class T>
bool stagnates(T const& v, int stagLen = 5, double eps=0.001)
{
	if (v.size() < stagLen)
		return false;

	// read last 'stagLen' results
	// if they are in 'eps' gap -> out
	double last = v.back();
	double top{ last + eps }, bot{ last - eps };
	auto p = v.crbegin();

	for (int i{1}; i != stagLen; ++i, ++p)
		if (!(*p > bot && *p < top)) // not in the eps gap
			return false;
	return true;
}

struct Ras {
	double operator()(vec const& x)
	{
		NFunCalls++;
		static double Pi{ 3.14 };
		static double A{ 10.0 };
		double sum{ A*x.size() };
		for (int i = 0; i < x.size(); ++i)
			sum += sq(x[i]) - A*cos(2.0*Pi*x[i]);
		return -sum;
	}
};