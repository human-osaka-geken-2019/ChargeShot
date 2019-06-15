#include "Scene.h"

namespace chargeshot
{
	Scene::~Scene()
	{
		ReleaseResources();
	}

	Scene::Scene()
	{

	}

	void Scene::CreateTexture(const TCHAR* pTextureKey, const TCHAR* pTexturePath)
	{
		pTEXTURE_KEYs.push_back(pTextureKey);

		m_rGameFramework.CreateTexture(pTextureKey, pTexturePath);
	}

	void Scene::CreateFont(const TCHAR* pFontKey, const RectSize& fontSize, const TCHAR* pTexturePath)
	{
		pFONT_KEYs.push_back(pFontKey);

		m_rGameFramework.CreateFont(pFontKey, fontSize, pTexturePath);
	}

	void Scene::ReleaseResources()
	{
		m_rObjectIntegrator.ReleaseAll();

		for (auto& pKey : pTEXTURE_KEYs)
		{
			m_rGameFramework.ReleaseTexture(pKey);
		}

		for (auto& pFont : pFONT_KEYs)
		{
			m_rGameFramework.ReleaseFont(pFont);
		}
	}
}
