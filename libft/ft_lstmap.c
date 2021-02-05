#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*frst;
	t_list	*tmp;

	frst = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		if (!(tmp = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&frst, del);
			return (NULL);
		}
		ft_lstadd_back(&frst, tmp);
		lst = lst->next;
	}
	return (frst);
}
