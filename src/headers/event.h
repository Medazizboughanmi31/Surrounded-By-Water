#ifndef EVENT_H_DEFINED
#define EVENT_H_DEFINED

#include "./common.h"

void event_manager(GameObject *G);

void window_events(SDL_Event *event, GameWindow *window);

#endif