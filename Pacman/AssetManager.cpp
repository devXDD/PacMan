#include "AssetManager.h"

AssetManager::AssetManager() {

}


AssetManager& AssetManager::Get() {
    static AssetManager* s_instance = new AssetManager;
    return *s_instance;
}

SDL_Surface* AssetManager:: GetSurface(std::string filepath, SDL_Renderer* render) {
    auto mappingSurface = retrieve_surface.find(filepath);
    if (mappingSurface != retrieve_surface.end()) {
        return retrieve_surface[filepath];
    }
    else
    {
        SDL_Surface* secondSurface = IMG_Load(filepath.c_str());
        retrieve_surface.insert(std::make_pair(filepath, secondSurface));
        return secondSurface;
    }
}

SDL_Texture* AssetManager::GetTexture(std::string filepath, SDL_Renderer* render) {
    auto mapping = single_surface.find(filepath);
    if (mapping != single_surface.end()) {
        return single_surface[filepath];
    }
    else 
    {
       SDL_Surface* surface =  GetSurface(filepath, render);
        SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(render, surface);
        single_surface.insert(std::make_pair(filepath, optimizedSurface));
        return single_surface[filepath];
    }
    return nullptr;
}

TTF_Font* AssetManager::GetFont(std::string filepath)
{
    auto font_mapping = retrieve_font.find(filepath);
    if (font_mapping != retrieve_font.end()) {
        return retrieve_font[filepath];
    }
    else
    {
        TTF_Font* font = TTF_OpenFont(filepath.c_str(), 24);
        retrieve_font.insert(std::make_pair(filepath, font));
        return retrieve_font[filepath];
    }
}

SDL_Surface* AssetManager::GetFontSurface(std::string aText,std::string filepath, SDL_Renderer* render)
{
    auto Font_Surface_mapping =retrieve_Fontsurface.find(filepath);
    if (Font_Surface_mapping != retrieve_Fontsurface.end()) {
        return retrieve_Fontsurface[filepath];
    }
    else
    {
        TTF_Font* font = GetFont(filepath);
        SDL_Color fg = { 255,0,0,255 };
        SDL_Surface* surface = TTF_RenderText_Solid(font, aText.c_str(), fg);
        retrieve_Fontsurface.insert(std::make_pair(filepath,surface));
        return retrieve_Fontsurface[filepath];
    }
    return nullptr;
}

SDL_Texture* AssetManager::GetFontTexture(std::string aText,std::string filepath, SDL_Renderer* render) {
    auto font_Texture_mapping = retreive_font_texture.find(filepath);
    if (font_Texture_mapping != retreive_font_texture.end()) {
        return retreive_font_texture[filepath];
    }
    else
    {
        SDL_Surface* surface = GetFontSurface(aText,filepath, render);
        SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(render, surface);
        retreive_font_texture.insert(std::make_pair(filepath, optimizedSurface));
        return retreive_font_texture[filepath];
    }
    return nullptr;
}