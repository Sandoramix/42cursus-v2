/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_solve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:10:39 by odudniak          #+#    #+#             */
/*   Updated: 2024/07/08 19:52:49 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	solve3(t_list **a)
{
	t_list	*n1;
	t_list	*n2;
	t_list	*n3;

	if (!a || lst_issorted(*a))
		return (true);
	if (lst_size(*a) == 2)
		return (ps_swap(a, SA), true);
	n1 = *a;
	n2 = (*a)->next;
	n3 = (*a)->next->next;
	if ((n1->val > n2->val && n2->val > n3->val)
		|| (n2->val < n1->val && n1->val < n3->val)
		|| (n1->val < n3->val && n3->val < n2->val))
		ps_swap(a, SA);
	if (n2->val < n3->val && n3->val < n1->val)
		ps_rot(a, RA);
	else if (n3->val < n1->val && n1->val < n2->val)
		ps_revrot(a, RRA);
	return (true);
}

static void	move_min_to_top(t_list **stack_a)
{
	t_list	*min;
	t_list	*tmp;
	int		idx;
	int		stack_a_size;

	idx = -1;
	tmp = *stack_a;
	min = lst_getmin(*stack_a);
	stack_a_size = lst_size(*stack_a);
	while (tmp && ++idx > -1)
	{
		if (tmp == min)
			break ;
		tmp = tmp->next;
	}
	if (idx <= stack_a_size / 2)
		while (idx-- > 0)
			ps_rot(stack_a, RA);
	else
		while (stack_a_size - idx++ > 0)
			ps_revrot(stack_a, RRA);
}

void	solve(t_list **a, t_list **b)
{
	int		just_pushed;
	int		a_len;
	int		middle_val;

	a_len = lst_size(*a);
	middle_val = lst_middle_val(*a);
	just_pushed = 0;
	while (a_len > 3 && !lst_issorted(*a))
	{
		ps_push(a, b, PB);
		if ((*b)->val < middle_val && just_pushed > 0)
			ps_rot(b, RB);
		else
			just_pushed++;
		a_len--;
	}
	solve3(a);
	while (*b)
	{
		update_next_move(*a, *b);
		execute_fastest(a, b);
	}
	move_min_to_top(a);
}
