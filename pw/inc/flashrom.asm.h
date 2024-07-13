/* vim: set ts=8: */

#ifndef _POKEWALKER_FLASHROM_DEFS_H_
#define _POKEWALKER_FLASHROM_DEFS_H_

/*** start of ROM: identification and vector table ***************************/

#define DATE_STRING							0x0050
#define VERSION_A							0x005c
#define VERSION_B							0x005d

#define VECTOR_NMI							0x005e
#define VECTOR_TRAPA_0							0x0060
#define VECTOR_TRAPA_1							0x0062
#define VECTOR_TRAPA_2							0x0064
#define VECTOR_TRAPA_3							0x0066
#define VECTOR_CPU_SLEEP						0x0068
#define VECTOR_COMP_0							0x006a
#define VECTOR_COMP_1							0x006c
#define VECTOR_RTC_WEEK							0x006e
#define VECTOR_RTC_ALARM						0x0070
#define VECTOR_WDT							0x0072
#define VECTOR_ASYNC_EVT_OVERFLOW					0x0074
#define VECTOR_SSU_I2C							0x0076

/*** subroutines *************************************************************/

#define set_timer_b_and_enable_irq					0x0078
#define performActionAsRequestedByRemote				0x009a
#define clear_special_route_info_and_all_B8_flags			0x019a

#define ENTRY								0x02c4

#define processSyncPacketFromGame					0x03b4
#define copyTeamAndconfigDataFromStagingArea				0x0426
#define startWalkEepromActions						0x048c
#define end_walk_action							0x0636
#define clearWattsAndErasePokemonStructure				0x06de

/* bclr    #2, @IRQ_IRR2:8; rte */
#define VECTOR_TIMER_B1							0x06fa

#define common_epilogue_also						0x0700
/** r0 u16 calcPacketCrc(r0 dataP, er1 len) */
#define calcPacketCrc							0x0714

/* rte */
#define VECTOR_SCI3							0x075a

#define get_packet_data_pointer						0x075c
#define io_related_weirdness						0x0762
/** void sendPacket(r0h cmd, r0l dataLen, r1l directionByte) */
#define sendPacket							0x0772
#define sciConfigureForIrDA						0x07f2
/** void irTxByte(r0l byte)
 *    xors the byte with 0xaa before sending
 */
#define irTxByte							0x0822
#define configureIrdaAndIrRxTimer					0x0832
#define configureSciAndSendPingByte					0x0880
#define irCommsEventLoop						0x08d6

#define maybe_shutDownIr_then_performActionAsRequested			0x1856
#define eraseCaughtPokemonanddowsedAndGiftedItems			0x187e
#define fill_some_eeprom_structs					0x188c
/** void textImageAddBorders(r0l imgWidth, r0h imgWidth, e0 textAsImageDataInRam, r1l flagsBits)
 *    flag bits:
 *      0x01: add overline
 *      0x02: add underline
 *      0x04: add bar on left
 *      0x08: add bar on right
 */
#define textImageAddBorders						0x18b6
/** void drawCurPokemonSmallAnimatedFrame(r0l x, r0h y) */
#define drawCurPokemonSmallAnimatedFrame				0x1936
/** void drawCurPokemonSmallAnimatedFrameHorizFlipped(r0l x, r0h y) */
#define drawCurPokemonSmallAnimatedFrameHorizFlipped			0x1972
/** void drawRouteAvailablePokemon(r0l x, r0h y, r1l availablePokemonIdx) */
#define drawRouteAvailablePokemon					0x19b8
/** void drawPeerPlayPokemonAnimationFrame(r0l x, r0h y, r1l bool flipHorz) */
#define drawPeerPlayPokemonAnimationFrame				0x1a0a
/** void drawCurPokemonNameWithBorders(r0l x, r0h y, r1l imgHeight) */
#define drawCurPokemonNameWithBorders					0x1a58
/** void drawPeerPokemonName(r0l x, r0h y, r1l borderFlagBits) */
#define drawPeerPokemonName						0x1ab2
/** void showEventPokeNameAndMaybeAnimation(r0l x, r0h y, r1l borderBits) */
#define showEventPokeNameAndMaybeAnimation				0x1af4
/** void drawNameOfEventPokemon(r0l x, r0h y, r1l pkmnNameBorderFlags) */
#define drawNameOfEventPokemon						0x1b40
/** void drawItemSymbolOnScreen(r0l x, r0h y) */
#define drawItemSymbolOnScreen						0x1b94
/** void drawNameOfRouteAvailablePokemon(r0l x, r0h y, r1l availPkmnIdx, r1h pkmnNameBorderFlags)
      draws onscreen th ename of a pokemon available on this route at index r1l */
