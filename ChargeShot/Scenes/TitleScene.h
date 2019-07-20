#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "Background.h"
#include "Player.h"
#include "PointChecker.h"
#include "PointTextCreater.h"
#include "Scene.h"
#include "Target.h"
#include "FlashText.h"
#include "GameTitle.h"
#include "HighScoreText.h"

namespace chargeshot
{
	class TitleScene :public Scene
	{
	public:
		TitleScene();
		~TitleScene();

	private:
		TitleScene(const TitleScene& titleScene) = delete;
		TitleScene& operator=(TitleScene& titleScene) = delete;

		void Initialize()override;
		void Finalize()override;

		void LoadResouces()override;
	};
}

#endif //!TITLE_SCENE_H
