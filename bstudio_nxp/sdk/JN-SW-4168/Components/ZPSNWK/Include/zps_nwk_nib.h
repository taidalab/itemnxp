/*****************************************************************************
 *
 * MODULE:             ZPS NWK
 *
 * COMPONENT:          zps_nwk_nib.h
 *
 * AUTHOR:             RCC
 *
 * DESCRIPTION:        ZPS NWK Network Information Base header
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Zigbee%20Protocol%20Stack/Modules/NWK/Branches/ZBPRO_R20_v1.1/Include/zps_nwk_nib.h $
 *
 * $Revision: 81986 $
 *
 * $LastChangedBy: nxp29741 $
 *
 * $LastChangedDate: 2016-08-02 03:00:54 +0100 (Tue, 02 Aug 2016) $
 *
 * $Id: zps_nwk_nib.h 81986 2016-08-02 02:00:54Z nxp29741 $
 *
 *****************************************************************************
 *
 * This software is owned by Jennic and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on Jennic products. You, and any third parties must reproduce
 * the copyright and warranty notice and any other legend of ownership on each
 * copy or partial copy of the software.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". JENNIC MAKES NO WARRANTIES, WHETHER
 * EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE,
 * ACCURACY OR LACK OF NEGLIGENCE. JENNIC SHALL NOT, IN ANY CIRCUMSTANCES,
 * BE LIABLE FOR ANY DAMAGES, INCLUDING, BUT NOT LIMITED TO, SPECIAL,
 * INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON WHATSOEVER.
 *
 * Copyright Jennic Ltd. 2008 All rights reserved
 *
 ****************************************************************************/

/**
 * @defgroup g_zps_nwk_nib ZPS NWK Network Information Base
 *
 * Parameters associated with setting or getting NIB values.
 * NIB direct access allows getting and setting of NIB attributes directly by obtaining
 * the NIB handle and dereferencing it appropriately.
 * All NIB attributes can be read (got) in this manner
 * Most NIB attributes can be written (set) in this manner, however some NIB attributes
 * require an auxiliary function call to be called instead. This is because they also require
 * hardware register values to change as well.
 * The functions listed in this group indicate which NIB attributes need to be set in this manner
 * @ingroup g_zps_nwk
 */

#ifndef _zps_nwk_nib_h_
#define _zps_nwk_nib_h_

