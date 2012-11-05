#include "label.h"

#include <string.h>
#include <stdio.h>
#include "utils/math.h"

static void applyScale(float scale, Geom* node){

	matIdent(node->mat_world);

	float mat_scale[16];
	matIdent(mat_scale);
	matScale(mat_scale, scale);

	matMul(mat_scale, node->mat_world, node->mat_world);

}

static Geom* geomGet(void* object){

	Label* lbl = (Label*)object;
	Geom* chars = lbl->chars;
	Geom* geom_char;

	char* text = lbl->text;
	static int idx = 0;
	static float cursor[2] = {0, 0};

	float offset_c = 1.5 * lbl->scale;

	while (text[idx] != '\0'){

		switch (text[idx]){
			case '\n':
				cursor[0] = 0;
				cursor[1] -= offset_c;
				++idx;
				break;
			case ' ':
				cursor[0] += offset_c;
				++idx;
		}

		geom_char = chars + (int)(text[idx] - '!');
		applyScale(lbl->scale, geom_char);
		geom_char->mat_world[12] = lbl->pos[0] + cursor[0];
		geom_char->mat_world[13] = lbl->pos[1] + cursor[1];

		cursor[0] += offset_c;
		++idx;

		return geom_char;
	}

	idx = 0;
	cursor[0] = cursor[1] = 0;
	return NULL;

}

void labelInit(Label* lbl, float x, float y, Geom* chars){

	lbl->geomGet = (Geom* (*)(void*))geomGet;
	lbl->scale = 1;
	lbl->pos[0] = x; lbl->pos[1] = y;
	lbl->chars = chars;
}

void labelSet(Label* lbl, char* text){

	lbl->text = text;
}

void labelScaleSet(Label* lbl, float scale){

	lbl->scale = scale;
}
