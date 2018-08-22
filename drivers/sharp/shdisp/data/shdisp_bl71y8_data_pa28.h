/* drivers/sharp/shdisp/data/shdisp_bl71y8_data_pa28.h  (Display Driver)
 *
 * Copyright (C) 2015 SHARP CORPORATION
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

/* ------------------------------------------------------------------------- */
/* SHARP DISPLAY DRIVER FOR KERNEL MODE                                        */
/* ------------------------------------------------------------------------- */

#ifndef SHDISP_BL71Y8_DATA_PA28_H
#define SHDISP_BL71Y8_DATA_PA28_H

/* ------------------------------------------------------------------------- */
/* INCLUDE FILES                                                             */
/* ------------------------------------------------------------------------- */

#include "../shdisp_bl71y8.h"

/* ------------------------------------------------------------------------- */
/* MACROS                                                                    */
/* ------------------------------------------------------------------------- */

#define SHDISP_BKL_FIX_TBL_NUM                  (256)
#define SHDISP_BKL_AUTO_STEP_NUM                (253)
#define SHDISP_BKL_AUTO_OPT_TBL_NUM             (24)
#define SHDISP_BKL_EMERGENCY_LIMIT_AUTO         (120)
#define SHDISP_BKL_EMERGENCY_LIMIT_FIX          (0x19)
#define SHDISP_BKL_PWM_LOWER_LIMIT              (0x000F)
#define SHDISP_BKL_PWM_OPT0_LOWER_LIMIT         (0x000F)
#define SHDISP_BKL_PWM_OPT1_23_LOWER_LIMIT      (0x0010)
#define SHDISP_BKL_PWM_UPPER_LIMIT              (0x03E8)
#define SHDISP_BKL_CURRENT_LOWER_LIMIT          (0)
#define SHDISP_BKL_CURRENT_UPPER_LIMIT          (190)
#ifdef SHDISP_ALS_INT
#define SHDISP_INT_ENABLE_GFAC                  (0x032C0308)
#else
#define SHDISP_INT_ENABLE_GFAC                  (0x002C0308)
#endif
#define SHDISP_LUX_CHANGE_LEVEL1                (0x0B)
#define SHDISP_LUX_CHANGE_LEVEL2                (0x01)
#define SHDISP_TRI_LED_EMOPATTERN_COLOR         (1)
#define SHDISP_TRI_LED_COLOR_TBL_NUM            (8)
#define SHDISP_COL_VARI_KIND                    (4)
#define SHDISP_HANDSET_COLOR_WHITE              (0x01)
#define SHDISP_HANDSET_COLOR_PINK               (0x02)
#define SHDISP_HANDSET_COLOR_TURQUOISE          (0x04)
#define SHDISP_HANDSET_COLOR_BLACK              (0x06)

/* ------------------------------------------------------------------------- */
/* MACROS(Register Value)                                                    */
/* ------------------------------------------------------------------------- */

#define BDIC_REG_VO2_PFML_VAL                   (0x17)
#define BDIC_REG_VO2_PWML_VAL                   (0x17)
#define BDIC_REG_VO2_PWMH_VAL                   (0x17)
#define BDIC_REG_M1LED_VAL                      (0x5C)
#define BDIC_REG_M2LED_VAL                      (0x5C)
#define BDIC_REG_SYSTEM1_BKL                    (0x03)
#define BDIC_REG_DCDC1_CLIMT_2_VAL              (0xC0)
#define BDIC_REG_DCDC1_GM_VAL                   (0x28)
#define BDIC_REG_DCDC1_OSC_2_VAL                (0x11)

#define BDIC_REG_GPIO_6_VAL                     (0x04)
#define BDIC_REG_GPIO_ANSW_VAL                  (0x1C)
#define BDIC_REG_GPIMSK1_VAL                    (0x21)

