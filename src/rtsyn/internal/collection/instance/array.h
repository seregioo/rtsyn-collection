/**
 * @file rtsyn/internal/collection/instance/array.h
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief Internal header file for the RTSyn Collection Instance.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * @copyright Copyright (c) Sergio Hidalgo 2026
 */
#ifndef RTSYN_INTERNAL_COLLECTION_INSTANCE_ARRAY_H
#define RTSYN_INTERNAL_COLLECTION_INSTANCE_ARRAY_H
#include "rtsyn/collection.h"
#include "rtsyn/collection/instance/array.h"

/**
 * @brief Destroy an RTSyn Collection Array.
 *
 * @param rtsyn_collection Collection Array to be destroyed.
 */
void
rtsyn_collection_instance_array_destroy(rtsyn_collection_instance_t *array,
                                        rtsyn_collection_destroy_elem_fn_t destroy_elem_fn);

bool
rtsyn_collection_instance_array_add(rtsyn_collection_instance_t *array, void *element,
                                    rtsyn_collection_cmp_key_fn_t cmp_key_fn);

bool
rtsyn_collection_instance_array_remove(rtsyn_collection_instance_t *array, void *key,
                                       rtsyn_collection_cmp_key_fn_t cmp_key_fn,
                                       rtsyn_collection_destroy_elem_fn_t destroy_elem_fn);

bool
rtsyn_collection_instance_array_contains(rtsyn_collection_instance_t *array, void *key,
                                         rtsyn_collection_cmp_key_fn_t cmp_key_fn);

void *
rtsyn_collection_instance_array_get(rtsyn_collection_instance_t *array, void *key,
                                    rtsyn_collection_cmp_key_fn_t cmp_key_fn);

#endif /* RTSYN_INTERNAL_COLLECTION_INSTANCE_ARRAY_H */
