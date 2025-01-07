/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/25 01:20:10 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

/*COLORS*/
# define END "\x1b[0m"
# define RED "\e[1;91m"
# define YELLOW "\e[1;93m"
# define BLUE "\e[1;94m"
# define GREEN "\e[1;92m"
# define CYAN "\e[1;96m"
# define PURPLE "\e[1;95m"
# define ORANGE "\e[1;38;2;255;128;0m"

/*STANDARD*/
# define STDIN 0
# define STDOUT 1
# define STDERR 2

/*PARSING*/
# define PIPE 1
# define INPUT 2
# define HEREDOC 3
# define OUTPUT 4
# define APPEND 5
# define FILE_REDIRECTION 6
# define CMD_ARGV 7

/*VARIABLE GLOBAL*/
extern volatile sig_atomic_t	g_signal_received;

typedef struct s_quotes
{
	int				quotes;
	int				miniquotes;
}					t_quotes;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				hidden;
	int				val;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*content;
	struct s_token	*back;
	struct s_token	*next;
	int				type;
}					t_token;

typedef struct s_xtkn
{
	char			*content;
	struct s_xtkn	*back;
	struct s_xtkn	*next;
	int				type;
	int				heardoc_expansion;
}					t_xtkn;

typedef struct s_redir
{
	int				type;
	char			*file_name;
	pid_t			pid;
	int				fd;
	int				heardoc_expansion;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**argv;
	char			*path;
	pid_t			pid;
	t_redir			*first_redir;
	struct s_cmd	*next;
	int				fd_in;
	int				fd_out;
}					t_cmd;

typedef struct s_xtkns
{
	t_xtkn			*new_xtkn;
	t_xtkn			*xtkn;
}					t_xtkns;

typedef struct s_convert
{
	int				*i;
	char			*tmp;
}					t_convert;

typedef struct s_split
{
	char			del;
	char			**res;
	const char		*s;
	int				stopper;
	int				start;
}					t_split;

typedef struct s_general
{
	char			*line;
	char			*pretoken;
	t_quotes		qdata;
	t_token			*first_token;
	t_xtkn			*first_xtkn;

	char			**paths;
	char			**env_matrix;
	t_cmd			*first_cmd;
	int				exit_status;
	int				pipe_fd[2];
	int				next_cmd_input_fd;
	int				flag;
	t_env			*env_lst;
	int				equal;
	int				builtin;
}					t_general;

// MAIN
int					minishell_loop(t_general *data);
int					line_is_empty_or_whitespace(char *line);

// INITIALITATIONS
void				init_data_values(t_general *data);
void				init_quote_values(t_general *data);
void				init_fd_values(t_general *data);

// SIGNALS
void				init_non_bloquing_signals(void);
void				init_heredoc_signals(void);
void				init_ignore_signals(void);
void				init_bloquing_signals(void);
void				do_eof(t_general *data);
void				control_c_normal_handler(int sig);
void				control_c_heredoc_handler(int sig);

// CREATE OWN ENVIROMENT
int					get_own_env(t_general *data, char **env);
int					set_empty_env(t_general *data);
int					fill_empty_env(t_general *data, char *name, char *value);
int					fill_oldpwd(t_general *data, char *name);
int					fill_path_env(t_general *data, char *name);
int					fill_env_node(t_general *data, t_env *s_env, char **env,
						int i);

void				env_to_lst(t_general *data, t_env *new_env);
void				update_lvl(t_general *data);

// LEXER
int					lexer(t_general *data);
void				delete_spaces(t_general *data);
int					fill_updated_line(t_general *data);
int					review_closed_quotes(t_general *data);
int					delete_useless_spaces(t_general *data);

// PARSER
int					parser(t_general *data);
int					prepare_pretoken(t_general *data, int *i, char ***argv);
int					take_pretoken(t_general *data, int *i);
int					fill_separator_pretoken(t_general *data, int *i);
int					fill_word_pretoken(t_general *data, int *i);
int					is_real_separator(char c, t_general *data);
int					build_tokens_list(t_general *data, char ***argv);
t_token				*create_token(t_general *data);
void				put_new_list_node(t_general *data, t_token *new_token);
void				classify_token_type(t_token *new_token);
int					check_syntax_errors(t_general *data);
int					check_syntax_errors_2(t_general *data, t_token *tmp_token);
void				check_number_of_heredocs(t_general *data);
int					check_pipe(t_general *data, t_token *token);
int					check_input(t_general *data, t_token *token);
int					check_heredoc(t_general *data, t_token *token);
int					check_output(t_general *data, t_token *token);
int					check_append(t_general *data, t_token *token);