#define BDIC_REG_AR_HI_TH_L_L_VAL               (0xFF)
#define BDIC_REG_AR_HI_TH_L_H_VAL               (0xFF)
#define BDIC_REG_AR_LO_TH_M_L_VAL               (0xB8)
#define BDIC_REG_AR_LO_TH_M_H_VAL               (0x0B)
#define BDIC_REG_AR_HI_TH_M_L_VAL               (0xFF)
#define BDIC_REG_AR_HI_TH_M_H_VAL               (0xFF)
#define BDIC_REG_AR_LO_TH_H_L_VAL               (0xE0)
#define BDIC_REG_AR_LO_TH_H_H_VAL               (0x2E)
#define BDIC_REG_AR_HI_TH_L_L_VAL_PS_ON         (0xFF)
#define BDIC_REG_AR_HI_TH_L_H_VAL_PS_ON         (0x3F)
#define BDIC_REG_AR_LO_TH_M_L_VAL_PS_ON         (0xEE)
#define BDIC_REG_AR_LO_TH_M_H_VAL_PS_ON         (0x02)
#define BDIC_REG_AR_HI_TH_M_L_VAL_PS_ON         (0xFF)
#define BDIC_REG_AR_HI_TH_M_H_VAL_PS_ON         (0x3F)
#define BDIC_REG_AR_LO_TH_H_L_VAL_PS_ON         (0xB8)
#define BDIC_REG_AR_LO_TH_H_H_VAL_PS_ON         (0x0B)
#define BDIC_REG_ALS_SHIFT_PS_OFF               (0x03)
#define BDIC_REG_ALS_SHIFT_PS_ON                (0x05)
#define BDIC_REG_AR_RANGE_L_VAL                 (0x18)
#define BDIC_REG_AR_RANGE_M_VAL                 (0x1C)
#define BDIC_REG_AR_RANGE_H_VAL                 (0x1E)
#define BDIC_REG_DATA_SHIFT_M_VAL               (0x40)
#define BDIC_REG_DATA_SHIFT_H_VAL               (0x06)

#define BDIC_REG_AR_RANGE_L_VAL_PS_ON           (0x20)
#define BDIC_REG_AR_RANGE_M_VAL_PS_ON           (0x24)
#define BDIC_REG_AR_RANGE_H_VAL_PS_ON           (0x26)

#define BDIC_REG_AR_CTRL_VAL                    (0xDE)

#define BDIC_REG_ALS_ADJ0_L_DEFAULT_A           (0x5C)
#define BDIC_REG_ALS_ADJ0_H_DEFAULT_A           (0x3F)
#define BDIC_REG_ALS_ADJ1_L_DEFAULT_A           (0x5C)
#define BDIC_REG_ALS_ADJ1_H_DEFAULT_A           (0x3F)
#define BDIC_REG_ALS_SHIFT_DEFAULT_A            (0x03)
#define BDIC_REG_CLEAR_OFFSET_DEFAULT_A         (0x00)
#define BDIC_REG_IR_OFFSET_DEFAULT_A            (0x00)

#define BDIC_REG_ALS_ADJ0_L_DEFAULT_B           (0xAC)
#define BDIC_REG_ALS_ADJ0_H_DEFAULT_B           (0x0C)
#define BDIC_REG_ALS_ADJ1_L_DEFAULT_B           (0x00)
#define BDIC_REG_ALS_ADJ1_H_DEFAULT_B           (0x00)
#define BDIC_REG_ALS_SHIFT_DEFAULT_B            (0x03)
#define BDIC_REG_CLEAR_OFFSET_DEFAULT_B         (0x00)
#define BDIC_REG_IR_OFFSET_DEFAULT_B            (0x00)

