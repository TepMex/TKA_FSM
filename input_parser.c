#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "input_parser.h"
#include "get_input.h"

void parse_states(char* string, state* states)
{
	int end_pos = strlen(string);
	
	char variable_names[MAX_VARIABLES][MAX_VARIABLE_NAME_SIZE];
	short variable_states[MAX_VARIABLES];
	
	int current_var = 0;
	short current_varstate = 1;
	char current_varname[MAX_VARIABLE_NAME_SIZE];
	int varname_pointer = 0;
	int find_var_index;
	int cycles = 0;
	
	
	for(int i=0; i<=end_pos; i++)
	{
		switch(string[i])
		{
			case '!':
			{
				current_varstate = 0;
				continue;
				break;
			}
			case '-':
			case ')':
			{
				continue;
				break;
			}
			case '>':
			{
				cycles++;
			}
			case '(':
			case ',':
			{
				if((find_var_index = find_exist_var(current_varname,variable_names,current_var)) == -1)
				{
					strcpy(variable_names[current_var],current_varname);
					variable_states[current_var] = current_varstate;
					current_var++;
				}
				else
				{
					variable_states[find_var_index] = current_varstate;
				}
				strcpy(current_varname,"");
				current_varstate = 1;
				varname_pointer = 0;
				continue;
				break;
			}
			
			default:
			{
				current_varname[varname_pointer++] = string[i];
				break;
			}
		}
	}
	
	
	memcpy(states[0].names,variable_names,sizeof(variable_names));
	memcpy(states[0].states,variable_states,sizeof(variable_states));
	states[0].varcount = current_var;
	
	for(int j = 0; j<states[0].varcount; j++)
	{
		printf("%s : %i \n", states[0].names[j],states[0].states[j]);
	}
	printf("cycles: %i \n",cycles);
	
}

int find_exist_var(char* var, char exist_vars[MAX_VARIABLES][MAX_VARIABLE_NAME_SIZE], int max_index)
{
	for(int i = 0; i<max_index; i++)
	{
		if(!strcmp(exist_vars[i],var))
		{
			return i;
		}
	}
	
	return -1;
}

void parse_transitions(char* string,transition* transitions)
{
	char *current_transition;
	
	while((current_transition = strsep(string,TRANSITION_DELIM)) != NULL)
	{
		for(int j = 0; j<strlen(current_transition); j++)
		{
			switch(current_transition[j])
			{
			}
		}
	}
	
}
