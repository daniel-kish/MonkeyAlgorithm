#pragma once
#include "common.h"
#include <random>
#include "Monkey.h"
#include <algorithm>
#include <fstream>

template <class T>
struct Less {
	bool operator()(Monkey<T> & l, Monkey<T> & r)
	{
		return l.lm.f(l.pos) < r.lm.f(r.pos);
	}
};

struct MonkeySearch {
	std::random_device rd;
	std::mt19937 mt{rd()};
	std::uniform_real_distribution<double> Ud{-5.0,5.0};

	double genUd() { return Ud(mt); };
	int dim = 2;// search space dimensions
	int S{3}; // number of monkeys
	std::vector<Monkey<Ras>> monkeys;
	int longMax = 20; // maximum of long (somersault) jumps
	double vmin{-0.5}, vmax{0.7}; 
	std::uniform_real_distribution<double> Uv{vmin,vmax};
	vec center; // the geometrical center of monkeys' positions
	vec best; // best monkey position

	MonkeySearch() : center(0.0, dim), best{}
	{
		for (int i = 0; i < S; ++i)
			monkeys.push_back(Monkey<Ras>(randVec(), Ras{}, dim));
		calcCenter();
		best = center;
	}

	void calcCenter()
	{
		std::fill(begin(center), end(center), 0.0);
		for (int i = 0; i < S; ++i)
		{
			center += monkeys[i].pos;
		}
		center /= S;
	}
	vec randVec()
	{
		vec v(dim);

		for (int i = 0; i < dim; ++i)
			v[i] = Ud(mt);
		return v;
	}
	void chooseBest()
	{
		auto now_best = std::max_element(begin(monkeys), end(monkeys), Less<Ras>{})->pos;
		if (monkeys.front().lm.f(now_best) > monkeys.front().lm.f(best))
			best = std::move(now_best);
	}
	void somersault()
	{
		calcCenter();
		for (auto& m : monkeys) {
			m.pos += Uv(mt)*(center - m.pos);
		}
		calcCenter();
	}
	void core()
	{
		std::ofstream os(R"(C:\Users\Daniel\Documents\Visual Studio 2015\Projects\MonkeyAlgorithm\convrgns.dat)");
		while (longMax--)
		{
			somersault();
			for (auto& m : monkeys) {
				m.exploreLocal();
			}
			chooseBest();
			
			os << 20 - longMax << ' ' << norm(best) << '\n';
		}
	}
};