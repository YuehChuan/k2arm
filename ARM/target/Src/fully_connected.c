/** 
 * @brief       Autogenerated module by Keras2arm.py
 *              This module contains a function which can be used to
 *              classify mnist images using the ARM-CMSIS-NN lib
 * @Note        This module uses the q15 implementation
 * @date        2019-05-14 17:51
 * @file        fully_connected.c
 * @author      Raphael Zingg zing@zhaw.ch
 * @copyright   2018 ZHAW / Institute of Embedded Systems
 */
#include "arm_nnfunctions.h"
#include "weights.h"
#include "fully_connected.h"
#include <stdint.h>

q15_t aq15_out_Buf[64];

uint8_t fully_connected_run(q15_t * aq15_input_data)
{
    int16_t i16_max_val = 0x8000, i = 0;
    uint8_t u8_max_prediction = 0;

    arm_fully_connected_q15(
        aq15_input_data,
        aq15_layer_1_weights,
        LAYER_1_IN_DIM,
        LAYER_1_OU_DIM,
        LAYER_1_IN_SHIFT,
        LAYER_1_OU_SHIFT,
        aq15_layer_1_bias,
        aq15_out_Buf,
        NULL);
    arm_relu_q15(
        aq15_out_Buf,
        LAYER_1_OU_DIM);
    memcpy(aq15_input_data, aq15_out_Buf, sizeof(aq15_out_Buf));
    arm_fully_connected_q15(
        aq15_input_data,
        aq15_layer_2_weights,
        LAYER_2_IN_DIM,
        LAYER_2_OU_DIM,
        LAYER_2_IN_SHIFT,
        LAYER_2_OU_SHIFT,
        aq15_layer_2_bias,
        aq15_out_Buf,
        NULL);
    arm_relu_q15(
        aq15_out_Buf,
        LAYER_2_OU_DIM);
    memcpy(aq15_input_data, aq15_out_Buf, sizeof(aq15_out_Buf));
    arm_fully_connected_q15(
        aq15_input_data,
        aq15_layer_3_weights,
        LAYER_3_IN_DIM,
        LAYER_3_OU_DIM,
        LAYER_3_IN_SHIFT,
        LAYER_3_OU_SHIFT,
        aq15_layer_3_bias,
        aq15_out_Buf,
        NULL);
    arm_relu_q15(
        aq15_out_Buf,
        LAYER_3_OU_DIM);
    memcpy(aq15_input_data, aq15_out_Buf, sizeof(aq15_out_Buf));
    arm_fully_connected_q15(
        aq15_input_data,
        aq15_layer_4_weights,
        LAYER_4_IN_DIM,
        LAYER_4_OU_DIM,
        LAYER_4_IN_SHIFT,
        LAYER_4_OU_SHIFT,
        aq15_layer_4_bias,
        aq15_out_Buf,
        NULL);
    memcpy(aq15_input_data, aq15_out_Buf, sizeof(aq15_out_Buf));
    arm_softmax_q15(
        aq15_input_data,
        LAYER_4_OU_DIM,
        aq15_out_Buf);
    for(i = 0; i < LAYER_4_OU_DIM; i++) {
        if(i16_max_val < aq15_out_Buf[i]) {
            i16_max_val = aq15_out_Buf[i];
            u8_max_prediction = i;
        }
    }
    return u8_max_prediction;
}
