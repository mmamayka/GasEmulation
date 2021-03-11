	.file	"gasunit.cpp"
# GNU C++14 (GCC) version 10.2.0 (x86_64-pc-linux-gnu)
#	compiled by GNU C version 10.2.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.21-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -D_GNU_SOURCE src/gasunit.cpp -march=skylake
# -auxbase-strip dumps/gausnit.asm -O2 -fverbose-asm
# options enabled:  -fPIC -fPIE -faggressive-loop-optimizations
# -falign-functions -falign-jumps -falign-labels -falign-loops
# -fallocation-dce -fasynchronous-unwind-tables -fauto-inc-dec
# -fbranch-count-reg -fcaller-saves -fcode-hoisting
# -fcombine-stack-adjustments -fcompare-elim -fcprop-registers
# -fcrossjumping -fcse-follow-jumps -fdefer-pop
# -fdelete-null-pointer-checks -fdevirtualize -fdevirtualize-speculatively
# -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-symbols
# -feliminate-unused-debug-types -fexceptions -fexpensive-optimizations
# -ffinite-loops -fforward-propagate -ffp-int-builtin-inexact
# -ffunction-cse -fgcse -fgcse-lm -fgnu-unique -fguess-branch-probability
# -fhoist-adjacent-loads -fident -fif-conversion -fif-conversion2
# -findirect-inlining -finline -finline-atomics -finline-functions
# -finline-functions-called-once -finline-small-functions -fipa-bit-cp
# -fipa-cp -fipa-icf -fipa-icf-functions -fipa-icf-variables -fipa-profile
# -fipa-pure-const -fipa-ra -fipa-reference -fipa-reference-addressable
# -fipa-sra -fipa-stack-alignment -fipa-vrp -fira-hoist-pressure
# -fira-share-save-slots -fira-share-spill-slots
# -fisolate-erroneous-paths-dereference -fivopts -fkeep-static-consts
# -fleading-underscore -flifetime-dse -flra-remat -fmath-errno
# -fmerge-constants -fmerge-debug-strings -fmove-loop-invariants
# -fomit-frame-pointer -foptimize-sibling-calls -foptimize-strlen
# -fpartial-inlining -fpeephole -fpeephole2 -fplt -fprefetch-loop-arrays
# -free -freg-struct-return -freorder-blocks -freorder-blocks-and-partition
# -freorder-functions -frerun-cse-after-loop
# -fsched-critical-path-heuristic -fsched-dep-count-heuristic
# -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
# -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
# -fsched-stalled-insns-dep -fschedule-fusion -fschedule-insns2
# -fsemantic-interposition -fshow-column -fshrink-wrap
# -fshrink-wrap-separate -fsigned-zeros -fsplit-ivs-in-unroller
# -fsplit-wide-types -fssa-backprop -fssa-phiopt -fstack-protector-strong
# -fstdarg-opt -fstore-merging -fstrict-aliasing
# -fstrict-volatile-bitfields -fsync-libcalls -fthread-jumps
# -ftoplevel-reorder -ftrapping-math -ftree-bit-ccp -ftree-builtin-call-dce
# -ftree-ccp -ftree-ch -ftree-coalesce-vars -ftree-copy-prop -ftree-cselim
# -ftree-dce -ftree-dominator-opts -ftree-dse -ftree-forwprop -ftree-fre
# -ftree-loop-distribute-patterns -ftree-loop-if-convert -ftree-loop-im
# -ftree-loop-ivcanon -ftree-loop-optimize -ftree-parallelize-loops=
# -ftree-phiprop -ftree-pre -ftree-pta -ftree-reassoc -ftree-scev-cprop
# -ftree-sink -ftree-slsr -ftree-sra -ftree-switch-conversion
# -ftree-tail-merge -ftree-ter -ftree-vrp -funit-at-a-time -funwind-tables
# -fverbose-asm -fzero-initialized-in-bss -m128bit-long-double -m64 -m80387
# -madx -maes -malign-stringops -mavx -mavx2 -mbmi -mbmi2 -mclflushopt
# -mcx16 -mf16c -mfancy-math-387 -mfma -mfp-ret-in-387 -mfsgsbase -mfxsr
# -mglibc -mhle -mieee-fp -mlong-double-80 -mlzcnt -mmmx -mmovbe -mpclmul
# -mpopcnt -mprfchw -mpush-args -mrdrnd -mrdseed -mred-zone -msahf -msgx
# -msse -msse2 -msse3 -msse4 -msse4.1 -msse4.2 -mssse3 -mstv
# -mtls-direct-seg-refs -mvzeroupper -mxsave -mxsavec -mxsaveopt -mxsaves

	.text
	.p2align 4
	.globl	_ZN4Phys16ResolveCollisionERNS_7GasUnitES1_
	.type	_ZN4Phys16ResolveCollisionERNS_7GasUnitES1_, @function
