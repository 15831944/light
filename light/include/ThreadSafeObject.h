#pragma once

namespace light
{

/**
@brief ������ �������ϰ� �����ϵ��� �ڷᱸ���� �������ִ� Ŭ����
*/
template <typename DataStructure, typename SyncObject>
class ThreadSafeObject
{
public:
	/**
	@brief ������
	*/
	ThreadSafeObject()
	{
	}

	/**
	@brief �Ҹ���
	*/
	~ThreadSafeObject()
	{
	}

	/**
	@brief ������ �߰� �޼ҵ�
	@param �߰��� ������
	*/
	template <typename T>
	void add(const T& Object)
	{
		m_SyncObject.lock();
		m_DataStructure.push_back(Object);
		m_SyncObject.unlock();
	}

	/**
	@brief ������ ���� �޼ҵ�
	@param ������ ������
	*/
	template <typename T>
	bool remove(const T& Object)
	{
		m_SyncObject.lock();
		DataStructure::iterator it = find(m_DataStructure.begin(), m_DataStructure.end(), Object);
		if(it == m_DataStructure.end())
		{
			m_SyncObject.unlock();
			return false;
		}
		m_DataStructure.erase(it);
		m_SyncObject.unlock();
		return true;
	}


	/**
	@brief ������ ������ �޼ҵ�
	@param Func ���۽�ų �Լ� ��ü
	*/
	template <typename T, typename Fuction>
	T* get(Fuction Func)
	{
		m_SyncObject.lock();
		for(DataStructure::iterator it = m_DataStructure.begin(); it != m_DataStructure.end(); ++it)
		{
			T& Object = *it;
			if(true == Func(Object))
			{
				m_SyncObject.unlock();
				return &Object;
			}
		}
		m_SyncObject.unlock();
		return NULL;
	}

	/**
	@brief ��� ��ȯ �޼ҵ� ȣ�� �޼ҵ�
	@param Func ���۽�ų �Լ� ��ü
	*/
	template <typename Fuction>
	void for_each(Fuction Func)
	{
		m_SyncObject.lock();
		for(auto it = m_DataStructure.begin(); it != m_DataStructure.end(); ++it)
		{
			Func(*it);
		}
		m_SyncObject.unlock();
	}

private:
	/// �ڷ� ����
	DataStructure m_DataStructure;

	/// ����ȭ ������ư
	SyncObject m_SyncObject;
};

} //namespace light
