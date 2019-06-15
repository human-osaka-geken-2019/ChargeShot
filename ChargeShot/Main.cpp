#include <windows.h>

#include <GameFramework.h>

#include "CollisionChecker.h"
#include "PointChecker.h"
#include "SceneSwitcher.h"
#include "SceneSwitchMediator.h"

using namespace gameframework;
using namespace chargeshot;

Window* InitializeWindow(HINSTANCE hInstance, const RectSize& windowSize)
{
	WindowParam::SetInstanceHandle(hInstance);
	WindowParam::SetWindowSize(windowSize);
	Window* pWindow = new Window(_T("Charge Shot"));
	SingletonHolder<Window>::Create(pWindow);

	return pWindow;
}

INT WINAPI WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrevInst, _In_ LPSTR szStr, _In_ INT iCmdShow)
{
	Window& rWindow = *InitializeWindow(hInst, RectSize(1600.0f, 900.0f));

	DirectXParam::Create();

	GameFramework& rGameFramework = GameFramework::CreateAndGetRef();

	SceneSwitcher& rSceneSwitcher = SceneSwitcher::CreateAndGetRef();

	ObjectIntegrator& rObjectIntegrator = ObjectIntegrator::CreateAndGetRef();

	CollisionChecker& rCollisionChecker = CollisionChecker::CreateAndGetRef();

	PointChecker& rPointChecker = PointChecker::CreateAndGetRef();

	while (!rWindow.ReceivedQuitMessage())
	{
		if (rWindow.ReceivedWinMessage()) continue;

		if (!rGameFramework.CanStartNextFrame()) continue;

		rGameFramework.PrepareInFrame();

		if (rGameFramework.KeyboardIsPressed(DIK_BACKSPACE))
		{
			SceneSwitchMediator::CreateAndGetRef().SendSwitchEvent(SCENE_KIND::IN_GAME);
		}

		rCollisionChecker.Update();

		rPointChecker.Update();

		rSceneSwitcher.Update();
		rObjectIntegrator.Update();
		rGameFramework.UpdateGraphicEffects();

		rObjectIntegrator.Render();
		rGameFramework.RenderGraphicEffects();

		rGameFramework.FinishInFrame();
	}
	return 0;
}
