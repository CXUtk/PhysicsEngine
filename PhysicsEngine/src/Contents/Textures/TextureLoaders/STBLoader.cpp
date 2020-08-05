#include "STBLoader.h"

STBLoader::STBLoader() {
}

STBLoader::~STBLoader() {
}

std::shared_ptr<Texture2D> STBLoader::loadImage(const std::string& name) {
    BitmapData data;
    int nrChannel;
    data.data = stbi_load(name.c_str(), &data.width, &data.height, &nrChannel, 0);

    if (!data.data) {
        throw std::exception("Failed to load image data");
    }

    GLuint id;
    glGenTextures(1, &id);
    std::shared_ptr<Texture2D> texture(new Texture2D(id, glm::ivec2(data.width, data.height)));

    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data.width, data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data.data);
    return texture;
}
