#include "ChargeEffect.h"

namespace chargeshot
{
	using namespace gameframework;

	ChargeEffect::ChargeEffect(const D3DXVECTOR3& occurencePosition, float radius, float radiusDifference, int requireFrameNum, int lifeLimit)
	{
		const int DFFUSE_EFFECT_NUM = 1;

		for (int i = DFFUSE_EFFECT_NUM; i > 0; --i)
		{
			m_partScheduler.Register(new ScalingFlashAbsorbedSquare(_T("CHARGE_METER"), 0.0f, 0.0f, 0, Color(0xFF23FFFF), Color(0xFFFF23FF),
				radius, radiusDifference, occurencePosition, requireFrameNum, lifeLimit));
		}
	}

	ChargeEffect::~ChargeEffect()
	{

	}

	void ChargeEffect::Update()
	{
		UpdateParts();

		if (!m_partScheduler.IsEnd()) return;

		m_isEnd = true;
	}
}
