#include <iostream>
#include "Monkey.h"
#include "common.h"
#include <cassert>
#include <algorithm>
#include "MonkeySearch.h"
#include <tuple>
#include <fstream>
//struct Ras {
//	double operator()(vec const& x)
//	{
//		static double Pi{ 3.14 };
//		static double A{ 10.0 };
//		double sum{ A*x.size() };
//		for (int i = 0; i < x.size(); ++i)
//			sum += sq(x[i]) - A*cos(2.0*Pi*x[i]);
//		return -sum;
//	}
//};
//
//struct Spherical {
//	vec x0;
//	Spherical(vec x) : x0(x)
//	{}
//	double operator()(vec const& x)
//	{
//		double sum{};
//		for (int i = 0; i < x.size(); ++i)
//			sum += -sq(x[i] - x0[i]);
//		return sum;
//	}
//};


using namespace std;
int main()
{
	MonkeySearch ms;
	ms.core();

	print(ms.best);

	//std::cout << '\n' << NFunCalls << '\n';

	//std::ofstream os{R"(C:\Users\Daniel\Documents\Visual Studio 2015\Projects\MPILab\MonkeyAlgorithm\MonkeyAlgorithm\results\plot4.dat)"};
	//if (!os)
	//{
	//	std::cerr << "error\n";
	//	exit(1);
	//}
	//
	//
	/*for (double v = 0.1; v <= 1.0; v += 0.1)
	{	
		int n = 8;
		vec avX(2);
		vec bestX(2);
		double avF = 0.0;
		double bestF = -150.0;
		while (n--) {
			MonkeySearch ms;
			ms.vmax = v;
			ms.vmin = -v;
			ms.core();

			double f = Ras{}(ms.best);
			avX += ms.best;
			avF += f;
			if (f > bestF) {
				bestF = f;
				bestX = ms.best;
			}
			std::cout << n << ' ';
		}
		os << v << ' ' << bestF << ' ' << norm(bestX) << ' ';
		os << avF << ' ' << norm(avX) << '\n';*/
	//}
	//int dim = 20;
	//std::random_device rd;
	//std::mt19937 mt{rd()};
	//std::uniform_real_distribution<double> Ud{ -0.4,0.4 };
	//
	//SPSA<Ras> lm(Ras{ }, dim, 0.05, 0.05);
	//vec x(dim);
	//for (int i = 0; i < dim; ++i)
	//	x[i] = Ud(mt);
	//
	//x = lm.go(std::move(x));
	//
	//std::cout << '\t' << norm(x) << '\n';
	//print(x);

}