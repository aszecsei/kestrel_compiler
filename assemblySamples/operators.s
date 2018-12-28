	.arch armv6
	.eabi_attribute 27, 3	@ Tag_ABI_HardFP_use
	.eabi_attribute 28, 1	@ Tag_ABI_VFP_args
	.fpu vfp
	.eabi_attribute 20, 1	@ Tag_ABI_FP_denormal
	.eabi_attribute 21, 1	@ Tag_ABI_FP_exceptions
	.eabi_attribute 23, 3	@ Tag_ABI_FP_number_model
	.eabi_attribute 24, 1	@ Tag_ABI_align8_needed
	.eabi_attribute 25, 1	@ Tag_ABI_align8_preserved
	.eabi_attribute 26, 2	@ Tag_ABI_enum_size
	.eabi_attribute 30, 6	@ Tag_ABI_optimization_goals
	.eabi_attribute 34, 1	@ Tag_CPU_unaligned_access
	.eabi_attribute 18, 4	@ Tag_ABI_PCS_wchar_t
	.file	"operators.c"
@ GNU C (Raspbian 4.9.2-10) version 4.9.2 (arm-linux-gnueabihf)
@	compiled by GNU C version 4.9.2, GMP version 6.0.0, MPFR version 3.1.2-p3, MPC version 1.0.2
@ GGC heuristics: --param ggc-min-expand=93 --param ggc-min-heapsize=118468
@ options passed:  -imultilib . -imultiarch arm-linux-gnueabihf operators.c
@ -march=armv6 -mfloat-abi=hard -mfpu=vfp -mtls-dialect=gnu -std=c99
@ -fno-asynchronous-unwind-tables -fverbose-asm
@ options enabled:  -faggressive-loop-optimizations -fauto-inc-dec -fcommon
@ -fdelete-null-pointer-checks -fdwarf2-cfi-asm -fearly-inlining
@ -feliminate-unused-debug-types -ffunction-cse -fgcse-lm -fgnu-runtime
@ -fgnu-unique -fident -finline-atomics -fira-hoist-pressure
@ -fira-share-save-slots -fira-share-spill-slots -fivopts
@ -fkeep-static-consts -fleading-underscore -fmath-errno
@ -fmerge-debug-strings -fpeephole -fprefetch-loop-arrays
@ -freg-struct-return -fsched-critical-path-heuristic
@ -fsched-dep-count-heuristic -fsched-group-heuristic -fsched-interblock
@ -fsched-last-insn-heuristic -fsched-rank-heuristic -fsched-spec
@ -fsched-spec-insn-heuristic -fsched-stalled-insns-dep -fshow-column
@ -fsigned-zeros -fsplit-ivs-in-unroller -fstrict-volatile-bitfields
@ -fsync-libcalls -ftrapping-math -ftree-coalesce-vars -ftree-cselim
@ -ftree-forwprop -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
@ -ftree-loop-optimize -ftree-parallelize-loops= -ftree-phiprop
@ -ftree-reassoc -ftree-scev-cprop -funit-at-a-time -fverbose-asm
@ -fzero-initialized-in-bss -marm -mglibc -mlittle-endian -mlra
@ -mpic-data-is-text-relative -msched-prolog -munaligned-access
@ -mvectorize-with-neon-quad

	.section	.rodata
	.align	2
.LC0:
	.ascii	"%d + %d = %d\012\000"
	.align	2
.LC1:
	.ascii	"%d - %d = %d\012\000"
	.align	2
.LC2:
	.ascii	"%d | %d = %d\012\000"
	.align	2
.LC3:
	.ascii	"%d * %d = %d\012\000"
	.global	__aeabi_idiv
	.align	2
.LC4:
	.ascii	"%d / %d = %d\012\000"
	.global	__aeabi_idivmod
	.align	2
.LC5:
	.ascii	"%d %% %d = %d\012\000"
	.align	2
.LC6:
	.ascii	"%d & %d = %d\012\000"
	.align	2
.LC7:
	.ascii	"-(%d + %d) = %d\012\000"
	.align	2
