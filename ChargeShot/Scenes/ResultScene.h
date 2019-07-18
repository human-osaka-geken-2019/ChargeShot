#ifndef RESULT_SCENE_H
#define RESULT_SCENE_H

#include "Background.h"

#include "ResultPointTextCreater.h"
#include "Scene.h"

namespace chargeshot
{
	class ResultScene :public Scene
	{
	public:
		ResultScene();
		~ResultScene();

	private:
		ResultScene(const ResultScene& resultScene) = delete;
		ResultScene& operator=(ResultScene& resultScene) = delete;

		void Initialize()override;
		void Finalize()override;

		void LoadResouces()override;
	};
}

#endif //!RESULT_SCENE_H
