/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_operators.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:45:52 by van-nguy          #+#    #+#             */
/*   Updated: 2025/06/25 22:27:34 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_operators(t_operators *operators)
{
	ft_strlcpy(operators->redir_in, "<", 2);
	ft_strlcpy(operators->redir_out, ">", 2);
	ft_strlcpy(operators->append, ">>", 3);
	ft_strlcpy(operators->heredoc, "<<", 3);
	ft_strlcpy(operators->pipe, "|", 2);
	ft_strlcpy(operators->and, "&&", 3);
	ft_strlcpy(operators->or, "||", 3);
}
