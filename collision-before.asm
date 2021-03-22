
obj/collision.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <Phys::CollisionCellManager::CollisionCellManager(double, double, double, double)>:
   0:	55                   	push   rbp
   1:	48 89 e5             	mov    rbp,rsp
   4:	41 54                	push   r12
   6:	53                   	push   rbx
   7:	48 83 e4 e0          	and    rsp,0xffffffffffffffe0
   b:	48 83 ec 20          	sub    rsp,0x20
   f:	ff 15 00 00 00 00    	call   QWORD PTR [rip+0x0]        # 15 <Phys::CollisionCellManager::CollisionCellManager(double, double, double, double)+0x15>
  15:	c5 fb 10 35 00 00 00 	vmovsd xmm6,QWORD PTR [rip+0x0]        # 1d <Phys::CollisionCellManager::CollisionCellManager(double, double, double, double)+0x1d>
  1c:	00 
  1d:	c5 fb 58 e8          	vaddsd xmm5,xmm0,xmm0
  21:	49 89 fc             	mov    r12,rdi
  24:	c5 d3 5e eb          	vdivsd xmm5,xmm5,xmm3
  28:	c5 f9 2f ee          	vcomisd xmm5,xmm6
  2c:	0f 83 4e 01 00 00    	jae    180 <Phys::CollisionCellManager::CollisionCellManager(double, double, double, double)+0x180>
  32:	c4 e1 fb 2c dd       	vcvttsd2si rbx,xmm5
  37:	c5 f3 58 e9          	vaddsd xmm5,xmm1,xmm1
  3b:	49 89 1c 24          	mov    QWORD PTR [r12],rbx
  3f:	c5 d3 5e eb          	vdivsd xmm5,xmm5,xmm3
  43:	c5 f9 2f ee          	vcomisd xmm5,xmm6
  47:	0f 83 1b 01 00 00    	jae    168 <Phys::CollisionCellManager::CollisionCellManager(double, double, double, double)+0x168>
  4d:	c4 e1 fb 2c c5       	vcvttsd2si rax,xmm5
  52:	c5 eb 58 e2          	vaddsd xmm4,xmm2,xmm2
  56:	49 89 44 24 08       	mov    QWORD PTR [r12+0x8],rax
  5b:	c5 db 5e e3          	vdivsd xmm4,xmm4,xmm3
  5f:	c5 f9 2f e6          	vcomisd xmm4,xmm6
  63:	0f 83 e7 00 00 00    	jae    150 <Phys::CollisionCellManager::CollisionCellManager(double, double, double, double)+0x150>
  69:	c4 e1 fb 2c d4       	vcvttsd2si rdx,xmm4
  6e:	49 89 54 24 10       	mov    QWORD PTR [r12+0x10],rdx
  73:	48 0f af d0          	imul   rdx,rax
  77:	48 b8 55 55 55 55 55 	movabs rax,0x555555555555555
  7e:	55 55 05 
  81:	c4 c1 7b 11 44 24 20 	vmovsd QWORD PTR [r12+0x20],xmm0
  88:	48 0f af da          	imul   rbx,rdx
  8c:	c4 c1 7b 11 4c 24 28 	vmovsd QWORD PTR [r12+0x28],xmm1
  93:	c4 c1 7b 11 54 24 30 	vmovsd QWORD PTR [r12+0x30],xmm2
  9a:	49 89 5c 24 18       	mov    QWORD PTR [r12+0x18],rbx
  9f:	c4 c1 7b 11 5c 24 38 	vmovsd QWORD PTR [r12+0x38],xmm3
  a6:	48 c7 c7 ff ff ff ff 	mov    rdi,0xffffffffffffffff
  ad:	48 39 c3             	cmp    rbx,rax
  b0:	77 0c                	ja     be <Phys::CollisionCellManager::CollisionCellManager(double, double, double, double)+0xbe>
  b2:	48 8d 04 5b          	lea    rax,[rbx+rbx*2]
  b6:	48 8d 3c c5 08 00 00 	lea    rdi,[rax*8+0x8]
  bd:	00 
  be:	c5 fb 11 54 24 08    	vmovsd QWORD PTR [rsp+0x8],xmm2
  c4:	c5 fb 11 4c 24 10    	vmovsd QWORD PTR [rsp+0x10],xmm1
  ca:	c5 fb 11 44 24 18    	vmovsd QWORD PTR [rsp+0x18],xmm0
  d0:	e8 00 00 00 00       	call   d5 <Phys::CollisionCellManager::CollisionCellManager(double, double, double, double)+0xd5>
  d5:	48 89 18             	mov    QWORD PTR [rax],rbx
  d8:	48 ff cb             	dec    rbx
  db:	c5 fb 10 44 24 18    	vmovsd xmm0,QWORD PTR [rsp+0x18]
  e1:	c5 fb 10 4c 24 10    	vmovsd xmm1,QWORD PTR [rsp+0x10]
  e7:	c5 fb 10 54 24 08    	vmovsd xmm2,QWORD PTR [rsp+0x8]
  ed:	48 8d 48 08          	lea    rcx,[rax+0x8]
  f1:	48 89 da             	mov    rdx,rbx
  f4:	78 2b                	js     121 <Phys::CollisionCellManager::CollisionCellManager(double, double, double, double)+0x121>
  f6:	48 89 c8             	mov    rax,rcx
  f9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
 100:	48 c7 00 00 00 00 00 	mov    QWORD PTR [rax],0x0
 107:	48 c7 40 08 00 00 00 	mov    QWORD PTR [rax+0x8],0x0
 10e:	00 
 10f:	48 c7 40 10 00 00 00 	mov    QWORD PTR [rax+0x10],0x0
 116:	00 
 117:	48 83 c0 18          	add    rax,0x18
 11b:	48 83 ea 01          	sub    rdx,0x1
 11f:	73 df                	jae    100 <Phys::CollisionCellManager::CollisionCellManager(double, double, double, double)+0x100>
 121:	c5 fa 7e d2          	vmovq  xmm2,xmm2
 125:	c5 f9 14 c1          	vunpcklpd xmm0,xmm0,xmm1
 129:	c4 e3 7d 18 c2 01    	vinsertf128 ymm0,ymm0,xmm2,0x1
 12f:	49 89 4c 24 40       	mov    QWORD PTR [r12+0x40],rcx
 134:	c4 c1 7d 29 44 24 60 	vmovapd YMMWORD PTR [r12+0x60],ymm0
 13b:	c5 f8 77             	vzeroupper 
 13e:	48 8d 65 f0          	lea    rsp,[rbp-0x10]
 142:	5b                   	pop    rbx
 143:	41 5c                	pop    r12
 145:	5d                   	pop    rbp
 146:	c3                   	ret    
 147:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
 14e:	00 00 
 150:	c5 db 5c e6          	vsubsd xmm4,xmm4,xmm6
 154:	c4 e1 fb 2c d4       	vcvttsd2si rdx,xmm4
 159:	48 0f ba fa 3f       	btc    rdx,0x3f
 15e:	e9 0b ff ff ff       	jmp    6e <Phys::CollisionCellManager::CollisionCellManager(double, double, double, double)+0x6e>
 163:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
 168:	c5 d3 5c ee          	vsubsd xmm5,xmm5,xmm6
 16c:	c4 e1 fb 2c c5       	vcvttsd2si rax,xmm5
 171:	48 0f ba f8 3f       	btc    rax,0x3f
 176:	e9 d7 fe ff ff       	jmp    52 <Phys::CollisionCellManager::CollisionCellManager(double, double, double, double)+0x52>
 17b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
 180:	c5 d3 5c ee          	vsubsd xmm5,xmm5,xmm6
 184:	c4 e1 fb 2c dd       	vcvttsd2si rbx,xmm5
 189:	48 0f ba fb 3f       	btc    rbx,0x3f
 18e:	e9 a4 fe ff ff       	jmp    37 <Phys::CollisionCellManager::CollisionCellManager(double, double, double, double)+0x37>
 193:	90                   	nop
 194:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
 19b:	00 00 00 00 
 19f:	90                   	nop

