#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#define SCREEN_WIDTH 800
#define SCREEN_HIGHT 600







int main(int argc,char *argv[]){
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    SDL_Window *window = SDL_CreateWindow("Hello World!", 100, 100, SCREEN_WIDTH, SCREEN_HIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }


    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
        SDL_DestroyWindow(window);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // graphics hardware and set flags
    SDL_Surface* surface;

    surface = IMG_Load("res/person.png");

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    SDL_Rect dest;

    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

    // adjust height and width of our image box.
    dest.w /= 1;
    dest.h /= 1;
 
    // sets initial x-position of object
    dest.x = (1000 - dest.w) / 2;
 
    // sets initial y-position of object
    dest.y = (1000 - dest.h) / 2;
 

    // speed of box
    int speed = 300;

    int quit = 0;
    while (!quit){
        SDL_Event event;

        // Events management
        while(SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT:{
                    quit = 1;
                }break;

                case SDL_KEYDOWN:
                    // keyboard API for key pressed
                    switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_W:
                    case SDL_SCANCODE_UP:
                        dest.y -= speed / 30;
                        break;
                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_LEFT:
                        dest.x -= speed / 30;
                        break;
                    case SDL_SCANCODE_S:
                    case SDL_SCANCODE_DOWN:
                        dest.y += speed / 30;
                        break;
                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        dest.x += speed / 30;
                        break;
                    default:
                        break;
                
                }
            }
        }

         // right boundary
        if (dest.x + dest.w > 1000)
            dest.x = 1000 - dest.w;
 
        // left boundary
        if (dest.x < 0)
            dest.x = 0;
 
        // bottom boundary
        if (dest.y + dest.h > 1000)
            dest.y = 1000 - dest.h;
 
        // upper boundary
        if (dest.y < 0)
            dest.y = 0;
 
        // clears the screen
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, tex, NULL, &dest);
 
        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(renderer);
 
        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }


    // destroy texture
    SDL_DestroyTexture(tex);
 
    // destroy renderer
    SDL_DestroyRenderer(renderer);
 
    // destroy window
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}