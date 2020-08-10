#include <_Time.h>
#include <_File.h>
#include <random>

double pi(double u)
{
	double s(u - 0.5);
	return s * s;
}

double q(double u)
{
	double l;
	if (u > 0.5)l = 1 - u;
	else l = u;
	if (l > 0.05)return 0.1;
	else return l + 0.05;
}

double Qu(std::uniform_real_distribution<double>& rd, std::mt19937_64& mt)
{
	return rd(mt);
}

double Q(double u, std::uniform_real_distribution<double>& rd, std::mt19937_64& mt)
{
	if (rd(mt) < 0.1)
		return rd(mt);
	for (;;)
	{
		double t(u + (rd(mt) - 0.5) / 10);
		if (t >= 0 && t <= 1)return t;
	}
}

double mutation(double u, std::uniform_real_distribution<double>& rd, std::mt19937_64& mt)
{
	double v(Q(u, rd, mt));
	double alpha((pi(v) * q(u)) / (pi(u) * q(v)));
	if (alpha > rd(mt))return v;
	else return u;
}

int main()
{
	std::uniform_real_distribution<double> rd(0, 1);
	std::mt19937_64 mt(time(nullptr));
	String<char> str;
	str.malloc(21000 * 10);
	double u(0);
	char tp[16];
	::sprintf(tp, "%lf\n", u);
	str += tp;
	for (unsigned int c0(0); c0 < 20000; ++c0)
	{
		::sprintf(tp, "%lf\n", u = mutation(u, rd, mt));
		str += tp;
	}

	File file("./");
	file.createText("a.txt", str);
}