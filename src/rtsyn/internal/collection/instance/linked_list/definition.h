/**
 * @file rtsyn/internal/collection/instance/linked_list/definition.h
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief Internal header file for the RTSyn Collection Instance Linked List definition.
 *
 * Defines the collection instance struct.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * @copyright Copyright (c) Sergio Hidalgo 2026
 */
#ifndef RTSYN_INTERNAL_COLLECTION_INSTANCE_LINKED_LIST_DEFINITION_H
#define RTSYN_INTERNAL_COLLECTION_INSTANCE_LINKED_LIST_DEFINITION_H
#include <stdint.h>

typedef struct rtsyn_collection_instance_linked_list_node_s
    rtsyn_collection_instance_linked_list_node_t;

struct rtsyn_collection_instance_linked_list_node_s {
    void *node_data;
    rtsyn_collection_instance_linked_list_node_t *next_node;
};

struct rtsyn_collection_instance_s {
    rtsyn_collection_instance_linked_list_node_t *first_node;
    rtsyn_collection_instance_linked_list_node_t *last_node;
    uint64_t n_nodes;
};

#endif /* RTSYN_INTERNAL_COLLECTION_INSTANCE_LINKED_LIST_DEFINITION_H */
