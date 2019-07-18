#include "ObjectIntegrator.h"

namespace chargeshot
{
	ObjectIntegrator::ObjectIntegrator()
	{
	
	}

	ObjectIntegrator::~ObjectIntegrator()
	{
		Finalize();
	}

	void ObjectIntegrator::Register(Object* pObject, LAYER_KIND layerKind, int zIndex)
	{
		ObjectData* pObjectData = new ObjectData(pObject, zIndex);

		InsertObjectDataByZIndex(layerKind, pObjectData);
	}

	void ObjectIntegrator::Update()
	{
		ReleaseDestroyed();

		std::vector<Object*> pOjects;

		for (auto& rObjectDatas : m_objectDatas)
		{
			for (auto& rObjectData : rObjectDatas.second)
			{
				pOjects.push_back(rObjectData->m_pObject);
			}
		}

		for (auto& pOject : pOjects)
		{
			pOject->Update();
		}
	}

	void ObjectIntegrator::Render()
	{
		LAYER_KIND layerKinds[] =
		{
			LAYER_KIND::OPAQUENESS,
			LAYER_KIND::TRANSPARENCY,
			LAYER_KIND::UI
		};

		for (auto& rlayerKind : layerKinds)
		{
			for (auto& rObjectData : m_objectDatas[rlayerKind])
			{
				rObjectData->m_pObject->Render();
			}
		}
	}

	void ObjectIntegrator::RenderFront()
	{
		for (auto& rObjectData : m_objectDatas[LAYER_KIND::FRONT])
		{
			rObjectData->m_pObject->Render();
		}
	}

	void ObjectIntegrator::ReleaseAll()
	{
		for (auto& rObjectDatas : m_objectDatas)
		{
			for (auto& rObjectData : rObjectDatas.second)
			{
				delete rObjectData;
			}
		}

		m_objectDatas.clear();
	}

	ObjectIntegrator::ObjectData::ObjectData(Object* pObject, char zIndex)
		:m_pObject(pObject), m_zIndex(zIndex)
	{
		
	}

	ObjectIntegrator::ObjectData::~ObjectData()
	{
		delete m_pObject;
	}

	void ObjectIntegrator::Finalize()
	{
		ReleaseAll();
	}

	void ObjectIntegrator::ReleaseDestroyed()
	{
		for (auto& rObjectDatas : m_objectDatas)
		{
			auto& rLayerObjectDatas = rObjectDatas.second;

			for (int i = static_cast<int>(rLayerObjectDatas.size() - 1); i >= 0; --i)
			{
				if (!rLayerObjectDatas[i]->m_pObject->ShouldDestroyed()) continue;

				delete rLayerObjectDatas[i];

				rLayerObjectDatas.erase(rLayerObjectDatas.begin() + i);
			}

			rLayerObjectDatas.shrink_to_fit();
		}
	}

	void ObjectIntegrator::InsertObjectDataByZIndex(LAYER_KIND layerKind, ObjectData* pObjectData)
	{
		ObjectDatas& rObjectDatas = m_objectDatas[layerKind];

		for (auto& rpObjectDatasComponent : rObjectDatas)
		{
			auto index = (&rpObjectDatasComponent - &rObjectDatas[0]);

			char zIndexDifference = pObjectData->m_zIndex - rpObjectDatasComponent->m_zIndex;

			if (zIndexDifference > 0) continue;

			rObjectDatas.insert(rObjectDatas.begin() + index, pObjectData);

			return;
		}

		rObjectDatas.insert(rObjectDatas.end(), pObjectData);
	}
}