_ZN4Phys16ResolveCollisionERNS_7GasUnitES1_:
.LFB8444:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:927:   return *(__m128 *)__P;
	vmovaps	(%rdi), %xmm3	# MEM[(__m128 * {ref-all})a_10(D)], _24
# src/gasunit.cpp:16: 			return false;
	xorl	%eax, %eax	# <retval>
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:192:   return (__m128) ((__v4sf)__A - (__v4sf)__B);
	vsubps	(%rsi), %xmm3, %xmm1	# MEM[(__m128 * {ref-all})b_9(D)], _24, _22
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:242:   return __builtin_ia32_andps (__A, __B);
	vandps	.LC0(%rip), %xmm1, %xmm0	#, _22, tmp144
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:386:   return (__m128) __builtin_ia32_cmpgeps ((__v4sf)__A, (__v4sf)__B);
	vcmpgeps	.LC1(%rip), %xmm0, %xmm0	#,, tmp144, tmp146
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:816:   return __builtin_ia32_movmskps ((__v4sf)__A);
	vmovmskps	%xmm0, %edx	# tmp146, tmp148
# src/gasunit.cpp:15: 		if(!InfNormLessThan(Abs(dr), D)) { [[likely]]
	testl	%edx, %edx	# tmp148
	je	.L9	#,
.L1:
# src/gasunit.cpp:80: 	}
	ret	
	.p2align 4,,10
	.p2align 3
.L9:
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:198:   return (__m128) ((__v4sf)__A * (__v4sf)__B);
	vmulps	%xmm1, %xmm1, %xmm0	# _22, _22, _17
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/pmmintrin.h:58:   return (__m128) __builtin_ia32_haddps ((__v4sf)__X, (__v4sf)__Y);
	vhaddps	%xmm0, %xmm0, %xmm0	# _17, _17, tmp150
	vhaddps	%xmm0, %xmm0, %xmm0	# tmp150, tmp150, tmp151
# src/gasunit.cpp:21: 		if(d2 >= D2) { [[likely]]
	vcomiss	.LC2(%rip), %xmm0	#, _14
	vmovaps	%xmm0, %xmm2	# tmp151, _14
	jnb	.L1	#,
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:927:   return *(__m128 *)__P;
	vmovaps	16(%rdi), %xmm5	# MEM[(__m128 * {ref-all})a_10(D) + 16B], _37
# src/gasunit.cpp:79: 		return true;
	movl	$1, %eax	#, <retval>
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:192:   return (__m128) ((__v4sf)__A - (__v4sf)__B);
	vsubps	16(%rsi), %xmm5, %xmm4	# MEM[(__m128 * {ref-all})b_9(D) + 16B], _37, _39
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:198:   return (__m128) ((__v4sf)__A * (__v4sf)__B);
	vmulps	%xmm4, %xmm4, %xmm0	# _39, _39, _33
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/pmmintrin.h:58:   return (__m128) __builtin_ia32_haddps ((__v4sf)__X, (__v4sf)__Y);
	vhaddps	%xmm0, %xmm0, %xmm0	# _33, _33, tmp152
	vhaddps	%xmm0, %xmm0, %xmm0	# tmp152, tmp152, tmp153
	vmovaps	%xmm0, %xmm6	# tmp153, _36
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:198:   return (__m128) ((__v4sf)__A * (__v4sf)__B);
	vmulps	%xmm4, %xmm1, %xmm0	# _39, _22, _29
