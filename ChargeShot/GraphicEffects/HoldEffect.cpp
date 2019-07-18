#include "HoldEffect.h"

namespace gameframework
{
	HoldEffect::HoldEffect(const D3DXVECTOR3& startPosition, const TCHAR* pTexturePath)
	{
		m_partScheduler.Register(new DiffuseDifferenceSquare(pTexturePath, 0.2f, 0.03f, 0, Color(0xFF23FFFF), Color(0xFFFF23FF), startPosition));
	}

	HoldEffect::~HoldEffect()
	{

	}

	void HoldEffect::Update()
	{
		UpdateParts();

		if (!m_partScheduler.IsEnd()) return;
		
		m_isEnd = true;
	}
}
