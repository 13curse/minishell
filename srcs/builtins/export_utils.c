/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:07:31 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/06 12:07:31 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		export_lst_size(t_minishell *shell);
void	ft_sort_str_tab(char **tab);
int		is_valid_id(const char *s);
void	free_args(char **args);

int	export_lst_size(t_minishell *shell)
{
	int		len;
	t_env	*export;

	export = shell->export_list;
	if (!export)
		return (0);
	len = 0;
	while (export)
	{
		export = export->next;
		len++;
	}
	return (len);
}

void	ft_sort_str_tab(char **tab)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (tab[i])
	{
		j = i + 1;
		while (tab[j])
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	is_valid_id(const char *s)
{
	int	i;

	if (!s || !(ft_isalpha(s[0]) || s[0] == '_'))
		return (0);
	i = 0;
	while (s[i] && s[i] != '=')
	{
		if (s[i] == '+' && s[i + 1] == '=' && i > 0)
			break ;
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	if (s[i] == '+' && s[i + 1] == '=')
		i++;
	if (s[i] == '=' || s[i] == '\0')
		return (1);
	return (1);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
		free(args[i++]);
	free(args);
}
