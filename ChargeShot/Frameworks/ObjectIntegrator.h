#ifndef OBJECT_INTEGRATOR_H
#define OBJECT_INTEGRATOR_H

#include <unordered_map>
#include <memory>
#include <tuple>
#include <vector>

#include <GameFramework.h>

#include "Object.h"
#include "LayerKind.h"

namespace chargeshot
{
	using gameframework::Singleton;

	class ObjectIntegrator :public Object, public Singleton<ObjectIntegrator>
	{
	public:
		friend Singleton<ObjectIntegrator>;

		~ObjectIntegrator();

		void Register(Object* pObject, LAYER_KIND layerKind = LAYER_KIND::TRANSPARENCY, int zIndex = 0);

		void Update()override;
		void Render()override;

		void ReleaseAll();

	private:
		struct ObjectData
		{
		public:
			ObjectData(Object* pObject, char zIndex);
			~ObjectData();

			Object* m_pObject = nullptr;
			char m_zIndex = 0;
		};

		using ObjectDatas = std::vector<ObjectData*>;

		ObjectIntegrator();
		
		ObjectIntegrator(const ObjectIntegrator& objectIntegrator) = delete;
		ObjectIntegrator& operator=(const ObjectIntegrator& objectIntegrator) = delete;

		void Finalize()override;

		void ReleaseDestroyed();

		void InsertObjectDataByZIndex(LAYER_KIND layerKind, ObjectData* pObjectData);

		std::unordered_map<LAYER_KIND, ObjectDatas> m_objectDatas;
	};
}// namespace summonersaster

#endif // !OBJECT_INTEGRATOR_H
