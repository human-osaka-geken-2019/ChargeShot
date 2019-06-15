#include "QuakeCounter_sec.h"

namespace chargeshot
{
	using namespace gameframework::algorithm;

	QuakeCounter_sec::QuakeCounter_sec(const float durationMax) :Counter_sec(durationMax)
	{

	}

	QuakeCounter_sec::~QuakeCounter_sec()
	{

	}

	float QuakeCounter_sec::Update()
	{
		m_duration += Tertiary(m_shouldIncreased, +1.0f, -1.0f) * m_rGameFramework.DeltaTime_sec();

		NormalizeWithinRange();

		return GetProcessingRatio();
	}

	void QuakeCounter_sec::NormalizeWithinRange()
	{
		if (0 <= m_duration && m_duration <= DURATION_MAX) return;

		float exceeding = m_duration - Tertiary(m_shouldIncreased, DURATION_MAX, 0.0f);

		m_duration -= exceeding;

		m_shouldIncreased = !m_shouldIncreased;

		NormalizeWithinRange();
	}
}
