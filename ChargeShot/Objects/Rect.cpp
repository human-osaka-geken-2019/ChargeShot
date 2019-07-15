#include "Rect.h"

namespace chargeshot
{
	using gameframework::Color;

	Rect::Rect(const TCHAR* pTextureKey)
		:Object2D(pTextureKey)
	{

	}

	Rect::~Rect()
	{
		Finalize();
	}

	void Rect::Update()
	{

	}

	void Rect::Finalize()
	{
		
	}
}
