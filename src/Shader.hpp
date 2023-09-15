#pragma once
#include <string>
#include <vector>
#include <map>

#include "Vendors/glm/glm.hpp"
#include "Vendors/glm/gtc/matrix_transform.hpp"
#include "Vendors/glm/gtc/type_ptr.hpp"

#include "Texture.hpp"


enum class ShaderType
{
    NONE = -1,
    VERTEX = 0,
    FRAGMENT = 1
};

struct Shaders
{
    std::string vertex;
    std::string framgent;
};

struct CachedUniform
{
    std::string uniformName;
    unsigned int locationID;
};

struct TextureUnit
{
    int layer;
    unsigned int locationID;
};


class Shader
{
private:
    unsigned int m_shaderID;
    std::vector<CachedUniform> m_Cache;
    std::vector<TextureUnit> m_shadertextures;
public:
    Shader();
    ~Shader();

    static Shaders getSahderSrc(const std::string& filepath);

    unsigned int CompileShader(unsigned int type, const std::string& source);

    unsigned int CreateShader(const std::string& vertexShader, const std::string fragmentShader);

    void BindShader();

    void UnbindShader();

    inline unsigned int& getShaderID() {return m_shaderID;}

    unsigned int getUniformLoction(const char* uniformName);

    void setUniformv3(const char* varibalName,float v0, float v1, float v2);

    void setUniformv1i(const char* varibalName,int v0);

    void setUniformvmatrix4f(const char* varibalName, glm::mat4& value);

    inline auto& getCache() const& {return m_Cache;}

    void setTexture(int textureLayer, const std::string& textureIndex);

    void setTexture(int textureLayer,const std::string& textureIndex, std::map<std::string, std::shared_ptr<Texture>>& textureList);

    static void loadShader(const std::string& newIndex, const std::string& filePath);

    static void loadShader(const std::string& newIndex, const std::string& filePath, std::map<std::string, std::shared_ptr<Shader>>& shaderList);

    void bindTextures();
};