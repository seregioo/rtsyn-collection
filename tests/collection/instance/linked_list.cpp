/**
 * @file aggregation_node.cpp
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief Test file for the aggregation node logic
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * @copyright Copyright (c) Sergio Hidalgo 2026
 */
#include <gtest/gtest.h>

extern "C" {
#include <stdlib.h>

#include "rtsyn/collection.h"
}

typedef struct mock_struct_s {
    int id;
} mock_struct_t;

static mock_struct_t *
mock_struct_create(int id)
{
    mock_struct_t *mock_struct = (mock_struct_t *)malloc(sizeof(mock_struct_t));
    if (!mock_struct)
    {
        return nullptr;
    }
    mock_struct->id = id;

    return mock_struct;
}

static bool
mock_struct_cmp(void *struct_a, void *key_b)
{
    if (!struct_a || !key_b)
    {
        return false;
    }

    mock_struct_t *struct_a_obj = (mock_struct_t *)struct_a;
    int key2 = *(int *)key_b;

    return struct_a_obj->id == key2;
}

static void
mock_struct_destroy_elem(void *mock_struct)
{
    mock_struct_t *mock_struct_obj = (mock_struct_t *)mock_struct;
    free(mock_struct_obj);
}

static int for_each_count;
static int for_each_sum;
static int for_each_stop_id;

static bool
mock_struct_for_each(void *element)
{
    mock_struct_t *mock_struct = (mock_struct_t *)element;

    for_each_count++;
    for_each_sum += mock_struct->id;
    return mock_struct->id != for_each_stop_id;
}

class NodeAggregationTest : public ::testing::Test {
  protected:
    void
    SetUp() override
    {
        linked_list_ = rtsyn_collection_create_linked_list(
            (rtsyn_collection_cmp_key_fn_t)mock_struct_cmp,
            (rtsyn_collection_destroy_elem_fn_t)mock_struct_destroy_elem);

        ASSERT_NE(linked_list_, nullptr);
    }

    void
    TearDown() override
    {
        rtsyn_collection_destroy(linked_list_);
        linked_list_ = nullptr;
    }

    rtsyn_collection_t *linked_list_ = nullptr;
};

TEST_F(NodeAggregationTest, AggregationAddNode)
{
    int mock_id = 59;
    mock_struct_t *elem = mock_struct_create(mock_id);

    EXPECT_TRUE(rtsyn_collection_add(linked_list_, elem, &mock_id));

    EXPECT_TRUE(rtsyn_collection_contains(linked_list_, &mock_id));

    int mock_id_2 = 4;
    mock_struct_t *aux_node = (mock_struct_t *)rtsyn_collection_get(linked_list_, &mock_id_2);
    EXPECT_EQ(aux_node, nullptr);
    EXPECT_FALSE(rtsyn_collection_contains(linked_list_, &mock_id_2));
}

TEST_F(NodeAggregationTest, AggregationRemoveNode)
{

    int mock_id = 9;
    mock_struct_t *node = mock_struct_create(mock_id);
    rtsyn_collection_add(linked_list_, node, &mock_id);

    EXPECT_TRUE(rtsyn_collection_contains(linked_list_, &mock_id));

    rtsyn_collection_remove(linked_list_, &mock_id);

    EXPECT_FALSE(rtsyn_collection_contains(linked_list_, &mock_id));
}

TEST_F(NodeAggregationTest, AggregationGetNode)
{
    int mock_id = 7;
    mock_struct_t *node = mock_struct_create(mock_id);
    rtsyn_collection_add(linked_list_, node, &mock_id);

    mock_struct_t *node_b = (mock_struct_t *)rtsyn_collection_get(linked_list_, &mock_id);

    EXPECT_NE(node_b, nullptr);
    EXPECT_TRUE(mock_struct_cmp(node, node_b));
}

TEST_F(NodeAggregationTest, AggregationAddSeveralNode)
{
    int mock_id = 59;
    int mock_id_2 = 4;
    int mock_id_3 = 8;

    mock_struct_t *elem = mock_struct_create(mock_id);
    mock_struct_t *elem_2 = mock_struct_create(mock_id_2);
    mock_struct_t *elem_3 = mock_struct_create(mock_id_3);

    EXPECT_TRUE(rtsyn_collection_add(linked_list_, elem, &mock_id));
    EXPECT_TRUE(rtsyn_collection_add(linked_list_, elem_2, &mock_id_2));
    EXPECT_TRUE(rtsyn_collection_add(linked_list_, elem_3, &mock_id_3));

    EXPECT_TRUE(rtsyn_collection_contains(linked_list_, &mock_id));
    EXPECT_TRUE(rtsyn_collection_contains(linked_list_, &mock_id_2));
    EXPECT_TRUE(rtsyn_collection_contains(linked_list_, &mock_id_3));
}

TEST_F(NodeAggregationTest, AggregationAddNRemoveSeveralNode)
{
    int mock_id = 59;
    int mock_id_2 = 4;
    int mock_id_3 = 8;

    mock_struct_t *elem = mock_struct_create(mock_id);
    mock_struct_t *elem_2 = mock_struct_create(mock_id_2);
    mock_struct_t *elem_3 = mock_struct_create(mock_id_3);

    EXPECT_TRUE(rtsyn_collection_add(linked_list_, elem, &mock_id));
    EXPECT_TRUE(rtsyn_collection_add(linked_list_, elem_2, &mock_id_2));
    EXPECT_TRUE(rtsyn_collection_add(linked_list_, elem_3, &mock_id_3));

    EXPECT_TRUE(rtsyn_collection_contains(linked_list_, &mock_id));
    EXPECT_TRUE(rtsyn_collection_contains(linked_list_, &mock_id_2));
    EXPECT_TRUE(rtsyn_collection_contains(linked_list_, &mock_id_3));

    EXPECT_TRUE(rtsyn_collection_remove(linked_list_, &mock_id));
    EXPECT_TRUE(rtsyn_collection_remove(linked_list_, &mock_id_2));
    EXPECT_TRUE(rtsyn_collection_remove(linked_list_, &mock_id_3));
}

TEST_F(NodeAggregationTest, ForEachVisitsEveryNode)
{
    int ids[] = {59, 4, 8};
    for (int id : ids)
    {
        ASSERT_TRUE(rtsyn_collection_add(linked_list_, mock_struct_create(id), &id));
    }

    for_each_count = 0;
    for_each_sum = 0;
    for_each_stop_id = -1;
    EXPECT_TRUE(rtsyn_collection_for_each(linked_list_, mock_struct_for_each));
    EXPECT_EQ(for_each_count, 3);
    EXPECT_EQ(for_each_sum, 71);
}

TEST_F(NodeAggregationTest, ForEachStopsWhenCallbackFails)
{
    int ids[] = {59, 4, 8};
    for (int id : ids)
    {
        ASSERT_TRUE(rtsyn_collection_add(linked_list_, mock_struct_create(id), &id));
    }

    for_each_count = 0;
    for_each_sum = 0;
    for_each_stop_id = 4;
    EXPECT_FALSE(rtsyn_collection_for_each(linked_list_, mock_struct_for_each));
    EXPECT_EQ(for_each_count, 2);
    EXPECT_EQ(for_each_sum, 63);
}
