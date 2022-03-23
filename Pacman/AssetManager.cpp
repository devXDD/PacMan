#include "AssetManager.h"

AssetManager::AssetManager() {

}


AssetManager& AssetManager::Get() {
    static AssetManager* s_instance = new AssetManager;
    return *s_instance;
}

SDL_Surface* AssetManager:: GetSur(std::string filepath, SDL_Renderer* render) {
    auto mappingSurface = retrieve_sruface.find(filepath);
    if (mappingSurface != retrieve_sruface.end()) {
        return retrieve_sruface[filepath];
    }
    else
    {
        SDL_Surface* secondSurface = IMG_Load(filepath.c_str());
        retrieve_sruface.insert(std::make_pair(filepath, secondSurface));
        return secondSurface;
    }
}

SDL_Texture* AssetManager::GetSurface(std::string filepath, SDL_Renderer* render) {
    auto mapping = single_surface.find(filepath);
    if (mapping != single_surface.end()) {
        return single_surface[filepath];
    }
    else 
    {
       SDL_Surface* surface =  GetSur(filepath, render);
        SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(render, surface);
        single_surface.insert(std::make_pair(filepath, optimizedSurface));
        return single_surface[filepath];
    }
    return nullptr;

}


