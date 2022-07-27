#ifndef KEYS_TO_POLL
#define KEYS_TO_POLL

#include "../_GameEngineSrc/Engines/Main/Input_Handler.h"
#include "GLFW/glfw3.h"

#include <vector>
#include <string>

namespace keys {

	const auto W = "W";
	const auto A = "A";
	const auto S = "S";
	const auto D = "D";
	const auto Space = "Space";

	const auto Up = "Up";
	const auto Down = "Down";
	const auto Left = "Left";
	const auto Right = "Right";

	const auto Enter = "Enter";
	const auto Grave = "Grave";

	const auto C = "C";

	const std::vector<std::pair<std::string, int>> keysToPoll = {
		{W, GLFW_KEY_W}, {A, GLFW_KEY_A}, {S, GLFW_KEY_S}, {D, GLFW_KEY_D},
		{Space, GLFW_KEY_SPACE},
		{Up, GLFW_KEY_UP}, {Down, GLFW_KEY_DOWN},
		{Left, GLFW_KEY_LEFT}, {Right, GLFW_KEY_RIGHT},
		{Enter, GLFW_KEY_ENTER}, 
		{Grave, GLFW_KEY_GRAVE_ACCENT},
		{C, GLFW_KEY_C},
	};

}

#endif // KEYS_TO_POLL