00000000000001a0 <Phys::CollisionCellManager::~CollisionCellManager()>:
 1a0:	55                   	push   rbp
 1a1:	48 89 e5             	mov    rbp,rsp
 1a4:	41 55                	push   r13
 1a6:	41 54                	push   r12
 1a8:	53                   	push   rbx
 1a9:	48 83 ec 08          	sub    rsp,0x8
 1ad:	ff 15 00 00 00 00    	call   QWORD PTR [rip+0x0]        # 1b3 <Phys::CollisionCellManager::~CollisionCellManager()+0x13>
 1b3:	48 8b 47 40          	mov    rax,QWORD PTR [rdi+0x40]
 1b7:	49 89 fc             	mov    r12,rdi
 1ba:	48 85 c0             	test   rax,rax
 1bd:	74 61                	je     220 <Phys::CollisionCellManager::~CollisionCellManager()+0x80>
 1bf:	48 8b 50 f8          	mov    rdx,QWORD PTR [rax-0x8]
 1c3:	48 8d 34 52          	lea    rsi,[rdx+rdx*2]
 1c7:	48 c1 e6 03          	shl    rsi,0x3
 1cb:	48 8d 1c 30          	lea    rbx,[rax+rsi*1]
 1cf:	48 39 d8             	cmp    rax,rbx
 1d2:	74 33                	je     207 <Phys::CollisionCellManager::~CollisionCellManager()+0x67>
 1d4:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
 1d8:	49 89 dd             	mov    r13,rbx
 1db:	48 8b 7b e8          	mov    rdi,QWORD PTR [rbx-0x18]
 1df:	48 83 eb 18          	sub    rbx,0x18
 1e3:	48 85 ff             	test   rdi,rdi
 1e6:	74 0c                	je     1f4 <Phys::CollisionCellManager::~CollisionCellManager()+0x54>
 1e8:	48 8b 73 10          	mov    rsi,QWORD PTR [rbx+0x10]
 1ec:	48 29 fe             	sub    rsi,rdi
 1ef:	e8 00 00 00 00       	call   1f4 <Phys::CollisionCellManager::~CollisionCellManager()+0x54>
 1f4:	49 39 5c 24 40       	cmp    QWORD PTR [r12+0x40],rbx
 1f9:	75 dd                	jne    1d8 <Phys::CollisionCellManager::~CollisionCellManager()+0x38>
 1fb:	49 8b 45 e0          	mov    rax,QWORD PTR [r13-0x20]
 1ff:	48 8d 34 40          	lea    rsi,[rax+rax*2]
 203:	48 c1 e6 03          	shl    rsi,0x3
 207:	48 83 c4 08          	add    rsp,0x8
 20b:	48 8d 7b f8          	lea    rdi,[rbx-0x8]
 20f:	5b                   	pop    rbx
 210:	41 5c                	pop    r12
 212:	41 5d                	pop    r13
 214:	48 83 c6 08          	add    rsi,0x8
 218:	5d                   	pop    rbp
 219:	e9 00 00 00 00       	jmp    21e <Phys::CollisionCellManager::~CollisionCellManager()+0x7e>
 21e:	66 90                	xchg   ax,ax
 220:	48 83 c4 08          	add    rsp,0x8
 224:	5b                   	pop    rbx
 225:	41 5c                	pop    r12
 227:	41 5d                	pop    r13
 229:	5d                   	pop    rbp
 22a:	c3                   	ret    
 22b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]

0000000000000230 <Phys::ResolveCollision(Phys::GasUnit&, Phys::GasUnit&)>:
 230:	55                   	push   rbp
 231:	48 89 e5             	mov    rbp,rsp
 234:	48 83 e4 e0          	and    rsp,0xffffffffffffffe0
 238:	48 83 ec 20          	sub    rsp,0x20
 23c:	ff 15 00 00 00 00    	call   QWORD PTR [rip+0x0]        # 242 <Phys::ResolveCollision(Phys::GasUnit&, Phys::GasUnit&)+0x12>
 242:	c5 fb 10 35 00 00 00 	vmovsd xmm6,QWORD PTR [rip+0x0]        # 24a <Phys::ResolveCollision(Phys::GasUnit&, Phys::GasUnit&)+0x1a>
 249:	00 
 24a:	31 c0                	xor    eax,eax
 24c:	c5 fd 28 3f          	vmovapd ymm7,YMMWORD PTR [rdi]
 250:	c5 c5 5c 0e          	vsubpd ymm1,ymm7,YMMWORD PTR [rsi]
 254:	c5 f5 59 c1          	vmulpd ymm0,ymm1,ymm1
 258:	c5 fd 7c c0          	vhaddpd ymm0,ymm0,ymm0
 25c:	c4 e3 7d 19 c2 01    	vextractf128 xmm2,ymm0,0x1
 262:	c5 fb 58 c2          	vaddsd xmm0,xmm0,xmm2
 266:	c5 f9 2f c6          	vcomisd xmm0,xmm6
 26a:	72 0c                	jb     278 <Phys::ResolveCollision(Phys::GasUnit&, Phys::GasUnit&)+0x48>
 26c:	c5 f8 77             	vzeroupper 
 26f:	c9                   	leave  
 270:	c3                   	ret    
 271:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
 278:	c5 fd 28 67 20       	vmovapd ymm4,YMMWORD PTR [rdi+0x20]
 27d:	c5 fb 5c c6          	vsubsd xmm0,xmm0,xmm6
 281:	c5 dd 5c 56 20       	vsubpd ymm2,ymm4,YMMWORD PTR [rsi+0x20]
 286:	c5 c9 57 f6          	vxorpd xmm6,xmm6,xmm6
 28a:	c5 ed 59 da          	vmulpd ymm3,ymm2,ymm2
 28e:	c5 f5 59 ca          	vmulpd ymm1,ymm1,ymm2
 292:	c5 e5 7c db          	vhaddpd ymm3,ymm3,ymm3
 296:	c5 f5 7c c9          	vhaddpd ymm1,ymm1,ymm1
 29a:	c4 e3 7d 19 dd 01    	vextractf128 xmm5,ymm3,0x1
 2a0:	c5 e3 58 dd          	vaddsd xmm3,xmm3,xmm5
 2a4:	c4 e3 7d 19 cf 01    	vextractf128 xmm7,ymm1,0x1
 2aa:	c5 f3 58 cf          	vaddsd xmm1,xmm1,xmm7
 2ae:	c5 e3 10 eb          	vmovsd xmm5,xmm3,xmm3
 2b2:	c5 e1 14 de          	vunpcklpd xmm3,xmm3,xmm6
 2b6:	c5 e1 54 1d 00 00 00 	vandpd xmm3,xmm3,XMMWORD PTR [rip+0x0]        # 2be <Phys::ResolveCollision(Phys::GasUnit&, Phys::GasUnit&)+0x8e>
 2bd:	00 
 2be:	c5 fb 10 3d 00 00 00 	vmovsd xmm7,QWORD PTR [rip+0x0]        # 2c6 <Phys::ResolveCollision(Phys::GasUnit&, Phys::GasUnit&)+0x96>
 2c5:	00 
 2c6:	c5 f9 2f fb          	vcomisd xmm7,xmm3
 2ca:	77 a0                	ja     26c <Phys::ResolveCollision(Phys::GasUnit&, Phys::GasUnit&)+0x3c>
 2cc:	c5 fb 59 c5          	vmulsd xmm0,xmm0,xmm5
 2d0:	c5 f3 10 d9          	vmovsd xmm3,xmm1,xmm1
 2d4:	c5 f1 57 3d 00 00 00 	vxorpd xmm7,xmm1,XMMWORD PTR [rip+0x0]        # 2dc <Phys::ResolveCollision(Phys::GasUnit&, Phys::GasUnit&)+0xac>
 2db:	00 
 2dc:	b8 01 00 00 00       	mov    eax,0x1
 2e1:	c4 e2 f1 bb c1       	vfmsub231sd xmm0,xmm1,xmm1
 2e6:	c5 cb c2 c9 01       	vcmpltsd xmm1,xmm6,xmm1
 2eb:	c4 e3 61 4b cf 10    	vblendvpd xmm1,xmm3,xmm7,xmm1
 2f1:	c5 fa 7e c0          	vmovq  xmm0,xmm0
 2f5:	c5 fb 51 c0          	vsqrtsd xmm0,xmm0,xmm0
 2f9:	c5 f3 58 c0          	vaddsd xmm0,xmm1,xmm0
 2fd:	c5 fb 5e ed          	vdivsd xmm5,xmm0,xmm5
 301:	c4 e2 7d 19 cd       	vbroadcastsd ymm1,xmm5
 306:	c4 e2 f5 ac 27       	vfnmadd213pd ymm4,ymm1,YMMWORD PTR [rdi]
 30b:	c4 e2 7d 19 ed       	vbroadcastsd ymm5,xmm5
 310:	c5 fd 29 27          	vmovapd YMMWORD PTR [rdi],ymm4
 314:	c5 fd 28 26          	vmovapd ymm4,YMMWORD PTR [rsi]
 318:	c4 e2 dd 9c 4e 20    	vfnmadd132pd ymm1,ymm4,YMMWORD PTR [rsi+0x20]
 31e:	c5 fd 29 0e          	vmovapd YMMWORD PTR [rsi],ymm1
 322:	c5 fd 28 27          	vmovapd ymm4,YMMWORD PTR [rdi]
 326:	c5 dd 5c c9          	vsubpd ymm1,ymm4,ymm1
 32a:	c5 ed 59 d1          	vmulpd ymm2,ymm2,ymm1
 32e:	c5 f5 59 c1          	vmulpd ymm0,ymm1,ymm1
 332:	c5 ed 7c d2          	vhaddpd ymm2,ymm2,ymm2
 336:	c5 fd 7c c0          	vhaddpd ymm0,ymm0,ymm0
 33a:	c4 e3 7d 19 d4 01    	vextractf128 xmm4,ymm2,0x1
 340:	c5 eb 58 d4          	vaddsd xmm2,xmm2,xmm4
 344:	c4 e3 7d 19 c3 01    	vextractf128 xmm3,ymm0,0x1
 34a:	c5 fb 58 c3          	vaddsd xmm0,xmm0,xmm3
 34e:	c4 e2 7d 19 d2       	vbroadcastsd ymm2,xmm2
 353:	c5 ed 59 d1          	vmulpd ymm2,ymm2,ymm1
 357:	c4 e2 7d 19 c0       	vbroadcastsd ymm0,xmm0
 35c:	c5 fd 28 67 20       	vmovapd ymm4,YMMWORD PTR [rdi+0x20]
 361:	c5 ed 5e d0          	vdivpd ymm2,ymm2,ymm0
 365:	c5 dd 5c c2          	vsubpd ymm0,ymm4,ymm2
 369:	c5 fd 29 47 20       	vmovapd YMMWORD PTR [rdi+0x20],ymm0
 36e:	c5 ed 58 56 20       	vaddpd ymm2,ymm2,YMMWORD PTR [rsi+0x20]
 373:	c5 fd 29 56 20       	vmovapd YMMWORD PTR [rsi+0x20],ymm2
 378:	c5 fd 28 47 20       	vmovapd ymm0,YMMWORD PTR [rdi+0x20]
 37d:	c4 e2 d5 a8 07       	vfmadd213pd ymm0,ymm5,YMMWORD PTR [rdi]
 382:	c5 fd 29 07          	vmovapd YMMWORD PTR [rdi],ymm0
 386:	c5 fd 28 26          	vmovapd ymm4,YMMWORD PTR [rsi]
 38a:	c4 e2 dd 98 6e 20    	vfmadd132pd ymm5,ymm4,YMMWORD PTR [rsi+0x20]
 390:	c5 fd 29 2e          	vmovapd YMMWORD PTR [rsi],ymm5
 394:	e9 d3 fe ff ff       	jmp    26c <Phys::ResolveCollision(Phys::GasUnit&, Phys::GasUnit&)+0x3c>
 399:	90                   	nop
 39a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

