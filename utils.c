#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static void require_init(bool module, const char *name) {
  if (!module) {
    printf("Failed to initialize %s.\n", name);
    exit(-1);
  }
}