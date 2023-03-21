#pragma once
#include <chrono>
#include <vector>
namespace aze
{
    class TrashTheCache final
    {
    public:
        TrashTheCache() = delete;

        static std::vector<std::chrono::microseconds> GetAvaragesTestInt(size_t amountOfTests = 50, size_t amountOfElements = 10'000'000);
        static std::vector<std::chrono::microseconds> GetAvaragesTestGameObject3D(size_t amountOfTests = 50, size_t amountOfElements = 10'000'000);
        static std::vector<std::chrono::microseconds> GetAvaragesTestGameObject3DAlt(size_t amountOfTests = 50, size_t amountOfElements = 10'000'000);

    private:
        struct Transform
        {
            float matrix[16] = {
                1,0,0,0,
                0,1,0,0,
                0,0,1,0,
                0,0,0,1
            };
        };

        class GameObject3D
        {
        public:
            Transform transform{};
            int ID{};
        };

        class GameObject3DAlt
        {
        public:
            Transform* transform{};
            int ID{};
        };

    };

}