00000000000003a0 <Phys::CollisionCellManager::collideCells(std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >&, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >&)>:
 3a0:	55                   	push   rbp
 3a1:	48 89 e5             	mov    rbp,rsp
 3a4:	41 57                	push   r15
 3a6:	41 56                	push   r14
 3a8:	41 55                	push   r13
 3aa:	41 54                	push   r12
 3ac:	53                   	push   rbx
 3ad:	48 83 ec 18          	sub    rsp,0x18
 3b1:	ff 15 00 00 00 00    	call   QWORD PTR [rip+0x0]        # 3b7 <Phys::CollisionCellManager::collideCells(std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >&, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >&)+0x17>
 3b7:	48 8b 46 08          	mov    rax,QWORD PTR [rsi+0x8]
 3bb:	4c 8b 2e             	mov    r13,QWORD PTR [rsi]
 3be:	48 89 45 c8          	mov    QWORD PTR [rbp-0x38],rax
 3c2:	49 89 d6             	mov    r14,rdx
 3c5:	49 39 c5             	cmp    r13,rax
 3c8:	74 39                	je     403 <Phys::CollisionCellManager::collideCells(std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >&, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >&)+0x63>
 3ca:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
 3d0:	49 8b 1e             	mov    rbx,QWORD PTR [r14]
 3d3:	4d 8b 66 08          	mov    r12,QWORD PTR [r14+0x8]
 3d7:	4d 8b 7d 00          	mov    r15,QWORD PTR [r13+0x0]
 3db:	49 39 dc             	cmp    r12,rbx
 3de:	74 19                	je     3f9 <Phys::CollisionCellManager::collideCells(std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >&, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >&)+0x59>
 3e0:	48 8b 33             	mov    rsi,QWORD PTR [rbx]
 3e3:	49 39 f7             	cmp    r15,rsi
 3e6:	74 08                	je     3f0 <Phys::CollisionCellManager::collideCells(std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >&, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >&)+0x50>
 3e8:	4c 89 ff             	mov    rdi,r15
 3eb:	e8 00 00 00 00       	call   3f0 <Phys::CollisionCellManager::collideCells(std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >&, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >&)+0x50>
 3f0:	48 83 c3 08          	add    rbx,0x8
 3f4:	49 39 dc             	cmp    r12,rbx
 3f7:	75 e7                	jne    3e0 <Phys::CollisionCellManager::collideCells(std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >&, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >&)+0x40>
 3f9:	49 83 c5 08          	add    r13,0x8
 3fd:	4c 39 6d c8          	cmp    QWORD PTR [rbp-0x38],r13
 401:	75 cd                	jne    3d0 <Phys::CollisionCellManager::collideCells(std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >&, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >&)+0x30>
 403:	48 83 c4 18          	add    rsp,0x18
 407:	5b                   	pop    rbx
 408:	41 5c                	pop    r12
 40a:	41 5d                	pop    r13
 40c:	41 5e                	pop    r14
 40e:	41 5f                	pop    r15
 410:	5d                   	pop    rbp
 411:	c3                   	ret    
 412:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
 419:	00 00 00 00 
 41d:	0f 1f 00             	nop    DWORD PTR [rax]

