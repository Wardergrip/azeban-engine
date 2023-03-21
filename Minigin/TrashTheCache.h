#pragma once
#include <chrono>
#include <vector>
namespace aze
{
    class TrashTheCache final
    {
    public:
        TrashTheCache() = delete;

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

        template <typename T>
        static std::vector<std::chrono::microseconds> GetAvaragesTest(size_t amountOfTests = 50, size_t amountOfElements = 10'000'000)
        {
            constexpr bool isSize_t = std::is_same<T, size_t>();
            constexpr bool isGameObject3D = std::is_same<T, GameObject3D>();
            constexpr bool isGameObject3DAlt = std::is_same<T, GameObject3DAlt>();
            constexpr bool validTypes = isSize_t | isGameObject3D | isGameObject3DAlt;
            static_assert(validTypes, "Not a valid type");

            if constexpr (isSize_t)
            {
                auto elements = new size_t[amountOfElements];
                for (size_t i{ 0 }; i < amountOfElements; ++i)
                {
                    elements[i] = i % 100;
                }
                std::vector<std::vector<std::chrono::microseconds>> times{};

                for (size_t testNr{ 0 }; testNr < amountOfTests; ++testNr)
                {
                    std::vector<std::chrono::microseconds> timeSequence{};
                    for (size_t stepsize{ 1 }; stepsize <= 1024; stepsize *= 2)
                    {
                        auto start = std::chrono::high_resolution_clock::now();
                        for (size_t i{ 0 }; i < amountOfElements; i += stepsize)
                        {
                            elements[i] *= 2;
                        }
                        auto end = std::chrono::high_resolution_clock::now();
                        auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                        timeSequence.emplace_back(elapsedTime);
                    }
                    times.emplace_back(timeSequence);
                }

                delete[] elements;

                std::vector<std::chrono::microseconds> avarages{};
                for (size_t i{ 0 }; i < times.back().size(); ++i)
                {
                    long long acc{};
                    for (size_t j{ 0 }; j < times.size(); ++j)
                    {
                        acc += times[j][i].count();
                    }
                    avarages.emplace_back(acc / times.size());
                }

                return avarages;
            }
            else
            {
                auto elements = new T[amountOfElements];
                for (size_t i{ 0 }; i < amountOfElements; ++i)
                {
                    elements[i].ID = i % 100;
                }
                std::vector<std::vector<std::chrono::microseconds>> times{};

                for (size_t testNr{ 0 }; testNr < amountOfTests; ++testNr)
                {
                    std::vector<std::chrono::microseconds> timeSequence{};
                    for (size_t stepsize{ 1 }; stepsize <= 1024; stepsize *= 2)
                    {
                        auto start = std::chrono::high_resolution_clock::now();
                        for (size_t i{ 0 }; i < amountOfElements; i += stepsize)
                        {
                            elements[i].ID *= 2;
                        }
                        auto end = std::chrono::high_resolution_clock::now();
                        auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                        timeSequence.emplace_back(elapsedTime);
                    }
                    times.emplace_back(timeSequence);
                }

                delete[] elements;

                std::vector<std::chrono::microseconds> avarages{};
                for (size_t i{ 0 }; i < times.back().size(); ++i)
                {
                    long long acc{};
                    for (size_t j{ 0 }; j < times.size(); ++j)
                    {
                        acc += times[j][i].count();
                    }
                    avarages.emplace_back(acc / times.size());
                }

                return avarages;
            }
        }

        static constexpr std::vector<float> ToFloatVector(const std::vector<std::chrono::microseconds>& vec)
        {
            std::vector<float> fv;
            std::for_each(vec.begin(), vec.end(),
                [&](const std::chrono::microseconds& ms)
                {
                    fv.push_back(static_cast<float>(ms.count()));
                }
            );
            return fv;
        }
    };

}