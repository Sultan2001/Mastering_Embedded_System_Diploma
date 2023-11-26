



.section .vectors
.word 0x20001000     /* stack top address */
.word _reset             /* 1 reset  */
.word Vector_handler    /* 2 NMI  */
.word Vector_handler    /* 3 Hard Fault  */
.word Vector_handler    /* 4 Bus Fault  */
.word Vector_handler    /* 5 usage Fault  */
.word Vector_handler    /* 6 Reserved */
.word Vector_handler    /* 7 Reserved */
.word Vector_handler    /* 8 Reserved */
.word Vector_handler    /* 9 Reserved */


.section .text
_reset :
	bl main
	b .
.thumb_func
Vector_handler :
	b _reset
