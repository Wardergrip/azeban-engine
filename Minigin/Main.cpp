#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Azeban.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"

void load()
{
	auto& scene = aze::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<aze::GameObject>();
	go->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<aze::GameObject>();
	go->SetTexture("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = aze::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<aze::GameObject>();
	auto toc = to->AddComponent<aze::TextObject>();
	auto tocs = toc.lock();
	tocs->SetFont(font);
	tocs->SetText("Programming 4 Assignment");
	tocs->SetPosition(80, 20);
	scene.Add(to);
}

int main(int, char*[]) {
	aze::Azeban engine("../Data/");
	engine.Run(load);
    return 0;
}