0000000000000420 <Phys::CollisionCellManager::resolveCollisions()>:
 420:	55                   	push   rbp
 421:	48 89 e5             	mov    rbp,rsp
 424:	41 57                	push   r15
 426:	41 56                	push   r14
 428:	41 55                	push   r13
 42a:	41 54                	push   r12
 42c:	53                   	push   rbx
 42d:	48 83 ec 68          	sub    rsp,0x68
 431:	ff 15 00 00 00 00    	call   QWORD PTR [rip+0x0]        # 437 <Phys::CollisionCellManager::resolveCollisions()+0x17>
 437:	48 83 3f 00          	cmp    QWORD PTR [rdi],0x0
 43b:	48 89 7d b8          	mov    QWORD PTR [rbp-0x48],rdi
 43f:	0f 84 df 01 00 00    	je     624 <Phys::CollisionCellManager::resolveCollisions()+0x204>
 445:	48 c7 45 88 00 00 00 	mov    QWORD PTR [rbp-0x78],0x0
 44c:	00 
 44d:	48 8b 57 08          	mov    rdx,QWORD PTR [rdi+0x8]
 451:	48 85 d2             	test   rdx,rdx
 454:	0f 84 b5 01 00 00    	je     60f <Phys::CollisionCellManager::resolveCollisions()+0x1ef>
 45a:	48 8b 4d 88          	mov    rcx,QWORD PTR [rbp-0x78]
 45e:	48 c7 45 90 00 00 00 	mov    QWORD PTR [rbp-0x70],0x0
 465:	00 
 466:	48 8d 41 ff          	lea    rax,[rcx-0x1]
 46a:	48 85 c9             	test   rcx,rcx
 46d:	b9 00 00 00 00       	mov    ecx,0x0
 472:	48 0f 44 c1          	cmove  rax,rcx
 476:	48 89 45 80          	mov    QWORD PTR [rbp-0x80],rax
 47a:	48 8b 45 b8          	mov    rax,QWORD PTR [rbp-0x48]
 47e:	48 8b 48 10          	mov    rcx,QWORD PTR [rax+0x10]
 482:	48 85 c9             	test   rcx,rcx
 485:	0f 84 73 01 00 00    	je     5fe <Phys::CollisionCellManager::resolveCollisions()+0x1de>
 48b:	48 8b 7d 90          	mov    rdi,QWORD PTR [rbp-0x70]
 48f:	48 c7 45 b0 00 00 00 	mov    QWORD PTR [rbp-0x50],0x0
 496:	00 
 497:	48 8d 47 ff          	lea    rax,[rdi-0x1]
 49b:	48 85 ff             	test   rdi,rdi
 49e:	bf 00 00 00 00       	mov    edi,0x0
 4a3:	48 0f 44 c7          	cmove  rax,rdi
 4a7:	48 89 85 78 ff ff ff 	mov    QWORD PTR [rbp-0x88],rax
 4ae:	48 8b 7d 88          	mov    rdi,QWORD PTR [rbp-0x78]
 4b2:	48 8b 5d b0          	mov    rbx,QWORD PTR [rbp-0x50]
 4b6:	48 89 f8             	mov    rax,rdi
 4b9:	48 0f af c2          	imul   rax,rdx
 4bd:	48 03 45 90          	add    rax,QWORD PTR [rbp-0x70]
 4c1:	48 0f af c1          	imul   rax,rcx
 4c5:	48 01 d8             	add    rax,rbx
 4c8:	48 8d 34 40          	lea    rsi,[rax+rax*2]
 4cc:	48 8b 45 b8          	mov    rax,QWORD PTR [rbp-0x48]
 4d0:	48 85 db             	test   rbx,rbx
 4d3:	48 8b 40 40          	mov    rax,QWORD PTR [rax+0x40]
 4d7:	48 8d 04 f0          	lea    rax,[rax+rsi*8]
 4db:	48 89 45 98          	mov    QWORD PTR [rbp-0x68],rax
 4df:	be 00 00 00 00       	mov    esi,0x0
 4e4:	48 8d 43 ff          	lea    rax,[rbx-0x1]
 4e8:	48 0f 44 c6          	cmove  rax,rsi
 4ec:	48 89 85 70 ff ff ff 	mov    QWORD PTR [rbp-0x90],rax
 4f3:	48 8b 45 80          	mov    rax,QWORD PTR [rbp-0x80]
 4f7:	48 39 f8             	cmp    rax,rdi
 4fa:	0f 87 ed 00 00 00    	ja     5ed <Phys::CollisionCellManager::resolveCollisions()+0x1cd>
 500:	48 89 45 a0          	mov    QWORD PTR [rbp-0x60],rax
 504:	48 8b 85 78 ff ff ff 	mov    rax,QWORD PTR [rbp-0x88]
 50b:	48 8b 7d 90          	mov    rdi,QWORD PTR [rbp-0x70]
 50f:	48 39 f8             	cmp    rax,rdi
 512:	0f 87 c3 00 00 00    	ja     5db <Phys::CollisionCellManager::resolveCollisions()+0x1bb>
 518:	48 89 45 a8          	mov    QWORD PTR [rbp-0x58],rax
 51c:	48 8b 85 70 ff ff ff 	mov    rax,QWORD PTR [rbp-0x90]
 523:	48 8b 7d b0          	mov    rdi,QWORD PTR [rbp-0x50]
 527:	48 39 f8             	cmp    rax,rdi
 52a:	0f 87 99 00 00 00    	ja     5c9 <Phys::CollisionCellManager::resolveCollisions()+0x1a9>
 530:	48 89 45 c0          	mov    QWORD PTR [rbp-0x40],rax
 534:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
 538:	48 8b 45 a0          	mov    rax,QWORD PTR [rbp-0x60]
 53c:	48 0f af c2          	imul   rax,rdx
 540:	48 03 45 a8          	add    rax,QWORD PTR [rbp-0x58]
 544:	48 0f af c1          	imul   rax,rcx
 548:	48 03 45 c0          	add    rax,QWORD PTR [rbp-0x40]
 54c:	48 8d 34 40          	lea    rsi,[rax+rax*2]
 550:	48 8b 45 b8          	mov    rax,QWORD PTR [rbp-0x48]
 554:	48 8b 40 40          	mov    rax,QWORD PTR [rax+0x40]
 558:	4c 8d 2c f0          	lea    r13,[rax+rsi*8]
 55c:	48 8b 45 98          	mov    rax,QWORD PTR [rbp-0x68]
 560:	4c 8b 20             	mov    r12,QWORD PTR [rax]
 563:	48 8b 40 08          	mov    rax,QWORD PTR [rax+0x8]
 567:	48 89 45 c8          	mov    QWORD PTR [rbp-0x38],rax
 56b:	49 39 c4             	cmp    r12,rax
 56e:	74 47                	je     5b7 <Phys::CollisionCellManager::resolveCollisions()+0x197>
 570:	4d 8b 75 08          	mov    r14,QWORD PTR [r13+0x8]
 574:	49 8b 5d 00          	mov    rbx,QWORD PTR [r13+0x0]
 578:	4d 8b 3c 24          	mov    r15,QWORD PTR [r12]
 57c:	4c 39 f3             	cmp    rbx,r14
 57f:	74 20                	je     5a1 <Phys::CollisionCellManager::resolveCollisions()+0x181>
 581:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
 588:	48 8b 33             	mov    rsi,QWORD PTR [rbx]
 58b:	49 39 f7             	cmp    r15,rsi
 58e:	74 08                	je     598 <Phys::CollisionCellManager::resolveCollisions()+0x178>
 590:	4c 89 ff             	mov    rdi,r15
 593:	e8 00 00 00 00       	call   598 <Phys::CollisionCellManager::resolveCollisions()+0x178>
 598:	48 83 c3 08          	add    rbx,0x8
 59c:	49 39 de             	cmp    r14,rbx
 59f:	75 e7                	jne    588 <Phys::CollisionCellManager::resolveCollisions()+0x168>
 5a1:	49 83 c4 08          	add    r12,0x8
 5a5:	4c 39 65 c8          	cmp    QWORD PTR [rbp-0x38],r12
 5a9:	75 c5                	jne    570 <Phys::CollisionCellManager::resolveCollisions()+0x150>
 5ab:	48 8b 45 b8          	mov    rax,QWORD PTR [rbp-0x48]
 5af:	48 8b 48 10          	mov    rcx,QWORD PTR [rax+0x10]
 5b3:	48 8b 50 08          	mov    rdx,QWORD PTR [rax+0x8]
 5b7:	48 ff 45 c0          	inc    QWORD PTR [rbp-0x40]
 5bb:	48 8b 45 c0          	mov    rax,QWORD PTR [rbp-0x40]
 5bf:	48 3b 45 b0          	cmp    rax,QWORD PTR [rbp-0x50]
 5c3:	0f 86 6f ff ff ff    	jbe    538 <Phys::CollisionCellManager::resolveCollisions()+0x118>
 5c9:	48 ff 45 a8          	inc    QWORD PTR [rbp-0x58]
 5cd:	48 8b 45 a8          	mov    rax,QWORD PTR [rbp-0x58]
 5d1:	48 3b 45 90          	cmp    rax,QWORD PTR [rbp-0x70]
 5d5:	0f 86 41 ff ff ff    	jbe    51c <Phys::CollisionCellManager::resolveCollisions()+0xfc>
 5db:	48 ff 45 a0          	inc    QWORD PTR [rbp-0x60]
 5df:	48 8b 45 a0          	mov    rax,QWORD PTR [rbp-0x60]
 5e3:	48 3b 45 88          	cmp    rax,QWORD PTR [rbp-0x78]
 5e7:	0f 86 17 ff ff ff    	jbe    504 <Phys::CollisionCellManager::resolveCollisions()+0xe4>
 5ed:	48 ff 45 b0          	inc    QWORD PTR [rbp-0x50]
 5f1:	48 8b 45 b0          	mov    rax,QWORD PTR [rbp-0x50]
 5f5:	48 39 c8             	cmp    rax,rcx
 5f8:	0f 82 b0 fe ff ff    	jb     4ae <Phys::CollisionCellManager::resolveCollisions()+0x8e>
 5fe:	48 ff 45 90          	inc    QWORD PTR [rbp-0x70]
 602:	48 8b 45 90          	mov    rax,QWORD PTR [rbp-0x70]
 606:	48 39 d0             	cmp    rax,rdx
 609:	0f 82 73 fe ff ff    	jb     482 <Phys::CollisionCellManager::resolveCollisions()+0x62>
 60f:	48 ff 45 88          	inc    QWORD PTR [rbp-0x78]
 613:	48 8b 4d b8          	mov    rcx,QWORD PTR [rbp-0x48]
 617:	48 8b 45 88          	mov    rax,QWORD PTR [rbp-0x78]
 61b:	48 39 01             	cmp    QWORD PTR [rcx],rax
 61e:	0f 87 2d fe ff ff    	ja     451 <Phys::CollisionCellManager::resolveCollisions()+0x31>
 624:	48 83 c4 68          	add    rsp,0x68
 628:	5b                   	pop    rbx
 629:	41 5c                	pop    r12
 62b:	41 5d                	pop    r13
 62d:	41 5e                	pop    r14
 62f:	41 5f                	pop    r15
 631:	5d                   	pop    rbp
 632:	c3                   	ret    
 633:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
 63a:	00 00 00 00 
 63e:	66 90                	xchg   ax,ax

