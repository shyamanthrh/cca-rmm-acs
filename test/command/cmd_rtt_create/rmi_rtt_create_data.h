/*
 * Copyright (c) 2023-2024, Arm Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "val_rmm.h"

enum test_intent {
    RD_UNALIGNED = 0X0,
    RD_DEV_MEM = 0X1,
    RD_OUTSIDE_OF_PERMITTED_PA = 0X2,
    RD_STATE_UNDELEGATED = 0X3,
    RD_STATE_DELEGATED = 0X4,
    RD_STATE_REC = 0X5,
    RD_STATE_RTT = 0X6,
    RD_STATE_DATA = 0X7,
    LEVEL_STARTING = 0X8,
    LEVEL_OOB = 0X9,
    IPA_UNALIGNED = 0XA,
    IPA_OOB = 0XB,
    RTT_UNALIGNED = 0XC,
    RTT_DEV_MEM = 0XD,
    RTT_OUTSIDE_PERMITTED_PA = 0XE,
    RTT_STATE_UNDELEGATED = 0XF,
    RTT_STATE_RD = 0X10,
    RTT_STATE_REC = 0X11,
    RTT_STATE_RTT = 0X12,
    RTT_STATE_DATA = 0X13,
    RTT_LPA2_PA = 0X14,
    LEVEL_NO_PARENT_RTTE = 0X15,
    RTTE_STATE_TABLE = 0X16
};

struct stimulus {
    char msg[100];
    uint64_t abi;
    enum test_intent label;
    uint64_t status;
    uint64_t index;
};

static struct stimulus test_data[] = {
    {.msg = "rd_align",
    .abi = RMI_RTT_CREATE,
    .label = RD_UNALIGNED,
    .status = RMI_ERROR_INPUT,
    .index = 0},
    {.msg = "rd_bound",
    .abi = RMI_RTT_CREATE,
    .label = RD_DEV_MEM,
    .status = RMI_ERROR_INPUT,
    .index = 0},
    {.msg = "rd_bound",
    .abi = RMI_RTT_CREATE,
    .label = RD_OUTSIDE_OF_PERMITTED_PA,
    .status = RMI_ERROR_INPUT,
    .index = 0},
    {.msg = "rd_state",
    .abi = RMI_RTT_CREATE,
    .label = RD_STATE_UNDELEGATED,
    .status = RMI_ERROR_INPUT,
    .index = 0},
    {.msg = "rd_state",
    .abi = RMI_RTT_CREATE,
    .label = RD_STATE_DELEGATED,
    .status = RMI_ERROR_INPUT,
    .index = 0},
    {.msg = "rd_state",
    .abi = RMI_RTT_CREATE,
    .label = RD_STATE_REC,
    .status = RMI_ERROR_INPUT,
    .index = 0},
    {.msg = "rd_state",
    .abi = RMI_RTT_CREATE,
    .label = RD_STATE_RTT,
    .status = RMI_ERROR_INPUT,
    .index = 0},
    {.msg = "rd_state",
    .abi = RMI_RTT_CREATE,
    .label = RD_STATE_DATA,
    .status = RMI_ERROR_INPUT,
    .index = 0},
    {.msg = "level_bound",
    .abi = RMI_RTT_CREATE,
    .label = LEVEL_STARTING,
    .status = RMI_ERROR_INPUT,
    .index = 0},
    {.msg = "level_bound",
    .abi = RMI_RTT_CREATE,
    .label = LEVEL_OOB,
    .status = RMI_ERROR_INPUT,
    .index = 0},
    {.msg = "ipa_align",
    .abi = RMI_RTT_CREATE,
    .label = IPA_UNALIGNED,
    .status = RMI_ERROR_INPUT,
    .index = 0},
    {.msg = "ipa_bound",
    .abi = RMI_RTT_CREATE,
    .label = IPA_OOB,
    .status = RMI_ERROR_INPUT,
    .index = 0},
    {.msg = "rtt_align",
    .abi = RMI_RTT_CREATE,
    .label = RTT_UNALIGNED,
    .status = RMI_ERROR_INPUT,
    .index = 0},
    {.msg = "rtt_bound",
    .abi = RMI_RTT_CREATE,
    .label = RTT_DEV_MEM,
    .status = RMI_ERROR_INPUT,
    .index = 0},
    {.msg = "rtt_bound",
    .abi = RMI_RTT_CREATE,
    .label = RTT_OUTSIDE_PERMITTED_PA,
    .status = RMI_ERROR_INPUT,
    .index = 0},
    {.msg = "rtt_state",
    .abi = RMI_RTT_CREATE,
    .label = RTT_STATE_UNDELEGATED,
    .status = RMI_ERROR_INPUT,
    .index = 0},
    {.msg = "rtt_state",
    .abi = RMI_RTT_CREATE,
    .label = RTT_STATE_RD,
    .status = RMI_ERROR_INPUT,
    .index = 0},
    {.msg = "rtt_state",
    .abi = RMI_RTT_CREATE,
    .label = RTT_STATE_REC,
    .status = RMI_ERROR_INPUT,
    .index = 0},
    {.msg = "rtt_state",
    .abi = RMI_RTT_CREATE,
    .label = RTT_STATE_RTT,
    .status = RMI_ERROR_INPUT,
    .index = 0},
    {.msg = "rtt_state",
    .abi = RMI_RTT_CREATE,
    .label = RTT_STATE_DATA,
    .status = RMI_ERROR_INPUT,
    .index = 0},
    {.msg = "rtt_bound2",
    .abi = RMI_RTT_CREATE,
    .label = RTT_LPA2_PA,
    .status = RMI_ERROR_INPUT,
    .index = 0},
    {.msg = "rtt_walk",
    .abi = RMI_RTT_CREATE,
    .label = LEVEL_NO_PARENT_RTTE,
    .status = RMI_ERROR_RTT,
    .index = 1},
    {.msg = "rtte_state",
    .abi = RMI_RTT_CREATE,
    .label = RTTE_STATE_TABLE,
    .status = RMI_ERROR_RTT,
    .index = 1}
};
