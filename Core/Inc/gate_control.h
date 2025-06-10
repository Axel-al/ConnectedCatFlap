#ifndef INC_GATE_CONTROL_H_
#define INC_GATE_CONTROL_H_

#include <stdbool.h>

void unlock_gate_temporary(void);
void lock_gate(void);
bool is_pir_triggered(void);

#endif /* INC_GATE_CONTROL_H_ */
