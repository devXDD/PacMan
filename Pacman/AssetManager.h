#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP
#include <string>
#include <unordered_map>
#include <SDL.h>
#include <SDL_image.h>

class AssetManager {
private:
    AssetManager();
    std::unordered_map<std::string, SDL_Surface*> single_surface;

public:
    static AssetManager& Get();
    SDL_Surface* GetSurface(std::string filepath);
};


#endif