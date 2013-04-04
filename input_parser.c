#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "input_parser.h"
#include "get_input.h"
#include "globals.h"

void parse_states(char* string)
{
	int end_pos = strlen(string);
	
	char variable_names[MAX_VARIABLES][MAX_VARIABLE_NAME_SIZE];
	short variable_states[MAX_VARIABLES];
	
	int current_var = 0;
	short current_varstate = 1;
	char current_varname[MAX_VARIABLE_NAME_SIZE];
	int varname_pointer = 0;
	int find_var_index;
	cycles = 0;
	
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
	
	for(int i=0;i<cycles; i++)
	{
		memcpy(states[i].names,variable_names,sizeof(variable_names));
		memcpy(states[i].states,variable_states,sizeof(variable_states));
		states[i].varcount = current_var;
	}
	
	for(int j = 0; j<states[0].varcount; j++)
	{
		//printf("%s : %i \n", states[0].names[j],states[0].states[j]);
	}
	//printf("cycles: %i \n",cycles);
	
	parse_transitions(string,variable_names);
	
	
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

void parse_transitions(char* string, char exist_vars[MAX_VARIABLES][MAX_VARIABLE_NAME_SIZE])
{
	
	int transition_count = 0;
	char *current_transition;
	
	while((current_transition = strsep(&string,TRANSITION_DELIM)) != NULL)
	{
		short curr_state = 1;
		char curr_name[MAX_VARIABLE_NAME_SIZE];
		int pointer = 0;
		int find_index = 0;
		int curr_var = 0;
		transitions[transition_count].changes=0;
		//printf("------\n");
		for(unsigned int j = 0; j<strlen(current_transition); j++)
		{
			
			switch(current_transition[j])
			{
				case '!':
				{
					curr_state = 0;
					continue;
					break;
				}
				
				case '(':
				case ')':
				case ',':
				{
					
					find_index = find_exist_var(curr_name,exist_vars,MAX_VARIABLES);
						
					transitions[transition_count].var_indexes[curr_var] = find_index;
					transitions[transition_count].states[curr_var] = curr_state;
					transitions[transition_count].changes++;
					//printf("%i : %i \n",find_index,curr_state);
					curr_var++;
					
					strcpy(curr_name,"");
					curr_state = 1;
					pointer = 0;
					continue;
					break;
				}
				default:
				{
					curr_name[pointer++] = current_transition[j];
					break;
				}
			}
		}
		
		transition_count++;
	}
	
}

void add_transition(int st_index, int tr_index)
{
	for(int i=0; i<transitions[tr_index].changes; i++)
	{
		states[st_index].states[transitions[tr_index].var_indexes[i]] = transitions[tr_index].states[i];
	}
}
