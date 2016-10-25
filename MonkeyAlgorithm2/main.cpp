#include <iostream>
#include <random>
#include <valarray>
#include <string>
#include <algorithm>
#include <iomanip>
#include <map>
#include <fstream>

const double pi = 3.1415926535897932384626433832795;

std::random_device rd;
std::mt19937 mt{rd()};
std::normal_distribution<double> N_coord{0.0,1.0};
std::bernoulli_distribution coin{0.5};

int U_balance()
{
	bool v = coin(mt);
	if (v)
		return 1;
	return -1;
}

template <class Vec>
Vec U_vecInSphere(int dim)
{
	Vec v(dim);
	std::generate(begin(v), end(v), []() { return N_coord(mt); });
	v /= sqrt((v*v).sum());
	return v;
}

using vec = std::valarray<double>;
double sq(double x) { return x*x; }
double norm(vec const& v) { return sqrt((v*v).sum()); }
std::ostream& operator << (std::ostream& os, std::valarray<double> v)
{
	os << '[' << ' ';
	for (const auto& e : v)
		os << e << ' ';
	return os << ']';
}

struct SphericalFun {
	int n{0};
	vec x0;
	SphericalFun(vec x) : x0(x)
	{}
	double operator()(vec const& x)
	{
		double sum{};
		for (unsigned i = 0; i < x.size(); ++i)
			sum += sq(x[i] - x0[i]);
		n++;
		return sum;
	}
};

double get_a_k(int k, double a, double A, double alpha)
{
	return a / pow(A + k, alpha);
}
double get_c_k(int k, double c, double gamma)
{
	return c / pow(k, gamma);
}

struct spsa_params {
	double a, c, A, alpha, gamma;
};

template <class Fun>
vec spsa(Fun& f, vec x, int k_max, spsa_params const& pars)
{
	const auto dim = x.size();

	vec psi(dim);
	vec prev(x);

	for (int k = 1; k <= k_max; ++k)
	{
		std::generate(std::begin(psi), std::end(psi), U_balance);
		double c_k = get_c_k(k, pars.c, pars.gamma);
		double f_plus = f(x + c_k*psi);
		double f_minus = f(x - c_k*psi);

		//pow(psi, -1.0);
		double delta_f = (f_plus - f_minus) / (2.0*c_k);
		psi *= delta_f; // from now on it's a pseudograd

		double a_k = get_a_k(k, pars.a, pars.A, pars.alpha);
		x -= a_k*psi;

		auto dx = norm(x - prev);
		if (dx < 0.01 && dx != 0.0)
			break;
		else
			prev = x;
	}
	return x;
}

int main()
{
	using namespace std;

	int dim = 10;
	SphericalFun f(vec(0.0, dim));
	spsa_params pars = {1.0,1.0,1.0,1.0,1.0};
	ofstream x_os{R"(C:\Users\Daniel\Documents\Visual Studio 2015\Projects\MonkeyAlgorithm\MonkeyAlgorithm\results\conv_x.dat)"};
	ofstream f_os{R"(C:\Users\Daniel\Documents\Visual Studio 2015\Projects\MonkeyAlgorithm\MonkeyAlgorithm\results\conv_f.dat)"};

	pars.a = 0.1;
	pars.A = 0.1;
	pars.alpha = 1.0;
	pars.gamma = 1.0;

	cout << spsa(f, vec(5.0, dim), 1000, pars) << '\n';
	cout << f.n << '\n';

	//for (double c = 0.001; c <= 0.5; c += 0.001) {
	//	int n{100};
	//	vec aver(0.0, dim);
	//	int f_n_aver{0};
	//	pars.c = c;
	//	while (n--) {
	//		auto sol = spsa(f, vec(5.0, dim), 1000, pars);
	//		aver += sol;
	//		f_n_aver += f.n; f.n = 0;
	//	}
	//	aver /= 100;
	//	x_os << c << ' ' << norm(aver) << '\n';
	//	f_os << c << ' ' << double(f_n_aver) / 100.0 << '\n';
	//}



}

