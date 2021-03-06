#include"../timer.h"
#include<fstream>
#include"../../include/fast_io_device.h"
//#include"../../include/fast_io_crypto.h"
#include"../../include/fast_io_legacy.h"
#include<exception>
#include<cmath>
#include<memory>
#include<cstdio>
#include<random>
#include<iomanip>
#include<charconv>

//standard library implementation is just too slow that wastes my time

int main()
try
{
	std::size_t constexpr N(10000000);
	std::vector<double> vec;
	vec.reserve(N);
	std::random_device device;
	std::mt19937_64 eng(device());
	std::uniform_real_distribution dis(-1000.0,1000.0);
	for(std::size_t i(0);i!=N;++i)
		vec.emplace_back(dis(eng));
	{
		fast_io::timer t("grisu exact");
		std::array<char,100> arr;
		fast_io::ospan osp(arr);
		for(auto const& e : vec)
		{
			osp.clear();
			print(osp,fast_io::grisu_exact(e));
		}
	}
	{
		fast_io::timer t("ryu");
		std::array<char,100> arr;
		fast_io::ospan osp(arr);
		for(auto const& e : vec)
		{
			osp.clear();
			print(osp,e);
		}
	}
	{
		fast_io::timer t("grisu exact");
		std::array<char,100> arr;
		fast_io::ospan osp(arr);
		for(auto const& e : vec)
		{
			osp.clear();
			print(osp,fast_io::grisu_exact(e));
		}
	}
}
catch(std::exception const& e)
{
	perrln(e);
	return 1;
}