#define BDIC_REG_OPT_TH_SHIFT_1_0_VAL           (0x00)
#define BDIC_REG_OPT_TH_SHIFT_3_2_VAL           (0x00)
#define BDIC_REG_OPT_TH_SHIFT_4_5_VAL           (0x00)
#define BDIC_REG_OPT_TH_SHIFT_6_7_VAL           (0x00)
#define BDIC_REG_OPT_TH_SHIFT_8_9_VAL           (0x00)
#define BDIC_REG_OPT_TH_SHIFT_11_10_VAL         (0x00)
#define BDIC_REG_OPT_TH_SHIFT_13_12_VAL         (0x00)
#define BDIC_REG_OPT_TH_SHIFT_15_14_VAL         (0x00)
#define BDIC_REG_OPT_TH_SHIFT_17_16_VAL         (0x44)
#define BDIC_REG_OPT_TH_SHIFT_19_18_VAL         (0x44)
#define BDIC_REG_OPT_TH_SHIFT_21_20_VAL         (0x44)
#define BDIC_REG_OPT_TH_SHIFT_23_22_VAL         (0x44)

#define BDIC_REG_OPT0_LT_L_VAL                  (0x00)
#define BDIC_REG_OPT0_LT_H_VAL                  (0x00)
#define BDIC_REG_OPT0_HT_L_VAL                  (0x20)
#define BDIC_REG_OPT0_HT_H_VAL                  (0x01)
#define BDIC_REG_OPT1_LT_L_VAL                  (0x0E)
#define BDIC_REG_OPT1_LT_H_VAL                  (0x00)
#define BDIC_REG_OPT1_HT_L_VAL                  (0xB2)
#define BDIC_REG_OPT1_HT_H_VAL                  (0x01)
#define BDIC_REG_OPT2_LT_L_VAL                  (0xAE)
#define BDIC_REG_OPT2_LT_H_VAL                  (0x01)
#define BDIC_REG_OPT2_HT_L_VAL                  (0xB3)
#define BDIC_REG_OPT2_HT_H_VAL                  (0x01)
#define BDIC_REG_OPT3_LT_L_VAL                  (0xAF)
#define BDIC_REG_OPT3_LT_H_VAL                  (0x01)
#define BDIC_REG_OPT3_HT_L_VAL                  (0xB4)
#define BDIC_REG_OPT3_HT_H_VAL                  (0x01)
#define BDIC_REG_OPT4_LT_L_VAL                  (0xB0)
#define BDIC_REG_OPT4_LT_H_VAL                  (0x01)
#define BDIC_REG_OPT4_HT_L_VAL                  (0xB5)
#define BDIC_REG_OPT4_HT_H_VAL                  (0x01)
#define BDIC_REG_OPT5_LT_L_VAL                  (0xB1)
#define BDIC_REG_OPT5_LT_H_VAL                  (0x01)
#define BDIC_REG_OPT5_HT_L_VAL                  (0x25)
#define BDIC_REG_OPT5_HT_H_VAL                  (0x02)
#define BDIC_REG_OPT6_LT_L_VAL                  (0xEB)
#define BDIC_REG_OPT6_LT_H_VAL                  (0x01)
#define BDIC_REG_OPT6_HT_L_VAL                  (0x2B)
#define BDIC_REG_OPT6_HT_H_VAL                  (0x03)
#define BDIC_REG_OPT7_LT_L_VAL                  (0xC5)
#define BDIC_REG_OPT7_LT_H_VAL                  (0x02)
#define BDIC_REG_OPT7_HT_L_VAL                  (0x50)
#define BDIC_REG_OPT7_HT_H_VAL                  (0x04)
#define BDIC_REG_OPT8_LT_L_VAL                  (0xF0)
#define BDIC_REG_OPT8_LT_H_VAL                  (0x03)
#define BDIC_REG_OPT8_HT_L_VAL                  (0x3B)
#define BDIC_REG_OPT8_HT_H_VAL                  (0x06)
#define BDIC_REG_OPT9_LT_L_VAL                  (0x75)
#define BDIC_REG_OPT9_LT_H_VAL                  (0x05)
#define BDIC_REG_OPT9_HT_L_VAL                  (0x0B)
#define BDIC_REG_OPT9_HT_H_VAL                  (0x0A)
#define BDIC_REG_OPT10_LT_L_VAL                 (0x85)
#define BDIC_REG_OPT10_LT_H_VAL                 (0x08)
#define BDIC_REG_OPT10_HT_L_VAL                 (0x90)
#define BDIC_REG_OPT10_HT_H_VAL                 (0x0E)
#define BDIC_REG_OPT11_LT_L_VAL                 (0x10)
#define BDIC_REG_OPT11_LT_H_VAL                 (0x0D)
#define BDIC_REG_OPT11_HT_L_VAL                 (0x90)
#define BDIC_REG_OPT11_HT_H_VAL                 (0x14)
#define BDIC_REG_OPT12_LT_L_VAL                 (0x50)
#define BDIC_REG_OPT12_LT_H_VAL                 (0x12)
#define BDIC_REG_OPT12_HT_L_VAL                 (0x45)
#define BDIC_REG_OPT12_HT_H_VAL                 (0x1E)
#define BDIC_REG_OPT13_LT_L_VAL                 (0x8B)
#define BDIC_REG_OPT13_LT_H_VAL                 (0x1A)
#define BDIC_REG_OPT13_HT_L_VAL                 (0x0B)
#define BDIC_REG_OPT13_HT_H_VAL                 (0x34)
#define BDIC_REG_OPT14_LT_L_VAL                 (0x05)
#define BDIC_REG_OPT14_LT_H_VAL                 (0x2B)
#define BDIC_REG_OPT14_HT_L_VAL                 (0xE5)
#define BDIC_REG_OPT14_HT_H_VAL                 (0x5E)
#define BDIC_REG_OPT15_LT_L_VAL                 (0xFB)
#define BDIC_REG_OPT15_LT_H_VAL                 (0x4D)
#define BDIC_REG_OPT15_HT_L_VAL                 (0xDB)
#define BDIC_REG_OPT15_HT_H_VAL                 (0xC9)
#define BDIC_REG_OPT16_LT_L_VAL                 (0xCD)
#define BDIC_REG_OPT16_LT_H_VAL                 (0x09)
#define BDIC_REG_OPT16_HT_L_VAL                 (0xE6)
#define BDIC_REG_OPT16_HT_H_VAL                 (0x14)
#define BDIC_REG_OPT17_LT_L_VAL                 (0x2A)
#define BDIC_REG_OPT17_LT_H_VAL                 (0x12)
#define BDIC_REG_OPT17_HT_L_VAL                 (0x78)
#define BDIC_REG_OPT17_HT_H_VAL                 (0x1D)
#define BDIC_REG_OPT18_LT_L_VAL                 (0x8D)
#define BDIC_REG_OPT18_LT_H_VAL                 (0x1A)
#define BDIC_REG_OPT18_HT_L_VAL                 (0xAA)
#define BDIC_REG_OPT18_HT_H_VAL                 (0x29)
#define BDIC_REG_OPT19_LT_L_VAL                 (0x06)
#define BDIC_REG_OPT19_LT_H_VAL                 (0x25)
#define BDIC_REG_OPT19_HT_L_VAL                 (0x32)
#define BDIC_REG_OPT19_HT_H_VAL                 (0x37)
#define BDIC_REG_OPT20_LT_L_VAL                 (0xC0)
#define BDIC_REG_OPT20_LT_H_VAL                 (0x32)
#define BDIC_REG_OPT20_HT_L_VAL                 (0xA5)
#define BDIC_REG_OPT20_HT_H_VAL                 (0x4C)
#define BDIC_REG_OPT21_LT_L_VAL                 (0x25)
#define BDIC_REG_OPT21_LT_H_VAL                 (0x44)
#define BDIC_REG_OPT21_HT_L_VAL                 (0x2B)
#define BDIC_REG_OPT21_HT_H_VAL                 (0x75)
#define BDIC_REG_OPT22_LT_L_VAL                 (0x28)
#define BDIC_REG_OPT22_LT_H_VAL                 (0x65)
#define BDIC_REG_OPT22_HT_L_VAL                 (0xD9)
#define BDIC_REG_OPT22_HT_H_VAL                 (0x9C)
#define BDIC_REG_OPT23_LT_L_VAL                 (0x03)
#define BDIC_REG_OPT23_LT_H_VAL                 (0x91)
#define BDIC_REG_OPT23_HT_L_VAL                 (0xFF)
#define BDIC_REG_OPT23_HT_H_VAL                 (0xFF)

