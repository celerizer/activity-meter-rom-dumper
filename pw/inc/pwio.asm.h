/* vim: set ts=8: */

#ifndef _POKEWALKER_PWIO_DEFS_H_
#define _POKEWALKER_PWIO_DEFS_H_

/******* IO1 *****************************************************************/

/* ROM */
#define FLMCR1	0xf020
#define FLMCR2	0xf021
#define FLPWCR	0xf022
#define EBR1	0xf023
#define FENR	0xf02b

/* RTC */
#define RTCFLG	0xf067
#define RSECDR	0xf068
#define RMINDR	0xf069
#define RHRDR	0xf06a
#define RWKDR	0xf06b
#define RTCCR1	0xf06c
#define RTCCR2	0xf06d
#define RTCCSR	0xf06f

/* IIC2 */
#define ICCR1	0xf078
#define ICCR2	0xf079
#define ICMR	0xf07a
#define ICIER	0xf07b
#define ICSR	0xf07c
#define SAR	0xf07d
#define ICDRT	0xf07e
#define ICDRR	0xf07f

/* system */
#define PFCR	0xf085
/* IO ports */
#define PUCR8	0xf086
#define PUCR9	0xf087
#define PODR9	0xf08c

/* timer B1 */
#define TMB1	0xf0d0
#define TCB1	0xf0d1
#define TLB1	0xf0d1

/* comparator */
#define CMCR0	0xf0dc
#define CMCR1	0xf0dd
#define CMDR	0xf0de

/* SSU */
#define SSCRH	0xf0e0
#define SSCRL	0xf0e1
#define SSCR	0xf0e0
#define SSMR	0xf0e2
#define SSER	0xf0e3
#define SSSR	0xf0e4
#define SSRDR	0xf0e9
#define SSTDR	0xf0eb

/* timer W */
#define TMRW	0xf0f0
#define TCRW	0xf0f1
#define TIERW	0xf0f2
#define TSRW	0xf0f3
#define TIOR0	0xf0f4
#define TIOR1	0xf0f5
#define TCNT	0xf0f6
#define GRA	0xf0f8
#define GRB	0xf0fa
#define GRC	0xf0fc
#define GRD	0xf0fe

/******* IO2 *****************************************************************/

/* AEC */
#define ECPWCR	0xff8c
#define ECPWDR	0xff8e
#define SPCR	0xff91
#define AESGR	0xff92
#define ECCR	0xff94
#define ECCSR	0xff95
#define ECH	0xff96
#define ECL	0xff97
#define EC	0xff96

/* SCI3/IrDA */
#define SMR3	0xff98
#define TDR3	0xff9b
#define SSR3	0xff9c
#define RDR3	0xff9d
#define SEMR	0xffa6
#define IrCR	0xffa7

/* WDT */
#define TMWD	0xffb0
#define TCSRWD1	0xffb1
#define TCSRWD2	0xffb2
#define TCDW	0xffb3

/* A/D converter */
#define ADRR	0xffbc
#define AMR	0xffbe
#define ADSR	0xffbf

/* IO ports */
#define PMR1	0xffc0
#define PMR3	0xffc2
#define PMRB	0xffca
#define PDR1	0xffd4
#define PDR3	0xffd6
#define PDR8	0xffdb
#define PDR9	0xffdc
#define PDRB	0xffde
#define PUCR1	0xffe0
#define PUCR3	0xffe1
#define PCR1	0xffe4
#define PCR3	0xffe6
#define PCR8	0xffeb
#define PCR9	0xffec

/* system, interrupts */
#define SYSCR1	0xfff0
#define SYSCR2	0xfff1
#define SYSCR	0xfff0
#define IEGR	0xfff2
#define IENR1	0xfff3
#define IENR2	0xfff4
#define OSCCR	0xfff5
#define IRR1	0xfff6
#define IRR2	0xfff7
#define CKSTPR1	0xfffa
#define CKSTPR2	0xfffb
#define CKSTPR	0xfffa

#endif

