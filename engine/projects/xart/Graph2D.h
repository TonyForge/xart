#pragma once

#include "..\..\RenderTarget.h"
#include "..\..\Color.h"
#include "..\..\LineBatch.h"
#include "..\..\SpriteBatch.h"
#include "..\..\Camera.h"
#include "..\..\AssetsBasic.h"

namespace ok
{
	namespace graphics
	{
		class Graph2D;

		enum class G2D_Anchor
		{
			G2D_Anchor_Center,
			G2D_Anchor_Left,
			G2D_Anchor_Left_Top,
			G2D_Anchor_Right,
			G2D_Anchor_Right_Top,
			G2D_Anchor_Top,
			G2D_Anchor_Bottom,
			G2D_Anchor_Left_Bottom,
			G2D_Anchor_Right_Bottom
		};

		class G2D_Canvas
		{
		public:
			G2D_Canvas(int width, int height);
			~G2D_Canvas();
			void Resize(int width, int height);
			void Clear();
			void Clear(ok::Color& color);
		private:
			friend class ok::graphics::Graph2D;
			ok::graphics::RenderTarget* _target = nullptr;
			ok::graphics::Camera* _camera = nullptr;
		};

		class Graph2D
		{
		public:
			static ok::graphics::Graph2D& instance();
			static ok::graphics::Graph2D& o();

			static void Init();

			static void PushCanvas(ok::graphics::G2D_Canvas * canvas);
			static void PopCanvas();
			static void DisplayCanvas(ok::graphics::G2D_Canvas * canvas);

			static void Clear(ok::Color& color);
			static void Clear();

			static void LineAB(glm::vec3 a, glm::vec3 b);
			static void MoveTo(glm::vec3 position);
			static void LineTo(glm::vec3 position);

			static void Circle(glm::vec3 center, float radius);
			static void Round(glm::vec3 center, float radius);
			static void Rect(glm::vec3 anchor, float width, float height, float radius = 0.f, ok::graphics::G2D_Anchor anchor_type = ok::graphics::G2D_Anchor::G2D_Anchor_Left_Top, float rotation = 0.f);
			//static void Text

			static void SetBrushColor(ok::Color color);
			static void SetBrushColor(ok::Color begin_color, ok::Color end_color);
			static void SetBrushThickness(float thickness);
			static void SetBrushSoftness(float softness);
		private:
			Graph2D() {}
			~Graph2D() {}
			ok::graphics::Graph2D(ok::graphics::Graph2D const&) { }
			ok::graphics::Graph2D& operator= (ok::graphics::Graph2D const&) {  }

			std::vector<ok::graphics::G2D_Canvas*> _canvas_stack;
			ok::graphics::LineBatch* _line_batch = nullptr;
			ok::graphics::SpriteBatch* _sprite_batch_premulalpha_decoder = nullptr;
			ok::graphics::SpriteBatch* _sprite_batch = nullptr;
			ok::graphics::SpriteBatch* _sprite_batch_ex1 = nullptr;
			ok::graphics::SpriteBatch* _sprite_batch_ex2 = nullptr;
		protected:
		};
	}
}