#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP
#include <string>
#include <unordered_map>
#include "SDL_ttf.h"
#include <SDL.h>
#include <SDL_image.h>

class AssetManager {
private:
    AssetManager();
    std::unordered_map<std::string, SDL_Texture*> single_surface;
    std::unordered_map<std::string, SDL_Texture*> retreive_font_texture;
    std::unordered_map<std::string, SDL_Surface*> retrieve_surface;
    std::unordered_map<std::string, SDL_Surface*> retrieve_Fontsurface;
    std::unordered_map<std::string, TTF_Font*> retrieve_font;

public:
    static AssetManager& Get();
    SDL_Texture* GetTexture(std::string filepath, SDL_Renderer* render);
    SDL_Texture* GetFontTexture(std::string aText, std::string filepath, SDL_Renderer* render);
    SDL_Surface* GetSurface(std::string filepath, SDL_Renderer* render);
    TTF_Font* GetFont(std::string filepath);
    SDL_Surface* GetFontSurface(std::string aText,std::string filepath, SDL_Renderer* render);
};


#endif