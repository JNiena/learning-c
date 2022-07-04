#include "keyboard.h"
#include "mouse.h"
#include "renderer.h"
#include <allegro5/display.h>
#include <allegro5/events.h>
#include <allegro5/timer.h>

struct Window {
  struct Renderer *renderer;
  struct Keyboard *keyboard;
  struct Mouse *mouse;
  struct ALLEGRO_TIMER *_timer;
  struct ALLEGRO_EVENT_QUEUE *_queue;
  struct ALLEGRO_DISPLAY *_display;
  void (*start)(struct Window *window);
  bool (*update)(struct Window *window);
  void (*stop)(struct Window *window);
};

struct Window *window_init(unsigned int width, unsigned int height,
                           unsigned int update_speed,
                           void (*start)(struct Window *window),
                           bool (*update)(struct Window *window),
                           void (*stop)(struct Window *window));

void window_start(struct Window *window);

void window_destroy(struct Window *window);