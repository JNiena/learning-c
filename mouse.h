#include <allegro5/events.h>
#include <allegro5/mouse.h>

struct Mouse {
  bool buttons[ALLEGRO_MOUSE_MAX_EXTRA_AXES];
  int x;
  int y;
};

struct Mouse *mouse_init(ALLEGRO_EVENT_QUEUE *queue);
void mouse_update(struct Mouse *mouse, ALLEGRO_EVENT *event);
bool mouse_is_pressed(struct Mouse *mouse, int key);
int mouse_x(struct Mouse *mouse);
int mouse_y(struct Mouse *mouse);
void mouse_destroy(struct Mouse *mouse);