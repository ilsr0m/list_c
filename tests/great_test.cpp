#include <gtest/gtest.h>

extern "C"{
    #include "list_c.h"

    typedef struct TestPoint{
        double x;
        double y;
    }test_point_t;
}

// for append, prepend functions
int test_integers[10] = {9, 2, -1, 5, 7, 0, 4, 5, 3, 1};
double test_doubles[10] = {-0.6, 1.7, 15.02, 2.3, 6.33, -19.29, 0.5, 5.11, 3.93, 24.0};

test_point_t test_points[10] = {
    { 3.1, -6.22 },
    { 0.0, 9.7 },
    { 1.2, -0.2 },
    { 7.3, -6.22 },
    { -6.1, -9.09 },
    { 9.1, 15.15 },
    { 1.11, -6.22 },
    { 3.87, 88.14 },
    { 4.44, -14.87 },
    { 2.28, 27.88 }
};

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

TEST(ListTest, InsertTest){
    list_t *list = list_create(sizeof(test_point_t));
    int result = 0;

    // fill list with values to make it not empty
    for(int i = 0; i < 10; i++)
        list_append(list, &test_points[i]);

    printf("a1\n");
    // put it as first item
    test_point_t p0 = {2.0, 2.0};
    result = list_insert(list, &p0, 0);
    
    EXPECT_NE(list, nullptr);
    EXPECT_EQ((*(test_point_t*)list->head->item).x, p0.x); 
    EXPECT_EQ((*(test_point_t*)list->head->item).y, p0.y); 
    EXPECT_EQ(result, 0); 
    EXPECT_EQ(list->size, 11);
    
    // put it as last item
    test_point_t p1 = {4.0, 4.0};
    result = list_insert(list, &p1, list->size);
    EXPECT_NE(list, nullptr);
    EXPECT_EQ((*(test_point_t*)list->tail->item).x, p1.x); 
    EXPECT_EQ((*(test_point_t*)list->tail->item).y, p1.y); 
    EXPECT_EQ(result, 0); 
    EXPECT_EQ(list->size, 12);

    // put it in the middle
    test_point_t p3 = {5.55, 5.55};
    int position = 7;
    result = list_insert(list, &p3, position);
    node_t *list_iter = list->head;
    int count = 0;
    while (list_iter != nullptr)
    {
        if(position == count) 
            break;
        count++;
        list_iter = list_iter->next;
    }

    EXPECT_NE(list, nullptr); 
    EXPECT_EQ((*(test_point_t*)list_iter->item).x, p3.x); 
    EXPECT_EQ((*(test_point_t*)list_iter->item).y, p3.y);  
    EXPECT_EQ(result, 0); 
    EXPECT_EQ(list->size, 13);

    list_delete(&list);
    EXPECT_EQ(list, nullptr);
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}