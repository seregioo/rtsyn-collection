#include <stdlib.h>

#include "rtsyn/collection.h"
#include "rtsyn/internal/collection.h"
#include "rtsyn/internal/collection/instance/array.h"
#include "rtsyn/internal/collection/instance/hash_map.h"
#include "rtsyn/internal/collection/instance/linked_list.h"

static const rtsyn_collection_handler_t RTSYN_COLLECTION_HANDLER_TBL[RYSYN_COLLECTION_TYPE_COUNT] =
    {
        // RTSYN_COLLECTION_HANDLER_TBL_ENTRY(
        //     RYSYN_COLLECTION_TYPE_ARRAY, rtsyn_collection_instance_array_create,
        //     rtsyn_collection_instance_array_destroy, rtsyn_collection_instance_array_add,
        //     rtsyn_collection_instance_array_remove, rtsyn_collection_instance_array_contains,
        //     rtsyn_collection_instance_array_get),
        RTSYN_COLLECTION_HANDLER_TBL_ENTRY(
            RTSYN_COLLECTION_TYPE_LINKED_LIST, rtsyn_collection_instance_linked_list_create,
            rtsyn_collection_instance_linked_list_destroy,
            rtsyn_collection_instance_linked_list_add, rtsyn_collection_instance_linked_list_remove,
            rtsyn_collection_instance_linked_list_contains,
            rtsyn_collection_instance_linked_list_get,
            rtsyn_collection_instance_linked_list_for_each),
        [RYSYN_COLLECTION_TYPE_HASH_MAP] = {},
};

rtsyn_collection_t *
rtsyn_collection_create(rtsyn_collection_type_t collection_type,
                        rtsyn_collection_cmp_key_fn_t cmp_key_function,
                        rtsyn_collection_destroy_elem_fn_t destroy_elem_function)
{
    if (rtsyn_collection_validate_type(collection_type) == RTSYN_COLLECTION_TYPE_INVALID
        || !cmp_key_function || !destroy_elem_function)
    {
        return nullptr;
    }
    rtsyn_collection_t *collection = (rtsyn_collection_t *)malloc(sizeof(rtsyn_collection_t));

    if (!collection)
    {
        return nullptr;
    }

    collection->handler = &RTSYN_COLLECTION_HANDLER_TBL[collection_type];

    collection->collection_instance = collection->handler->create_fn();

    if (!collection->collection_instance)
    {
        free(collection);
        return nullptr;
    }

    collection->collection_type = collection_type;
    collection->cmp_key_function = cmp_key_function;
    collection->destroy_elem_function = destroy_elem_function;

    return collection;
}

rtsyn_collection_t *
rtsyn_collection_create_linked_list(rtsyn_collection_cmp_key_fn_t cmp_key_function,
                                    rtsyn_collection_destroy_elem_fn_t destroy_elem_function)
{
    return rtsyn_collection_create(RTSYN_COLLECTION_TYPE_LINKED_LIST, cmp_key_function,
                                   destroy_elem_function);
}

void
rtsyn_collection_destroy(rtsyn_collection_t *rtsyn_collection)
{
    rtsyn_collection->handler->destroy_fn(rtsyn_collection->collection_instance,
                                          rtsyn_collection->destroy_elem_function);
    free(rtsyn_collection);
}

rtsyn_collection_type_t
rtsyn_collection_validate_type(rtsyn_collection_type_t collection_type)
{
    if (collection_type <= RTSYN_COLLECTION_TYPE_INVALID
        || collection_type >= RYSYN_COLLECTION_TYPE_COUNT)
    {
        return RTSYN_COLLECTION_TYPE_INVALID;
    }

    return collection_type;
}

bool
rtsyn_collection_add(rtsyn_collection_t *rtsyn_collection, void *element, void *key)
{
    if (!rtsyn_collection || !rtsyn_collection->collection_instance || !element || !key
        || rtsyn_collection_contains(rtsyn_collection, key))
    {
        return false;
    }

    return rtsyn_collection->handler->add_fn(rtsyn_collection->collection_instance, element,
                                             rtsyn_collection->cmp_key_function);
}

bool
rtsyn_collection_remove(rtsyn_collection_t *rtsyn_collection, void *key)
{
    if (!rtsyn_collection || !rtsyn_collection->collection_instance || !key
        || !rtsyn_collection_contains(rtsyn_collection, key))
    {
        return false;
    }

    return rtsyn_collection->handler->remove_fn(rtsyn_collection->collection_instance, key,
                                                rtsyn_collection->cmp_key_function,
                                                rtsyn_collection->destroy_elem_function);
}

bool
rtsyn_collection_contains(rtsyn_collection_t *rtsyn_collection, void *key)
{
    if (!rtsyn_collection || !rtsyn_collection->collection_instance || !key)
    {
        return false;
    }

    return rtsyn_collection->handler->contains_fn(rtsyn_collection->collection_instance, key,
                                                  rtsyn_collection->cmp_key_function);
}

void *
rtsyn_collection_get(rtsyn_collection_t *rtsyn_collection, void *key)
{
    if (!rtsyn_collection || !rtsyn_collection->collection_instance || !key
        || !rtsyn_collection_contains(rtsyn_collection, key))
    {
        return nullptr;
    }

    return rtsyn_collection->handler->get_fn(rtsyn_collection->collection_instance, key,
                                             rtsyn_collection->cmp_key_function);
}

void *
rtsyn_collection_lookup(rtsyn_collection_t *rtsyn_collection, void *key,
                        rtsyn_collection_cmp_key_fn_t cmp_key_fn)
{
    if (!rtsyn_collection || !rtsyn_collection->collection_instance || !key
        || !rtsyn_collection->handler->contains_fn(rtsyn_collection->collection_instance, key,
                                                   cmp_key_fn))
    {
        return nullptr;
    }

    return rtsyn_collection->handler->get_fn(rtsyn_collection->collection_instance, key,
                                             cmp_key_fn);
}

bool
rtsyn_collection_for_each(rtsyn_collection_t *rtsyn_collection,
                          rtsyn_collection_for_each_fn_t for_each_fn)
{
    if (!rtsyn_collection || !rtsyn_collection->collection_instance || !for_each_fn
        || !rtsyn_collection->handler->for_each_fn)
    {
        return false;
    }

    return rtsyn_collection->handler->for_each_fn(rtsyn_collection->collection_instance,
                                                  for_each_fn);
}
