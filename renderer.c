#include "renderer.h"
#include "utils/sc_array.h"
#include <allegro5/allegro5.h>
#include <allegro5/color.h>
#include <allegro5/events.h>
#include <stdlib.h>

struct Renderer *renderer_init(ALLEGRO_EVENT_QUEUE *queue,
                               ALLEGRO_COLOR clear_color) {
  struct Renderer *renderer = malloc(sizeof(struct Renderer));
  sc_array_init(&renderer->items);
  renderer->clear_color = clear_color;
  return renderer;
}

void renderer_update(struct Renderer *renderer, ALLEGRO_EVENT *event) {
  if (event->type != ALLEGRO_EVENT_TIMER)
    return;
  al_clear_to_color(renderer->clear_color);
  for (unsigned int i = 0; i < sc_array_size(&renderer->items); i++) {
    renderer->pipeline(renderer->items.elems[i]);
  }
  al_flip_display();
}

void renderer_add_item(struct Renderer *renderer, void *item) {
  sc_array_add(&renderer->items, item);
}

void renderer_remove_item(struct Renderer *renderer, void *item) {
  int remove_index = -1;
  for (unsigned int i = 0; i < sc_array_size(&renderer->items); i++) {
    if (renderer->items.elems[i] == item) {
      remove_index = i;
      break;
    }
  }
  if (remove_index != -1) {
    sc_array_del(&renderer->items, remove_index);
  }
}

void renderer_clear_items(struct Renderer *renderer) {
  sc_array_clear(&renderer->items);
}

void renderer_set_pipeline(struct Renderer *renderer,
                           void (*pipeline)(void *)) {
  renderer->pipeline = pipeline;
}

void renderer_destroy(struct Renderer *renderer) {
  sc_array_term(&renderer->items);
  free(renderer);
}