# src/gasunit.cpp:30: 		float C = d2 - D2;
	vsubss	.LC2(%rip), %xmm2, %xmm1	#, _14, C
# src/gasunit.cpp:36: 		if(Bhalf > 0.f) {
	vxorps	%xmm2, %xmm2, %xmm2	# tmp161
# src/gasunit.cpp:31: 		float Dby4 = Bhalf * Bhalf - A * C;
	vmulss	%xmm6, %xmm1, %xmm1	# _36, C, tmp158
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/pmmintrin.h:58:   return (__m128) __builtin_ia32_haddps ((__v4sf)__X, (__v4sf)__Y);
	vhaddps	%xmm0, %xmm0, %xmm0	# _29, _29, tmp154
	vhaddps	%xmm0, %xmm0, %xmm0	# tmp154, tmp154, tmp155
# src/gasunit.cpp:31: 		float Dby4 = Bhalf * Bhalf - A * C;
	vfmsub231ss	%xmm0, %xmm0, %xmm1	# Bhalf, Bhalf, Dby4
# src/gasunit.cpp:37: 			Bhalf = -Bhalf;
	vxorps	.LC4(%rip), %xmm0, %xmm8	#, Bhalf, tmp181
	vmovaps	%xmm0, %xmm7	# Bhalf, tmp182
	vcmpltss	%xmm0, %xmm2, %xmm0	#, Bhalf, tmp161, tmp183
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:887:   return __extension__ (__m128)(__v4sf){ __F, 0.0f, 0.0f, 0.0f };
	vinsertps	$0xe, %xmm1, %xmm1, %xmm1	# Dby4, tmp159
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:154:   return (__m128) __builtin_ia32_sqrtss ((__v4sf)__A);
	vsqrtss	%xmm1, %xmm1, %xmm1	# tmp159, tmp159, tmp160
# src/gasunit.cpp:37: 			Bhalf = -Bhalf;
	vblendvps	%xmm0, %xmm8, %xmm7, %xmm0	# tmp183, tmp181, tmp182, Bhalf
# src/gasunit.cpp:39: 		dt = (Bhalf + Sqrt(Dby4)) / A;
	vaddss	%xmm1, %xmm0, %xmm0	# _11, Bhalf, tmp165
