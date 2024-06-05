/*
 * csp_i2c_settings.h
 *
 *  Created on: Jun 5, 2024
 *      Author: Alessandro
 */

#ifndef INC_CSP_I2C_SETTINGS_H_
#define INC_CSP_I2C_SETTINGS_H_

#define CSP_I2C_ADDRESS 0x01
#define CSP_I2C_BITRATE 100000
#define CSP_NODE_ADDRESS 0x01

int my_i2c_tx(void *driver_data, csp_packet_t *packet);

#endif /* INC_CSP_I2C_SETTINGS_H_ */
