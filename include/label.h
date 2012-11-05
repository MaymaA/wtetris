#ifndef WTET_LABEL_H
#define WTET_LABEL_H

#include "utils/rawdimp.h"

typedef struct{
	Geom* (*geomGet)(void* object);
	float scale;
	float pos[2];
	Geom* chars;
	char* text;
} Label;

void labelInit(Label* lbl, float x, float y, Geom* chars);
void labelSet(Label* lbl, char* text);
void labelScaleSet(Label* lbl, float scale);

#endif
