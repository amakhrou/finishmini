/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakhrou <amakhrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:17:14 by amakhrou          #+#    #+#             */
/*   Updated: 2023/09/13 18:15:55 by amakhrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ac_check(int ac)
{
	//g_exit_status = 0;
	if (ac != 1)
	{
		write(2, "minishell : ", 13);
		write(2, "no such file or directory\n", 27);
		exit(1);
	}
}

void    get_input(t_command *command)
{
	
    t_command *cmd;
	t_redirection *in;
	// t_redirection *out;

    int     i;
    int     x;
	
    cmd = command;
	printf("----------TABLE-------------\n");
	i = 0;
	while (cmd)
    {
        x = 0;
        while (cmd->cmd && cmd->cmd[x])
        {
            printf("[node:%d] cmd[%d] = %s\n", i, x, cmd->cmd[x]);
			// printf("type ==================[%d]\n", cmd->type);
			// printf("type ==================[%d]\n", cmd->redirection->type);
            x++;
        }
        if (cmd->redirection)
        {
			in = cmd->redirection;
			while (in)
			{
				printf("-------------in-------------\n");
				printf("type = %d\n", in->type);
				printf("file = %s\n", in->file);
		// 		printf("fd = %d\n", in->fd);
		// 		printf("m_expd = %d\n", in->must_exp);
				in = in->next;
			}
        }
        printf("----------------------------\n");
		i++;
		cmd = cmd->next;
	}
	printf("\n");
}
void	sig_int_handler(int s)
{
	(void)s;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	set_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_int_handler);
}

int main(int ac, char **av, char **env)
{
    t_env_lst   **env_copy;
    char *input;
    t_command   *cmd;
    t_token *token;
	av = NULL;

    ac_check(ac);
    env_copy = env_dyalna(env);
    set_signals();
    while(1)
    {
        input = readline("minishell : ");
        token = NULL;
        if(!input)
        {
            ft_putstr_fd("exit", 2);
            exit(1);
        }
        add_history(input);
        cmd = parse(input, env_copy);
        get_input(cmd);
		free_cmd(cmd);
		free(input);
    }
}