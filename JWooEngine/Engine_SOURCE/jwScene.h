#pragma once
#include "jwEntity.h"
#include "jwLayer.h"

namespace jw
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void AddGameObject(eLayerType type, GameObject* gameObj);

	private:
		std::vector<Layer> mLayers;
	};
}
