	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 0	sdk_version 15, 2
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #80
	stp	x29, x30, [sp, #64]             ; 16-byte Folded Spill
	add	x29, sp, #64
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	wzr, [x29, #-4]
	mov	x9, sp
	sub	x8, x29, #8
	str	x8, [x9]
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	bl	_scanf
	b	LBB0_1
LBB0_1:                                 ; =>This Inner Loop Header: Depth=1
	mov	x9, sp
	sub	x8, x29, #12
	str	x8, [x9]
	sub	x8, x29, #16
	str	x8, [x9, #8]
	adrp	x0, l_.str.1@PAGE
	add	x0, x0, l_.str.1@PAGEOFF
	bl	_scanf
	ldur	w8, [x29, #-12]
	adds	w8, w8, #1
	cset	w8, ne
	mov	w9, #0                          ; =0x0
	stur	w9, [x29, #-24]                 ; 4-byte Folded Spill
	tbnz	w8, #0, LBB0_3
	b	LBB0_2
LBB0_2:                                 ;   in Loop: Header=BB0_1 Depth=1
	ldur	w8, [x29, #-16]
	adds	w8, w8, #1
	cset	w8, eq
	stur	w8, [x29, #-24]                 ; 4-byte Folded Spill
	b	LBB0_3
LBB0_3:                                 ;   in Loop: Header=BB0_1 Depth=1
	ldur	w8, [x29, #-24]                 ; 4-byte Folded Reload
	tbnz	w8, #0, LBB0_7
	b	LBB0_4
LBB0_4:                                 ;   in Loop: Header=BB0_1 Depth=1
	sub	x8, x29, #12
	str	x8, [sp, #24]                   ; 8-byte Folded Spill
	ldur	w8, [x29, #-12]
	adrp	x9, _idx@PAGE
	ldr	w10, [x9, _idx@PAGEOFF]
	add	w11, w10, #1
	str	w11, [x9, _idx@PAGEOFF]
	adrp	x10, _price@PAGE
	add	x10, x10, _price@PAGEOFF
	str	w8, [x10, w11, sxtw #2]
	sub	x1, x29, #16
	ldur	w8, [x29, #-16]
	ldrsw	x10, [x9, _idx@PAGEOFF]
	adrp	x9, _xiaoliang@PAGE
	add	x9, x9, _xiaoliang@PAGEOFF
	str	w8, [x9, x10, lsl #2]
	adrp	x8, _x@PAGE
	str	x8, [sp, #16]                   ; 8-byte Folded Spill
	adrp	x0, _x@PAGE
	add	x0, x0, _x@PAGEOFF
	bl	__ZNSt3__13maxB8ne180100IiEERKT_S3_S3_
	ldr	x9, [sp, #16]                   ; 8-byte Folded Reload
	ldr	x1, [sp, #24]                   ; 8-byte Folded Reload
	ldr	w8, [x0]
	str	w8, [x9, _x@PAGEOFF]
	adrp	x8, _p@PAGE
	str	x8, [sp, #32]                   ; 8-byte Folded Spill
	adrp	x0, _p@PAGE
	add	x0, x0, _p@PAGEOFF
	bl	__ZNSt3__13minB8ne180100IiEERKT_S3_S3_
	ldr	x9, [sp, #32]                   ; 8-byte Folded Reload
	ldr	w8, [x0]
	str	w8, [x9, _p@PAGEOFF]
	ldur	w8, [x29, #-12]
	ldur	w9, [x29, #-16]
	mul	w8, w8, w9
	adrp	x9, _ans@PAGE
	ldr	w9, [x9, _ans@PAGEOFF]
	subs	w8, w8, w9
	cset	w8, lt
	tbnz	w8, #0, LBB0_6
	b	LBB0_5
LBB0_5:                                 ;   in Loop: Header=BB0_1 Depth=1
	ldur	w8, [x29, #-12]
	adrp	x9, _ansa@PAGE
	str	w8, [x9, _ansa@PAGEOFF]
	ldur	w8, [x29, #-16]
	adrp	x9, _ansb@PAGE
	str	w8, [x9, _ansb@PAGEOFF]
	ldur	w8, [x29, #-12]
	ldur	w9, [x29, #-16]
	mul	w8, w8, w9
	adrp	x9, _ans@PAGE
	str	w8, [x9, _ans@PAGEOFF]
	b	LBB0_6
LBB0_6:                                 ;   in Loop: Header=BB0_1 Depth=1
	b	LBB0_1
LBB0_7:
	mov	x9, sp
	sub	x8, x29, #20
	str	x8, [x9]
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	bl	_scanf
	b	LBB0_8
LBB0_8:                                 ; =>This Inner Loop Header: Depth=1
	adrp	x8, _x@PAGE
	ldr	w8, [x8, _x@PAGEOFF]
	subs	w8, w8, #0
	cset	w8, lt
	tbnz	w8, #0, LBB0_12
	b	LBB0_9
LBB0_9:                                 ;   in Loop: Header=BB0_8 Depth=1
	adrp	x9, _p@PAGE
	ldr	w8, [x9, _p@PAGEOFF]
	add	w8, w8, #1
	str	w8, [x9, _p@PAGEOFF]
	ldur	w11, [x29, #-20]
	adrp	x8, _x@PAGE
	ldr	w10, [x8, _x@PAGEOFF]
	subs	w10, w10, w11
	str	w10, [x8, _x@PAGEOFF]
	ldr	w8, [x8, _x@PAGEOFF]
	ldr	w9, [x9, _p@PAGEOFF]
	mul	w8, w8, w9
	adrp	x9, _ans@PAGE
	ldr	w9, [x9, _ans@PAGEOFF]
	subs	w8, w8, w9
	cset	w8, lt
	tbnz	w8, #0, LBB0_11
	b	LBB0_10
LBB0_10:                                ;   in Loop: Header=BB0_8 Depth=1
	adrp	x9, _p@PAGE
	ldr	w8, [x9, _p@PAGEOFF]
	adrp	x10, _ansa@PAGE
	str	w8, [x10, _ansa@PAGEOFF]
	adrp	x8, _x@PAGE
	ldr	w10, [x8, _x@PAGEOFF]
	adrp	x11, _ansb@PAGE
	str	w10, [x11, _ansb@PAGEOFF]
	ldr	w8, [x8, _x@PAGEOFF]
	ldr	w9, [x9, _p@PAGEOFF]
	mul	w8, w8, w9
	adrp	x9, _ans@PAGE
	str	w8, [x9, _ans@PAGEOFF]
	b	LBB0_11
LBB0_11:                                ;   in Loop: Header=BB0_8 Depth=1
	b	LBB0_8
LBB0_12:
	adrp	x8, _ansa@PAGE
	ldr	w8, [x8, _ansa@PAGEOFF]
	ldur	w9, [x29, #-8]
	subs	w10, w8, w9
	mov	x9, sp
                                        ; implicit-def: $x8
	mov	x8, x10
	str	x8, [x9]
	adrp	x0, l_.str.2@PAGE
	add	x0, x0, l_.str.2@PAGEOFF
	bl	_printf
	mov	w0, #0                          ; =0x0
	ldp	x29, x30, [sp, #64]             ; 16-byte Folded Reload
	add	sp, sp, #80
	ret
	.cfi_endproc
                                        ; -- End function
	.private_extern	__ZNSt3__13maxB8ne180100IiEERKT_S3_S3_ ; -- Begin function _ZNSt3__13maxB8ne180100IiEERKT_S3_S3_
	.globl	__ZNSt3__13maxB8ne180100IiEERKT_S3_S3_
	.weak_definition	__ZNSt3__13maxB8ne180100IiEERKT_S3_S3_
	.p2align	2
__ZNSt3__13maxB8ne180100IiEERKT_S3_S3_: ; @_ZNSt3__13maxB8ne180100IiEERKT_S3_S3_
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	str	x1, [sp, #16]
	ldur	x0, [x29, #-8]
	ldr	x1, [sp, #16]
	bl	__ZNSt3__13maxB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.private_extern	__ZNSt3__13minB8ne180100IiEERKT_S3_S3_ ; -- Begin function _ZNSt3__13minB8ne180100IiEERKT_S3_S3_
	.globl	__ZNSt3__13minB8ne180100IiEERKT_S3_S3_
	.weak_definition	__ZNSt3__13minB8ne180100IiEERKT_S3_S3_
	.p2align	2
__ZNSt3__13minB8ne180100IiEERKT_S3_S3_: ; @_ZNSt3__13minB8ne180100IiEERKT_S3_S3_
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	str	x1, [sp, #16]
	ldur	x0, [x29, #-8]
	ldr	x1, [sp, #16]
	bl	__ZNSt3__13minB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.private_extern	__ZNSt3__13maxB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_ ; -- Begin function _ZNSt3__13maxB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_
	.globl	__ZNSt3__13maxB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_
	.weak_definition	__ZNSt3__13maxB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_
	.p2align	2
__ZNSt3__13maxB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_: ; @_ZNSt3__13maxB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	str	x0, [sp, #16]
	str	x1, [sp, #8]
	ldr	x1, [sp, #16]
	ldr	x2, [sp, #8]
	sub	x0, x29, #1
	bl	__ZNKSt3__16__lessIvvEclB8ne180100IiiEEbRKT_RKT0_
	tbz	w0, #0, LBB3_2
	b	LBB3_1
LBB3_1:
	ldr	x8, [sp, #8]
	str	x8, [sp]                        ; 8-byte Folded Spill
	b	LBB3_3
LBB3_2:
	ldr	x8, [sp, #16]
	str	x8, [sp]                        ; 8-byte Folded Spill
	b	LBB3_3
LBB3_3:
	ldr	x0, [sp]                        ; 8-byte Folded Reload
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.private_extern	__ZNKSt3__16__lessIvvEclB8ne180100IiiEEbRKT_RKT0_ ; -- Begin function _ZNKSt3__16__lessIvvEclB8ne180100IiiEEbRKT_RKT0_
	.globl	__ZNKSt3__16__lessIvvEclB8ne180100IiiEEbRKT_RKT0_
	.weak_definition	__ZNKSt3__16__lessIvvEclB8ne180100IiiEEbRKT_RKT0_
	.p2align	2
__ZNKSt3__16__lessIvvEclB8ne180100IiiEEbRKT_RKT0_: ; @_ZNKSt3__16__lessIvvEclB8ne180100IiiEEbRKT_RKT0_
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	str	x0, [sp, #24]
	str	x1, [sp, #16]
	str	x2, [sp, #8]
	ldr	x8, [sp, #16]
	ldr	w8, [x8]
	ldr	x9, [sp, #8]
	ldr	w9, [x9]
	subs	w8, w8, w9
	cset	w8, lt
	and	w0, w8, #0x1
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.private_extern	__ZNSt3__13minB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_ ; -- Begin function _ZNSt3__13minB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_
	.globl	__ZNSt3__13minB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_
	.weak_definition	__ZNSt3__13minB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_
	.p2align	2
__ZNSt3__13minB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_: ; @_ZNSt3__13minB8ne180100IiNS_6__lessIvvEEEERKT_S5_S5_T0_
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	str	x0, [sp, #16]
	str	x1, [sp, #8]
	ldr	x1, [sp, #8]
	ldr	x2, [sp, #16]
	sub	x0, x29, #1
	bl	__ZNKSt3__16__lessIvvEclB8ne180100IiiEEbRKT_RKT0_
	tbz	w0, #0, LBB5_2
	b	LBB5_1
LBB5_1:
	ldr	x8, [sp, #8]
	str	x8, [sp]                        ; 8-byte Folded Spill
	b	LBB5_3
LBB5_2:
	ldr	x8, [sp, #16]
	str	x8, [sp]                        ; 8-byte Folded Spill
	b	LBB5_3
LBB5_3:
	ldr	x0, [sp]                        ; 8-byte Folded Reload
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_price                          ; @price
.zerofill __DATA,__common,_price,400040,2
	.globl	_xiaoliang                      ; @xiaoliang
.zerofill __DATA,__common,_xiaoliang,400040,2
	.globl	_idx                            ; @idx
.zerofill __DATA,__common,_idx,4,2
	.globl	_x                              ; @x
.zerofill __DATA,__common,_x,4,2
	.globl	_p                              ; @p
.zerofill __DATA,__common,_p,4,2
	.globl	_ansa                           ; @ansa
.zerofill __DATA,__common,_ansa,4,2
	.globl	_ansb                           ; @ansb
.zerofill __DATA,__common,_ansb,4,2
	.globl	_ans                            ; @ans
.zerofill __DATA,__common,_ans,4,2
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"%d"

l_.str.1:                               ; @.str.1
	.asciz	"%d%d"

l_.str.2:                               ; @.str.2
	.asciz	"%d\n"

.subsections_via_symbols