#ifdef __cplusplus
extern "C" {
#endif

/***********************/
/**** INCLUDE FILES ****/
/***********************/

#include "jendefs.h"
#include "zps_nwk_config.h"
#include "zps_nwk_sap.h"
#include "zps_nwk_slist.h"
#include "zps_tsv.h"

/************************/
/**** MACROS/DEFINES ****/
/************************/
/**
 * @name NWK constants
 * @ingroup g_zps_nwk_nib
 * All the network constants
 * @{
 */


#ifndef ZPS_NWK_INLINE
#define ZPS_NWK_INLINE  INLINE
#endif

// Trac #502 8ms Btt tick
/** Route request retry interval = 0xfe milliseconds = 0x20 8ms periods */
#define ZPS_NWK_CONST_RREQ_RETRY_INTERVAL              ((uint8)0x20)

#define ZPS_NWK_CONST_INIT_RREQ_RETRIES                ((uint8)3)
#define ZPS_NWK_CONST_RREQ_RETRIES                     ((uint8)2)

/**
 * @name NIB defaults, maxima and minima
 * @ingroup g_zps_nwk_nib
 * All the default values, minima and maxima for the ZPS NWK NIB
 * @{
 */

/** Max. routers minimum */
#define ZPS_NWK_NIB_MAX_ROUTERS_MIN                     ((uint8)0x01)
/** Max. routers default - depends on stack profile */
#define ZPS_NWK_NIB_MAX_ROUTERS_DEF                     ((uint8)0x05)
/** Max. routers maximum */
#define ZPS_NWK_NIB_MAX_ROUTERS_MAX                     ((uint8)0xff)

/** Max. children minimum */
#define ZPS_NWK_NIB_MAX_CHILDREN_MIN                    ((uint8)0x00)
/** Max. children default - depends on stack profile */
#define ZPS_NWK_NIB_MAX_CHILDREN_DEF                    ((uint8)0x07)
/** Max. children maximum */
#define ZPS_NWK_NIB_MAX_CHILDREN_MAX                    ((uint8)0xff)

/** Max. depth */
#define ZPS_NWK_NIB_MAX_DEPTH_MIN                       ((uint8)0x01)
/** Max. depth default - depends on stack profile */
#define ZPS_NWK_NIB_MAX_DEPTH_DEF                       ((uint8)ZPS_NWK_OPT_FS_MAX_DEPTH)
/** Max. depth maximum */
#define ZPS_NWK_NIB_MAX_DEPTH_MAX                       ((uint8)ZPS_NWK_NWKC_MAX_DEPTH)

/** Passive ack. timeout minimum (in half-seconds) */
#define ZPS_NWK_NIB_PASSIVE_ACK_TIMEOUT_MIN             ((uint8)1)
/** Passive ack. timeout default - depends on stack profile (in half-seconds) */
#define ZPS_NWK_NIB_PASSIVE_ACK_TIMEOUT_DEF             ((uint8)1)
/** Passive ack. timeout maximum (in half-seconds) */
#define ZPS_NWK_NIB_PASSIVE_ACK_TIMEOUT_MAX             ((uint8)20)

/** Max. broadcast retries minimum */
#define ZPS_NWK_NIB_MAX_BROADCAST_RETRIES_MIN           ((uint8)0)
/** Max. broadcast retries default */
#define ZPS_NWK_NIB_MAX_BROADCAST_RETRIES_DEF           ((uint8)2)
/** Max. broadcast retries maximum */
#define ZPS_NWK_NIB_MAX_BROADCAST_RETRIES_MAX           ((uint8)5)

/** Broadcast delivery time default - in half seconds */
#define ZPS_NWK_NIB_BROADCAST_DELIVERY_TIME_DEF         ((uint8)18)

/** Max. source route minimum */
#define ZPS_NWK_NIB_MAX_SOURCE_ROUTE_MIN                ((uint8)0x00)
/** Max. source route default */
#define ZPS_NWK_NIB_MAX_SOURCE_ROUTE_DEF                ((uint8)0x0c)
/** Max. source route maximum */
#define ZPS_NWK_NIB_MAX_SOURCE_ROUTE_MAX                ((uint8)0xff)

/** Unique address default - depends on feature set */
#ifdef ZPS_NWK_OPT_FS_ZIGBEE_FS
#define ZPS_NWK_NIB_UNIQUE_ADDR_DEF                     TRUE
#else
#define ZPS_NWK_NIB_UNIQUE_ADDR_DEF                     FALSE
#endif

/** Address alloc default - depends on feature set */
typedef enum
{
    ZPS_NWK_ADDR_ALC_DISTRIBUTED = 0,
    ZPS_NWK_ADDR_ALC_RESERVED = 1,
    ZPS_NWK_ADDR_ALC_STOCHASTIC = 2,
    ZPS_NWK_ADDR_ALC_VS_FIXED = 3    /* Vendor specific for testing */
} ZPS_teNwkAddrAlloc;

#ifdef ZPS_NWK_OPT_FS_ZIGBEE_FS
#define ZPS_NWK_NIB_ADDR_ALC_DEF                        ZPS_NWK_ADDR_ALC_DISTRIBUTED
#else
#define ZPS_NWK_NIB_ADDR_ALC_DEF                        ZPS_NWK_ADDR_ALC_STOCHASTIC
#endif

/** Tree routing default - depends on feature set */
#ifdef ZPS_NWK_OPT_FS_ZIGBEE_FS
#define ZPS_NWK_NIB_USE_TREE_ROUTING_DEF                TRUE
#else
#define ZPS_NWK_NIB_USE_TREE_ROUTING_DEF                FALSE
#endif

/** Symmetric link default - depends on feature set */
#ifdef ZPS_NWK_OPT_FS_ZIGBEE_FS
#define ZPS_NWK_NIB_SYM_LINK_DEF                        FALSE
#else
#define ZPS_NWK_NIB_SYM_LINK_DEF                        TRUE
#endif

/** Use multicast default */
#define ZPS_NWK_NIB_USE_MULTICAST_DEF                   FALSE

/** Link status period minimum */
#define ZPS_NWK_NIB_LINK_STATUS_PERIOD_MIN              ((uint8)0x00)
/** Link status period default */
#define ZPS_NWK_NIB_LINK_STATUS_PERIOD_DEF              ((uint8)0x0f)
/** Link status period maximum */
#define ZPS_NWK_NIB_LINK_STATUS_PERIOD_MAX              ((uint8)0xff)

/** Router age limit minimum */
#define ZPS_NWK_NIB_ROUTER_AGE_LIMIT_MIN                ((uint8)0x00)
/** Router age limit default */
#define ZPS_NWK_NIB_ROUTER_AGE_LIMIT_DEF                ((uint8)0x03)
/** Router age limit maximum */
#define ZPS_NWK_NIB_ROUTER_AGE_LIMIT_MAX                ((uint8)0xff)

/* Note: It is not clear from the specification how this is used */
/** Route discovery retries permitted minimum */
#define ZPS_NWK_NIB_ROUTE_DISC_RETRIES_PERMITTED_MIN    ((uint8)0x00)
/** Route discovery retries permitted default */
#define ZPS_NWK_NIB_ROUTE_DISC_RETRIES_PERMITTED_DEF    ((uint8)0x03)
/** Route discovery retries permitted maximum */
#define ZPS_NWK_NIB_ROUTE_DISC_RETRIES_PERMITTED_MAX    ((uint8)0x03)

/** TODO: Network formation ED threshold */
#define ZPS_NWK_NIB_VS_FORM_ED_THRESHOLD                100

/** TODO: Tx fail threshold */
#define ZPS_NWK_NIB_VS_TX_FAIL_THRESHOLD                5

/* Old route expiry time - 60 seconds */
#define ZPS_NWK_NIB_OLD_ROUTE_EXPIRY_TIME               600

#define ZPS_NWK_NIB_VS_MAX_OUTGOING_COST                4

/** Security level default - actually same for both feature sets */
#ifdef ZPS_NWK_OPT_FS_ZIGBEE_FS
#define ZPS_NWK_NIB_SECURITY_LEVEL_DEF                  5
#else
#define ZPS_NWK_NIB_SECURITY_LEVEL_DEF                  5
#endif

/* @} */

/** Security defines */
#define ZPS_NWK_KEY_LENGTH                              16

/* @} */

#ifndef BIT_W_1
#define BIT_W_1     0x1
#define BIT_W_2     0x3
#define BIT_W_3     0x7
#define BIT_W_4     0xF
#define BIT_W_5     0x1F
#define BIT_W_6     0x3F
#define BIT_W_7     0x7F
#define BIT_W_8     0xFF
#endif

/**** Mask operations ****/

#define ZPS_NWK_NT_TST(x, m)               ((x) & (m))
#define ZPS_NWK_NT_SET(x, m)               ((x) |= (m))
#define ZPS_NWK_NT_CLR(x, m)               ((x) &= ~(m))
#define ZPS_NWK_NT_MOD(x, m, y)            ((x) = (((x) & ~(m)) | (y)))

/**** Superframe specification ****/

/* Bits 0-3 - Beacon order - not interested */
/* Bits 4-7 - Superframe order - not interested */
/* Bits 8-11 - Final CAP slot - not interested */
/* Bit 12 - Battery life extension - not interested */
/* Bit 13 - Reserved - not interested */
/* Bit 14 - PAN Coordinator: Corresponds to ZigBee Coordinator in NT */
/* Bit 15 - Association permit: Corresponds to Join permit in NT */

#if 0

/* Bitfields */

#define ZPS_NWK_DISC_NT_SS_PAN_COORD_BIT                14
#define ZPS_NWK_DISC_NT_SS_PAN_COORD_MASK               ((uint16)(BIT_W_1 << ZPS_NWK_NT_SS_PAN_COORD_BIT))
#define ZPS_NWK_DISC_NT_GET_SS_PAN_COORD(x)             (((x) & ZPS_NWK_NT_SS_PAN_COORD_MASK) >> ZPS_NWK_NT_SS_PAN_COORD_BIT)
#define ZPS_NWK_DISC_NT_MOD_SS_PAN_COORD(x, d)          ZPS_NWK_NT_MOD(x, ZPS_NWK_NT_SS_PAN_COORD_MASK, ((d) << ZPS_NWK_NT_SS_PAN_COORD_BIT))
#define ZPS_NWK_DISC_NT_TST_SS_PAN_COORD(x)             ZPS_NWK_NT_TST(x, ZPS_NWK_NT_SS_PAN_COORD_MASK)
#define ZPS_NWK_DISC_NT_SET_SS_PAN_COORD(x)             ZPS_NWK_NT_SET(x, ZPS_NWK_NT_SS_PAN_COORD_MASK)
#define ZPS_NWK_DISC_NT_CLR_SS_PAN_COORD(x)             ZPS_NWK_NT_CLR(x, ZPS_NWK_NT_SS_PAN_COORD_MASK)


#define ZPS_NWK_DISC_NT_SS_ASSOC_PERMIT_BIT             15
#define ZPS_NWK_DISC_NT_SS_ASSOC_PERMIT_MASK            ((uint16)(BIT_W_1 << ZPS_NWK_NT_SS_ASSOC_PERMIT_BIT))
#define ZPS_NWK_DISC_NT_GET_SS_ASSOC_PERMIT(x)          (((x) & ZPS_NWK_NT_SS_ASSOC_PERMIT_MASK) >> ZPS_NWK_NT_SS_ASSOC_PERMIT_BIT)
#define ZPS_NWK_DISC_NT_MOD_SS_ASSOC_PERMIT(x, d)       ZPS_NWK_NT_MOD(x, ZPS_NWK_NT_SS_ASSOC_PERMIT_MASK, ((d) << ZPS_NWK_NT_SS_ASSOC_PERMIT_BIT))
#define ZPS_NWK_DISC_NT_TST_SS_ASSOC_PERMIT(x)          ZPS_NWK_NT_TST(x, ZPS_NWK_NT_SS_ASSOC_PERMIT_MASK)
#define ZPS_NWK_DISC_NT_SET_SS_ASSOC_PERMIT(x)          ZPS_NWK_NT_SET(x, ZPS_NWK_NT_SS_ASSOC_PERMIT_MASK)
#define ZPS_NWK_DISC_NT_CLR_SS_ASSOC_PERMIT(x)          ZPS_NWK_NT_CLR(x, ZPS_NWK_NT_SS_ASSOC_PERMIT_MASK)

#endif

/* Capability fields */

#define ZPS_NWK_CAP_DEVICE_TYPE_BIT             1
#define ZPS_NWK_CAP_DEVICE_TYPE_MASK            ((uint8)(BIT_W_1 << ZPS_NWK_CAP_DEVICE_TYPE_BIT))
#define ZPS_NWK_CAP_DEVICE_TYPE(x)              (((x) & ZPS_NWK_CAP_DEVICE_TYPE_MASK) >> ZPS_NWK_CAP_DEVICE_TYPE_BIT)
#define ZPS_NWK_CAP_MOD_DEVICE_TYPE(x, d)       ZPS_NWK_NT_MOD(x, ZPS_NWK_CAP_DEVICE_TYPE_MASK, ((d) << ZPS_NWK_CAP_DEVICE_TYPE_BIT))
#define ZPS_NWK_CAP_TST_DEVICE_TYPE(x)          ZPS_NWK_NT_TST(x, ZPS_NWK_CAP_DEVICE_TYPE_MASK)
#define ZPS_NWK_CAP_SET_DEVICE_TYPE(x)          ZPS_NWK_NT_SET(x, ZPS_NWK_CAP_DEVICE_TYPE_MASK)
#define ZPS_NWK_CAP_CLR_DEVICE_TYPE(x)          ZPS_NWK_NT_CLR(x, ZPS_NWK_CAP_DEVICE_TYPE_MASK)

#define ZPS_NWK_CAP_PWR_SRC_BIT                 2
#define ZPS_NWK_CAP_PWR_SRC_MASK                ((uint8)(BIT_W_1 << ZPS_NWK_CAP_PWR_SRC_BIT))
#define ZPS_NWK_CAP_PWR_SRC(x)                  (((x) & ZPS_NWK_CAP_PWR_SRC_MASK) >> ZPS_NWK_CAP_PWR_SRC_BIT)
#define ZPS_NWK_CAP_MOD_PWR_SRC(x, d)           ZPS_NWK_NT_MOD(x, ZPS_NWK_CAP_PWR_SRC_MASK, ((d) << ZPS_NWK_CAP_PWR_SRC_BIT))
#define ZPS_NWK_CAP_TST_PWR_SRC(x)              ZPS_NWK_NT_TST(x, ZPS_NWK_CAP_PWR_SRC_MASK)
#define ZPS_NWK_CAP_SET_PWR_SRC(x)              ZPS_NWK_NT_SET(x, ZPS_NWK_CAP_PWR_SRC_MASK)
#define ZPS_NWK_CAP_CLR_PWR_SRC(x)              ZPS_NWK_NT_CLR(x, ZPS_NWK_CAP_PWR_SRC_MASK)

#define ZPS_NWK_CAP_RX_ON_WHEN_IDLE_BIT         3
#define ZPS_NWK_CAP_RX_ON_WHEN_IDLE_MASK        ((uint8)(BIT_W_1 << ZPS_NWK_CAP_RX_ON_WHEN_IDLE_BIT))
#define ZPS_NWK_CAP_RX_ON_WHEN_IDLE(x)          (((x) & ZPS_NWK_CAP_RX_ON_WHEN_IDLE_MASK) >> ZPS_NWK_CAP_RX_ON_WHEN_IDLE_BIT)
#define ZPS_NWK_CAP_MOD_RX_ON_WHEN_IDLE(x, d)   ZPS_NWK_NT_MOD(x, ZPS_NWK_CAP_RX_ON_WHEN_IDLE_MASK, ((d) << ZPS_NWK_CAP_RX_ON_WHEN_IDLE_BIT))
#define ZPS_NWK_CAP_TST_RX_ON_WHEN_IDLE(x)      ZPS_NWK_NT_TST(x, ZPS_NWK_CAP_RX_ON_WHEN_IDLE_MASK)
#define ZPS_NWK_CAP_SET_RX_ON_WHEN_IDLE(x)      ZPS_NWK_NT_SET(x, ZPS_NWK_CAP_RX_ON_WHEN_IDLE_MASK)
#define ZPS_NWK_CAP_CLR_RX_ON_WHEN_IDLE(x)      ZPS_NWK_NT_CLR(x, ZPS_NWK_CAP_RX_ON_WHEN_IDLE_MASK)

#define ZPS_NWK_CAP_SECURITY_MODE_BIT           6
#define ZPS_NWK_CAP_SECURITY_MODE_MASK          ((uint8)(BIT_W_1 << ZPS_NWK_CAP_SECURITY_MODE_BIT))
#define ZPS_NWK_CAP_SECURITY_MODE(x)            (((x) & ZPS_NWK_CAP_SECURITY_MODE_MASK) >> ZPS_NWK_CAP_SECURITY_MODE_BIT)
#define ZPS_NWK_CAP_MOD_SECURITY_MODE(x, d)     ZPS_NWK_NT_MOD(x, ZPS_NWK_CAP_SECURITY_MODE_MASK, ((d) << ZPS_NWK_CAP_SECURITY_MODE_BIT))
#define ZPS_NWK_CAP_TST_SECURITY_MODE(x)        ZPS_NWK_NT_TST(x, ZPS_NWK_CAP_SECURITY_MODE_MASK)
#define ZPS_NWK_CAP_SET_SECURITY_MODE(x)        ZPS_NWK_NT_SET(x, ZPS_NWK_CAP_SECURITY_MODE_MASK)
#define ZPS_NWK_CAP_CLR_SECURITY_MODE(x)        ZPS_NWK_NT_CLR(x, ZPS_NWK_CAP_SECURITY_MODE_MASK)

#define ZPS_NWK_CAP_ALLOC_ADDR_BIT              7
#define ZPS_NWK_CAP_ALLOC_ADDR_MASK             ((uint8)(BIT_W_1 << ZPS_NWK_CAP_ALLOC_ADDR_BIT))
#define ZPS_NWK_CAP_ALLOC_ADDR(x)               (((x) & ZPS_NWK_CAP_ALLOC_ADDR_MASK) >> ZPS_NWK_CAP_ALLOC_ADDR_BIT)
#define ZPS_NWK_CAP_MOD_ALLOC_ADDR(x, d)        ZPS_NWK_NT_MOD(x, ZPS_NWK_CAP_ALLOC_ADDR_MASK, ((d) << ZPS_NWK_CAP_ALLOC_ADDR_BIT))
#define ZPS_NWK_CAP_TST_ALLOC_ADDR(x)           ZPS_NWK_NT_TST(x, ZPS_NWK_CAP_ALLOC_ADDR_MASK)
#define ZPS_NWK_CAP_SET_ALLOC_ADDR(x)           ZPS_NWK_NT_SET(x, ZPS_NWK_CAP_ALLOC_ADDR_MASK)
#define ZPS_NWK_CAP_CLR_ALLOC_ADDR(x)           ZPS_NWK_NT_CLR(x, ZPS_NWK_CAP_ALLOC_ADDR_MASK)


#define ZPS_NWK_CAP_BUILD(x)                    (((x).u1DeviceType << ZPS_NWK_CAP_DEVICE_TYPE_BIT) | \
                                                 ((x).u1PowerSource << ZPS_NWK_CAP_PWR_SRC_BIT) | \
                                                 ((x).u1RxOnWhenIdle << ZPS_NWK_CAP_RX_ON_WHEN_IDLE_BIT) | \
                                                 ((x).u1SecurityMode << ZPS_NWK_CAP_SECURITY_MODE_BIT))

