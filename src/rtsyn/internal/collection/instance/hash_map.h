/**
 * @file rtsyn/internal/collection/instance/hash_map.h
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief Internal header file for the RTSyn Collection Instance Hash Map.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * @copyright Copyright (c) Sergio Hidalgo 2026
 */
#ifndef RTSYN_INTERNAL_COLLECTION_INSTANCE_HASH_MAP_H
#define RTSYN_INTERNAL_COLLECTION_INSTANCE_HASH_MAP_H
#include "rtsyn/collection.h"
#include "rtsyn/collection/instance/hash_map.h"

/**
 * @brief Destroy an RTSyn Collection Hash Map.
 *
 * @param rtsyn_collection Collection hash_map to be destroyed.
 */
void
rtsyn_collection_instance_hash_map_destroy(rtsyn_collection_instance_t *hash_map,
                                           rtsyn_collection_destroy_elem_fn_t destroy_elem_fn);

bool
rtsyn_collection_instance_hash_map_add(rtsyn_collection_instance_t *hash_map, void *element,
                                       rtsyn_collection_cmp_key_fn_t cmp_key_fn);

bool
rtsyn_collection_instance_hash_map_remove(rtsyn_collection_instance_t *hash_map, void *key,
                                          rtsyn_collection_cmp_key_fn_t cmp_key_fn,
                                          rtsyn_collection_destroy_elem_fn_t destroy_elem_fn);

bool
rtsyn_collection_instance_hash_map_contains(rtsyn_collection_instance_t *hash_map, void *key,
                                            rtsyn_collection_cmp_key_fn_t cmp_key_fn);

void *
rtsyn_collection_instance_hash_map_get(rtsyn_collection_instance_t *hash_map, void *key,
                                       rtsyn_collection_cmp_key_fn_t cmp_key_fn);

#endif /* RTSYN_INTERNAL_COLLECTION_INSTANCE_HASH_MAP_H */
