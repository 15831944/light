#pragma once

#pragma warning ( push )
#pragma warning ( disable : 4819)
#include "boost/random.hpp"
#pragma warning ( pop )

namespace light
{

/**
@brief boost/random wrapping class.
@desc randEngine �� Distributions ������ http://www.boost.org/doc/libs/1_52_0/doc/html/boost_random/performance.html �� �����ϼ���. �ӵ��� ������ ���տ� ���� �ſ� ���̰� ���ϴ�.
*/
class BoostRandom
{
private:
	template <typename T, typename Distribution, typename randEngine>
	class Generator
	{
	public:
		Generator(size_t seed, const T min, const T max)
			: m_Generator(randEngine(seed), Distribution(min, max))
		{

		}

		Generator(const T min, const T max)
			: m_Generator(randEngine(), Distribution(min, max))
		{

		}

		T operator()()
		{
			return m_Generator();
		}

	private:
		boost::variate_generator<randEngine, Distribution> m_Generator;
	};

public:
	template <typename T, typename Distribution, typename randEngine = boost::mt19937>
	class seed
	{
	public:
		seed(const size_t seed = 0)
			: m_seed(seed)
		{

		}

		T rand(const T minimum, const T maximum)
		{
			T val = BoostRandom::rand<T, Distribution, randEngine>(m_seed, minimum, maximum);
			m_seed = (size_t)val; // �õ� ����. �̷��� �����, ���� ���� �ٲ�.
			return val;
		}

		void set(const size_t n)
		{
			m_seed = n;
		}

	private:
		size_t m_seed;
	};

	typedef seed<int, boost::uniform_int<> > SeedInt;

	typedef seed<double, boost::uniform_real<> > SeedDouble;

public: // public simple method.
	static int rand_int(const int minimum, const int maximum);

	static double rand_double(const double minimum, const double maximum);

public: // template rand method. if you choice randEngine and Distribution, use to this function.
	template <typename T, typename Distribution, typename randEngine>
	static T rand(const size_t seed, const T minimum, const T maximum)
	{
		if( false == valid(minimum, maximum) ) 
			return minimum;

		Generator< T, Distribution, randEngine > generator(seed, minimum, maximum);
		return generator();
	}

private:
	template <typename T>
	static bool valid(const T minimum, const T maximum)
	{
		if(minimum == maximum) // ���� ������ ���� �����ϸ�, ���� ������ ������. ��~ �׽�Ʈ ���غ����� �� �ɻ�...
			return false;

		return true;
	}
};

} // namespace light
