#ifndef __LX_DO_H__
#define __LX_DO_H__

#include "lobject.h"
#include "lua.h"

LUAI_FUNC int lxD_is_empty_func(StkId func);
LUAI_FUNC int lxD_is_callable(lua_State *L, StkId func);

#endif
