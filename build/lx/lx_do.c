#include "lx_do.h"
#include "ldo.c"

LUAI_FUNC int lxD_is_empty_func(StkId func)
{
    switch (ttypetag(s2v(func)))
    {
    case LUA_VLCL: {
        /* Lua function */
        // CallInfo* ci;
        Proto *p = clLvalue(s2v(func))->p;
        if (p->code)
            return GET_OPCODE(*(p->code)) == OP_RETURN0;
        else
            return 0;
    }
    default:
        return 0;
    }
}

LUAI_FUNC int lxtD_is_callable(lua_State *L, StkId func)
{
    switch (ttype(s2v(func)))
    {
    case LUA_TFUNCTION:
        return 1;
    case LUA_TTABLE:
    case LUA_TUSERDATA: {
        const TValue *tm = luaT_gettmbyobj(L, s2v(func), TM_CALL);
        if (ttisnil(tm))
            return 0;
        return 1;
    }
    default:
        return 0;
    }
}
