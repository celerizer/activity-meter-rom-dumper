/* vim: set ft=gas ts=8: */

.ifndef _POKEWALKER_FLASHROM_DEFS_H_
.set _POKEWALKER_FLASHROM_DEFS_H_, 0

/*** start of ROM: identification and vector table ***************************/

.set DATE_STRING,							0x0050
.set VERSION_A,								0x005c
.set VERSION_B,								0x005d

.set VECTOR_NMI,							0x005e
.set VECTOR_TRAPA_0,							0x0060
.set VECTOR_TRAPA_1,							0x0062
.set VECTOR_TRAPA_2,							0x0064
.set VECTOR_TRAPA_3,							0x0066
.set VECTOR_CPU_SLEEP,							0x0068
.set VECTOR_COMP_0,							0x006a
.set VECTOR_COMP_1,							0x006c
.set VECTOR_RTC_WEEK,							0x006e
.set VECTOR_RTC_ALARM,							0x0070
.set VECTOR_WDT,							0x0072
.set VECTOR_ASYNC_EVT_OVERFLOW,						0x0074
.set VECTOR_SSU_I2C,							0x0076

/*** subroutines *************************************************************/

.set set_timer_b_and_enable_irq,					0x0078
.set performActionAsRequestedByRemote,					0x009a
.set clear_special_route_info_and_all_B8_flags,				0x019a

.set ENTRY,								0x02c4

.set processSyncPacketFromGame,						0x03b4
.set copyTeamAndconfigDataFromStagingArea,				0x0426
.set startWalkEepromActions,						0x048c
.set end_walk_action,							0x0636
.set clearWattsAndErasePokemonStructure,				0x06de

/* bclr    #2, @IRQ_IRR2:8; rte */
.set VECTOR_TIMER_B1,							0x06fa

.set common_epilogue_also,						0x0700
/** r0 u16 calcPacketCrc(r0 dataP, er1 len) */
.set calcPacketCrc,							0x0714

/* rte */
.set VECTOR_SCI3,							0x075a

.set get_packet_data_pointer,						0x075c
.set io_related_weirdness,						0x0762
/** void sendPacket(r0h cmd, r0l dataLen, r1l directionByte) */
.set sendPacket,							0x0772
.set sciConfigureForIrDA,						0x07f2
/** void irTxByte(r0l byte)
 *    xors the byte with 0xaa before sending
 */
.set irTxByte,								0x0822
.set configureIrdaAndIrRxTimer,						0x0832
.set configureSciAndSendPingByte,					0x0880
.set irCommsEventLoop,							0x08d6

.set maybe_shutDownIr_then_performActionAsRequested,			0x1856
.set eraseCaughtPokemonanddowsedAndGiftedItems,				0x187e
.set fill_some_eeprom_structs,						0x188c
/** void textImageAddBorders(r0l imgWidth, r0h imgWidth, e0 textAsImageDataInRam, r1l flagsBits)
 *    flag bits:
 *      0x01: add overline
 *      0x02: add underline
 *      0x04: add bar on left
 *      0x08: add bar on right
 */