#define drawNameOfRouteAvailablePokemon					0x1bc6
/** void drawRouteAvailableItemName(r0l x, r0h y, r1l itemIdxInRouteAvailItem, r1h nameBorderFlags) */
#define drawRouteAvailableItemName					0x1c26
/** void showRxedItemName(r0l imgWidth, r0h imgHeight, r1l flagBits) */
#define showRxedItemName						0x1c80
/** void drawLargeItemChest(r0l x, r0h y) */
#define drawLargeItemChest						0x1cbe
/** void drawLargePresentItem(r0l x, r0h y) */
#define drawLargePresentItem						0x1cf0
/** void setThatWeveParticipatedInAGivenEvent(r0 tmpSpace[0x68], r1l evtIdx) */
#define setThatWeveParticipatedInAGivenEvent				0x1d22
/** r0l bool checkForWhetherWeveParticipatedInAGivenEvent(r0 tmpBuf[0x68], r1l evtIdx)
      always false for index 0 */
#define checkForWhetherWeveParticipatedInAGivenEvent			0x1d7a
/** void moveImageVerticaly(r0l imgWidth, r0h imgHeight, e0 imgDataInRam, r1l "by")
      negative is up */
#define moveImageVerticaly						0x1dca
/** r0l byte findFirstEmptyslotInCaughtPokeList(void* pokeStruct)
      returns 3 if all 3 slots are full, else idx of first empty slot */
#define findFirstEmptyslotInCaughtPokeList				0x1eca
/** r0 getItemIdForNthItemOnRoute(r0l n) */
#define getItemIdForNthItemOnRoute					0x1eee
/** ? findFreeItemSlotIdxInStarndardFoundItemsArray(void* r0 data)
      data: 4 bytes per item, 2 are item number, 2 unknown */
#define findFreeItemSlotIdxInStarndardFoundItemsArray			0x1f1c
/** void addWatts(r0l watts) */
#define addWatts							0x1f3e
/** void drawNumberAndWattsymbolOnscreen(r0l x, r0h y, r1l nameBorderFlags) */
#define drawNumberAndWattsymbolOnscreen					0x1f6c
/** void drawNumberOnscreen(r0l x, r0l y, er1 n, [sp] bool addOverline)
      x: left side of rightmost chars. at most one char right of this, possibly many left */
#define drawNumberOnscreen						0x1fee

/** void drawLargeMessagePotentiallyWithBlinkingCursor(r0l y, r0h msgIdx, r1l borderFlagBits, r1h bool blinkCursorInBotRgt)
      always drawn at x=0 */
#define drawLargeMessagePotentiallyWithBlinkingCursor			0x2096
/** void imageFlipHorizontal(r0l imgWidth, r0h imgHeight, e0 imgData)
      height must be multiple of 8 */
#define imageFlipHorizontal						0x2178
/** void drawLowBatteryIconAnimationFrame(r0l x, r0h y)
      also determined if this is needed at all */
#define drawLowBatteryIconAnimationFrame				0x21fe
/** void imageOverlay(r0 imageDataInRam, e0 img1, r1l imgWidth, r1h imgHeight, e1 img2) */
#define imageOverlay							0x224c
#define wdt_off								0x245e
#define wdt_on								0x246c
/** uses space in normal ir rx buffer (0xf8f0) */
#define setHeapPointer							0x247e
/** void* r0 static_malloc(r0 size) */
#define static_malloc							0x2488
#define accountForStepTakenLikely					0x24ac
#define deviceSleep							0x256e
#define wdt_pet								0x259e
#define check_some_rtc_set_bit_and_maybe_wait				0x25ac
/** void setRandomSeed(er0 seed) */
#define setRandomSeed							0x25c8
#define rand								0x25d0
/** void decompress(u8* e0 out, u8* r0 in) */
#define decompress							0x25f6
#define enother_common_epilogue						0x2660
#define common_epilogue_5						0x266c
/** used in number rendering to add overline */
#define orr_0x0101_into_three_words					0x2680
/** void accelRegRead(r0l regno, r0h nbytes, e0 dstRamPtr)
      0x80 or'ed into regno by this func */
