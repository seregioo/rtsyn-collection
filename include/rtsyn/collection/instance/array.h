/**
 * @file rtsyn/collection/instance/array.h
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief Header file for the RTSyn Collection Instance.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * @copyright Copyright (c) Sergio Hidalgo 2026
 */
#ifndef RTSYN_COLLECTION_INSTANCE_ARRAY_H
#define RTSYN_COLLECTION_INSTANCE_ARRAY_H
#include "rtsyn/collection.h"
#include "rtsyn/collection/instance.h"

/**
 * @brief Create an RTSyn Collection Array.
 *
 * @return Pointer to the created collection, or NULL if creation fails.
 */
rtsyn_collection_instance_t *
rtsyn_collection_instance_array_create();

#endif /* RTSYN_INTERNAL_COLLECTION_INSTANCE_ARRAY_H */
