#ifndef __LX_API_H__
#define __LX_API_H__

#include "lua.h"

typedef struct
{
    lua_Integer a;
    lua_Integer b;
} InternString;

LUA_API void lx_table_clear(lua_State *L, int idx);
LUA_API void lx_table_clear_array(lua_State *L, int idx);
LUA_API void lx_table_clear_hash(lua_State *L, int idx);
LUA_API void lx_table_clear_int_keys(lua_State *L, int idx);
LUA_API void lx_table_try_grow(lua_State *L, int idx, int refIdx);
LUA_API void lx_table_grow(lua_State *L, int idx, unsigned int array_size, unsigned int hash_size);
LUA_API void lx_table_shrink(lua_State *L, int idx);
LUA_API void lx_table_capacity(lua_State *L, int idx, unsigned int *array_size, unsigned int *hash_size);
LUA_API void lx_table_size(lua_State *L, int idx, unsigned int *array_size, unsigned int *hash_size);
LUA_API int lx_is_empty_func(lua_State *L, int idx);
LUA_API lua_Integer lx_raw_integer(lua_State *L, int idx);
LUA_API int lx_is_callable(lua_State *L, int idx);
LUA_API void lx_intern_string(lua_State *L, const char *str, InternString *buffer);
LUA_API void lx_push_intern_string(lua_State *L, const InternString *buffer);

#define lx_is_table_or_userdata(L, idx)                                                                                \
    ({                                                                                                                 \
        int __lx_type_t = lua_type(L, idx);                                                                            \
        __lx_type_t == LUA_TTABLE || __lx_type_t == LUA_TUSERDATA;                                                     \
    })

#endif
