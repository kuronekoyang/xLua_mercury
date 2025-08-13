#include "lx_table.h"
#include "ltable.c"

LUAI_FUNC void lxH_clear_array(Table *t)
{
    if (t->array != NULL)
    {
        const unsigned int limit = setlimittosize(t);
        for (unsigned int i = 0; i < limit; i++)
        {
            setempty(&t->array[i]);
        }
    }
}

LUAI_FUNC void lxH_clear_hash(Table *t)
{
    const int size = allocsizenode(t);
    if (size > 0)
    {
        for (int i = 0; i < size; ++i)
        {
            Node *n = gnode(t, i);
            gnext(n) = 0;
            setnilkey(n);
            setempty(gval(n));
        }
        t->lastfree = gnode(t, size);
    }
}

LUAI_FUNC void lxH_clear_int_keys(Table *t)
{
    lxH_clear_array(t);

    const int size = allocsizenode(t);
    if (size > 0)
    {
        for (int i = 0; i < size; ++i)
        {
            Node *n = gnode(t, i);
            if (keyisinteger(n))
            {
                setnilvalue(gval(n));
            }
        }
    }
}

LUAI_FUNC void lxH_grow_to_target(lua_State *L, Table *t, const Table *target)
{
    const unsigned int nsize = (unsigned int)allocsizenode(t);
    const unsigned int nsizeref = (unsigned int)allocsizenode(target);
    const unsigned int nasize = luaH_realasize(t);
    const unsigned int nasizeref = luaH_realasize(target);
    if (nsize < nsizeref || nasize < nasizeref)
        luaH_resize(L, t, nasize < nasizeref ? nasizeref : nasize, nsize < nsizeref ? nsizeref : nsize);
}

LUAI_FUNC void lxH_grow(lua_State *L, Table *t, unsigned int new_array_size, unsigned int new_hash_size)
{
    const unsigned int hash_size = (unsigned int)allocsizenode(t);
    const unsigned int array_size = luaH_realasize(t);
    if (hash_size < new_hash_size || array_size < new_array_size)
        luaH_resize(L, t, array_size < new_array_size ? new_array_size : array_size,
                    hash_size < new_hash_size ? new_hash_size : hash_size);
}

LUAI_FUNC void lxH_shrink(lua_State *L, Table *t)
{
    rehash(L, t, NULL);
}

LUAI_FUNC void lxH_size(lua_State *L, const Table *t, unsigned int *array_size, unsigned int *hash_size)
{
    *array_size = 0;
    if (t->array != NULL)
    {
        const unsigned int limit = setlimittosize(t);
        for (unsigned int i = 0; i < limit; i++)
        {
            if (!isempty(&t->array[i]))
            {
                ++(*array_size);
            }
        }
    }

    *hash_size = 0;
    const int size = allocsizenode(t);
    if (size > 0)
    {
        for (int i = 0; i < size; ++i)
        {
            const Node *n = gnode(t, i);
            if (!isempty(gval(n)))
            {
                ++(*hash_size);
            }
        }
    }
}
