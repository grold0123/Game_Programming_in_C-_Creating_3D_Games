#include"object.hpp"


Object::Object():
    rect(SDL_FRect{0,0,50,50}),
    position{rect.x,rect.y}
{}
Object::Object(SDL_FRect rect):
    rect{rect},
    position{rect.x,rect.y}
{}
void Object::draw(SDL_Renderer*renderer)const{
    if (!texture){
        SDL_SetRenderDrawColor(renderer,
            static_cast<Uint8>(objectColor.r),
            static_cast<Uint8>(objectColor.g),
            static_cast<Uint8>(objectColor.b),
            static_cast<Uint8>(objectColor.a)
        );
        SDL_RenderFillRect(renderer,&rect);
    }
    else SDL_RenderTexture(renderer,texture,NULL,&rect);
}
void Object::update(const float&deltaTime){    
}