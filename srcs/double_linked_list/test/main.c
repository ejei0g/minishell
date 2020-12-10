#include <stdio.h>
#include <stdlib.h>

typedef struct s_node {
	struct s_node *next;
	int	data;
	//void *data;
}		t_node;

int main(void)
{
	t_node head;

	head.next = NULL;
	head.data = 4;

	t_node *node1 = malloc(sizeof(t_node));
	head.next = node1;
	node1->next = 0;
	node1->data = 1;

	t_node *curr;

	curr = &head;

	while (curr)
	{
		printf("%d -> ", curr->data);
		curr = curr->next;
	}
	return (0);
}
