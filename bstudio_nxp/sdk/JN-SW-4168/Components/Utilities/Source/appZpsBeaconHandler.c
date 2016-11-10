 /*
 * MODULE:      Utils
 *
 * COMPONENT:   appZpsBeaconHandler.c
 *
 * AUTHOR:      nxp29741
 *
 * DESCRIPTION:
 *
 * $HeadURL:  $
 *
 * $Revision:  $
 *
 * $LastChangedBy: nxp29741 $
 *
 * $LastChangedDate: $
 *
 * $Id:  $
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

/***********************/
/**** INCLUDE FILES ****/
/***********************/

#include "appZpsBeaconHandler.h"

/************************/
/**** MACROS/DEFINES ****/
/************************/
/**************************/
/**** TYPE DEFINITIONS ****/
/**************************/
/******************************/
/**** FORWARD DECLARATIONS ****/
/******************************/

/*****************/
/**** IMPORTS ****/
/*****************/
extern uint64 zps_u64NwkLibFromPayload(
    uint8 *pu8Buffer);
/*****************/
/**** EXPORTS ****/
/*****************/

tsBeaconFilterType *psBeaconFilter = NULL;
/**************/
/**** DATA ****/
/**************/

/**** LOCAL SCOPE ****/
/**** MODULE SCOPE ****/

/*************************/
/*************************/
/**** PRIVATE METHODS ****/
/*************************/
/*************************/
/************************/
/************************/
/**** MODULE METHODS ****/
/************************/
/************************/

/************************/
/************************/
/**** PUBLIC METHODS ****/
/************************/
/************************/



/****************************************************************************
 *
 * NAME:       ZPS_bAppAddBeaconFilter
 */
/**
 * @param
 *            tsBeaconFilterType *
 * @return
 *
 * @note
 *
 * Function is called by application to enable filtering
 ****************************************************************************/

PUBLIC void ZPS_bAppAddBeaconFilter(tsBeaconFilterType *psAppBeaconStruct)
{
    psBeaconFilter = psAppBeaconStruct;
}


/****************************************************************************
 *
 * NAME:       ZPS_bAppRemoveBeaconFilter
 */
/**
 * @param
 *
 * @return
 *
 * @note
 * Funcation may be called to disable filtering. It is called from the stack
 * and may be called from the application
 *
 * WARNING DO NOT CHANGE FUNCTION NAME,PARAMETER LIST AND RETURN TYPE
 * THIS IS CALLED FROM THE STACK
 ****************************************************************************/

PUBLIC void ZPS_bAppRemoveBeaconFilter(void)
{
    psBeaconFilter = NULL;
}


/****************************************************************************
 *
 * NAME:       ZPS_bAppPassBeaconToHigherLayer
 */
/**
 * @param
 *            MAC_MlmeDcfmInd_s*
 * @return
 *            boolean
 * @note
 *
 * The function is called from the Zigbee pro stack to indicate beacon
 * notification. It provides a mechanism to be selective on the which beacons
 * we are interested in
 * WARNING DO NOT CHANGE FUNCTION NAME,PARAMETER LIST AND RETURN TYPE
 * THIS IS CALLED FROM THE STACK. THE BODY OF THE FUNCTION MAY BE CHANGED.
 ****************************************************************************/

PUBLIC bool_t ZPS_bAppPassBeaconToHigherLayer(MAC_MlmeDcfmInd_s* psBeaconIndication)
{
    uint8 u8Traverse;
        /* we only want zigbee beacons */
    if(((psBeaconIndication->uParam.sIndBeacon.u8SDUlength > 0) &&
    (BF_BCN_PL_PROTOCOL_ID(psBeaconIndication->uParam.sIndBeacon.u8SDU) == 0)))
    {
        /* Is filter registered */
        if(psBeaconFilter)
        {
            if(psBeaconFilter->u8FilterMap & BF_USED_BITMASK)
            {
                if((psBeaconFilter->u8FilterMap & (BF_BITMAP_BLACKLIST|BF_BITMAP_WHITELIST)) == (BF_BITMAP_BLACKLIST|BF_BITMAP_WHITELIST))
                {
                    return TRUE; /* invalid bitmask pass the upwards*/
                }

                if(psBeaconFilter->u8FilterMap & (BF_BITMAP_BLACKLIST|BF_BITMAP_WHITELIST))
                {
                    for(u8Traverse=0; u8Traverse < psBeaconFilter->u8ListSize; u8Traverse++)
                    {
                        uint64 u64ExtendedPanId = zps_u64NwkLibFromPayload(BF_BCN_PL_EXT_PAN_ID_PTR(psBeaconIndication->uParam.sIndBeacon.u8SDU));

                        if((u64ExtendedPanId == psBeaconFilter->pu64ExtendPanIdList[u8Traverse])
                           && psBeaconFilter->u8FilterMap & BF_BITMAP_BLACKLIST)
                        {
                            return FALSE;
                        }

                        if((u64ExtendedPanId == psBeaconFilter->pu64ExtendPanIdList[u8Traverse])
                            && psBeaconFilter->u8FilterMap & BF_BITMAP_WHITELIST)
                        {
                            break;
                        }
                    }

                    if((psBeaconFilter->u8FilterMap & BF_BITMAP_WHITELIST) &&
                    (u8Traverse == psBeaconFilter->u8ListSize))
                    {
                        return FALSE; /* Not in Whitelist */
                    }
                }

                /*check for any other filters */

                if((psBeaconFilter->u8FilterMap & BF_BITMAP_PERMIT_JOIN))
                {
                    if(BF_GET_ASSOC_PERMIT(psBeaconIndication->uParam.sIndBeacon.sPANdescriptor.u16SuperframeSpec) == 0)
                    {
                        return FALSE; /* Association not permitted */
                    }

                }

                if((psBeaconFilter->u8FilterMap & BF_BITMAP_CAP_ENDDEVICE))
                {
                    if(BF_BCN_PL_ZED_CAPACITY(psBeaconIndication->uParam.sIndBeacon.u8SDU) == 0)
                    {
                        return FALSE;/* no End device capacity  */
                    }
                }

                if((psBeaconFilter->u8FilterMap & BF_BITMAP_CAP_ROUTER))
                {
                    if(BF_BCN_PL_ZR_CAPACITY(psBeaconIndication->uParam.sIndBeacon.u8SDU) == 0)
                    {
                        return FALSE;/* no Router capacity  */
                    }
                }

                if((psBeaconFilter->u8FilterMap & BF_BITMAP_LQI))
                {
                    if(psBeaconIndication->uParam.sIndBeacon.sPANdescriptor.u8LinkQuality < psBeaconFilter->u8Lqi)
                    {
                        return FALSE; /* link quality isn't good enough */
                    }
                }

                /* passed all the filter tests */
                return TRUE;


            }
            else
            {
                return TRUE; /* invalid filter pass the beacon upwards */
            }
        }
        else /* no filter registered pass the beacon upwards */
        {
            return TRUE;
        }

    }

    return FALSE; /* We get here only if not a zigbee beacon,throw the beacon away*/


}
/* End of file $Id: appZpsBeaconHandler.c 2014-01-08 17:21:12Z nxp29741 $ *******************************************/
