#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  SDL_Rect dest;
  SDL_Surface *image, *pressedImage;
} Button;

int mouseOver(SDL_Event event, Button butt)
{
  if (event.button.x >= butt.dest.x &&
      event.button.y >= butt.dest.y &&
      event.button.x <= butt.dest.x + butt.image->w &&
      event.button.y <= butt.dest.y + butt.image->h) {
        return 1;
      }
  return 0;
}

void menu_update(SDL_Surface *screen , SDL_Event *event)
{
}

int level_1_update(SDL_Surface *screen , SDL_Event *event)
{
  SDL_Surface *background1 = NULL;
  SDL_Rect positionBg1;

  background1 = IMG_Load("image/bg.jpg");
  positionBg1.x = 0;
  positionBg1.y = 0;
  SDL_BlitSurface(background1, NULL, screen, &positionBg1);
  switch((*event).type)
  {
    case SDL_QUIT:
    return 0;
    break;
  }
  return 1;
}




int main() {
  SDL_Surface *screen = NULL, *background = NULL, *gun=NULL;;
  Button newgame, settings, exit;
  Mix_Music *music = NULL;
  Mix_Chunk *click = NULL;
  int boucle=0;
  int choix=-1;


  SDL_Init(SDL_INIT_VIDEO);
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("impossible d'inisialiser:%s\n", SDL_GetError());
    return 1;
  } else {
    screen = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  }

  if (screen == NULL) {
    printf("unable to set video mode : %s\n", SDL_GetError());
    return 1;
  }
  SDL_Rect positionBg,positiongun ;
  positionBg.x = 0;
  positionBg.y = 0;
  positiongun.x= 430;
  positiongun.y= 115;
  newgame.dest.x = 580;
  newgame.dest.y = 480;
  settings.dest.x = 580;
  settings.dest.y = 540;
  exit.dest.x = 580;
  exit.dest.y = 600;


  background = IMG_Load("image/bg.jpg");
  if (background == NULL) {
    printf("unable to load\n");
    return 1;
  }

  gun = IMG_Load("image/gun.jpg");
  if (gun == NULL) {
    printf("unable to load\n");
    return 1;
  }

  newgame.image = IMG_Load("image/newgame.png");
  if (newgame.image == NULL) {
    printf("unable to load\n");
    return 1;
  }

  newgame.pressedImage = IMG_Load("image/newgamepressed.png");
  if (newgame.pressedImage == NULL) {
    printf("unable to load\n");
    return 1;
  }

  settings.image = IMG_Load("image/settings.png");
  if (settings.image == NULL) {
    printf("unable to load\n");
    return 1;
  }

  settings.pressedImage = IMG_Load("image/settingspressed.png");
  if (settings.pressedImage == NULL) {
    printf("unable to load\n");
    return 1;
  }

  exit.image = IMG_Load("image/exit.png");
  if (exit.image == NULL) {
    printf("unable to load\n");
    return 1;
  }

  exit.pressedImage = IMG_Load("image/exitpressed.png");
  if (exit.pressedImage == NULL) {
    printf("unable to load\n");
    return 1;
  }


  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) ==
      -1) {
    printf("%s", Mix_GetError());
  }
  music = Mix_LoadMUS("musique/music.mp3");
  Mix_PlayMusic(music, -1);
  click = Mix_LoadWAV("musique/beep.ogg");
  SDL_Event event;
  int done = 1;
  while (done == 1) {
    SDL_WaitEvent(&event);
    if(boucle==0)
    {
    SDL_BlitSurface(background, NULL, screen, &positionBg);

    SDL_BlitSurface(settings.image, NULL, screen, &settings.dest);
    SDL_BlitSurface(exit.image, NULL, screen, &exit.dest);

      SDL_BlitSurface(newgame.image, NULL, screen, &newgame.dest);
      SDL_BlitSurface(gun, NULL, screen, &positiongun);

    switch (event.type) {
    case SDL_QUIT:
      done = 0;
      break;
    case SDL_MOUSEBUTTONDOWN:
      if (mouseOver(event, newgame) == 1)
      {
            SDL_BlitSurface(newgame.pressedImage, NULL, screen, &newgame.dest);
      }

      if (mouseOver(event, settings) == 1)
      {
            SDL_BlitSurface(settings.pressedImage, NULL, screen, &settings.dest);
      }

      if (mouseOver(event, exit) == 1)
      {
            SDL_BlitSurface(exit.pressedImage, NULL, screen, &exit.dest);
      }
      break;

    case SDL_MOUSEBUTTONUP:
        if (mouseOver(event, newgame) == 1)
        {
          if(event.button.button == SDL_BUTTON_LEFT)
          {
            Mix_PlayChannel(1,click,0);
            boucle=1;
          }
        }

        if (mouseOver(event, settings) == 1)
        {
          if(event.button.button == SDL_BUTTON_LEFT)
          {
            Mix_PlayChannel(1,click,0);
            boucle=1;
          }
        }

          if (mouseOver(event, exit) == 1)
          {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
              Mix_PlayChannel(1,click,0);
              boucle=1;
            }
          }
        break;

        case SDL_KEYDOWN:
        {
          if(event.key.keysym.sym == SDLK_DOWN)
          {
            Mix_PlayChannel(1,click,0);
              choix++;
              if(choix>=2)
              {choix=2;}
          }
          if(event.key.keysym.sym == SDLK_UP)
          {
            Mix_PlayChannel(1,click,0);
              choix--;
              if(choix<=-1)
              {choix=0;}
          }

          switch(choix)
          {
            case 0 :
              SDL_BlitSurface(newgame.pressedImage, NULL, screen, &newgame.dest);
              SDL_Flip(screen);
              break;
            case 1 :
              SDL_BlitSurface(settings.pressedImage, NULL, screen, &settings.dest);
              SDL_Flip(screen);
              break;
            case 2 :
               SDL_BlitSurface(exit.pressedImage, NULL, screen, &exit.dest);
               SDL_Flip(screen);
               break;
          }
        }
    }
  }else {
    done =level_1_update(screen , &event);
    switch(event.type)
    {
      case SDL_KEYUP:
      if (event.key.keysym.sym == SDLK_ESCAPE)
      {
        boucle=0;
      }
      break;
    }
  }
    SDL_Flip(screen);
  }
  Mix_FreeMusic(music);
  SDL_Quit();
  return 0;
}
