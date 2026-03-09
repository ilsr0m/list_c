#include "list_c.h"

list_t* list_create(const size_t item_size)
{
	assert(item_size > 0);
	if(item_size == 0) return NULL;

	list_t* list = (list_t*)malloc(sizeof item_size);
	memset(list, 0, sizeof item_size);
	list->item_size = item_size;
	list->head = NULL;
	list->tail = NULL;
	return list;
}

void list_clear(list_t *list)
{
	assert(list != NULL);
	// прописать очистку итемов
	node_t *cur = list->head;
	while(cur != NULL){
		node_t* next = cur->next;
		free(cur->item);
		free(cur);
		cur = next;
	}
	list->head = NULL;
	list->tail = NULL;

	list->item_size = 0;
	list->size = 0;
}

void list_delete(list_t *list)
{
	assert(list != NULL);
	// прописать очистку итемов
	node_t *cur = list->head;
	while(cur != NULL){
		node_t* next = cur->next;
		free(cur->item);
		free(cur);
		cur = next;
	}
	list->head = NULL;
	list->tail = NULL;
	list->item_size = 0;
	list->size = 0;
	free(list);
	list = NULL;
}

int list_append(list_t *list, const void *item)
{
	assert(list != NULL);
	assert(item != NULL);
	if(!list || !item) return -1;
	// new node pointer
	node_t* new_ptr = (node_t*)malloc(sizeof(node_t));
	new_ptr->item = malloc( list->item_size);
	memcpy(new_ptr->item, item, list->item_size);
	new_ptr->next = NULL;

	// if first item placed
	if(list->head == NULL){
		list->head = new_ptr;
	    list->tail = new_ptr;
	}
	else{ // if more than one
		list->tail->next = new_ptr;
		list->tail = new_ptr;
	}
	list->size += 1;
	return 0;
}

