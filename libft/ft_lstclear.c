#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = *lst;
		tmp = tmp->next;
		del((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
}
