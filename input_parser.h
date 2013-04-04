#include "definitions.h"
#include "TKA_FSM.h"

void parse_states(char*);
int find_exist_var(char*, char[MAX_VARIABLES][MAX_VARIABLE_NAME_SIZE], int);
void parse_transitions(char*, char[MAX_VARIABLES][MAX_VARIABLE_NAME_SIZE]);
void add_transition(int, int);
