/* vim: set ts=8: */

#ifndef _POKEWALKER_RAMVARS_DEFS_H_
#define _POKEWALKER_RAMVARS_DEFS_H_

#define RamCache_totalSteps						0xf780
#define RamCache_STEP_COUNT						0xf784
#define RamCache_lastSyncTime						0xf788
#define RamCache_totalDays						0xf78c
#define RamCache_curWatts						0xf78e
#define stepToWattDividerState						0xf792
#define curEventLogPointer						0xf793
#define RamCache_settingsByte						0xf797

#define CUR_KEYS							0xf79a
#define stepCountTodaySoFar						0xf79c
#define someWalkingRelatedState						0xf7a0
#define currentSecond							0xf7a4
#define currentMinute							0xf7a5
#define currentHour							0xf7a6
#define base_contrast_value						0xf7a9
#define menuCurItem							0xf7aa
#define curUiFlags							0xf7ac
#define commsErrorMessageId						0xf7ad
#define ACCEL_SAMPLE_NEXT_WRITE_IDX					0xf7ae
#define currentlyActiveView						0xf7b1
#define step_detection_related_A					0xf7b2
#define step_detection_related_B					0xf7b3
#define step_detection_related_C					0xf7b4
#define common_bit_flags						0xf7b5
#define walker_status_flags						0xf7b6
#define TimeWhenLastByteRxed						0xf7b8
#define NumBytesRxedsoFar						0xf7ba
#define CUR_HEAP_PTR							0xf7be
#define RandomSeed							0xf7c0
#define volume								0xf7c6

#define gCurSubstateY							0xf7ce
#define gCurSubstateZ							0xf7cf
#define gCurSubstateA							0xf7d0
#define gCurSubstateB							0xf7d2
#define gCurSubstateC							0xf7d4
#define gCurSubstateD							0xf7d5
#define gCurSubstateE							0xf7d6
#define gCurSubstateF							0xf7d8

/** RCE: write fn ptr to execute here */
#define currentEventLoopFunc						0xf7e0
#define prevEventLoopFunc						0xf7e2
#define sometimes_new_rxed_data_for_0xED				0xf7e6

#define ACCEL_SAMPLES_X							0xf826
#define RamCache_ED_data						0xf84e
#define ACCEL_SAMPLES_Y							0xf866
#define ACCEL_SAMPLES_Z							0xf8a6

#define SuggestedOurSideSessionId					0xf8b6
#define CurrentSessionID						0xf8ba
#define ourPeerRole							0xf8be
#define numTimesWeSentIrAdv						0xf8bf
#define NumPingsSent							0xf8c2
#define bool_got_at_least_one_packet					0xf8c3
#define REQUESTED_POKEMON_ACTION_TYPE					0xf8c4
#define PeerPlayStage							0xf8c5
#define PeerPlayEepromXferSizeLeft					0xf8c6
#define PeerPlayEepromXferLocalAddr					0xf8c8
#define PeerPlayEepromXferRemoteAddr					0xf8ca
#define PeerPlayEepromXfreNumPacketsSentSoFar				0xf8cc
#define LastRxedUnusedByte						0xf8cd

#define TX_PACKET_cmd							0xf8ce
#define TX_PACKET_extraByte						0xf8cf
#define TX_PACKET_crc							0xf8d0
#define TX_PACKET_session						0xf8d2
/** 16 bytes */
#define TX_PACKET_payload						0xf8d6

#define HEAP_START							0xf8f0
/** RCE: write code here */
#define DECOMPRESSION_BUFFER						0xf956
#define RAM_END								0xff80
/*
 * additional possible usable RAM sections:
 * - 0xf7f6 and onwards until 0xf826
 * - 0xf82e .. 0xf84e
 * - 0xf858 .. 0xf866
 */

#endif

