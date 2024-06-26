#include "../../inc/minishell.h"

char *trim_str(char *str, int new_start)
{
	char *new;
	char *input;
	int i;
	int j;

	i = 0;
	if (str)
	{	
		input = ft_strdup(str);
		free(str);
		str = NULL;
	}
	new = malloc(sizeof(char) * (ft_strlen(str) - new_start) + 1);
	if (!new)
		return NULL;
	while(i < new_start)
		i++;
	j = 0;
	while(str[i])
	{
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (free(input),new);
}

void read_word(char *str)
{
	
	int i;
	char *word;

	i = 0;
	printf("str read word : %s\n",str);
	i += check_quotes(str, 0, (int) 34);
	i += check_quotes(str, 0, (int) 39);
	if (i == 0)
		i = check_len_token(str, 0);
	// if (check_special_char(str, i))
	printf("next char is special char : %d\n", check_special_char(str, i));
	printf("next char is whitespace char : %d\n", check_whitespace(str, i));
	printf("i : %d char : %c\n", i, str[i]);
	word = ft_substr(str, 0, i);
	str = trim_str(ft_strdup(str), i); //probleme eqund on trim le word de str
	printf("str : %s\n", str);
	printf("word : %s\n", word);
}

// segfault quand on envoie ca :        "echo | cat" > infile -e | pwd
int token_read_(char *input, t_tokens *token){
	
	char *dup;
	int i;

	i = 0;
	while (check_whitespace(input, i))
		i++;
	if (i != 0){
		dup = trim_str(input, i);
		printf("str token read : %s\n", dup);
		read_word(dup);
	}
	else if (i == 0){
		printf("str token read : %s\n", input);
		read_word(input);
	}
	// while (dup){
	// 	token = malloc(sizeof(t_tokens));

	// }
	printf("-----------------------\n\n");
}

//		"echo | cat" > infile -e | pwd