.LC8:
	.ascii	"~(%d + %d) = %d\012\000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}	@,
	add	fp, sp, #4	@,,
	sub	sp, sp, #16	@,,
	mov	r3, #1	@ tmp114,
	str	r3, [fp, #-8]	@ tmp114, i
	mov	r3, #2	@ tmp115,
	str	r3, [fp, #-12]	@ tmp115, j
	mov	r3, #0	@ tmp116,
	str	r3, [fp, #-16]	@ tmp116, k
	ldr	r2, [fp, #-8]	@ tmp118, i
	ldr	r3, [fp, #-12]	@ tmp119, j
	add	r3, r2, r3	@ tmp117, tmp118, tmp119
	str	r3, [fp, #-16]	@ tmp117, k
	ldr	r0, .L3	@,
	ldr	r1, [fp, #-8]	@, i
	ldr	r2, [fp, #-12]	@, j
	ldr	r3, [fp, #-16]	@, k
	bl	printf	@
	ldr	r2, [fp, #-8]	@ tmp121, i
	ldr	r3, [fp, #-12]	@ tmp122, j
	rsb	r3, r3, r2	@ tmp120, tmp122, tmp121
	str	r3, [fp, #-16]	@ tmp120, k
	ldr	r0, .L3+4	@,
	ldr	r1, [fp, #-8]	@, i
	ldr	r2, [fp, #-12]	@, j
	ldr	r3, [fp, #-16]	@, k
	bl	printf	@
	ldr	r2, [fp, #-8]	@ tmp124, i
	ldr	r3, [fp, #-12]	@ tmp125, j
	orr	r3, r2, r3	@ tmp123, tmp124, tmp125
	str	r3, [fp, #-16]	@ tmp123, k
	ldr	r0, .L3+8	@,
	ldr	r1, [fp, #-8]	@, i
	ldr	r2, [fp, #-12]	@, j
	ldr	r3, [fp, #-16]	@, k
	bl	printf	@
	ldr	r3, [fp, #-8]	@ tmp127, i
	ldr	r2, [fp, #-12]	@ tmp128, j
	mul	r3, r2, r3	@ tmp126, tmp128, tmp127
	str	r3, [fp, #-16]	@ tmp126, k
	ldr	r0, .L3+12	@,
	ldr	r1, [fp, #-8]	@, i
	ldr	r2, [fp, #-12]	@, j
	ldr	r3, [fp, #-16]	@, k
	bl	printf	@
	ldr	r0, [fp, #-12]	@, j
	ldr	r1, [fp, #-8]	@, i
	bl	__aeabi_idiv	@
	mov	r3, r0	@ tmp132,
	str	r3, [fp, #-16]	@ tmp132, k
	ldr	r0, .L3+16	@,
	ldr	r1, [fp, #-12]	@, j
	ldr	r2, [fp, #-8]	@, i
	ldr	r3, [fp, #-16]	@, k
	bl	printf	@
	ldr	r3, [fp, #-12]	@ tmp134, j
	mov	r0, r3	@, tmp134
	ldr	r1, [fp, #-8]	@, i
	bl	__aeabi_idivmod	@
	mov	r3, r1	@ tmp139,
	str	r3, [fp, #-16]	@ tmp139, k
	ldr	r0, .L3+20	@,
	ldr	r1, [fp, #-12]	@, j
	ldr	r2, [fp, #-8]	@, i
	ldr	r3, [fp, #-16]	@, k
	bl	printf	@
	ldr	r2, [fp, #-12]	@ tmp141, j
	ldr	r3, [fp, #-8]	@ tmp142, i
	and	r3, r3, r2	@ tmp140, tmp142, tmp141
	str	r3, [fp, #-16]	@ tmp140, k
	ldr	r0, .L3+24	@,
	ldr	r1, [fp, #-12]	@, j
	ldr	r2, [fp, #-8]	@, i
	ldr	r3, [fp, #-16]	@, k
	bl	printf	@
	ldr	r2, [fp, #-8]	@ tmp143, i
	ldr	r3, [fp, #-12]	@ tmp144, j
	add	r3, r2, r3	@ D.4357, tmp143, tmp144
	rsb	r3, r3, #0	@ tmp145, D.4357
	str	r3, [fp, #-16]	@ tmp145, k
	ldr	r0, .L3+28	@,
	ldr	r1, [fp, #-8]	@, i
	ldr	r2, [fp, #-12]	@, j
	ldr	r3, [fp, #-16]	@, k
	bl	printf	@
	ldr	r2, [fp, #-8]	@ tmp146, i
	ldr	r3, [fp, #-12]	@ tmp147, j
	add	r3, r2, r3	@ D.4357, tmp146, tmp147
	mvn	r3, r3	@ tmp148, D.4357
	str	r3, [fp, #-16]	@ tmp148, k
	ldr	r0, .L3+32	@,
	ldr	r1, [fp, #-8]	@, i
	ldr	r2, [fp, #-12]	@, j
	ldr	r3, [fp, #-16]	@, k
	bl	printf	@
	mov	r3, #0	@ D.4357,
	mov	r0, r3	@, <retval>
	sub	sp, fp, #4	@,,
	@ sp needed	@
	ldmfd	sp!, {fp, pc}	@
.L4:
	.align	2
.L3:
	.word	.LC0
	.word	.LC1
	.word	.LC2
	.word	.LC3
	.word	.LC4
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LC8
	.size	main, .-main
	.ident	"GCC: (Raspbian 4.9.2-10) 4.9.2"
	.section	.note.GNU-stack,"",%progbits