#define SENSOR_REG_COMMAND2_INI_VAL             (0x28)

#define SENSOR_REG_PS_LT_LSB_VAL                (0xFF)
#define SENSOR_REG_PS_LT_MSB_VAL                (0xFF)
#define SENSOR_REG_PS_HT_LSB_VAL                (0xFF)
#define SENSOR_REG_PS_HT_MSB_VAL                (0xFF)

#define BDIC_WAIT_TIMER_STOP                    (3 * 1000)
#define SENSOR_WAIT_UNDEFINED                   (100000)

/* ------------------------------------------------------------------------- */
/* VARIABLES                                                                 */
/* ------------------------------------------------------------------------- */


static const unsigned char shdisp_main_bkl_tbl[SHDISP_BKL_FIX_TBL_NUM] = {
    0x00,
    0x04,
    0x04,
    0x04,
    0x05,
    0x05,
    0x05,
    0x05,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x07,
    0x07,
    0x07,
    0x07,
    0x07,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x09,
    0x09,
    0x09,
    0x09,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x0B,
    0x0B,
    0x0B,
    0x0B,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0D,
    0x0D,
    0x0D,
    0x0E,
    0x0E,
    0x0E,
    0x0E,
    0x0F,
    0x0F,
    0x0F,
    0x0F,
    0x10,
    0x10,
    0x10,
    0x11,
    0x11,
    0x11,
    0x12,
    0x12,
    0x12,
    0x12,
    0x13,
    0x13,
    0x13,
    0x14,
    0x14,
    0x14,
    0x15,
    0x15,
    0x15,
    0x16,
    0x16,
    0x16,
    0x17,
    0x17,
    0x17,
    0x18,
    0x18,
    0x18,
    0x19,
    0x19,
    0x19,
    0x1A,
    0x1A,
    0x1B,
    0x1B,
    0x1B,
    0x1C,
    0x1C,
    0x1C,
    0x1D,
    0x1D,
    0x1E,
    0x1E,
    0x1E,
    0x1F,
    0x1F,
    0x20,
    0x20,
    0x21,
    0x21,
    0x21,
    0x22,
    0x22,
    0x23,
    0x23,
    0x24,
    0x24,
    0x25,
    0x25,
    0x26,
    0x26,
    0x27,
    0x27,
    0x28,
    0x28,
    0x29,
    0x29,
    0x2A,
    0x2A,
    0x2B,
    0x2B,
    0x2C,
    0x2C,
    0x2D,
    0x2D,
    0x2E,
    0x2F,
    0x2F,
    0x30,
    0x30,
    0x31,
    0x32,
    0x32,
    0x33,
    0x33,
    0x34,
    0x35,
    0x35,
    0x36,
    0x37,
    0x37,
    0x38,
    0x39,
    0x39,
    0x3A,
    0x3B,
    0x3C,
    0x3C,
    0x3D,
    0x3E,
    0x3F,
    0x3F,
    0x40,
    0x41,
    0x42,
    0x42,
    0x43,
    0x44,
    0x45,
    0x46,
    0x46,
    0x47,
    0x48,
    0x49,
    0x4A,
    0x4B,
    0x4C,
    0x4D,
    0x4D,
    0x4E,
    0x4F,
    0x50,
    0x51,
    0x52,
    0x53,
    0x54,
    0x55,
    0x56,
    0x57,
    0x58,
    0x59,
    0x5A,
    0x5B,
    0x5C,
    0x5D,
    0x5E,
    0x5F,
    0x60,
    0x61,
    0x63,
    0x64,
    0x65,
    0x66,
    0x67,
    0x68,
    0x69,
    0x6B,
    0x6C,
    0x6D,
    0x6E,
    0x6F,
    0x71,
    0x72,
    0x73,
    0x74,
    0x76,
    0x77,
    0x78,
    0x7A,
    0x7B,
    0x7C,
    0x7E,
    0x7F,
    0x80,
    0x82,
    0x83,
    0x84,
    0x86,
    0x87,
    0x89,
    0x8A,
    0x8C,
    0x8D,
    0x8E,
    0x90,
    0x91,
    0x93,
    0x94,
    0x96,
    0x97,
    0x99,
    0x9A,
    0x9C,
    0x9D,
    0x9F,
    0xA0,
    0xA2,
    0xA3,
    0xA5,
    0xA6,
    0xA8,
    0xAA,
    0xAB,
    0xAD,
    0xAE,
    0xB0,
    0xB1,
    0xB3,
    0xB5,
    0xB6,
    0xB8,
    0xB9,
    0xBB,
    0xBD,
    0xBE
};

