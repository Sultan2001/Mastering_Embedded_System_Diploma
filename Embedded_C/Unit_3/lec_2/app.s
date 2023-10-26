
app.o:     file format elf32-littlearm


Disassembly of section .text:

00000000 <main>:
   0:	e92d4800 	push	{fp, lr}
   4:	e28db004 	add	fp, sp, #4
   8:	e59f0008 	ldr	r0, [pc, #8]	; 18 <main+0x18>
   c:	ebfffffe 	bl	0 <Uart_send_string>
  10:	e1a00000 	nop			; (mov r0, r0)
  14:	e8bd8800 	pop	{fp, pc}
  18:	00000000 	andeq	r0, r0, r0

Disassembly of section .data:

00000000 <string_buffer>:
   0:	7261654c 	rsbvc	r6, r1, #76, 10	; 0x13000000
   4:	6e692d6e 	cdpvs	13, 6, cr2, cr9, cr14, {3}
   8:	7065642d 	rsbvc	r6, r5, sp, lsr #8
   c:	6d3a6874 	ldcvs	8, cr6, [sl, #-464]!	; 0xfffffe30
  10:	6d61686f 	stclvs	8, cr6, [r1, #-444]!	; 0xfffffe44
  14:	73206465 			; <UNDEFINED> instruction: 0x73206465
  18:	61746c75 	cmnvs	r4, r5, ror ip
  1c:	0000006e 	andeq	r0, r0, lr, rrx
	...

Disassembly of section .rodata:

00000000 <string_buffer_2>:
   0:	61686f6d 	cmnvs	r8, sp, ror #30
   4:	2064656d 	rsbcs	r6, r4, sp, ror #10
   8:	746c7573 	strbtvc	r7, [ip], #-1395	; 0xfffffa8d
   c:	00006e61 	andeq	r6, r0, r1, ror #28
	...

Disassembly of section .debug_info:

00000000 <.debug_info>:
   0:	00000090 	muleq	r0, r0, r0
   4:	00000004 	andeq	r0, r0, r4
   8:	01040000 	mrseq	r0, (UNDEF: 4)
   c:	00000029 	andeq	r0, r0, r9, lsr #32
  10:	0000f10c 	andeq	pc, r0, ip, lsl #2
  14:	00009600 	andeq	r9, r0, r0, lsl #12
  18:	00000000 	andeq	r0, r0, r0
  1c:	00001c00 	andeq	r1, r0, r0, lsl #24
  20:	00000000 	andeq	r0, r0, r0
  24:	003c0200 	eorseq	r0, ip, r0, lsl #4
  28:	00350000 	eorseq	r0, r5, r0
  2c:	35030000 	strcc	r0, [r3, #-0]
  30:	63000000 	movwvs	r0, #0
  34:	07040400 	streq	r0, [r4, -r0, lsl #8]
  38:	0000001c 	andeq	r0, r0, ip, lsl r0
  3c:	00080104 	andeq	r0, r8, r4, lsl #2
  40:	05000000 	streq	r0, [r0, #-0]
  44:	0000003c 	andeq	r0, r0, ip, lsr r0
  48:	00000e06 	andeq	r0, r0, r6, lsl #28
  4c:	0f020100 	svceq	0x00020100
  50:	00000025 	andeq	r0, r0, r5, lsr #32
  54:	00000305 	andeq	r0, r0, r5, lsl #6
  58:	43020000 	movwmi	r0, #8192	; 0x2000
  5c:	6a000000 	bvs	64 <.debug_info+0x64>
  60:	03000000 	movweq	r0, #0
  64:	00000035 	andeq	r0, r0, r5, lsr r0
  68:	5a050063 	bpl	1401fc <main+0x1401fc>
  6c:	06000000 	streq	r0, [r0], -r0
  70:	00000086 	andeq	r0, r0, r6, lsl #1
  74:	6a150301 	bvs	540c80 <main+0x540c80>
  78:	05000000 	streq	r0, [r0, #-0]
  7c:	00000003 	andeq	r0, r0, r3
  80:	00f70700 	rscseq	r0, r7, r0, lsl #14
  84:	04010000 	streq	r0, [r1], #-0
  88:	00000006 	andeq	r0, r0, r6
  8c:	00001c00 	andeq	r1, r0, r0, lsl #24
  90:	009c0100 	addseq	r0, ip, r0, lsl #2

Disassembly of section .debug_abbrev:

00000000 <.debug_abbrev>:
   0:	25011101 	strcs	r1, [r1, #-257]	; 0xfffffeff
   4:	030b130e 	movweq	r1, #45838	; 0xb30e
   8:	110e1b0e 	tstne	lr, lr, lsl #22
   c:	10061201 	andne	r1, r6, r1, lsl #4
  10:	02000017 	andeq	r0, r0, #23
  14:	13490101 	movtne	r0, #37121	; 0x9101
  18:	00001301 	andeq	r1, r0, r1, lsl #6
  1c:	49002103 	stmdbmi	r0, {r0, r1, r8, sp}
  20:	000b2f13 	andeq	r2, fp, r3, lsl pc
  24:	00240400 	eoreq	r0, r4, r0, lsl #8
  28:	0b3e0b0b 	bleq	f82c5c <main+0xf82c5c>
  2c:	00000e03 	andeq	r0, r0, r3, lsl #28
  30:	49002605 	stmdbmi	r0, {r0, r2, r9, sl, sp}
  34:	06000013 			; <UNDEFINED> instruction: 0x06000013
  38:	0e030034 	mcreq	0, 0, r0, cr3, cr4, {1}
  3c:	0b3b0b3a 	bleq	ec2d2c <main+0xec2d2c>
  40:	13490b39 	movtne	r0, #39737	; 0x9b39
  44:	1802193f 	stmdane	r2, {r0, r1, r2, r3, r4, r5, r8, fp, ip}
  48:	2e070000 	cdpcs	0, 0, cr0, cr7, cr0, {0}
  4c:	03193f00 	tsteq	r9, #0, 30
  50:	3b0b3a0e 	blcc	2ce890 <main+0x2ce890>
  54:	110b390b 	tstne	fp, fp, lsl #18
  58:	40061201 	andmi	r1, r6, r1, lsl #4
  5c:	19429618 	stmdbne	r2, {r3, r4, r9, sl, ip, pc}^
  60:	Address 0x00000060 is out of bounds.


Disassembly of section .debug_aranges:

00000000 <.debug_aranges>:
   0:	0000001c 	andeq	r0, r0, ip, lsl r0
   4:	00000002 	andeq	r0, r0, r2
   8:	00040000 	andeq	r0, r4, r0
	...
  14:	0000001c 	andeq	r0, r0, ip, lsl r0
	...

Disassembly of section .debug_line:

00000000 <.debug_line>:
   0:	00000037 	andeq	r0, r0, r7, lsr r0
   4:	001c0003 	andseq	r0, ip, r3
   8:	01020000 	mrseq	r0, (UNDEF: 2)
   c:	000d0efb 	strdeq	r0, [sp], -fp
  10:	01010101 	tsteq	r1, r1, lsl #2
  14:	01000000 	mrseq	r0, (UNDEF: 0)
  18:	00010000 	andeq	r0, r1, r0
  1c:	2e707061 	cdpcs	0, 7, cr7, cr0, cr1, {3}
  20:	00000063 	andeq	r0, r0, r3, rrx
  24:	01050000 	mrseq	r0, (UNDEF: 5)
  28:	00020500 	andeq	r0, r2, r0, lsl #10
  2c:	16000000 	strne	r0, [r0], -r0
  30:	054b0205 	strbeq	r0, [fp, #-517]	; 0xfffffdfb
  34:	06024b01 	streq	r4, [r2], -r1, lsl #22
  38:	Address 0x00000038 is out of bounds.


Disassembly of section .debug_str:

00000000 <.debug_str>:
   0:	69736e75 	ldmdbvs	r3!, {r0, r2, r4, r5, r6, r9, sl, fp, sp, lr}^
   4:	64656e67 	strbtvs	r6, [r5], #-3687	; 0xfffff199
   8:	61686320 	cmnvs	r8, r0, lsr #6
   c:	74730072 	ldrbtvc	r0, [r3], #-114	; 0xffffff8e
  10:	676e6972 			; <UNDEFINED> instruction: 0x676e6972
  14:	6675625f 			; <UNDEFINED> instruction: 0x6675625f
  18:	00726566 	rsbseq	r6, r2, r6, ror #10
  1c:	69736e75 	ldmdbvs	r3!, {r0, r2, r4, r5, r6, r9, sl, fp, sp, lr}^
  20:	64656e67 	strbtvs	r6, [r5], #-3687	; 0xfffff199
  24:	746e6920 	strbtvc	r6, [lr], #-2336	; 0xfffff6e0
  28:	554e4700 	strbpl	r4, [lr, #-1792]	; 0xfffff900
  2c:	37314320 	ldrcc	r4, [r1, -r0, lsr #6]!
  30:	2e303120 	rsfcssp	f3, f0, f0
  34:	20312e33 	eorscs	r2, r1, r3, lsr lr
  38:	31323032 	teqcc	r2, r2, lsr r0
  3c:	34323830 	ldrtcc	r3, [r2], #-2096	; 0xfffff7d0
  40:	65722820 	ldrbvs	r2, [r2, #-2080]!	; 0xfffff7e0
  44:	7361656c 	cmnvc	r1, #108, 10	; 0x1b000000
  48:	2d202965 			; <UNDEFINED> instruction: 0x2d202965
  4c:	7570636d 	ldrbvc	r6, [r0, #-877]!	; 0xfffffc93
  50:	6d72613d 	ldfvse	f6, [r2, #-244]!	; 0xffffff0c
  54:	65363239 	ldrvs	r3, [r6, #-569]!	; 0xfffffdc7
  58:	20732d6a 	rsbscs	r2, r3, sl, ror #26
  5c:	6c666d2d 	stclvs	13, cr6, [r6], #-180	; 0xffffff4c
  60:	2d74616f 	ldfcse	f6, [r4, #-444]!	; 0xfffffe44
  64:	3d696261 	sfmcc	f6, 2, [r9, #-388]!	; 0xfffffe7c
  68:	74666f73 	strbtvc	r6, [r6], #-3955	; 0xfffff08d
  6c:	616d2d20 	cmnvs	sp, r0, lsr #26
  70:	2d206d72 	stccs	13, cr6, [r0, #-456]!	; 0xfffffe38
  74:	6372616d 	cmnvs	r2, #1073741851	; 0x4000001b
  78:	72613d68 	rsbvc	r3, r1, #104, 26	; 0x1a00
  7c:	7435766d 	ldrtvc	r7, [r5], #-1645	; 0xfffff993
  80:	2d206a65 	vstmdbcs	r0!, {s12-s112}
  84:	74730067 	ldrbtvc	r0, [r3], #-103	; 0xffffff99
  88:	676e6972 			; <UNDEFINED> instruction: 0x676e6972
  8c:	6675625f 			; <UNDEFINED> instruction: 0x6675625f
  90:	5f726566 	svcpl	0x00726566
  94:	3a430032 	bcc	10c0164 <main+0x10c0164>
  98:	6573555c 	ldrbvs	r5, [r3, #-1372]!	; 0xfffffaa4
  9c:	6d5c7372 	ldclvs	3, cr7, [ip, #-456]	; 0xfffffe38
  a0:	6d61686f 	stclvs	8, cr6, [r1, #-444]!	; 0xfffffe44
  a4:	75736465 	ldrbvc	r6, [r3, #-1125]!	; 0xfffffb9b
  a8:	6e61746c 	cdpvs	4, 6, cr7, cr1, cr12, {3}
  ac:	636f445c 	cmnvs	pc, #92, 8	; 0x5c000000
  b0:	6e656d75 	mcrvs	13, 3, r6, cr5, cr5, {3}
  b4:	4d5c7374 	ldclmi	3, cr7, [ip, #-464]	; 0xfffffe30
  b8:	65747361 	ldrbvs	r7, [r4, #-865]!	; 0xfffffc9f
  bc:	676e6972 			; <UNDEFINED> instruction: 0x676e6972
  c0:	626d455f 	rsbvs	r4, sp, #398458880	; 0x17c00000
  c4:	65646465 	strbvs	r6, [r4, #-1125]!	; 0xfffffb9b
  c8:	79535f64 	ldmdbvc	r3, {r2, r5, r6, r8, r9, sl, fp, ip, lr}^
  cc:	6d657473 	cfstrdvs	mvd7, [r5, #-460]!	; 0xfffffe34
  d0:	7069445f 	rsbvc	r4, r9, pc, asr r4
  d4:	616d6f6c 	cmnvs	sp, ip, ror #30
  d8:	626d455c 	rsbvs	r4, sp, #92, 10	; 0x17000000
  dc:	65646465 	strbvs	r6, [r4, #-1125]!	; 0xfffffb9b
  e0:	5c435f64 	mcrrpl	15, 6, r5, r3, cr4
  e4:	74696e55 	strbtvc	r6, [r9], #-3669	; 0xfffff1ab
  e8:	6c5c335f 	mrrcvs	3, 5, r3, ip, cr15
  ec:	325f6365 	subscc	r6, pc, #-1811939327	; 0x94000001
  f0:	70706100 	rsbsvc	r6, r0, r0, lsl #2
  f4:	6d00632e 	stcvs	3, cr6, [r0, #-184]	; 0xffffff48
  f8:	006e6961 	rsbeq	r6, lr, r1, ror #18

Disassembly of section .comment:

00000000 <.comment>:
   0:	43434700 	movtmi	r4, #14080	; 0x3700
   4:	4728203a 			; <UNDEFINED> instruction: 0x4728203a
   8:	4120554e 			; <UNDEFINED> instruction: 0x4120554e
   c:	45206d72 	strmi	r6, [r0, #-3442]!	; 0xfffff28e
  10:	6465626d 	strbtvs	r6, [r5], #-621	; 0xfffffd93
  14:	20646564 	rsbcs	r6, r4, r4, ror #10
  18:	6c6f6f54 	stclvs	15, cr6, [pc], #-336	; fffffed0 <main+0xfffffed0>
  1c:	69616863 	stmdbvs	r1!, {r0, r1, r5, r6, fp, sp, lr}^
  20:	3031206e 	eorscc	r2, r1, lr, rrx
  24:	322d332e 	eorcc	r3, sp, #-1207959552	; 0xb8000000
  28:	2e313230 	mrccs	2, 1, r3, cr1, cr0, {1}
  2c:	20293031 	eorcs	r3, r9, r1, lsr r0
  30:	332e3031 			; <UNDEFINED> instruction: 0x332e3031
  34:	3220312e 	eorcc	r3, r0, #-2147483637	; 0x8000000b
  38:	30313230 	eorscc	r3, r1, r0, lsr r2
  3c:	20343238 	eorscs	r3, r4, r8, lsr r2
  40:	6c657228 	sfmvs	f7, 2, [r5], #-160	; 0xffffff60
  44:	65736165 	ldrbvs	r6, [r3, #-357]!	; 0xfffffe9b
  48:	Address 0x00000048 is out of bounds.


Disassembly of section .debug_frame:

00000000 <.debug_frame>:
   0:	0000000c 	andeq	r0, r0, ip
   4:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
   8:	7c020001 	stcvc	0, cr0, [r2], {1}
   c:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  10:	00000018 	andeq	r0, r0, r8, lsl r0
	...
  1c:	0000001c 	andeq	r0, r0, ip, lsl r0
  20:	8b080e42 	blhi	203930 <main+0x203930>
  24:	42018e02 	andmi	r8, r1, #2, 28
  28:	00040b0c 	andeq	r0, r4, ip, lsl #22

Disassembly of section .ARM.attributes:

00000000 <.ARM.attributes>:
   0:	00002b41 	andeq	r2, r0, r1, asr #22
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	00000021 	andeq	r0, r0, r1, lsr #32
  10:	45543505 	ldrbmi	r3, [r4, #-1285]	; 0xfffffafb
  14:	0506004a 	streq	r0, [r6, #-74]	; 0xffffffb6
  18:	01090108 	tsteq	r9, r8, lsl #2
  1c:	01140412 	tsteq	r4, r2, lsl r4
  20:	03170115 	tsteq	r7, #1073741829	; 0x40000005
  24:	01190118 	tsteq	r9, r8, lsl r1
  28:	061e011a 			; <UNDEFINED> instruction: 0x061e011a
