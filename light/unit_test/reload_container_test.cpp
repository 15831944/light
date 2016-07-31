#include "stdafx.h"
#include "ReloadContainer.h"

#include <map>
#include <list>
#include <vector>
#include <deque>
#include <set>

static const int TEST_DATA_SIZE = 10;

TEST(ReloadContainer, MapTest)
{
	typedef std::map<int, int> CONTAINER;

	light::ReloadMappedContainer<CONTAINER> Reload;

	/// insert�� ���� ���� find �ص� ���ϴ� ������Ʈ�� ã������ �ʾƾ���. load���� �����̱� ����
	for( int i = 0; i < TEST_DATA_SIZE; ++i)
		Reload.insert(i, i);

	/// deploy�������� �����Ͱ� �����������Ѵ�.
	ASSERT_TRUE(Reload.empty());

	int n = 0, key = 5;
	ASSERT_FALSE(Reload.find(key, n));

	ASSERT_EQ(n, 0);
	ASSERT_FALSE(Reload[key]);

	/// ���� �����̳ʿ� �Ű� ��� ����
	Reload.deploy();

	/// deploy �Ŀ��� �����Ͱ� ã������ ���� �����Ѵ�.
	ASSERT_TRUE(Reload.find(key, n));
	ASSERT_EQ(n, 5);

	ASSERT_EQ(TEST_DATA_SIZE, Reload.size());
}

TEST(ReloadContainer, SetTest)
{
	typedef std::set<int> CONTAINER;

	light::ReloadContainer<CONTAINER> Reload;

	/// insert�� ���� ���� find �ص� ���ϴ� ������Ʈ�� ã������ �ʾƾ���. load���� �����̱� ����
	for( int i = 0; i < TEST_DATA_SIZE; ++i)
		Reload.insert(i);

	/// deploy�������� �����Ͱ� �����������Ѵ�.
	ASSERT_TRUE(Reload.empty());

	int val = 5;
	ASSERT_FALSE(Reload.find(val));

	/// ���� �����̳ʿ� �Ű� ��� ����
	Reload.deploy();

	/// deploy �Ŀ��� �����Ͱ� ã������ ���� �����Ѵ�.
	ASSERT_TRUE(Reload.find(val));

	ASSERT_EQ(TEST_DATA_SIZE, Reload.size());
}

TEST(ReloadContainer, ListTest)
{
	typedef std::list<int> CONTAINER;

	light::ReloadContainer<CONTAINER> Reload;

	/// insert�� ���� ���� find �ص� ���ϴ� ������Ʈ�� ã������ �ʾƾ���. load���� �����̱� ����
	for( int i = 0; i < TEST_DATA_SIZE; ++i)
		Reload.push_back(i);

	/// deploy�������� �����Ͱ� �����������Ѵ�.
	ASSERT_TRUE(Reload.empty());

	/// ���� �����̳ʿ� �Ű� ��� ����
	Reload.deploy();

	/// deploy �Ŀ��� �����Ͱ� ã������ ���� �����Ѵ�.
	ASSERT_EQ(TEST_DATA_SIZE, Reload.size());

	const CONTAINER& container = Reload;
	ASSERT_EQ(container.size(), Reload.size());
}

TEST(ReloadContainer, DequeTest)
{
	typedef std::deque<int> CONTAINER;

	light::ReloadContainer<CONTAINER> Reload;

	/// insert�� ���� ���� find �ص� ���ϴ� ������Ʈ�� ã������ �ʾƾ���. load���� �����̱� ����
	for( int i = 0; i < TEST_DATA_SIZE; ++i)
		Reload.push_back(i);

	/// deploy�������� �����Ͱ� �����������Ѵ�.
	ASSERT_TRUE(Reload.empty());

	int n = 0, val = 5;
	ASSERT_FALSE(Reload.at(val, n));
	ASSERT_EQ(n, 0);

	/// ���� �����̳ʿ� �Ű� ��� ����
	Reload.deploy();

	/// deploy �Ŀ��� �����Ͱ� ã������ ���� �����Ѵ�.
	ASSERT_TRUE(Reload.at(val, n));
	ASSERT_EQ(n, 5);

	ASSERT_EQ(TEST_DATA_SIZE, Reload.size());
}

TEST(ReloadContainer, VectorTest)
{
	typedef std::vector<int> CONTAINER;

	light::ReloadContainer<CONTAINER> Reload;

	/// insert�� ���� ���� find �ص� ���ϴ� ������Ʈ�� ã������ �ʾƾ���. load���� �����̱� ����
	for( int i = 0; i < TEST_DATA_SIZE; ++i)
		Reload.push_back(i);

	/// deploy�������� �����Ͱ� �����������Ѵ�.
	ASSERT_TRUE(Reload.empty());

	int n = 0, val = 5;
	ASSERT_FALSE(Reload.at(val, n));
	ASSERT_EQ(n, 0);

	/// ���� �����̳ʿ� �Ű� ��� ����
	Reload.deploy();

	/// deploy �Ŀ��� �����Ͱ� ã������ ���� �����Ѵ�.
	ASSERT_TRUE(Reload.at(5, n));
	ASSERT_EQ(n, 5);

	ASSERT_EQ(TEST_DATA_SIZE, Reload.size());
}

