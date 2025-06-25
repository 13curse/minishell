/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:41:14 by van               #+#    #+#             */
/*   Updated: 2025/06/07 17:34:36 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

// tokenization.c
int		fill_tokens_arr(char *input, char ***tokens,
			t_operators *operators);

// token_utils.c
int		ft_isspace(char c);
int		skip_space(char **input);
int		is_op(char *input, t_operators *operators);
int		reach_next_quote(char **input);

// token_handling.c
int		alloc_and_copy_token(char ***tokens, int *i, char *input, int len);
int		handle_operator(t_token *data, char ***tokens, int *i,
			t_operators *operators);
int		handle_data(t_token *data, char ***tokens, int *i);
void	init_token_data(t_token *data, char **input, int *len, int *quote);
int		handle_end(char ***tokens, int *i, char *input, int len);

// token_split.c
char	**split_tokens(char *input);
int		count_split(char *input, t_operators *operators);

#endif
