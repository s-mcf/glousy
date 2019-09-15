#include "Drawable.hpp"

void GLousy::DrawableSet::update_shader_cache() {
	for (auto &d : drawables) {
		shaders.insert(d->shader());
	}
}
