#pragma once
#include <string>
#include <functional>

namespace aze
{
	class Azeban
	{
	public:
		explicit Azeban(const std::string& dataPath);
		~Azeban();
		void Run(const std::function<void()>& load);

		Azeban(const Azeban& other) = delete;
		Azeban(Azeban&& other) = delete;
		Azeban& operator=(const Azeban& other) = delete;
		Azeban& operator=(Azeban&& other) = delete;
	};
}