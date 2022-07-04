#include "keyboard.h"
#include "utils.c"
#include <allegro5/events.h>
#include <allegro5/keyboard.h>
#include <stdlib.h>
#include <string.h>

struct Keyboard *keyboard_init(ALLEGRO_EVENT_QUEUE *queue) {
  if (!al_is_keyboard_installed()) {
    require_init(al_install_keyboard(), "keyboard");
  }
  al_register_event_source(queue, al_get_keyboard_event_source());
  struct Keyboard *keyboard = malloc(sizeof(struct Keyboard));
  memset(keyboard->keys, 0, sizeof(keyboard->keys));
  return keyboard;
}

void keyboard_update(struct Keyboard *keyboard, ALLEGRO_EVENT *event) {
  switch (event->type) {
  case ALLEGRO_EVENT_TIMER:
    for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
      keyboard->keys[i] &= KEY_SEEN;
    }
    break;
  case ALLEGRO_EVENT_KEY_DOWN:
    keyboard->keys[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
    break;
  case ALLEGRO_EVENT_KEY_UP:
    keyboard->keys[event->keyboard.keycode] &= KEY_RELEASED;
    break;
  }
}

bool keyboard_is_pressed(struct Keyboard *keyboard, int key) {
  return keyboard->keys[key];
}

void keyboard_destroy(struct Keyboard *keyboard) { free(keyboard); }