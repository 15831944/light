#include "light-view.h"
#include "Polygon2D.h"
#include "DirectX.h"
#include "TextureManager.h"

namespace light
{

namespace view
{

Polygon2D::Polygon2D()
: m_width(0)
, m_height(0)
{
}


/**
@brief ������
*/
Polygon2D::Polygon2D(light::weak_raw_ptr<DirectX> directX)
: m_direct_x(directX)
, m_width(0)
, m_height(0)
{
}

/**
@brief ���� ������
@param polygon ������ ��ü
*/
Polygon2D::Polygon2D(const Polygon2D& polygon)
: m_width(polygon.m_width)
, m_height(polygon.m_height)
, m_texture(polygon.m_texture)
, m_direct_x(polygon.m_direct_x)
{
	for(int i = 0; i < _countof(m_vertex_data); i++)
		m_vertex_data[i] = polygon.m_vertex_data[i];
}

/**
@brief �Ҹ���
*/
Polygon2D::~Polygon2D()
{
	Release();
}


/**
@brief ���� ������.
*/
const Polygon2D& Polygon2D::operator = (const Polygon2D& polygon)
{
	UNREFERENCED_PARAMETER(polygon);
	return *this;
}

/**
@brief �ؽ��� �ε� �Լ�. 
@param strName �ؽ��� ���� ��
@param DWORD dwColorKey �÷�Ű
*/
bool Polygon2D::LoadTexture(const std::wstring& strName, DWORD dwColorKey)
{
	if ( true == strName.empty() )
	{
		//Just create with out texture.
		m_width = 32;
		m_height = 32;
	}
	else
	{
		
		m_texture = m_direct_x->TextureMgr()->Load(strName, dwColorKey);
		if( NULL == m_texture.get())
		{
			LOG_ERROR(L"%s [%s]", __FUNCTIONW__, strName.c_str());
			return false;
		}

		if( m_texture.get() == m_direct_x->TextureMgr()->NullTexture() )
		{
			LOG_ERROR(L"%s [%s] Not Load. this is NullTexture.", __FUNCTIONW__, strName.c_str());
		}

		// Getting texture size information.3
		m_width = m_texture->GetWidth();
		m_height = m_texture->GetHeight();
	}

	reset();
	return true;
}


void Polygon2D::SetDirectX(light::weak_raw_ptr<DirectX> directX)
{
	m_direct_x = directX;
}

/**
@brief �ʱ� �� ���� �޼ҵ�
*/
void Polygon2D::reset()
{
	for ( int i = 0;i < _countof(m_vertex_data);i++ )
	{
		m_vertex_data[i].color = D3DCOLOR_RGBA(255,255,255,255);
	}

	// Vertex A1 puts position data.
	m_vertex_data[0].x	= 0;
	m_vertex_data[0].y	= 0;
	m_vertex_data[0].z	= 0.5f;
	m_vertex_data[0].rhw	= 1.0f;
	m_vertex_data[0].tu	= 0.0f;
	m_vertex_data[0].tv	= 0.0f;
	// Vertex A2 puts position data.
	m_vertex_data[1].x	= (float)m_texture->GetWidth();
	m_vertex_data[1].y	= 0;
	m_vertex_data[1].z	= 0.5f;
	m_vertex_data[1].rhw	= 1.0f;
	m_vertex_data[1].tu	= 1.0f;
	m_vertex_data[1].tv	= 0.0f;
	// Vertex A3 puts position data.
	m_vertex_data[2].x	= (float)m_texture->GetWidth();
	m_vertex_data[2].y	= (float)m_texture->GetHeight();
	m_vertex_data[2].z	= 0.5f;
	m_vertex_data[2].rhw	= 1.0f;
	m_vertex_data[2].tu	= 1.0f;
	m_vertex_data[2].tv	= 1.0f;
	// Vertex A4 puts position data.
	m_vertex_data[3].x	= 0;
	m_vertex_data[3].y	= (float)m_texture->GetHeight();
	m_vertex_data[3].z	= 0.5f;
	m_vertex_data[3].rhw	= 1.0f;
	m_vertex_data[3].tu	= 0.0f;
	m_vertex_data[3].tv	= 1.0f;
}

/**
@brief ȭ�鿡 �ؽ��ĸ� �׷��ִ� �޼ҵ�. ������ ��ȯ�� �ʿ��ϴ�. you can do everything transform!
@param Rect Rect
@param Uv �ؽ��� ���� UV ��ǥ
@param Mirror �¿� ���� ����
@param fRot ȸ�� ��
*/
void Polygon2D::Blt(const light::RECT_FLOAT& Rect, const light::RECT_FLOAT& Uv, const bool Mirror, float fRot /* = 0.0f */)
{	
	light::RECT_FLOAT fTempRt;

	// �ȼ��迭���� �ۼ������� �迭�� ��ȯ
	fTempRt.Left((float)(1*Uv.Left()/m_width));
	fTempRt.Top((float)(1*Uv.Top()/m_height));
	fTempRt.Right((float)(1*Uv.Right()/m_width));
	fTempRt.Bottom((float)(1*Uv.Bottom()/m_height));

	// �߽����� ���Ѵ�	
	float wid = Rect.Right() / 2.0f;
	float hei = Rect.Bottom() / 2.0f;
	if (fRot != 0.0f)
	{
		light::POSITION_FLOAT fRadian[4];
		for(int i = 0; i < 4; i++)
		{
			static const float fnumX[4] = {-1.0f, 1.0f, 1.0f, -1.0f};
			static const float fnumY[4] = {-1.0f, -1.0f, 1.0f, 1.0f};

			double foundangle = 0;
			// ������ ��ġ�� ��� --, +-, ++, -+ ������
			fRadian[i].X(Rect.Left() + (wid * fnumX[i]));					
			fRadian[i].Y(Rect.Top() + (hei * fnumY[i]));

			// atan ���� �����ֱ� ���� ��ġ�� ���� ��������
			if(fRadian[i].Y() < Rect.Top())	
				foundangle = 180.0f;				
			else							
				foundangle = 0.0f;		

			// ���� ���� ���� Rectition�� 10, 10���� �ʱⰪ�� �Ǿ� �ִ� 
			// �� Rectition�� �߽����� (0, 0)���� ���߱� ����
			fRadian[i] -= Rect.LeftTop();											

			// �Ÿ� ���
			float v = (float)sqrt(fRadian[i].X() * fRadian[i].X() + fRadian[i].Y() * fRadian[i].Y());

			// ���� ���
			double temp_angle = (float)atan((float)fRadian[i].X() / fRadian[i].Y()) * 180.0f / 3.14159;

			// Radian�� ��� 
			float r = (float)(((temp_angle - fRot + foundangle)  / 180.0f) * 3.14159);

			// ���� ���� ���ؼ� ��ǥ�� ���
			fRadian[i].X(v * sin(r));
			fRadian[i].Y(v * cos(r));

			// ������ ��ġ�� ���� �ֱ� ���� ������ ��ǥ ���� �� ���̸� ���Ѵ�.
			fRadian[i].X( fRadian[i].X() + Rect.Left() + wid);
			fRadian[i].Y( fRadian[i].Y() + Rect.Top() + hei);
		}

		m_vertex_data[0].x = fRadian[0].X() + 0.5f;
		m_vertex_data[0].y = fRadian[0].Y() + 0.5f;
		m_vertex_data[1].x = fRadian[1].X();
		m_vertex_data[1].y = fRadian[1].Y();
		m_vertex_data[2].x = fRadian[2].X();
		m_vertex_data[2].y = fRadian[2].Y();
		m_vertex_data[3].x = fRadian[3].X();
		m_vertex_data[3].y = fRadian[3].Y();
	}
	else
	{
		m_vertex_data[0].x =	Rect.Left() - 0.5f;
		m_vertex_data[0].y =	Rect.Top() - 0.5f;
		m_vertex_data[1].x =	m_vertex_data[0].x + Rect.Right();
		m_vertex_data[1].y =	m_vertex_data[0].y;
		m_vertex_data[2].x =	m_vertex_data[0].x + Rect.Right();
		m_vertex_data[2].y =	m_vertex_data[0].y + Rect.Bottom();
		m_vertex_data[3].x =	m_vertex_data[0].x;
		m_vertex_data[3].y =	m_vertex_data[0].y + Rect.Bottom();
	}

	if(Mirror)
	{
		m_vertex_data[0].tu = fTempRt.Right();
		m_vertex_data[0].tv = fTempRt.Top();
		m_vertex_data[1].tu = fTempRt.Left();
		m_vertex_data[1].tv = fTempRt.Top();
		m_vertex_data[2].tu = fTempRt.Left();
		m_vertex_data[2].tv = fTempRt.Bottom();
		m_vertex_data[3].tu = fTempRt.Right();
		m_vertex_data[3].tv = fTempRt.Bottom();
	}
	else
	{
		m_vertex_data[0].tu = fTempRt.Left();
		m_vertex_data[0].tv = fTempRt.Top();
		m_vertex_data[1].tu = fTempRt.Right();
		m_vertex_data[1].tv = fTempRt.Top();
		m_vertex_data[2].tu = fTempRt.Right();
		m_vertex_data[2].tv = fTempRt.Bottom();
		m_vertex_data[3].tu = fTempRt.Left();
		m_vertex_data[3].tv = fTempRt.Bottom();
	}

	if ( fRot != 0.0f || 
		(Rect.Right() != m_width || Rect.Bottom() != m_height) || 
		(Uv.Right() != m_width || Uv.Bottom() != m_height) ) // ����� �ٲ�����
	{
		DrawTexture(true);
	}
	else
	{
		DrawTexture(false);
	}
}

/**
@brief ȭ�鿡 �׷��ִ� �޼ҵ�
@param bBlur �� �޼ҵ�
*/
void Polygon2D::DrawTexture(bool bBlur /* = false */)
{
	/// ���� ���� ��
	m_direct_x->DxDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true );