.set textImageAddBorders,						0x18b6
/** void drawCurPokemonSmallAnimatedFrame(r0l x, r0h y) */
.set drawCurPokemonSmallAnimatedFrame,					0x1936
/** void drawCurPokemonSmallAnimatedFrameHorizFlipped(r0l x, r0h y) */
.set drawCurPokemonSmallAnimatedFrameHorizFlipped,			0x1972
/** void drawRouteAvailablePokemon(r0l x, r0h y, r1l availablePokemonIdx) */
.set drawRouteAvailablePokemon,						0x19b8
/** void drawPeerPlayPokemonAnimationFrame(r0l x, r0h y, r1l bool flipHorz) */
.set drawPeerPlayPokemonAnimationFrame,					0x1a0a
/** void drawCurPokemonNameWithBorders(r0l x, r0h y, r1l imgHeight) */
.set drawCurPokemonNameWithBorders,					0x1a58
/** void drawPeerPokemonName(r0l x, r0h y, r1l borderFlagBits) */
.set drawPeerPokemonName,						0x1ab2
/** void showEventPokeNameAndMaybeAnimation(r0l x, r0h y, r1l borderBits) */
.set showEventPokeNameAndMaybeAnimation,				0x1af4
/** void drawNameOfEventPokemon(r0l x, r0h y, r1l pkmnNameBorderFlags) */
.set drawNameOfEventPokemon,						0x1b40
/** void drawItemSymbolOnScreen(r0l x, r0h y) */
.set drawItemSymbolOnScreen,						0x1b94
/** void drawNameOfRouteAvailablePokemon(r0l x, r0h y, r1l availPkmnIdx, r1h pkmnNameBorderFlags)
      draws onscreen th ename of a pokemon available on this route at index r1l */
.set drawNameOfRouteAvailablePokemon,					0x1bc6
/** void drawRouteAvailableItemName(r0l x, r0h y, r1l itemIdxInRouteAvailItem, r1h nameBorderFlags) */
.set drawRouteAvailableItemName,					0x1c26
/** void showRxedItemName(r0l imgWidth, r0h imgHeight, r1l flagBits) */
.set showRxedItemName,							0x1c80
/** void drawLargeItemChest(r0l x, r0h y) */
.set drawLargeItemChest,						0x1cbe
/** void drawLargePresentItem(r0l x, r0h y) */
.set drawLargePresentItem,						0x1cf0
/** void setThatWeveParticipatedInAGivenEvent(r0 tmpSpace[0x68], r1l evtIdx) */
.set setThatWeveParticipatedInAGivenEvent,				0x1d22
/** r0l bool checkForWhetherWeveParticipatedInAGivenEvent(r0 tmpBuf[0x68], r1l evtIdx)
      always false for index 0 */
.set checkForWhetherWeveParticipatedInAGivenEvent,			0x1d7a
/** void moveImageVerticaly(r0l imgWidth, r0h imgHeight, e0 imgDataInRam, r1l "by")
      negative is up */
.set moveImageVerticaly,						0x1dca
/** r0l byte findFirstEmptyslotInCaughtPokeList(void* pokeStruct)
      returns 3 if all 3 slots are full, else idx of first empty slot */
.set findFirstEmptyslotInCaughtPokeList,				0x1eca
/** r0 getItemIdForNthItemOnRoute(r0l n) */
.set getItemIdForNthItemOnRoute,					0x1eee
/** ? findFreeItemSlotIdxInStarndardFoundItemsArray(void* r0 data)
      data: 4 bytes per item, 2 are item number, 2 unknown */
.set findFreeItemSlotIdxInStarndardFoundItemsArray,			0x1f1c
/** void addWatts(r0l watts) */
.set addWatts,								0x1f3e
/** void drawNumberAndWattsymbolOnscreen(r0l x, r0h y, r1l nameBorderFlags) */
.set drawNumberAndWattsymbolOnscreen,					0x1f6c
/** void drawNumberOnscreen(r0l x, r0l y, er1 n, [sp] bool addOverline)
      x: left side of rightmost chars. at most one char right of this, possibly many left */
.set drawNumberOnscreen,						0x1fee

/** void drawLargeMessagePotentiallyWithBlinkingCursor(r0l y, r0h msgIdx, r1l borderFlagBits, r1h bool blinkCursorInBotRgt)
      always drawn at x=0 */
.set drawLargeMessagePotentiallyWithBlinkingCursor,			0x2096
/** void imageFlipHorizontal(r0l imgWidth, r0h imgHeight, e0 imgData)
      height must be multiple of 8 */
.set imageFlipHorizontal,						0x2178
/** void drawLowBatteryIconAnimationFrame(r0l x, r0h y)
      also determined if this is needed at all */
