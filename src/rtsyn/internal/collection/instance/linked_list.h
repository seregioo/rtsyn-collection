/**
 * @file rtsyn/collection/instance/linked_list.h
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief Internal header file for the RTSyn Collection Instance Linked List.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * @copyright Copyright (c) Sergio Hidalgo 2026
 */
#ifndef RTSYN_INTERNAL_COLLECTION_INSTANCE_LINKED_LIST_H
#define RTSYN_INTERNAL_COLLECTION_INSTANCE_LINKED_LIST_H

#include <stdint.h>

#include "rtsyn/collection.h"
#include "rtsyn/collection/instance/linked_list.h"

/**
 * @brief Destroy an RTSyn Collection Linked List.
 *
 * @param rtsyn_collection Collection linked_list to be destroyed.
 */
void
rtsyn_collection_instance_linked_list_destroy(rtsyn_collection_instance_t *linked_list,
                                              rtsyn_collection_destroy_elem_fn_t destroy_elem_fn);

bool
rtsyn_collection_instance_linked_list_add(rtsyn_collection_instance_t *linked_list, void *element,
                                          rtsyn_collection_cmp_key_fn_t cmp_key_fn);

bool
rtsyn_collection_instance_linked_list_remove(rtsyn_collection_instance_t *linked_list, void *key,
                                             rtsyn_collection_cmp_key_fn_t cmp_key_fn,
                                             rtsyn_collection_destroy_elem_fn_t destroy_elem_fn);

bool
rtsyn_collection_instance_linked_list_contains(rtsyn_collection_instance_t *linked_list, void *key,
                                               rtsyn_collection_cmp_key_fn_t cmp_key_fn);

void *
rtsyn_collection_instance_linked_list_get(rtsyn_collection_instance_t *linked_list, void *key,
                                          rtsyn_collection_cmp_key_fn_t cmp_key_fn);

bool
rtsyn_collection_instance_linked_list_for_each(rtsyn_collection_instance_t *linked_list,
                                               rtsyn_collection_for_each_fn_t for_each_fn);

#endif /* RTSYN_INTERNAL_COLLECTION_INSTANCE_LINKED_LIST_H */
