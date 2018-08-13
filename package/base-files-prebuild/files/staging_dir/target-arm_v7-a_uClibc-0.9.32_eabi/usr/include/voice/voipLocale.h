/***************************************************************************
*
* <:copyright-BRCM:2005:proprietary:standard
* 
*    Copyright (c) 2005 Broadcom 
*    All Rights Reserved
* 
*  This program is the proprietary software of Broadcom and/or its
*  licensors, and may only be used, duplicated, modified or distributed pursuant
*  to the terms and conditions of a separate, written license agreement executed
*  between you and Broadcom (an "Authorized License").  Except as set forth in
*  an Authorized License, Broadcom grants no license (express or implied), right
*  to use, or waiver of any kind with respect to the Software, and Broadcom
*  expressly reserves all rights in and to the Software and all intellectual
*  property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU HAVE
*  NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY
*  BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.
* 
*  Except as expressly set forth in the Authorized License,
* 
*  1. This program, including its structure, sequence and organization,
*     constitutes the valuable trade secrets of Broadcom, and you shall use
*     all reasonable efforts to protect the confidentiality thereof, and to
*     use this information only in connection with your use of Broadcom
*     integrated circuit products.
* 
*  2. TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
*     AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
*     WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
*     RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND
*     ALL IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT,
*     FITNESS FOR A PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR
*     COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE
*     TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF USE OR
*     PERFORMANCE OF THE SOFTWARE.
* 
*  3. TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR
*     ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL,
*     INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY
*     WAY RELATING TO YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN
*     IF BROADCOM HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES;
*     OR (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT ACTUALLY PAID FOR THE
*     SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE LIMITATIONS
*     SHALL APPLY NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF ANY
*     LIMITED REMEDY.
* :>
*
****************************************************************************
*
*    Filename: locale.h
*
****************************************************************************
*    Description:
*
*      This file contains definition for locale support.
*
****************************************************************************/

/*
   International Country Strings based on three letter code (ISO alpha-3)
*/
#define CC_COUNTRY_STR_AUSTRALIA             "AUS"
#define CC_COUNTRY_STR_BELGIUM               "BEL"
#define CC_COUNTRY_STR_BRAZIL                "BRA"
#define CC_COUNTRY_STR_CHILE                 "CHL"
#define CC_COUNTRY_STR_CHINA                 "CHN"
#define CC_COUNTRY_STR_CZECH                 "CZH"
#define CC_COUNTRY_STR_DENMARK               "DNK"
#define CC_COUNTRY_STR_ETSI                  "ETS"
#define CC_COUNTRY_STR_FINLAND               "FIN"
#define CC_COUNTRY_STR_FRANCE                "FRA"
#define CC_COUNTRY_STR_GERMANY               "DEU"
#define CC_COUNTRY_STR_HUNGARY               "HUN"
#define CC_COUNTRY_STR_INDIA                 "IND"
#define CC_COUNTRY_STR_ITALY                 "ITA"
#define CC_COUNTRY_STR_JAPAN                 "JPN"
#define CC_COUNTRY_STR_MEXICO                "MEX"
#define CC_COUNTRY_STR_NETHERLANDS           "NLD"
#define CC_COUNTRY_STR_NEW_ZEALAND           "NZL"
#define CC_COUNTRY_STR_NORTH_AMERICA         "USA"
#define CC_COUNTRY_STR_POLAND                "POL"
#define CC_COUNTRY_STR_SPAIN                 "ESP"
#define CC_COUNTRY_STR_SWEDEN                "SWE"
#define CC_COUNTRY_STR_NORWAY                "NOR"
#define CC_COUNTRY_STR_SWITZERLAND           "CHE"
#define CC_COUNTRY_STR_TR57                  "T57"
#define CC_COUNTRY_STR_UK                    "GBR"
#define CC_COUNTRY_STR_TAIWAN                "TWN"
#define CC_COUNTRY_STR_UNITED_ARAB_EMIRATES  "UAE"
#define CC_COUNTRY_STR_CYPRUS                "CYP"

#if 1 //ZyXEL Porting.B: Add.
#define CC_COUNTRY_STR_TURKEY				 "TUK" /* 2015.06.29.Add country code by brady */
#define CC_COUNTRY_STR_CROATIA				 "HRV" /* 2015.10.02.Add country code " Croatia " by yushiuan  */
#define CC_COUNTRY_STR_COLOMBIA				 "COL" /* 2015.10.08.Add country code " Colombia " by yushiuan  */
//
#define CC_COUNTRY_STR_SLOVAKIA				 "SVK" /* 2015.10.08.Add country code " Slovakia " by yushiuan  */
#define CC_COUNTRY_STR_SLOVENIA				 "SVN" /* 2015.10.08.Add country code " Slovenia " by yushiuan  */
#endif //ZyXEL Porting.E: Add.