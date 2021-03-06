#include "./headers/dev.h"

void lib_errorLog(char msg[], const char *error)
{
  printf("%s: %s\n", msg, error);
}

void coords_log(float x, float y, float w, float h)
{
  printf("x: %.3f   y: %.3f   w: %.3f   h: %.3f\n", x, y, w, h);
}

void load_Texture_Img(SDL_Texture **texture, char path[], SDL_Renderer **renderer)
{
  SDL_Surface *tempSurface = NULL;
  SDL_RWops *tempPath = NULL;

  tempPath = tempPath = SDL_RWFromFile(path, "rb");
  if (tempPath == NULL)
    lib_errorLog("failed at getting img path", SDL_GetError());

  tempSurface = IMG_LoadPNG_RW(tempPath);
  if (tempSurface == NULL)
    lib_errorLog("failed at loading img from path", IMG_GetError());

  SDL_DestroyTexture(*texture);
  *texture = SDL_CreateTextureFromSurface(*renderer, tempSurface);

  SDL_FreeSurface(tempSurface);
  SDL_FreeRW(tempPath);
}

void load_Texture_Text(SDL_Texture **texture, TTF_Font **font, char text[], SDL_Color color, SDL_Renderer **renderer)
{
  SDL_Surface *tempSurface = NULL;

  tempSurface = TTF_RenderUTF8_Blended(*font, text, color);
  if (tempSurface == NULL)
    lib_errorLog("failed at rendering font", TTF_GetError());

  SDL_DestroyTexture(*texture);
  *texture = SDL_CreateTextureFromSurface(*renderer, tempSurface);

  if (*texture == NULL)
  {
    lib_errorLog("failed at creating texture from font", SDL_GetError());
  }

  SDL_FreeSurface(tempSurface);
}

float get_Text_W_ratio(TTF_Font *font, char text[])
{
  int text_w = 0, text_h = 0;
  float text_w_ratio = 1;

  int mesure = TTF_SizeUTF8(font, text, &text_w, &text_h);
  if (mesure != 0)
    lib_errorLog("failed at calculating the text mesures", TTF_GetError());

  text_w_ratio = (float)text_h / text_w;
  return text_w_ratio;
}

int get_Random_Number(MTRand *r, int min, int max)
{
  int rd = (genRandLong(r) % (max - min + 1)) + min;
  return rd;
}

void load_Sprite(SDL_Texture *texture[], int num, char path[], SDL_Renderer **renderer)
{
  char complete_Path[100];
  for (int i = 0; i < num; i++)
  {
    char img_num[3];
    itoa(i, img_num, 10);

    strcpy(complete_Path, path);
    strcat(complete_Path, img_num);
    strcat(complete_Path, ".png\0");

    texture[i] = NULL;
    load_Texture_Img(&(texture[i]), complete_Path, renderer);
  }
}
