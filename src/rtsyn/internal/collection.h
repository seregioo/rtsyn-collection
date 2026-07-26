/**
 * @file rtsyn/collection/instance.h
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief Header file for the RTSyn Collection Instance.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * @copyright Copyright (c) Sergio Hidalgo 2026
 */
#ifndef RTSYN_INTERNAL_COLLECTION_H
#define RTSYN_INTERNAL_COLLECTION_H

#include "rtsyn/collection.h"
#include "rtsyn/collection/handler.h"
#include "rtsyn/collection/instance.h"
#include "rtsyn/internal/collection/handler.h"

struct rtsyn_collection_s {
    rtsyn_collection_type_t collection_type;
    rtsyn_collection_cmp_key_fn_t cmp_key_function;
    rtsyn_collection_destroy_elem_fn_t destroy_elem_function;
    const rtsyn_collection_handler_t *handler;
    rtsyn_collection_instance_t *collection_instance;
};

#define RTSYN_COLLECTION_HANDLER_TBL_ENTRY(rtsyn_collection_type, create_function,                 \
                                           destroy_function, add_function, remove_function,        \
                                           contains_function, get_function, for_each_function)     \
    [rtsyn_collection_type] = (rtsyn_collection_handler_t)                                         \
    {                                                                                              \
        .create_fn = create_function, .destroy_fn = destroy_function, .add_fn = add_function,      \
        .remove_fn = remove_function, .contains_fn = contains_function, .get_fn = get_function,    \
        .for_each_fn = for_each_function                                                           \
    }

#endif /* RTSYN_INTERNAL_COLLECTION_H */