.set drawLowBatteryIconAnimationFrame,					0x21fe
/** void imageOverlay(r0 imageDataInRam, e0 img1, r1l imgWidth, r1h imgHeight, e1 img2) */
.set imageOverlay,							0x224c
.set wdt_off,								0x245e
.set wdt_on,								0x246c
/** uses space in normal ir rx buffer (0xf8f0) */
.set setHeapPointer,							0x247e
/** void* r0 static_malloc(r0 size) */
.set static_malloc,							0x2488
.set accountForStepTakenLikely,						0x24ac
.set deviceSleep,							0x256e
.set wdt_pet,								0x259e
.set check_some_rtc_set_bit_and_maybe_wait,				0x25ac
/** void setRandomSeed(er0 seed) */
.set setRandomSeed,							0x25c8
.set rand,								0x25d0
/** void decompress(u8* e0 out, u8* r0 in) */
.set decompress,							0x25f6
.set enother_common_epilogue,						0x2660
.set common_epilogue_5,							0x266c
/** used in number rendering to add overline */
.set orr_0x0101_into_three_words,					0x2680
/** void accelRegRead(r0l regno, r0h nbytes, e0 dstRamPtr)
      0x80 or'ed into regno by this func */
.set accelRegRead,							0x26a0
/** void accelRegWrite(r0l regno, r0h value)
      manipulates nCS as needed */
.set accelRegWrite,							0x270a
/** bool r0l accelInit() */
.set accelInit,								0x273c
/** u16 checksumProtectAdcValue(u16 val)
      add values are actually only 12 bits (lower 12)
      this adds a checksum to this adc value for safer EEPROM storage
      0x0XYZ -> 0xTXYZ, where T = (X + Y + Z) & 0x0f */
.set checksumProtectAdcValue,						0x27c2
/** bool r0l adcClibrationDataVerifySelfChecksum(r0 word) */
.set adcClibrationDataVerifySelfChecksum,				0x27ec
/** u16 r0 adcSample() */
.set adcSample,								0x281e
/** bool checkBatteryBelowGivenLevel(r0 level) */
.set checkBatteryForBelowGivenLevel,					0x289a
/** void measureBatteryAndSetLowFlag() */
.set measureBatteryAndSetLowFlag,					0x290a

/** void recordPokeCaughtNormal()
      gCurSubstateY has poke index on route OR somethign else...  1..3 is poke on route, 4 is event poke */
.set recordPokeCaughtNormal,						0x2a96

.set interactionHandlerPokeBattle,					0x2c62
.set battleScreenDraw,							0x30a6
.set is_F7C4_nonzero,							0x369c
.set configureSomeIoAndTimerW,						0x36aa
/** void randomEepromChecksumCheck(r0l area)
      area in 0..15 */
.set randomEepromChecksumCheck,						0x36f2
/** void write_F7C4_clear_F7C8_and_F7CA(r0 valueToWrite) */
.set write_F7C4_clear_F7C8_and_F7CA,					0x37c6

.set setVolume,								0x3832
/** void setBeeperFreq(r0l period)
      period in 32 kHz ticks */
.set setBeeperFreq,							0x3838

.set timer_w_irq,							0x388c
.set VECTOR_TIMER_W,							0x3a4a
.set set_gCurSubstateZ_to_1,						0x3a68
.set recordPokeCaughtNoEventConsideration_WEIRD,			0x3a70
.set recordItemFoundNoEventConsideration_WEIRD,				0x3b02
.set interactionHandlerSwitchScreen,					0x3b94
.set drawCurSelectedPokeNameForSwitchScreen,				0x3c0a
.set drawSwitchScreen,							0x3cd8
.set drawBallFropFromTopOfScreen,					0x3dbc
.set drawPokeballInMiddleOfScreen,					0x3e34
.set drawCloudWithBarsOnTopAndBottomOfScreen2,				0x3ece
.set drawLargePokemonImageWithBarsOnTopAndBottomOfScreen,		0x3f32
.set pokemonArrivalHandler,						0x3f72
.set drawItemMapStampOrRouteReceived,					0x3fc6