# src/gasunit.cpp:39: 		dt = (Bhalf + Sqrt(Dby4)) / A;
	vdivss	%xmm6, %xmm0, %xmm0	# _36, tmp165, dt
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:894:   return __extension__ (__m128)(__v4sf){ __F, __F, __F, __F };
	vshufps	$0, %xmm0, %xmm0, %xmm0	# dt, tmp166
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:192:   return (__m128) ((__v4sf)__A - (__v4sf)__B);
	vfnmadd231ps	%xmm0, %xmm5, %xmm3	# tmp166, _37, _66
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:976:   *(__m128 *)__P = __A;
	vmovaps	%xmm3, (%rdi)	# _66, MEM[(__m128 * {ref-all})a_10(D)]
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:192:   return (__m128) ((__v4sf)__A - (__v4sf)__B);
	vmovaps	16(%rsi), %xmm1	# MEM[(__m128 * {ref-all})b_9(D) + 16B], _63
	vfnmadd213ps	(%rsi), %xmm0, %xmm1	# MEM[(__m128 * {ref-all})b_9(D)], tmp166, _63
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:976:   *(__m128 *)__P = __A;
	vmovaps	%xmm1, (%rsi)	# _63, MEM[(__m128 * {ref-all})b_9(D)]
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:192:   return (__m128) ((__v4sf)__A - (__v4sf)__B);
	vmovaps	(%rdi), %xmm7	# MEM[(__m128 * {ref-all})a_10(D)], tmp185
	vmovaps	16(%rdi), %xmm5	# MEM[(__m128 * {ref-all})a_10(D) + 16B], tmp186
	vsubps	%xmm1, %xmm7, %xmm3	# _63, tmp185, _61
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:198:   return (__m128) ((__v4sf)__A * (__v4sf)__B);
	vmulps	%xmm3, %xmm4, %xmm4	# _61, _39, _54
	vmulps	%xmm3, %xmm3, %xmm1	# _61, _61, _57
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/pmmintrin.h:58:   return (__m128) __builtin_ia32_haddps ((__v4sf)__X, (__v4sf)__Y);
	vhaddps	%xmm4, %xmm4, %xmm4	# _54, _54, tmp170
	vhaddps	%xmm1, %xmm1, %xmm1	# _57, _57, tmp168
	vhaddps	%xmm4, %xmm4, %xmm4	# tmp170, tmp170, tmp171
	vhaddps	%xmm1, %xmm1, %xmm2	# tmp168, tmp168, tmp169
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:198:   return (__m128) ((__v4sf)__A * (__v4sf)__B);
	vpermilps	$0, %xmm4, %xmm1	#, tmp171, tmp172
	vmulps	%xmm3, %xmm1, %xmm1	# _61, tmp172, tmp173
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:204:   return (__m128) ((__v4sf)__A / (__v4sf)__B);
	vpermilps	$0, %xmm2, %xmm2	#, tmp169, tmp174
	vdivps	%xmm2, %xmm1, %xmm1	# tmp174, tmp173, _52
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:192:   return (__m128) ((__v4sf)__A - (__v4sf)__B);
	vsubps	%xmm1, %xmm5, %xmm2	# _52, tmp186, tmp175
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:976:   *(__m128 *)__P = __A;
	vmovaps	%xmm2, 16(%rdi)	# tmp175, MEM[(__m128 * {ref-all})a_10(D) + 16B]
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:186:   return (__m128) ((__v4sf)__A + (__v4sf)__B);
	vaddps	16(%rsi), %xmm1, %xmm1	# MEM[(__m128 * {ref-all})b_9(D) + 16B], _52, tmp177
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:976:   *(__m128 *)__P = __A;
	vmovaps	%xmm1, 16(%rsi)	# tmp177, MEM[(__m128 * {ref-all})b_9(D) + 16B]
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:186:   return (__m128) ((__v4sf)__A + (__v4sf)__B);
	vmovaps	16(%rdi), %xmm1	# MEM[(__m128 * {ref-all})a_10(D) + 16B], _45
	vfmadd213ps	(%rdi), %xmm0, %xmm1	# MEM[(__m128 * {ref-all})a_10(D)], tmp166, _45
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:976:   *(__m128 *)__P = __A;
	vmovaps	%xmm1, (%rdi)	# _45, MEM[(__m128 * {ref-all})a_10(D)]
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:186:   return (__m128) ((__v4sf)__A + (__v4sf)__B);
	vmovaps	(%rsi), %xmm6	# MEM[(__m128 * {ref-all})b_9(D)], tmp188
	vfmadd132ps	16(%rsi), %xmm6, %xmm0	# MEM[(__m128 * {ref-all})b_9(D) + 16B], tmp188, _41
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:976:   *(__m128 *)__P = __A;
	vmovaps	%xmm0, (%rsi)	# _41, MEM[(__m128 * {ref-all})b_9(D)]
# src/gasunit.cpp:80: 	}
	ret	
	.cfi_endproc
.LFE8444:
	.size	_ZN4Phys16ResolveCollisionERNS_7GasUnitES1_, .-_ZN4Phys16ResolveCollisionERNS_7GasUnitES1_
	.p2align 4
	.globl	_ZN4Phys16ResolveCollisionERNS_7GasUnitERKNS_17ContainerColliderE
	.type	_ZN4Phys16ResolveCollisionERNS_7GasUnitERKNS_17ContainerColliderE, @function
