#pragma once

#include <Windows.h>
#include "Str.h"

namespace light
{
/**
@brief ������ �۷ι� ��Ű�� ���ϰ� �����ϴ� Ŭ����.
*/
class HotKey
{
public:
	/// ������ ���.
	typedef DWORD MODIFIER;

	/// ������ ��� ���� ����
	enum
	{
		MODIFIER_NONE = 0x0000,
		MODIFIER_ALT = MOD_ALT,
		MODIFIER_CONTROL = MOD_CONTROL,
		MODIFIER_SHIFT = MOD_SHIFT,
		MODIFIER_WIN = MOD_WIN,
	};

	/// ��Ű ���� ����ü
	struct INFORMATION
	{
	public:
		/**
		@breif ������
		*/
		INFORMATION()
			: m_Modifier(MODIFIER_NONE)
			, m_uVK(0)
		{
		}

		/**
		@breif ������
		@param Modifier ������
		@param uVK ����Ű �ڵ�
		*/
		INFORMATION(const MODIFIER Modifier, const UINT uVK)
			: m_Modifier(Modifier)
			, m_uVK(uVK)
		{
		}

		/**
		@breif �ʱ�ȭ �޼ҵ�
		*/
		void initialize()
		{
			m_Modifier = MODIFIER_NONE;
			m_uVK = 0;
		}

		/**
		@brief ���� ������
		@param rhs INFORMATIONŬ���� ������
		@return ���Ե� ��� Ŭ���� ������
		*/
		INFORMATION& operator=(const INFORMATION& rhs)
		{
			this->m_Modifier = rhs.m_Modifier;
			this->m_uVK = rhs.m_uVK;
			return *this;
		}

		/** 
		@brief �� ������
		@param Information Ű ����
		@return �� ���
		*/
		bool operator == (const INFORMATION& Information) const
		{
			return this->Modifier() == Information.Modifier() && this->VirtualKey() == Information.VirtualKey() ? true : false;
		}

		/**
		@brief ������ ��ȯ
		@return ������
		*/
		const MODIFIER Modifier() const
		{
			return m_Modifier;
		}

		/**
		@brief ���� Ű �ڵ� ��ȯ
		@return ���� Ű �ڵ�
		*/
		const UINT VirtualKey() const
		{
			return m_uVK;
		}

		/**
		@brief ���� �ִ� �������� ���Τ�
		@return ���� Ű �ڵ� ���� �ִ��� ����
		*/
		const bool Valid() const
		{
			return VirtualKey() != 0;
		}

	private:
		/// ������
		MODIFIER m_Modifier;

		/// ���� Ű �ڵ�
		UINT m_uVK;
	};

public:
/** 
	@brief �� ������ (==)
	@param Information Ű ����
	@return �� ���
	*/
	bool operator == (const INFORMATION& Information) const
	{
		return m_Information == Information ? true : false;
	}

	/** 
	@brief �� ������ (!=)
	@param Information Ű ����
	@return �� ���
	*/
	bool operator != (const INFORMATION& Information) const
	{
		return !operator==(Information);
	}

	/** 
	@brief �� ������ (==)
	@param hotkey ���� hotkey Ŭ���� ��ü
	@return �� ���
	*/
	bool operator == (const HotKey& hotkey) const
	{
		return m_Information == hotkey.m_Information ? true : false;
	}

	/** 
	@brief �� ������ (!=)
	@param hotkey ���� hotkey Ŭ���� ��ü
	@return �� ���
	*/
	bool operator != (const HotKey& Hotkey) const
	{
		return !operator==(Hotkey);
	}

public:
	/// ������.
	HotKey(const HWND& hWnd);

	/// �Ҹ���. 
	virtual ~HotKey();

	/// ��Ű ��� �޼ҵ�
	bool set(const INFORMATION& Information);

	/// ���� �ִ� ��Ű ��� �޼ҵ�
	bool set();

	/// ��Ű ��� ���� �޼ҵ�
	bool clear();

	/// ���� �ִ� ���� Ŭ���� �ϴ� �޼ҵ�
	bool Clear();

	/**
	@brief ��Ű ������ ���ڿ��� ��ȯ�ϴ� �޼ҵ�
	@return ��Ű ���� ���ڿ�
	*/
	const std::wstring String() const
	{
		return InformationToString(m_Information);
	}

	/**
	@brief ��Ű ���� ��ȯ
	@return ��Ű ����
	*/
	const INFORMATION& Information() const
	{
		return m_Information;
	}

	/**
	@brief ���� ������
	@param rhs HotKeyŬ���� ������
	@return ���Ե� ��� Ŭ���� ������
	*/
	HotKey& operator=(const HotKey& rhs)
	{
		m_Information = rhs.m_Information;
		return *this;
	}

	/**
	@brief ���� ������
	@param rhs INFORMATIONŬ���� ������
	@return ���Ե� ��� Ŭ���� ������
	*/
	HotKey& operator=(const INFORMATION& rhs)
	{
		m_Information = rhs;
		return *this;
	}

	/**
	@brief ����� �����ͷ� ��ȯ���ִ� �޼ҵ�
	@return ����� �����ͷ� ���ڵ�
	*/
	const std::wstring Encode() const
	{
		std::wstringstream strStream;
		strStream << m_Information.Modifier() << L"|" << m_Information.VirtualKey();
		return strStream.str();
	}

	/**
	@brief ����� �����͸� ���� �����ͷ� ��ȯ���ִ� �޼ҵ�
	@param str �����ߴ� ������
	*/
	void Decode(std::wstring& str)
	{
		MODIFIER Modifier = MODIFIER_NONE;
		UINT vk = 0;
		std::wstringstream strStream(str);
		WCHAR delimeter;
		strStream >> Modifier >> delimeter >> vk;
		INFORMATION Info(Modifier, vk);

		if(Info.Valid() != 0)
		{
			set(Info);
		}
	}

private:
	/// ��Ű ������ ���ڿ��� ��ȯ�ϴ� �޼ҵ�
	static std::wstring InformationToString(const INFORMATION& Information);

	/// �����ڸ� ���ڿ��� ��ȯ�ϴ� �޼ҵ�
	static std::wstringstream ModifierToString(const MODIFIER Modifier);

	/// ����Ű�� ���ڿ��� ��ȯ�ϴ� �޼ҵ�
	static std::wstring VirtualKeyToString(const UINT vk);

private:
	/// ������ ��Ʈ�� ID
	const DWORD m_ID;

	/// Ű ���� ����
	bool m_register;

	/// Ű ����
	INFORMATION m_Information;

	/// ������ �ڵ�
	const HWND m_hWnd;

	/// �������� ��Ʈ�� ID
	static DWORD m_CountableID;
};
} //namespace light