#define accelRegRead							0x26a0
/** void accelRegWrite(r0l regno, r0h value)
      manipulates nCS as needed */
#define accelRegWrite							0x270a
/** bool r0l accelInit() */
#define accelInit							0x273c
/** u16 checksumProtectAdcValue(u16 val)
      add values are actually only 12 bits (lower 12)
      this adds a checksum to this adc value for safer EEPROM storage
      0x0XYZ -> 0xTXYZ, where T = (X + Y + Z) & 0x0f */
#define checksumProtectAdcValue						0x27c2
/** bool r0l adcClibrationDataVerifySelfChecksum(r0 word) */
#define adcClibrationDataVerifySelfChecksum				0x27ec
/** u16 r0 adcSample() */
#define adcSample							0x281e
/** bool checkBatteryBelowGivenLevel(r0 level) */
#define checkBatteryForBelowGivenLevel					0x289a
/** void measureBatteryAndSetLowFlag() */
#define measureBatteryAndSetLowFlag					0x290a

/** void recordPokeCaughtNormal()
      gCurSubstateY has poke index on route OR somethign else...  1..3 is poke on route, 4 is event poke */
#define recordPokeCaughtNormal						0x2a96

#define interactionHandlerPokeBattle					0x2c62
#define battleScreenDraw						0x30a6
#define is_F7C4_nonzero							0x369c
#define configureSomeIoAndTimerW					0x36aa
/** void randomEepromChecksumCheck(r0l area)
      area in 0..15 */
#define randomEepromChecksumCheck					0x36f2
/** void write_F7C4_clear_F7C8_and_F7CA(r0 valueToWrite) */
#define write_F7C4_clear_F7C8_and_F7CA					0x37c6

#define setVolume							0x3832
/** void setBeeperFreq(r0l period)
      period in 32 kHz ticks */
#define setBeeperFreq							0x3838

#define timer_w_irq							0x388c
#define VECTOR_TIMER_W							0x3a4a
#define set_gCurSubstateZ_to_1						0x3a68
#define recordPokeCaughtNoEventConsideration_WEIRD			0x3a70
#define recordItemFoundNoEventConsideration_WEIRD			0x3b02
#define interactionHandlerSwitchScreen					0x3b94
#define drawCurSelectedPokeNameForSwitchScreen				0x3c0a
#define drawSwitchScreen						0x3cd8
#define drawBallFropFromTopOfScreen					0x3dbc
#define drawPokeballInMiddleOfScreen					0x3e34
#define drawCloudWithBarsOnTopAndBottomOfScreen2			0x3ece
#define drawLargePokemonImageWithBarsOnTopAndBottomOfScreen		0x3f32
#define pokemonArrivalHandler						0x3f72
#define drawItemMapStampOrRouteReceived					0x3fc6

#define interactionHandlerPokemonArrivedAnimation			0x40f8
#define drawPokemonArrivedAnimation					0x4148
#define interactionHandlerSomethingReceivedScreenDirectIrCommand	0x4178
#define drawSomethingReceivedAnimation					0x42a0
#define drawLargePokemonImageWithBarsOnTopAndBottomOfScreen2		0x42d0
#define drawCloudWithBarsOnTopAndBottomOfScreen				0x4310
#define drawMovingBlankIconWithBarsOnTopAndBottom			0x4372
#define pokemonDepartureHandler						0x43e4
#define drawPokewalkerAndCompletedMessage				0x4434
#define interactionHandlerUnknonView_0x10				0x449e
#define drawSomethignDepartingandCompletedMessage			0x44f4
#define epilogue_common_pop_r6_r5_r2					0x4534
#define common_epilogue_6						0x453c

/** void logEvent(r0 teamRouteInfoRam, e0 tmpBuf, r1l evType, r1h bool isOnSpecialEvtRoute, e1 extrainf, u8 [sp] availablePokeIdx) */
#define logEvent							0x4546

#define goToDowsingMicroApp						0x4792
#define interactionHandlerDowsing					0x47ce
/** void readSpecialItemInfo(void* r0 ramdst) */
#define readSpecialItemInfo						0x499c
/** void writeSpecialItemInfo(void* r0 ramsrc) */
#define writeSpecialItemInfo						0x49ae
#define foundSomeEventItem						0x49c0
#define pokeFoundRandomItem						0x4af2
#define dowsingStartHandleLikely					0x4b9c
#define dowsingDraw							0x4cd6
/** void checkIfPokeOrItemCanBeEncountered(r0 idx0, r1 idx1, r5 ptr)
      load LEu16 at ptr[idx0 + idx1], compare with current step counter */
