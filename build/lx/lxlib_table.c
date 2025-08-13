#include "lauxlib.h"
#include "lua.h"
#include "lx_api.h"
#include "lxlib.h"

static int table_clear(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TTABLE);
    lx_table_clear(L, 1);
    lua_pushvalue(L, 1);
    return 1;
}

static int table_clear_array(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TTABLE);
    lx_table_clear_array(L, 1);
    lua_pushvalue(L, 1);
    return 1;
}

static int table_clear_hash(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TTABLE);
    lx_table_clear_hash(L, 1);
    lua_pushvalue(L, 1);
    return 1;
}

static int table_clear_int_keys(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TTABLE);

    lx_table_clear_int_keys(L, 1);
    lua_pushvalue(L, 1);
    return 1;
}

static int table_grow_to_target(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TTABLE);

    if (!lua_rawequal(L, 1, 2))
    {
        lua_settop(L, 2);
        lx_table_grow_to_target(L, 1, 2);
    }
    lua_pushvalue(L, 1);
    return 1;
}

static int table_grow(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TTABLE);

    const lua_Integer arraysize = lua_tointeger(L, 2);
    const lua_Integer hashsize = lua_tointeger(L, 3);
    lua_settop(L, 3);
    lx_table_grow(L, 1, (unsigned int)(arraysize < 0 ? 0 : arraysize), (unsigned int)(hashsize < 0 ? 0 : hashsize));

    lua_pushvalue(L, 1);
    return 1;
}

static int table_shrink(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TTABLE);

    lua_settop(L, 1);
    lx_table_shrink(L, 1);

    lua_pushvalue(L, 1);
    return 1;
}

static int table_capacity(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TTABLE);

    lua_settop(L, 1);
    unsigned int arraysize = 0;
    unsigned int hashsize = 0;
    lx_table_capacity(L, 1, &arraysize, &hashsize);
    lua_pushinteger(L, (lua_Integer)arraysize);
    lua_pushinteger(L, (lua_Integer)hashsize);
    return 2;
}

static int table_size(lua_State *L)
{
    if (!lua_istable(L, 1))
    {
        lua_pushinteger(L, 0);
    }
    else
    {
        unsigned int array_size = 0;
        unsigned int hash_size = 0;
        lx_table_size(L, 1, &array_size, &hash_size);
        lua_pushinteger(L, (lua_Integer)(array_size + hash_size));
    }
    return 1;
}

static int table_pack(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TTABLE);
    const int idx = (int)luaL_checkinteger(L, 2);

    const int n = lua_gettop(L);             /* number of elements to pack */
    for (int i = n - 3 + idx; i >= idx; i--) /* assign elements */
        lua_seti(L, 1, i);
    lua_pushinteger(L, n - 2);
    return 2; /* return table and size */
}

static int table_copy(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TTABLE);

    if (!lua_rawequal(L, 1, 2))
    {
        lua_settop(L, 2);
        lx_table_grow_to_target(L, 1, 2);
        lua_pushnil(L);
        while (lua_next(L, 2))
        {
            lua_pushvalue(L, -2);
            lua_pushvalue(L, -2);
            lua_rawset(L, 1);
            lua_pop(L, 1);
        }
    }
    lua_pushvalue(L, 1);
    return 1;
}

static int less_compare(lua_State *L, int a, int b, int funcIdx)
{
    switch (lua_type(L, funcIdx))
    {
    case LUA_TNIL:
        return lua_compare(L, a, b, LUA_OPLT); /* a < b */
    case LUA_TFUNCTION: {
        a = lua_absindex(L, a);
        b = lua_absindex(L, b);
        lua_pushvalue(L, funcIdx);      /* push function */
        lua_pushvalue(L, a);            /* -1 to compensate function */
        lua_pushvalue(L, b);            /* -2 to compensate function and 'a' */
        lua_call(L, 2, 1);              /* call function */
        int res = lua_toboolean(L, -1); /* get result */
        lua_pop(L, 1);                  /* pop result */
        return res;
    }
    default: {
        a = lua_absindex(L, a);
        b = lua_absindex(L, b);
        lua_pushvalue(L, funcIdx);
        lua_gettable(L, a);
        int res = lua_compare(L, -1, b, LUA_OPLT);
        lua_pop(L, 1);
        return res;
    }
    }
}

