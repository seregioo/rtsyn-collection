/**
 * @file rtsyn/collection.h
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief Header file for the RTSyn Collection.
 *
 * The RTSyn Runtime Collection abstracts aggregations of objets.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * @copyright Copyright (c) Sergio Hidalgo 2026
 */
#ifndef RTSYN_COLLECTION_H
#define RTSYN_COLLECTION_H

/**
 * @brief Opaque collection object.
 */
typedef struct rtsyn_collection_s rtsyn_collection_t;

typedef bool (*rtsyn_collection_cmp_key_fn_t)(void *, void *);
typedef void (*rtsyn_collection_destroy_elem_fn_t)(void *);
typedef bool (*rtsyn_collection_for_each_fn_t)(void *);

typedef enum rtsyn_collection_type_e {
    RTSYN_COLLECTION_TYPE_INVALID = 0,
    RYSYN_COLLECTION_TYPE_ARRAY,
    RTSYN_COLLECTION_TYPE_LINKED_LIST,
    RYSYN_COLLECTION_TYPE_HASH_MAP,
    RYSYN_COLLECTION_TYPE_COUNT,
} rtsyn_collection_type_t;

/**
 * @brief Create an RTSyn collection.
 *
 * @param collection_type Type for the collection.
 * @param cmp_function Comparison function between objects.
 * @return Pointer to the created collection, or NULL if creation fails.
 */
rtsyn_collection_t *
rtsyn_collection_create(rtsyn_collection_type_t collection_type,
                        rtsyn_collection_cmp_key_fn_t cmp_key_function,
                        rtsyn_collection_destroy_elem_fn_t destroy_elem_function);

rtsyn_collection_t *
rtsyn_collection_create_linked_list(rtsyn_collection_cmp_key_fn_t cmp_key_function,
                                    rtsyn_collection_destroy_elem_fn_t destroy_elem_function);

/**
 * @brief Destroy an RTSyn collection.
 *
 * @param rtsyn_collection Collection to be destroyed.
 */
void
rtsyn_collection_destroy(rtsyn_collection_t *rtsyn_collection);

rtsyn_collection_type_t
rtsyn_collection_validate_type(rtsyn_collection_type_t collection_type);

bool
rtsyn_collection_add(rtsyn_collection_t *rtsyn_collection, void *element, void *key);

bool
rtsyn_collection_remove(rtsyn_collection_t *rtsyn_collection, void *key);

bool
rtsyn_collection_contains(rtsyn_collection_t *rtsyn_collection, void *key);

void *
rtsyn_collection_get(rtsyn_collection_t *rtsyn_collection, void *key);

void *
rtsyn_collection_lookup(rtsyn_collection_t *rtsyn_collection, void *key,
                        rtsyn_collection_cmp_key_fn_t cmp_key_fn);

bool
rtsyn_collection_for_each(rtsyn_collection_t *rtsyn_collection,
                          rtsyn_collection_for_each_fn_t for_each_fn);

#endif /* RTSYN_COLLECTION_H */