/*
 * Any bits overlaid must be 0
 * 01001110
 * ||||||||
 * |||||||+- Alternate PAN coordinator: overlaid with Used
 * ||||||+-- Device type
 * |||||+--- Power source
 * ||||+---- Rx on when idle
 * ||++----- Reserved: Overlaid with relationship
 * |+------- Security capability (= mode)
 * +-------- Allocate address: Overlaid with authenticated
 */
#define ZPS_NWK_CAP_FIELD_MASK                  0x4e

/*
 * Any bits overlaid must be 0
 * 00110011
 * ||||||||
 * |||||||+- Used
 * ||||||+-- Device type
 * |||||+--- Power source
 * ||||+---- Rx on when idle
 * ||++----- Relationship
 * |+------- Security capability (= mode)
 * +-------- Authenticated
 */

#define ZPS_NWK_NT_ACTV_USED_RELATIONSHIP_MASK 0x33
#define ZPS_NWK_NT_ACTV_USED_RELATIONSHIP_CHILD 0x11

/* Enumerations */
#define ZPS_NWK_NT_AP_RELATIONSHIP_PARENT          (0)
#define ZPS_NWK_NT_AP_RELATIONSHIP_CHILD           (1)
#define ZPS_NWK_NT_AP_RELATIONSHIP_SIBLING         (2)
#define ZPS_NWK_NT_AP_RELATIONSHIP_UNKNOWN         (3)

