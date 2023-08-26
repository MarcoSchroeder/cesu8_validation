
build/CMakeFiles/cesu8_benchmark_avx2.dir/src/cesu8_AVX2.cpp.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm>:
   0:	f3 0f 1e fa          	repz nop edx
   4:	55                   	push   rbp
   5:	48 89 e5             	mov    rbp,rsp
   8:	41 55                	push   r13
   a:	41 54                	push   r12
   c:	49 89 f4             	mov    r12,rsi
   f:	53                   	push   rbx
  10:	0f b6 05 00 00 00 00 	movzx  eax,BYTE PTR [rip+0x0]        # 17 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x17>
  17:	48 89 fb             	mov    rbx,rdi
  1a:	48 83 e4 e0          	and    rsp,0xffffffffffffffe0
  1e:	84 c0                	test   al,al
  20:	0f 84 aa 02 00 00    	je     2d0 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x2d0>
  26:	0f b6 05 00 00 00 00 	movzx  eax,BYTE PTR [rip+0x0]        # 2d <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x2d>
  2d:	84 c0                	test   al,al
  2f:	0f 84 5b 02 00 00    	je     290 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x290>
  35:	0f b6 05 00 00 00 00 	movzx  eax,BYTE PTR [rip+0x0]        # 3c <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x3c>
  3c:	84 c0                	test   al,al
  3e:	0f 84 0c 02 00 00    	je     250 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x250>
  44:	0f b6 05 00 00 00 00 	movzx  eax,BYTE PTR [rip+0x0]        # 4b <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x4b>
  4b:	84 c0                	test   al,al
  4d:	0f 84 bd 01 00 00    	je     210 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x210>
  53:	49 83 fc 1f          	cmp    r12,0x1f
  57:	0f 86 8b 01 00 00    	jbe    1e8 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x1e8>
  5d:	49 8d 44 24 e0       	lea    rax,[r12-0x20]
  62:	c5 d9 ef e4          	vpxor  xmm4,xmm4,xmm4
  66:	c5 7d 6f 35 00 00 00 	vmovdqa ymm14,YMMWORD PTR [rip+0x0]        # 6e <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x6e>
  6d:	00 
  6e:	c5 7d 6f 2d 00 00 00 	vmovdqa ymm13,YMMWORD PTR [rip+0x0]        # 76 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x76>
  75:	00 
  76:	48 83 e0 e0          	and    rax,0xffffffffffffffe0
  7a:	c5 7d 6f 25 00 00 00 	vmovdqa ymm12,YMMWORD PTR [rip+0x0]        # 82 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x82>
  81:	00 
  82:	c5 7d 6f 1d 00 00 00 	vmovdqa ymm11,YMMWORD PTR [rip+0x0]        # 8a <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x8a>
  89:	00 
  8a:	c5 fd 6f f4          	vmovdqa ymm6,ymm4
  8e:	c5 fd 6f 2d 00 00 00 	vmovdqa ymm5,YMMWORD PTR [rip+0x0]        # 96 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x96>
  95:	00 
  96:	c5 7d 6f 15 00 00 00 	vmovdqa ymm10,YMMWORD PTR [rip+0x0]        # 9e <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x9e>
  9d:	00 
  9e:	48 8d 7c 03 20       	lea    rdi,[rbx+rax*1+0x20]
  a3:	c5 fd 6f dc          	vmovdqa ymm3,ymm4
  a7:	c5 7d 6f 0d 00 00 00 	vmovdqa ymm9,YMMWORD PTR [rip+0x0]        # af <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0xaf>
  ae:	00 
  af:	c5 7d 6f 05 00 00 00 	vmovdqa ymm8,YMMWORD PTR [rip+0x0]        # b7 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0xb7>
  b6:	00 
  b7:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
  be:	00 00 
  c0:	c5 fd 6f cb          	vmovdqa ymm1,ymm3
  c4:	c5 fe 6f 1b          	vmovdqu ymm3,YMMWORD PTR [rbx]
  c8:	48 83 c3 20          	add    rbx,0x20
  cc:	c4 e3 75 46 cb 21    	vperm2i128 ymm1,ymm1,ymm3,0x21
  d2:	c5 ed 71 d3 04       	vpsrlw ymm2,ymm3,0x4
  d7:	c4 63 65 0f f9 0f    	vpalignr ymm15,ymm3,ymm1,0xf
  dd:	c4 e3 65 0f c9 0e    	vpalignr ymm1,ymm3,ymm1,0xe
  e3:	c5 d5 db d2          	vpand  ymm2,ymm5,ymm2
  e7:	c5 fd 71 d1 04       	vpsrlw ymm0,ymm1,0x4
  ec:	c4 c1 05 71 d7 04    	vpsrlw ymm15,ymm15,0x4
  f2:	c5 d5 db c9          	vpand  ymm1,ymm5,ymm1
  f6:	c5 d5 db c0          	vpand  ymm0,ymm5,ymm0
  fa:	c4 e2 25 00 c9       	vpshufb ymm1,ymm11,ymm1
  ff:	c4 41 55 db ff       	vpand  ymm15,ymm5,ymm15
 104:	c4 e2 1d 00 c0       	vpshufb ymm0,ymm12,ymm0
 109:	c4 42 15 00 ff       	vpshufb ymm15,ymm13,ymm15
 10e:	c4 e2 0d 00 fa       	vpshufb ymm7,ymm14,ymm2
 113:	c5 fd db c1          	vpand  ymm0,ymm0,ymm1
 117:	c5 bd 74 d2          	vpcmpeqb ymm2,ymm8,ymm2
 11b:	c5 fd 6f cc          	vmovdqa ymm1,ymm4
 11f:	c4 c1 7d db c7       	vpand  ymm0,ymm0,ymm15
 124:	c4 c1 7d db e2       	vpand  ymm4,ymm0,ymm10
 129:	c4 41 7d db f9       	vpand  ymm15,ymm0,ymm9
 12e:	c5 fd db c7          	vpand  ymm0,ymm0,ymm7
 132:	c4 e3 75 46 cc 21    	vperm2i128 ymm1,ymm1,ymm4,0x21
 138:	c4 c1 05 71 f7 01    	vpsllw ymm15,ymm15,0x1
 13e:	c5 fd eb c2          	vpor   ymm0,ymm0,ymm2
 142:	c4 e3 5d 0f c9 0d    	vpalignr ymm1,ymm4,ymm1,0xd
 148:	c4 c1 75 ef cf       	vpxor  ymm1,ymm1,ymm15
 14d:	c5 f5 eb ce          	vpor   ymm1,ymm1,ymm6
 151:	c5 fd eb f1          	vpor   ymm6,ymm0,ymm1
 155:	48 39 fb             	cmp    rbx,rdi
 158:	0f 85 62 ff ff ff    	jne    c0 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0xc0>
 15e:	41 83 e4 1f          	and    r12d,0x1f
 162:	c4 e2 7d 17 f6       	vptest ymm6,ymm6
 167:	0f 85 89 00 00 00    	jne    1f6 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x1f6>
 16d:	c5 fd d7 c4          	vpmovmskb eax,ymm4
 171:	25 00 00 00 e0       	and    eax,0xe0000000
 176:	3d 00 00 00 20       	cmp    eax,0x20000000
 17b:	74 43                	je     1c0 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x1c0>
 17d:	3d 00 00 00 40       	cmp    eax,0x40000000
 182:	0f 84 a0 01 00 00    	je     328 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x328>
 188:	3d 00 00 00 80       	cmp    eax,0x80000000
 18d:	0f 84 7d 01 00 00    	je     310 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x310>
 193:	0f b6 47 fe          	movzx  eax,BYTE PTR [rdi-0x2]
 197:	83 e0 f0             	and    eax,0xfffffff0
 19a:	3c e0                	cmp    al,0xe0
 19c:	0f 84 97 01 00 00    	je     339 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x339>
 1a2:	0f b6 47 ff          	movzx  eax,BYTE PTR [rdi-0x1]
 1a6:	31 f6                	xor    esi,esi
 1a8:	83 e0 c0             	and    eax,0xffffffc0
 1ab:	3c c0                	cmp    al,0xc0
 1ad:	40 0f 94 c6          	sete   sil
 1b1:	48 89 f0             	mov    rax,rsi
 1b4:	48 f7 d8             	neg    rax
 1b7:	eb 13                	jmp    1cc <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x1cc>
 1b9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
 1c0:	48 c7 c0 fb ff ff ff 	mov    rax,0xfffffffffffffffb
 1c7:	be 05 00 00 00       	mov    esi,0x5
 1cc:	4c 01 e6             	add    rsi,r12
 1cf:	48 01 c7             	add    rdi,rax
 1d2:	c5 f8 77             	vzeroupper 
 1d5:	48 8d 65 e8          	lea    rsp,[rbp-0x18]
 1d9:	5b                   	pop    rbx
 1da:	41 5c                	pop    r12
 1dc:	41 5d                	pop    r13
 1de:	5d                   	pop    rbp
 1df:	e9 00 00 00 00       	jmp    1e4 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x1e4>
 1e4:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
 1e8:	c5 f9 ef c0          	vpxor  xmm0,xmm0,xmm0
 1ec:	48 89 df             	mov    rdi,rbx
 1ef:	c4 e2 7d 17 c0       	vptest ymm0,ymm0
 1f4:	74 9d                	je     193 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x193>
 1f6:	31 c0                	xor    eax,eax
 1f8:	c5 f8 77             	vzeroupper 
 1fb:	48 8d 65 e8          	lea    rsp,[rbp-0x18]
 1ff:	5b                   	pop    rbx
 200:	41 5c                	pop    r12
 202:	41 5d                	pop    r13
 204:	5d                   	pop    rbp
 205:	c3                   	ret    
 206:	66 2e 0f 1f 84 00 00 	nop    WORD PTR cs:[rax+rax*1+0x0]
 20d:	00 00 00 
 210:	4c 8d 2d 00 00 00 00 	lea    r13,[rip+0x0]        # 217 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x217>
 217:	4c 89 ef             	mov    rdi,r13
 21a:	e8 00 00 00 00       	call   21f <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x21f>
 21f:	85 c0                	test   eax,eax
 221:	0f 84 2c fe ff ff    	je     53 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x53>
 227:	c5 fd 6f 05 00 00 00 	vmovdqa ymm0,YMMWORD PTR [rip+0x0]        # 22f <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x22f>
 22e:	00 
 22f:	4c 89 ef             	mov    rdi,r13
 232:	c5 fd 7f 05 00 00 00 	vmovdqa YMMWORD PTR [rip+0x0],ymm0        # 23a <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x23a>
 239:	00 
 23a:	c5 f8 77             	vzeroupper 
 23d:	e8 00 00 00 00       	call   242 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x242>
 242:	e9 0c fe ff ff       	jmp    53 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x53>
 247:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
 24e:	00 00 
 250:	4c 8d 2d 00 00 00 00 	lea    r13,[rip+0x0]        # 257 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x257>
 257:	4c 89 ef             	mov    rdi,r13
 25a:	e8 00 00 00 00       	call   25f <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x25f>
 25f:	85 c0                	test   eax,eax
 261:	0f 84 dd fd ff ff    	je     44 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x44>
 267:	c5 fd 6f 05 00 00 00 	vmovdqa ymm0,YMMWORD PTR [rip+0x0]        # 26f <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x26f>
 26e:	00 
 26f:	4c 89 ef             	mov    rdi,r13
 272:	c5 fd 7f 05 00 00 00 	vmovdqa YMMWORD PTR [rip+0x0],ymm0        # 27a <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x27a>
 279:	00 
 27a:	c5 f8 77             	vzeroupper 
 27d:	e8 00 00 00 00       	call   282 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x282>
 282:	e9 bd fd ff ff       	jmp    44 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x44>
 287:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
 28e:	00 00 
 290:	4c 8d 2d 00 00 00 00 	lea    r13,[rip+0x0]        # 297 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x297>
 297:	4c 89 ef             	mov    rdi,r13
 29a:	e8 00 00 00 00       	call   29f <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x29f>
 29f:	85 c0                	test   eax,eax
 2a1:	0f 84 8e fd ff ff    	je     35 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x35>
 2a7:	c5 fd 6f 05 00 00 00 	vmovdqa ymm0,YMMWORD PTR [rip+0x0]        # 2af <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x2af>
 2ae:	00 
 2af:	4c 89 ef             	mov    rdi,r13
 2b2:	c5 fd 7f 05 00 00 00 	vmovdqa YMMWORD PTR [rip+0x0],ymm0        # 2ba <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x2ba>
 2b9:	00 
 2ba:	c5 f8 77             	vzeroupper 
 2bd:	e8 00 00 00 00       	call   2c2 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x2c2>
 2c2:	e9 6e fd ff ff       	jmp    35 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x35>
 2c7:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
 2ce:	00 00 
 2d0:	4c 8d 2d 00 00 00 00 	lea    r13,[rip+0x0]        # 2d7 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x2d7>
 2d7:	4c 89 ef             	mov    rdi,r13
 2da:	e8 00 00 00 00       	call   2df <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x2df>
 2df:	85 c0                	test   eax,eax
 2e1:	0f 84 3f fd ff ff    	je     26 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x26>
 2e7:	c5 fd 6f 05 00 00 00 	vmovdqa ymm0,YMMWORD PTR [rip+0x0]        # 2ef <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x2ef>
 2ee:	00 
 2ef:	4c 89 ef             	mov    rdi,r13
 2f2:	c5 fd 7f 05 00 00 00 	vmovdqa YMMWORD PTR [rip+0x0],ymm0        # 2fa <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x2fa>
 2f9:	00 
 2fa:	c5 f8 77             	vzeroupper 
 2fd:	e8 00 00 00 00       	call   302 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x302>
 302:	e9 1f fd ff ff       	jmp    26 <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x26>
 307:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
 30e:	00 00 
 310:	48 c7 c0 fd ff ff ff 	mov    rax,0xfffffffffffffffd
 317:	be 03 00 00 00       	mov    esi,0x3
 31c:	e9 ab fe ff ff       	jmp    1cc <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x1cc>
 321:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
 328:	48 c7 c0 fc ff ff ff 	mov    rax,0xfffffffffffffffc
 32f:	be 04 00 00 00       	mov    esi,0x4
 334:	e9 93 fe ff ff       	jmp    1cc <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x1cc>
 339:	48 c7 c0 fe ff ff ff 	mov    rax,0xfffffffffffffffe
 340:	be 02 00 00 00       	mov    esi,0x2
 345:	e9 82 fe ff ff       	jmp    1cc <_ZN5cesu819is_valid_cesu8_AVX2EPKhm+0x1cc>