static const unsigned short shdisp_main_bkl_min_tbl[SHDISP_BKL_AUTO_OPT_TBL_NUM] = {
    9
   ,15
   ,15
   ,15
   ,15
   ,15
   ,18
   ,22
   ,24
   ,28
   ,35
   ,39
   ,43
   ,49
   ,53
   ,58
   ,65
   ,69
   ,75
   ,88
   ,116
   ,185
   ,365
   ,566
};

static const unsigned short shdisp_main_bkl_max_tbl[SHDISP_BKL_AUTO_OPT_TBL_NUM] = {
    110
   ,251
   ,251
   ,251
   ,251
   ,251
   ,330
   ,419
   ,476
   ,586
   ,771
   ,882
   ,1015
   ,1185
   ,1307
   ,1488
   ,1707
   ,1864
   ,2051
   ,2245
   ,2333
   ,2423
   ,2423
   ,2284
};

static unsigned short const shdisp_bdic_bkl_ado_index[SHDISP_BKL_AUTO_OPT_TBL_NUM] = {
    ((BDIC_REG_OPT0_HT_H_VAL << 8)  | BDIC_REG_OPT0_HT_L_VAL),
    ((BDIC_REG_OPT1_HT_H_VAL << 8)  | BDIC_REG_OPT1_HT_L_VAL),
    ((BDIC_REG_OPT2_HT_H_VAL << 8)  | BDIC_REG_OPT2_HT_L_VAL),
    ((BDIC_REG_OPT3_HT_H_VAL << 8)  | BDIC_REG_OPT3_HT_L_VAL),
    ((BDIC_REG_OPT4_HT_H_VAL << 8)  | BDIC_REG_OPT4_HT_L_VAL),
    ((BDIC_REG_OPT5_HT_H_VAL << 8)  | BDIC_REG_OPT5_HT_L_VAL),
    ((BDIC_REG_OPT6_HT_H_VAL << 8)  | BDIC_REG_OPT6_HT_L_VAL),
    ((BDIC_REG_OPT7_HT_H_VAL << 8)  | BDIC_REG_OPT7_HT_L_VAL),
    ((BDIC_REG_OPT8_HT_H_VAL << 8)  | BDIC_REG_OPT8_HT_L_VAL),
    ((BDIC_REG_OPT9_HT_H_VAL << 8)  | BDIC_REG_OPT9_HT_L_VAL),
    ((BDIC_REG_OPT10_HT_H_VAL << 8) | BDIC_REG_OPT10_HT_L_VAL),
    ((BDIC_REG_OPT11_HT_H_VAL << 8) | BDIC_REG_OPT11_HT_L_VAL),
    ((BDIC_REG_OPT12_HT_H_VAL << 8) | BDIC_REG_OPT12_HT_L_VAL),
    ((BDIC_REG_OPT13_HT_H_VAL << 8) | BDIC_REG_OPT13_HT_L_VAL),
    ((BDIC_REG_OPT14_HT_H_VAL << 8) | BDIC_REG_OPT14_HT_L_VAL),
    ((BDIC_REG_OPT15_HT_H_VAL << 8) | BDIC_REG_OPT15_HT_L_VAL),
    ((BDIC_REG_OPT16_HT_H_VAL << 8) | BDIC_REG_OPT16_HT_L_VAL),
    ((BDIC_REG_OPT17_HT_H_VAL << 8) | BDIC_REG_OPT17_HT_L_VAL),
    ((BDIC_REG_OPT18_HT_H_VAL << 8) | BDIC_REG_OPT18_HT_L_VAL),
    ((BDIC_REG_OPT19_HT_H_VAL << 8) | BDIC_REG_OPT19_HT_L_VAL),
    ((BDIC_REG_OPT20_HT_H_VAL << 8) | BDIC_REG_OPT20_HT_L_VAL),
    ((BDIC_REG_OPT21_HT_H_VAL << 8) | BDIC_REG_OPT21_HT_L_VAL),
    ((BDIC_REG_OPT22_HT_H_VAL << 8) | BDIC_REG_OPT22_HT_L_VAL),
    ((BDIC_REG_OPT23_HT_H_VAL << 8) | BDIC_REG_OPT23_HT_L_VAL)
};

