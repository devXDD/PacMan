#include "AssetManager.h"

AssetManager::AssetManager() {

}


AssetManager& AssetManager::Get() {
    static AssetManager* s_instance = new AssetManager;
    return *s_instance;
}

SDL_Surface* AssetManager::GetSurface(std::string filepath) {
    auto mapping = single_surface.find(filepath);
    if (mapping != single_surface.end()) {
        return single_surface[filepath];
    }
    else 
    {
        SDL_Surface* surface = IMG_Load(filepath.c_str());
        single_surface.insert(std::make_pair(filepath, surface));
        return single_surface[filepath];
    }
    return nullptr;

}
