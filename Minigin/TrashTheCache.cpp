#include "TrashTheCache.h"

std::vector<std::chrono::microseconds> aze::TrashTheCache::GetAvaragesTestInt(size_t amountOfTests, size_t amountOfElements)
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

std::vector<std::chrono::microseconds> aze::TrashTheCache::GetAvaragesTestGameObject3D(size_t amountOfTests, size_t amountOfElements)
{
    auto elements = new GameObject3D[amountOfElements];
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

std::vector<std::chrono::microseconds> aze::TrashTheCache::GetAvaragesTestGameObject3DAlt(size_t amountOfTests, size_t amountOfElements)
{
    auto elements = new GameObject3DAlt[amountOfElements];
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
