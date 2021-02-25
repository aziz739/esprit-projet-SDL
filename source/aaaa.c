#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  SDL_Surface *screen = NULL, *background = NULL, *newgame = NULL,
              *settings = NULL, *exit = NULL, *newgamepressed = NULL,
              *settingspressed = NULL, *exitpressed = NULL;
  Mix_Music *music = NULL;
  Mix_Chunk *click = NULL;

  SDL_Init(SDL_INIT_VIDEO);
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("impossible d'inisialiser:%s\n", SDL_GetError());
    return 1;
  } else {
    screen = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  }

  if (screen  == NULL) {
    printf("unable to set video mode : %s\n", SDL_GetError());
    return 1;
  }
  SDL_Rect positionBg, positionnewgame, positionset, positionexit;
  positionBg.x = 0;
  positionBg.y = 0;
  positionnewgame.x = 580;
  positionnewgame.y = 480;
  positionset.x = 580;
  positionset.y = 540;
  positionexit.x = 580;
  positionexit.y = 600;

  background = IMG_Load("bg.jpg");
  if (background == NULL) {
    printf("unable to load\n");
    return 1;
  }

  newgame = IMG_Load("newgame.png");
  if (newgame == NULL) {
    printf("unable to load\n");
    return 1;
  }

  newgamepressed = IMG_Load("newgamepressed.png");
  if (newgame == NULL) {
    printf("unable to load\n");
    return 1;
  }

  settings = IMG_Load("settings.png");
  if (settings == NULL) {
    printf("unable to load\n");
    return 1;
  }

  settingspressed = IMG_Load("settingspressed.png");
  if (settings == NULL) {
    printf("unable to load\n");
    return 1;
  }

  exit = IMG_Load("exit.png");
  if (exit == NULL) {
    printf("unable to load\n");
    return 1;
  }

  exitpressed = IMG_Load("exitpressed.png");
  if (exit == NULL) {
    printf("unable to load\n");
    return 1;
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) ==
      -1) {
    printf("%s", Mix_GetError());
  }
  music = Mix_LoadMUS("music.mp3");
  Mix_PlayMusic(music, -1);
  click = Mix_LoadWAV("beep.ogg");

  SDL_Event event;
  int done;
  done = 1;
  while (done == 1) {
    SDL_WaitEvent(&event);
    SDL_BlitSurface(background, NULL, screen, &positionBg);
    SDL_BlitSurface(newgame, NULL, screen, &positionnewgame);
    SDL_BlitSurface(settings, NULL, screen, &positionset);
    SDL_BlitSurface(exit, NULL, screen, &positionexit);
    SDL_Flip (screen);

    switch (event.type) {
    case SDL_QUIT:
      done = 0;
      break;

    case SDL_MOUSEMOTION:
      if (event.button.x >= positionnewgame.x &&
        event.button.y >= positionnewgame.y &&
        event.button.x <= positionnewgame.x + newgame->w &&
        event.button.y <= positionnewgame.y + newgame->h){

          SDL_BlitSurface(newgamepressed, NULL, screen, &positionnewgame);
          SDL_Flip(screen);
        }



           if (event.button.x >= positionset.x &&
            event.button.y >= positionset.y &&
            event.button.x <= positionset.x + settings->w &&
            event.button.y <= positionset.y +settings->h)
            {
              SDL_BlitSurface(settingspressed, NULL, screen, &positionset);
              SDL_Flip(screen);
             }


             if (event.button.x >= positionexit.x &&
              event.button.y >= positionexit.y &&
              event.button.x <= positionexit.x + settings->w &&
              event.button.y <= positionexit.y +settings->h){
                SDL_BlitSurface(exitpressed, NULL, screen, &positionexit);
                SDL_Flip(screen);
          }
    break;
    case SDL_MOUSEBUTTONUP:
      if (event.button.x >= positionnewgame.x &&
         event.button.y >= positionnewgame.y &&
         event.button.x <= positionnewgame.x + newgame->w &&
         event.button.y <= positionnewgame.y + newgame->h){
           if(event.button.button == SDL_BUTTON_LEFT)
           {
             SDL_BlitSurface(newgamepressed, NULL, screen, &positionnewgame);
             Mix_PlayChannel(1,click,0);
           }
           }

        if (event.button.x >= positionset.x &&
              event.button.y >= positionset.y &&
              event.button.x <= positionset.x + settings->w &&
              event.button.y <= positionset.y +settings->h)
              {
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                  SDL_BlitSurface(settingspressed, NULL, screen, &positionset);
                  Mix_PlayChannel(1,click,0);
                  done=1;
                }
              }

          if (event.button.x >= positionexit.x &&
               event.button.y >= positionexit.y &&
               event.button.x <= positionexit.x + settings->w &&
               event.button.y <= positionexit.y +settings->h)
               {
                 if(event.button.button == SDL_BUTTON_LEFT)
                    {
                      SDL_BlitSurface(exitpressed, NULL, screen, &positionexit);
                      Mix_PlayChannel(1,click,0);
                      SDL_BlitSurface(background, NULL, screen, &positionBg);
                    }
               }
          break;
  }
  }
  Mix_FreeMusic(music);
  SDL_Quit();
  return 0;
}
