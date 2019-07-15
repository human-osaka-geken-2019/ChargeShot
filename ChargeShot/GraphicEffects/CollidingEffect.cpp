#include "CollidingEffect.h"

namespace chargeshot
{
	using namespace gameframework;

	CollidingEffect::CollidingEffect(const D3DXVECTOR3& occurencePosition)
	{
		for (int i = 20; i > 0; --i)
		{
			m_partScheduler.Register(new DiffuseDifferenceSquare(_T("PLAYER"), 1.5f, 0.15f, rand() % 20, Color(0xFF23FFFF), Color(0xFFFF23FF), occurencePosition));
		}
	}

	CollidingEffect::~CollidingEffect()
	{

	}

	void CollidingEffect::Update()
	{
		UpdateParts();

		if (!m_partScheduler.IsEnd()) return;

		m_isEnd = true;
	}
}
