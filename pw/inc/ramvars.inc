/* vim: set ft=gas ts=8: */

.ifndef _POKEWALKER_RAMVARS_DEFS_H_
.set _POKEWALKER_RAMVARS_DEFS_H_, 0

.set RamCache_totalSteps,						0xf780
.set RamCache_STEP_COUNT,						0xf784
.set RamCache_lastSyncTime,						0xf788
.set RamCache_totalDays,						0xf78c
.set RamCache_curWatts,							0xf78e
.set stepToWattDividerState,						0xf792
.set curEventLogPointer,						0xf793
.set RamCache_settingsByte,						0xf797

.set CUR_KEYS,								0xf79a
.set stepCountTodaySoFar,						0xf79c
.set someWalkingRelatedState,						0xf7a0
.set currentSecond,							0xf7a4
.set currentMinute,							0xf7a5
.set currentHour,							0xf7a6
.set base_contrast_value,						0xf7a9
.set menuCurItem,							0xf7aa
.set curUiFlags,							0xf7ac
.set commsErrorMessageId,						0xf7ad
.set ACCEL_SAMPLE_NEXT_WRITE_IDX,					0xf7ae
.set currentlyActiveView,						0xf7b1
.set step_detection_related_A,						0xf7b2
.set step_detection_related_B,						0xf7b3
.set step_detection_related_C,						0xf7b4
.set common_bit_flags,							0xf7b5
.set walker_status_flags,						0xf7b6
.set TimeWhenLastByteRxed,						0xf7b8
.set NumBytesRxedsoFar,							0xf7ba
.set CUR_HEAP_PTR,							0xf7be
.set RandomSeed,							0xf7c0
.set volume,								0xf7c6

.set gCurSubstateY,							0xf7ce
.set gCurSubstateZ,							0xf7cf
.set gCurSubstateA,							0xf7d0
.set gCurSubstateB,							0xf7d2
.set gCurSubstateC,							0xf7d4
.set gCurSubstateD,							0xf7d5
.set gCurSubstateE,							0xf7d6
.set gCurSubstateF,							0xf7d8

/** RCE: write fn ptr to execute here */
.set currentEventLoopFunc,						0xf7e0
.set prevEventLoopFunc,							0xf7e2
.set sometimes_new_rxed_data_for_0xED,					0xf7e6

.set ACCEL_SAMPLES_X,							0xf826
.set RamCache_ED_data,							0xf84e
.set ACCEL_SAMPLES_Y,							0xf866
.set ACCEL_SAMPLES_Z,							0xf8a6

.set SuggestedOurSideSessionId,						0xf8b6
.set CurrentSessionID,							0xf8ba
.set ourPeerRole,							0xf8be
.set numTimesWeSentIrAdv,						0xf8bf
.set NumPingsSent,							0xf8c2
.set bool_got_at_least_one_packet,					0xf8c3
.set REQUESTED_POKEMON_ACTION_TYPE,					0xf8c4
.set PeerPlayStage,							0xf8c5
.set PeerPlayEepromXferSizeLeft,					0xf8c6
.set PeerPlayEepromXferLocalAddr,					0xf8c8
.set PeerPlayEepromXferRemoteAddr,					0xf8ca
.set PeerPlayEepromXfreNumPacketsSentSoFar,				0xf8cc
.set LastRxedUnusedByte,						0xf8cd

.set TX_PACKET_cmd,							0xf8ce
.set TX_PACKET_extraByte,						0xf8cf
.set TX_PACKET_crc,							0xf8d0
.set TX_PACKET_session,							0xf8d2
/** 16 bytes */
.set TX_PACKET_payload,							0xf8d6

.set HEAP_START,							0xf8f0
/** RCE: write code here */
.set DECOMPRESSION_BUFFER,						0xf956
.set RAM_END,								0xff80
/*
 * additional possible usable RAM sections:
 * - 0xf7f6 and onwards until 0xf826
 * - 0xf82e .. 0xf84e
 * - 0xf858 .. 0xf866
 */

.endif

