/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsas <dsas@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 19:52:06 by dsas              #+#    #+#             */
/*   Updated: 2023/03/25 14:22:50 by dsas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/include.h"

void	change_quotes(t_token *temp)
{
	char	*ret;
	char	*info;
	int		i;

	ret = NULL;
	info = temp->info;
	i = 0;
	while (info[i])
	{
		if (info[i] == '$' && (info[i + 1] != ' ' && info[i + 1] != '\0'))
		{
			sub_dollar(&ret, info, &i);
		}
		else
		{
			charjoin_free(&ret, info[i]);
			i++;
		}
	}
	free(temp->info);
	temp->info = ret;
	temp->len = ft_strlen(ret);
}

void	expander(t_token **token)
{
	t_token	*temp;
	int		index;
	char	*key;
	char	*ret;

	temp = *token;
	while (temp)
	{
		if (temp->type == WORD && temp->info
			&& temp->info[0] == '$' && temp->info[1])
			change_words(temp);
		if (temp->type == DOUBLE_QUOTES)
			change_quotes(temp);
		temp = temp->next;
	}
}

void	sub_dollar(char **ret, char *info, int *i)
{
	char	*key;
	int		index;
	char	*ret1;

	key = NULL;
	(*i)++;
	if (info[*i] == '?' && (!(info[*i]) || info[*i + 1] == ' '))
	{
		strjoin_free(ret, ft_itoa(shell_h->error));
	}
	while (info[*i] != ' ' && info[*i] != '\0')
	{
		charjoin_free(&key, info[*i]);
		(*i)++;
	}
	index = find_path_env(shell_h->envp, key);
	if (index == -1)
	{
		free(key);
		return ;
	}
	ret1 = cut_key(shell_h->envp, index, key);
	free(key);
	strjoin_free(ret, ret1);
	free(ret1);
}