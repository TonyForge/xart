#pragma once

#include "Application.h"
#include "UI.h"
#include "projects\xart\Graph2D.h"
#include "Input.h"

namespace XART
{
	class App : public ok::Application
	{
	public:
		App();
		void Init();
		void Update(float dt);
	private:
		ok::graphics::G2D_Canvas* scr0;
	protected:
	};
}