/*
 * my_csp_hooks.h
 *
 *  Created on: May 18, 2024
 *      Author: Alessandro
 */

#ifndef INC_MY_CSP_HOOKS_H_
#define INC_MY_CSP_HOOKS_H_

#include <csp/csp.h>

void csp_reboot_hook(void);

void csp_shutdown_hook(void);

#endif /* INC_MY_CSP_HOOKS_H_ */