_ZN4Phys16ResolveCollisionERNS_7GasUnitERKNS_17ContainerColliderE:
.LFB8445:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:746:   return (__m128) __builtin_ia32_shufps ((__v4sf)__A, (__v4sf)__B, __mask);
	vmovss	.LC5(%rip), %xmm0	#, tmp155
	vshufps	$64, %xmm0, %xmm0, %xmm1	#, tmp155, tmp155, tmp154
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:927:   return *(__m128 *)__P;
	vmovaps	(%rdi), %xmm0	# MEM[(__m128 * {ref-all})a_56(D)], _64
	vmovaps	(%rsi), %xmm3	# MEM[(__m128 * {ref-all})b_55(D)], _58
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:186:   return (__m128) ((__v4sf)__A + (__v4sf)__B);
	vaddps	%xmm0, %xmm1, %xmm2	# _64, tmp154, tmp157
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:192:   return (__m128) ((__v4sf)__A - (__v4sf)__B);
	vsubps	%xmm1, %xmm0, %xmm0	# tmp154, _64, tmp161
	vxorps	%xmm1, %xmm1, %xmm1	# tmp163
	vsubps	%xmm3, %xmm1, %xmm1	# _58, tmp163, tmp162
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:380:   return (__m128) __builtin_ia32_cmpgtps ((__v4sf)__A, (__v4sf)__B);
	vcmpltps	%xmm2, %xmm3, %xmm2	#, tmp157, _58, tmp158
# src/gasunit.cpp:91: 			return false;
	xorl	%r8d, %r8d	# <retval>
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:368:   return (__m128) __builtin_ia32_cmpltps ((__v4sf)__A, (__v4sf)__B);
	vcmpltps	%xmm1, %xmm0, %xmm0	#, tmp162, tmp161, tmp164
# /usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include/xmmintrin.h:816:   return __builtin_ia32_movmskps ((__v4sf)__A);
	vmovmskps	%xmm2, %edx	# tmp158, tmp159
	vmovmskps	%xmm0, %eax	# tmp164, tmp165
# src/gasunit.cpp:88: 			(CMPLTMask(a.pos() - Rvec, -b.size()) << 4));
	sall	$4, %eax	#, tmp167
# src/gasunit.cpp:90: 		if(!cmask) { [[likely]]
	orl	%edx, %eax	# tmp159, cmask
	jne	.L36	#,
.L10:
# src/gasunit.cpp:123: 	}
	movl	%r8d, %eax	# <retval>,
	ret	
	.p2align 4,,10
	.p2align 3
.L36:
# src/gasunit.cpp:95: 		if(cmask & (1 << 0)) {
	testb	$1, %al	#, cmask
	je	.L12	#,
# src/gasunit.cpp:96: 			a.vel().x = -a.vel().x;
	vmovss	16(%rdi), %xmm0	# MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.x, MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.x
# src/gasunit.cpp:97: 			a.pos().x -= 2 * (a.pos().x + R - b.size().x);
	vmovss	(%rdi), %xmm1	# MEM[(struct Vec4 &)a_56(D)].D.74617.D.74615.x, _5
# src/gasunit.cpp:96: 			a.vel().x = -a.vel().x;
	vxorps	.LC4(%rip), %xmm0, %xmm0	#, MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.x, tmp169
# src/gasunit.cpp:96: 			a.vel().x = -a.vel().x;
	vmovss	%xmm0, 16(%rdi)	# tmp169, MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.x
# src/gasunit.cpp:97: 			a.pos().x -= 2 * (a.pos().x + R - b.size().x);
	vaddss	.LC6(%rip), %xmm1, %xmm0	#, _5, tmp172
