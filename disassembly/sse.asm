
build/CMakeFiles/cesu8_benchmark_sse.dir/src/cesu8_SSE.cpp.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <_ZN5cesu818is_valid_cesu8_SSEEPKhm>:
   0:	f3 0f 1e fa          	repz nop edx
   4:	41 54                	push   r12
   6:	55                   	push   rbp
   7:	48 89 f5             	mov    rbp,rsi
   a:	53                   	push   rbx
   b:	0f b6 05 00 00 00 00 	movzx  eax,BYTE PTR [rip+0x0]        # 12 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x12>
  12:	48 89 fb             	mov    rbx,rdi
  15:	84 c0                	test   al,al
  17:	0f 84 ab 02 00 00    	je     2c8 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x2c8>
  1d:	0f b6 05 00 00 00 00 	movzx  eax,BYTE PTR [rip+0x0]        # 24 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x24>
  24:	84 c0                	test   al,al
  26:	0f 84 64 02 00 00    	je     290 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x290>
  2c:	0f b6 05 00 00 00 00 	movzx  eax,BYTE PTR [rip+0x0]        # 33 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x33>
  33:	84 c0                	test   al,al
  35:	0f 84 1d 02 00 00    	je     258 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x258>
  3b:	0f b6 05 00 00 00 00 	movzx  eax,BYTE PTR [rip+0x0]        # 42 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x42>
  42:	84 c0                	test   al,al
  44:	0f 84 d6 01 00 00    	je     220 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x220>
  4a:	48 83 fd 0f          	cmp    rbp,0xf
  4e:	0f 86 b4 01 00 00    	jbe    208 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x208>
  54:	48 8d 45 f0          	lea    rax,[rbp-0x10]
  58:	66 0f ef f6          	pxor   xmm6,xmm6
  5c:	66 44 0f 6f 2d 00 00 	movdqa xmm13,XMMWORD PTR [rip+0x0]        # 65 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x65>
  63:	00 00 
  65:	66 44 0f 6f 25 00 00 	movdqa xmm12,XMMWORD PTR [rip+0x0]        # 6e <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x6e>
  6c:	00 00 
  6e:	48 83 e0 f0          	and    rax,0xfffffffffffffff0
  72:	66 0f 6f e6          	movdqa xmm4,xmm6
  76:	66 0f 6f de          	movdqa xmm3,xmm6
  7a:	66 44 0f 6f 1d 00 00 	movdqa xmm11,XMMWORD PTR [rip+0x0]        # 83 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x83>
  81:	00 00 
  83:	66 44 0f 6f 15 00 00 	movdqa xmm10,XMMWORD PTR [rip+0x0]        # 8c <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x8c>
  8a:	00 00 
  8c:	48 8d 7c 03 10       	lea    rdi,[rbx+rax*1+0x10]
  91:	66 0f 6f 2d 00 00 00 	movdqa xmm5,XMMWORD PTR [rip+0x0]        # 99 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x99>
  98:	00 
  99:	66 44 0f 6f 0d 00 00 	movdqa xmm9,XMMWORD PTR [rip+0x0]        # a2 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0xa2>
  a0:	00 00 
  a2:	66 44 0f 6f 05 00 00 	movdqa xmm8,XMMWORD PTR [rip+0x0]        # ab <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0xab>
  a9:	00 00 
  ab:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  b0:	66 0f 6f d4          	movdqa xmm2,xmm4
  b4:	f3 0f 6f 23          	movdqu xmm4,XMMWORD PTR [rbx]
  b8:	66 45 0f 6f fc       	movdqa xmm15,xmm12
  bd:	48 83 c3 10          	add    rbx,0x10
  c1:	66 45 0f 6f f5       	movdqa xmm14,xmm13
  c6:	66 0f 6f c4          	movdqa xmm0,xmm4
  ca:	66 0f 6f cc          	movdqa xmm1,xmm4
  ce:	66 0f 3a 0f ca 0e    	palignr xmm1,xmm2,0xe
  d4:	66 0f 3a 0f c2 0f    	palignr xmm0,xmm2,0xf
  da:	66 0f 6f d4          	movdqa xmm2,xmm4
  de:	66 0f 71 d0 04       	psrlw  xmm0,0x4
  e3:	66 0f 71 d2 04       	psrlw  xmm2,0x4
  e8:	66 0f 6f f9          	movdqa xmm7,xmm1
  ec:	66 0f db c5          	pand   xmm0,xmm5
  f0:	66 0f 71 d7 04       	psrlw  xmm7,0x4
  f5:	66 0f db cd          	pand   xmm1,xmm5
  f9:	66 44 0f 38 00 f8    	pshufb xmm15,xmm0
  ff:	66 0f db fd          	pand   xmm7,xmm5
 103:	66 41 0f 6f c3       	movdqa xmm0,xmm11
 108:	66 0f 38 00 c7       	pshufb xmm0,xmm7
 10d:	66 41 0f 6f fa       	movdqa xmm7,xmm10
 112:	66 0f db d5          	pand   xmm2,xmm5
 116:	66 0f 38 00 f9       	pshufb xmm7,xmm1
 11b:	66 44 0f 38 00 f2    	pshufb xmm14,xmm2
 121:	66 0f db c7          	pand   xmm0,xmm7
 125:	66 0f 74 15 00 00 00 	pcmpeqb xmm2,XMMWORD PTR [rip+0x0]        # 12d <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x12d>
 12c:	00 
 12d:	66 41 0f db c7       	pand   xmm0,xmm15
 132:	66 44 0f 6f fe       	movdqa xmm15,xmm6
 137:	66 0f 6f f0          	movdqa xmm6,xmm0
 13b:	66 0f 6f f8          	movdqa xmm7,xmm0
 13f:	66 41 0f db c6       	pand   xmm0,xmm14
 144:	66 41 0f db f1       	pand   xmm6,xmm9
 149:	66 41 0f db f8       	pand   xmm7,xmm8
 14e:	66 0f eb c2          	por    xmm0,xmm2
 152:	66 0f 6f ce          	movdqa xmm1,xmm6
 156:	66 0f 71 f7 01       	psllw  xmm7,0x1
 15b:	66 41 0f 3a 0f cf 0d 	palignr xmm1,xmm15,0xd
 162:	66 0f ef cf          	pxor   xmm1,xmm7
 166:	66 0f eb cb          	por    xmm1,xmm3
 16a:	66 0f 6f d8          	movdqa xmm3,xmm0
 16e:	66 0f eb d9          	por    xmm3,xmm1
 172:	48 39 fb             	cmp    rbx,rdi
 175:	0f 85 35 ff ff ff    	jne    b0 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0xb0>
 17b:	83 e5 0f             	and    ebp,0xf
 17e:	66 0f 38 17 db       	ptest  xmm3,xmm3
 183:	0f 85 8d 00 00 00    	jne    216 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x216>
 189:	66 0f d7 c6          	pmovmskb eax,xmm6
 18d:	25 00 e0 00 00       	and    eax,0xe000
 192:	3d 00 20 00 00       	cmp    eax,0x2000
 197:	74 4f                	je     1e8 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x1e8>
 199:	3d 00 40 00 00       	cmp    eax,0x4000
 19e:	0f 84 74 01 00 00    	je     318 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x318>
 1a4:	3d 00 80 00 00       	cmp    eax,0x8000
 1a9:	0f 84 51 01 00 00    	je     300 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x300>
 1af:	0f b6 47 fe          	movzx  eax,BYTE PTR [rdi-0x2]
 1b3:	83 e0 f0             	and    eax,0xfffffff0
 1b6:	3c e0                	cmp    al,0xe0
 1b8:	0f 84 75 01 00 00    	je     333 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x333>
 1be:	0f b6 47 ff          	movzx  eax,BYTE PTR [rdi-0x1]
 1c2:	31 f6                	xor    esi,esi
 1c4:	5b                   	pop    rbx
 1c5:	83 e0 c0             	and    eax,0xffffffc0
 1c8:	3c c0                	cmp    al,0xc0
 1ca:	40 0f 94 c6          	sete   sil
 1ce:	48 89 f0             	mov    rax,rsi
 1d1:	48 01 ee             	add    rsi,rbp
 1d4:	5d                   	pop    rbp
 1d5:	41 5c                	pop    r12
 1d7:	48 f7 d8             	neg    rax
 1da:	48 01 c7             	add    rdi,rax
 1dd:	e9 00 00 00 00       	jmp    1e2 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x1e2>
 1e2:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
 1e8:	48 c7 c0 fb ff ff ff 	mov    rax,0xfffffffffffffffb
 1ef:	be 05 00 00 00       	mov    esi,0x5
 1f4:	5b                   	pop    rbx
 1f5:	48 01 ee             	add    rsi,rbp
 1f8:	48 01 c7             	add    rdi,rax
 1fb:	5d                   	pop    rbp
 1fc:	41 5c                	pop    r12
 1fe:	e9 00 00 00 00       	jmp    203 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x203>
 203:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
 208:	66 0f ef c0          	pxor   xmm0,xmm0
 20c:	48 89 df             	mov    rdi,rbx
 20f:	66 0f 38 17 c0       	ptest  xmm0,xmm0
 214:	74 99                	je     1af <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x1af>
 216:	5b                   	pop    rbx
 217:	31 c0                	xor    eax,eax
 219:	5d                   	pop    rbp
 21a:	41 5c                	pop    r12
 21c:	c3                   	ret    
 21d:	0f 1f 00             	nop    DWORD PTR [rax]
 220:	4c 8d 25 00 00 00 00 	lea    r12,[rip+0x0]        # 227 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x227>
 227:	4c 89 e7             	mov    rdi,r12
 22a:	e8 00 00 00 00       	call   22f <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x22f>
 22f:	85 c0                	test   eax,eax
 231:	0f 84 13 fe ff ff    	je     4a <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x4a>
 237:	66 0f 6f 05 00 00 00 	movdqa xmm0,XMMWORD PTR [rip+0x0]        # 23f <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x23f>
 23e:	00 
 23f:	4c 89 e7             	mov    rdi,r12
 242:	0f 29 05 00 00 00 00 	movaps XMMWORD PTR [rip+0x0],xmm0        # 249 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x249>
 249:	e8 00 00 00 00       	call   24e <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x24e>
 24e:	e9 f7 fd ff ff       	jmp    4a <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x4a>
 253:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
 258:	4c 8d 25 00 00 00 00 	lea    r12,[rip+0x0]        # 25f <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x25f>
 25f:	4c 89 e7             	mov    rdi,r12
 262:	e8 00 00 00 00       	call   267 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x267>
 267:	85 c0                	test   eax,eax
 269:	0f 84 cc fd ff ff    	je     3b <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x3b>
 26f:	66 0f 6f 05 00 00 00 	movdqa xmm0,XMMWORD PTR [rip+0x0]        # 277 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x277>
 276:	00 
 277:	4c 89 e7             	mov    rdi,r12
 27a:	0f 29 05 00 00 00 00 	movaps XMMWORD PTR [rip+0x0],xmm0        # 281 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x281>
 281:	e8 00 00 00 00       	call   286 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x286>
 286:	e9 b0 fd ff ff       	jmp    3b <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x3b>
 28b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
 290:	4c 8d 25 00 00 00 00 	lea    r12,[rip+0x0]        # 297 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x297>
 297:	4c 89 e7             	mov    rdi,r12
 29a:	e8 00 00 00 00       	call   29f <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x29f>
 29f:	85 c0                	test   eax,eax
 2a1:	0f 84 85 fd ff ff    	je     2c <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x2c>
 2a7:	66 0f 6f 05 00 00 00 	movdqa xmm0,XMMWORD PTR [rip+0x0]        # 2af <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x2af>
 2ae:	00 
 2af:	4c 89 e7             	mov    rdi,r12
 2b2:	0f 29 05 00 00 00 00 	movaps XMMWORD PTR [rip+0x0],xmm0        # 2b9 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x2b9>
 2b9:	e8 00 00 00 00       	call   2be <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x2be>
 2be:	e9 69 fd ff ff       	jmp    2c <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x2c>
 2c3:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
 2c8:	4c 8d 25 00 00 00 00 	lea    r12,[rip+0x0]        # 2cf <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x2cf>
 2cf:	4c 89 e7             	mov    rdi,r12
 2d2:	e8 00 00 00 00       	call   2d7 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x2d7>
 2d7:	85 c0                	test   eax,eax
 2d9:	0f 84 3e fd ff ff    	je     1d <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x1d>
 2df:	66 0f 6f 05 00 00 00 	movdqa xmm0,XMMWORD PTR [rip+0x0]        # 2e7 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x2e7>
 2e6:	00 
 2e7:	4c 89 e7             	mov    rdi,r12
 2ea:	0f 29 05 00 00 00 00 	movaps XMMWORD PTR [rip+0x0],xmm0        # 2f1 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x2f1>
 2f1:	e8 00 00 00 00       	call   2f6 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x2f6>
 2f6:	e9 22 fd ff ff       	jmp    1d <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x1d>
 2fb:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
 300:	48 c7 c0 fd ff ff ff 	mov    rax,0xfffffffffffffffd
 307:	be 03 00 00 00       	mov    esi,0x3
 30c:	e9 e3 fe ff ff       	jmp    1f4 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x1f4>
 311:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
 318:	48 c7 c0 fc ff ff ff 	mov    rax,0xfffffffffffffffc
 31f:	be 04 00 00 00       	mov    esi,0x4
 324:	5b                   	pop    rbx
 325:	48 01 ee             	add    rsi,rbp
 328:	48 01 c7             	add    rdi,rax
 32b:	5d                   	pop    rbp
 32c:	41 5c                	pop    r12
 32e:	e9 00 00 00 00       	jmp    333 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x333>
 333:	48 c7 c0 fe ff ff ff 	mov    rax,0xfffffffffffffffe
 33a:	be 02 00 00 00       	mov    esi,0x2
 33f:	e9 b0 fe ff ff       	jmp    1f4 <_ZN5cesu818is_valid_cesu8_SSEEPKhm+0x1f4>
