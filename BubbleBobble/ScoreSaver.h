#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <algorithm>

namespace aze
{
	struct ScoreEntry final
	{
		ScoreEntry() = default;
		ScoreEntry(const std::string& _name, uint16_t _score)
			:score{_score}
		{
			SetName(_name);
		}
		char name[3]{ 'A','A','A' };
		uint16_t score{ 0 };

		ScoreEntry& SetName(const std::string& _name)
		{
			for (size_t i{ 0 }; i < _name.size(); ++i)
			{
				if (i >= 3) break;
				name[i] = _name[i];
			}
			return *this;
		}
	};
	class ScoreSaver final
	{
	public:
		ScoreSaver() = default;

		const std::vector<ScoreEntry>& ReadScoreEntries(const std::string& filePath);
		ScoreSaver& WriteScoreEntries(const std::string& filePath);

		void AddNewScoreEntry(const ScoreEntry& scoreEntry);

		const std::vector<ScoreEntry>& GetScoreEntries() const { return m_ScoreEntries; }
		void Clear() { m_ScoreEntries.clear(); }
		ScoreSaver& SortScoreEntries()
		{
			static auto compareByScore = [](const ScoreEntry& entry1, const ScoreEntry& entry2) 
			{
				return entry1.score > entry2.score;
			};
			if (!m_ScoreEntries.empty())
			{
				std::sort(m_ScoreEntries.begin(), m_ScoreEntries.end(), compareByScore);
			}
			return *this;
		}
	private:
		std::vector<ScoreEntry> m_ScoreEntries;
	};
}
