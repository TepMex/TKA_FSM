#include <stdio.h>
#include <stdlib.h>

#include "get_input.h"
#include "input_parser.h"

state states[MAX_CYCLES];
transition transitions[MAX_CYCLES];

int main(int argc, char* argv[])
{
	parse_states(get_string_from_config("input.tka"),states);
	return 0;
}
