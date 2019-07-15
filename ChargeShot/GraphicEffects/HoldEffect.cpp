#include "HoldEffect.h"

namespace gameframework
{
	HoldEffect::HoldEffect(const D3DXVECTOR3& startPosition)
	{
		m_partScheduler.Register(new DiffuseDifferenceSquare(_T("中空き円"), 0.2f, 0.03f, 0, Color(0xFF23FFFF), Color(0xFFFF23FF), startPosition));
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
