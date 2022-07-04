#include "mouse.h"
#include "utils.c"
#include <allegro5/events.h>
#include <allegro5/mouse.h>
#include <stdbool.h>

struct Mouse *mouse_init(ALLEGRO_EVENT_QUEUE *queue) {
  if (!al_is_mouse_installed()) {
    require_init(al_install_mouse(), "mouse");
  }
  al_register_event_source(queue, al_get_mouse_event_source());
  return (struct Mouse *)malloc(sizeof(struct Mouse));
}

void mouse_update(struct Mouse *mouse, ALLEGRO_EVENT *event) {
  switch (event->type) {
  case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
    mouse->buttons[event->mouse.button] = true;
    break;
  case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
    mouse->buttons[event->mouse.button] = false;
    break;
  case ALLEGRO_EVENT_MOUSE_AXES:
    mouse->x = event->mouse.x;
    mouse->y = event->mouse.y;
    break;
  }
}

bool mouse_is_pressed(struct Mouse *mouse, int key) {
  return mouse->buttons[key];
}

int mouse_x(struct Mouse *mouse) { return mouse->x; }

int mouse_y(struct Mouse *mouse) { return mouse->y; }

void mouse_destroy(struct Mouse *mouse) { free(mouse); }