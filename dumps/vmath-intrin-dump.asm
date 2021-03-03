
obj/vmath.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <Math::operator^(Math::Vec4 const&, Math::Vec4 const&)>:
   0:	e9 00 00 00 00       	jmp    5 <Math::operator^(Math::Vec4 const&, Math::Vec4 const&)+0x5>
   5:	90                   	nop
   6:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
   d:	00 00 00 

0000000000000010 <Math::Vec4::Vec4(float)>:
  10:	c5 fa 11 07          	vmovss DWORD PTR [rdi],xmm0
  14:	c5 fa 11 47 04       	vmovss DWORD PTR [rdi+0x4],xmm0
  19:	c5 fa 11 47 08       	vmovss DWORD PTR [rdi+0x8],xmm0
  1e:	c5 fa 11 47 0c       	vmovss DWORD PTR [rdi+0xc],xmm0
  23:	c3                   	ret    
  24:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  2b:	00 00 00 00 
  2f:	90                   	nop

0000000000000030 <Math::Vec4::Vec4(float, float, float)>:
  30:	c7 47 0c 00 00 80 3f 	mov    DWORD PTR [rdi+0xc],0x3f800000
  37:	c5 fa 11 07          	vmovss DWORD PTR [rdi],xmm0
  3b:	c5 fa 11 4f 04       	vmovss DWORD PTR [rdi+0x4],xmm1
  40:	c5 fa 11 57 08       	vmovss DWORD PTR [rdi+0x8],xmm2
  45:	c3                   	ret    
  46:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
  4d:	00 00 00 

0000000000000050 <Math::Vec4::Vec4(float, float, float, float)>:
  50:	c5 fa 11 07          	vmovss DWORD PTR [rdi],xmm0
  54:	c5 fa 11 4f 04       	vmovss DWORD PTR [rdi+0x4],xmm1
  59:	c5 fa 11 57 08       	vmovss DWORD PTR [rdi+0x8],xmm2
  5e:	c5 fa 11 5f 0c       	vmovss DWORD PTR [rdi+0xc],xmm3
  63:	c3                   	ret    
  64:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  6b:	00 00 00 00 
  6f:	90                   	nop

0000000000000070 <Math::Vec4::sqlen() const>:
  70:	c5 f8 28 07          	vmovaps xmm0,XMMWORD PTR [rdi]
  74:	c5 f8 59 c0          	vmulps xmm0,xmm0,xmm0
  78:	c5 fb 7c c0          	vhaddps xmm0,xmm0,xmm0
  7c:	c5 fb 7c c0          	vhaddps xmm0,xmm0,xmm0
  80:	c3                   	ret    
