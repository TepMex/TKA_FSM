#include "definitions.h"

typedef struct
{
	char names[MAX_VARIABLES][MAX_VARIABLE_NAME_SIZE];
	short states[MAX_VARIABLES];
	int varcount;
} state;

typedef struct
{
	int var_indexes[MAX_TRANSITIONS];
	short states[MAX_TRANSITIONS];
	int changes;
} transition;

void show_cyclogramm(short);
void build_states_matrix(void);