static const struct shdisp_bdic_led_color_index shdisp_triple_led_color_index_tbl[SHDISP_TRI_LED_COLOR_TBL_NUM] = {
    {0, 0, 0,  0}
   ,{1, 0, 0,  1}
   ,{0, 1, 0,  2}
   ,{1, 1, 0,  3}
   ,{0, 0, 1,  4}
   ,{1, 0, 1,  5}
   ,{0, 1, 1,  6}
   ,{1, 1, 1,  7}
};

static const unsigned char shdisp_clrvari_index[SHDISP_COL_VARI_KIND] = {
    SHDISP_HANDSET_COLOR_BLACK,
    SHDISP_HANDSET_COLOR_PINK,
    SHDISP_HANDSET_COLOR_WHITE,
    SHDISP_HANDSET_COLOR_TURQUOISE
};

static const unsigned char shdisp_triple_led_tbl[SHDISP_COL_VARI_KIND][SHDISP_TRI_LED_COLOR_TBL_NUM][3] = {
  {
    { 0x00, 0x00, 0x00 },
    { 0x50, 0x00, 0x00 },
    { 0x00, 0x64, 0x00 },
    { 0x3C, 0x3C, 0x00 },
    { 0x00, 0x00, 0x64 },
    { 0x3C, 0x00, 0x3C },
    { 0x00, 0x3C, 0x3C },
    { 0x1D, 0x27, 0x15 }
  },
  {
    { 0x00, 0x00, 0x00 },
    { 0x2D, 0x00, 0x00 },
    { 0x00, 0x1E, 0x00 },
    { 0x25, 0x25, 0x00 },
    { 0x00, 0x00, 0x41 },
    { 0x24, 0x00, 0x24 },
    { 0x00, 0x1E, 0x1E },
    { 0x12, 0x1C, 0x0C }
  },
  {
    { 0x00, 0x00, 0x00 },
    { 0x14, 0x00, 0x00 },
    { 0x00, 0x14, 0x00 },
    { 0x14, 0x14, 0x00 },
    { 0x00, 0x00, 0x50 },
    { 0x14, 0x00, 0x14 },
    { 0x00, 0x0F, 0x0F },
    { 0x0C, 0x12, 0x08 }
  },
  {
    { 0x00, 0x00, 0x00 },
    { 0x32, 0x00, 0x00 },
    { 0x00, 0x1E, 0x00 },
    { 0x28, 0x28, 0x00 },
    { 0x00, 0x00, 0x46 },
    { 0x24, 0x00, 0x24 },
    { 0x00, 0x1E, 0x1E },
    { 0x12, 0x16, 0x0C }
  }
};

