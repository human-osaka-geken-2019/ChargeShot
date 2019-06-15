#include "SceneSwitchMediator.h"

namespace chargeshot
{
	SceneSwitchMediator::~SceneSwitchMediator()
	{

	}

	void SceneSwitchMediator::RegisterReceiver(SwitchEvent* pSwitchEventPost)
	{
		m_pSwitchEventPosts.push_back(pSwitchEventPost);
	}

	void SceneSwitchMediator::UnregisterReceiver(SwitchEvent* pSwitchEventPost)
	{
		for (auto& rpPost : m_pSwitchEventPosts)
		{
			if (rpPost != pSwitchEventPost) continue;

			auto index = &rpPost - &m_pSwitchEventPosts[0];

			m_pSwitchEventPosts.erase(m_pSwitchEventPosts.begin() + index);

			return;
		}
	}

	void SceneSwitchMediator::SendSwitchEvent(SCENE_KIND nextSceneKind)
	{
		for (auto& rpPost : m_pSwitchEventPosts)
		{
			rpPost->m_nextSceneKind = nextSceneKind;
			rpPost->m_shouldSwitch = true;
		}
	}

	SceneSwitchMediator::SceneSwitchMediator()
	{

	}
}
