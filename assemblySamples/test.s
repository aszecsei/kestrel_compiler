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
	.file	"test.c"
@ GNU C (Raspbian 4.9.2-10) version 4.9.2 (arm-linux-gnueabihf)
@	compiled by GNU C version 4.9.2, GMP version 6.0.0, MPFR version 3.1.2-p3, MPC version 1.0.2
@ GGC heuristics: --param ggc-min-expand=93 --param ggc-min-heapsize=118468
@ options passed:  -imultilib . -imultiarch arm-linux-gnueabihf test.c
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

	.text
	.align	2
	.global	mdouble
	.type	mdouble, %function
mdouble:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!	@,
	add	fp, sp, #0	@,,
	sub	sp, sp, #12	@,,
	str	r0, [fp, #-8]	@ input, input
	ldr	r3, [fp, #-8]	@ tmp112, input
	mov	r3, r3, asl #1	@ D.4360, tmp112,
	mov	r0, r3	@, <retval>
	sub	sp, fp, #0	@,,
	@ sp needed	@
	ldr	fp, [sp], #4	@,
	bx	lr	@
	.size	mdouble, .-mdouble
	.section	.rodata
	.align	2
.LC0:
	.ascii	"i=%d\012j=%d\012\000"
	.align	2
.LC1:
	.ascii	"HI THERE\000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}	@,
	add	fp, sp, #4	@,,
	sub	sp, sp, #8	@,,
	mov	r3, #1	@ tmp112,
	str	r3, [fp, #-8]	@ tmp112, i
	ldr	r2, [fp, #-8]	@ tmp113, i
	mov	r3, r2	@ tmp114, tmp113
	mov	r3, r3, asl #2	@ tmp114, tmp114,
	add	r3, r3, r2	@ tmp114, tmp114, tmp113
	mov	r3, r3, asl #1	@ tmp115, tmp114,
	str	r3, [fp, #-8]	@ tmp114, i
	ldr	r3, [fp, #-8]	@ tmp117, i
	sub	r3, r3, #5	@ tmp116, tmp117,
	str	r3, [fp, #-8]	@ tmp116, i
	ldr	r0, [fp, #-8]	@, i
	bl	mdouble	@
	str	r0, [fp, #-12]	@, j
	ldr	r0, .L5	@,
	ldr	r1, [fp, #-8]	@, i
	ldr	r2, [fp, #-12]	@, j
	bl	printf	@
	ldr	r0, .L5+4	@,
	bl	puts	@
	mov	r3, #0	@ D.4361,
	mov	r0, r3	@, <retval>
	sub	sp, fp, #4	@,,
	@ sp needed	@
	ldmfd	sp!, {fp, pc}	@
.L6:
	.align	2
.L5:
	.word	.LC0
	.word	.LC1
	.size	main, .-main
	.ident	"GCC: (Raspbian 4.9.2-10) 4.9.2"
	.section	.note.GNU-stack,"",%progbits
