#include "Framebuffer.hpp"

#include <glad/glad.h>

namespace GLousy {

	Framebuffer::Framebuffer() {
		glCreateFramebuffers(1, &id_);
	}

	Framebuffer::~Framebuffer() {
		glDeleteFramebuffers(1, &id_);
	}
	
	bool Framebuffer::is_complete() const {
		return (glCheckNamedFramebufferStatus(id(), GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
	}

	void Framebuffer::attach_texture(const Texture &t) {
		glNamedFramebufferTexture(id(), GL_COLOR_ATTACHMENT0, t.id(), 0);
	}

	void Framebuffer::attach_renderbuffer(const Renderbuffer &r) {
		glNamedFramebufferRenderbuffer(id(), GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, r.id());
	}

	Renderbuffer::Renderbuffer(const int width, const int height) {
		glCreateRenderbuffers(1, &id_);
		glNamedRenderbufferStorage(id(), GL_DEPTH24_STENCIL8, width, height);
	}

	Renderbuffer::~Renderbuffer() {
		glDeleteRenderbuffers(1, &id_);
	}


}
