#include "Counter_sec.h"

namespace chargeshot
{
	Counter_sec::Counter_sec(const float durationMax) :DURATION_MAX(durationMax)
	{

	}

	Counter_sec::~Counter_sec()
	{

	}

	float Counter_sec::GetProcessingRatio()
	{
		return m_duration / DURATION_MAX;
	}

	float Counter_sec::Update()
	{
		m_duration += m_rGameFramework.DeltaTime_sec();

		m_duration = min(m_duration, DURATION_MAX);

		return GetProcessingRatio();
	}

	void Counter_sec::Zero()
	{
		m_duration = 0.0f;
	}
}