/* Device type */
#define ZPS_NWK_NT_AP_DEVICE_TYPE_ZED              (0)
#define ZPS_NWK_NT_AP_DEVICE_TYPE_ZR_ZC            (1)

/* Power source */
#define ZPS_NWK_NT_AP_PWR_SRC_BATT                 (0)
#define ZPS_NWK_NT_AP_PWR_SRC_MAINS                (1)

/*
 * Initial parent bitmap
 * 00001111
 * ||||||||
 * |||||||+- Used: True
 * ||||||+-- Device type: ZC/ZR
 * |||||+--- Power source: Mains (TODO)
 * ||||+---- Rx on when idle: True (TODO?)
 * ||++----- Device type: Parent (0x00)
 * |+------- Security capability (= mode): 0 (don't know yet)
 * +-------- Authenticated: 0 (don't know yet)
 */
#define ZPS_NWK_NT_AP_INITIAL_PARENT              0x0f

/*
 * Initial sibling bitmap
 * 00101111
 * ||||||||
 * |||||||+- Used: True
 * ||||||+-- Device type: ZC/ZR
 * |||||+--- Power source: Mains (TODO)
 * ||||+---- Rx on when idle: True (TODO?)
 * ||++----- Device type: Sibling (0x02)
 * |+------- Security capability (= mode): 0 (don't know yet)
 * +-------- Authenticated: 0 (don't know yet)
 */
#define ZPS_NWK_NT_AP_INITIAL_SIBLING             0x2f

/**
 * Active neighbour table search masks
 */
#define ZPS_NWK_NT_ACTV_MATCH_NWK_ADDR 0x01 /**< Match network address */
#define ZPS_NWK_NT_ACTV_MATCH_EXT_ADDR 0x02 /**< Match extended address */
#define ZPS_NWK_NT_ACTV_MATCH_CHILD    0x04 /**< Match child */
#define ZPS_NWK_NT_ACTV_MATCH_ZED      0x08 /**< Match end device */

#define ZPS_NWK_NT_ACTV_MATCH_EXT_ADDR_CHILD     (ZPS_NWK_NT_ACTV_MATCH_EXT_ADDR | ZPS_NWK_NT_ACTV_MATCH_CHILD)
#define ZPS_NWK_NT_ACTV_MATCH_NWK_ADDR_CHILD     (ZPS_NWK_NT_ACTV_MATCH_NWK_ADDR | ZPS_NWK_NT_ACTV_MATCH_CHILD)
#define ZPS_NWK_NT_ACTV_MATCH_NWK_ADDR_ZED_CHILD (ZPS_NWK_NT_ACTV_MATCH_NWK_ADDR | ZPS_NWK_NT_ACTV_MATCH_CHILD | ZPS_NWK_NT_ACTV_MATCH_ZED)

/**************************/
/**** TYPE DEFINITIONS ****/
/**************************/

/**
 * ZPS NWK Routing Table entry status
 * The status of a Routing Table entry
 * @ingroup g_zps_nwk_nib
 */
typedef enum
{
    ZPS_NWK_RT_ACTIVE = 0,
    ZPS_NWK_RT_DISC_UNDERWAY = 1,
    ZPS_NWK_RT_DISC_FAILED = 2,
    ZPS_NWK_RT_INACTIVE = 3,
    ZPS_NWK_RT_VALDN_UNDERWAY = 4
} ZPS_teNwkRtStatus;

