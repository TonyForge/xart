#include "Graph2D.h"

ok::graphics::Graph2D & ok::graphics::Graph2D::instance()
{
	static ok::graphics::Graph2D s;
	return s;
}

ok::graphics::Graph2D & ok::graphics::Graph2D::o()
{
	return instance();
}

void ok::graphics::Graph2D::Init()
{
	o()._line_batch = new ok::graphics::LineBatch();
	o()._line_batch->SetMaterial(ok::AssetsBasic::instance().GetMaterial("LineBatch.PreMulAlphaMaterial.xml"));
	o()._sprite_batch_premulalpha_decoder = new ok::graphics::SpriteBatch();
	o()._sprite_batch_premulalpha_decoder->SetMaterial(ok::AssetsBasic::instance().GetMaterial("SpriteBatch.PreMulAlphaDecoderMaterial.xml"));
	o()._sprite_batch = new ok::graphics::SpriteBatch();
	o()._sprite_batch->SetMaterial(ok::AssetsBasic::instance().GetMaterial("SpriteBatch.PreMulAlphaMaterial.xml"));

	o()._sprite_batch_ex1 = new ok::graphics::SpriteBatch(1000,1);
}

void ok::graphics::Graph2D::PushCanvas(ok::graphics::G2D_Canvas * canvas)
{
	if (canvas == nullptr)
	{
		return;
	}

	o()._canvas_stack.push_back(canvas);
	canvas->_target->BindTarget();
	ok::graphics::Camera::PushCamera(canvas->_camera);
}

void ok::graphics::Graph2D::PopCanvas()
{
	if (o()._canvas_stack.size() > 0)
	{
		auto canvas = o()._canvas_stack.back();
		o()._canvas_stack.pop_back();
		canvas->_target->UnbindTarget();
		ok::graphics::Camera::PopCamera();
	}
}

void ok::graphics::Graph2D::DisplayCanvas(ok::graphics::G2D_Canvas * canvas)
{
	o()._sprite_batch_premulalpha_decoder->BatchBegin(2.0f);
	ok::graphics::Texture _tex = ok::graphics::Texture(canvas->_target);
	o()._sprite_batch_premulalpha_decoder->Blit(&_tex, 0, 0, glm::vec2(0.f,0.f), false);
	o()._sprite_batch_premulalpha_decoder->BatchEnd();
}

void ok::graphics::Graph2D::Clear(ok::Color & color)
{
	o()._canvas_stack.back()->Clear(color);
}

void ok::graphics::Graph2D::Clear()
{
	o()._canvas_stack.back()->Clear();
}

void ok::graphics::Graph2D::LineAB(glm::vec3 a, glm::vec3 b)
{
	o()._line_batch->BatchBegin();
	o()._line_batch->LineAB(a, b);
	o()._line_batch->BatchEnd();
}

void ok::graphics::Graph2D::MoveTo(glm::vec3 position)
{
	o()._line_batch->MoveTo(position);
}

void ok::graphics::Graph2D::LineTo(glm::vec3 position)
{
	o()._line_batch->BatchBegin();
	o()._line_batch->LineTo(position);
	o()._line_batch->BatchEnd();
}

void ok::graphics::Graph2D::Circle(glm::vec3 center, float radius)
{
	ok::graphics::SpriteInfo info;
	info.tint_color = o()._line_batch->GetBrushColor();
	info.tint_power = 1.f;
	info.rect.texture = nullptr;
	info.rect.uv_rect = glm::vec4(0.f, 0.f, 1.f, 1.f);
	info.rect.left = 0; info.rect.top = 0;
	info.rect.width = 1; info.rect.height = 1;

	info.extra_data.push_back(glm::vec4(1.f,0.f,0.f,0.f));

	o()._sprite_batch_ex1->SetMaterial(ok::AssetsBasic::instance().GetMaterial("SpriteBatch.CircleMaterial.xml"));
	o()._sprite_batch_ex1->BatchBegin();
	o()._sprite_batch_ex1->Draw(&info, glm::vec2(center.x, center.y), 0.f, glm::vec2(radius, radius));
	o()._sprite_batch_ex1->BatchEnd();
}

/*void ok::graphics::Graph2D::Circle(glm::vec3 center, float radius, float arc_step_degrees)
{
	o()._line_batch->BatchBegin();
	o()._line_batch->Circle(center, glm::vec3(0.f,0.f,1.f), glm::vec3(0.f,1.f,0.f), radius, arc_step_degrees);
	o()._line_batch->BatchEnd();
}*/

void ok::graphics::Graph2D::SetBrushColor(ok::Color color)
{
	o()._line_batch->SetBrushColor(color);
}

void ok::graphics::Graph2D::SetBrushColor(ok::Color begin_color, ok::Color end_color)
{
	o()._line_batch->SetBrushColor(begin_color, end_color);
}

void ok::graphics::Graph2D::SetBrushThickness(float thickness)
{
	o()._line_batch->SetBrushThickness(thickness);
}

void ok::graphics::Graph2D::SetBrushSoftness(float softness)
{
	o()._line_batch->SetBrushSoftness(softness);
}

ok::graphics::G2D_Canvas::G2D_Canvas(int width, int height)
{
	Resize(width, height);
}

ok::graphics::G2D_Canvas::~G2D_Canvas()
{
}

void ok::graphics::G2D_Canvas::Resize(int width, int height)
{
	bool was_binded = false;

	if (_target != nullptr)
	{
		if (_target->IsBinded()) 
		{
			_target->UnbindTarget();
			was_binded = true;
		}
		delete _target;
		delete _camera;
		_target = nullptr;
		_camera = nullptr;
	}

	_camera = new ok::graphics::Camera(ok::graphics::CameraCoordinateSystem::Cartesian);
	_camera->SetProjectionOrtho(static_cast<float>(width), static_cast<float>(height), 1.f, 1000.f);

	_camera->BeginTransform();
	_camera->SetPosition(glm::vec3(0.f, 0.f, -500.f));
	_camera->EndTransform(false);

	_target = new ok::graphics::RenderTarget(width, height, true, false, false, true);
	if (was_binded)
	{
		_target->BindTarget();
	}
}

void ok::graphics::G2D_Canvas::Clear()
{
	bool was_binded = _target->IsBinded();

	if (was_binded == false)
	{
		_target->BindTarget();
	}
	
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	if (was_binded == false)
	{
		_target->UnbindTarget();
	}
	
}

void ok::graphics::G2D_Canvas::Clear(ok::Color & color)
{
	bool was_binded = _target->IsBinded();

	if (was_binded == false)
	{
		_target->BindTarget();
	}

	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT);

	if (was_binded == false)
	{
		_target->UnbindTarget();
	}
}
