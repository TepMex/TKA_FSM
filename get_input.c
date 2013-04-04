#include <stdio.h>
#include <stdlib.h>

#include "get_input.h"

char* get_string_from_config(char* config_file_name)
{
	FILE *config_file;
	char* current_string = (char*)malloc(MAX_INPUT_STRING_SIZE);
	char* config_string = (char*)malloc(MAX_INPUT_STRING_SIZE);
	int chars_readed = 0;
	int config_string_pointer = 0;
	
	short is_config = 0;
	
	if((config_file = fopen(config_file_name,"r")) == NULL)
	{
		printf("Error: could not to open file");
	}
	else
	{
		chars_readed = fread(current_string,sizeof(char),MAX_INPUT_STRING_SIZE,config_file);
		fclose(config_file);
	}
	
	for(int i=0; i<chars_readed; i++)
	{
		switch(current_string[i])
		{
			case '|':
			{
				if(!is_config)
				{
					is_config = 1;
				}
				else
				{
					is_config = 0;
				}
				continue;
				break;
			}
			
			case '\n':
			case '\t':
			case '\0':
			case '\r':
			case ' ':
			{
				continue;
			}
			
			default:
			{
				break;
			}
		}
		
		if(is_config)
		{
			config_string[config_string_pointer++] = current_string[i];
		}
		
	}
	
	free(current_string);
	free(config_string);
	
	return config_string;
}
