#ifndef GE_TYPEWRITER_H
#define GE_TYPEWRITER_H

enum TYPEWRITER_TYPE
{
    TYPE_TEXT,
    TYPE_IMG,
    TYPE_POPUP
};

void typewriter(int scene);

const music_item *resolve_typewriter_music(int scene);
const conversation *resolve_typewriter_conversation(int scene);
const sound_item *resolve_typewriter_sfx(int scene);
int resolve_typewriter_type(int scene);

#endif