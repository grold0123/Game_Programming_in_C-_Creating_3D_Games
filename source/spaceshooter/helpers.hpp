#pragma once
#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include<filesystem>
#include<iostream>
#include<vector>

std::vector<SDL_Texture*>getTextures(SDL_Renderer*renderer,const char*fileDir);

std::vector<SDL_Texture*>getTextures(SDL_Renderer*renderer,const char*fileDir){
    
    std::vector<SDL_Texture*> files;
    
    for (const auto&entry:std::filesystem::directory_iterator(fileDir)){
        files.push_back(IMG_LoadTexture(renderer,entry.path().string().c_str()));
    }

    return files;

}
