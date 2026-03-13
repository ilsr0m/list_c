#include <gtest/gtest.h>

extern "C"{
    #include "list_c.h"
}

// for append, prepend functions
int test_integers[10] = {9, 2, -1, 5, 7, 0, 4, 5, 3, 1};
double test_doubles[10] = {-0.6, 1.7, 15.02, 2.3, 6.33, -19.29, 0.5, 5.11, 3.93, 24.0};

TEST(ListTest, CreateTest){
    list_t *list = list_create(sizeof(int));
    
    EXPECT_NE(list, nullptr); // list is not null, coz it's already initialized
    EXPECT_EQ(list->size, 0); // no any items
    EXPECT_EQ(list->head, nullptr); // obviously null
    EXPECT_EQ(list->tail, nullptr); // obviously null
    EXPECT_EQ(list->item_size, sizeof(int)); // regards to the argument in list_create

    // simple check of function list_delete
    list_delete(&list);
    EXPECT_EQ(list, nullptr);
}

TEST(ListTest, AppendOnceTest){
    list_t *list = list_create(sizeof(int));
    int value = 5;
    list_append(list, &value);

    EXPECT_NE(list, nullptr);
    EXPECT_EQ(list->size, 1); // plus one item
    EXPECT_NE(list->head, nullptr); 
    EXPECT_NE(list->tail, nullptr);  
    EXPECT_EQ(list->tail, list->head); // head and tail must be equal

    int item = *(int*)list->tail->item;
    EXPECT_EQ(item, value); // item is equal to value
    EXPECT_EQ(list->item_size, sizeof(int));

    // simple check of function list_delete
    list_delete(&list);
    EXPECT_EQ(list, nullptr);
}

TEST(ListTest, PrependOnceTest){
    list_t *list = list_create(sizeof(int));
    int value = 5;
    list_prepend(list, &value);

    EXPECT_NE(list, nullptr);
    EXPECT_EQ(list->size, 1); // plus one item
    EXPECT_NE(list->head, nullptr); 
    EXPECT_NE(list->tail, nullptr);  
    EXPECT_EQ(list->tail, list->head); // head and tail must be equal

    int item = *(int*)list->tail->item;
    EXPECT_EQ(item, value); // item is equal to value
    EXPECT_EQ(list->item_size, sizeof(int));

    // simple check of function list_delete
    list_delete(&list);
    EXPECT_EQ(list, nullptr);
}

TEST(ListTest, AppendSeveralTest){
    list_t *list = list_create(sizeof(int));

    // fill list with some values
    for(int i = 0; i < 10; i++)
        list_append(list, &test_integers[i]);
    
    EXPECT_NE(list, nullptr);
    EXPECT_NE(list->head, nullptr); 
    EXPECT_NE(list->tail, nullptr);
    EXPECT_EQ(list->size, 10); 
    
    // check each value in list
    node_t *list_iter = list->head;
    int value_index = 0;
    while(list_iter != nullptr){
        EXPECT_EQ(*(int*)list_iter->item, test_integers[value_index]);
        value_index++;
        list_iter = list_iter->next;
    }

    list_delete(&list);
    EXPECT_EQ(list, nullptr);
}

TEST(ListTest, PrependSeveralTest){
    list_t *list = list_create(sizeof(int));
    
    // fill list with some values
    for(int i = 0; i < 10; i++)
        list_prepend(list, &test_integers[i]);
    
    EXPECT_NE(list, nullptr);
    EXPECT_NE(list->head, nullptr); 
    EXPECT_NE(list->tail, nullptr);
    EXPECT_EQ(list->size, 10); 
    
    // check each value in list
    node_t *list_iter = list->head;
    int value_index = 10;
    while(list_iter != nullptr){
        value_index--;
        EXPECT_EQ(*(int*)list_iter->item, test_integers[value_index]);
        list_iter = list_iter->next;
    }

    list_delete(&list);
    EXPECT_EQ(list, nullptr);
}

TEST(ListTest, ClearTest){
    list_t *list = list_create(sizeof(double));
    // fill list with values to make it not empty
    for(int i = 0; i < 10; i++)
        list_append(list, &test_doubles[i]);
    // then clear it to check if this function works properly
    list_clear(list);
    EXPECT_NE(list, nullptr);
    EXPECT_EQ(list->head, nullptr); 
    EXPECT_EQ(list->tail, nullptr);
    EXPECT_EQ(list->size, 0); 
    EXPECT_EQ(list->item_size, 0); 

    list_delete(&list);
    EXPECT_EQ(list, nullptr);
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}