# src/gasunit.cpp:97: 			a.pos().x -= 2 * (a.pos().x + R - b.size().x);
	vsubss	(%rsi), %xmm0, %xmm0	# MEM[(__m128 * {ref-all})b_55(D)], tmp172, tmp174
# src/gasunit.cpp:97: 			a.pos().x -= 2 * (a.pos().x + R - b.size().x);
	vfnmadd132ss	.LC7(%rip), %xmm1, %xmm0	#, _5, _8
	vmovss	%xmm0, (%rdi)	# _8, MEM[(struct Vec4 &)a_56(D)].D.74617.D.74615.x
.L12:
# src/gasunit.cpp:99: 		if(cmask & (1 << 1)) {
	testb	$2, %al	#, cmask
	je	.L13	#,
# src/gasunit.cpp:100: 			a.vel().y = -a.vel().y;
	vmovss	20(%rdi), %xmm0	# MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.y, MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.y
# src/gasunit.cpp:101: 			a.pos().y -= 2 * (a.pos().y + R - b.size().y);
	vmovss	4(%rdi), %xmm1	# MEM[(struct Vec4 &)a_56(D)].D.74617.D.74615.y, _12
# src/gasunit.cpp:100: 			a.vel().y = -a.vel().y;
	vxorps	.LC4(%rip), %xmm0, %xmm0	#, MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.y, tmp177
# src/gasunit.cpp:100: 			a.vel().y = -a.vel().y;
	vmovss	%xmm0, 20(%rdi)	# tmp177, MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.y
# src/gasunit.cpp:101: 			a.pos().y -= 2 * (a.pos().y + R - b.size().y);
	vaddss	.LC6(%rip), %xmm1, %xmm0	#, _12, tmp180
# src/gasunit.cpp:101: 			a.pos().y -= 2 * (a.pos().y + R - b.size().y);
	vsubss	4(%rsi), %xmm0, %xmm0	# MEM[(__m128 * {ref-all})b_55(D)], tmp180, tmp182
# src/gasunit.cpp:101: 			a.pos().y -= 2 * (a.pos().y + R - b.size().y);
	vfnmadd132ss	.LC7(%rip), %xmm1, %xmm0	#, _12, _15
	vmovss	%xmm0, 4(%rdi)	# _15, MEM[(struct Vec4 &)a_56(D)].D.74617.D.74615.y
.L13:
# src/gasunit.cpp:103: 		if(cmask & (1 << 2)) {
	testb	$4, %al	#, cmask
	je	.L14	#,
# src/gasunit.cpp:104: 			a.vel().z = -a.vel().z;
	vmovss	24(%rdi), %xmm0	# MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.z, MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.z
# src/gasunit.cpp:105: 			a.pos().z -= 2 * (a.pos().z + R - b.size().z);
	vmovss	8(%rdi), %xmm1	# MEM[(struct Vec4 &)a_56(D)].D.74617.D.74615.z, _19
# src/gasunit.cpp:104: 			a.vel().z = -a.vel().z;
	vxorps	.LC4(%rip), %xmm0, %xmm0	#, MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.z, tmp185
# src/gasunit.cpp:104: 			a.vel().z = -a.vel().z;
	vmovss	%xmm0, 24(%rdi)	# tmp185, MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.z
# src/gasunit.cpp:105: 			a.pos().z -= 2 * (a.pos().z + R - b.size().z);
	vaddss	.LC6(%rip), %xmm1, %xmm0	#, _19, tmp188
# src/gasunit.cpp:105: 			a.pos().z -= 2 * (a.pos().z + R - b.size().z);
	vsubss	8(%rsi), %xmm0, %xmm0	# MEM[(__m128 * {ref-all})b_55(D)], tmp188, tmp190
# src/gasunit.cpp:105: 			a.pos().z -= 2 * (a.pos().z + R - b.size().z);
	vfnmadd132ss	.LC7(%rip), %xmm1, %xmm0	#, _19, _22
	vmovss	%xmm0, 8(%rdi)	# _22, MEM[(struct Vec4 &)a_56(D)].D.74617.D.74615.z