static int less_equal_compare(lua_State *L, int a, int b, int funcIdx)
{
    switch (lua_type(L, funcIdx))
    {
    case LUA_TNIL:
        return lua_compare(L, a, b, LUA_OPLE); /* a < b */
    case LUA_TFUNCTION: {
        a = lua_absindex(L, a);
        b = lua_absindex(L, b);
        lua_pushvalue(L, funcIdx);       /* push function */
        lua_pushvalue(L, a);             /* -1 to compensate function */
        lua_pushvalue(L, b);             /* -2 to compensate function and 'a' */
        lua_call(L, 2, 1);               /* call function */
        int res = !lua_toboolean(L, -1); /* get result */
        lua_pop(L, 1);                   /* pop result */
        return res;
    }
    default: {
        a = lua_absindex(L, a);
        b = lua_absindex(L, b);
        lua_pushvalue(L, funcIdx);
        lua_gettable(L, a);
        int res = lua_compare(L, -1, b, LUA_OPLE);
        lua_pop(L, 1);
        return res;
    }
    }
}

static lua_Integer aux_lowerbound(lua_State *L, int idx, lua_Integer begin, lua_Integer end, int keyIdx,
                                  int compFuncIdx)
{
    lua_Integer first = begin;
    lua_Integer count = end - begin;
    lua_Integer mid, count2;

    while (0 < count)
    {
        count2 = count / 2;
        mid = first + count2;
        lua_rawgeti(L, idx, mid);
        if (less_compare(L, -1, keyIdx, compFuncIdx))
        {
            first = mid + 1;
            count = count - count2 - 1;
        }
        else
        {
            count = count2;
        }
        lua_pop(L, 1);
    }
    return first;
}

static lua_Integer aux_upperbound(lua_State *L, int idx, lua_Integer begin, lua_Integer end, int keyIdx,
                                  int compFuncIdx)
{
    lua_Integer first = begin;
    lua_Integer count = end - begin;
    lua_Integer mid, count2;

    while (0 < count)
    {
        count2 = count / 2;
        mid = first + count2;
        lua_rawgeti(L, idx, mid);
        if (less_equal_compare(L, -1, keyIdx, compFuncIdx))
        {
            first = mid + 1;
            count = count - count2 - 1;
        }
        else
        {
            count = count2;
        }
        lua_pop(L, 1);
    }
    return first;
}

static int table_lower_bound(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TTABLE);

    const lua_Integer begin = lua_tointeger(L, 2);
    const lua_Integer end = lua_tointeger(L, 3);
    luaL_checkany(L, 4);
    lua_settop(L, 5);
    const lua_Integer r = aux_lowerbound(L, 1, begin, end, 4, 5);
    if (r == end)
        return 0;
    lua_pushinteger(L, r);
    return 1;
}

static int table_upper_bound(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TTABLE);

    const lua_Integer begin = lua_tointeger(L, 2);
    const lua_Integer end = lua_tointeger(L, 3);
    luaL_checkany(L, 4);
    lua_settop(L, 5);
    const lua_Integer r = aux_upperbound(L, 1, begin, end, 4, 5);
    if (r == end)
        return 0;
    lua_pushinteger(L, r);
    return 1;
}

static int table_is_empty(lua_State *L)
{
    if (lua_type(L, 1) == LUA_TTABLE)
    {
        lua_pushnil(L);
        const int r = lua_next(L, 1);
        lua_pushboolean(L, !r);
    }
    else
    {
        lua_pushboolean(L, 1);
    }

    return 1;
}

static const luaL_Reg lxlib_table[] = {lxlib_reg_pair(table, clear),
                                       lxlib_reg_pair(table, clear_array),
                                       lxlib_reg_pair(table, clear_hash),
                                       lxlib_reg_pair(table, clear_int_keys),
                                       lxlib_reg_pair(table, grow_to_target),
                                       lxlib_reg_pair(table, grow),
                                       lxlib_reg_pair(table, shrink),
                                       lxlib_reg_pair(table, capacity),
                                       lxlib_reg_pair(table, size),
                                       lxlib_reg_pair(table, pack),
                                       lxlib_reg_pair(table, copy),
                                       lxlib_reg_pair(table, lower_bound),
                                       lxlib_reg_pair(table, upper_bound),
                                       lxlib_reg_pair(table, is_empty),

                                       {NULL, NULL}};

static void lxlib_reg_table(lua_State *L)
{
    luaL_newlib(L, lxlib_table);
    lua_setglobal(L, "lx_table");
}