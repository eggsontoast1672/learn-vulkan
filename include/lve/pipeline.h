#pragma once

typedef struct {
} LvePipeline;

void lve_pipeline_create(LvePipeline *pipeline, const char *vert_filepath,
                         const char *frag_filepath);
