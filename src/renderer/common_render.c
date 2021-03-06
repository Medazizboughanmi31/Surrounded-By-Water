#include "../headers/renderer.h"

void update_renderer(GameWindow *window)
{
  int setColor = SDL_SetRenderDrawColor(window->mainRenderer, 0, 0, 0, 255);
  if (setColor != 0)
    lib_errorLog("failed at setting renderer color", SDL_GetError());

  int update_Renderer = SDL_RenderClear(window->mainRenderer);

  if (update_Renderer != 0)
    lib_errorLog("failed at updating window", SDL_GetError());
}

void render_FPS(GameWindow *window, DevUI *ui, GameDev dev)
{
  static float render_FPS_Delta = 100;
  static SDL_Rect FPS_Coords = {0, 0, 0, 0};

  render_FPS_Delta += dev.deltaTime * 1000;

  if (render_FPS_Delta / 100 >= 1)
  {
    // updating texture
    char displayFPS[5];
    itoa(dev.FPS, displayFPS, 10);

    load_Texture_Text(&(ui->FPS_Text), &(ui->dev_Font), displayFPS, ui->FPS_Color, &(window->mainRenderer));

    float text_w_ratio = get_Text_W_ratio(ui->dev_Font, displayFPS);
    FPS_Coords.x = 1;
    FPS_Coords.y = 1;
    FPS_Coords.w = 10 * strlen(displayFPS);
    FPS_Coords.h = 10 * text_w_ratio * strlen(displayFPS);

    render_FPS_Delta = 0;
  }

  int rendered = SDL_RenderCopy(window->mainRenderer, ui->FPS_Text, NULL, &FPS_Coords);
  if (rendered != 0)
    lib_errorLog("failed at blit surface", SDL_GetError());
}

void render_BlackLayer(GameWindow *window, Uint8 alpha)
{
  int setBlend = SDL_SetRenderDrawBlendMode(window->mainRenderer, SDL_BLENDMODE_BLEND);
  if (setBlend != 0)
    lib_errorLog("failed at setting blend mode", SDL_GetError());

  int setColor = SDL_SetRenderDrawColor(window->mainRenderer, 0, 0, 0, alpha);
  if (setColor != 0)
    lib_errorLog("failed at setting renderer color", SDL_GetError());

  SDL_Rect fullWindow = {0, 0, window->w, window->h};

  int fillWindow = SDL_RenderFillRect(window->mainRenderer, &fullWindow);
  if (fillWindow != 0)
    lib_errorLog("failed at fill rect", SDL_GetError());
}

void render_Outline(GameWindow *window, DevUI *ui)
{
  for (int i = 0; i < ui->outline_num; i++)
  {
    int setColor = SDL_SetRenderDrawColor(window->mainRenderer, ui->outlines[i].color.r, ui->outlines[i].color.g, ui->outlines[i].color.b, ui->outlines[i].color.a);
    if (setColor != 0)
      lib_errorLog("failed at setting renderer color", SDL_GetError());

    int outline = SDL_RenderDrawRect(window->mainRenderer, &(ui->outlines[i].coords));
    if (outline != 0)
      lib_errorLog("failed at rendering the outline", SDL_GetError());

    setColor = SDL_SetRenderDrawColor(window->mainRenderer, 255, 0, 0, 255);
    outline = SDL_RenderDrawPoint(window->mainRenderer, ui->outlines[i].coords.x + ui->outlines[i].coords.w / 2, ui->outlines[i].coords.y + ui->outlines[i].coords.h / 2);
  }
}
