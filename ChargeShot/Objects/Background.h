#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Object2D.h"
#include "WindowMeasure.h"

namespace chargeshot
{
	using gameframework::TextureUVs;

	class Background :public Object2D
	{
	public:
		Background(const TCHAR* pTextureKey = nullptr, const D3DXVECTOR2& scrolling_sec = D3DXVECTOR2(0.0f, 0.0f));

		virtual ~Background();

		void Update();

	protected:
		virtual void Scroll();

		D3DXVECTOR2 m_scrolling_sec;
		D3DXVECTOR2 m_textureUVsTopLeft;

	private:
		Background(const Background& background) = delete;
		Background& operator=(Background& background) = delete;

		void FormVertices();
	};
}

#endif // !BACKGROUND_H