#define checkIfPokeOrItemCanBeEncountered				0x4f50
#define ssuConfigure							0x4f70
#define ssu_Rx_Off							0x4f92
/** u8 r0 ssu_WaitForRx() */
#define ssu_WaitForRx							0x4fa0
/** void eepromWriteSingleByte(r0 addr, r1l val) */
#define eepromWriteSingleByte						0x4fca

/** void writeReliableDataToEeprom(r0 eepaddr0, e0 eepaddr1, r1 src, e1 size) */
#define writeReliableDataToEeprom					0x50d8
/** u8 r0l readReliableDataFromEeprom(r0 eepaddr0, e0 eepaddr1, r1 dst, e1 size)
      data is stored in two provided locations and read to RAM
      each location includes a checksum right after the data (not inluded in length)
      if only one location has checksum-valid data, other is replaced with it
      if both appear valid, #0 is assumed dominant
      if neither appears vlid, they are overwritten with 0xff, and so is the
      ram buffer,. returned checksum is also set to 0xFF */
#define readReliableDataFromEeprom					0x5128
/** void eepromWriteData(r0 eepaddr, e0 srcptr, r1 size) */
#define eepromWriteData							0x524e
/** void eepromReadToRamAlso(r0 eepaddr, e0 dstptr, r1 size) */
#define eepromReadToRam							0x5384
/** u8 r0l eepromReadSingleByte(r0 eepaddr) */
#define eepromReadSingleByte						0x552e
/** void eepromFillPageWithByte(r0 addr, r1l val) */
#define eepromFillPageWithByte						0x5634
/** void eepromFillWithByte(r0 addr, e0 size, r1l val) */
#define eepromFillWithByte						0x5742
/** void eepromWrite128Bytes(r0 eepaddr, e0 srcptr) */
#define eepromWrite128Bytes						0x5874
#define factoryTestPerformIfNeeded					0x5990
#define pokemonJoinsEmptyWalkerWalk					0x5c0a
/** ? addRandomGift(r0l gift)
      when a pokemon randomly finds something */
#define addRandomGift							0x5d52
#define interactionHandlerRandomGiftFromBoredPokemon			0x5e9e
#define showPokemonFeelingsAndRandomFindings				0x5edc
#define findRandomItem							0x5fc2

/** ? processAcceleromerSamplesAxis(r0 ptr)
      data for one axis */
#define processAcceleromerSamplesAxis					0x60da
#define goToPeerPlayMicroApp						0x632c
#define calculateAndApplyPeerGift					0x6382
/** void drawMusicNoteWithVariableShiftUp(r0l x, r0h y, r1l shiftup_px) */
#define drawMusicNoteWithVariableShiftUp				0x6582
#define drawPeerPlay							0x6574
#define seeIfWeSawThisTrainerBefore					0x6784
#define pushSeenTrainersListLogDownOne					0x67de
#define logPeerPlay							0x6816
#define setEventLoopFunc						0x693a
#define goToConnectionMicroApp						0x694c
#define setCurrentlyActiveView						0x69b8
/** void homeScreenDrawLargeCurrentPokemonImage(r0l x, r0h y) */
#define homeScreenDrawLargeCurrentPokemonImage				0x69be
#define someStateVarShuffling						0x6a1c
#define interactionHandlerHomeScreen					0x6a3e
/** void drawPokemonFeelingBubble(r0l feelingIdx) */
#define drawPokemonFeelingBubble					0x6ad8
#define drawCurrentAreaSmallImage					0x6b10

#define drawHomeScreenMain						0x6bf8

#define interactionHandlerSettings					0x6dfc
#define drawSettingsScreen						0x6e62

#define drawPokewalkerInitialConnectionInstructionScreen		0x703c
#define drawSadPokewalkerImage						0x711a
#define drawHappyPokewalkerWithActiveConnectivityAnimation		0x71a4
#define connectionStartHandler						0x722c
/** ? showCommsErrorMessage(msgid)
      1: "no trainer found"
      2,8: "cannot connect"
      3: "cannot complete this connection"
      4: "no pokemon held!"
      5: "cannot connect to trainer again"
      6: "already received this event"
      7: "could not receive" */
