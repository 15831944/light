#include "stdafx.h"
#include <algorithm>

#include "boost/function.hpp"

/*
[]      // lambda capture ����
()      // parameter list ����
{}      // body ����
()      // �̴� �� lambda �Լ��� ��������� ȣ���� ��
*/

template< typename T >
void fill(std::vector<int> & v, T done)
{
    int i = 0;
    while (!done())
    {
        v.push_back(i++);
    }
}

// http://devsw.tistory.com/197
// http://itguru.tistory.com/196
// http://egloos.zum.com/sweeper/v/3015035

TEST(lambda, capture_test)
{
    std::vector<int> stuff;
    fill(stuff, [&]()->bool { return stuff.size() >= 8; });

    std::array<int, 8> stuff_array;
    for (int n = 0; n < 8; ++n)
    {
        stuff_array[n] = n;
    }

    for_each(stuff.begin(), stuff.end(), [&](int i) {  ASSERT_EQ(stuff_array[i], i); });
}

template<typename TFunc>
void TemplateFunc(TFunc func)
{
    func();
};

TEST(lambda, parameter)
{
    auto func = [] {  };
    TemplateFunc(func);
}

boost::function<void()> FunctionReturn()
{
    return [] { std::cout << "���ѹα�~~~¦¦¦ ¦¦~~~" << std::endl; };
}

TEST(lambda, return)
{
    auto func = FunctionReturn();
    func();
}

TEST(lambda, vector)
{
    std::vector<boost::function<const char* ()> > v;

    v.push_back([] { return "���ѹα� "; });
    v.push_back([] { return "¦¦¦~~~¦¦~~~"; });
}

TEST(lambda, explicit_return)
{
    // �Ͻ��� Ÿ�� ��ȯ
    auto func1 = [] { return 3.14; };

    // ���� ��ȯ ������ �̿��� ����� ��ȯ�� Ÿ�� ���� ( [ -> (return type) ] )
    // �Ķ���Ͱ� ������ �ݵ�� �Ķ���� ����� ������ �־�� �Ѵ�
    auto func2 = []() -> float { return 3.14f; };

    // func2�� ��ȯ���� double Ÿ������ �߷еǾ���. �Ʒ� ��� �߻�
    // warning C4244: '�ʱ�ȭ ��' :
    //                  'double'���� 'float'(��)�� ��ȯ�ϸ鼭 �����Ͱ� �սǵ� �� �ֽ��ϴ�.
    //float f1 = func1();
    //ASSERT_EQ(3.14, f1);

    // ��������� float ��ȯ�߱⿡ OK
    float f2 = func2();
    ASSERT_EQ(3.14f, f2);
}


TEST(lambda, capture_reference)
{
    std::vector<int> v;
    for (int i = 0; i < 10; ++i)
    {
        v.push_back(i);
    }

    int evenCount = 0;

    // lambda �Լ�
    for_each(v.begin(), v.end(), [&evenCount](int n)
    {
        if (n % 2 == 0) { evenCount++; }
    });
}

TEST(lambda, copy_reference)
{
    std::vector<int> v;
    for (int i = 0; i < 10; ++i)
    {
        v.push_back(i);
    }

    int evenCount = 0;

    // lambda �Լ�
    for_each(v.begin(), v.end(), [evenCount](int n) mutable
    {
        if (n % 2 == 0) { evenCount++; }
    });
}

TEST(lambda, capture_multi)
{
    int a;
    short b;
    float c;
    char d;

    // a, d ������... b, c �����...
    auto func = [&a, b, c, &d] { std::cout << a << b << c << d; };
}

int g_evenCount = 0;

TEST(lambda, capture_global)
{
    std::vector<int> v;
    for (int i = 0; i < 10; ++i)
    {
        v.push_back(i);
    }

    // lambda �Լ�
    for_each(v.begin(), v.end(), [&](int n)
    {
        if (n % 2 == 0) { g_evenCount++; }
    });
}

class PrimeNumber
{
public:
    PrimeNumber()
    {
        m_primeList.push_back(1);
        m_primeList.push_back(2);
        m_primeList.push_back(5);
        m_primeList.push_back(7);

        // ...
    }

    void PrintPrimeNumbers() const
    {
        // this�� ĸ���� �Ϳ� �ָ�!!!
        for_each(m_primeList.begin(), m_primeList.end(), [this](int primeNumber)
        {
            _Print(primeNumber);
        });
    }

private:
    typedef std::vector<int> PrimeNumberList;
    PrimeNumberList m_primeList;

    void _Print(int primeNumber) const
    {
        std::cout << "The prime number : " << primeNumber << std::endl;
    }
};

TEST(lambda, capture_class)
{
    PrimeNumber pn;
    pn.PrintPrimeNumbers();
}