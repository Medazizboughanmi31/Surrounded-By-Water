#include "../headers/logic.h"

void logic_manager(GameObject *G)
{
  if (G->window.game_scene == 0)
  {
    menu_Intro_Animation(&(G->UI.common_UI), &(G->window), &(G->dev));
    wind_Animation(&(G->UI.common_UI), &(G->window), &(G->sound), &(G->dev));
    bird_Animation(&(G->UI.common_UI), &(G->window), &(G->sound), &(G->dev));
    shortcut_Input(&(G->input), &(G->sound), &(G->window), &(G->UI), &(G->dev));
  }
  else if (G->window.game_scene == 1)
  {

    static int player_spawned = 0; ///TODO: delete this
    if (player_spawned == 0)
    {
      spawn_Player(&(G->logic), &(G->window));
      player_spawned = 1;
    }

    update_Player_Coords(&(G->logic), &(G->window), &(G->input));
    update_Cam_Coords(&(G->logic), &(G->window), &(G->UI.in_game_UI));
  }
  G->input.num_keys = 0;
}