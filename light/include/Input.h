#pragma once

#include "Singleton.h"
#include "Position.h"

namespace light
{

namespace Input
{

class Mouse
{
public:
	static void Pos(const light::POSITION_INT& pos);

	static light::POSITION_INT& Pos();

	static void LButtonClickPos(const light::POSITION_INT& pos);

	static light::POSITION_INT& LButtonClickPos();

	static void RButtonClickPos(const light::POSITION_INT& pos);

	static light::POSITION_INT& RButtonClickPos();

	static void LButtonClick(const bool flag);

	static bool LButtonClick();

	static void RButtonClick(const bool flag);

	static bool RButtonClick();

	static void LButtonDoubleClick(const bool click);

	static bool LButtonDoubleClick();

	static void RButtonDoubleClick(const bool click);

	static bool RButtonDoubleClick();

	static void Wheel(const int nWheel);

	static int Wheel();

public:
	static void reset();

private:
	/// ���콺 ��ġ
	static light::POSITION_INT m_os;

	/// ��Ŭ���� ��ġ
	static light::POSITION_INT m_LButtonClickPos;

	/// ����Ŭ���� ��ġ
	static light::POSITION_INT m_RButtonClickPos;

	/// ���콺 ���� ��ư
	static bool m_LButtonClick;

	/// ���콺 ������ ��ư
	static bool m_RButtonClick;

	/// ���콺 ���� ����Ŭ��
	static bool m_LButtonDoubleClick;

	/// ���콺 ������ ����Ŭ��
	static bool m_RButtonDoubleClick;

	/// ���콺 ��
	static int m_Wheel;
};

class Keyboard
{
public:
	static const int MAX_KEY = 256;

public:
	static void Up(int key);

	static void Down(int key);

public:
	static bool Pressing(int key);

public:
	static void reset();

private:
	static std::vector<bool> m_key;
};

} // namespace Input

} //namespace light
