#include "STBLoader.h"

STBLoader::STBLoader() {
}

STBLoader::~STBLoader() {
}

std::shared_ptr<Texture2D> STBLoader::loadImage(const std::string& name) {
    int width, height;
    int nrChannel;
    unsigned char* data = nullptr;
    data = stbi_load(name.c_str(), &width, &height, &nrChannel, 0);

    if (!data) {
        throw std::exception("Failed to load image data");
    }

    GLuint id;
    glGenTextures(1, &id);
    std::shared_ptr<Texture2D> texture(new Texture2D(id, glm::ivec2(width, height)));

    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
    return texture;
}
