/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:56:03 by sbehar            #+#    #+#             */
/*   Updated: 2025/06/11 15:56:03 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		cd_too_many_args(char **args);
int		cd_get_target(char **args, t_minishell *shell,
			char **target, char **oldpwd);
int		cd_change_dir(const char *target);
void	cd_update_env(t_minishell *shell, const char *oldpwd);
void	cd_print_cwd_ifn(char **args);
int		count_args(char **args);
int		err_cd_argc(void);
char	*resolve_cd_target(char **args, t_minishell *shell);

int	cd_too_many_args(char **args)
{
	if (count_args(args) > 2)
		return (err_cd_argc());
	return (0);
}

int	cd_get_target(char **args, t_minishell *shell,
			char **target, char **oldpwd)
{
	*oldpwd = get_env_value(shell, "PWD");
	*target = resolve_cd_target(args, shell);
	if (!*target)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	return (0);
}

int	cd_change_dir(const char *target)
{
	if (chdir(target) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

void	cd_update_env(t_minishell *shell, const char *oldpwd)
{
	char	cwd[PATH_MAX];

	set_env_value(shell, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		set_env_value(shell, "PWD", cwd);
}

void	cd_print_cwd_ifn(char **args)
{
	char	cwd[PATH_MAX];

	if (args[1] && !ft_strcmp(args[1], "-"))
	{
		if (getcwd(cwd, sizeof(cwd)))
			printf("%s\n", cwd);
	}
}
