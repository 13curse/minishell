/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:50:13 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/13 11:28:03 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int			count_args(char **args);
int			err_cd_argc(void);
char		*resolve_cd_target(char **args, t_minishell *shell);
int			builtin_cd(char **args, t_minishell *shell);
int			cd_too_many_args(char **args);
int			cd_get_target(char **args, t_minishell *shell,
				char **target, char **oldpwd);
int			cd_change_dir(const char *target);
void		cd_update_env(t_minishell *shell, const char *oldpwd);
void		cd_print_cwd_ifn(char **args);

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

int	err_cd_argc(void)
{
	ft_printf(2, "minishell: cd: too many arguments\n");
	return (1);
}

char	*resolve_cd_target(char **args, t_minishell *shell)
{
	if (!args[1] || !ft_strcmp(args[1], "~"))
		return (get_env_value(shell, "HOME"));
	else if (!ft_strcmp(args[1], "-"))
		return (get_env_value(shell, "OLDPWD"));
	else
		return (args[1]);
}

int	builtin_cd(char **args, t_minishell *shell)
{
	char	*target;
	char	*oldpwd;

	if (args[1] && is_invalid_opt(args[1]))
	{
		ft_printf(2, "minishell: cd: `%s': not a valid identifier\n",
			args[1]);
		return (2);
	}
	if (cd_too_many_args(args))
		return (1);
	if (cd_get_target(args, shell, &target, &oldpwd))
		return (1);
	if (cd_change_dir(target))
		return (1);
	cd_update_env(shell, oldpwd);
	cd_print_cwd_ifn(args);
	return (0);
}