/**
 * ZPS NWK Broadcast Transaction Table entry state
 * The state a Broadcast Transaction Table entry can be in
 * @ingroup g_zps_nwk_nib
 */
typedef enum
{
    ZPS_NWK_BTR_INACTIVE,
    ZPS_NWK_BTR_JITTER_PASSIVE_ACK,         /**< Timing with passive ack for standard broadcast - jitter phase */
    ZPS_NWK_BTR_JITTER_PASSIVE_ACK_RECD,    /**< Timing with passive ack for standard broadcast - jitter phase, passive ack recd. */
    ZPS_NWK_BTR_PASSIVE_ACK,                /**< Timing with passive ack for standard broadcast */
    ZPS_NWK_BTR_NO_PASSIVE_ACK,             /**< Timing with no passive ack for member mode multicast */
    ZPS_NWK_BTR_RREQ_RETRY_INTERVAL,        /**< Timing route request retry interval */
    ZPS_NWK_BTR_BCAST_DELIVERY_TIME,        /**< Timing broadcast delivery time for standard broadcast */
} ZPS_teNwkBtrState;

/**
 * ZPS NWK Discovery Neighbor table entry
 * The neighbor table for devices within radio range during a discovery
 * @ingroup g_zps_nwk_nib
 * @note Only fields which can be gleaned from the PAN Descriptor and beacon payload
 * need to be considered here.
 */
typedef struct
{
    uint64 u64ExtPanId;         /**< Extended PAN ID */
    uint16 u16PanId;            /**< PAN ID */
    uint16 u16NwkAddr;          /**< Network address */
    uint8  u8LinkQuality;       /**< Link quality */
    uint8  u8LogicalChan;       /**< Logical channel */
    uint8  u8NwkUpdateId;       /**< Update ID */
    /*
     * Bitfields are used for syntactic neatness and space saving. May need to assess whether
     * these are suitable for embedded environment
     */
    union
    {
        struct
        {
            unsigned u1PanCoord:1;
            unsigned u1JoinPermit:1;
            unsigned u1ZrCapacity:1;
            unsigned u4Depth:4;
            unsigned u1ZedCapacity:1;
            unsigned u4StackProfile:4;      /**< Stack profile */
            unsigned u1PotentialParent:1;
            unsigned u1Used:1;
        } bfBitfields;
        uint8 au8Field[2];
    } uAncAttrs;
} ZPS_tsNwkDiscNtEntry;

/**
 * ZPS NWK Neighbor table entry
 * The neighbor table for devices within radio range. This is when the device is
 * active and will, for a tree, indicate one parent and all children. For a mesh,
 * may also include siblings
 * @ingroup g_zps_nwk_nib
 * @note
 * Only need one bit for u1DeviceType to show if it is a router or end device.
 * A ZC will be shown as router but always have u16NwkAddr as 0x0000.
 */
typedef struct
{
    zps_tsNwkSlistNode sNode;  /**< Single linked list node */
    uint16 u16Lookup;         /**< Extended address */
    uint16 u16NwkAddr;         /**< Network address */
    uint8  u8TxFailed;         /**< Transmit failed count */
    uint8  u8LinkQuality;      /**< Link Quality indication */
    /*
     * Bitfields are used for syntactic neatness and space saving. May need to assess whether
     * these are suitable for embedded environment
     */
    union
    {
        struct
        {
            unsigned u1Used:1;           /* Overlays: Alternate PAN coordinator */
            unsigned u1DeviceType:1;
            unsigned u1PowerSource:1;
            unsigned u1RxOnWhenIdle:1;
            unsigned u2Relationship:2;   /* Overlays: Reserved */
            unsigned u1SecurityMode:1;
            unsigned u1Authenticated:1;  /* Overlays: Allocate address */
            unsigned u1LinkStatusDone:1; /**< Link status has been processed for this device */
            unsigned u3OutgoingCost:3;     /**< Outgoing cost for sym link = true */
            unsigned u3Age:3;              /**< Router age (in link status periods) */
            unsigned u1ExpectAnnc:1;       /*** Set for newly joined children, cleared on hearing their annce **/
        } bfBitfields;
        uint8 au8Field[2];
    }  uAncAttrs;
} ZPS_tsNwkActvNtEntry;

#define ZPS_NWK_NT_ACTV_PARENT              0 /**< Entry 0 is the parent */
#define ZPS_NWK_NT_ACTV_FIRST_NON_PARENT    ZPS_NWK_NT_ACTV_PARENT+1 /**< Entry 0 is the parent */

/**
 * ZPS NWK NIB Initial values
 * This overlays the top of the NIB, making it easier to initialise the NIB in one go
 * @note Any changes to the NIB order MUST be reflected here
 * A union/substructure was not use for clarity in the NIB itself
 */
typedef struct
{
    uint32 u32VsOldRouteExpiryTime;                         /**< Vendor specific - Period of old route garbage collection */
    uint8  u8MaxRouters;                                    /**< nwkMaxRouters */
    uint8  u8MaxChildren;                                   /**< nwkMaxChildren */
    uint8  u8MaxDepth;                                      /**< nwkMaxDepth */
    uint8  u8PassiveAckTimeout;                             /**< nwkPassiveAckTimeout (in half-seconds) */ /* Potential const */
    uint8  u8MaxBroadcastRetries;                           /**< nwkMaxBroadcastRetries */ /* Potential const */
    uint8  u8MaxSourceRoute;                                /**< nwkMaxSourceRoute */
    uint8  u8NetworkBroadcastDeliveryTime;                  /**< nwkNetworkBroadcastDeliveryTime */ /* Potential const */
    uint8  u8UniqueAddr;                                    /**< nwkUniqueAddr */
    uint8  u8AddrAlloc;                                     /**< nwkAddrAlloc */
    uint8  u8UseTreeRouting;                                /**< nwkUseTreeRouting: bool */
    uint8  u8SymLink;                                       /**< nwkSymLink: bool */
    uint8  u8UseMulticast;                                  /**< nwkUseMulticast: bool */
    uint8  u8LinkStatusPeriod;                              /**< nwkLinkStatusPeriod */
    uint8  u8RouterAgeLimit;                                /**< nwkRouterAgeLimit */
    uint8  u8RouteDiscoveryRetriesPermitted;                /**< nwkRouteDiscoveryRetriesPermitted */
    uint8  u8VsFormEdThreshold;                             /**< Vendor specific - energy detect threshold for network forming */
    uint8  u8SecurityLevel;                                 /**< nwkSecurityLevel */ /* Potential const */
    uint8  u8AllFresh;                                      /**< nwkAllFresh */ /* Potential const */
    uint8  u8SecureAllFrames;                               /**< nwkSecureAllFrames */ /* Potential const */
    uint8  u8VsTxFailThreshold;                             /**< Vendor specific - transmit fail threshold when RT next hop gets cleared */
    uint8  u8VsMaxOutgoingCost;                             /**< Vendor specific - only uses links with cost >= than this */
    uint8  u8VsLeaveRejoin;
} ZPS_tsNwkNibInitialValues;

