#pragma once

#include <valarray>
#include <random>
#include "common.h"
#include <memory>

template <class Fun>
struct SPSA { // Simultaneous Perturbation Stochastic Approximation
	std::shared_ptr<std::random_device> rd{ new std::random_device{} };
	mutable std::mt19937 mt{ (*rd)() };
	std::uniform_int_distribution<int> U{0,1};
	std::uniform_real_distribution<double> Ud{ 0.8,1.2 };
	Fun f;
	double n;
	double lambda;
	double a;

	SPSA(Fun f_, double n_, double l=0.1, double a_=0.1) : f(f_), n(n_), lambda(l), a(a_)
	{}

	vec Psi() const
	{
		vec psi(n);
		for (int i = 0; i < n; ++i)
			psi[i] = a*((U(mt) == 0)? -1:1);
		return psi;
	}
	vec pseudoGrad(vec const& x)
	{
		vec pg(n);
		auto psi = Psi();
		for (int j = 0; j < n; ++j)
			pg[j] = (f(x + psi) - f(x - psi)) / 2.0*psi[j];
		return pg;
	}
	vec go(vec x)
	{
		//std::vector<double> res;
		// res.reserve(400);
		int maxTries = 10;
		double prev{f(x)};
		double f0{prev};
		int i{};
		double l{lambda};
		vec x0(x.size());
		while (maxTries--) {
			i++;
			x0 = x + lambda*pseudoGrad(x);
			f0 = f(x0);
			if (f0 > prev) {
				//res.push_back(norm(x0));
				x = x0;
				prev = f0;
			}
			else {
				lambda *= 0.9;
				continue;
			}
			//if (stagnates(res,10,0.00001))
			//	break;
		}
		//std::cout << "elapsed " << i << '\n';
		lambda = l;
		return x;
	}
};