#define showCommsErrorMessage						0x728a
#define interactionHandler						0x7348
#define viewDoDisplay							0x7406
#define drawhomeScreenSmallIconsOnBottom				0x74bc
#define accelReadSample							0x76aa
#define sleepModeEventLoop						0x7882
#define normalModeEventLoop						0x7998
#define common_prologue_2						0x7a0a
#define common_epologue_2						0x7a2a
/** void drawImageToBuffer(r0l imgw, r0h imgH, e0 imgPtr, R1l x, r1h y, e1 dstptr, [sp] bufWidth, [sp+2] bufHeight) */
#define drawImageToBuffer						0x7a40
/** ? lcdSendSingleByteCommand(r0l cmd) */
#define lcdSendSingleByteCommand					0x7b44
#define smallDelay							0x7b64
#define initLcdUsingRomOrEepromCommands					0x7b72
/** void lcdSetContrast(u8 r0l contrast)
      incremented by base_contrast_value */
#define lcdSetContrast							0x7c24
#define lcdRelatedWTF							0x7c56
#define someLcdThingYetAgain						0x7cac
#define screenShenenigans						0x7cfa
#define lcdRelatedWTFZYX						0x7d4a
/** void lcdFillRectangle(r0l x, r0h y, r1l w, r1h h, [sp] color) */
#define lcdFillRectangle						0x7e58
#define lcdExitPowerSaveMode						0x7fb8
#define lcdEnterPowerSaveMode						0x7fda
#define someLcdRelatedThing						0x7ffc

/** void drawImageToScreen(r0l x, r0h y, e0 imgPtr, r1l imgW, r1h imgH) */
#define drawImageToScreen						0x80ac
/** void drawImageInSomeWeirdWay(r0l x, r0h y, e0 imgW, r1 imgH, e1 imgPtr) */
#define drawImageInSomeWeirdWay						0x82ea
/** void drawTinyChars(r0l x, r0h y, e0 char* text) */
#define drawTinyChars							0x858a
#define someFullLcdDrawingThing						0x8766
#define someFullLcdDrawingThin2						0x88e2
#define someDisplayNonsense						0x8a36
#define common_epilogue_4						0x8ab0
#define common_epilogue_3						0x8abc
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
#define takeItemAndPokeInventory					0x8aca

#define interactionHandlerPokemonAndItemsScreen				0x8d02
#define drawPokemonAndItemsScreen					0x8d88

#define interactionHandlerGiftedItemsScreen				0x9116
#define giftedItemsView							0x918c
#define clear_bytes_at_F8EE_F8EF_words_at_F8EA_F8E6			0x9328
#define processAccelSamplesIncrementStepCountersAndNotifyInterestedPartiesAsNeeded 0x945a
#define clear_gCurSubstateY						0x974e
#define interactionHAndlerMainMenu					0x9756
#define mainMenuDraw							0x9930
#define maybeConfigureKeys						0x9b34
#define likelyKeyDebounceRoutine					0x9b84
/** r0l checkKeyStates(r0l wanted)
      0x02: enter
      0x04: left
      0x08: right */
#define checkKeyStates							0x9c40
#define pickPokemonToEncounter						0x9c48
#define goToPokeRadarMicroApp						0x9d92
#define interactionHandlerPokeRadar					0x9e72
#define pokeRadarDraw							0x9f44

#define interactionHandlerPokeRadarFailureUserTooSlow			0xa10a
#define pokeradarUserTooSlowScreen					0xa12c
#define accelProcessDataDetectStep					0xa1a8

#define VECTOR_IRQ0							0xa300
#define VECTOR_IRQ1							0xa31c
#define VECTOR_IRQ_AEC							0xa322
#define VECTOR_ADC							0xa328
#define clampTotalStepToLimit						0xa32e

#define dayEndedRecordailyStepadnshipHistoricStepCounts			0xa45e
/** void rtcSet(er0 seconds) */
#define rtcSet								0xa4fe
/** (r0 seconds, e0 minutes, r1 hours) rtcReadBcd() */
#define rtcReadBcd							0xa54d
#define VECTOR_RTC_QUARTER_SEC						0xa65e
#define VECTOR_RTC_HALF_SEC						0xa674
#define VECTOR_RTC_EVERY_SEC						0xa682
#define VECTOR_RTC_EVERY_MIN						0xa6e2
#define VECTOR_RTC_EVERY_HOUR						0xa702
/** bool r0l eepromFactoryTest(r0 startaddr)
      'startaddr' must be a multiple of 256
      wipes all data after 'startaddr' */