/**
 * ZPS NWK Route discovery table entry
 * The route discovery table for mesh routing devices.
 * @ingroup g_zps_nwk
 * @note
 */
typedef struct
{
    ZPS_tsTsvTimer sTimer;   /**< Route discovery timer */
    uint16 u16NwkSrcAddr;    /**< Network address of RREQ's initiator */
    uint16 u16NwkSenderAddr; /**< Network address of RREQ's corresponding to u8RreqId neighbour relayer with best link cost */
    uint16 u16RtEntryId;       /**< Associated Routing Table entry ID (its index) */
    uint8 u8RouteReqId;      /**< RREQ ID */
    uint8 u8ForwardCost;     /**< Accumulated path cost from RREQ src to this node */
    uint8 u8ResidualCost;    /**< Accumulated path cost this node to RREQ dst (symmetrical routing?) */
} ZPS_tsNwkRtDiscEntry;

/**
 * ZPS NWK Route table entry
 * The routing table for mesh routing devices.
 * @ingroup g_zps_nwk_nib
 * @note
 */
typedef struct
{
    uint16 u16NwkDstAddr;     /**< Destination Network address */
    uint16 u16NwkNxtHopAddr;  /**< Next hop Network address */
    uint8  u8ExpiryCount;
    /*
     * Bitfields are used for syntactic neatness and space saving. May need to assess whether
     * these are suitable for embedded environment
     */
    union
    {
        struct
        {
            unsigned u3Status:3;          /**< Status of route */
            unsigned u1NoRouteCache:1;    /**< Destination address is unable to store source routes */
            unsigned u1ManyToOne:1;       /**< Destination address is concentrator that issued a many-to-one route request */
            unsigned u1RouteRecordReqd:1; /**< Route record is required */
            unsigned u1GroupIdFlag:1;     /**< Indicates u16DstAddr is a group ID */
            unsigned u1RecentlyUsed:1;    /**< Indicates route has recently been used */
        } bfBitfields;
        uint8 au8Field[1];
    } uAncAttrs;
} ZPS_tsNwkRtEntry;

/**
 * ZPS NWK Broadcast transaction record
 * The broadcast transaction record (BTR)
 * @ingroup g_zps_nwk_nib
 * @note
 * As we had to go into a second word, fill it up with info
 */
typedef struct
{
    uint16 u16NwkSrcAddr;     /**< Source Network address */
    uint8  u8SeqNum;          /**< Sequence number */
    uint8  u8ExpiryTime;      /**< Expiration time */
    uint8  u8State;           /**< State (use a uint8 to save space) */
    uint8  u8ExpiryPeriods;   /**< Used for retries and longer timings */
} ZPS_tsNwkBtr;

/**
 * ZPS NWK Route record table entry
 * A route record entry in the Route Record table
 * @ingroup g_zps_nwk_nib
 * @note
 */
typedef struct
{
    uint16 u16NwkDstAddr;                           /**< Destination address */
    uint8  u8RelayCount;                            /**< Relay count */
    uint16 au16Path[30];                            /**< The total number of hops is 11 because the tunnel command can only fit
                                                         that many hops */
} ZPS_tsNwkRctEntry;

/*****************************************************************************/
/* SECURITY ATTRIBUTES */
/*****************************************************************************/


/**
 * ZPS NWK Security Material Set
 * @ingroup g_zps_nwk_nib
 * @note
 */
typedef struct
{
	uint8               au8Key[ZPS_NWK_KEY_LENGTH] __attribute__ ((aligned (16)));         /**< The Key */
	uint8               u8KeySeqNum;                        /**< Key Sequence Number */
    uint8               u8KeyType;                          /**< Key Type */

} ZPS_tsNwkSecMaterialSet;

/**
 * ZPS NWK Initial Table sizes
 * Used for passing as a parameter on initialisation
 * @ingroup g_zps_nwk_nib
 */
typedef struct
{
    uint16 u16NtActv;     /**< nwkNeighborTable (active) size */
    uint16 u16Rt;         /**< nwkRouteTable size */
    uint16 u16Rct;        /**< nwkRouteRecordTable size */
    uint16 u16AddrMap;    /**< nwkAddressMap size */
    uint8 u8NtDisc;     /**< nwkNeighborTable (discovery) size */
    uint8 u8RtDisc;     /**< Route discovery table (not strictly NIB) */
    uint8 u8Btt;        /**< nwkBroadcastTransactionTable size */
    uint8 u8SecMatSet;  /**< nwkSecurityMaterialSet size */
    uint8 u8NibDefault; /** size of the nib default struct **/
    uint8 u8ChildTable;
    uint16 u16MacAddTableSize;
} ZPS_tsNwkNibTblSize;


/**
 * ZPS NWK Initial Table locations
 * Used for passing as a parameter on initialisation
 * @ingroup g_zps_nwk_nib
 */
typedef struct
{
    ZPS_tsNwkDiscNtEntry *psNtDisc;                                      /**< nwkNeighborTable - discovery */
    ZPS_tsNwkActvNtEntry *psNtActv;                                      /**< nwkNeighborTable - active */
    ZPS_tsNwkRtDiscEntry *psRtDisc;                                      /**< Route discovery table (not strictly NIB) */
    ZPS_tsNwkRtEntry *psRt;                                              /**< nwkRouteTable */
    ZPS_tsNwkBtr *psBtt;                                                 /**< nwkBroadcastTransactionTable */
    /* Group ID */                                                       /**< nwkGroupIDTable */
    ZPS_tsNwkRctEntry *psRct;                                            /**< nwkRouteRecordTable */
    ZPS_tsNwkSecMaterialSet *psSecMatSet;                                /**< nwkSecurityMaterialSet */     /* [I SP001379_sr 67] */
    ZPS_tsNwkNibInitialValues* psNibDefault;                             /** struct holding Nib defaults (NOT a table) **/
    uint16 *pu16AddrMapNwk;                                              /**< nwkAddressMap - network addresses */
    uint16 *pu16AddrLookup;                                              /**< lookup index in the MAC table */
    uint32              *pu32InFCSet;                                    /**< Incoming Frame Counter Set  */
    uint32              u32OutFC; 							             /** < Vendor specific - single NWK outgoing frame counter for all security sets */
    uint64 *pu64AddrExtAddrMap;                                          /**< nwkAddressMap - extended addresses */
} ZPS_tsNwkNibTbl;

