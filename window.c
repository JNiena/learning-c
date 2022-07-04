#include "window.h"
#include "utils.c"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/display.h>
#include <allegro5/events.h>
#include <allegro5/timer.h>
#include <stdlib.h>

struct Window *window_init(unsigned int width, unsigned int height,
                           unsigned int update_speed,
                           void (*start)(struct Window *window),
                           bool (*update)(struct Window *window),
                           void (*stop)(struct Window *window)) {
  require_init(al_init(), "allegro");
  require_init(al_init_primitives_addon(), "primitives");
  struct Window *window = (struct Window *)malloc(sizeof(struct Window));
  window->_timer = al_create_timer(1.0 / update_speed);
  require_init(window->_timer, "timer");
  window->_queue = al_create_event_queue();
  require_init(window->_queue, "queue");
  window->_display = al_create_display(width, height);
  require_init(window->_display, "display");
  al_register_event_source(window->_queue,
                           al_get_display_event_source(window->_display));
  al_register_event_source(window->_queue,
                           al_get_timer_event_source(window->_timer));
  window->keyboard = keyboard_init(window->_queue);
  window->mouse = mouse_init(window->_queue);
  window->renderer = renderer_init(window->_queue, al_map_rgb(0, 0, 0));
  window->start = start;
  window->update = update;
  window->stop = stop;
  return window;
}

void window_start(struct Window *window) {
  window->start(window);
  ALLEGRO_EVENT event;
  al_start_timer(window->_timer);
  while (true) {
    al_wait_for_event(window->_queue, &event);
    keyboard_update(window->keyboard, &event);
    mouse_update(window->mouse, &event);
    renderer_update(window->renderer, &event);
    if (event.type == ALLEGRO_EVENT_TIMER) {
      if (window->update(window)) {
        break;
      }
    }
  }
  window->stop(window);
  window_destroy(window);
}

void window_destroy(struct Window *window) {
  renderer_destroy(window->renderer);
  keyboard_destroy(window->keyboard);
  mouse_destroy(window->mouse);
  al_destroy_display(window->_display);
  al_destroy_event_queue(window->_queue);
  al_destroy_timer(window->_timer);
}