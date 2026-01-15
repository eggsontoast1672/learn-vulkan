#include "lve/pipeline.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char *data;
  size_t size;
} FileContents;

static FileContents read_file(const char *filepath) {
  FILE *file = fopen(filepath, "rb");
  if (file == NULL) {
    return (FileContents){
        .data = NULL,
        .size = 0,
    };
  }

  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *contents = malloc(size);
  fread(contents, 1, size, file);

  fclose(file);

  return (FileContents){
      .data = contents,
      .size = size,
  };
}

static void create_graphics_pipeline(LvePipeline *pipeline,
                                     const char *vert_filepath,
                                     const char *frag_filepath) {
  FileContents vert_code = read_file(vert_filepath);
  FileContents frag_code = read_file(frag_filepath);

  printf("Vertex shader code size: %lu\n", vert_code.size);
  printf("Fragment shader code size: %lu\n", frag_code.size);

  free(frag_code.data);
  free(vert_code.data);
}

void lve_pipeline_create(LvePipeline *pipeline, const char *vert_filepath,
                         const char *frag_filepath) {
  create_graphics_pipeline(pipeline, vert_filepath, frag_filepath);
}
