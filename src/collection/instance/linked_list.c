/**
 * @file node/aggregation.c
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief Compile unit for the RTSyn Runtime Node Aggregation
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * @copyright Copyright (c) Sergio Hidalgo 2026
 */
#include <stdint.h>
#include <stdlib.h>

#include "rtsyn/collection.h"
#include "rtsyn/internal/collection/instance/linked_list.h"
#include "rtsyn/internal/collection/instance/linked_list/definition.h"

rtsyn_collection_instance_t *
rtsyn_collection_instance_linked_list_create()
{
    rtsyn_collection_instance_t *linked_list =
        (rtsyn_collection_instance_t *)malloc(sizeof(rtsyn_collection_instance_t));

    if (!linked_list)
    {
        return nullptr;
    }

    linked_list->n_nodes = 0;
    linked_list->first_node = NULL;
    linked_list->last_node = NULL;

    return linked_list;
}

void
rtsyn_collection_instance_linked_list_destroy(rtsyn_collection_instance_t *linked_list,
                                              rtsyn_collection_destroy_elem_fn_t destroy_elem_fn)

{
    rtsyn_collection_instance_linked_list_node_t *node = linked_list->first_node;
    rtsyn_collection_instance_linked_list_node_t *node_aux = NULL;
    while (node)
    {
        destroy_elem_fn(node->node_data);
        node_aux = node;
        node = node->next_node;
        free(node_aux);
    }
    free(linked_list);
}

bool
rtsyn_collection_instance_linked_list_add(rtsyn_collection_instance_t *linked_list, void *element,
                                          rtsyn_collection_cmp_key_fn_t cmp_key_fn)
{

    rtsyn_collection_instance_linked_list_node_t *new_elem =
        (rtsyn_collection_instance_linked_list_node_t *)malloc(
            sizeof(rtsyn_collection_instance_linked_list_node_t));

    if (!new_elem)
    {
        return false;
    }

    new_elem->node_data = element;
    new_elem->next_node = NULL;

    if (linked_list->n_nodes == 0)
    {
        linked_list->first_node = new_elem;
        linked_list->last_node = new_elem;
    } else
    {
        linked_list->last_node->next_node = new_elem;
        linked_list->last_node = new_elem;
    }

    linked_list->n_nodes++;

    return true;
}

bool
rtsyn_collection_instance_linked_list_remove(rtsyn_collection_instance_t *linked_list, void *key,
                                             rtsyn_collection_cmp_key_fn_t cmp_key_fn,
                                             rtsyn_collection_destroy_elem_fn_t destroy_elem_fn)
{

    rtsyn_collection_instance_linked_list_node_t *node = linked_list->first_node;
    rtsyn_collection_instance_linked_list_node_t *previous_node = NULL;

    while (node && !cmp_key_fn(node->node_data, key))
    {
        previous_node = node;
        node = node->next_node;
    }

    if (node)
    {
        if (previous_node)
        {
            previous_node->next_node = node->next_node;
        }

        if (linked_list->first_node == node)
        {
            linked_list->first_node = node->next_node;
        }

        if (linked_list->last_node == node)
        {
            linked_list->last_node = previous_node;
        }

        linked_list->n_nodes--;
        destroy_elem_fn(node->node_data);
        free(node);
        return true;
    }
    return false;
}

bool
rtsyn_collection_instance_linked_list_contains(rtsyn_collection_instance_t *linked_list, void *key,
                                               rtsyn_collection_cmp_key_fn_t cmp_key_fn)
{
    rtsyn_collection_instance_linked_list_node_t *node = linked_list->first_node;
    while (node && !cmp_key_fn(node->node_data, key))
    {
        node = node->next_node;
    }

    return node != NULL;
}

void *
rtsyn_collection_instance_linked_list_get(rtsyn_collection_instance_t *linked_list, void *key,
                                          rtsyn_collection_cmp_key_fn_t cmp_key_fn)
{
    if (!linked_list || !key)
    {
        return nullptr;
    }

    rtsyn_collection_instance_linked_list_node_t *node = linked_list->first_node;
    while (node && !cmp_key_fn(node->node_data, key))
    {
        node = node->next_node;
    };

    if (node)
    {
        return node->node_data;
    }

    return NULL;
}

bool
rtsyn_collection_instance_linked_list_for_each(rtsyn_collection_instance_t *linked_list,
                                               rtsyn_collection_for_each_fn_t for_each_fn)
{
    if (!linked_list || !for_each_fn)
    {
        return false;
    }

    rtsyn_collection_instance_linked_list_node_t *node = linked_list->first_node;
    while (node)
    {
        if (!for_each_fn(node->node_data))
        {
            return false;
        }
        node = node->next_node;
    }

    return true;
}