	// turn on rander when use the screen effect.
	m_direct_x->DxDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_direct_x->DxDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// in case of broken texture should be turn on the blur effect.
	if ( false == bBlur )
	{
		m_direct_x->DxDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_NONE);
		m_direct_x->DxDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE);
	}
	else
	{
		m_direct_x->DxDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	}

	// Set this texture to D3Ddev.
	m_direct_x->DxDevice()->SetTexture(0, m_texture->GetTexture());

	// Draw up the screen. DrawPrimitiveUP() - ���� ���۸� ������� �ʰ� ���� Rendering  
	m_direct_x->DxDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertex_data, sizeof(Vertex2D));

	m_direct_x->DxDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

/**
@brief �ؽ����� ���Ŀ� RGB �÷��� �����Ѵ�.
*/
void Polygon2D::SetTransformColor(const COLORS_FLOAT& color)
{
	for (int i = 0;i < _countof(m_vertex_data); i++)
	{
		m_vertex_data[i].color = color.RGBA();
	}
}

/**
@brief Clean-up all polygon and texture data.
*/
void Polygon2D::Release()
{
	ReleaseTexture();
}

/**
@brief Clean-up all Texture data.
*/
void Polygon2D::ReleaseTexture()
{
	m_texture.release();
}

} // namespace view

} // namespace view