// EXPANSOR
int					expansor(t_general *data);
int					start_xtkns(t_general *data);
t_xtkn				*expand_xtkn(t_token *token, t_general *data);
t_xtkn				*token_to_xtoken(t_token *token, t_general *data);
t_xtkn				*create_xtoken(void);
void				put_new_list_xtoken_node(t_general *data, t_xtkn *xtkn);
int					build_expanded_content(t_xtkn *xtkn, t_token *token,
						t_general *data);
int					there_is_expansion_to_manage(t_xtkn *xtkn, t_token *token,
						int *i, t_general *data);
int					there_is_expansion_to_manage_2(t_xtkn *xtkn, t_token *token,
						int *i, t_general *data);
int					expand_regular_variable(t_token *token, t_xtkn *xtkn,
						int *i, t_general *data);
char				*identify_variable_to_expand(t_token *token, int *i);
int					miniquotes_conversion(t_xtkn *xtkn, char *tmp);
int					quotes_conversion(t_xtkn *xtkn, char *tmp, t_env *env);
int					build_heredoc_delimiter(t_xtkn *xtkn, char *tmp);
int					manage_quotes_variable(t_xtkn *xtkn, char *tmp, t_env *env);
int					regular_conversion(t_convert *info, t_token *token,
						t_xtkn *xtkn, t_env *env);
int					manage_inexistent_regular_variable(t_xtkn *xtkn,
						t_token *token, char *tmp, int *i);
int					manage_regular_variable(t_xtkn *xtkn, t_token *token,
						char *tmp, t_env *env);
int					expansor_variable_has_space(char *tmp, t_env *env);
int					expand_exit_status_variable(t_xtkn *xtkn, int exit_status,
						int *i);
int					expand_digit_variable(t_general *data, t_token *token,
						t_xtkn *xtkn, int *i);
int					manage_quotes_after_dollar(t_general *data, t_token *token,
						t_xtkn *xtkn, int *i);
int					manage_miniquotes_after_dollar(t_general *data,
						t_token *token, t_xtkn *xtkn, int *i);
int					manage_dollar_variable_between_quotes(t_general *data,
						t_token *token, t_xtkn *xtkn, int *i);
int					check_expansor_variable_exists(char *tmp, t_env *env);
int					change_expansor_variable(t_xtkn *xtkn, char *tmp,
						t_env *env);
int					expand_final_value(t_xtkn *xtkn, t_env *env_tmp, int *i);
int					split_xtkn(t_xtkn *xtkn, t_general *data);
int					adapt_xtkn_list(t_xtkn *xtkn, t_general *data,
						char **splited_content, t_xtkn *new_xtkn);
int					retokenize_same_xtoken(t_xtkn *xtkn,
						char **splited_content);
int					enlarge_xtkns_list(t_xtkns *info, t_general *data, int *i,
						char **splited_content);
int					finish_xtkns(t_xtkn *first_xtkn, t_general *data);
int					remove_quotes(t_xtkn *xtkn, t_general *data);
int					build_content_without_quotes(t_xtkn *xtkn, t_general *data,
						char **tmp);
void				change_non_printable_chars(t_xtkn *xtkn);

// EXECUTOR
int					executor(t_general *data);
int					preparations_for_the_executor(t_general *data);
int					get_matrix_env(t_general *data, t_env *env_lst);
int					env_matrix_base(t_env *env_lst);
void				free_things(t_general *data);
int					fill_matrix(t_env *tmp, t_general *data, int *i);
int					get_all_paths(t_env *env_lst, t_general *data);
t_env				*there_is_path(t_env *env_lst);
int					get_command(t_general *data, t_xtkn *first_xtkn);
t_cmd				*create_and_put_new_cmd_node(t_general *data);
t_cmd				*create_command(void);
void				put_new_list_cmd_node(t_general *data, t_cmd *new_cmd);
int					count_cmd_argvs(t_xtkn **count_xtkn);
int					fill_cmd_argvs_and_redirs(t_general *data,
						t_xtkn **tmp_xtkn, t_cmd *new_cmd);
