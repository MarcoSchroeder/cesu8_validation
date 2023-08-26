
build/CMakeFiles/cesu8_benchmark_avx512.dir/src/cesu8_AVX512.cpp.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm>:
   0:	f3 0f 1e fa          	repz nop edx
   4:	55                   	push   rbp
   5:	48 89 e5             	mov    rbp,rsp
   8:	41 55                	push   r13
   a:	41 54                	push   r12
   c:	49 89 f4             	mov    r12,rsi
   f:	53                   	push   rbx
  10:	0f b6 05 00 00 00 00 	movzx  eax,BYTE PTR [rip+0x0]        # 17 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x17>
  17:	48 89 fb             	mov    rbx,rdi
  1a:	48 83 e4 c0          	and    rsp,0xffffffffffffffc0
  1e:	84 c0                	test   al,al
  20:	0f 84 9a 03 00 00    	je     3c0 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x3c0>
  26:	0f b6 05 00 00 00 00 	movzx  eax,BYTE PTR [rip+0x0]        # 2d <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x2d>
  2d:	84 c0                	test   al,al
  2f:	0f 84 4b 03 00 00    	je     380 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x380>
  35:	0f b6 05 00 00 00 00 	movzx  eax,BYTE PTR [rip+0x0]        # 3c <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x3c>
  3c:	84 c0                	test   al,al
  3e:	0f 84 fc 02 00 00    	je     340 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x340>
  44:	0f b6 05 00 00 00 00 	movzx  eax,BYTE PTR [rip+0x0]        # 4b <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x4b>
  4b:	84 c0                	test   al,al
  4d:	0f 84 9d 02 00 00    	je     2f0 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x2f0>
  53:	49 83 fc 3f          	cmp    r12,0x3f
  57:	0f 86 d3 02 00 00    	jbe    330 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x330>
  5d:	49 8d 44 24 c0       	lea    rax,[r12-0x40]
  62:	c5 d1 ef ed          	vpxor  xmm5,xmm5,xmm5
  66:	62 71 fd 48 6f 25 00 	vmovdqa64 zmm12,ZMMWORD PTR [rip+0x0]        # 70 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x70>
  6d:	00 00 00 
  70:	62 71 fd 48 6f 1d 00 	vmovdqa64 zmm11,ZMMWORD PTR [rip+0x0]        # 7a <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x7a>
  77:	00 00 00 
  7a:	48 83 e0 c0          	and    rax,0xffffffffffffffc0
  7e:	62 71 fd 48 6f ed    	vmovdqa64 zmm13,zmm5
  84:	62 71 fd 48 6f 15 00 	vmovdqa64 zmm10,ZMMWORD PTR [rip+0x0]        # 8e <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x8e>
  8b:	00 00 00 
  8e:	62 71 fd 48 6f 0d 00 	vmovdqa64 zmm9,ZMMWORD PTR [rip+0x0]        # 98 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x98>
  95:	00 00 00 
  98:	62 f2 7d 48 58 25 00 	vpbroadcastd zmm4,DWORD PTR [rip+0x0]        # a2 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0xa2>
  9f:	00 00 00 
  a2:	48 8d 44 03 40       	lea    rax,[rbx+rax*1+0x40]
  a7:	62 72 7d 48 58 05 00 	vpbroadcastd zmm8,DWORD PTR [rip+0x0]        # b1 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0xb1>
  ae:	00 00 00 
  b1:	62 f1 fd 48 6f dd    	vmovdqa64 zmm3,zmm5
  b7:	62 f2 7d 48 58 3d 00 	vpbroadcastd zmm7,DWORD PTR [rip+0x0]        # c1 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0xc1>
  be:	00 00 00 
  c1:	c4 e1 fc 47 c0       	kxorq  k0,k0,k0
  c6:	62 f2 7d 48 78 35 00 	vpbroadcastb zmm6,BYTE PTR [rip+0x0]        # d0 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0xd0>
  cd:	00 00 00 
  d0:	62 f1 fd 48 6f cb    	vmovdqa64 zmm1,zmm3
  d6:	62 f1 fe 48 6f 1b    	vmovdqu64 zmm3,ZMMWORD PTR [rbx]
  dc:	48 83 c3 40          	add    rbx,0x40
  e0:	62 f3 65 48 03 c9 0f 	valignd zmm1,zmm3,zmm1,0xf
  e7:	62 f1 0d 48 72 f3 10 	vpslld zmm14,zmm3,0x10
  ee:	62 f1 7d 48 72 f3 08 	vpslld zmm0,zmm3,0x8
  f5:	62 f1 6d 48 72 d1 18 	vpsrld zmm2,zmm1,0x18
  fc:	62 f1 75 48 72 d1 10 	vpsrld zmm1,zmm1,0x10
 103:	62 d1 75 48 eb ce    	vpord  zmm1,zmm1,zmm14
 109:	62 f1 0d 48 71 d3 04 	vpsrlw zmm14,zmm3,0x4
 110:	62 f1 6d 48 eb d0    	vpord  zmm2,zmm2,zmm0
 116:	62 f1 7d 48 71 d1 04 	vpsrlw zmm0,zmm1,0x4
 11d:	62 f1 6d 48 71 d2 04 	vpsrlw zmm2,zmm2,0x4
 124:	62 f1 75 48 db cc    	vpandd zmm1,zmm1,zmm4
 12a:	62 f1 5d 48 db c0    	vpandd zmm0,zmm4,zmm0
 130:	62 f2 35 48 00 c9    	vpshufb zmm1,zmm9,zmm1
 136:	62 f1 5d 48 db d2    	vpandd zmm2,zmm4,zmm2
 13c:	62 f2 2d 48 00 c0    	vpshufb zmm0,zmm10,zmm0
 142:	62 f2 25 48 00 d2    	vpshufb zmm2,zmm11,zmm2
 148:	62 51 5d 48 db f6    	vpandd zmm14,zmm4,zmm14
 14e:	62 f1 7d 48 db c1    	vpandd zmm0,zmm0,zmm1
 154:	62 f1 fd 48 6f cd    	vmovdqa64 zmm1,zmm5
 15a:	62 52 1d 48 00 fe    	vpshufb zmm15,zmm12,zmm14
 160:	62 f1 7d 48 db c2    	vpandd zmm0,zmm0,zmm2
 166:	62 d3 4d 48 3f ce 00 	vpcmpb k1,zmm6,zmm14,0x0
 16d:	62 d1 7d 48 db d0    	vpandd zmm2,zmm0,zmm8
 173:	62 e1 7d 48 db c7    	vpandd zmm16,zmm0,zmm7
 179:	62 d1 7d 48 db c7    	vpandd zmm0,zmm0,zmm15
 17f:	62 f3 6d 48 03 c9 0f 	valignd zmm1,zmm2,zmm1,0xf
 186:	62 f1 fd 48 6f ea    	vmovdqa64 zmm5,zmm2
 18c:	62 f1 6d 48 72 f2 18 	vpslld zmm2,zmm2,0x18
 193:	62 b1 7d 40 71 f0 01 	vpsllw zmm16,zmm16,0x1
 19a:	c4 e1 fc 45 c1       	korq   k0,k0,k1
 19f:	62 f1 75 48 72 d1 08 	vpsrld zmm1,zmm1,0x8
 1a6:	62 f1 75 48 eb ca    	vpord  zmm1,zmm1,zmm2
 1ac:	62 b1 75 48 ef c8    	vpxord zmm1,zmm1,zmm16
 1b2:	62 d1 75 48 eb cd    	vpord  zmm1,zmm1,zmm13
 1b8:	62 71 75 48 eb e8    	vpord  zmm13,zmm1,zmm0
 1be:	48 39 c3             	cmp    rbx,rax
 1c1:	0f 85 09 ff ff ff    	jne    d0 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0xd0>
 1c7:	41 83 e4 3f          	and    r12d,0x3f
 1cb:	c4 e1 f8 98 c0       	kortestq k0,k0
 1d0:	40 0f 95 c6          	setne  sil
 1d4:	62 73 fd 48 3b e8 01 	vextracti64x4 ymm0,zmm13,0x1
 1db:	c4 c1 7d eb c5       	vpor   ymm0,ymm0,ymm13
 1e0:	c4 e3 7d 39 c1 01    	vextracti128 xmm1,ymm0,0x1
 1e6:	c5 f1 eb c8          	vpor   xmm1,xmm1,xmm0
 1ea:	c5 f9 70 c1 4e       	vpshufd xmm0,xmm1,0x4e
 1ef:	c5 f9 eb c1          	vpor   xmm0,xmm0,xmm1
 1f3:	c5 f9 7e c1          	vmovd  ecx,xmm0
 1f7:	c4 e3 79 16 c2 01    	vpextrd edx,xmm0,0x1
 1fd:	09 d1                	or     ecx,edx
 1ff:	0f 85 db 00 00 00    	jne    2e0 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x2e0>
 205:	40 84 f6             	test   sil,sil
 208:	0f 85 d2 00 00 00    	jne    2e0 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x2e0>
 20e:	80 78 fb ed          	cmp    BYTE PTR [rax-0x5],0xed
 212:	0f b6 70 fd          	movzx  esi,BYTE PTR [rax-0x3]
 216:	0f b6 48 fc          	movzx  ecx,BYTE PTR [rax-0x4]
 21a:	74 54                	je     270 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x270>
 21c:	0f b6 50 fe          	movzx  edx,BYTE PTR [rax-0x2]
 220:	80 f9 ed             	cmp    cl,0xed
 223:	74 6b                	je     290 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x290>
 225:	0f b6 48 ff          	movzx  ecx,BYTE PTR [rax-0x1]
 229:	83 e2 f0             	and    edx,0xfffffff0
 22c:	40 80 fe ed          	cmp    sil,0xed
 230:	0f 84 82 00 00 00    	je     2b8 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x2b8>
 236:	80 fa e0             	cmp    dl,0xe0
 239:	0f 84 c1 01 00 00    	je     400 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x400>
 23f:	83 e1 c0             	and    ecx,0xffffffc0
 242:	31 f6                	xor    esi,esi
 244:	80 f9 c0             	cmp    cl,0xc0
 247:	40 0f 94 c6          	sete   sil
 24b:	48 89 f7             	mov    rdi,rsi
 24e:	48 f7 df             	neg    rdi
 251:	4c 01 e6             	add    rsi,r12
 254:	48 01 c7             	add    rdi,rax
 257:	c5 f8 77             	vzeroupper 
 25a:	48 8d 65 e8          	lea    rsp,[rbp-0x18]
 25e:	5b                   	pop    rbx
 25f:	41 5c                	pop    r12
 261:	41 5d                	pop    r13
 263:	5d                   	pop    rbp
 264:	e9 00 00 00 00       	jmp    269 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x269>
 269:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
 270:	89 ca                	mov    edx,ecx
 272:	83 e2 f0             	and    edx,0xfffffff0
 275:	80 fa a0             	cmp    dl,0xa0
 278:	75 a2                	jne    21c <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x21c>
 27a:	89 f2                	mov    edx,esi
 27c:	83 e2 c0             	and    edx,0xffffffc0
 27f:	80 fa 80             	cmp    dl,0x80
 282:	0f 84 9a 01 00 00    	je     422 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x422>
 288:	0f b6 50 fe          	movzx  edx,BYTE PTR [rax-0x2]
 28c:	eb 97                	jmp    225 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x225>
 28e:	66 90                	xchg   ax,ax
 290:	89 f1                	mov    ecx,esi
 292:	83 e1 f0             	and    ecx,0xfffffff0
 295:	80 f9 a0             	cmp    cl,0xa0
 298:	75 8b                	jne    225 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x225>
 29a:	89 d1                	mov    ecx,edx
 29c:	83 e1 c0             	and    ecx,0xffffffc0
 29f:	80 f9 80             	cmp    cl,0x80
 2a2:	0f 84 69 01 00 00    	je     411 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x411>
 2a8:	0f b6 48 ff          	movzx  ecx,BYTE PTR [rax-0x1]
 2ac:	83 e2 f0             	and    edx,0xfffffff0
 2af:	eb 85                	jmp    236 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x236>
 2b1:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
 2b8:	80 fa a0             	cmp    dl,0xa0
 2bb:	0f 85 75 ff ff ff    	jne    236 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x236>
 2c1:	83 e1 c0             	and    ecx,0xffffffc0
 2c4:	80 f9 80             	cmp    cl,0x80
 2c7:	0f 85 75 ff ff ff    	jne    242 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x242>
 2cd:	48 c7 c7 fd ff ff ff 	mov    rdi,0xfffffffffffffffd
 2d4:	be 03 00 00 00       	mov    esi,0x3
 2d9:	e9 73 ff ff ff       	jmp    251 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x251>
 2de:	66 90                	xchg   ax,ax
 2e0:	31 c0                	xor    eax,eax
 2e2:	c5 f8 77             	vzeroupper 
 2e5:	48 8d 65 e8          	lea    rsp,[rbp-0x18]
 2e9:	5b                   	pop    rbx
 2ea:	41 5c                	pop    r12
 2ec:	41 5d                	pop    r13
 2ee:	5d                   	pop    rbp
 2ef:	c3                   	ret    
 2f0:	4c 8d 2d 00 00 00 00 	lea    r13,[rip+0x0]        # 2f7 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x2f7>
 2f7:	4c 89 ef             	mov    rdi,r13
 2fa:	e8 00 00 00 00       	call   2ff <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x2ff>
 2ff:	85 c0                	test   eax,eax
 301:	0f 84 4c fd ff ff    	je     53 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x53>
 307:	62 f1 fd 48 6f 05 00 	vmovdqa64 zmm0,ZMMWORD PTR [rip+0x0]        # 311 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x311>
 30e:	00 00 00 
 311:	4c 89 ef             	mov    rdi,r13
 314:	62 f1 fd 48 7f 05 00 	vmovdqa64 ZMMWORD PTR [rip+0x0],zmm0        # 31e <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x31e>
 31b:	00 00 00 
 31e:	c5 f8 77             	vzeroupper 
 321:	e8 00 00 00 00       	call   326 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x326>
 326:	49 83 fc 3f          	cmp    r12,0x3f
 32a:	0f 87 2d fd ff ff    	ja     5d <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x5d>
 330:	48 89 d8             	mov    rax,rbx
 333:	31 f6                	xor    esi,esi
 335:	c4 41 11 ef ed       	vpxor  xmm13,xmm13,xmm13
 33a:	e9 95 fe ff ff       	jmp    1d4 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x1d4>
 33f:	90                   	nop
 340:	4c 8d 2d 00 00 00 00 	lea    r13,[rip+0x0]        # 347 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x347>
 347:	4c 89 ef             	mov    rdi,r13
 34a:	e8 00 00 00 00       	call   34f <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x34f>
 34f:	85 c0                	test   eax,eax
 351:	0f 84 ed fc ff ff    	je     44 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x44>
 357:	62 f1 fd 48 6f 05 00 	vmovdqa64 zmm0,ZMMWORD PTR [rip+0x0]        # 361 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x361>
 35e:	00 00 00 
 361:	4c 89 ef             	mov    rdi,r13
 364:	62 f1 fd 48 7f 05 00 	vmovdqa64 ZMMWORD PTR [rip+0x0],zmm0        # 36e <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x36e>
 36b:	00 00 00 
 36e:	c5 f8 77             	vzeroupper 
 371:	e8 00 00 00 00       	call   376 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x376>
 376:	e9 c9 fc ff ff       	jmp    44 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x44>
 37b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
 380:	4c 8d 2d 00 00 00 00 	lea    r13,[rip+0x0]        # 387 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x387>
 387:	4c 89 ef             	mov    rdi,r13
 38a:	e8 00 00 00 00       	call   38f <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x38f>
 38f:	85 c0                	test   eax,eax
 391:	0f 84 9e fc ff ff    	je     35 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x35>
 397:	62 f1 fd 48 6f 05 00 	vmovdqa64 zmm0,ZMMWORD PTR [rip+0x0]        # 3a1 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x3a1>
 39e:	00 00 00 
 3a1:	4c 89 ef             	mov    rdi,r13
 3a4:	62 f1 fd 48 7f 05 00 	vmovdqa64 ZMMWORD PTR [rip+0x0],zmm0        # 3ae <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x3ae>
 3ab:	00 00 00 
 3ae:	c5 f8 77             	vzeroupper 
 3b1:	e8 00 00 00 00       	call   3b6 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x3b6>
 3b6:	e9 7a fc ff ff       	jmp    35 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x35>
 3bb:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
 3c0:	4c 8d 2d 00 00 00 00 	lea    r13,[rip+0x0]        # 3c7 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x3c7>
 3c7:	4c 89 ef             	mov    rdi,r13
 3ca:	e8 00 00 00 00       	call   3cf <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x3cf>
 3cf:	85 c0                	test   eax,eax
 3d1:	0f 84 4f fc ff ff    	je     26 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x26>
 3d7:	62 f1 fd 48 6f 05 00 	vmovdqa64 zmm0,ZMMWORD PTR [rip+0x0]        # 3e1 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x3e1>
 3de:	00 00 00 
 3e1:	4c 89 ef             	mov    rdi,r13
 3e4:	62 f1 fd 48 7f 05 00 	vmovdqa64 ZMMWORD PTR [rip+0x0],zmm0        # 3ee <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x3ee>
 3eb:	00 00 00 
 3ee:	c5 f8 77             	vzeroupper 
 3f1:	e8 00 00 00 00       	call   3f6 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x3f6>
 3f6:	e9 2b fc ff ff       	jmp    26 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x26>
 3fb:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
 400:	48 c7 c7 fe ff ff ff 	mov    rdi,0xfffffffffffffffe
 407:	be 02 00 00 00       	mov    esi,0x2
 40c:	e9 40 fe ff ff       	jmp    251 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x251>
 411:	48 c7 c7 fc ff ff ff 	mov    rdi,0xfffffffffffffffc
 418:	be 04 00 00 00       	mov    esi,0x4
 41d:	e9 2f fe ff ff       	jmp    251 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x251>
 422:	48 c7 c7 fb ff ff ff 	mov    rdi,0xfffffffffffffffb
 429:	be 05 00 00 00       	mov    esi,0x5
 42e:	e9 1e fe ff ff       	jmp    251 <_ZN5cesu821is_valid_cesu8_AVX512EPKhm+0x251>
