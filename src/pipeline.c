#include "lve/pipeline.h"

#include <stdio.h>

static char *read_file(const char *filepath) {
  FILE *file = fopen(filepath, "rb");
  if (file != NULL) {
    fclose(file);
  }

  // TODO: What happens if we cannot open the file?
  
  return NULL;
}

static void create_graphics_pipeline(LvePipeline *pipeline,
                                     const char *vert_filepath,
                                     const char *frag_filepath) {}
