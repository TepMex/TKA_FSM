#include <stdio.h>
#include <stdlib.h>

#include "get_input.h"
#include "input_parser.h"
#include "globals.h"

int main(int argc, char* argv[])
{
	parse_states(get_string_from_config("input.tka"));
	build_states_matrix();
	show_cyclogramm(1);
	return 0;
}

void show_cyclogramm(short digit_view)
{
	for(int i=0; i<states[0].varcount; i++)
	{
		printf("%s ",states[0].names[i]);
		for(int j=0; j<cycles; j++)
		{
			if(digit_view)
			{
				printf("%i ", states[j].states[i]);
			}
			else
			{
				if(states[j].states[i])
				{
					printf("/\\");
				}
				else
				{
					printf("__");
				}
			}
		}
		printf("\n");
		
	}
}

void build_states_matrix()
{
	for(int i=0;i<cycles;i++)
	{
		add_transition(i+1,i);
	}
}
