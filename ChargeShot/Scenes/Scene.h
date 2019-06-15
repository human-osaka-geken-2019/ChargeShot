#ifndef SCENE_H
#define SCENE_H

#include <tchar.h>

#include <GameFramework.h>

#include "Object.h"
#include "ObjectIntegrator.h"

namespace chargeshot
{
	using gameframework::RectSize;
	using gameframework::GameFramework;

	class Scene
	{
	public:
		virtual ~Scene();

	protected:
		Scene();

		virtual void Initialize() = 0;
		virtual void Finalize() = 0;
		
		virtual void LoadResouces() = 0;

		void CreateTexture(const TCHAR* pTextureKey, const TCHAR* pTexturePath);

		void CreateFont(const TCHAR* pFontKey, const RectSize& fontSize, const TCHAR* pFontName);

		GameFramework& m_rGameFramework = GameFramework::CreateAndGetRef();

		ObjectIntegrator& m_rObjectIntegrator = ObjectIntegrator::CreateAndGetRef();
		
		std::vector<const TCHAR*> pTEXTURE_KEYs;
		std::vector<const TCHAR*> pFONT_KEYs;

	private:
		Scene(const Scene& scene) = delete;
		Scene& operator=(Scene& scene) = delete;

		void ReleaseResources();
	};
}

#endif //!SCENE_H
