#pragma once
#include "Command.h"
#include <string>

namespace aze
{
	class DebugCommand : public Command
	{
	public:
		DebugCommand(const std::string& msg)
			:m_Msg{msg}
		{}
		void Execute() override
		{
			std::cout << m_Msg << '\n';
		}

	private:
		std::string m_Msg;
	};
}