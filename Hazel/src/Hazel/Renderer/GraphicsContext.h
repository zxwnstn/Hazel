#pragma once

namespace Hazel {

	class GraphicsContext
	{
	public:
		virtual void init() = 0;
		virtual void SwapBuffers() = 0;
	};
}