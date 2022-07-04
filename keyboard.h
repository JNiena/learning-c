#include <allegro5/events.h>
#include <allegro5/keycodes.h>
#include <stdbool.h>

#define KEY_SEEN 1
#define KEY_RELEASED 2

struct Keyboard {
  unsigned char keys[ALLEGRO_KEY_MAX];
};

struct Keyboard *keyboard_init(ALLEGRO_EVENT_QUEUE *queue);
void keyboard_update(struct Keyboard *keyboard, ALLEGRO_EVENT *event);
bool keyboard_is_pressed(struct Keyboard *keyboard, int key);
void keyboard_destroy(struct Keyboard *keyboard);