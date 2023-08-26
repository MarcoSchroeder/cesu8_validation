
build/CMakeFiles/cesu8_benchmark_scalar.dir/src/cesu8_scalar.cpp.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <_ZN5cesu821is_valid_cesu8_scalarEPKhm>:
   0:	f3 0f 1e fa          	repz nop edx
   4:	48 89 fa             	mov    rdx,rdi
   7:	48 89 f1             	mov    rcx,rsi
   a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

  # while (len>0)
  10:	48 85 c9             	test   rcx,rcx
  13:	74 15                	je     2a <_ZN5cesu821is_valid_cesu8_scalarEPKhm+0x2a>
  # while loop start
  # iff (is_c1(*str))
  15:	0f b6 32             	movzx  esi,BYTE PTR [rdx]
  18:	40 84 f6             	test   sil,sil
  1b:	78 13                	js     30 <_ZN5cesu821is_valid_cesu8_scalarEPKhm+0x30>

  # 1-unit ECP
  1d:	48 83 e9 01          	sub    rcx,0x1 # --len
  21:	48 83 c2 01          	add    rdx,0x1 # ++str

      # while (len>0)
  25:	48 85 c9             	test   rcx,rcx
  28:	75 eb                	jne    15 <_ZN5cesu821is_valid_cesu8_scalarEPKhm+0x15>

  # Return true
  2a:	b8 01 00 00 00       	mov    eax,0x1
  2f:	c3                   	ret

  # iif is(c2(*str))
  30:	89 f0                	mov    eax,esi
  32:	83 e0 e0             	and    eax,0xffffffe0
  35:	3c c0                	cmp    al,0xc0
  37:	74 5f                	je     98 <_ZN5cesu821is_valid_cesu8_scalarEPKhm+0x98>


   # iff is(c3(*str))
  39:	89 f0                	mov    eax,esi
  3b:	83 e0 f0             	and    eax,0xfffffff0
  3e:	3c e0                	cmp    al,0xe0
  40:	0f 95 c0             	setne  al

   # iff (len<3)
  43:	48 83 f9 02          	cmp    rcx,0x2
  47:	40 0f 96 c7          	setbe  dil
  4b:	40 08 f8             	or     al,dil
  4e:	0f 85 9c 00 00 00    	jne    f0 <_ZN5cesu821is_valid_cesu8_scalarEPKhm+0xf0>

      # iff(!is_ed(*str))
  54:	44 0f b6 42 01       	movzx  r8d,BYTE PTR [rdx+0x1]
  59:	40 80 fe ed          	cmp    sil,0xed
  5d:	74 61                	je     c0 <_ZN5cesu821is_valid_cesu8_scalarEPKhm+0xc0>

  # 3-unit ECP
      # iff(!is_cb(str[1]))
  5f:	44 89 c7             	mov    edi,r8d
  62:	83 e7 c0             	and    edi,0xffffffc0
  65:	40 80 ff 80          	cmp    dil,0x80
  69:	0f 85 c1 00 00 00    	jne    130 <_ZN5cesu821is_valid_cesu8_scalarEPKhm+0x130>

      # iff(!is_cb(str[2]))
  6f:	0f b6 7a 02          	movzx  edi,BYTE PTR [rdx+0x2]
  73:	83 e7 c0             	and    edi,0xffffffc0
  76:	40 80 ff 80          	cmp    dil,0x80
  7a:	75 69                	jne    e5 <_ZN5cesu821is_valid_cesu8_scalarEPKhm+0xe5>

      # iff(is_overlong_c3_cb_cb(*str, str[1]))
  7c:	40 80 fe e0          	cmp    sil,0xe0
  80:	75 06                	jne    88 <_ZN5cesu821is_valid_cesu8_scalarEPKhm+0x88>
  82:	41 80 f8 9f          	cmp    r8b,0x9f
  86:	76 5d                	jbe    e5 <_ZN5cesu821is_valid_cesu8_scalarEPKhm+0xe5>

  88:	48 83 c2 03          	add    rdx,0x3 # str += 3
  8c:	48 83 e9 03          	sub    rcx,0x3 # len -= 3
  90:	e9 7b ff ff ff       	jmp    10 <_ZN5cesu821is_valid_cesu8_scalarEPKhm+0x10>
  95:	0f 1f 00             	nop    DWORD PTR [rax]

  # 2-unit ECP
      # iff (len<2)
  98:	48 83 f9 01          	cmp    rcx,0x1
  9c:	74 52                	je     f0 <_ZN5cesu821is_valid_cesu8_scalarEPKhm+0xf0>
      # iff (!is_cb(str[1]))
  9e:	0f b6 42 01          	movzx  eax,BYTE PTR [rdx+0x1]
  a2:	83 e0 c0             	and    eax,0xffffffc0
  a5:	3c 80                	cmp    al,0x80
  a7:	75 47                	jne    f0 <_ZN5cesu821is_valid_cesu8_scalarEPKhm+0xf0>

      # iff (is_overlong_c2_cb(*str))
  a9:	40 80 fe c1          	cmp    sil,0xc1
  ad:	76 41                	jbe    f0 <_ZN5cesu821is_valid_cesu8_scalarEPKhm+0xf0>

  af:	48 83 c2 02          	add    rdx,0x2 # str += 2
  b3:	48 83 e9 02          	sub    rcx,0x2 # len -= 2
  b7:	e9 54 ff ff ff       	jmp    10 <_ZN5cesu821is_valid_cesu8_scalarEPKhm+0x10>
  bc:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

  # iff (is_ed_a(*str ,str[1])) and iff(!is_a_or_b(str[1]))
  c0:	44 89 c7             	mov    edi,r8d
  c3:	83 e7 e0             	and    edi,0xffffffe0
  c6:	40 80 ff a0          	cmp    dil,0xa0
  ca:	75 93                	jne    5f <_ZN5cesu821is_valid_cesu8_scalarEPKhm+0x5f>
  cc:	41 83 e0 f0          	and    r8d,0xfffffff0
  d0:	41 80 f8 a0          	cmp    r8b,0xa0
  d4:	40 0f 95 c6          	setne  sil
  d8:	48 83 f9 05          	cmp    rcx,0x5 # iff (len < 6)
  dc:	40 0f 96 c7          	setbe  dil
  e0:	40 08 fe             	or     sil,dil
  e3:	74 0e                	je     f3 <_ZN5cesu821is_valid_cesu8_scalarEPKhm+0xf3>

  # Return false
  e5:	c3                   	ret
  e6:	66 2e 0f 1f 84 00 00 	nop    WORD PTR cs:[rax+rax*1+0x0]
  ed:	00 00 00

  # Return false
  f0:	31 c0                	xor    eax,eax
  f2:	c3                   	ret

  # 6-unit ECP
      # iff(!is_cb(str[2]))
  f3:	0f b6 72 02          	movzx  esi,BYTE PTR [rdx+0x2]
  f7:	83 e6 c0             	and    esi,0xffffffc0
  fa:	40 80 fe 80          	cmp    sil,0x80
  fe:	75 e5                	jne    e5 <_ZN5cesu821is_valid_cesu8_scalarEPKhm+0xe5>

      # iff(!is_ed_b_cb(str[3], str[4], str[5]))
 100:	80 7a 03 ed          	cmp    BYTE PTR [rdx+0x3],0xed
 104:	75 df                	jne    e5 <_ZN5cesu821is_valid_cesu8_scalarEPKhm+0xe5>
 106:	0f b6 72 04          	movzx  esi,BYTE PTR [rdx+0x4]
 10a:	83 e6 f0             	and    esi,0xfffffff0
 10d:	40 80 fe b0          	cmp    sil,0xb0
 111:	75 d2                	jne    e5 <_ZN5cesu821is_valid_cesu8_scalarEPKhm+0xe5>
 113:	0f b6 42 05          	movzx  eax,BYTE PTR [rdx+0x5]
 117:	83 e0 c0             	and    eax,0xffffffc0
 11a:	3c 80                	cmp    al,0x80
 11c:	75 d2                	jne    f0 <_ZN5cesu821is_valid_cesu8_scalarEPKhm+0xf0>

 11e:	48 83 c2 06          	add    rdx,0x6 # str += 6
 122:	48 83 e9 06          	sub    rcx,0x6 # len -= 6
 126:	e9 e5 fe ff ff       	jmp    10 <_ZN5cesu821is_valid_cesu8_scalarEPKhm+0x10>
 12b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]

 # Return false
 130:	c3                   	ret
