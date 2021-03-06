////////////////////////////////////////////////////////////////////////////////////////////////////
//
//   Copyright (c) 2012 Microsoft Corporation.  All Rights Reserved.
//
//   Module Name:
//      CompletionFunctions_PendAuthorizationCallouts.h
//
//   Abstract:
//      This module contains prototypes for WFP Completion functions for pending authorizations that
//         inject data back into the data path.
//
//   Author:
//      Dusty Harper      (DHarper)
//
//   Revision History:
//
//      [ Month ][Day] [Year] - [Revision]-[ Comments ]
//      May       01,   2010  -     1.0   -  Creation
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef COMPLETION_PEND_AUTHORIZATION_H
#define COMPLETION_PEND_AUTHORIZATION_H

typedef struct PEND_AUTHORIZATION_COMPLETION_DATA_
{
   KSPIN_LOCK                  spinLock;
   UINT32                      refCount;
   BOOLEAN                     performedInline;
   CLASSIFY_DATA*              pClassifyData;
   INJECTION_DATA*             pInjectionData;
   FWPS_TRANSPORT_SEND_PARAMS* pSendParams;
}PEND_AUTHORIZATION_COMPLETION_DATA, *PPEND_AUTHORIZATION_COMPLETION_DATA;

_At_(*ppCompletionData, _Pre_ _Notnull_)
_At_(*ppCompletionData, _Post_ _Null_ __drv_freesMem(Pool))
_IRQL_requires_min_(PASSIVE_LEVEL)
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_same_
_Success_(*ppCompletionData == 0)
VOID PendAuthorizationCompletionDataDestroy(_Inout_ PEND_AUTHORIZATION_COMPLETION_DATA** ppCompletionData,
                                            _In_ BOOLEAN override = FALSE);

_IRQL_requires_min_(PASSIVE_LEVEL)
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_same_
VOID CompletePendAuthorization(_In_ VOID* pContext,
                               _Inout_ NET_BUFFER_LIST* pNetBufferList,
                               _In_ BOOLEAN dispatchLevel);

#endif /// COMPLETION_PEND_AUTHORIZATION_H