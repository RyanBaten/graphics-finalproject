#ifndef TEXTUREMAP_H
#define TEXTUREMAP_H

#include<map>
#include<string>

class TextureMap {
  private:
    // Maps std::string names to textures
    std::map<std::string, unsigned int> texture_map;
  public:
    // Constructor
    TextureMap();
    // Adding textures
    void addTexture(std::string name, std::string fn);
    // Removing by name
    void removeTexture(std::string name);
    // Bind by name
    void bindTexture(std::string name);
};

#endif
