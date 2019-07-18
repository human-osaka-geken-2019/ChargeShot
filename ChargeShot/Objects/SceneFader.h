#ifndef SCENE_FADER_H
#define SCENE_FADER_H

#include <GameFramework.h>

#include "Object2D.h"
#include "WindowMeasure.h"

namespace chargeshot
{
	class SceneFader :public Object2D
	{
	public:
		SceneFader();

		virtual ~SceneFader();

		virtual void Update()override;

		virtual inline bool GetShouldFadeOut()
		{
			return m_shouldFadeOut;
		}

		virtual inline void SetShouldFadeOut(bool shouldFadeOut)
		{
			m_shouldFadeOut = shouldFadeOut;
		}

		virtual inline bool GetEnds()
		{
			return m_ends;
		}

		static inline bool GetStagingFinished()
		{
			return m_stagingFinished;
		}

		static const int FRAMES_TO_FADE_MAX;

	protected:
		virtual void FadeInOut();

		int m_fadeFrameCount = FRAMES_TO_FADE_MAX;

		bool m_shouldFadeOut = false;

		bool m_ends = false;

		static bool m_stagingFinished;

	private:
		SceneFader(const SceneFader& sceneFader) = delete;
		SceneFader& operator=(SceneFader& sceneFader) = delete;

		void FormVertices();
	};
}

#endif // !SCENE_FADER_H