0000000000000640 <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)>:
 640:	55                   	push   rbp
 641:	48 89 e5             	mov    rbp,rsp
 644:	48 83 e4 e0          	and    rsp,0xffffffffffffffe0
 648:	ff 15 00 00 00 00    	call   QWORD PTR [rip+0x0]        # 64e <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0xe>
 64e:	c5 fa 7e 05 00 00 00 	vmovq  xmm0,QWORD PTR [rip+0x0]        # 656 <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0x16>
 655:	00 
 656:	45 31 c0             	xor    r8d,r8d
 659:	c4 e3 fd 01 c8 40    	vpermpd ymm1,ymm0,0x40
 65f:	c5 fd 28 07          	vmovapd ymm0,YMMWORD PTR [rdi]
 663:	c5 fd 28 1e          	vmovapd ymm3,YMMWORD PTR [rsi]
 667:	c5 f5 58 d0          	vaddpd ymm2,ymm1,ymm0
 66b:	c5 fd 5c c1          	vsubpd ymm0,ymm0,ymm1
 66f:	c5 f1 57 c9          	vxorpd xmm1,xmm1,xmm1
 673:	c5 f5 5c cb          	vsubpd ymm1,ymm1,ymm3
 677:	c5 ed c2 d3 1e       	vcmpgt_oqpd ymm2,ymm2,ymm3
 67c:	c5 fd c2 c1 11       	vcmplt_oqpd ymm0,ymm0,ymm1
 681:	c5 fd 50 d2          	vmovmskpd edx,ymm2
 685:	c5 fd 50 c0          	vmovmskpd eax,ymm0
 689:	c1 e0 04             	shl    eax,0x4
 68c:	09 d0                	or     eax,edx
 68e:	75 10                	jne    6a0 <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0x60>
 690:	44 89 c0             	mov    eax,r8d
 693:	c5 f8 77             	vzeroupper 
 696:	c9                   	leave  
 697:	c3                   	ret    
 698:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
 69f:	00 
 6a0:	a8 01                	test   al,0x1
 6a2:	74 2f                	je     6d3 <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0x93>
 6a4:	c5 fb 10 47 20       	vmovsd xmm0,QWORD PTR [rdi+0x20]
 6a9:	c5 fb 10 0f          	vmovsd xmm1,QWORD PTR [rdi]
 6ad:	c5 f9 57 05 00 00 00 	vxorpd xmm0,xmm0,XMMWORD PTR [rip+0x0]        # 6b5 <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0x75>
 6b4:	00 
 6b5:	c5 fb 11 47 20       	vmovsd QWORD PTR [rdi+0x20],xmm0
 6ba:	c5 f3 58 05 00 00 00 	vaddsd xmm0,xmm1,QWORD PTR [rip+0x0]        # 6c2 <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0x82>
 6c1:	00 
 6c2:	c5 fb 5c 06          	vsubsd xmm0,xmm0,QWORD PTR [rsi]
 6c6:	c4 e2 f1 9d 05 00 00 	vfnmadd132sd xmm0,xmm1,QWORD PTR [rip+0x0]        # 6cf <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0x8f>
 6cd:	00 00 
 6cf:	c5 fb 11 07          	vmovsd QWORD PTR [rdi],xmm0
 6d3:	a8 02                	test   al,0x2
 6d5:	74 32                	je     709 <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0xc9>
 6d7:	c5 fb 10 47 28       	vmovsd xmm0,QWORD PTR [rdi+0x28]
 6dc:	c5 fb 10 4f 08       	vmovsd xmm1,QWORD PTR [rdi+0x8]
 6e1:	c5 f9 57 05 00 00 00 	vxorpd xmm0,xmm0,XMMWORD PTR [rip+0x0]        # 6e9 <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0xa9>
 6e8:	00 
 6e9:	c5 fb 11 47 28       	vmovsd QWORD PTR [rdi+0x28],xmm0
 6ee:	c5 f3 58 05 00 00 00 	vaddsd xmm0,xmm1,QWORD PTR [rip+0x0]        # 6f6 <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0xb6>
 6f5:	00 
 6f6:	c5 fb 5c 46 08       	vsubsd xmm0,xmm0,QWORD PTR [rsi+0x8]
 6fb:	c4 e2 f1 9d 05 00 00 	vfnmadd132sd xmm0,xmm1,QWORD PTR [rip+0x0]        # 704 <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0xc4>
 702:	00 00 
 704:	c5 fb 11 47 08       	vmovsd QWORD PTR [rdi+0x8],xmm0
 709:	a8 04                	test   al,0x4
 70b:	74 32                	je     73f <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0xff>
 70d:	c5 fb 10 47 30       	vmovsd xmm0,QWORD PTR [rdi+0x30]
 712:	c5 fb 10 4f 10       	vmovsd xmm1,QWORD PTR [rdi+0x10]
 717:	c5 f9 57 05 00 00 00 	vxorpd xmm0,xmm0,XMMWORD PTR [rip+0x0]        # 71f <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0xdf>
 71e:	00 
 71f:	c5 fb 11 47 30       	vmovsd QWORD PTR [rdi+0x30],xmm0
 724:	c5 f3 58 05 00 00 00 	vaddsd xmm0,xmm1,QWORD PTR [rip+0x0]        # 72c <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0xec>
 72b:	00 
 72c:	c5 fb 5c 46 10       	vsubsd xmm0,xmm0,QWORD PTR [rsi+0x10]
 731:	c4 e2 f1 9d 05 00 00 	vfnmadd132sd xmm0,xmm1,QWORD PTR [rip+0x0]        # 73a <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0xfa>
 738:	00 00 
 73a:	c5 fb 11 47 10       	vmovsd QWORD PTR [rdi+0x10],xmm0
 73f:	a8 10                	test   al,0x10
 741:	74 37                	je     77a <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0x13a>
 743:	c5 fb 10 4f 20       	vmovsd xmm1,QWORD PTR [rdi+0x20]
 748:	c5 fa 7e 05 00 00 00 	vmovq  xmm0,QWORD PTR [rip+0x0]        # 750 <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0x110>
 74f:	00 
 750:	c5 f1 57 c8          	vxorpd xmm1,xmm1,xmm0
 754:	c5 fb 11 4f 20       	vmovsd QWORD PTR [rdi+0x20],xmm1
 759:	c5 fb 10 0f          	vmovsd xmm1,QWORD PTR [rdi]
 75d:	c5 f1 57 c0          	vxorpd xmm0,xmm1,xmm0
 761:	c5 fb 5c 06          	vsubsd xmm0,xmm0,QWORD PTR [rsi]
 765:	c5 fb 58 05 00 00 00 	vaddsd xmm0,xmm0,QWORD PTR [rip+0x0]        # 76d <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0x12d>
 76c:	00 
 76d:	c4 e2 f1 99 05 00 00 	vfmadd132sd xmm0,xmm1,QWORD PTR [rip+0x0]        # 776 <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0x136>
 774:	00 00 
 776:	c5 fb 11 07          	vmovsd QWORD PTR [rdi],xmm0
 77a:	a8 20                	test   al,0x20
 77c:	74 3a                	je     7b8 <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0x178>
 77e:	c5 fb 10 4f 28       	vmovsd xmm1,QWORD PTR [rdi+0x28]
 783:	c5 fa 7e 05 00 00 00 	vmovq  xmm0,QWORD PTR [rip+0x0]        # 78b <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0x14b>
 78a:	00 
 78b:	c5 f1 57 c8          	vxorpd xmm1,xmm1,xmm0
 78f:	c5 fb 11 4f 28       	vmovsd QWORD PTR [rdi+0x28],xmm1
 794:	c5 fb 10 4f 08       	vmovsd xmm1,QWORD PTR [rdi+0x8]
 799:	c5 f1 57 c0          	vxorpd xmm0,xmm1,xmm0
 79d:	c5 fb 5c 46 08       	vsubsd xmm0,xmm0,QWORD PTR [rsi+0x8]
 7a2:	c5 fb 58 05 00 00 00 	vaddsd xmm0,xmm0,QWORD PTR [rip+0x0]        # 7aa <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0x16a>
 7a9:	00 
 7aa:	c4 e2 f1 99 05 00 00 	vfmadd132sd xmm0,xmm1,QWORD PTR [rip+0x0]        # 7b3 <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0x173>
 7b1:	00 00 
 7b3:	c5 fb 11 47 08       	vmovsd QWORD PTR [rdi+0x8],xmm0
 7b8:	41 b8 01 00 00 00    	mov    r8d,0x1
 7be:	a8 40                	test   al,0x40
 7c0:	0f 84 ca fe ff ff    	je     690 <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0x50>
 7c6:	c5 fb 10 4f 30       	vmovsd xmm1,QWORD PTR [rdi+0x30]
 7cb:	c5 fa 7e 05 00 00 00 	vmovq  xmm0,QWORD PTR [rip+0x0]        # 7d3 <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0x193>
 7d2:	00 
 7d3:	c5 f1 57 c8          	vxorpd xmm1,xmm1,xmm0
 7d7:	c5 fb 11 4f 30       	vmovsd QWORD PTR [rdi+0x30],xmm1
 7dc:	c5 fb 10 4f 10       	vmovsd xmm1,QWORD PTR [rdi+0x10]
 7e1:	c5 f1 57 c0          	vxorpd xmm0,xmm1,xmm0
 7e5:	c5 fb 5c 46 10       	vsubsd xmm0,xmm0,QWORD PTR [rsi+0x10]
 7ea:	c5 fb 58 05 00 00 00 	vaddsd xmm0,xmm0,QWORD PTR [rip+0x0]        # 7f2 <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0x1b2>
 7f1:	00 
 7f2:	c4 e2 f1 99 05 00 00 	vfmadd132sd xmm0,xmm1,QWORD PTR [rip+0x0]        # 7fb <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0x1bb>
 7f9:	00 00 
 7fb:	c5 fb 11 47 10       	vmovsd QWORD PTR [rdi+0x10],xmm0
 800:	e9 8b fe ff ff       	jmp    690 <Phys::ResolveCollision(Phys::GasUnit&, Phys::ContainerCollider const&)+0x50>
 805:	90                   	nop
 806:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
 80d:	00 00 00 

