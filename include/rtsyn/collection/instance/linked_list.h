/**
 * @file rtsyn/collection/instance/linked_list.h
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief Header file for the RTSyn Collection Instance Linked List.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * @copyright Copyright (c) Sergio Hidalgo 2026
 */
#ifndef RTSYN_COLLECTION_INSTANCE_LINKED_LIST_H
#define RTSYN_COLLECTION_INSTANCE_LINKED_LIST_H
#include "rtsyn/collection/instance.h"

/**
 * @brief Create an RTSyn Collection Linked List.
 *
 * @return Pointer to the created collection, or NULL if creation fails.
 */
rtsyn_collection_instance_t *
rtsyn_collection_instance_linked_list_create();

#endif /* RTSYN_COLLECTION_INSTANCE_LINKED_LIST_H */