.set interactionHandlerPokemonArrivedAnimation,				0x40f8
.set drawPokemonArrivedAnimation,					0x4148
.set interactionHandlerSomethingReceivedScreenDirectIrCommand,		0x4178
.set drawSomethingReceivedAnimation,					0x42a0
.set drawLargePokemonImageWithBarsOnTopAndBottomOfScreen2,		0x42d0
.set drawCloudWithBarsOnTopAndBottomOfScreen,				0x4310
.set drawMovingBlankIconWithBarsOnTopAndBottom,				0x4372
.set pokemonDepartureHandler,						0x43e4
.set drawPokewalkerAndCompletedMessage,					0x4434
.set interactionHandlerUnknonView_0x10,					0x449e
.set drawSomethignDepartingandCompletedMessage,				0x44f4
.set epilogue_common_pop_r6_r5_r2,					0x4534
.set common_epilogue_6,							0x453c

/** void logEvent(r0 teamRouteInfoRam, e0 tmpBuf, r1l evType, r1h bool isOnSpecialEvtRoute, e1 extrainf, u8 [sp] availablePokeIdx) */
.set logEvent,								0x4546

.set goToDowsingMicroApp,						0x4792
.set interactionHandlerDowsing,						0x47ce
/** void readSpecialItemInfo(void* r0 ramdst) */
.set readSpecialItemInfo,						0x499c
/** void writeSpecialItemInfo(void* r0 ramsrc) */
.set writeSpecialItemInfo,						0x49ae
.set foundSomeEventItem,						0x49c0
.set pokeFoundRandomItem,						0x4af2
.set dowsingStartHandleLikely,						0x4b9c
.set dowsingDraw,							0x4cd6
/** void checkIfPokeOrItemCanBeEncountered(r0 idx0, r1 idx1, r5 ptr)
      load LEu16 at ptr[idx0 + idx1], compare with current step counter */
.set checkIfPokeOrItemCanBeEncountered,					0x4f50
.set ssuConfigure,							0x4f70
.set ssu_Rx_Off,							0x4f92
/** u8 r0 ssu_WaitForRx() */
.set ssu_WaitForRx,							0x4fa0
/** void eepromWriteSingleByte(r0 addr, r1l val) */
.set eepromWriteSingleByte,						0x4fca

/** void writeReliableDataToEeprom(r0 eepaddr0, e0 eepaddr1, r1 src, e1 size) */
.set writeReliableDataToEeprom,						0x50d8
/** u8 r0l readReliableDataFromEeprom(r0 eepaddr0, e0 eepaddr1, r1 dst, e1 size)
      data is stored in two provided locations and read to RAM
      each location includes a checksum right after the data (not inluded in length)
      if only one location has checksum-valid data, other is replaced with it
      if both appear valid, #0 is assumed dominant
      if neither appears vlid, they are overwritten with 0xff, and so is the
      ram buffer,. returned checksum is also set to 0xFF */
.set readReliableDataFromEeprom,					0x5128
/** void eepromWriteData(r0 eepaddr, e0 srcptr, r1 size) */
.set eepromWriteData,							0x524e
/** void eepromReadToRamAlso(r0 eepaddr, e0 dstptr, r1 size) */
.set eepromReadToRam,							0x5384
/** u8 r0l eepromReadSingleByte(r0 eepaddr) */
.set eepromReadSingleByte,						0x552e
/** void eepromFillPageWithByte(r0 addr, r1l val) */
.set eepromFillPageWithByte,						0x5634
/** void eepromFillWithByte(r0 addr, e0 size, r1l val) */
.set eepromFillWithByte,						0x5742
/** void eepromWrite128Bytes(r0 eepaddr, e0 srcptr) */
.set eepromWrite128Bytes,						0x5874
.set factoryTestPerformIfNeeded,					0x5990
.set pokemonJoinsEmptyWalkerWalk,					0x5c0a
/** ? addRandomGift(r0l gift)
      when a pokemon randomly finds something */
