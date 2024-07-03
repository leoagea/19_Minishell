#include "../../inc/minishell.h"

static int in_quote(char *str, int i)
{
	char quote;

	quote = str[i];
	i++;
	while (str[i])
	{
		while (str[i] != quote && str[i] && quote != 0)
			i++;
		quote = 0;
		i++;
		if ((str[i] == (int)34 || str[i] == (int)39) && str[i])
		{
			quote = str[i];
			i++;
		}
		else if ((check_special_char(str, i) || check_whitespace(str, i)) && str[i])
			return i;
	}
	return i;

}

int lexer(char *input, t_dll *tokens)
{
	int i = 0;
	int start;
	char c;
	char *word;

	while (input[i])
	{
		i = skip_whitespace(input, i);
		if((input[i] == (int)34 || input[i] == (int) 39) && input[i])
		{
			start = i;
			i = in_quote(input, i);
		}
		else
		{
			if (input[i])
			{
				i = skip_whitespace(input, i);
				start = i;
				if (check_special_char(input, i))
					while (check_special_char(input, i))
						i++;
				else
				{
					while (!check_whitespace(input, i) && input[i])
					{
						if((input[i] == (int)34 || input[i] == (int) 39) && input[i])
							i = in_quote(input, i);
						else
							i++;
					}
				}
			}
		}
		word = ft_substr(input, start, i - start);
		c = check_open_quote(word);
		if (c != 34 && c != 39 && c != -2 )
			return (write(1, "Error: open quote\n",18), 1);
		dll_insert_tail(word, tokens);
		i = skip_whitespace(input, i);
	}
	dll_print_forward(tokens);
	if (check_open_pipe(tokens))
		return (write(1, "Error: open pipe\n",17), 1);
}



// "te""st" "cat" | infile > ls

// "'''hola'''"'""hello""'

// echo test"de la mort"te tete

// "Hello"'>''<''|'|"Hello"

/*
minishell$ "HOLA"
test
start : 0
i : 6
word : "HOLA"

start : 7
i : 8
word : 

minishell$ "'HOLA'"
test
start : 0
i : 8
word : "'HOLA'"

minishell$ "''HOLA"
test
start : 0
i : 8
word : "''HOLA"

minishell$ "'''''HOLA'''''HELOO'''"
test
start : 0
i : 24
word : "'''''HOLA'''''HELOO'''"

minishell$ Hello ca
start : 0
i : 5
word : Hello

start : 6
i : 8
word : ca

start : 9
i : 14
word : 

start : 15
i : 16
word : 

start : 17
i : 18
word : 

minishell$ Hello cat 
start : 0
i : 5
word : Hello

start : 6
i : 9
word : cat

minishell$      
start : 0
i : 5
word :      

minishell$            
start : 0
i : 11
word :            

minishell$     
start : 0
i : 4
word :     

minishell$    
start : 0
i : 3
word :    

minishell$     
start : 0
i : 4
word :     

minishell$ "     "
test
start : 0
i : 7
word : "     "

minishell$ '     '
test
start : 0
i : 7
word : '     '

minishell$ "Hello"'>''<''|'|"Hello"
test
start : 0
i : 8
word : "Hello"'

test
start : 9
i : 11
word : ''

test
start : 12
i : 14
word : ''

test
start : 15
i : 24
word : '|"Hello"

start : 25
i : 30
word : 

minishell$ "Hello"">""<""|"|"Hello"
test
start : 0
i : 8
word : "Hello""

test
start : 9
i : 11
word : ""

test
start : 12
i : 14
word : ""

test
start : 15
i : 24
word : "|"Hello"

minishell$ "hello'>"
test
start : 0
i : 7
word : "hello'

test
start : 8
i : 9
word : "
*/


/*----------------------------------*/
/*----------------------------------*/
/*----------------------------------*/
/*----------------------------------*/
/*----------------------------------*/
/*----------------------------------*/
/*----------------------------------*/
/*----------------------------------*/

/*

minishell$ echo lol
start : 0
i : 4
word : echo

start : 5
i : 8
word : lol

minishell$ echo << test
start : 0
i : 4
word : echo

start : 5
i : 6
word : <

start : 6
i : 7
word : <

start : 8
i : 12
word : test

minishell$ echo >> er
start : 0
i : 4
word : echo

start : 5
i : 6
word : >

start : 6
i : 7
word : >

start : 8
i : 10
word : er

minishell$ echo test || cat lo
start : 0
i : 4
word : echo

start : 5
i : 9
word : test

start : 10
i : 11
word : |

start : 11
i : 12
word : |

start : 13
i : 16
word : cat

start : 17
i : 19
word : lo

minishell$ echo lol <<< test
start : 0
i : 4
word : echo

start : 5
i : 8
word : lol

start : 9
i : 10
word : <

start : 10
i : 11
word : <

start : 11
i : 12
word : <

start : 13
i : 17
word : test

minishell$ echo "test de la mort" 
start : 0
i : 4
word : echo

start : 5
i : 22
word : "test de la mort"

minishell$ echo test"de la mort"te tete
start : 0
i : 4
word : echo

start : 5
i : 12
word : test"de

start : 13
i : 15
word : la

start : 16
i : 23
word : mort"te

start : 24
i : 28
word : tete

minishell$ echo "ere er er e"
start : 0
i : 4
word : echo

start : 5
i : 18
word : "ere er er e"

minishell$ echo test'de lamort'erwr
start : 0
i : 4
word : echo

start : 5
i : 12
word : test'de

start : 13
i : 24
word : lamort'erwr

minishell$ echo "test ' de la" mort '
start : 0
i : 4
word : echo

start : 5
i : 19
word : "test ' de la"

start : 20
i : 24
word : mort

start : 25
i : 26
word : '

minishell$ echo test << test << test << 
start : 0
i : 4
word : echo

start : 5
i : 9
word : test

start : 10
i : 11
word : <

start : 11
i : 12
word : <

start : 13
i : 17
word : test

start : 18
i : 19
word : <

start : 19
i : 20
word : <

start : 21
i : 25
word : test

start : 26
i : 27
word : <

start : 27
i : 28
word : <

minishell$ */