#define eepromFactoryTest						0xa72a
#define rtcFactoryTest							0xa800
#define accelFactoryTest						0xa830
#define adcFactoryTestAndCalibrate					0xa8f8

#define interactionHandlerDebugMode22					0xaa6c

#define drawSomethingWithTinyChars					0xad06
#define drawSomethingWithTinyChars2					0xaefa

#define drawNG6inTinyChars						0xb0a2
#define writeNintendoStringToFlash					0xb0ae
#define checkForNintendoStringInFlash					0xb0c8
#define basicIoConfig							0xb0f2
#define wipeOutStepsAndsyncTime						0xb124
#define updateCachedWalkerStatusByteFromEeprom				0xb176
/** void some_sort_of_eeprom_init(bool r0l wipeEventBitfield, bool r0h wipeSteps) */
#define some_sort_of_eeprom_init					0xb1ae
#define checkForAndInitEepromContentsIfNeeded				0xb2e2
#define delaySomewhatAndThenSetTheRtc					0xb390
#define goToTrainerCardMicroApp						0xb3c0
#define interactionHandlerTrainerCardAndStatsScreens			0xb3cc
#define drawTrainerCard							0xb48c
#define drawStepStatisticsScreen					0xb682
#define showGoodJobBanner						0xb7ee
#define drawRewardReceivedBanner					0xb8a6
#define drawTrainerCardAndstatsScreens					0xb8f2
/** ? bitfieldInsert(u8* r0 data, r1l valToInsert, r2l nbits, r2h bitOffset)
      bitOffset == 0: modify top bits
      bitfield is 8 bit */
#define bitfieldInsert							0xb924
/** er0 = er0 / er1, er1 = er0 % er1 */
#define divmod32							0xb94e
/** void lslByteAtPtr(u8* r0 ptr, r1 shift)
      *(u8*)ptr <<= shift */
#define lslByteAtPtr							0xb98a
/** void lsrByteAtPtr(u8* r0 ptr, r1 shift)
      *(u8*)ptr >>= shift */
#define lsrByteAtPtr							0xb99c
/** er0 = er0 * er1 */
#define mul32								0xb9ae
/** void memcpy(r0 src, r1 dst, r2 len) */
#define memcpy								0xb9ce
#define common_prologue							0xba42
#define common_epologue							0xba62
#define copy_data_zero_bss						0xba78

/****** data section *********************************************************/

#define FREQTAB								0xbb4a
#define POKEWALKER_LARGE_IMAGE						0xbb74
#define POKEWALKER_NEUTRAL_FACE_IMAGE					0xbc74
#define POKEWALKER_HAPPY_FACE_IMAGE					0xbc94
#define POKEWALKER_SAD_FACE_IMAGE					0xbcb4
#define POKEWALKER_UP_ARROW_ICON					0xbcd4
#define POKEWALKER_IR_ACTIVE_ICON					0xbce4
#define TINY_CHARS							0xbcf4

#define BALL_DROP_Y_COORD						0xbd70
#define item_screen_locs						0xbd76
#define GOING_AWAY_ANIMATION_Y_COORDS					0xbd7c
#define POKEBALL_THROW_ARC_Y						0xbdd0
#define PEER_PLAY_MUSIC_NOTE_VERTICAL_MOVE_AMT				0xbe70
#define INDEX_TO_FEELING_IMAGE_MAP					0xbeb0
#define ROM_LCD_INIT_COMMANDS						0xbeb8
#define ACTIVITY_WATT_COSTS						0xbf0e
#define MAIN_MENU_ITEM_POSITIONS_Y_RELATIVE				0xbf14
#define BUSH_X_COORDINATES_IN_POKERADAR					0xbf25
#define DATA_FOR_EEPROM_HEADER						0xbf98
#define DATA_FOR_EEPROM_0x8cf0						0xbfa2
#define data_list_start							0xbfba
#define bss_list_start							0xbfc0
#define bss_list_end							0xbfc4

#define unused_flash							0xbfc8
#define FLASH_END							0xc000

#endif

