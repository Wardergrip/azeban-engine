#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Azeban.h"
#include "SceneDefinitions.h"

int main(int, char* [])
{
	aze::Azeban engine("../Data/");
	engine.Run(aze::full_load);
	return 0;
}