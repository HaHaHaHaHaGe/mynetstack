#include "../inc/basic_list.h"




void Init_List(LIST *list)
{
	list->end = NULL_PTR;
	list->start = NULL_PTR;
	list->Number = 0;
}


void Add_List(LIST *list,u8 *data,u32 len)
{
	LIST_DATA *ptr = basic_malloc(sizeof(LIST_DATA));
	ptr->data = data;
	ptr->next = NULL_PTR;
	ptr->len = len;

	if (list->end != NULL_PTR)
		list->end->next = ptr;
	list->end = ptr;

	if (list->start == NULL_PTR)
		list->start = ptr;

	
	list->Number++;
}

void Delete_List(LIST *list, LIST_DATA *data)
{
	LIST_DATA *ptr = list->start;
	LIST_DATA *last_ptr = NULL_PTR;
	while (ptr)
	{
		if (ptr == data)
		{
			list->Number--;
			if (list->Number == 1)
				list->end = NULL_PTR;
			if (last_ptr == NULL_PTR)
			{
				list->start = data->next;
				basic_free(data);
				return;
			}
			last_ptr->next = data->next;
			basic_free(data);
			return;
		}
		last_ptr = ptr;
		ptr = ptr->next;
	}

}