/**
 * ZPS NWK NIB Persisted Data
 * This includes members of the NIB which must persist through reset etc.
 * @note This does not include any tables e.g neighbour table, which are persisted separately
 */
typedef struct
{
    uint8  u8UpdateId;                                      /**< nwkUpdateId */
    uint8  u8ActiveKeySeqNumber;                            /**< nwkActiveKeySeqNumber */                    /* [I SP001379_sr 67] */
    uint8  u8VsDepth;                                       /**< Vendor specific - Depth this node is at */
    uint8  u8CapabilityInformation;                         /**< nwkCapabilityInformation */
    uint8  u8VsChannel;                                     /**< Vendor specific - Channel: In Phy also */
    uint16 u16VsPanId;                                      /**< Vendor specific - nwkPANId: In MAC PIB */
    uint16 u16NwkAddr;                                      /**< nwkNetworkAddress: In MAC PIB */
    uint16 u16VsParentAddr;                                 /**< Vendor specific - Parent network address: also in PIB */
    uint64 u64ExtPanId;                                     /**< nwkExtendedPANID */
    //uint16 u16VsAddrLow;
    //uint16 u16VsAddrHigh;
} ZPS_tsNWkNibPersist;

/**
 * ZPS NWK NIB
 * The NIB itself
 * @ingroup g_zps_nwk_nib
 * @note: TODO Would be an idea to sort out based on size etc. like MAC
 * @note: Some are potential constants given ZigBee and ZigBee PRO feature sets but
 * are still included here for flexibility:
 * nwkPassiveAckTimeout = 0.5s (ZigBee and PRO)
 * nwkBroadcastRetries = 2 (ZigBee and PRO)
 * nwkBroadcastDeliveryTime = 9 (ZigBee and PRO)
 * nwkAllFresh = TRUE
 * nwkSecureAllFrames = TRUE
 * nwkSecurityLevel = 5
 * @note: Some are constants given ZigBee and ZigBee PRO feature sets and will not be included:
 * nwkTimeStamp = FALSE
 * @note: Some are in the MAC PIB and will be accessed through the MAC PIB:
 * nwkTransactionPersistenceTime = macTransactionPersistenceTime
 * nwkShortAddress = macShortAddress
 * nwkPanId = macPANId
 */
typedef struct
{
    /**** Initial values described in struct above start here ****/
    uint32 u32VsOldRouteExpiryTime;                         /**< Vendor specific - Period of old route garbage collection */
    uint8  u8MaxRouters;                                    /**< nwkMaxRouters */
    uint8  u8MaxChildren;                                   /**< nwkMaxChildren */
    uint8  u8MaxDepth;                                      /**< nwkMaxDepth */
    uint8  u8PassiveAckTimeout;                             /**< nwkPassiveAckTimeout (in half-seconds) */ /* Potential const */
    uint8  u8MaxBroadcastRetries;                           /**< nwkMaxBroadcastRetries */ /* Potential const */
    uint8  u8MaxSourceRoute;                                /**< nwkMaxSourceRoute */
    uint8  u8NetworkBroadcastDeliveryTime;                  /**< nwkNetworkBroadcastDeliveryTime */ /* Potential const */
    uint8  u8UniqueAddr;                                    /**< nwkUniqueAddr */
    uint8  u8AddrAlloc;                                     /**< nwkAddrAlloc */
    uint8  u8UseTreeRouting;                                /**< nwkUseTreeRouting: bool */
    uint8  u8SymLink;                                       /**< nwkSymLink: bool */
    uint8  u8UseMulticast;                                  /**< nwkUseMulticast: bool */
    uint8  u8LinkStatusPeriod;                              /**< nwkLinkStatusPeriod */
    uint8  u8RouterAgeLimit;                                /**< nwkRouterAgeLimit */
    uint8  u8RouteDiscoveryRetriesPermitted;                /**< nwkRouteDiscoveryRetriesPermitted */
    uint8  u8VsFormEdThreshold;                             /**< Vendor specific - energy detect threshold for network forming */
    uint8  u8SecurityLevel;                                 /**< nwkSecurityLevel */ /* Potential const */   /* [I SP001379_sr 67] */
    uint8  u8AllFresh;                                      /**< nwkAllFresh */ /* Potential const */        /* [I SP001379_sr 67] */
    uint8  u8SecureAllFrames;                               /**< nwkSecureAllFrames */ /* Potential const */ /* [I SP001379_sr 67] */
    uint8  u8VsTxFailThreshold;                             /**< Vendor specific - transmit fail threshold when RT nxt hop gets cleared */
    uint8  u8VsMaxOutgoingCost;                             /**< Vendor specific - only uses links with cost >= than this */
    uint8  u8VsLeaveRejoin;
    /**** Initial values described in struct above end here ****/
    uint8  u8ReportConstantCost;                            /**< nwkReportConstantCost */ /* Potential const */
    uint8  u8IsConcentrator;                                /**< nwkIsConcentrator: bool */
    uint8  u8ConcentratorRadius;                            /**< nwkConcentratorRadius */
    uint8  u8ConcentratorDiscoveryTime;                     /**< nwkConcentratorDiscoveryTime */
    uint8  u8SequenceNumber;                                /**< nwkSequenceNumber */
    uint16 u16ManagerAddr;                                  /**< nwkManagerAddr */
    uint16 u16TxTotal;                                      /**< nwkTxTotal */
    uint16 u16VsFixedAlcAddr;                               /**< Vendor specific - fixed allocated address */
    uint64 u64VsLastPanIdConflict;                          /**< Vendor specific - EPID of other network in last Pan Id conflict detection */

    /**** Tables ****/
    zps_tsNwkSlist       sActvSortedList;                   /**< Linked list of sorted NT entries */
    ZPS_tsNwkNibTblSize  sTblSize;                          /**< Table sizes */
    ZPS_tsNwkNibTbl      sTbl;                              /**< Tables */
    ZPS_tsNWkNibPersist  sPersist;                          /**< Members of NIB which require persisting */

    /* The network address map is done like this as an entry containing a uint16 and uint64 is very inefficient */
} ZPS_tsNwkNib;

/****************************/
/**** EXPORTED VARIABLES ****/
/****************************/

/****************************/
/**** EXPORTED FUNCTIONS ****/
/****************************/

PUBLIC ZPS_tsNwkNib *
ZPS_psNwkNibGetHandle(void *pvNwk);

PUBLIC void
ZPS_vNwkNibClearTables(void *pvNwk);

PUBLIC void
ZPS_vNwkNibClearDiscoveryNT(void *pvNwk);

PUBLIC uint16
ZPS_u16NwkNibGetNwkAddr(void *pvNwk);

