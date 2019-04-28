#include "xart.h"

INITIALIZE_EASYLOGGINGPP

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	XART::App app;

	LOG(INFO) << "XART initiated...";
	app.Run();

	return 0;
}

XART::App::App()
{
	_settings_file_name = "xart.settings.xml";
}

void XART::App::Init()
{
	DisableFeature(ok::ApplicationFeature::AutoClearStencil);
	ok::graphics::Graph2D::Init();

	scr0 = new ok::graphics::G2D_Canvas(640, 480);
}

void XART::App::Update(float dt)
{
	ok::graphics::Graph2D::PushCanvas(scr0);
	ok::graphics::Graph2D::Clear(ok::Color(0.f, 0.f, 0.f, 0.f));
	ok::graphics::Graph2D::SetBrushColor(ok::Color::Red);
	ok::graphics::Graph2D::SetBrushThickness(4.f);
	ok::graphics::Graph2D::SetBrushSoftness(1.0f);
	//ok::graphics::Graph2D::LineAB(glm::vec3(0.f, 0.f, 0.f), glm::vec3(100.f, 100.f, 0.f));
	ok::graphics::Graph2D::Circle(glm::vec3(100.f, 200.f, 0.f), 200.f);
	
	ok::graphics::Graph2D::SetBrushColor(ok::Color::Cyan);
	ok::graphics::Graph2D::SetBrushSoftness(1.0f);
	ok::graphics::Graph2D::SetBrushThickness(4.f);
	//ok::graphics::Graph2D::Circle(glm::vec3(150.f, 200.f, 0.f), 200.f, 5.f);

	ok::graphics::Graph2D::PopCanvas();


	//main menu
	ok::ui::BeginUI(screen_width, screen_height);
	ok::graphics::Graph2D::DisplayCanvas(scr0);
	ok::ui::EndUI();
}
