#pragma once
#include "localMinima.h"
#include "common.h"

template <class Fun>
struct Monkey {
	vec pos;
	SPSA<Fun> lm;
	int watchesMax{5};
	int watches{};
	double b{1.5};
	std::uniform_real_distribution<double> Uwj{-b,b};

	Monkey(vec init = vec{}, Fun f = Fun{}, int dim = int{})
		: pos(init), lm(f, dim, 0.05, 0.1)
	{}

	void climb()
	{
		pos = lm.go(std::move(pos)); // climb		
	}
	void watchJump()
	{
		vec tmp(pos);
		for (int i = 0; i < lm.n; ++i)
			pos[i] += Uwj(lm.mt);
		watches++;
		climb();
		if (lm.f(pos) < lm.f(tmp))
			pos = std::move(tmp);
	}
	void exploreLocal()
	{
		watches = 0;
		climb();
		while (watches <= watchesMax)
			watchJump();
		watches = 0;
	}
};