.L14:
# src/gasunit.cpp:108: 		if(cmask & (1 << 4)) {
	testb	$16, %al	#, cmask
	je	.L15	#,
# src/gasunit.cpp:109: 			a.vel().x = -a.vel().x;
	vmovss	16(%rdi), %xmm1	# MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.x, MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.x
	vmovss	.LC4(%rip), %xmm0	#, tmp195
	vxorps	%xmm0, %xmm1, %xmm1	# tmp195, MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.x, tmp193
# src/gasunit.cpp:109: 			a.vel().x = -a.vel().x;
	vmovss	%xmm1, 16(%rdi)	# tmp193, MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.x
# src/gasunit.cpp:110: 			a.pos().x += 2 * (-a.pos().x - b.size().x + R);
	vmovss	(%rdi), %xmm1	# MEM[(struct Vec4 &)a_56(D)].D.74617.D.74615.x, _26
# src/gasunit.cpp:110: 			a.pos().x += 2 * (-a.pos().x - b.size().x + R);
	vxorps	%xmm0, %xmm1, %xmm0	# tmp195, _26, tmp196
# src/gasunit.cpp:110: 			a.pos().x += 2 * (-a.pos().x - b.size().x + R);
	vsubss	(%rsi), %xmm0, %xmm0	# MEM[(__m128 * {ref-all})b_55(D)], tmp196, tmp198
# src/gasunit.cpp:110: 			a.pos().x += 2 * (-a.pos().x - b.size().x + R);
	vaddss	.LC6(%rip), %xmm0, %xmm0	#, tmp198, tmp199
# src/gasunit.cpp:110: 			a.pos().x += 2 * (-a.pos().x - b.size().x + R);
	vfmadd132ss	.LC7(%rip), %xmm1, %xmm0	#, _26, _30
	vmovss	%xmm0, (%rdi)	# _30, MEM[(struct Vec4 &)a_56(D)].D.74617.D.74615.x
.L15:
# src/gasunit.cpp:112: 		if(cmask & (1 << 5)) {
	testb	$32, %al	#, cmask
	je	.L16	#,
# src/gasunit.cpp:113: 			a.vel().y = -a.vel().y;
	vmovss	20(%rdi), %xmm1	# MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.y, MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.y
	vmovss	.LC4(%rip), %xmm0	#, tmp205
	vxorps	%xmm0, %xmm1, %xmm1	# tmp205, MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.y, tmp203
# src/gasunit.cpp:113: 			a.vel().y = -a.vel().y;
	vmovss	%xmm1, 20(%rdi)	# tmp203, MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.y
# src/gasunit.cpp:114: 			a.pos().y += 2 * (-a.pos().y - b.size().y + R);
	vmovss	4(%rdi), %xmm1	# MEM[(struct Vec4 &)a_56(D)].D.74617.D.74615.y, _34
# src/gasunit.cpp:114: 			a.pos().y += 2 * (-a.pos().y - b.size().y + R);
	vxorps	%xmm0, %xmm1, %xmm0	# tmp205, _34, tmp206
# src/gasunit.cpp:114: 			a.pos().y += 2 * (-a.pos().y - b.size().y + R);
	vsubss	4(%rsi), %xmm0, %xmm0	# MEM[(__m128 * {ref-all})b_55(D)], tmp206, tmp208
# src/gasunit.cpp:114: 			a.pos().y += 2 * (-a.pos().y - b.size().y + R);
	vaddss	.LC6(%rip), %xmm0, %xmm0	#, tmp208, tmp209
# src/gasunit.cpp:114: 			a.pos().y += 2 * (-a.pos().y - b.size().y + R);
	vfmadd132ss	.LC7(%rip), %xmm1, %xmm0	#, _34, _38
	vmovss	%xmm0, 4(%rdi)	# _38, MEM[(struct Vec4 &)a_56(D)].D.74617.D.74615.y
