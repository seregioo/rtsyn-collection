/**
 * @file rtsyn/collection/instance.h
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief Header file for the RTSyn Collection Instance.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * @copyright Copyright (c) Sergio Hidalgo 2026
 */
#ifndef RTSYN_INTERNAL_COLLECTION_HANDLER_H
#define RTSYN_INTERNAL_COLLECTION_HANDLER_H

#include "rtsyn/collection.h"
#include "rtsyn/collection/handler.h"
#include "rtsyn/collection/instance.h"

typedef rtsyn_collection_instance_t *(*rtsyn_collection_handler_create_fn_t)();

typedef void (*rtsyn_collection_handler_destroy_fn_t)(rtsyn_collection_instance_t *,
                                                      rtsyn_collection_destroy_elem_fn_t);

typedef bool (*rtsyn_collection_handler_add_fn_t)(rtsyn_collection_instance_t *, void *,
                                                  rtsyn_collection_cmp_key_fn_t);
typedef bool (*rtsyn_collection_handler_remove_fn_t)(rtsyn_collection_instance_t *, void *,
                                                     rtsyn_collection_cmp_key_fn_t,
                                                     rtsyn_collection_destroy_elem_fn_t);
typedef bool (*rtsyn_collection_handler_contains_fn_t)(rtsyn_collection_instance_t *, void *,
                                                       rtsyn_collection_cmp_key_fn_t);
typedef void *(*rtsyn_collection_handler_get_fn_t)(rtsyn_collection_instance_t *, void *,
                                                   rtsyn_collection_cmp_key_fn_t);
typedef bool (*rtsyn_collection_handler_for_each_fn_t)(rtsyn_collection_instance_t *,
                                                       rtsyn_collection_for_each_fn_t);

typedef struct rtsyn_collection_handler_s {
    rtsyn_collection_handler_create_fn_t create_fn;
    rtsyn_collection_handler_destroy_fn_t destroy_fn;
    rtsyn_collection_handler_add_fn_t add_fn;
    rtsyn_collection_handler_remove_fn_t remove_fn;
    rtsyn_collection_handler_contains_fn_t contains_fn;
    rtsyn_collection_handler_get_fn_t get_fn;
    rtsyn_collection_handler_for_each_fn_t for_each_fn;
} rtsyn_collection_handler_t;

#endif /* RTSYN_INTERNAL_COLLECTION_HANDLER_H */
