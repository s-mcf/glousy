#include "Skybox.hpp"

const float sky_verts[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

namespace GLousy {

	Skybox::Skybox(std::array<std::string, 6> paths) :
		ShaderedDrawable(std::make_shared<Shader>("shaders/vert_skybox.glsl", "shaders/frag_skybox.glsl"))
	{
		cubemap_ = load_cubemap_from_imageset(paths);

		glCreateVertexArrays(1, &VAO);
		glCreateBuffers(1, &VBO);

		glNamedBufferData(VBO, sizeof(sky_verts), &sky_verts, GL_STATIC_DRAW);
		
		// verts
		glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(VAO, 0, 0);
		glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 3 * sizeof(float));
		glEnableVertexArrayAttrib(VAO, 0);
	}


	Skybox::~Skybox() {
	}

	void Skybox::draw() const {
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_LEQUAL);

		shader()->use();
		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_->id());
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);
	}

}