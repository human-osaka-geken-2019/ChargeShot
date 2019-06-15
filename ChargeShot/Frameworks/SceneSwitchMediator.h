#ifndef SCENE_SWITCH_MEDIATOR_H
#define SCENE_SWITCH_MEDIATOR_H

#include <tchar.h>
#include <vector>

#include <GameFramework.h>

#include "SceneKind.h"
#include "SwitchEvent.h"

namespace chargeshot
{
	using gameframework::Singleton;

	class SceneSwitchMediator :public Singleton<SceneSwitchMediator>
	{
	public:
		friend Singleton<SceneSwitchMediator>;

		~SceneSwitchMediator();

		void RegisterReceiver(SwitchEvent* pSwitchEventPost);

		void UnregisterReceiver(SwitchEvent* pSwitchEventPost);

		void SendSwitchEvent(SCENE_KIND nextSceneKind);

	private:
		SceneSwitchMediator();

		SceneSwitchMediator(const SceneSwitchMediator& sceneSwitchMediator) = delete;
		SceneSwitchMediator& operator=(const SceneSwitchMediator& sceneSwitchMediator) = delete;

		std::vector<SwitchEvent*> m_pSwitchEventPosts;
	};
}

#endif //!SCENE_SWITCH_MEDIATOR_H
