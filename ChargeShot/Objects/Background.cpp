#include "Background.h"

namespace chargeshot
{
	using namespace gameframework;

	Background::Background(const TCHAR* pTextureKey, const D3DXVECTOR2& scrolling_sec)
		:Object2D(pTextureKey), m_scrolling_sec(scrolling_sec)
	{
		FormVertices();
	}

	Background::~Background()
	{

	}

	void Background::Update()
	{
		Scroll();
	}

	void Background::Scroll()
	{
		m_textureUVsTopLeft += m_scrolling_sec * m_rGameFramework.DeltaTime_sec();

		RectSize textureSize(1.0f, 1.0f);
		TextureUVs textureUVs(m_textureUVsTopLeft, textureSize, textureSize, 1);

		m_pVertices->SetTextureUVs(textureUVs);
	}

	void Background::FormVertices()
	{
		m_textureUVsTopLeft = { 0.0f, 0.0f };

		D3DXVECTOR2 centerVector2 = WindowMeasure::GetNormalizeVector(50.0f);

		D3DXVECTOR3 centerVector3(centerVector2.x, centerVector2.y, 1.0f);

		m_pVertices->SetCenterAndSize(centerVector3, WindowMeasure::GetNormalize());
	}
}