.set addRandomGift,							0x5d52
.set interactionHandlerRandomGiftFromBoredPokemon,			0x5e9e
.set showPokemonFeelingsAndRandomFindings,				0x5edc
.set findRandomItem,							0x5fc2

/** ? processAcceleromerSamplesAxis(r0 ptr)
      data for one axis */
.set processAcceleromerSamplesAxis,					0x60da
.set goToPeerPlayMicroApp,						0x632c
.set calculateAndApplyPeerGift,						0x6382
/** void drawMusicNoteWithVariableShiftUp(r0l x, r0h y, r1l shiftup_px) */
.set drawMusicNoteWithVariableShiftUp,					0x6582
.set drawPeerPlay,							0x6574
.set seeIfWeSawThisTrainerBefore,					0x6784
.set pushSeenTrainersListLogDownOne,					0x67de
.set logPeerPlay,							0x6816
.set setEventLoopFunc,							0x693a
.set goToConnectionMicroApp,						0x694c
.set setCurrentlyActiveView,						0x69b8
/** void homeScreenDrawLargeCurrentPokemonImage(r0l x, r0h y) */
.set homeScreenDrawLargeCurrentPokemonImage,				0x69be
.set someStateVarShuffling,						0x6a1c
.set interactionHandlerHomeScreen,					0x6a3e
/** void drawPokemonFeelingBubble(r0l feelingIdx) */
.set drawPokemonFeelingBubble,						0x6ad8
.set drawCurrentAreaSmallImage,						0x6b10

.set drawHomeScreenMain,						0x6bf8

.set interactionHandlerSettings,					0x6dfc
.set drawSettingsScreen,						0x6e62

.set drawPokewalkerInitialConnectionInstructionScreen,			0x703c
.set drawSadPokewalkerImage,						0x711a
.set drawHappyPokewalkerWithActiveConnectivityAnimation,		0x71a4
.set connectionStartHandler,						0x722c
/** ? showCommsErrorMessage(msgid)
      1: "no trainer found"
      2,8: "cannot connect"
      3: "cannot complete this connection"
      4: "no pokemon held!"
      5: "cannot connect to trainer again"
      6: "already received this event"
      7: "could not receive" */
.set showCommsErrorMessage,						0x728a
.set interactionHandler,						0x7348
.set viewDoDisplay,							0x7406
.set drawhomeScreenSmallIconsOnBottom,					0x74bc
.set accelReadSample,							0x76aa
.set sleepModeEventLoop,						0x7882
.set normalModeEventLoop,						0x7998
.set common_prologue_2,							0x7a0a
.set common_epilogue_2,							0x7a2a
/** void drawImageToBuffer(r0l imgw, r0h imgH, e0 imgPtr, R1l x, r1h y, e1 dstptr, [sp] bufWidth, [sp+2] bufHeight) */
.set drawImageToBuffer,							0x7a40
/** ? lcdSendSingleByteCommand(r0l cmd) */
.set lcdSendSingleByteCommand,						0x7b44
.set smallDelay,							0x7b64
.set initLcdUsingRomOrEepromCommands,					0x7b72
/** void lcdSetContrast(u8 r0l contrast)
      incremented by base_contrast_value */
.set lcdSetContrast,							0x7c24
.set lcdRelatedWTF,							0x7c56
.set someLcdThingYetAgain,						0x7cac
.set screenShenenigans,							0x7cfa
.set lcdRelatedWTFZYX,							0x7d4a
/** void lcdFillRectangle(r0l x, r0h y, r1l w, r1h h, [sp] color) */
.set lcdFillRectangle,							0x7e58
.set lcdExitPowerSaveMode,						0x7fb8
.set lcdEnterPowerSaveMode,						0x7fda
.set someLcdRelatedThing,						0x7ffc