int					fill_cmd_argvs(int *i, t_cmd *new_cmd, t_xtkn **tmp_xtkn,
						t_general *data);
t_redir				*create_and_put_new_redir_node(t_general *data,
						t_cmd *new_cmd);
t_redir				*create_redir(void);
void				put_new_list_redir_node(t_cmd *new_cmd, t_redir *new_redir);
int					fill_redir_node(t_general *data, t_xtkn **tmp_xtkn,
						t_redir *new_redir);
int					do_heredoc(t_general *data);
int					manage_heredoc_stuff(t_general *data, int *pipe_fd,
						t_redir *redir);
int					create_heredoc_pipe(t_general *data, int *pipe_fd);
int					child_heredoc_process(t_general *data, int *pipe_fd,
						t_redir *redir);
int					check_limitter_word(char *line, int *pipe_fd,
						t_redir *redir);
void				print_line_in_file(t_redir *redir, char *line, int *pipe_fd,
						t_general *data);
char				*expand_line(char *line, t_general *data);
int					there_is_heredoc_expansion_to_manage(char *line, int *i,
						char **xline, t_general *data);
int					expand_heredoc_digit_variable(char *line, char **xline,
						int *i);
int					expand_heredoc_exit_status_variable(int exit_status,
						char **xline, int *i);
int					expand_heredoc_regular_variable(char *line, int *i,
						t_env *env, char **xline);
char				*identify_heredoc_variable_to_expand(char *line, int *i);
int					change_expanded_heredoc_line(char **xline, char *tmp,
						t_env *env);
int					check_expanded_heredoc_line_exists(char *tmp, t_env *env);
void				heredoc_father_status(t_general *data, int *pid,
						int *pipe_fd);
int					do_execution(t_general *data, int *builtin_only);
int					check_executor_type(t_general *data);
int					builtin_execution_only(t_general *data);
int					check_father_redirs_1(t_general *data, t_cmd *first_cmd);
int					check_father_redirs_2(t_general *data, t_cmd *first_cmd);
int					check_father_append_redir(t_cmd *cmd, t_redir *redir,
						t_general *data);
int					check_father_write_append_file(t_cmd *cmd, t_redir *redir);
int					check_father_output_redir(t_cmd *cmd, t_redir *redir,
						t_general *data);
int					check_father_overwrite_file(t_cmd *cmd, t_redir *redir);
int					check_father_heredoc_redir(t_cmd *cmd, t_redir *redir,
						t_general *data);
int					check_father_input_redir(t_cmd *cmd, t_redir *redir,
						t_general *data);
int					check_father_read_file(t_cmd *cmd, t_redir *redir);
int					get_children(t_general *data, int n, int i);
int					count_commands(t_general *data);
int					duplicate_pipe_fd0(t_general *data);
void				create_pipe(t_general *data);
int					init_new_process(t_general *data, t_cmd *cmd);
int					create_child(t_general *data, t_cmd *cmd, int i, int n);
void				check_cmd_path(t_cmd *cmd, char **paths, t_env *env);
char				*check_cmd_access(char **paths, char *cmd_argv);
char				*check_cmd_absolut_path(char *cmd_argv);
char				*check_cmd_relative_path(char *cmd_argv, char *path);
int					build_command_path(char **tmp, char **tmp2, char *str,
						char *cmd_argv);
void				prepare_input_pipe(t_general *data);
void				prepare_output_pipe(t_general *data);
void				check_redirs(t_cmd *cmd, t_redir *redir);
void				check_heredoc_redir(t_cmd *cmd, t_redir *redir);
void				check_input_redir(t_cmd *cmd, t_redir *redir);
int					check_read_file(t_cmd *cmd, t_redir *redir);
void				check_append_redir(t_cmd *cmd, t_redir *redir);
int					check_write_append_file(t_cmd *cmd, t_redir *redir);
void				check_output_redir(t_cmd *cmd, t_redir *redir);
int					check_overwrite_file(t_cmd *cmd, t_redir *redir);
void				execute_cmd(t_general *data, t_cmd *cmd);
void				close_fds(t_general *data, t_redir *redir);
void				father_status(t_general *data);
void				father_signal_status(t_general *data, int status);

