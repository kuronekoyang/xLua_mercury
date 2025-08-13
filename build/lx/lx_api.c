#include "lapi.c"

#include "lauxlib.h"
#include "lx_api.h"
#include "lx_do.h"
#include "lx_table.h"

LUA_API void lx_table_clear(lua_State *L, int idx)
{
    lua_lock(L);
    Table *t = gettable(L, idx);
    lxH_clear_array(t);
    lxH_clear_hash(t);
    lua_unlock(L);
}

LUA_API void lx_table_clear_array(lua_State *L, int idx)
{
    lua_lock(L);
    Table *t = gettable(L, idx);
    lxH_clear_array(t);
    lua_unlock(L);
}

LUA_API void lx_table_clear_hash(lua_State *L, int idx)
{
    lua_lock(L);
    Table *t = gettable(L, idx);
    lxH_clear_hash(t);
    lua_unlock(L);
}

LUA_API void lx_table_clear_int_keys(lua_State *L, int idx)
{
    lua_lock(L);
    Table *t = gettable(L, idx);
    lxH_clear_int_keys(t);
    lua_unlock(L);
}

LUA_API void lx_table_grow_to_target(lua_State *L, int idx, int targetIdx)
{
    lua_lock(L);
    Table *t = gettable(L, idx);
    const Table *target = gettable(L, targetIdx);
    lxH_grow_to_target(L, t, target);
    lua_unlock(L);
}

LUA_API void lx_table_grow(lua_State *L, int idx, unsigned int array_size, unsigned int hash_size)
{
    lua_lock(L);
    Table *t = gettable(L, idx);
    lxH_grow(L, t, array_size, hash_size);
    lua_unlock(L);
}

LUA_API void lx_table_shrink(lua_State *L, int idx)
{
    lua_lock(L);
    Table *t = gettable(L, idx);
    lxH_shrink(L, t);
    lua_unlock(L);
}

LUA_API void lx_table_capacity(lua_State *L, int idx, unsigned int *array_size, unsigned int *hash_size)
{
    lua_lock(L);
    const Table *t = gettable(L, idx);
    *hash_size = (unsigned int)allocsizenode(t);
    *array_size = luaH_realasize(t);
    lua_unlock(L);
}

LUA_API void lx_table_size(lua_State *L, int idx, unsigned int *array_size, unsigned int *hash_size)
{
    lua_lock(L);
    const Table *t = gettable(L, idx);
    lxH_size(L, t, array_size, hash_size);
    lua_unlock(L);
}

LUA_API int lx_is_empty_func(lua_State *L, int idx)
{
    const StkId func = index2stack(L, idx);
    return lxD_is_empty_func(func);
}

LUA_API lua_Integer lx_raw_integer(lua_State *L, int idx)
{
    const TValue *o = index2value(L, idx);
    return o->value_.i;
}

LUA_API int lx_is_callable(lua_State *L, int idx)
{
    const StkId func = index2stack(L, idx);
    return lxD_is_callable(L, func);
}

LUA_API void lx_intern_string(lua_State *L, const char *str, InternString *buffer)
{
    TValue *dest = (TValue *)buffer;
    int oldtop = lua_gettop(L);
    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    lua_pushstring(L, str);
    const TValue *o = index2value(L, -1);
    *dest = *o;
    lua_rawseti(L, LUA_REGISTRYINDEX, ref);
    lua_settop(L, oldtop);
}

LUA_API void lx_push_intern_string(lua_State *L, const InternString *buffer)
{
    lua_lock(L);
    setobj2s(L, L->top, (const TValue *)buffer);
    api_incr_top(L);
    lua_unlock(L);
}
