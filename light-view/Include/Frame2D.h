#pragma once

#include "Rectangle.h"

namespace light
{

namespace view
{

/**
@brief ���̾� ���� ���������� �Դϴ�. �ؽ����� ��ġ ������ �Էµ˴ϴ�.
*/
class Frame2D
{
public:
	typedef WORD NO;

public:
	Frame2D();

	Frame2D(const COLORS_FLOAT& color, const light::RECT_FLOAT& uv, const light::RECT_FLOAT& rect, const float rotate);

	virtual ~Frame2D();

	COLORS_FLOAT Color() const;

	void Color(const COLORS_FLOAT& color);

	light::RECT_FLOAT UV() const;
	
	void UV(const light::RECT_FLOAT& rect);

	light::RECT_FLOAT Rect() const;

	void Rect(const light::RECT_FLOAT& rect);

	light::RECT_FLOAT OriginalRect() const;

	void OriginalRect(const light::RECT_FLOAT& rect);

	float Rotate() const;

	void Rotate(const float rotate);

private:
	float m_rotate;

	COLORS_FLOAT m_color;
	
	light::RECT_FLOAT m_uv;

	light::RECT_FLOAT m_rect;

	light::RECT_FLOAT m_original_rect;
};

} // namespace view

} // namespace view
