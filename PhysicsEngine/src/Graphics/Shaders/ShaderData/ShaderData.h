#pragma once

#include <glad/glad.h>
#include <string>
#include <memory>


class ShaderData {
public:
    static GLuint loadShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);

    ShaderData(GLuint id);
    virtual ~ShaderData() = 0 {}

    GLuint getID() const { return _id; }

    virtual void apply() { glUseProgram(_id); }

private:
    GLuint _id;
};