0000000000000810 <Phys::CollisionCellManager::registerUnits(std::vector<Phys::GasUnit, std::allocator<Phys::GasUnit> >&)>:
 810:	55                   	push   rbp
 811:	48 89 e5             	mov    rbp,rsp
 814:	41 57                	push   r15
 816:	41 56                	push   r14
 818:	41 55                	push   r13
 81a:	41 54                	push   r12
 81c:	53                   	push   rbx
 81d:	48 83 ec 18          	sub    rsp,0x18
 821:	ff 15 00 00 00 00    	call   QWORD PTR [rip+0x0]        # 827 <Phys::CollisionCellManager::registerUnits(std::vector<Phys::GasUnit, std::allocator<Phys::GasUnit> >&)+0x17>
 827:	48 8b 57 18          	mov    rdx,QWORD PTR [rdi+0x18]
 82b:	49 89 ff             	mov    r15,rdi
 82e:	48 85 d2             	test   rdx,rdx
 831:	74 2a                	je     85d <Phys::CollisionCellManager::registerUnits(std::vector<Phys::GasUnit, std::allocator<Phys::GasUnit> >&)+0x4d>
 833:	48 8b 4f 40          	mov    rcx,QWORD PTR [rdi+0x40]
 837:	48 8d 14 52          	lea    rdx,[rdx+rdx*2]
 83b:	48 8d 41 08          	lea    rax,[rcx+0x8]
 83f:	48 8d 4c d1 08       	lea    rcx,[rcx+rdx*8+0x8]
 844:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
 848:	48 8b 50 f8          	mov    rdx,QWORD PTR [rax-0x8]
 84c:	48 39 10             	cmp    QWORD PTR [rax],rdx
 84f:	74 03                	je     854 <Phys::CollisionCellManager::registerUnits(std::vector<Phys::GasUnit, std::allocator<Phys::GasUnit> >&)+0x44>
 851:	48 89 10             	mov    QWORD PTR [rax],rdx
 854:	48 83 c0 18          	add    rax,0x18
 858:	48 39 c8             	cmp    rax,rcx
 85b:	75 eb                	jne    848 <Phys::CollisionCellManager::registerUnits(std::vector<Phys::GasUnit, std::allocator<Phys::GasUnit> >&)+0x38>
 85d:	4c 8b 36             	mov    r14,QWORD PTR [rsi]
 860:	4c 8b 66 08          	mov    r12,QWORD PTR [rsi+0x8]
 864:	4d 8d 6f 60          	lea    r13,[r15+0x60]
 868:	48 bb 00 00 00 00 00 	movabs rbx,0x8000000000000000
 86f:	00 00 80 
 872:	4d 39 e6             	cmp    r14,r12
 875:	0f 85 8e 00 00 00    	jne    909 <Phys::CollisionCellManager::registerUnits(std::vector<Phys::GasUnit, std::allocator<Phys::GasUnit> >&)+0xf9>
 87b:	e9 16 01 00 00       	jmp    996 <Phys::CollisionCellManager::registerUnits(std::vector<Phys::GasUnit, std::allocator<Phys::GasUnit> >&)+0x186>
 880:	c4 e1 fb 2c c1       	vcvttsd2si rax,xmm1
 885:	c4 c1 7b 10 4e 08    	vmovsd xmm1,QWORD PTR [r14+0x8]
 88b:	49 0f af 47 08       	imul   rax,QWORD PTR [r15+0x8]
 890:	c4 c1 73 58 4f 28    	vaddsd xmm1,xmm1,QWORD PTR [r15+0x28]
 896:	c5 f3 5e cb          	vdivsd xmm1,xmm1,xmm3
 89a:	c5 f9 2f ca          	vcomisd xmm1,xmm2
 89e:	0f 83 c4 00 00 00    	jae    968 <Phys::CollisionCellManager::registerUnits(std::vector<Phys::GasUnit, std::allocator<Phys::GasUnit> >&)+0x158>
 8a4:	c4 e1 fb 2c d1       	vcvttsd2si rdx,xmm1
 8a9:	c4 c1 7b 10 46 10    	vmovsd xmm0,QWORD PTR [r14+0x10]
 8af:	48 01 d0             	add    rax,rdx
 8b2:	c4 c1 7b 58 47 30    	vaddsd xmm0,xmm0,QWORD PTR [r15+0x30]
 8b8:	49 0f af 47 10       	imul   rax,QWORD PTR [r15+0x10]
 8bd:	c5 fb 5e c3          	vdivsd xmm0,xmm0,xmm3
 8c1:	c5 f9 2f c2          	vcomisd xmm0,xmm2
 8c5:	0f 83 85 00 00 00    	jae    950 <Phys::CollisionCellManager::registerUnits(std::vector<Phys::GasUnit, std::allocator<Phys::GasUnit> >&)+0x140>
 8cb:	c4 e1 fb 2c d0       	vcvttsd2si rdx,xmm0
 8d0:	48 01 d0             	add    rax,rdx
 8d3:	48 8d 14 40          	lea    rdx,[rax+rax*2]
 8d7:	49 8b 47 40          	mov    rax,QWORD PTR [r15+0x40]
 8db:	4c 89 75 c8          	mov    QWORD PTR [rbp-0x38],r14
 8df:	48 8d 3c d0          	lea    rdi,[rax+rdx*8]
 8e3:	48 8b 77 08          	mov    rsi,QWORD PTR [rdi+0x8]
 8e7:	48 3b 77 10          	cmp    rsi,QWORD PTR [rdi+0x10]
 8eb:	0f 84 8f 00 00 00    	je     980 <Phys::CollisionCellManager::registerUnits(std::vector<Phys::GasUnit, std::allocator<Phys::GasUnit> >&)+0x170>
 8f1:	4c 89 36             	mov    QWORD PTR [rsi],r14
 8f4:	48 83 c6 08          	add    rsi,0x8
 8f8:	49 83 c6 40          	add    r14,0x40
 8fc:	48 89 77 08          	mov    QWORD PTR [rdi+0x8],rsi
 900:	4d 39 f4             	cmp    r12,r14
 903:	0f 84 8d 00 00 00    	je     996 <Phys::CollisionCellManager::registerUnits(std::vector<Phys::GasUnit, std::allocator<Phys::GasUnit> >&)+0x186>
 909:	4c 89 ee             	mov    rsi,r13
 90c:	4c 89 f7             	mov    rdi,r14
 90f:	e8 00 00 00 00       	call   914 <Phys::CollisionCellManager::registerUnits(std::vector<Phys::GasUnit, std::allocator<Phys::GasUnit> >&)+0x104>
 914:	c4 c1 7b 10 0e       	vmovsd xmm1,QWORD PTR [r14]
 919:	c4 c1 7b 10 5f 38    	vmovsd xmm3,QWORD PTR [r15+0x38]
 91f:	c4 c1 73 58 4f 20    	vaddsd xmm1,xmm1,QWORD PTR [r15+0x20]
 925:	48 8b 05 00 00 00 00 	mov    rax,QWORD PTR [rip+0x0]        # 92c <Phys::CollisionCellManager::registerUnits(std::vector<Phys::GasUnit, std::allocator<Phys::GasUnit> >&)+0x11c>
 92c:	c5 f3 5e cb          	vdivsd xmm1,xmm1,xmm3
 930:	c4 e1 f9 6e d0       	vmovq  xmm2,rax
 935:	c5 f9 2f ca          	vcomisd xmm1,xmm2
 939:	0f 82 41 ff ff ff    	jb     880 <Phys::CollisionCellManager::registerUnits(std::vector<Phys::GasUnit, std::allocator<Phys::GasUnit> >&)+0x70>
 93f:	c5 f3 5c ca          	vsubsd xmm1,xmm1,xmm2
 943:	c4 e1 fb 2c c1       	vcvttsd2si rax,xmm1
 948:	48 31 d8             	xor    rax,rbx
 94b:	e9 35 ff ff ff       	jmp    885 <Phys::CollisionCellManager::registerUnits(std::vector<Phys::GasUnit, std::allocator<Phys::GasUnit> >&)+0x75>
 950:	c5 fb 5c c2          	vsubsd xmm0,xmm0,xmm2
 954:	c4 e1 fb 2c d0       	vcvttsd2si rdx,xmm0
 959:	48 31 da             	xor    rdx,rbx
 95c:	e9 6f ff ff ff       	jmp    8d0 <Phys::CollisionCellManager::registerUnits(std::vector<Phys::GasUnit, std::allocator<Phys::GasUnit> >&)+0xc0>
 961:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
 968:	c5 f3 5c ca          	vsubsd xmm1,xmm1,xmm2
 96c:	c4 e1 fb 2c d1       	vcvttsd2si rdx,xmm1
 971:	48 31 da             	xor    rdx,rbx
 974:	e9 30 ff ff ff       	jmp    8a9 <Phys::CollisionCellManager::registerUnits(std::vector<Phys::GasUnit, std::allocator<Phys::GasUnit> >&)+0x99>
 979:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
 980:	48 8d 55 c8          	lea    rdx,[rbp-0x38]
 984:	49 83 c6 40          	add    r14,0x40
 988:	e8 00 00 00 00       	call   98d <Phys::CollisionCellManager::registerUnits(std::vector<Phys::GasUnit, std::allocator<Phys::GasUnit> >&)+0x17d>
 98d:	4d 39 f4             	cmp    r12,r14
 990:	0f 85 73 ff ff ff    	jne    909 <Phys::CollisionCellManager::registerUnits(std::vector<Phys::GasUnit, std::allocator<Phys::GasUnit> >&)+0xf9>
 996:	48 83 c4 18          	add    rsp,0x18
 99a:	5b                   	pop    rbx
 99b:	41 5c                	pop    r12
 99d:	41 5d                	pop    r13
 99f:	41 5e                	pop    r14
 9a1:	41 5f                	pop    r15
 9a3:	5d                   	pop    rbp
 9a4:	c3                   	ret    

