/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:53:28 by van-nguy          #+#    #+#             */
/*   Updated: 2025/06/13 11:33:48 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

# include <unistd.h>
# include <stdlib.h> 
# include <limits.h>
# include <signal.h>
# include <readline/readline.h>
# include <termios.h>				// gestion des flèches historique
# include <sys/types.h>				// pid_t
# include <sys/wait.h>				// wait, waitpid
# include <sys/ioctl.h>				
# include <fcntl.h>					// O_FLAGS
// # include <readline/history.h>

# include <stdio.h>

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# ifndef MAX_HISTORY
#  define MAX_HISTORY 20
# endif

extern volatile sig_atomic_t	g_sigint_received;

# define MAX_HEREDOCS 15
# define MAX_UNINTERPRETED 32

typedef struct s_operators		t_operators;
typedef struct s_token			t_token;
typedef struct s_history		t_history;
typedef struct s_heredocs		t_heredocs;
typedef struct s_env			t_env;
typedef struct s_input_state	t_input_state;
typedef struct s_expand			t_expand;
typedef struct s_cmd_alloc		t_cmd_alloc;

typedef struct s_minishell
{
	char		**env;
	char		**paths;
	char		*input;
	char		**tokens;
	char		****cmds_lst;
	int			cmdc;
	int			cmd_id;
	int			in_fork;
	int			status;
	int			**pipes;
	pid_t		*pids;
	t_heredocs	*heredocs;
	int			**last_redir_in;
	t_operators	*op;
	t_env		*env_list;
	t_env		*export_list;
	t_history	*history;
	int			**uninterpreted;
	int			stdin;
	int			stdout;
	int			*cmds_seps;
}				t_minishell;

struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
};

struct s_operators
{
	char	redir_in[2];
	char	redir_out[2];
	char	append[3];
	char	heredoc[3];
	char	pipe[2];
	char	and[3];
	char	or[3];
};

struct s_token
{
	char	**tokens;
	char	*input;
	int		len;
};

struct s_cmd_alloc
{
	char	****cmds;
	char	**original_tokens;
};

struct s_expand
{
	t_minishell	*shell;
	char		**token;
	char		**new;
	int			i;
	int			j;
	int			*l;
	char		quote;
};

struct s_history
{
	char				*line;
	struct s_history	*next;
};

struct s_input_state
{
	char	*buffer;
	int		len;
	int		size;
	int		cursor;
	int		history_index;
	int		history_size;
};

struct s_heredocs
{
	int		fds[MAX_HEREDOCS + 1];
	int		i;
	char	*names[MAX_HEREDOCS + 1];
	int		expand_var;
};

enum	e_cmd_sep
{
	PIPE = 0,
	OR = 1,
	AND = 2
};

typedef struct s_fet_params
{
	int		i;
	char	*exp_tkn;
	char	*tkn;
	int		*unint;
	char	*var;
	int		len;
}				t_fet_params;

typedef struct s_exp_tkn
{
	char		*expd_tkn;
	int			unint[256];
	char		*tkn;
	char		**new;
	t_minishell	*shell;
}				t_exp_tkn;

typedef struct s_exp_quotes
{
	int		i;
	int		shift;
	int		rem;
	int		l;
	char	quote;
	int		ign_i;
}				t_exp_quotes;

typedef struct s_cpy_exp
{
	int			i;
	int			l;
	t_minishell	*shell;
}				t_cpy_exp;

// typedef struct s_efv
// {
// 	int		len;
// 	int		quote;
// 	int		uninterpreted_i;
// 	char	*filename;
// 	char	*new;
// 	int		*uninterpreted;
// }				t_efv;

typedef struct s_efv
{
	int	quote;
	int	len;
	int	unint_i;
}				t_efv;

typedef struct s_redir
{
	int	ret;
	int	tkn_i;
}				t_redir;

typedef struct s_redir_in
{
	int	i;
	int	ret;
	int	tkn_i;
}				t_redir_in;

typedef struct s_ev
{
	char	*new;
	int		len;
	int		i;
	char	*token;
	int		j;
	int		ret;
}				t_ev;

typedef struct s_eq
{
	int		i;
	char	quote;
	int		shift;
	int		rem;
	int		ign_i;
	int		l;
}				t_eq;

typedef struct s_fta
{
	int			i;
	int			quote;
	int			len;
	t_operators	*op;
	char		***tokens;
	char		*input;
	int			ret;
}				t_fta;

//---HISTORY---
// arrows.c
void	arrow_up(t_input_state *input, t_minishell *shell,
			const char *prompt);
void	arrow_down(t_input_state *inp, t_minishell *shell,
			const char *prompt);
void	move_cursor_left(t_input_state *input, const char *prompt);
void	move_cursor_right(t_input_state *input, const char *prompt);
// cleaning.c
int		get_terminal_cols(void);
void	clear_lines(int prev_term_width);
// display.c
int		color_prompt_len(const char *s);
int		get_terminal_width(const char *s, const char *prompt);
int		copy_hist_line(t_input_state *input, char *line);
void	print_prompt_and_buff(t_input_state *input, const char *prompt);
// history.c
void	init_input_state(t_input_state *input, int buf_size, int history_size);
void	add_to_history(t_minishell *shell, const char *line);
int		print_history(t_minishell *shell);
void	free_history(t_history *history);
// insertion.c
void	insert_char(t_input_state *input, char c, const char *prompt);
void	delete_char(t_input_state *input, const char *prompt);
int		handle_arrow_keys(t_input_state *input, t_minishell *shell);
// raw_mode.c
int		enable_raw_mode(struct termios *orig_termios);
int		disable_raw_mode(struct termios *orig_termios);

// prompt.c
char	*sent_prompt(t_minishell *shell);

// abort.c
void	kill_shell(t_minishell *shell);
void	free_shell(t_minishell *shell);
void	free_uninterpreted(int ***uninterpreted);
void	free_cmds_seps(int **cmds_seps);
void	free_cmds_lst(t_minishell *shell);
void	free_last_redir_in(t_minishell *shell);

// init.c
int		init_shell(t_minishell *shell, char **envp);
int		init_cmds_seps(t_minishell *shell, int cmdc);

// s_operators.c
void	init_operators(t_operators *operators);

//	---READLINE-------
// 				ft_readline.c
char	*ft_readline(char *prompt, int add_his, t_minishell *shell);
char	*realloc_buffer(char *buffer, int *size);
// 				ft_readline2.c
char	*ft_readline2(t_minishell *shell);
// 				expand_vars_heredoc.c
char	*expand_var_heredoc(t_minishell *shell, char *line);
// 				read_user_input.c
int		get_history_size(t_history *history);
int		init_input_and_buff(t_input_state *input, t_minishell *shell);
int		handle_ctrl_d(t_input_state *input);
int		handle_read_errors(int ret, t_input_state *input);
char	*handle_sigint_rd(t_input_state *input, t_minishell *shell);

// tokenizations.c
char	**split_tokens(char *input);

// token_identification.c
char	***split_cmds(t_minishell *shell, char **tokens);
void	free_cmds(t_minishell *shell, char ****cmds);
void	print_cmds(char ***cmds);
void	print_arr(char **arr);
// cmds_lst.c
char	****cmds_lst(t_minishell *shell, char **tokens);
int		is_cmds_sep(char *str);

//	---EXEC-----------
// 				exec.c
void	exec_all(t_minishell *shell);
// 				child_routine.c
void	child_routine(t_minishell *shell, char **cmd, int cmdc, int cmds_lst_i);
// 				exec_cmd.c
void	exec_cmd(t_minishell *shell, char **cmd);
// 				exec_parent.c
int		exec_parent(t_minishell *shell);

//	---REDIRECTIONS---
// 				redirections.c
int		redirections(t_minishell *shell, char **cmd, int cmds_lst_i);
// 				redirections2.c
void	remove_redirections(t_minishell *shell, char **cmd);
int		redir_in(t_minishell *shell);
int		reset_stdio(t_minishell *shell);
//				last_redir_in.c
int		init_last_redir_in(t_minishell *shell);

//	---EXPANSION------
// 				expand_quotes.c
void	expand_quotes(t_minishell *shell, char **cmd);
int		expand_vars(t_minishell *shell, char **cmd);
// 				uninterpreted.c
int		alloc_uninterpreted(t_minishell *shell, char **cmd);
void	set_uninterpreted(t_minishell *shell, int i);
void	add_uninterpreted(t_minishell *shell, int i, int l);
int		is_interpreted(t_minishell *shell, int i, int l);
void	update_uninterpreted(t_minishell *shell, int ign_i, int l, int shift);
void	print_uninterpreted(t_minishell *shell);		// rm
// 				get_var.c
char	*get_var(t_minishell *shell, char **token);
char	*get_status(t_minishell *shell);
int		is_dollar_to_be_printed(char *token);
// 				count_tokens.c
int		count_tokens_after_expand(t_minishell *shell);

//---HEREDOC---
// heredoc.c
int		heredoc(t_minishell *shell, char *limiter, int i);
int		find_unique_filename(char *name);
int		write_heredoc_line(int fd, char *limiter,
			t_minishell *shell, char **input);
int		write_to_heredoc(t_minishell *shell, char *limiter);
// expand_var_heredoc.c
char	*expand_var_heredoc(t_minishell *shell, char *line);

// utils.c
int		is_op(char *input, t_operators *operators);
void	fill_null(void **arr, int count);
void	free_split(char **split);
int		cmds_len(char ***arr);
int		is_made_of(char *input, char *accepted);
int		arr_len(void **arr);

// token_utils.c
int		ft_isspace(char c);
int		skip_space(char **input);

// errors.c
int		err_malloc(int err);
int		err_unclosed_quote(void);
int		err_too_long_path(int err);

// get_env.c
int		env_lst_size(t_minishell *shell);
void	fill_env(t_minishell *shell, char **envp);
char	*get_env_value(t_minishell *shell, const char *key);
void	set_env_value(t_minishell *shell, const char *key, const char *value);
void	free_env_list(t_minishell *shell);

//---BUILTINS---
// builtins.c
int		exec_builtins(char **args, t_minishell *shell);
int		is_builtin(const char *cmd);
int		builtin_env(t_minishell *shell);
int		builtin_exit(t_minishell *shell, char **args);
int		builtin_export(char **args, t_minishell *shell);
int		builtin_pwd(t_minishell *shell);
int		builtin_unset(char **args, t_minishell *shell);
int		builtin_cd(char **args, t_minishell *shell);
int		builtin_echo(char **args);
int		is_builtin_cmd(t_minishell *shell, char **cmd);
// export_utils.c
int		export_lst_size(t_minishell *shell);
void	ft_sort_str_tab(char **tab);
int		is_valid_id(const char *s);
void	free_args(char **args);
int		is_invalid_opt(const char *arg);
// export_sort.c
void	set_var(t_env **lst, const char *key, const char *value);
char	**get_sorted_exp(t_minishell *shell);
void	append_var(t_env **lst, const char *key, const char *value);
void	extract_exp_key(const char *arg, char *key, int *append);
void	print_export_var(t_env *var);

// signals.c
void	handle_sigint(int sig);
void	setup_signal_handlers(int interactive);

#endif