PUBLIC void
ZPS_vNwkNibSetNwkAddr(void *pvNwk, uint16 u16NwkAddr);

PUBLIC void
ZPS_vNwkNibSetNwkAddrNibOnly(void *pvNwk, uint16 u16NwkAddr);

PUBLIC uint64
ZPS_u64NwkNibGetExtAddr(void *pvNwk);

PUBLIC void
ZPS_vNwkNibSetExtPanId(void *pvNwk,
                       uint64 u64ExtPanId);

PUBLIC bool_t
ZPS_bNwkNibAddrMapAddEntry(void *pvNwk,
                           uint16 u16NwkAddr,
                           uint64 u64ExtAddr,bool_t bCheckNeighborTable);

PUBLIC bool_t
ZPS_bNwkNibNtActvMatch(void *pvNwk,
                       uint8 u8MatchMask,
                       uint64 u16NwkAddr,
                       uint64 u64ExtAddr,
                       ZPS_tsNwkActvNtEntry **ppsActvNtEntry);

PUBLIC bool_t ZPS_bNwkNibNtActvFindChild (
    void *pvNwk,
    bool bFindChildEntry,
    uint8 u8MatchMask,
    uint64 u16NwkAddr,
    uint64 u64ExtAddr,
    ZPS_tsNwkActvNtEntry **ppsActvNtEntry);

PUBLIC uint8
ZPS_u8NwkNibNtDiscMatch(void *pvNwk,
                        uint64 u64ExtPanId,
                        ZPS_teNwkRejoin eRejoin,
                        ZPS_tsNwkDiscNtEntry **ppsDiscNtEntry);

PUBLIC uint64
ZPS_u64NwkNibFindExtAddr(void *pvNwk,
                         uint16 u16NwkAddr);

PUBLIC uint16
ZPS_u16NwkNibFindNwkAddr(void *pvNwk,
                         uint64 u64ExtAddr);
PUBLIC void ZPS_vNwkNibNtDiscSetPParent(
        void *pvNwk,
        uint64 u64ExtPanId);

PUBLIC void
ZPS_vNwkNibCheckAndUpdateAddresses(void *pvNwk,
                                   uint16 u16NwkAddr,
                                   uint64 u64ExtAddr,bool bZgp);

PUBLIC void ZPS_vNwkNibCheckAndUpdateChildren(void *pvNwk,
                                   uint16 u16NwkAddr,
                                   uint64 u64ExtAddr,
                                   uint8 u8Capability );

PUBLIC void
ZPS_vNwkNibSetKeySeqNum(void *pvNwk,
                        uint8 u8ActiveKeySeqNumber);

PUBLIC void
ZPS_vNwkNibSetDepth(void *pvNwk,
                    uint8 u8Depth);

PUBLIC void
ZPS_vNwkNibIncSeqNum(void *pvNwk);

PUBLIC void
ZPS_vNwkNibSetUpdateId(void *pvNwk,
                       uint8 u8UpdateId);

PUBLIC void
ZPS_vNwkNibSetPanId(void *pvNwk,
                    uint16 u16PanId);

PUBLIC void
ZPS_vNwkNibSetCapabilityInfo(void *pvNwk,
                             uint8 u8CapabilityInfo);

PUBLIC void
ZPS_vNwkNibSetChannel(void *pvNwk,
                      uint8 u8Channel);

PUBLIC void
ZPS_vNwkNibSetParentAddr(void *pvNwk,
                         uint16 u16ParentAddr);

PUBLIC void
ZPS_vNwkSaveNt(void *pvNwk);

PUBLIC void
ZPS_vNwkSaveNib(void *pvNwk);

PUBLIC void ZPS_vNwkSaveSecMat(void *pvNwk);

#ifdef ZPS_NWK_OPT_RT_PERSISTED
PUBLIC void ZPS_vNwkSaveRtTable(void *pvNwk);
#endif
PUBLIC void ZPS_vNwkIncOutFC(void *pvNwk);

PUBLIC uint64
ZPS_u64NwkNibGetEpid(void *pvNwk);

PUBLIC void
ZPS_vNtSetAuthStatus(void *pvNwk,
                     ZPS_tsNwkActvNtEntry *psActvNtEntry,
                     bool_t bStatus);

PUBLIC void
ZPS_vNtSetUsedStatus(void *pvNwk,
                     ZPS_tsNwkActvNtEntry *psActvNtEntry,
                     bool_t bStatus);

PUBLIC uint16 ZPS_u16NwkNibGetMacPanId(void *pvNwk);

PUBLIC void * ZPS_pvNwkNibGetMacHandle(void *pvNwk);
PUBLIC void ZPS_vNwkNibSetLeaveRejoin(void *pvNwk, bool bRejoin);
PUBLIC void ZPS_vNwkNibSetLeaveAllowed(void *pvNwk, bool bLeave);
PUBLIC void zps_vRemoveRoute(void * pvNwk, uint16 u16NwkAddr);
PUBLIC void zps_vRemoveNextHop(void * pvNwk, uint16 u16NwkAddr);
PUBLIC void zps_vStartRouter(void *pvNwk,
                             ZPS_tsNwkNlmeReqRsp *psNlmeReqRsp,
                             ZPS_tsNwkNlmeSyncCfm *psNlmeSyncCfm);

PUBLIC void ZPS_vNwkNibSetTables (
    void *pvNwk,
    ZPS_tsNwkNibTblSize *psTblSize,
    ZPS_tsNwkNibTbl *psTbl);
PUBLIC void zps_vBuildSortedActvNTList(void* pvNwk);
PUBLIC bool_t zps_bNwkFindAddIeeeAddr(void *pvNwk,uint64 u64MacAddress, uint16 *pu16Location, bool_t bNeighborTable);
PUBLIC void ZPS_vRemoveEntryFromAddressMap(void *pvNwk, uint16 u16ShortAddress);
PUBLIC uint64 ZPS_u64NwkNibGetMappedIeeeAddr(void* pvNwk, uint16 u16Location);
PUBLIC void ZPS_vNwkTimerQueueOverflow(ZPS_tsTsvTimerInfo *psTimerInfo);
PUBLIC void ZPS_vNwkSendNwkStatusCommand(void *pvNwk, uint16 u16DstAddress, uint16 u16TargetAddress, uint8 u8CommandId, uint8 u8Radius);
PUBLIC void ZPS_vNwkPurgeMacAddressAndRelatedEntries ( void *pvNwk,
                                                       uint64 u64MacAddress,
                                                       bool_t bMacRemove);
#ifdef __cplusplus
};
#endif

#endif /* _zps_nwk_nib_h_ */

/* End of file $Id: zps_nwk_nib.h 81986 2016-08-02 02:00:54Z nxp29741 $ *******************************************/