/** void drawImageToScreen(r0l x, r0h y, e0 imgPtr, r1l imgW, r1h imgH) */
.set drawImageToScreen,							0x80ac
/** void drawImageInSomeWeirdWay(r0l x, r0h y, e0 imgW, r1 imgH, e1 imgPtr) */
.set drawImageInSomeWeirdWay,						0x82ea
/** void drawTinyChars(r0l x, r0h y, e0 char* text) */
.set drawTinyChars,							0x858a
.set someFullLcdDrawingThing,						0x8766
.set someFullLcdDrawingThin2,						0x88e2
.set someDisplayNonsense,						0x8a36
.set common_epilogue_4,							0x8ab0
.set common_epilogue_3,							0x8abc
/** ? takeItemAndPokeInventory(u16 inventory[2])
      word[0]: 0x0001 - poke has joined empty walker on
               0x0002 - have caught poke slot #1 full or have event item
               0x0004 - have caught poke slot #2 full
               0x0008 - have caught poke slot #3 full
               0x0010 - have event poke slot full
               0x0020 - haven "special map" slot full
               0x0040 - have dowsed item slot #1 full
               0x0080 - have dowsed item slot #2 full
               0x0100 - have dowsed item slot #3 full
      word[1]: one bit per giften item slot. 10 total */
.set takeItemAndPokeInventory,						0x8aca

.set interactionHandlerPokemonAndItemsScreen,				0x8d02
.set drawPokemonAndItemsScreen,						0x8d88

.set interactionHandlerGiftedItemsScreen,				0x9116
.set giftedItemsView,							0x918c
.set clear_bytes_at_F8EE_F8EF_words_at_F8EA_F8E6,			0x9328
.set processAccelSamplesIncrementStepCountersAndNotifyInterestedPartiesAsNeeded, 0x945a
.set clear_gCurSubstateY,						0x974e
.set interactionHAndlerMainMenu,					0x9756
.set mainMenuDraw,							0x9930
.set maybeConfigureKeys,						0x9b34
.set likelyKeyDebounceRoutine,						0x9b84
/** r0l checkKeyStates(r0l wanted)
      0x02: enter
      0x04: left
      0x08: right */
.set checkKeyStates,							0x9c40
.set pickPokemonToEncounter,						0x9c48
.set goToPokeRadarMicroApp,						0x9d92
.set interactionHandlerPokeRadar,					0x9e72
.set pokeRadarDraw,							0x9f44

.set interactionHandlerPokeRadarFailureUserTooSlow,			0xa10a
.set pokeradarUserTooSlowScreen,					0xa12c
.set accelProcessDataDetectStep,					0xa1a8

.set VECTOR_IRQ0,							0xa300
.set VECTOR_IRQ1,							0xa31c
.set VECTOR_IRQ_AEC,							0xa322
.set VECTOR_ADC,							0xa328
.set clampTotalStepToLimit,						0xa32e

.set dayEndedRecordailyStepadnshipHistoricStepCounts,			0xa45e
/** void rtcSet(er0 seconds) */
.set rtcSet,								0xa4fe
/** (r0 seconds, e0 minutes, r1 hours) rtcReadBcd() */
.set rtcReadBcd,							0xa54d
.set VECTOR_RTC_QUARTER_SEC,						0xa65e
.set VECTOR_RTC_HALF_SEC,						0xa674
.set VECTOR_RTC_EVERY_SEC,						0xa682
.set VECTOR_RTC_EVERY_MIN,						0xa6e2
.set VECTOR_RTC_EVERY_HOUR,						0xa702
/** bool r0l eepromFactoryTest(r0 startaddr)
      'startaddr' must be a multiple of 256
      wipes all data after 'startaddr' */
.set eepromFactoryTest,							0xa72a
.set rtcFactoryTest,							0xa800
.set accelFactoryTest,							0xa830
.set adcFactoryTestAndCalibrate,					0xa8f8

.set interactionHandlerDebugMode22,					0xaa6c

.set drawSomethingWithTinyChars,					0xad06
.set drawSomethingWithTinyChars2,					0xaefa