static const unsigned char shdisp_triple_led_emopattern_tbl[SHDISP_COL_VARI_KIND][3][SHDISP_TRI_LED_EMOPATTERN_COLOR][3] = {
  {
    {
        { 0x09, 0x00, 0x09 }
    },
    {
        { 0x18, 0x00, 0x18 }
    },
    {
        { 0x24, 0x00, 0x24 }
    }
  },
  {
    {
        { 0x09, 0x00, 0x09 }
    },
    {
        { 0x18, 0x00, 0x18 }
    },
    {
        { 0x24, 0x00, 0x24 }
    }
  },
  {
    {
        { 0x04, 0x00, 0x04 }
    },
    {
        { 0x0A, 0x00, 0x0A }
    },
    {
        { 0x0F, 0x00, 0x0F }
    }
  },
  {
    {
        { 0x09, 0x00, 0x09 }
    },
    {
        { 0x18, 0x00, 0x18 }
    },
    {
        { 0x24, 0x00, 0x24 }
    }
  }
};

static const unsigned char shdisp_triple_led_anime_tbl[SHDISP_COL_VARI_KIND][2][SHDISP_TRI_LED_COLOR_TBL_NUM][3] = {
  {
    {
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 }
    },
    {
        { 0x00, 0x00, 0x00 },
        { 0x50, 0x00, 0x00 },
        { 0x00, 0x64, 0x00 },
        { 0x3C, 0x3C, 0x00 },
        { 0x00, 0x00, 0x64 },
        { 0x3C, 0x00, 0x3C },
        { 0x00, 0x3C, 0x3C },
        { 0x1D, 0x27, 0x15 }
    }
  },
  {
    {
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 }
    },
    {
        { 0x00, 0x00, 0x00 },
        { 0x2D, 0x00, 0x00 },
        { 0x00, 0x1E, 0x00 },
        { 0x25, 0x25, 0x00 },
        { 0x00, 0x00, 0x41 },
        { 0x24, 0x00, 0x24 },
        { 0x00, 0x1E, 0x1E },
        { 0x12, 0x1C, 0x0C }
    }
  },
  {
    {
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 }
    },
    {
        { 0x00, 0x00, 0x00 },
        { 0x14, 0x00, 0x00 },
        { 0x00, 0x14, 0x00 },
        { 0x14, 0x14, 0x00 },
        { 0x00, 0x00, 0x50 },
        { 0x14, 0x00, 0x14 },
        { 0x00, 0x0F, 0x0F },
        { 0x0C, 0x12, 0x08 }
    }
  },
  {
    {
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00 }
    },
    {
        { 0x00, 0x00, 0x00 },
        { 0x32, 0x00, 0x00 },
        { 0x00, 0x1E, 0x00 },
        { 0x28, 0x28, 0x00 },
        { 0x00, 0x00, 0x46 },
        { 0x24, 0x00, 0x24 },
        { 0x00, 0x1E, 0x1E },
        { 0x12, 0x16, 0x0C }
    }
  }
};

static const struct shdisp_bdic_bkl_ado_tbl shdisp_bdic_bkl_ado_tbl[5] = {
    {   0,      4,   262,    -30},
    {   4,     38,   264,    -52},
    {  38,    365,   274,   -533},
    { 365,   8291,   109, 101301},
    {8291,  65536,   165,-494231},
};

/* ------------------------------------------------------------------------- */
/* TYPES                                                                     */
/* ------------------------------------------------------------------------- */



/* ------------------------------------------------------------------------- */
/* PROTOTYPES                                                                */
/* ------------------------------------------------------------------------- */



#endif /* SHDISP_BL71Y8_DATA_PA28_H */

/* ------------------------------------------------------------------------- */
/* END OF FILE                                                               */
/* ------------------------------------------------------------------------- */
