/* vim: set ft=gas ts=8: */

.ifndef _POKEWALKER_PWIO_DEFS_H_
.set _POKEWALKER_PWIO_DEFS_H_, 0

/******* IO1 *****************************************************************/

/* ROM */
.set FLMCR1,	0xf020
.set FLMCR2,	0xf021
.set FLPWCR,	0xf022
.set EBR1,	0xf023
.set FENR,	0xf02b

/* RTC */
.set RTCFLG,	0xf067
.set RSECDR,	0xf068
.set RMINDR,	0xf069
.set RHRDR,	0xf06a
.set RWKDR,	0xf06b
.set RTCCR1,	0xf06c
.set RTCCR2,	0xf06d
.set RTCCSR,	0xf06f

/* IIC2 */
.set ICCR1,	0xf078
.set ICCR2,	0xf079
.set ICMR,	0xf07a
.set ICIER,	0xf07b
.set ICSR,	0xf07c
.set SAR,	0xf07d
.set ICDRT,	0xf07e
.set ICDRR,	0xf07f

/* system */
.set PFCR,	0xf085
/* IO ports */
.set PUCR8,	0xf086
.set PUCR9,	0xf087
.set PODR9,	0xf08c

/* timer B1 */
.set TMB1,	0xf0d0
.set TCB1,	0xf0d1
.set TLB1,	0xf0d1

/* comparator */
.set CMCR0,	0xf0dc
.set CMCR1,	0xf0dd
.set CMDR,	0xf0de

/* SSU */
.set SSCRH,	0xf0e0
.set SSCRL,	0xf0e1
.set SSCR,	0xf0e0
.set SSMR,	0xf0e2
.set SSER,	0xf0e3
.set SSSR,	0xf0e4
.set SSRDR,	0xf0e9
.set SSTDR,	0xf0eb

/* timer W */
.set TMRW,	0xf0f0
.set TCRW,	0xf0f1
.set TIERW,	0xf0f2
.set TSRW,	0xf0f3
.set TIOR0,	0xf0f4
.set TIOR1,	0xf0f5
.set TCNT,	0xf0f6
.set GRA,	0xf0f8
.set GRB,	0xf0fa
.set GRC,	0xf0fc
.set GRD,	0xf0fe

/******* IO2 *****************************************************************/

/* AEC */
.set ECPWCR,	0xff8c
.set ECPWDR,	0xff8e
.set SPCR,	0xff91
.set AESGR,	0xff92
.set ECCR,	0xff94
.set ECCSR,	0xff95
.set ECH,	0xff96
.set ECL,	0xff97
.set EC,	0xff96

/* SCI3/IrDA */
.set SMR3,	0xff98
.set TDR3,	0xff9b
.set SSR3,	0xff9c
.set RDR3,	0xff9d
.set SEMR,	0xffa6
.set IrCR,	0xffa7

/* WDT */
.set TMWD,	0xffb0
.set TCSRWD1,	0xffb1
.set TCSRWD2,	0xffb2
.set TCDW,	0xffb3

/* A/D converter */
.set ADRR,	0xffbc
.set AMR,	0xffbe
.set ADSR,	0xffbf

/* IO ports */
.set PMR1,	0xffc0
.set PMR3,	0xffc2
.set PMRB,	0xffca
.set PDR1,	0xffd4
.set PDR3,	0xffd6
.set PDR8,	0xffdb
.set PDR9,	0xffdc
.set PDRB,	0xffde
.set PUCR1,	0xffe0
.set PUCR3,	0xffe1
.set PCR1,	0xffe4
.set PCR3,	0xffe6
.set PCR8,	0xffeb
.set PCR9,	0xffec

/* system, interrupts */
.set SYSCR1,	0xfff0
.set SYSCR2,	0xfff1
.set SYSCR,	0xfff0
.set IEGR,	0xfff2
.set IENR1,	0xfff3
.set IENR2,	0xfff4
.set OSCCR,	0xfff5
.set IRR1,	0xfff6
.set IRR2,	0xfff7
.set CKSTPR1,	0xfffa
.set CKSTPR2,	0xfffb
.set CKSTPR,	0xfffa

.endif

