#include "SceneFader.h"

namespace chargeshot
{
	using gameframework::Color;

	const int SceneFader::FRAMES_TO_FADE_MAX = 60;

	bool SceneFader::m_stagingFinished = false;

	SceneFader::SceneFader()
		:Object2D(nullptr)
	{
		FormVertices();
	}

	SceneFader::~SceneFader()
	{
	
	}

	void SceneFader::Update()
	{
		FadeInOut();
	}

	void SceneFader::FadeInOut()
	{
		m_stagingFinished = false;

		if (m_fadeFrameCount <= FRAMES_TO_FADE_MAX / 2)
		{
			if (!m_shouldFadeOut)
			{
				m_stagingFinished = true;

				return;
			}
		}

		if (m_fadeFrameCount < 0)
		{
			m_stagingFinished = true;

			m_ends = true;

			return;
		}

		--m_fadeFrameCount;

		m_pVertices->Flash(FRAMES_TO_FADE_MAX, 255, 0);
	}

	void SceneFader::FormVertices()
	{
		D3DXVECTOR2 centerVector2 = WindowMeasure::GetNormalizeVector(50.0f);

		D3DXVECTOR3 centerVector3(centerVector2.x, centerVector2.y, 0.0f);

		m_pVertices->SetCenterAndSize(centerVector3, WindowMeasure::GetNormalize());

		m_pVertices->SetColor(0x00000000);
	}
}
