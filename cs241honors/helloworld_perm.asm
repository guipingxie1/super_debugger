
helloworld:     file format elf64-x86-64


Disassembly of section .init:

0000000000400668 <_init>:
_init():
  400668:	48 83 ec 08          	sub    $0x8,%rsp
  40066c:	48 8b 05 85 09 20 00 	mov    0x200985(%rip),%rax        # 600ff8 <_DYNAMIC+0x1e0>
  400673:	48 85 c0             	test   %rax,%rax
  400676:	74 05                	je     40067d <_init+0x15>
  400678:	e8 33 00 00 00       	callq  4006b0 <__gmon_start__@plt>
  40067d:	48 83 c4 08          	add    $0x8,%rsp
  400681:	c3                   	retq   

Disassembly of section .plt:

0000000000400690 <_ZNSolsEi@plt-0x10>:
  400690:	ff 35 72 09 20 00    	pushq  0x200972(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400696:	ff 25 74 09 20 00    	jmpq   *0x200974(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40069c:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004006a0 <_ZNSolsEi@plt>:
  4006a0:	ff 25 72 09 20 00    	jmpq   *0x200972(%rip)        # 601018 <_GLOBAL_OFFSET_TABLE_+0x18>
  4006a6:	68 00 00 00 00       	pushq  $0x0
  4006ab:	e9 e0 ff ff ff       	jmpq   400690 <_init+0x28>

00000000004006b0 <__gmon_start__@plt>:
  4006b0:	ff 25 6a 09 20 00    	jmpq   *0x20096a(%rip)        # 601020 <_GLOBAL_OFFSET_TABLE_+0x20>
  4006b6:	68 01 00 00 00       	pushq  $0x1
  4006bb:	e9 d0 ff ff ff       	jmpq   400690 <_init+0x28>

00000000004006c0 <_ZNSt8ios_base4InitC1Ev@plt>:
  4006c0:	ff 25 62 09 20 00    	jmpq   *0x200962(%rip)        # 601028 <_GLOBAL_OFFSET_TABLE_+0x28>
  4006c6:	68 02 00 00 00       	pushq  $0x2
  4006cb:	e9 c0 ff ff ff       	jmpq   400690 <_init+0x28>

00000000004006d0 <__libc_start_main@plt>:
  4006d0:	ff 25 5a 09 20 00    	jmpq   *0x20095a(%rip)        # 601030 <_GLOBAL_OFFSET_TABLE_+0x30>
  4006d6:	68 03 00 00 00       	pushq  $0x3
  4006db:	e9 b0 ff ff ff       	jmpq   400690 <_init+0x28>

00000000004006e0 <__cxa_atexit@plt>:
  4006e0:	ff 25 52 09 20 00    	jmpq   *0x200952(%rip)        # 601038 <_GLOBAL_OFFSET_TABLE_+0x38>
  4006e6:	68 04 00 00 00       	pushq  $0x4
  4006eb:	e9 a0 ff ff ff       	jmpq   400690 <_init+0x28>

00000000004006f0 <_ZNSt8ios_base4InitD1Ev@plt>:
  4006f0:	ff 25 4a 09 20 00    	jmpq   *0x20094a(%rip)        # 601040 <_GLOBAL_OFFSET_TABLE_+0x40>
  4006f6:	68 05 00 00 00       	pushq  $0x5
  4006fb:	e9 90 ff ff ff       	jmpq   400690 <_init+0x28>

0000000000400700 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>:
  400700:	ff 25 42 09 20 00    	jmpq   *0x200942(%rip)        # 601048 <_GLOBAL_OFFSET_TABLE_+0x48>
  400706:	68 06 00 00 00       	pushq  $0x6
  40070b:	e9 80 ff ff ff       	jmpq   400690 <_init+0x28>

Disassembly of section .text:

0000000000400710 <_start>:
_start():
  400710:	31 ed                	xor    %ebp,%ebp
  400712:	49 89 d1             	mov    %rdx,%r9
  400715:	5e                   	pop    %rsi
  400716:	48 89 e2             	mov    %rsp,%rdx
  400719:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  40071d:	50                   	push   %rax
  40071e:	54                   	push   %rsp
  40071f:	49 c7 c0 90 09 40 00 	mov    $0x400990,%r8
  400726:	48 c7 c1 20 09 40 00 	mov    $0x400920,%rcx
  40072d:	48 c7 c7 fd 07 40 00 	mov    $0x4007fd,%rdi
  400734:	e8 97 ff ff ff       	callq  4006d0 <__libc_start_main@plt>
  400739:	f4                   	hlt    
  40073a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400740 <deregister_tm_clones>:
deregister_tm_clones():
  400740:	b8 67 10 60 00       	mov    $0x601067,%eax
  400745:	55                   	push   %rbp
  400746:	48 2d 60 10 60 00    	sub    $0x601060,%rax
  40074c:	48 83 f8 0e          	cmp    $0xe,%rax
  400750:	48 89 e5             	mov    %rsp,%rbp
  400753:	77 02                	ja     400757 <deregister_tm_clones+0x17>
  400755:	5d                   	pop    %rbp
  400756:	c3                   	retq   
  400757:	b8 00 00 00 00       	mov    $0x0,%eax
  40075c:	48 85 c0             	test   %rax,%rax
  40075f:	74 f4                	je     400755 <deregister_tm_clones+0x15>
  400761:	5d                   	pop    %rbp
  400762:	bf 60 10 60 00       	mov    $0x601060,%edi
  400767:	ff e0                	jmpq   *%rax
  400769:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400770 <register_tm_clones>:
register_tm_clones():
  400770:	b8 60 10 60 00       	mov    $0x601060,%eax
  400775:	55                   	push   %rbp
  400776:	48 2d 60 10 60 00    	sub    $0x601060,%rax
  40077c:	48 c1 f8 03          	sar    $0x3,%rax
  400780:	48 89 e5             	mov    %rsp,%rbp
  400783:	48 89 c2             	mov    %rax,%rdx
  400786:	48 c1 ea 3f          	shr    $0x3f,%rdx
  40078a:	48 01 d0             	add    %rdx,%rax
  40078d:	48 d1 f8             	sar    %rax
  400790:	75 02                	jne    400794 <register_tm_clones+0x24>
  400792:	5d                   	pop    %rbp
  400793:	c3                   	retq   
  400794:	ba 00 00 00 00       	mov    $0x0,%edx
  400799:	48 85 d2             	test   %rdx,%rdx
  40079c:	74 f4                	je     400792 <register_tm_clones+0x22>
  40079e:	5d                   	pop    %rbp
  40079f:	48 89 c6             	mov    %rax,%rsi
  4007a2:	bf 60 10 60 00       	mov    $0x601060,%edi
  4007a7:	ff e2                	jmpq   *%rdx
  4007a9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000004007b0 <__do_global_dtors_aux>:
__do_global_dtors_aux():
  4007b0:	80 3d b9 09 20 00 00 	cmpb   $0x0,0x2009b9(%rip)        # 601170 <completed.6973>
  4007b7:	75 11                	jne    4007ca <__do_global_dtors_aux+0x1a>
  4007b9:	55                   	push   %rbp
  4007ba:	48 89 e5             	mov    %rsp,%rbp
  4007bd:	e8 7e ff ff ff       	callq  400740 <deregister_tm_clones>
  4007c2:	5d                   	pop    %rbp
  4007c3:	c6 05 a6 09 20 00 01 	movb   $0x1,0x2009a6(%rip)        # 601170 <completed.6973>
  4007ca:	f3 c3                	repz retq 
  4007cc:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004007d0 <frame_dummy>:
frame_dummy():
  4007d0:	48 83 3d 38 06 20 00 	cmpq   $0x0,0x200638(%rip)        # 600e10 <__JCR_END__>
  4007d7:	00 
  4007d8:	74 1e                	je     4007f8 <frame_dummy+0x28>
  4007da:	b8 00 00 00 00       	mov    $0x0,%eax
  4007df:	48 85 c0             	test   %rax,%rax
  4007e2:	74 14                	je     4007f8 <frame_dummy+0x28>
  4007e4:	55                   	push   %rbp
  4007e5:	bf 10 0e 60 00       	mov    $0x600e10,%edi
  4007ea:	48 89 e5             	mov    %rsp,%rbp
  4007ed:	ff d0                	callq  *%rax
  4007ef:	5d                   	pop    %rbp
  4007f0:	e9 7b ff ff ff       	jmpq   400770 <register_tm_clones>
  4007f5:	0f 1f 00             	nopl   (%rax)
  4007f8:	e9 73 ff ff ff       	jmpq   400770 <register_tm_clones>

00000000004007fd <main>:
main():
/home/guiping/cs241/honorsProjekt/helloworld.cpp:7
  4007fd:	55                   	push   %rbp
  4007fe:	48 89 e5             	mov    %rsp,%rbp
  400801:	48 83 ec 50          	sub    $0x50,%rsp
/home/guiping/cs241/honorsProjekt/helloworld.cpp:38
  400805:	48 c7 45 c8 ae 09 40 	movq   $0x4009ae,-0x38(%rbp)
  40080c:	00 
/home/guiping/cs241/honorsProjekt/helloworld.cpp:40
  40080d:	48 b8 cd cc cc cc cc 	movabs $0x3ff0cccccccccccd,%rax
  400814:	cc f0 3f 
  400817:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
/home/guiping/cs241/honorsProjekt/helloworld.cpp:41
  40081b:	48 b8 cc 5d 4b c8 07 	movabs $0x40261d07c84b5dcc,%rax
  400822:	1d 26 40 
  400825:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
/home/guiping/cs241/honorsProjekt/helloworld.cpp:43
  400829:	c6 45 b9 61          	movb   $0x61,-0x47(%rbp)
/home/guiping/cs241/honorsProjekt/helloworld.cpp:45
  40082d:	c7 45 c4 ff ff ff ff 	movl   $0xffffffff,-0x3c(%rbp)
/home/guiping/cs241/honorsProjekt/helloworld.cpp:47
  400834:	48 c7 45 e0 ff ff ff 	movq   $0xffffffffffffffff,-0x20(%rbp)
  40083b:	ff 
/home/guiping/cs241/honorsProjekt/helloworld.cpp:49
  40083c:	48 c7 45 e8 ff ff ff 	movq   $0xffffffffffffffff,-0x18(%rbp)
  400843:	ff 
/home/guiping/cs241/honorsProjekt/helloworld.cpp:51
  400844:	48 c7 45 f0 ff ff ff 	movq   $0xffffffffffffffff,-0x10(%rbp)
  40084b:	ff 
/home/guiping/cs241/honorsProjekt/helloworld.cpp:53
  40084c:	48 b8 00 00 00 00 01 	movabs $0x100000000,%rax
  400853:	00 00 00 
  400856:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
/home/guiping/cs241/honorsProjekt/helloworld.cpp:55
  40085a:	66 c7 45 ba 00 40    	movw   $0x4000,-0x46(%rbp)
/home/guiping/cs241/honorsProjekt/helloworld.cpp:57
  400860:	c7 45 bc 00 00 00 00 	movl   $0x0,-0x44(%rbp)
/home/guiping/cs241/honorsProjekt/helloworld.cpp:58
  400867:	c7 45 c0 00 00 00 00 	movl   $0x0,-0x40(%rbp)
  40086e:	eb 0a                	jmp    40087a <main+0x7d>
/home/guiping/cs241/honorsProjekt/helloworld.cpp:59 (discriminator 2)
  400870:	8b 45 c0             	mov    -0x40(%rbp),%eax
  400873:	01 45 bc             	add    %eax,-0x44(%rbp)
/home/guiping/cs241/honorsProjekt/helloworld.cpp:58 (discriminator 2)
  400876:	83 45 c0 01          	addl   $0x1,-0x40(%rbp)
/home/guiping/cs241/honorsProjekt/helloworld.cpp:58 (discriminator 1)
  40087a:	83 7d c0 09          	cmpl   $0x9,-0x40(%rbp)
  40087e:	7e f0                	jle    400870 <main+0x73>
/home/guiping/cs241/honorsProjekt/helloworld.cpp:61
  400880:	be ba 09 40 00       	mov    $0x4009ba,%esi
  400885:	bf 60 10 60 00       	mov    $0x601060,%edi
  40088a:	e8 71 fe ff ff       	callq  400700 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
  40088f:	8b 55 bc             	mov    -0x44(%rbp),%edx
  400892:	89 d6                	mov    %edx,%esi
  400894:	48 89 c7             	mov    %rax,%rdi
  400897:	e8 04 fe ff ff       	callq  4006a0 <_ZNSolsEi@plt>
  40089c:	be c3 09 40 00       	mov    $0x4009c3,%esi
  4008a1:	48 89 c7             	mov    %rax,%rdi
  4008a4:	e8 57 fe ff ff       	callq  400700 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
/home/guiping/cs241/honorsProjekt/helloworld.cpp:63
  4008a9:	f2 0f 10 45 d0       	movsd  -0x30(%rbp),%xmm0
  4008ae:	f2 0f 59 45 d8       	mulsd  -0x28(%rbp),%xmm0
  4008b3:	f2 0f 11 45 d0       	movsd  %xmm0,-0x30(%rbp)
/home/guiping/cs241/honorsProjekt/helloworld.cpp:65
  4008b8:	b8 00 00 00 00       	mov    $0x0,%eax
/home/guiping/cs241/honorsProjekt/helloworld.cpp:66
  4008bd:	c9                   	leaveq 
  4008be:	c3                   	retq   

00000000004008bf <_Z41__static_initialization_and_destruction_0ii>:
__static_initialization_and_destruction_0():
  4008bf:	55                   	push   %rbp
  4008c0:	48 89 e5             	mov    %rsp,%rbp
  4008c3:	48 83 ec 10          	sub    $0x10,%rsp
  4008c7:	89 7d fc             	mov    %edi,-0x4(%rbp)
  4008ca:	89 75 f8             	mov    %esi,-0x8(%rbp)
  4008cd:	83 7d fc 01          	cmpl   $0x1,-0x4(%rbp)
  4008d1:	75 27                	jne    4008fa <_Z41__static_initialization_and_destruction_0ii+0x3b>
/home/guiping/cs241/honorsProjekt/helloworld.cpp:66 (discriminator 1)
  4008d3:	81 7d f8 ff ff 00 00 	cmpl   $0xffff,-0x8(%rbp)
  4008da:	75 1e                	jne    4008fa <_Z41__static_initialization_and_destruction_0ii+0x3b>
/usr/include/c++/4.8/iostream:74
  4008dc:	bf 71 11 60 00       	mov    $0x601171,%edi
  4008e1:	e8 da fd ff ff       	callq  4006c0 <_ZNSt8ios_base4InitC1Ev@plt>
  4008e6:	ba 58 10 60 00       	mov    $0x601058,%edx
  4008eb:	be 71 11 60 00       	mov    $0x601171,%esi
  4008f0:	bf f0 06 40 00       	mov    $0x4006f0,%edi
  4008f5:	e8 e6 fd ff ff       	callq  4006e0 <__cxa_atexit@plt>
/home/guiping/cs241/honorsProjekt/helloworld.cpp:66
  4008fa:	c9                   	leaveq 
  4008fb:	c3                   	retq   

00000000004008fc <_GLOBAL__sub_I_main>:
_GLOBAL__sub_I_main():
  4008fc:	55                   	push   %rbp
  4008fd:	48 89 e5             	mov    %rsp,%rbp
  400900:	be ff ff 00 00       	mov    $0xffff,%esi
  400905:	bf 01 00 00 00       	mov    $0x1,%edi
  40090a:	e8 b0 ff ff ff       	callq  4008bf <_Z41__static_initialization_and_destruction_0ii>
  40090f:	5d                   	pop    %rbp
  400910:	c3                   	retq   
  400911:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  400918:	00 00 00 
  40091b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000400920 <__libc_csu_init>:
__libc_csu_init():
  400920:	41 57                	push   %r15
  400922:	41 89 ff             	mov    %edi,%r15d
  400925:	41 56                	push   %r14
  400927:	49 89 f6             	mov    %rsi,%r14
  40092a:	41 55                	push   %r13
  40092c:	49 89 d5             	mov    %rdx,%r13
  40092f:	41 54                	push   %r12
  400931:	4c 8d 25 c0 04 20 00 	lea    0x2004c0(%rip),%r12        # 600df8 <__frame_dummy_init_array_entry>
  400938:	55                   	push   %rbp
  400939:	48 8d 2d c8 04 20 00 	lea    0x2004c8(%rip),%rbp        # 600e08 <__init_array_end>
  400940:	53                   	push   %rbx
  400941:	4c 29 e5             	sub    %r12,%rbp
  400944:	31 db                	xor    %ebx,%ebx
  400946:	48 c1 fd 03          	sar    $0x3,%rbp
  40094a:	48 83 ec 08          	sub    $0x8,%rsp
  40094e:	e8 15 fd ff ff       	callq  400668 <_init>
  400953:	48 85 ed             	test   %rbp,%rbp
  400956:	74 1e                	je     400976 <__libc_csu_init+0x56>
  400958:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  40095f:	00 
  400960:	4c 89 ea             	mov    %r13,%rdx
  400963:	4c 89 f6             	mov    %r14,%rsi
  400966:	44 89 ff             	mov    %r15d,%edi
  400969:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40096d:	48 83 c3 01          	add    $0x1,%rbx
  400971:	48 39 eb             	cmp    %rbp,%rbx
  400974:	75 ea                	jne    400960 <__libc_csu_init+0x40>
  400976:	48 83 c4 08          	add    $0x8,%rsp
  40097a:	5b                   	pop    %rbx
  40097b:	5d                   	pop    %rbp
  40097c:	41 5c                	pop    %r12
  40097e:	41 5d                	pop    %r13
  400980:	41 5e                	pop    %r14
  400982:	41 5f                	pop    %r15
  400984:	c3                   	retq   
  400985:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  40098c:	00 00 00 00 

0000000000400990 <__libc_csu_fini>:
__libc_csu_fini():
  400990:	f3 c3                	repz retq 

Disassembly of section .fini:

0000000000400994 <_fini>:
_fini():
  400994:	48 83 ec 08          	sub    $0x8,%rsp
  400998:	48 83 c4 08          	add    $0x8,%rsp
  40099c:	c3                   	retq   