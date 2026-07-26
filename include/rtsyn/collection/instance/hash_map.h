/**
 * @file rtsyn/collection/instance/hash_map.h
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief Header file for the RTSyn Collection Instance Hash Map.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * @copyright Copyright (c) Sergio Hidalgo 2026
 */
#ifndef RTSYN_COLLECTION_INSTANCE_HASH_MAP_H
#define RTSYN_COLLECTION_INSTANCE_HASH_MAP_H
#include "rtsyn/collection.h"
#include "rtsyn/collection/instance.h"

/**
 * @brief Create an RTSyn Collection Hash Map.
 *
 * @return Pointer to the created collection, or NULL if creation fails.
 */
rtsyn_collection_instance_t *
rtsyn_collection_instance_hash_map_create();

#endif /* RTSYN_COLLECTION_INSTANCE_HASH_MAP_H */
