	.file	"gasunit.cpp"
	.text
	.p2align 4
	.globl	_ZN4Phys16ResolveCollisionERNS_7GasUnitES1_
	.type	_ZN4Phys16ResolveCollisionERNS_7GasUnitES1_, @function
_ZN4Phys16ResolveCollisionERNS_7GasUnitES1_:
.LFB8531:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	vmovaps	(%rsi), %xmm1
	vmovaps	(%rdi), %xmm4
	xorl	%eax, %eax
	vsubps	%xmm1, %xmm4, %xmm2
	vandps	.LC0(%rip), %xmm2, %xmm0
	vcmpgeps	.LC1(%rip), %xmm0, %xmm0
	vmovmskps	%xmm0, %edx
	testl	%edx, %edx
	je	.L6
.L1:
	ret
	.p2align 4,,10
	.p2align 3
.L6:
	vmulps	%xmm2, %xmm2, %xmm0
	vhaddps	%xmm0, %xmm0, %xmm0
	vhaddps	%xmm0, %xmm0, %xmm3
	vcomiss	.LC2(%rip), %xmm3
	jnb	.L1
	vmovaps	16(%rdi), %xmm6
	vmovaps	16(%rsi), %xmm10
	movl	$1, %eax
	vsubps	%xmm10, %xmm6, %xmm0
	vmulps	%xmm0, %xmm0, %xmm7
	vmulps	%xmm0, %xmm2, %xmm0
	vhaddps	%xmm7, %xmm7, %xmm7
	vhaddps	%xmm0, %xmm0, %xmm0
	vhaddps	%xmm7, %xmm7, %xmm7
	vhaddps	%xmm0, %xmm0, %xmm5
	vmulps	%xmm6, %xmm4, %xmm0
	vaddss	%xmm7, %xmm7, %xmm7
	vhaddps	%xmm0, %xmm0, %xmm0
	vhaddps	%xmm0, %xmm0, %xmm8
	vmulps	%xmm10, %xmm1, %xmm0
	vmovss	.LC3(%rip), %xmm10
	vxorps	%xmm10, %xmm5, %xmm1
	vsubss	%xmm8, %xmm1, %xmm1
	vhaddps	%xmm0, %xmm0, %xmm0
	vhaddps	%xmm0, %xmm0, %xmm0
	vsubss	%xmm0, %xmm1, %xmm0
	vaddss	%xmm7, %xmm7, %xmm1
	vmulss	%xmm3, %xmm1, %xmm1
	vpermilps	$0, %xmm3, %xmm3
	vfmsub231ss	%xmm0, %xmm0, %xmm1
	vxorps	%xmm10, %xmm0, %xmm0
	vinsertps	$0xe, %xmm1, %xmm1, %xmm1
	vsqrtss	%xmm1, %xmm1, %xmm1
	vsubss	%xmm1, %xmm0, %xmm1
	vdivss	%xmm7, %xmm1, %xmm1
	vshufps	$0, %xmm1, %xmm1, %xmm1
	vfnmadd231ps	%xmm6, %xmm1, %xmm4
	vmovaps	%xmm4, (%rdi)
	vmovaps	16(%rsi), %xmm0
	vfnmadd213ps	(%rsi), %xmm1, %xmm0
	vmovaps	%xmm0, (%rsi)
	vmovaps	16(%rdi), %xmm5
	vmulps	%xmm5, %xmm2, %xmm0
	vhaddps	%xmm0, %xmm0, %xmm0
	vhaddps	%xmm0, %xmm0, %xmm0
	vaddss	%xmm0, %xmm0, %xmm0
	vshufps	$0, %xmm0, %xmm0, %xmm4
	vmulps	%xmm2, %xmm4, %xmm4
	vdivps	%xmm3, %xmm4, %xmm4
	vsubps	%xmm4, %xmm5, %xmm4
	vmovaps	%xmm4, 16(%rdi)
	vmovaps	16(%rsi), %xmm5
	vmulps	%xmm5, %xmm2, %xmm4
	vhaddps	%xmm4, %xmm4, %xmm4
	vhaddps	%xmm4, %xmm4, %xmm4
	vaddss	%xmm4, %xmm4, %xmm4
	vshufps	$0, %xmm4, %xmm4, %xmm0
	vmulps	%xmm2, %xmm0, %xmm2
	vdivps	%xmm3, %xmm2, %xmm0
	vsubps	%xmm0, %xmm5, %xmm0
	vmovaps	%xmm0, 16(%rsi)
	vmovaps	16(%rdi), %xmm0
	vfmadd213ps	(%rdi), %xmm1, %xmm0
	vmovaps	%xmm0, (%rdi)
	vmovaps	(%rsi), %xmm6
	vfmadd132ps	16(%rsi), %xmm6, %xmm1
	vmovaps	%xmm1, (%rsi)
	ret
	.cfi_endproc
.LFE8531:
	.size	_ZN4Phys16ResolveCollisionERNS_7GasUnitES1_, .-_ZN4Phys16ResolveCollisionERNS_7GasUnitES1_
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.type	_GLOBAL__sub_I__ZN4Phys16ResolveCollisionERNS_7GasUnitES1_, @function
_GLOBAL__sub_I__ZN4Phys16ResolveCollisionERNS_7GasUnitES1_:
.LFB9211:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	leaq	_ZStL8__ioinit(%rip), %rdi
	call	_ZNSt8ios_base4InitC1Ev@PLT
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rdi
	leaq	__dso_handle(%rip), %rdx
	leaq	_ZStL8__ioinit(%rip), %rsi
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	jmp	__cxa_atexit@PLT
	.cfi_endproc
.LFE9211:
	.size	_GLOBAL__sub_I__ZN4Phys16ResolveCollisionERNS_7GasUnitES1_, .-_GLOBAL__sub_I__ZN4Phys16ResolveCollisionERNS_7GasUnitES1_
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__ZN4Phys16ResolveCollisionERNS_7GasUnitES1_
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	2147483647
	.long	2147483647
	.long	2147483647
	.long	2147483647
	.align 16
.LC1:
	.long	1073741824
	.long	1073741824
	.long	1073741824
	.long	1073741824
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC2:
	.long	1082130432
	.section	.rodata.cst16
	.align 16
.LC3:
	.long	-2147483648
	.long	0
	.long	0
	.long	0
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 10.2.0"
	.section	.note.GNU-stack,"",@progbits
