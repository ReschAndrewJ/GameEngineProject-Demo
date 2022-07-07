#ifndef KEYS_TO_POLL
#define KEYS_TO_POLL

#include "GameEngineLib/Engines/Main/Input_Handler.h"
#include "GLFW/glfw3.h"

#include <vector>
#include <string>

namespace keys {

	const auto W = "W";
	const auto A = "A";
	const auto S = "S";
	const auto D = "D";
	const auto Space = "Space";

	std::vector<std::pair<std::string, int>> keysToPoll = {
		{W, GLFW_KEY_W}, {A, GLFW_KEY_A}, {S, GLFW_KEY_S}, {D, GLFW_KEY_D},
		{Space, GLFW_KEY_SPACE},
	};

}

#endif // KEYS_TO_POLL