#include <thread>

#include "./render/Graphics.hpp"
#include "features/Trigger.hpp"

#include "utils/HWID.hpp"
#include "features/RCS.hpp"

void exit_button()
{
	while (Settings::running)
	{
		if (GetAsyncKeyState(VK_DELETE) && isDown)
			Settings::running = false;

		std::this_thread::sleep_for(10ms);
	}
}

void StartThreads()
{
	HWID::checkHwid();

	Settings::Load();
	Settings::running = true;

	std::thread graphics(Render::Create);
	std::thread trigger(Trigger::loop);
	std::thread rcs(RCS::loop);
	std::thread ext(exit_button);

	ext.join();
	graphics.join();
	rcs.join();
	trigger.join();
}