// BUILT-INS
int					is_builtin(t_cmd *cmd);
void				execute_builtin(t_general *data, t_cmd *cmd);
int					do_oldpwd(t_general *data, char **arg);
int					ft_env(t_env *env);
int					ft_pwd(t_env *env);
int					ft_cd(t_general *data, char **argv, int cd_ret);
int					error_dir(t_general *data, char *str);
int					check_dir(char *path);
void				is_hidd(t_general *data, char *name, char *dir);
int					go_to_old_path(t_general *data);
int					go_to_home_path(t_general *data);
void				upd_oldpwd(t_general *data);
int					env_update(t_general *data, char *k_word, char *n_value);
char				*get_env_path(t_general *data, char *k_word);
int					ft_echo(char **argv, t_general *data, int flag);
void				ft_exit(t_general *data);
int					ft_export(char **argv, t_general *data);
int					handle_args(t_general *data, char *argv);
int					ft_unset(t_general *dat, t_cmd *cmd);
void				do_unset(t_general *data, char *var);
void				upd_node(t_env *env, char *old_value, char *value,
						int equal);
void				print_sort(t_env *own_env);
int					print_export_lst(t_env *own_env);
int					export_opt(char *name, char *argv);
void				export_plus_var(t_general *data, char *name, char *value);
char				*find_env_var(t_general *data, char *var_name);
int					env_add_last(t_general *data, char *name, char *value);
void				add_upd_env(t_general *data, char *name, char **value);
int					loop_add_upd_env(t_general *data, char *name, t_env *env,
						char **value);

// UTILS
void				account_quotes(char c, t_general *data);
char				**ft_token_split(char const *s, char del, t_general *data);
int					token_num_words(const char *s, char del, t_general *data);
char				**matrix_token_words(char **res, const char *s, char del,
						t_general *data);
int					matrix_process(t_split *info, int *i, int word,
						t_general *data);
int					build_matrix_word(t_split *info, int *i, int word,
						t_general *data);
void				find_end_of_the_miniquotes_word(int *i, const char *s,
						char del, t_general *data);
void				find_end_of_the_quotes_word(int *i, const char *s, char del,
						t_general *data);
void				find_end_of_the_word(int *i, const char *s, char del,
						t_general *data);
void				skip_delimiter(int *i, const char *s, char del,
						t_general *data);
void				free_token_matrix(char **res, int num_col);

// ERROR_MESSAGES
void				too_many_parameters(void);
void				error_lvl(char *i);
void				perror_message(char *start, char *message);
void				maximum_heredoc_exceeded(void);
void				unexpected_token_message(char *message);
void				end_of_file_in_heredoc(char *limitter_word);
void				no_such_file_or_directory(char *start);
void				permission_denied(char *start);
void				command_not_found(char *start);
void				perror_message(char *start, char *message);
void				ambiguous_redirect(char *start);
int					error_cd_last(t_general *data, char c, int flag);
int					error_identifier(char *s1, char *s2, char **arr,
						char *argv);
void				error_brk(t_general *data, char *msg, char *name, int flag);
int					error_opt(char *s1, char c1);

// FREE
void				free_env(t_env *head);
void				free_before_next_round(t_general *data);
void				free_parsing_process(t_general *data, char ***argv);
void				free_tokens_list(t_general *data);
void				free_pretoken_argv(char ***argv);
void				free_expansor(t_general *data);
void				free_splited_content(char **content);
void				free_executor_process(t_general *data);
void				free_builtin_execution_only(t_general *data,
						int *copy_stdin, int *copy_stdout, char *message);
void				free_xtkns_list(t_general *data);
void				free_matrix_env(t_general *data);
void				free_data_paths(t_general *data);
void				free_get_cmd_process(t_general *data);
void				free_cmd(t_general *data);
void				free_cmd_argv(t_general *data, int *i);
void				free_cmd_redir(t_general *data);
void				free_heredoc_pipe(t_general *data, t_redir *redir,
						int *pipe_fd);
void				free_control_c_in_heredoc(t_general *data);
void				close_heredoc_fds(t_general *data);
void				*ft_memdel(void *ptr);
void				arr_clean(char **arr);
void				unset_free(t_env *env);
void				free_exit(t_general *data);

#endif