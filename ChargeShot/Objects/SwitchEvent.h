#ifndef SWITCH_EVENT_H
#define SWITCH_EVENT_H

#include "SceneKind.h"

namespace chargeshot
{
	struct SwitchEvent
	{
	public:
		SCENE_KIND m_nextSceneKind = SCENE_KIND::IN_GAME;

		bool m_shouldSwitch = false;
	};
}

#endif //!SWITCH_EVENT_H
