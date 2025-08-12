#ifndef __LX_TABLE_H__
#define __LX_TABLE_H__

#include "lobject.h"
#include "lua.h"

LUAI_FUNC void lxH_clear_array(Table *t);
LUAI_FUNC void lxH_clear_hash(Table *t);
LUAI_FUNC void lxH_clear_int_keys(Table *t);
LUAI_FUNC void lxH_try_grow(lua_State *L, Table *t, Table *tref);
LUAI_FUNC void lxH_grow(lua_State *L, Table *t, unsigned int new_array_size, unsigned int new_hash_size);
LUAI_FUNC void lxH_shrink(lua_State *L, Table *t);
LUAI_FUNC void lxH_size(lua_State *L, const Table *t, unsigned int *array_size, unsigned int *hash_size);

#endif
