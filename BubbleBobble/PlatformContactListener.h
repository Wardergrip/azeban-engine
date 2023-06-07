#pragma once
#include "../3rdParty/box2d/box2d.h"
#include "Observer.h"
#include "PhysicsManager.h"
#include <iostream>

namespace aze
{
    static bool operator==(const b2FixtureUserData& a, const b2FixtureUserData& b)
    {
        return a.pointer == b.pointer;
    }
    class PlatformContactListener final : public b2ContactListener, public Observer<bool>, public Singleton<PlatformContactListener>
    {
    protected:
        friend class Singleton<PlatformContactListener>;
        PlatformContactListener()
            :m_WantsToDrop{false}
        {
            PLATFORM_USER_DATA.pointer = reinterpret_cast<uintptr_t>(this);
            PhysicsManager::GetInstance().GetWorld()->SetContactListener(this);
        }
    public:
        void PreSolve(b2Contact* contact, const b2Manifold* /*oldManifold*/) override
        {
            //b2Fixture* fixtureA = contact->GetFixtureA();
            //b2Fixture* fixtureB = contact->GetFixtureB();

            //bool isPlatformA = fixtureA->GetUserData() == PLATFORM_USER_DATA;
            //bool isPlatformB = fixtureB->GetUserData() == PLATFORM_USER_DATA;

            //// Make sure one of the fixtures is a platform.
            //if (!(isPlatformA || isPlatformB))
            //    return;

            //b2Fixture* platform = isPlatformA ? fixtureA : fixtureB;
            //b2Fixture* character = isPlatformA ? fixtureB : fixtureA;

            //b2Body* characterBody = character->GetBody();
            //b2Body* platformBody = platform->GetBody();

            //// Check if the character is under the platform.
            //if (characterBody->GetPosition().y < platformBody->GetPosition().y)
            //{
            //    std::cout << "here\n";
            //    // Check if the character is going up
            //    if (characterBody->GetLinearVelocity().y >= -FLT_EPSILON)
            //    {
            //        std::cout << "disabled\n";
            //        contact->SetEnabled(false);
            //    }
            //    else
            //    {
            //        std::cout << "enabled\n";
            //        contact->SetEnabled(true);
            //    }
            //    return;
            //}

            //// Check if the character is moving downward.
            //if (characterBody->GetLinearVelocity().y < 0)
            //    return;

            //// If the character wants to drop through the platform, ignore this collision.
            //if (m_WantsToDrop)  // You'll have to write this function.
            //    contact->SetEnabled(false);

            b2Fixture* fixtureA = contact->GetFixtureA();
            b2Fixture* fixtureB = contact->GetFixtureB();

            bool isPlatformA = fixtureA->GetUserData() == PLATFORM_USER_DATA;
            bool isPlatformB = fixtureB->GetUserData() == PLATFORM_USER_DATA;

            // Make sure one is a platform but not both.
            if (isPlatformA)
            {
                if (isPlatformB) return;
            }
            else if (isPlatformB == false) return;

            b2Fixture* platform = isPlatformA ? fixtureA : fixtureB;
            b2Fixture* character = isPlatformA ? fixtureB : fixtureA;

            b2Vec2 position = character->GetBody()->GetPosition();

            float top{ platform->GetBody()->GetPosition().y + 0.5f };
            if (position.y < top)
            {
                std::cout << "Disabled\n";
                contact->SetEnabled(false);
            }
            std::cout << "No change\n";
        }

        void OnNotify(bool* data)
        {
            m_WantsToDrop = data ? true : false;
        }

        const b2FixtureUserData& GetPlatformUserData() const { return PLATFORM_USER_DATA;}

    private:
        b2FixtureUserData PLATFORM_USER_DATA{};
        bool m_WantsToDrop{};
    };
}