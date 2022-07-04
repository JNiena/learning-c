#include "utils/sc_array.h"
#include <allegro5/color.h>
#include <allegro5/events.h>
#include <allegro5/keycodes.h>

struct Renderer {
  struct sc_array_ptr items;
  struct ALLEGRO_COLOR clear_color;
  void (*pipeline)(void *item);
};

struct Renderer *renderer_init(ALLEGRO_EVENT_QUEUE *queue,
                               ALLEGRO_COLOR clear_color);
void renderer_update(struct Renderer *renderer, ALLEGRO_EVENT *event);
void renderer_add_item(struct Renderer *renderer, void *item);
void renderer_remove_item(struct Renderer *renderer, void *item);
void renderer_clear_items(struct Renderer *renderer);
void renderer_set_pipeline(struct Renderer *renderer,
                           void (*pipeline)(void *item));
void renderer_destroy(struct Renderer *renderer);