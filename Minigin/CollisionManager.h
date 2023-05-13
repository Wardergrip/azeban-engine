#pragma once
#include "Singleton.h"
#include <vector>
#include <stdexcept>

namespace aze
{
	class collider_not_registered : public std::runtime_error
	{
	public:
		collider_not_registered() :runtime_error(what()) {}
		const char* what() const override
		{
			return "Collider is not registered";
		}
	};
	
	class collider_already_registered : public std::runtime_error
	{
	public:
		collider_already_registered() :runtime_error(what()) {}
		const char* what() const override
		{
			return "Collider is already registered";
		}
	};

	class collider_is_null : public std::runtime_error
	{
	public:
		collider_is_null() :runtime_error(what()) {}
		const char* what() const override
		{
			return "Collider is nullptr";
		}
	};

	class BoxColliderComponent;
	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		void RegisterCollider(BoxColliderComponent* pCollider);
		void UnregisterCollider(BoxColliderComponent* pCollider);

		void Update();
	private:
		friend class Singleton<CollisionManager>;

		std::vector<BoxColliderComponent*> m_pColliders;
	};
}