.L16:
# src/gasunit.cpp:122: 		return true;
	movl	$1, %r8d	#, <retval>
# src/gasunit.cpp:116: 		if(cmask & (1 << 6)) {
	testb	$64, %al	#, cmask
	je	.L10	#,
# src/gasunit.cpp:117: 			a.vel().z = -a.vel().z;
	vmovss	24(%rdi), %xmm1	# MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.z, MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.z
	vmovss	.LC4(%rip), %xmm0	#, tmp215
	vxorps	%xmm0, %xmm1, %xmm1	# tmp215, MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.z, tmp213
# src/gasunit.cpp:117: 			a.vel().z = -a.vel().z;
	vmovss	%xmm1, 24(%rdi)	# tmp213, MEM[(struct Vec4 &)a_56(D) + 16].D.74617.D.74615.z
# src/gasunit.cpp:118: 			a.pos().z += 2 * (-a.pos().z - b.size().z + R);
	vmovss	8(%rdi), %xmm1	# MEM[(struct Vec4 &)a_56(D)].D.74617.D.74615.z, _42
# src/gasunit.cpp:118: 			a.pos().z += 2 * (-a.pos().z - b.size().z + R);
	vxorps	%xmm0, %xmm1, %xmm0	# tmp215, _42, tmp216
# src/gasunit.cpp:118: 			a.pos().z += 2 * (-a.pos().z - b.size().z + R);
	vsubss	8(%rsi), %xmm0, %xmm0	# MEM[(__m128 * {ref-all})b_55(D)], tmp216, tmp218
# src/gasunit.cpp:118: 			a.pos().z += 2 * (-a.pos().z - b.size().z + R);
	vaddss	.LC6(%rip), %xmm0, %xmm0	#, tmp218, tmp219
# src/gasunit.cpp:118: 			a.pos().z += 2 * (-a.pos().z - b.size().z + R);
	vfmadd132ss	.LC7(%rip), %xmm1, %xmm0	#, _42, _46
	vmovss	%xmm0, 8(%rdi)	# _46, MEM[(struct Vec4 &)a_56(D)].D.74617.D.74615.z
	jmp	.L10	#
	.cfi_endproc
.LFE8445:
	.size	_ZN4Phys16ResolveCollisionERNS_7GasUnitERKNS_17ContainerColliderE, .-_ZN4Phys16ResolveCollisionERNS_7GasUnitERKNS_17ContainerColliderE
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.type	_GLOBAL__sub_I__ZN4Phys16ResolveCollisionERNS_7GasUnitES1_, @function
_GLOBAL__sub_I__ZN4Phys16ResolveCollisionERNS_7GasUnitES1_:
.LFB8964:
	.cfi_startproc
	subq	$8, %rsp	#,
	.cfi_def_cfa_offset 16
# /usr/include/c++/10.2.0/iostream:74:   static ios_base::Init __ioinit;
	leaq	_ZStL8__ioinit(%rip), %rdi	#,
	call	_ZNSt8ios_base4InitC1Ev@PLT	#
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rdi	#,
	leaq	__dso_handle(%rip), %rdx	#,
	leaq	_ZStL8__ioinit(%rip), %rsi	#,
# src/gasunit.cpp:124: }
	addq	$8, %rsp	#,
	.cfi_def_cfa_offset 8
# /usr/include/c++/10.2.0/iostream:74:   static ios_base::Init __ioinit;
	jmp	__cxa_atexit@PLT	#
	.cfi_endproc
.LFE8964:
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
	.long	1112014848
	.long	1112014848
	.long	1112014848
	.long	1112014848
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC2:
	.long	1159479296
	.section	.rodata.cst16
	.align 16
.LC4:
	.long	-2147483648
	.long	0
	.long	0
	.long	0
	.align 16
.LC5:
	.long	1103626240
	.long	0
	.long	0
	.long	0
	.section	.rodata.cst4
	.align 4
.LC6:
	.long	1103626240
	.align 4
.LC7:
	.long	1073741824
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