Disassembly of section .text._ZNSt6vectorIPN4Phys7GasUnitESaIS2_EE17_M_realloc_insertIJS2_EEEvN9__gnu_cxx17__normal_iteratorIPS2_S4_EEDpOT_:

0000000000000000 <void std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >::_M_realloc_insert<Phys::GasUnit*>(__gnu_cxx::__normal_iterator<Phys::GasUnit**, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> > >, Phys::GasUnit*&&)>:
   0:	55                   	push   rbp
   1:	48 89 e5             	mov    rbp,rsp
   4:	41 57                	push   r15
   6:	41 56                	push   r14
   8:	41 55                	push   r13
   a:	41 54                	push   r12
   c:	53                   	push   rbx
   d:	48 83 ec 28          	sub    rsp,0x28
  11:	ff 15 00 00 00 00    	call   QWORD PTR [rip+0x0]        # 17 <void std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >::_M_realloc_insert<Phys::GasUnit*>(__gnu_cxx::__normal_iterator<Phys::GasUnit**, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> > >, Phys::GasUnit*&&)+0x17>
  17:	48 bb ff ff ff ff ff 	movabs rbx,0xfffffffffffffff
  1e:	ff ff 0f 
  21:	4c 8b 77 08          	mov    r14,QWORD PTR [rdi+0x8]
  25:	4c 8b 07             	mov    r8,QWORD PTR [rdi]
  28:	4c 89 f0             	mov    rax,r14
  2b:	4c 29 c0             	sub    rax,r8
  2e:	48 c1 f8 03          	sar    rax,0x3
  32:	49 89 fc             	mov    r12,rdi
  35:	49 89 f5             	mov    r13,rsi
  38:	49 89 d7             	mov    r15,rdx
  3b:	48 39 d8             	cmp    rax,rbx
  3e:	0f 84 35 01 00 00    	je     179 <void std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >::_M_realloc_insert<Phys::GasUnit*>(__gnu_cxx::__normal_iterator<Phys::GasUnit**, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> > >, Phys::GasUnit*&&)+0x179>
  44:	48 85 c0             	test   rax,rax
  47:	ba 01 00 00 00       	mov    edx,0x1
  4c:	48 0f 45 d0          	cmovne rdx,rax
  50:	31 c9                	xor    ecx,ecx
  52:	48 01 d0             	add    rax,rdx
  55:	0f 92 c1             	setb   cl
  58:	48 89 f2             	mov    rdx,rsi
  5b:	4c 29 c2             	sub    rdx,r8
  5e:	48 85 c9             	test   rcx,rcx
  61:	0f 85 d1 00 00 00    	jne    138 <void std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >::_M_realloc_insert<Phys::GasUnit*>(__gnu_cxx::__normal_iterator<Phys::GasUnit**, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> > >, Phys::GasUnit*&&)+0x138>
  67:	48 85 c0             	test   rax,rax
  6a:	0f 85 f8 00 00 00    	jne    168 <void std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >::_M_realloc_insert<Phys::GasUnit*>(__gnu_cxx::__normal_iterator<Phys::GasUnit**, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> > >, Phys::GasUnit*&&)+0x168>
  70:	31 db                	xor    ebx,ebx
  72:	49 8b 07             	mov    rax,QWORD PTR [r15]
  75:	4d 89 f2             	mov    r10,r14
  78:	4c 8d 4c 11 08       	lea    r9,[rcx+rdx*1+0x8]
  7d:	4d 29 ea             	sub    r10,r13
  80:	48 89 04 11          	mov    QWORD PTR [rcx+rdx*1],rax
  84:	4d 8b 74 24 10       	mov    r14,QWORD PTR [r12+0x10]
  89:	4f 8d 3c 11          	lea    r15,[r9+r10*1]
  8d:	48 85 d2             	test   rdx,rdx
  90:	7f 2e                	jg     c0 <void std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >::_M_realloc_insert<Phys::GasUnit*>(__gnu_cxx::__normal_iterator<Phys::GasUnit**, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> > >, Phys::GasUnit*&&)+0xc0>
  92:	4d 85 d2             	test   r10,r10
  95:	7f 71                	jg     108 <void std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >::_M_realloc_insert<Phys::GasUnit*>(__gnu_cxx::__normal_iterator<Phys::GasUnit**, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> > >, Phys::GasUnit*&&)+0x108>
  97:	4d 85 c0             	test   r8,r8
  9a:	75 4f                	jne    eb <void std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >::_M_realloc_insert<Phys::GasUnit*>(__gnu_cxx::__normal_iterator<Phys::GasUnit**, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> > >, Phys::GasUnit*&&)+0xeb>
  9c:	4d 89 7c 24 08       	mov    QWORD PTR [r12+0x8],r15
  a1:	49 89 5c 24 10       	mov    QWORD PTR [r12+0x10],rbx
  a6:	49 89 0c 24          	mov    QWORD PTR [r12],rcx
  aa:	48 83 c4 28          	add    rsp,0x28
  ae:	5b                   	pop    rbx
  af:	41 5c                	pop    r12
  b1:	41 5d                	pop    r13
  b3:	41 5e                	pop    r14
  b5:	41 5f                	pop    r15
  b7:	5d                   	pop    rbp
  b8:	c3                   	ret    
  b9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  c0:	4c 89 c6             	mov    rsi,r8
  c3:	48 89 cf             	mov    rdi,rcx
  c6:	4c 89 55 b8          	mov    QWORD PTR [rbp-0x48],r10
  ca:	4c 89 4d c0          	mov    QWORD PTR [rbp-0x40],r9
  ce:	4c 89 45 c8          	mov    QWORD PTR [rbp-0x38],r8
  d2:	e8 00 00 00 00       	call   d7 <void std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >::_M_realloc_insert<Phys::GasUnit*>(__gnu_cxx::__normal_iterator<Phys::GasUnit**, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> > >, Phys::GasUnit*&&)+0xd7>
  d7:	4c 8b 55 b8          	mov    r10,QWORD PTR [rbp-0x48]
  db:	4c 8b 45 c8          	mov    r8,QWORD PTR [rbp-0x38]
  df:	4d 85 d2             	test   r10,r10
  e2:	4c 8b 4d c0          	mov    r9,QWORD PTR [rbp-0x40]
  e6:	48 89 c1             	mov    rcx,rax
  e9:	7f 1d                	jg     108 <void std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >::_M_realloc_insert<Phys::GasUnit*>(__gnu_cxx::__normal_iterator<Phys::GasUnit**, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> > >, Phys::GasUnit*&&)+0x108>
  eb:	4c 89 f6             	mov    rsi,r14
  ee:	4c 29 c6             	sub    rsi,r8
  f1:	4c 89 c7             	mov    rdi,r8
  f4:	48 89 4d c8          	mov    QWORD PTR [rbp-0x38],rcx
  f8:	e8 00 00 00 00       	call   fd <void std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >::_M_realloc_insert<Phys::GasUnit*>(__gnu_cxx::__normal_iterator<Phys::GasUnit**, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> > >, Phys::GasUnit*&&)+0xfd>
  fd:	48 8b 4d c8          	mov    rcx,QWORD PTR [rbp-0x38]
 101:	eb 99                	jmp    9c <void std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >::_M_realloc_insert<Phys::GasUnit*>(__gnu_cxx::__normal_iterator<Phys::GasUnit**, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> > >, Phys::GasUnit*&&)+0x9c>
 103:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
 108:	4c 89 d2             	mov    rdx,r10
 10b:	4c 89 ee             	mov    rsi,r13
 10e:	4c 89 cf             	mov    rdi,r9
 111:	4c 89 45 c0          	mov    QWORD PTR [rbp-0x40],r8
 115:	48 89 4d c8          	mov    QWORD PTR [rbp-0x38],rcx
 119:	e8 00 00 00 00       	call   11e <void std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >::_M_realloc_insert<Phys::GasUnit*>(__gnu_cxx::__normal_iterator<Phys::GasUnit**, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> > >, Phys::GasUnit*&&)+0x11e>
 11e:	4c 8b 45 c0          	mov    r8,QWORD PTR [rbp-0x40]
 122:	48 8b 4d c8          	mov    rcx,QWORD PTR [rbp-0x38]
 126:	4d 85 c0             	test   r8,r8
 129:	0f 84 6d ff ff ff    	je     9c <void std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >::_M_realloc_insert<Phys::GasUnit*>(__gnu_cxx::__normal_iterator<Phys::GasUnit**, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> > >, Phys::GasUnit*&&)+0x9c>
 12f:	eb ba                	jmp    eb <void std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >::_M_realloc_insert<Phys::GasUnit*>(__gnu_cxx::__normal_iterator<Phys::GasUnit**, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> > >, Phys::GasUnit*&&)+0xeb>
 131:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
 138:	48 bb f8 ff ff ff ff 	movabs rbx,0x7ffffffffffffff8
 13f:	ff ff 7f 
 142:	48 89 df             	mov    rdi,rbx
 145:	48 89 55 c0          	mov    QWORD PTR [rbp-0x40],rdx
 149:	4c 89 45 c8          	mov    QWORD PTR [rbp-0x38],r8
 14d:	e8 00 00 00 00       	call   152 <void std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >::_M_realloc_insert<Phys::GasUnit*>(__gnu_cxx::__normal_iterator<Phys::GasUnit**, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> > >, Phys::GasUnit*&&)+0x152>
 152:	48 89 c1             	mov    rcx,rax
 155:	4c 8b 45 c8          	mov    r8,QWORD PTR [rbp-0x38]
 159:	48 8b 55 c0          	mov    rdx,QWORD PTR [rbp-0x40]
 15d:	48 01 c3             	add    rbx,rax
 160:	e9 0d ff ff ff       	jmp    72 <void std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >::_M_realloc_insert<Phys::GasUnit*>(__gnu_cxx::__normal_iterator<Phys::GasUnit**, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> > >, Phys::GasUnit*&&)+0x72>
 165:	0f 1f 00             	nop    DWORD PTR [rax]
 168:	48 39 d8             	cmp    rax,rbx
 16b:	48 0f 47 c3          	cmova  rax,rbx
 16f:	48 8d 1c c5 00 00 00 	lea    rbx,[rax*8+0x0]
 176:	00 
 177:	eb c9                	jmp    142 <void std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >::_M_realloc_insert<Phys::GasUnit*>(__gnu_cxx::__normal_iterator<Phys::GasUnit**, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> > >, Phys::GasUnit*&&)+0x142>
 179:	48 8d 3d 00 00 00 00 	lea    rdi,[rip+0x0]        # 180 <void std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> >::_M_realloc_insert<Phys::GasUnit*>(__gnu_cxx::__normal_iterator<Phys::GasUnit**, std::vector<Phys::GasUnit*, std::allocator<Phys::GasUnit*> > >, Phys::GasUnit*&&)+0x180>
 180:	e8 00 00 00 00       	call   185 <.LC6+0x165>

