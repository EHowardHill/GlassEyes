#include "ge_dialogue.h"
#include "ge_text.h"
#include "ge_text_auto.h"

const char *ITEM_LABELS[ITEMS_SIZE] = {
	"Lime",
	"Photograph",
	"Document",
	"Ticket",
	"Flint",
	"Steel",
	"Sticks",
	"Stones",
	"Pie",
	"Water Bottle",
};

const bool ITEM_DROP[ITEMS_SIZE] = {
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
};

const conversation *ITEM_CONVOS[ITEMS_SIZE] = {
	&convo_obj_lime,
	&convo_obj_photograph,
	&convo_obj_document,
	&convo_obj_ticket,
	&convo_obj_flint,
	&convo_obj_steel,
	&convo_obj_sticks,
	&convo_obj_stones,
	&convo_obj_pie,
	&convo_obj_water_bottle,
};
