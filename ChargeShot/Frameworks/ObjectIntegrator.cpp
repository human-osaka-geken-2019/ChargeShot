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

		for (auto& rObjectDatas : m_objectDatas)
		{
			for (auto& rObjectData : rObjectDatas.second)
			{
				rObjectData->m_pObject->Update();
			}
		}
	}

	void ObjectIntegrator::Render()
	{
		for (auto& rObjectDatas : m_objectDatas)
		{
			for (auto& rObjectData : rObjectDatas.second)
			{
				rObjectData->m_pObject->Render();
			}
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