Disassembly of section .text.startup:

0000000000000000 <_GLOBAL__sub_I__ZN4Phys20CollisionCellManagerC2Edddd>:
   0:	55                   	push   rbp
   1:	48 89 e5             	mov    rbp,rsp
   4:	ff 15 00 00 00 00    	call   QWORD PTR [rip+0x0]        # a <_GLOBAL__sub_I__ZN4Phys20CollisionCellManagerC2Edddd+0xa>
   a:	48 8d 3d 00 00 00 00 	lea    rdi,[rip+0x0]        # 11 <_GLOBAL__sub_I__ZN4Phys20CollisionCellManagerC2Edddd+0x11>
  11:	e8 00 00 00 00       	call   16 <_GLOBAL__sub_I__ZN4Phys20CollisionCellManagerC2Edddd+0x16>
  16:	48 8b 3d 00 00 00 00 	mov    rdi,QWORD PTR [rip+0x0]        # 1d <_GLOBAL__sub_I__ZN4Phys20CollisionCellManagerC2Edddd+0x1d>
  1d:	48 8d 15 00 00 00 00 	lea    rdx,[rip+0x0]        # 24 <_GLOBAL__sub_I__ZN4Phys20CollisionCellManagerC2Edddd+0x24>
  24:	48 8d 35 00 00 00 00 	lea    rsi,[rip+0x0]        # 2b <_GLOBAL__sub_I__ZN4Phys20CollisionCellManagerC2Edddd+0x2b>
  2b:	5d                   	pop    rbp
  2c:	e9 00 00 00 00       	jmp    31 <.LC6+0x11>