.set drawNG6inTinyChars,						0xb0a2
.set writeNintendoStringToFlash,					0xb0ae
.set checkForNintendoStringInFlash,					0xb0c8
.set basicIoConfig,							0xb0f2
.set wipeOutStepsAndsyncTime,						0xb124
.set updateCachedWalkerStatusByteFromEeprom,				0xb176
/** void some_sort_of_eeprom_init(bool r0l wipeEventBitfield, bool r0h wipeSteps) */
.set some_sort_of_eeprom_init,						0xb1ae
.set checkForAndInitEepromContentsIfNeeded,				0xb2e2
.set delaySomewhatAndThenSetTheRtc,					0xb390
.set goToTrainerCardMicroApp,						0xb3c0
.set interactionHandlerTrainerCardAndStatsScreens,			0xb3cc
.set drawTrainerCard,							0xb48c
.set drawStepStatisticsScreen,						0xb682
.set showGoodJobBanner,							0xb7ee
.set drawRewardReceivedBanner,						0xb8a6
.set drawTrainerCardAndstatsScreens,					0xb8f2
/** ? bitfieldInsert(u8* r0 data, r1l valToInsert, r2l nbits, r2h bitOffset)
      bitOffset == 0: modify top bits
      bitfield is 8 bit */
.set bitfieldInsert,							0xb924
/** er0 = er0 / er1, er1 = er0 % er1 */
.set divmod32,								0xb94e
/** void lslByteAtPtr(u8* r0 ptr, r1 shift)
      *(u8*)ptr <<= shift */
.set lslByteAtPtr,							0xb98a
/** void lsrByteAtPtr(u8* r0 ptr, r1 shift)
      *(u8*)ptr >>= shift */
.set lsrByteAtPtr,							0xb99c
/** er0 = er0 * er1 */
.set mul32,								0xb9ae
/** void memcpy(r0 src, r1 dst, r2 len) */
.set memcpy,								0xb9ce
.set common_prologue,							0xba42
.set common_epilogue,							0xba62
.set copy_data_zero_bss,						0xba78

/****** data section *********************************************************/

.set FREQTAB,								0xbb4a
/** 32x32 */
.set POKEWALKER_LARGE_IMAGE,						0xbb74
/** 16x8 */
.set POKEWALKER_NEUTRAL_FACE_IMAGE,					0xbc74
/** 16x8 */
.set POKEWALKER_HAPPY_FACE_IMAGE,					0xbc94
/** 16x8 */
.set POKEWALKER_SAD_FACE_IMAGE,						0xbcb4
/** 8x8 */
.set POKEWALKER_UP_ARROW_ICON,						0xbcd4
.set POKEWALKER_IR_ACTIVE_ICON,						0xbce4
.set TINY_CHARS,							0xbcf4

.set BALL_DROP_Y_COORD,							0xbd70
.set item_screen_locs,							0xbd76
.set GOING_AWAY_ANIMATION_Y_COORDS,					0xbd7c
.set POKEBALL_THROW_ARC_Y,						0xbdd0
.set PEER_PLAY_MUSIC_NOTE_VERTICAL_MOVE_AMT,				0xbe70
.set INDEX_TO_FEELING_IMAGE_MAP,					0xbeb0
.set ROM_LCD_INIT_COMMANDS,						0xbeb8
.set ACTIVITY_WATT_COSTS,						0xbf0e
.set MAIN_MENU_ITEM_POSITIONS_Y_RELATIVE,				0xbf14
.set BUSH_X_COORDINATES_IN_POKERADAR,					0xbf25
.set DATA_FOR_EEPROM_HEADER,						0xbf98
.set DATA_FOR_EEPROM_0x8cf0,						0xbfa2
.set data_list_start,							0xbfba
.set bss_list_start,							0xbfc0
.set bss_list_end,							0xbfc4

.set unused_flash,							0xbfc8
.set FLASH_END,								0xc000

.endif

