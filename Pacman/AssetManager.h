#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP
#include <string>
#include <unordered_map>
#include <SDL.h>
#include <SDL_image.h>

class AssetManager {
private:
    AssetManager();
    std::unordered_map<std::string, SDL_Texture*> single_surface;
    std::unordered_map<std::string, SDL_Surface*> retrieve_sruface;

public:
    static AssetManager& Get();
    SDL_Texture* GetSurface(std::string filepath, SDL_Renderer* render);
    SDL_Surface* GetSur(std::string filepath, SDL_Renderer* render);
};


#endif