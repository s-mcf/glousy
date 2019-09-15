#pragma once

#include "Texture.hpp"

namespace GLousy {
	class Renderbuffer {
	public:
		Renderbuffer(const int width, const int height);
		~Renderbuffer();

		unsigned int id() const {
			return id_;
		}
	private:
		unsigned int id_;
	};

	class Framebuffer {
	public:
		Framebuffer();
		~Framebuffer();
		
		bool is_complete() const;

		void attach_texture(const Texture &t);
		void attach_renderbuffer(const Renderbuffer &r);

		unsigned int id() const {
			return id_;
		}
	private:
		unsigned int id_;
	};
}
