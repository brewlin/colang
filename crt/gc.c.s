	.file	"gc.c"
	.text
.Ltext0:
	.comm	Hugmem,8,8
	.comm	sp_start,8,8
	.globl  usedpools
	.data
    .align 32
    .type   usedpools, @object
    .size   usedpools, 512
usedpools:
    .zero   512
	#.comm	usedpools,512,32
	.globl	arenas
	#.bss
	.align 8
	.type	arenas, @object
	.size	arenas, 8
arenas:
	.zero	8
	.globl	maxarenas
	.align 4
	.type	maxarenas, @object
	.size	maxarenas, 4
maxarenas:
	.zero	4
	.globl	unused_arena_objects
	.align 8
	.type	unused_arena_objects, @object
	.size	unused_arena_objects, 8
unused_arena_objects:
	.zero	8
	.globl	usable_arenas
	.align 8
	.type	usable_arenas, @object
	.size	usable_arenas, 8
usable_arenas:
	.zero	8
	.globl	narenas_currently_allocated
	.align 8
	.type	narenas_currently_allocated, @object
	.size	narenas_currently_allocated, 8
narenas_currently_allocated:
	.zero	8
	#.section	.rodata
	.align 8
.LC0:
	.string	"/home/xiaodo/c++/colang/src/gc/gc.c"
.LC1:
	.string	"usable_arenas == NULL"
.LC2:
	.string	"unused_arena_objects == NULL"
.LC3:
	.string	"unused_arena_objects != NULL"
.LC4:
	.string	"arenaobj->address == 0"
	.align 8
.LC5:
	.string	"POOL_SIZE * arenaobj->nfreepools == ARENA_SIZE"
	.text
	.globl	new_arena
	.type	new_arena, @function
new_arena:
.LFB5:
	.file 1 "/home/xiaodo/c++/colang/src/gc/gc.c"
	.loc 1 48 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	.loc 1 53 0
	movq	unused_arena_objects(%rip), %rax
	testq	%rax, %rax
	jne	.L2
.LBB2:
	.loc 1 60 0
	movl	maxarenas(%rip), %eax
	testl	%eax, %eax
	je	.L3
	.loc 1 60 0 is_stmt 0 discriminator 1
	movl	maxarenas(%rip), %eax
	addl	%eax, %eax
	jmp	.L4
.L3:
	.loc 1 60 0 discriminator 2
	movl	$16, %eax
.L4:
	.loc 1 60 0 discriminator 4
	movl	%eax, -8(%rbp)
	.loc 1 62 0 is_stmt 1 discriminator 4
	movl	maxarenas(%rip), %eax
	cmpl	%eax, -8(%rbp)
	ja	.L5
	.loc 1 63 0
	movl	$0, %eax
	jmp	.L6
.L5:
	.loc 1 64 0
	movl	-8(%rbp), %edx
	movq	%rdx, %rax
	salq	$3, %rax
	subq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, -16(%rbp)
	.loc 1 66 0
	movq	arenas(%rip), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	realloc@PLT
	movq	%rax, -24(%rbp)
	.loc 1 67 0
	cmpq	$0, -24(%rbp)
	jne	.L7
	.loc 1 68 0
	movl	$0, %eax
	jmp	.L6
.L7:
	.loc 1 70 0
	movq	-24(%rbp), %rax
	movq	%rax, arenas(%rip)
	.loc 1 73 0
	movq	usable_arenas(%rip), %rax
	testq	%rax, %rax
	je	.L8
	.loc 1 73 0 is_stmt 0 discriminator 1
	leaq	__PRETTY_FUNCTION__.3287(%rip), %rcx
	movl	$73, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	call	__assert_fail@PLT
.L8:
	.loc 1 74 0 is_stmt 1
	movq	unused_arena_objects(%rip), %rax
	testq	%rax, %rax
	je	.L9
	.loc 1 74 0 is_stmt 0 discriminator 1
	leaq	__PRETTY_FUNCTION__.3287(%rip), %rcx
	movl	$74, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC2(%rip), %rdi
	call	__assert_fail@PLT
.L9:
	.loc 1 77 0 is_stmt 1
	movl	maxarenas(%rip), %eax
	movl	%eax, -4(%rbp)
	jmp	.L10
.L13:
	.loc 1 78 0
	movq	arenas(%rip), %rcx
	movl	-4(%rbp), %edx
	movq	%rdx, %rax
	salq	$3, %rax
	subq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	$0, (%rax)
	.loc 1 79 0
	movl	-8(%rbp), %eax
	subl	$1, %eax
	.loc 1 80 0
	cmpl	%eax, -4(%rbp)
	jnb	.L11
	.loc 1 80 0 is_stmt 0 discriminator 1
	movq	arenas(%rip), %rdx
	movl	-4(%rbp), %eax
	addl	$1, %eax
	movl	%eax, %ecx
	movq	%rcx, %rax
	salq	$3, %rax
	subq	%rcx, %rax
	salq	$3, %rax
	leaq	(%rdx,%rax), %rcx
	jmp	.L12
.L11:
	.loc 1 80 0 discriminator 2
	movl	$0, %ecx
.L12:
	.loc 1 79 0 is_stmt 1 discriminator 2
	movq	arenas(%rip), %rsi
	movl	-4(%rbp), %edx
	movq	%rdx, %rax
	salq	$3, %rax
	subq	%rdx, %rax
	salq	$3, %rax
	addq	%rsi, %rax
	movq	%rcx, 40(%rax)
	.loc 1 77 0 discriminator 2
	addl	$1, -4(%rbp)
.L10:
	.loc 1 77 0 is_stmt 0 discriminator 1
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jb	.L13
	.loc 1 83 0 is_stmt 1
	movq	arenas(%rip), %rdx
	movl	maxarenas(%rip), %eax
	movl	%eax, %ecx
	movq	%rcx, %rax
	salq	$3, %rax
	subq	%rcx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	movq	%rax, unused_arena_objects(%rip)
	.loc 1 85 0
	movl	-8(%rbp), %eax
	movl	%eax, maxarenas(%rip)
.L2:
.LBE2:
	.loc 1 88 0
	movq	unused_arena_objects(%rip), %rax
	testq	%rax, %rax
	jne	.L14
	.loc 1 88 0 is_stmt 0 discriminator 1
	leaq	__PRETTY_FUNCTION__.3287(%rip), %rcx
	movl	$88, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC3(%rip), %rdi
	call	__assert_fail@PLT
.L14:
	.loc 1 89 0 is_stmt 1
	movq	unused_arena_objects(%rip), %rax
	movq	%rax, -24(%rbp)
	.loc 1 90 0
	movq	-24(%rbp), %rax
	movq	40(%rax), %rax
	movq	%rax, unused_arena_objects(%rip)
	.loc 1 92 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L15
	.loc 1 92 0 is_stmt 0 discriminator 1
	leaq	__PRETTY_FUNCTION__.3287(%rip), %rcx
	movl	$92, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC4(%rip), %rdi
	call	__assert_fail@PLT
.L15:
	.loc 1 94 0 is_stmt 1
	movl	$262144, %edi
	call	malloc@PLT
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	.loc 1 95 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L16
	.loc 1 97 0
	movq	unused_arena_objects(%rip), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, 40(%rax)
	.loc 1 98 0
	movq	-24(%rbp), %rax
	movq	%rax, unused_arena_objects(%rip)
	.loc 1 99 0
	movl	$0, %eax
	jmp	.L6
.L16:
	.loc 1 102 0
	movq	narenas_currently_allocated(%rip), %rax
	addq	$1, %rax
	movq	%rax, narenas_currently_allocated(%rip)
	.loc 1 104 0
	movq	-24(%rbp), %rax
	movq	$0, 32(%rax)
	.loc 1 105 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, 16(%rax)
	.loc 1 106 0
	movq	-24(%rbp), %rax
	movl	$64, 24(%rax)
	.loc 1 107 0
	movq	-24(%rbp), %rax
	movl	24(%rax), %eax
	sall	$12, %eax
	cmpl	$262144, %eax
	je	.L17
	.loc 1 107 0 is_stmt 0 discriminator 1
	leaq	__PRETTY_FUNCTION__.3287(%rip), %rcx
	movl	$107, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC5(%rip), %rdi
	call	__assert_fail@PLT
.L17:
	.loc 1 109 0 is_stmt 1
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	andl	$4095, %eax
	movl	%eax, -28(%rbp)
	.loc 1 110 0
	cmpl	$0, -28(%rbp)
	je	.L18
	.loc 1 111 0
	movq	-24(%rbp), %rax
	movl	24(%rax), %eax
	leal	-1(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, 24(%rax)
	.loc 1 112 0
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	movl	$4096, %edx
	subl	-28(%rbp), %edx
	movl	%edx, %edx
	addq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, 16(%rax)
.L18:
	.loc 1 115 0
	movq	-24(%rbp), %rax
	movq	16(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 1 117 0
	movq	-24(%rbp), %rax
	movl	24(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, 28(%rax)
	.loc 1 119 0
	movq	-24(%rbp), %rax
.L6:
	.loc 1 120 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	new_arena, .-new_arena
	#.section	.rodata
.LC6:
	.string	"bp != NULL"
.LC7:
	.string	"usable_arenas->address != 0"
	.align 8
.LC8:
	.string	"usable_arenas->freepools == NULL"
	.align 8
.LC9:
	.string	"usable_arenas->nextarena == NULL || usable_arenas->nextarena->prevarena == usable_arenas"
	.align 8
.LC10:
	.string	"usable_arenas->freepools != NULL || usable_arenas->pool_address <= (uchar*)usable_arenas->address + ARENA_SIZE - POOL_SIZE"
.LC11:
	.string	"usable_arenas->nfreepools > 0"
	.align 8
.LC12:
	.string	"(uchar*)pool <= (uchar*)usable_arenas->address + ARENA_SIZE - POOL_SIZE"
	.align 8
.LC13:
	.string	"&arenas[pool->arenaindex] == usable_arenas"
	.text
	.globl	Malloc
	.type	Malloc, @function
Malloc:
.LFB6:
	.loc 1 123 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	.loc 1 130 0
	cmpq	$2147483647, -56(%rbp)
	jbe	.L20
	.loc 1 131 0
	movl	$0, %eax
	jmp	.L21
.L20:
	.loc 1 134 0
	movq	-56(%rbp), %rax
	subq	$1, %rax
	cmpq	$255, %rax
	ja	.L44
	.loc 1 136 0
	movq	-56(%rbp), %rax
	subl	$1, %eax
	shrl	$3, %eax
	movl	%eax, -12(%rbp)
	.loc 1 137 0
	movl	-12(%rbp), %eax
	addl	%eax, %eax
	movl	%eax, %eax
	leaq	0(,%rax,8), %rdx
	leaq	usedpools(%rip), %rax
	movq	(%rdx,%rax), %rax
	movq	%rax, -8(%rbp)
	.loc 1 138 0
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	cmpq	%rax, -8(%rbp)
	je	.L45
	.loc 1 140 0
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, (%rax)
	.loc 1 142 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -24(%rbp)
	.loc 1 143 0
	cmpq	$0, -24(%rbp)
	jne	.L24
	.loc 1 144 0
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -32(%rbp)
	.loc 1 145 0
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -8(%rbp)
	.loc 1 146 0
	movq	-32(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 24(%rax)
	.loc 1 147 0
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, 16(%rax)
	.loc 1 148 0
	jmp	.L23
.L24:
	.loc 1 150 0
	cmpq	$0, -24(%rbp)
	jne	.L25
	.loc 1 150 0 is_stmt 0 discriminator 1
	leaq	__PRETTY_FUNCTION__.3299(%rip), %rcx
	movl	$150, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC6(%rip), %rdi
	call	__assert_fail@PLT
.L25:
	.loc 1 153 0 is_stmt 1
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	je	.L26
	.loc 1 155 0
	movq	-24(%rbp), %rax
	jmp	.L21
.L26:
	.loc 1 158 0
	movq	-8(%rbp), %rax
	movl	40(%rax), %edx
	movq	-8(%rbp), %rax
	movl	44(%rax), %eax
	cmpl	%eax, %edx
	ja	.L27
	.loc 1 160 0
	movq	-8(%rbp), %rax
	movl	40(%rax), %eax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	addq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 1 162 0
	movq	-8(%rbp), %rax
	movl	40(%rax), %eax
	movl	-12(%rbp), %edx
	addl	$1, %edx
	sall	$3, %edx
	addl	%eax, %edx
	movq	-8(%rbp), %rax
	movl	%edx, 40(%rax)
	.loc 1 164 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	$0, 8(%rax)
	.loc 1 166 0
	movq	-24(%rbp), %rax
	jmp	.L21
.L27:
	.loc 1 178 0
	movl	$0, %eax
	call	gc@PLT
	.loc 1 179 0
	movq	-24(%rbp), %rax
	jmp	.L21
.L45:
	.loc 1 181 0
	nop
.L23:
	.loc 1 183 0
	movq	usable_arenas(%rip), %rax
	testq	%rax, %rax
	jne	.L28
	.loc 1 185 0
	call	new_arena
	movq	%rax, usable_arenas(%rip)
	.loc 1 186 0
	movq	usable_arenas(%rip), %rax
	testq	%rax, %rax
	je	.L46
	.loc 1 193 0
	movq	usable_arenas(%rip), %rax
	movq	$0, 48(%rax)
	.loc 1 192 0
	movq	usable_arenas(%rip), %rdx
	.loc 1 193 0
	movq	48(%rax), %rax
	.loc 1 192 0
	movq	%rax, 40(%rdx)
.L28:
	.loc 1 196 0
	movq	usable_arenas(%rip), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L30
	.loc 1 196 0 is_stmt 0 discriminator 1
	leaq	__PRETTY_FUNCTION__.3299(%rip), %rcx
	movl	$196, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC7(%rip), %rdi
	call	__assert_fail@PLT
.L30:
	.loc 1 199 0 is_stmt 1
	movq	usable_arenas(%rip), %rax
	movq	32(%rax), %rax
	movq	%rax, -8(%rbp)
	.loc 1 200 0
	cmpq	$0, -8(%rbp)
	je	.L31
	.loc 1 202 0
	movq	usable_arenas(%rip), %rax
	movq	-8(%rbp), %rdx
	movq	16(%rdx), %rdx
	movq	%rdx, 32(%rax)
	.loc 1 205 0
	movq	usable_arenas(%rip), %rax
	movl	24(%rax), %edx
	subl	$1, %edx
	movl	%edx, 24(%rax)
	.loc 1 206 0
	movq	usable_arenas(%rip), %rax
	movl	24(%rax), %eax
	testl	%eax, %eax
	jne	.L32
	.loc 1 208 0
	movq	usable_arenas(%rip), %rax
	movq	32(%rax), %rax
	testq	%rax, %rax
	je	.L33
	.loc 1 208 0 is_stmt 0 discriminator 1
	leaq	__PRETTY_FUNCTION__.3299(%rip), %rcx
	movl	$208, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC8(%rip), %rdi
	call	__assert_fail@PLT
.L33:
	.loc 1 209 0 is_stmt 1
	movq	usable_arenas(%rip), %rax
	movq	40(%rax), %rax
	testq	%rax, %rax
	je	.L34
	.loc 1 209 0 is_stmt 0 discriminator 1
	movq	usable_arenas(%rip), %rax
	movq	40(%rax), %rax
	movq	48(%rax), %rdx
	movq	usable_arenas(%rip), %rax
	cmpq	%rax, %rdx
	je	.L34
	.loc 1 209 0 discriminator 2
	leaq	__PRETTY_FUNCTION__.3299(%rip), %rcx
	movl	$211, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC9(%rip), %rdi
	call	__assert_fail@PLT
.L34:
	.loc 1 213 0 is_stmt 1
	movq	usable_arenas(%rip), %rax
	movq	40(%rax), %rax
	movq	%rax, usable_arenas(%rip)
	.loc 1 214 0
	movq	usable_arenas(%rip), %rax
	testq	%rax, %rax
	je	.L35
	.loc 1 215 0
	movq	usable_arenas(%rip), %rax
	movq	$0, 48(%rax)
	.loc 1 216 0
	movq	usable_arenas(%rip), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L35
	.loc 1 216 0 is_stmt 0 discriminator 1
	leaq	__PRETTY_FUNCTION__.3299(%rip), %rcx
	movl	$216, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC7(%rip), %rdi
	call	__assert_fail@PLT
.L32:
	.loc 1 221 0 is_stmt 1
	movq	usable_arenas(%rip), %rax
	movq	32(%rax), %rax
	testq	%rax, %rax
	jne	.L47
	.loc 1 221 0 is_stmt 0 discriminator 1
	movq	usable_arenas(%rip), %rax
	movq	16(%rax), %rdx
	movq	usable_arenas(%rip), %rax
	movq	(%rax), %rax
	addq	$258048, %rax
	cmpq	%rax, %rdx
	jbe	.L35
	.loc 1 221 0 discriminator 2
	leaq	__PRETTY_FUNCTION__.3299(%rip), %rcx
	movl	$224, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC10(%rip), %rdi
	call	__assert_fail@PLT
.L47:
	.loc 1 226 0 is_stmt 1
	nop
	jmp	.L35
.L48:
	.loc 1 285 0
	nop
.L35:
	.loc 1 228 0
	movl	-12(%rbp), %eax
	addl	%eax, %eax
	movl	%eax, %eax
	leaq	0(,%rax,8), %rdx
	leaq	usedpools(%rip), %rax
	movq	(%rdx,%rax), %rax
	movq	%rax, -32(%rbp)
	.loc 1 229 0
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, 16(%rax)
	.loc 1 230 0
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, 24(%rax)
	.loc 1 231 0
	movq	-32(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 16(%rax)
	.loc 1 232 0
	movq	-32(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 24(%rax)
	.loc 1 233 0
	movq	-8(%rbp), %rax
	movl	$1, (%rax)
	.loc 1 234 0
	movq	-8(%rbp), %rax
	movl	36(%rax), %eax
	cmpl	%eax, -12(%rbp)
	jne	.L36
	.loc 1 236 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -24(%rbp)
	.loc 1 237 0
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 1 239 0
	movq	-24(%rbp), %rax
	jmp	.L21
.L36:
	.loc 1 246 0
	movq	-8(%rbp), %rax
	movl	-12(%rbp), %edx
	movl	%edx, 36(%rax)
	.loc 1 247 0
	movl	-12(%rbp), %eax
	addl	$1, %eax
	sall	$3, %eax
	movl	%eax, -12(%rbp)
	.loc 1 249 0
	movq	-8(%rbp), %rax
	addq	$48, %rax
	movq	%rax, -24(%rbp)
	.loc 1 250 0
	movl	-12(%rbp), %eax
	addl	%eax, %eax
	leal	48(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 40(%rax)
	.loc 1 251 0
	movl	$4096, %eax
	subl	-12(%rbp), %eax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movl	%edx, 44(%rax)
	.loc 1 252 0
	movl	-12(%rbp), %edx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 1 253 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	$0, 8(%rax)
	.loc 1 255 0
	movq	-24(%rbp), %rax
	jmp	.L21
.L31:
	.loc 1 259 0
	movq	usable_arenas(%rip), %rax
	movl	24(%rax), %eax
	testl	%eax, %eax
	jne	.L37
	.loc 1 259 0 is_stmt 0 discriminator 1
	leaq	__PRETTY_FUNCTION__.3299(%rip), %rcx
	movl	$259, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC11(%rip), %rdi
	call	__assert_fail@PLT
.L37:
	.loc 1 260 0 is_stmt 1
	movq	usable_arenas(%rip), %rax
	movq	32(%rax), %rax
	testq	%rax, %rax
	je	.L38
	.loc 1 260 0 is_stmt 0 discriminator 1
	leaq	__PRETTY_FUNCTION__.3299(%rip), %rcx
	movl	$260, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC8(%rip), %rdi
	call	__assert_fail@PLT
.L38:
	.loc 1 262 0 is_stmt 1
	movq	usable_arenas(%rip), %rax
	movq	16(%rax), %rax
	movq	%rax, -8(%rbp)
	.loc 1 263 0
	movq	usable_arenas(%rip), %rax
	movq	(%rax), %rax
	addq	$258048, %rax
	cmpq	%rax, -8(%rbp)
	jbe	.L39
	.loc 1 263 0 is_stmt 0 discriminator 1
	leaq	__PRETTY_FUNCTION__.3299(%rip), %rcx
	movl	$264, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC12(%rip), %rdi
	call	__assert_fail@PLT
.L39:
	.loc 1 265 0 is_stmt 1
	movq	usable_arenas(%rip), %rax
	movq	%rax, %rdx
	movq	arenas(%rip), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	sarq	$3, %rax
	movq	%rax, %rdx
	movabsq	$7905747460161236407, %rax
	imulq	%rdx, %rax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movl	%edx, 32(%rax)
	.loc 1 266 0
	movq	arenas(%rip), %rdx
	movq	-8(%rbp), %rax
	movl	32(%rax), %eax
	movl	%eax, %ecx
	movq	%rcx, %rax
	salq	$3, %rax
	subq	%rcx, %rax
	salq	$3, %rax
	addq	%rax, %rdx
	movq	usable_arenas(%rip), %rax
	cmpq	%rax, %rdx
	je	.L40
	.loc 1 266 0 is_stmt 0 discriminator 1
	leaq	__PRETTY_FUNCTION__.3299(%rip), %rcx
	movl	$266, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC13(%rip), %rdi
	call	__assert_fail@PLT
.L40:
	.loc 1 267 0 is_stmt 1
	movq	-8(%rbp), %rax
	movl	$65535, 36(%rax)
	.loc 1 269 0
	movq	usable_arenas(%rip), %rax
	movq	16(%rax), %rdx
	movq	usable_arenas(%rip), %rax
	addq	$4096, %rdx
	movq	%rdx, 16(%rax)
	.loc 1 270 0
	movq	usable_arenas(%rip), %rax
	movl	24(%rax), %edx
	subl	$1, %edx
	movl	%edx, 24(%rax)
	.loc 1 272 0
	movq	usable_arenas(%rip), %rax
	movl	24(%rax), %eax
	testl	%eax, %eax
	jne	.L48
	.loc 1 273 0
	movq	usable_arenas(%rip), %rax
	movq	40(%rax), %rax
	testq	%rax, %rax
	je	.L42
	.loc 1 273 0 is_stmt 0 discriminator 1
	movq	usable_arenas(%rip), %rax
	movq	40(%rax), %rax
	movq	48(%rax), %rdx
	movq	usable_arenas(%rip), %rax
	cmpq	%rax, %rdx
	je	.L42
	.loc 1 273 0 discriminator 2
	leaq	__PRETTY_FUNCTION__.3299(%rip), %rcx
	movl	$275, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC9(%rip), %rdi
	call	__assert_fail@PLT
.L42:
	.loc 1 278 0 is_stmt 1
	movq	usable_arenas(%rip), %rax
	movq	40(%rax), %rax
	movq	%rax, usable_arenas(%rip)
	.loc 1 279 0
	movq	usable_arenas(%rip), %rax
	testq	%rax, %rax
	je	.L48
	.loc 1 280 0
	movq	usable_arenas(%rip), %rax
	movq	$0, 48(%rax)
	.loc 1 281 0
	movq	usable_arenas(%rip), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L48
	.loc 1 281 0 is_stmt 0 discriminator 1
	leaq	__PRETTY_FUNCTION__.3299(%rip), %rcx
	movl	$281, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC7(%rip), %rdi
	call	__assert_fail@PLT
.L44:
	.loc 1 289 0 is_stmt 1
	nop
	jmp	.L22
.L46:
	.loc 1 189 0
	nop
.L22:
	.loc 1 291 0
	cmpq	$0, -56(%rbp)
	jne	.L43
	.loc 1 292 0
	movq	$1, -56(%rbp)
.L43:
	.loc 1 293 0
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -40(%rbp)
	.loc 1 294 0
	movq	-56(%rbp), %rax
	movl	%eax, %edx
	movq	-40(%rbp), %rax
	leaq	8(%rax), %rcx
	movq	Hugmem(%rip), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	push@PLT
	.loc 1 295 0
	movq	-40(%rbp), %rax
.L21:
	.loc 1 296 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	Malloc, .-Malloc
	#.section	.rodata
.LC14:
	.string	"pool->ref.count > 0"
	.align 8
.LC15:
	.string	"ao->prevarena->nextarena == ao"
.LC16:
	.string	"usable_arenas == ao"
	.align 8
.LC17:
	.string	"ao->nextarena == NULL || ao->prevarena == ao->nextarena->prevarena"
	.align 8
.LC18:
	.string	"ao->prevarena->nextarena == ao->nextarena"
	.align 8
.LC19:
	.string	"ao->nextarena == NULL || nf <= ao->nextarena->nfreepools"
	.align 8
.LC20:
	.string	"ao->prevarena == NULL || nf > ao->prevarena->nfreepools"
	.align 8
.LC21:
	.string	"ao->nextarena == NULL || ao->nextarena->prevarena == ao"
	.align 8
.LC22:
	.string	"(usable_arenas == ao && ao->prevarena == NULL) || ao->prevarena->nextarena == ao"
	.text
	.globl	Free
	.type	Free, @function
Free:
.LFB7:
	.loc 1 303 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -72(%rbp)
	.loc 1 309 0
	cmpq	$0, -72(%rbp)
	je	.L76
	.loc 1 312 0
	movq	-72(%rbp), %rax
	andq	$-4096, %rax
	movq	%rax, -8(%rbp)
	.loc 1 315 0
	movq	-8(%rbp), %rax
	movl	32(%rax), %edx
	movl	maxarenas(%rip), %eax
	cmpl	%eax, %edx
	jnb	.L52
	.loc 1 315 0 is_stmt 0 discriminator 1
	movq	-72(%rbp), %rdx
	movq	arenas(%rip), %rcx
	movq	-8(%rbp), %rax
	movl	32(%rax), %eax
	movl	%eax, %esi
	movq	%rsi, %rax
	salq	$3, %rax
	subq	%rsi, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	cmpq	$262143, %rax
	ja	.L52
	.loc 1 315 0 discriminator 2
	movq	arenas(%rip), %rdx
	movq	-8(%rbp), %rax
	movl	32(%rax), %eax
	movl	%eax, %ecx
	movq	%rcx, %rax
	salq	$3, %rax
	subq	%rcx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L52
	.loc 1 317 0 is_stmt 1
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	je	.L77
	.loc 1 321 0
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L54
	.loc 1 321 0 is_stmt 0 discriminator 1
	leaq	__PRETTY_FUNCTION__.3311(%rip), %rcx
	movl	$321, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC14(%rip), %rdi
	call	__assert_fail@PLT
.L54:
	.loc 1 323 0 is_stmt 1
	movq	-8(%rbp), %rax
	movl	36(%rax), %eax
	addl	$1, %eax
	sall	$3, %eax
	movl	%eax, %edx
	movq	-72(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset@PLT
	.loc 1 324 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	-72(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 8(%rax)
	.loc 1 326 0
	movq	-8(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rdx, 8(%rax)
	.loc 1 327 0
	cmpq	$0, -16(%rbp)
	je	.L55
.LBB3:
	.loc 1 332 0
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	leal	-1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, (%rax)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L78
	.loc 1 337 0
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -32(%rbp)
	.loc 1 338 0
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -40(%rbp)
	.loc 1 339 0
	movq	-32(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 24(%rax)
	.loc 1 340 0
	movq	-40(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, 16(%rax)
	.loc 1 342 0
	movq	arenas(%rip), %rdx
	movq	-8(%rbp), %rax
	movl	32(%rax), %eax
	movl	%eax, %ecx
	movq	%rcx, %rax
	salq	$3, %rax
	subq	%rcx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	movq	%rax, -48(%rbp)
	.loc 1 343 0
	movq	-48(%rbp), %rax
	movq	32(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 16(%rax)
	.loc 1 344 0
	movq	-48(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 32(%rax)
	.loc 1 345 0
	movq	-48(%rbp), %rax
	movl	24(%rax), %eax
	leal	1(%rax), %edx
	movq	-48(%rbp), %rax
	movl	%edx, 24(%rax)
	movq	-48(%rbp), %rax
	movl	24(%rax), %eax
	movl	%eax, -52(%rbp)
	.loc 1 347 0
	movq	-48(%rbp), %rax
	movq	40(%rax), %rax
	testq	%rax, %rax
	je	.L79
	.loc 1 348 0 discriminator 1
	movq	-48(%rbp), %rax
	movq	40(%rax), %rax
	movl	24(%rax), %eax
	.loc 1 347 0 discriminator 1
	cmpl	%eax, -52(%rbp)
	jbe	.L79
	.loc 1 354 0
	movq	-48(%rbp), %rax
	movq	48(%rax), %rax
	testq	%rax, %rax
	je	.L59
	.loc 1 356 0
	movq	-48(%rbp), %rax
	movq	48(%rax), %rax
	movq	40(%rax), %rax
	cmpq	%rax, -48(%rbp)
	je	.L60
	.loc 1 356 0 is_stmt 0 discriminator 1
	leaq	__PRETTY_FUNCTION__.3311(%rip), %rcx
	movl	$356, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC15(%rip), %rdi
	call	__assert_fail@PLT
.L60:
	.loc 1 357 0 is_stmt 1
	movq	-48(%rbp), %rax
	movq	48(%rax), %rax
	movq	-48(%rbp), %rdx
	movq	40(%rdx), %rdx
	movq	%rdx, 40(%rax)
	jmp	.L61
.L59:
	.loc 1 361 0
	movq	usable_arenas(%rip), %rax
	cmpq	%rax, -48(%rbp)
	je	.L62
	.loc 1 361 0 is_stmt 0 discriminator 1
	leaq	__PRETTY_FUNCTION__.3311(%rip), %rcx
	movl	$361, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC16(%rip), %rdi
	call	__assert_fail@PLT
.L62:
	.loc 1 362 0 is_stmt 1
	movq	-48(%rbp), %rax
	movq	40(%rax), %rax
	movq	%rax, usable_arenas(%rip)
.L61:
	.loc 1 364 0
	movq	-48(%rbp), %rax
	movq	40(%rax), %rax
	movq	-48(%rbp), %rdx
	movq	48(%rdx), %rdx
	movq	%rdx, 48(%rax)
	.loc 1 369 0
	jmp	.L63
.L65:
	.loc 1 371 0
	movq	-48(%rbp), %rax
	movq	40(%rax), %rdx
	movq	-48(%rbp), %rax
	movq	%rdx, 48(%rax)
	.loc 1 372 0
	movq	-48(%rbp), %rax
	movq	40(%rax), %rax
	movq	40(%rax), %rdx
	movq	-48(%rbp), %rax
	movq	%rdx, 40(%rax)
.L63:
	.loc 1 369 0
	movq	-48(%rbp), %rax
	movq	40(%rax), %rax
	testq	%rax, %rax
	je	.L64
	.loc 1 370 0 discriminator 1
	movq	-48(%rbp), %rax
	movq	40(%rax), %rax
	movl	24(%rax), %eax
	.loc 1 369 0 discriminator 1
	cmpl	%eax, -52(%rbp)
	ja	.L65
.L64:
	.loc 1 376 0
	movq	-48(%rbp), %rax
	movq	40(%rax), %rax
	testq	%rax, %rax
	je	.L66
	.loc 1 376 0 is_stmt 0 discriminator 1
	movq	-48(%rbp), %rax
	movq	48(%rax), %rdx
	movq	-48(%rbp), %rax
	movq	40(%rax), %rax
	movq	48(%rax), %rax
	cmpq	%rax, %rdx
	je	.L66
	.loc 1 376 0 discriminator 2
	leaq	__PRETTY_FUNCTION__.3311(%rip), %rcx
	movl	$377, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC17(%rip), %rdi
	call	__assert_fail@PLT
.L66:
	.loc 1 378 0 is_stmt 1
	movq	-48(%rbp), %rax
	movq	48(%rax), %rax
	movq	40(%rax), %rdx
	movq	-48(%rbp), %rax
	movq	40(%rax), %rax
	cmpq	%rax, %rdx
	je	.L67
	.loc 1 378 0 is_stmt 0 discriminator 1
	leaq	__PRETTY_FUNCTION__.3311(%rip), %rcx
	movl	$378, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC18(%rip), %rdi
	call	__assert_fail@PLT
.L67:
	.loc 1 380 0 is_stmt 1
	movq	-48(%rbp), %rax
	movq	48(%rax), %rax
	movq	-48(%rbp), %rdx
	movq	%rdx, 40(%rax)
	.loc 1 381 0
	movq	-48(%rbp), %rax
	movq	40(%rax), %rax
	testq	%rax, %rax
	je	.L68
	.loc 1 382 0
	movq	-48(%rbp), %rax
	movq	40(%rax), %rax
	movq	-48(%rbp), %rdx
	movq	%rdx, 48(%rax)
.L68:
	.loc 1 385 0
	movq	-48(%rbp), %rax
	movq	40(%rax), %rax
	testq	%rax, %rax
	je	.L69
	.loc 1 385 0 is_stmt 0 discriminator 1
	movq	-48(%rbp), %rax
	movq	40(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -52(%rbp)
	jbe	.L69
	.loc 1 385 0 discriminator 2
	leaq	__PRETTY_FUNCTION__.3311(%rip), %rcx
	movl	$386, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC19(%rip), %rdi
	call	__assert_fail@PLT
.L69:
	.loc 1 387 0 is_stmt 1
	movq	-48(%rbp), %rax
	movq	48(%rax), %rax
	testq	%rax, %rax
	je	.L70
	.loc 1 387 0 is_stmt 0 discriminator 1
	movq	-48(%rbp), %rax
	movq	48(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -52(%rbp)
	ja	.L70
	.loc 1 387 0 discriminator 2
	leaq	__PRETTY_FUNCTION__.3311(%rip), %rcx
	movl	$388, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC20(%rip), %rdi
	call	__assert_fail@PLT
.L70:
	.loc 1 389 0 is_stmt 1
	movq	-48(%rbp), %rax
	movq	40(%rax), %rax
	testq	%rax, %rax
	je	.L71
	.loc 1 389 0 is_stmt 0 discriminator 1
	movq	-48(%rbp), %rax
	movq	40(%rax), %rax
	movq	48(%rax), %rax
	cmpq	%rax, -48(%rbp)
	je	.L71
	.loc 1 389 0 discriminator 2
	leaq	__PRETTY_FUNCTION__.3311(%rip), %rcx
	movl	$390, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC21(%rip), %rdi
	call	__assert_fail@PLT
.L71:
	.loc 1 391 0 is_stmt 1
	movq	usable_arenas(%rip), %rax
	cmpq	%rax, -48(%rbp)
	jne	.L72
	.loc 1 391 0 is_stmt 0 discriminator 1
	movq	-48(%rbp), %rax
	movq	48(%rax), %rax
	testq	%rax, %rax
	je	.L75
.L72:
	.loc 1 391 0 discriminator 3
	movq	-48(%rbp), %rax
	movq	48(%rax), %rax
	movq	40(%rax), %rax
	cmpq	%rax, -48(%rbp)
	je	.L80
	.loc 1 391 0 discriminator 4
	leaq	__PRETTY_FUNCTION__.3311(%rip), %rcx
	movl	$393, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC22(%rip), %rdi
	call	__assert_fail@PLT
.L75:
	.loc 1 396 0 is_stmt 1 discriminator 5
	jmp	.L80
.L55:
.LBE3:
	.loc 1 399 0
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	leal	-1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, (%rax)
	.loc 1 400 0
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L74
	.loc 1 400 0 is_stmt 0 discriminator 1
	leaq	__PRETTY_FUNCTION__.3311(%rip), %rcx
	movl	$400, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC14(%rip), %rdi
	call	__assert_fail@PLT
.L74:
	.loc 1 401 0 is_stmt 1
	movq	-8(%rbp), %rax
	movl	36(%rax), %eax
	movl	%eax, -20(%rbp)
	.loc 1 402 0
	movl	-20(%rbp), %eax
	addl	%eax, %eax
	movl	%eax, %eax
	leaq	0(,%rax,8), %rdx
	leaq	usedpools(%rip), %rax
	movq	(%rdx,%rax), %rax
	movq	%rax, -32(%rbp)
	.loc 1 403 0
	movq	-32(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -40(%rbp)
	.loc 1 405 0
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, 16(%rax)
	.loc 1 406 0
	movq	-8(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 24(%rax)
	.loc 1 407 0
	movq	-32(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 24(%rax)
	.loc 1 408 0
	movq	-40(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 16(%rax)
	.loc 1 410 0
	jmp	.L49
.L52:
	.loc 1 414 0
	movq	-72(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	Hugmem(%rip), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	del@PLT
	.loc 1 415 0
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	jmp	.L49
.L76:
	.loc 1 310 0
	nop
	jmp	.L49
.L77:
	.loc 1 318 0
	nop
	jmp	.L49
.L78:
.LBB4:
	.loc 1 335 0
	nop
	jmp	.L49
.L79:
	.loc 1 351 0
	nop
	jmp	.L49
.L80:
	.loc 1 396 0
	nop
.L49:
.LBE4:
	.loc 1 416 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	Free, .-Free
	.globl	gc_malloc
	.type	gc_malloc, @function
gc_malloc:
.LFB8:
	.loc 1 424 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	.loc 1 425 0
	movq	-24(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	Malloc
	movq	%rax, -8(%rbp)
	.loc 1 426 0
	movq	-24(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset@PLT
	.loc 1 427 0
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	orl	$1, %eax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movl	%edx, (%rax)
	.loc 1 428 0
	movq	-8(%rbp), %rax
	addq	$8, %rax
	.loc 1 430 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	gc_malloc, .-gc_malloc
	.globl	gc_init
	.type	gc_init, @function
gc_init:
.LFB9:
	.loc 1 434 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	.loc 1 435 0
	movl	$0, %eax
	call	get_bp@PLT
	movq	%rax, sp_start(%rip)
	.loc 1 436 0
	movl	$8, %edi
	call	malloc@PLT
	movq	%rax, Hugmem(%rip)
.LBB5:
	.loc 1 437 0
	movl	$0, -4(%rbp)
	jmp	.L84
.L85:
	.loc 1 438 0 discriminator 3
	movl	-4(%rbp), %eax
	addl	%eax, %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	usedpools(%rip), %rax
	addq	%rax, %rdx
	movl	-4(%rbp), %eax
	addl	%eax, %eax
	leaq	-16(%rdx), %rcx
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	usedpools(%rip), %rax
	movq	%rcx, (%rdx,%rax)
	.loc 1 439 0 discriminator 3
	movl	-4(%rbp), %eax
	addl	%eax, %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	usedpools(%rip), %rax
	addq	%rax, %rdx
	movl	-4(%rbp), %eax
	addl	%eax, %eax
	addl	$1, %eax
	leaq	-16(%rdx), %rcx
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	usedpools(%rip), %rax
	movq	%rcx, (%rdx,%rax)
	.loc 1 437 0 discriminator 3
	addl	$1, -4(%rbp)
.L84:
	.loc 1 437 0 is_stmt 0 discriminator 1
	cmpl	$31, -4(%rbp)
	jle	.L85
.LBE5:
	.loc 1 441 0 is_stmt 1
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	gc_init, .-gc_init
	.globl	gc_realloc
	.type	gc_realloc, @function
gc_realloc:
.LFB10:
	.loc 1 447 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	.loc 1 448 0
	cmpq	$0, -24(%rbp)
	jne	.L87
	.loc 1 453 0
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	gc_malloc
	jmp	.L88
.L87:
	.loc 1 459 0
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	gc_malloc
	movq	%rax, -8(%rbp)
	.loc 1 460 0
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	.loc 1 461 0
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	gc_free
	.loc 1 462 0
	movq	-8(%rbp), %rax
.L88:
	.loc 1 463 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	gc_realloc, .-gc_realloc
	.globl	gc_free
	.type	gc_free, @function
gc_free:
.LFB11:
	.loc 1 467 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	.loc 1 468 0
	movq	-8(%rbp), %rax
	subq	$8, %rax
	movq	%rax, %rdi
	call	Free
	.loc 1 469 0
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	gc_free, .-gc_free
#	.section	.rodata
	.align 8
	.type	__PRETTY_FUNCTION__.3287, @object
	.size	__PRETTY_FUNCTION__.3287, 10
__PRETTY_FUNCTION__.3287:
	.string	"new_arena"
	.type	__PRETTY_FUNCTION__.3299, @object
	.size	__PRETTY_FUNCTION__.3299, 7
__PRETTY_FUNCTION__.3299:
	.string	"Malloc"
	.type	__PRETTY_FUNCTION__.3311, @object
	.size	__PRETTY_FUNCTION__.3311, 5
__PRETTY_FUNCTION__.3311:
	.string	"Free"
	.text
.Letext0:
	.file 2 "/usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h"
	.file 3 "/usr/include/x86_64-linux-gnu/bits/types.h"
	.file 4 "/usr/include/x86_64-linux-gnu/bits/libio.h"
	.file 5 "/usr/include/stdio.h"
	.file 6 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h"
	.file 7 "/usr/include/unistd.h"
	.file 8 "/usr/include/x86_64-linux-gnu/bits/getopt_core.h"
	.file 9 "/usr/include/time.h"
	.file 10 "/home/xiaodo/c++/colang/src/gc/Hugmem.h"
	.file 11 "/home/xiaodo/c++/colang/src/gc/gc.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x95c
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF123
	.byte	0xc
	.long	.LASF124
	.long	.LASF125
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.long	.LASF7
	.byte	0x2
	.byte	0xd8
	.long	0x38
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF0
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF2
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF4
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.long	.LASF5
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF6
	.uleb128 0x2
	.long	.LASF8
	.byte	0x3
	.byte	0x8c
	.long	0x69
	.uleb128 0x2
	.long	.LASF9
	.byte	0x3
	.byte	0x8d
	.long	0x69
	.uleb128 0x5
	.byte	0x8
	.uleb128 0x6
	.byte	0x8
	.long	0x8e
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF10
	.uleb128 0x7
	.long	0x8e
	.uleb128 0x8
	.long	.LASF40
	.byte	0xd8
	.byte	0x4
	.byte	0xf5
	.long	0x21a
	.uleb128 0x9
	.long	.LASF11
	.byte	0x4
	.byte	0xf6
	.long	0x62
	.byte	0
	.uleb128 0x9
	.long	.LASF12
	.byte	0x4
	.byte	0xfb
	.long	0x88
	.byte	0x8
	.uleb128 0x9
	.long	.LASF13
	.byte	0x4
	.byte	0xfc
	.long	0x88
	.byte	0x10
	.uleb128 0x9
	.long	.LASF14
	.byte	0x4
	.byte	0xfd
	.long	0x88
	.byte	0x18
	.uleb128 0x9
	.long	.LASF15
	.byte	0x4
	.byte	0xfe
	.long	0x88
	.byte	0x20
	.uleb128 0x9
	.long	.LASF16
	.byte	0x4
	.byte	0xff
	.long	0x88
	.byte	0x28
	.uleb128 0xa
	.long	.LASF17
	.byte	0x4
	.value	0x100
	.long	0x88
	.byte	0x30
	.uleb128 0xa
	.long	.LASF18
	.byte	0x4
	.value	0x101
	.long	0x88
	.byte	0x38
	.uleb128 0xa
	.long	.LASF19
	.byte	0x4
	.value	0x102
	.long	0x88
	.byte	0x40
	.uleb128 0xa
	.long	.LASF20
	.byte	0x4
	.value	0x104
	.long	0x88
	.byte	0x48
	.uleb128 0xa
	.long	.LASF21
	.byte	0x4
	.value	0x105
	.long	0x88
	.byte	0x50
	.uleb128 0xa
	.long	.LASF22
	.byte	0x4
	.value	0x106
	.long	0x88
	.byte	0x58
	.uleb128 0xa
	.long	.LASF23
	.byte	0x4
	.value	0x108
	.long	0x252
	.byte	0x60
	.uleb128 0xa
	.long	.LASF24
	.byte	0x4
	.value	0x10a
	.long	0x258
	.byte	0x68
	.uleb128 0xa
	.long	.LASF25
	.byte	0x4
	.value	0x10c
	.long	0x62
	.byte	0x70
	.uleb128 0xa
	.long	.LASF26
	.byte	0x4
	.value	0x110
	.long	0x62
	.byte	0x74
	.uleb128 0xa
	.long	.LASF27
	.byte	0x4
	.value	0x112
	.long	0x70
	.byte	0x78
	.uleb128 0xa
	.long	.LASF28
	.byte	0x4
	.value	0x116
	.long	0x46
	.byte	0x80
	.uleb128 0xa
	.long	.LASF29
	.byte	0x4
	.value	0x117
	.long	0x54
	.byte	0x82
	.uleb128 0xa
	.long	.LASF30
	.byte	0x4
	.value	0x118
	.long	0x25e
	.byte	0x83
	.uleb128 0xa
	.long	.LASF31
	.byte	0x4
	.value	0x11c
	.long	0x26e
	.byte	0x88
	.uleb128 0xa
	.long	.LASF32
	.byte	0x4
	.value	0x125
	.long	0x7b
	.byte	0x90
	.uleb128 0xa
	.long	.LASF33
	.byte	0x4
	.value	0x12d
	.long	0x86
	.byte	0x98
	.uleb128 0xa
	.long	.LASF34
	.byte	0x4
	.value	0x12e
	.long	0x86
	.byte	0xa0
	.uleb128 0xa
	.long	.LASF35
	.byte	0x4
	.value	0x12f
	.long	0x86
	.byte	0xa8
	.uleb128 0xa
	.long	.LASF36
	.byte	0x4
	.value	0x130
	.long	0x86
	.byte	0xb0
	.uleb128 0xa
	.long	.LASF37
	.byte	0x4
	.value	0x132
	.long	0x2d
	.byte	0xb8
	.uleb128 0xa
	.long	.LASF38
	.byte	0x4
	.value	0x133
	.long	0x62
	.byte	0xc0
	.uleb128 0xa
	.long	.LASF39
	.byte	0x4
	.value	0x135
	.long	0x274
	.byte	0xc4
	.byte	0
	.uleb128 0xb
	.long	.LASF126
	.byte	0x4
	.byte	0x9a
	.uleb128 0x8
	.long	.LASF41
	.byte	0x18
	.byte	0x4
	.byte	0xa0
	.long	0x252
	.uleb128 0x9
	.long	.LASF42
	.byte	0x4
	.byte	0xa1
	.long	0x252
	.byte	0
	.uleb128 0x9
	.long	.LASF43
	.byte	0x4
	.byte	0xa2
	.long	0x258
	.byte	0x8
	.uleb128 0x9
	.long	.LASF44
	.byte	0x4
	.byte	0xa6
	.long	0x62
	.byte	0x10
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x221
	.uleb128 0x6
	.byte	0x8
	.long	0x9a
	.uleb128 0xc
	.long	0x8e
	.long	0x26e
	.uleb128 0xd
	.long	0x38
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x21a
	.uleb128 0xc
	.long	0x8e
	.long	0x284
	.uleb128 0xd
	.long	0x38
	.byte	0x13
	.byte	0
	.uleb128 0xe
	.long	.LASF127
	.uleb128 0xf
	.long	.LASF45
	.byte	0x4
	.value	0x13f
	.long	0x284
	.uleb128 0xf
	.long	.LASF46
	.byte	0x4
	.value	0x140
	.long	0x284
	.uleb128 0xf
	.long	.LASF47
	.byte	0x4
	.value	0x141
	.long	0x284
	.uleb128 0x6
	.byte	0x8
	.long	0x95
	.uleb128 0x7
	.long	0x2ad
	.uleb128 0x10
	.long	.LASF48
	.byte	0x5
	.byte	0x87
	.long	0x258
	.uleb128 0x10
	.long	.LASF49
	.byte	0x5
	.byte	0x88
	.long	0x258
	.uleb128 0x10
	.long	.LASF50
	.byte	0x5
	.byte	0x89
	.long	0x258
	.uleb128 0x10
	.long	.LASF51
	.byte	0x6
	.byte	0x1a
	.long	0x62
	.uleb128 0xc
	.long	0x2b3
	.long	0x2ef
	.uleb128 0x11
	.byte	0
	.uleb128 0x7
	.long	0x2e4
	.uleb128 0x10
	.long	.LASF52
	.byte	0x6
	.byte	0x1b
	.long	0x2ef
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF53
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF54
	.uleb128 0xf
	.long	.LASF55
	.byte	0x7
	.value	0x222
	.long	0x319
	.uleb128 0x6
	.byte	0x8
	.long	0x88
	.uleb128 0x10
	.long	.LASF56
	.byte	0x8
	.byte	0x24
	.long	0x88
	.uleb128 0x10
	.long	.LASF57
	.byte	0x8
	.byte	0x32
	.long	0x62
	.uleb128 0x10
	.long	.LASF58
	.byte	0x8
	.byte	0x37
	.long	0x62
	.uleb128 0x10
	.long	.LASF59
	.byte	0x8
	.byte	0x3b
	.long	0x62
	.uleb128 0xc
	.long	0x88
	.long	0x35b
	.uleb128 0xd
	.long	0x38
	.byte	0x1
	.byte	0
	.uleb128 0x10
	.long	.LASF60
	.byte	0x9
	.byte	0x9f
	.long	0x34b
	.uleb128 0x10
	.long	.LASF61
	.byte	0x9
	.byte	0xa0
	.long	0x62
	.uleb128 0x10
	.long	.LASF62
	.byte	0x9
	.byte	0xa1
	.long	0x69
	.uleb128 0x10
	.long	.LASF63
	.byte	0x9
	.byte	0xa6
	.long	0x34b
	.uleb128 0x10
	.long	.LASF64
	.byte	0x9
	.byte	0xae
	.long	0x62
	.uleb128 0x10
	.long	.LASF65
	.byte	0x9
	.byte	0xaf
	.long	0x69
	.uleb128 0x8
	.long	.LASF66
	.byte	0x18
	.byte	0xa
	.byte	0x7
	.long	0x3ce
	.uleb128 0x9
	.long	.LASF67
	.byte	0xa
	.byte	0x9
	.long	0x86
	.byte	0
	.uleb128 0x9
	.long	.LASF68
	.byte	0xa
	.byte	0xa
	.long	0x62
	.byte	0x8
	.uleb128 0x9
	.long	.LASF69
	.byte	0xa
	.byte	0xb
	.long	0x3ce
	.byte	0x10
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x39d
	.uleb128 0x2
	.long	.LASF70
	.byte	0xa
	.byte	0xc
	.long	0x39d
	.uleb128 0x8
	.long	.LASF71
	.byte	0x8
	.byte	0xa
	.byte	0xe
	.long	0x3f8
	.uleb128 0x9
	.long	.LASF72
	.byte	0xa
	.byte	0xf
	.long	0x3f8
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x3d4
	.uleb128 0x2
	.long	.LASF73
	.byte	0xa
	.byte	0x10
	.long	0x3df
	.uleb128 0x2
	.long	.LASF74
	.byte	0xb
	.byte	0x12
	.long	0x38
	.uleb128 0x12
	.byte	0x10
	.byte	0xb
	.byte	0x54
	.long	0x435
	.uleb128 0x9
	.long	.LASF75
	.byte	0xb
	.byte	0x55
	.long	0x62
	.byte	0
	.uleb128 0x9
	.long	.LASF76
	.byte	0xb
	.byte	0x56
	.long	0x86
	.byte	0x8
	.byte	0
	.uleb128 0x2
	.long	.LASF77
	.byte	0xb
	.byte	0x57
	.long	0x414
	.uleb128 0x13
	.byte	0x8
	.byte	0xb
	.byte	0x5a
	.long	0x45f
	.uleb128 0x14
	.long	.LASF78
	.byte	0xb
	.byte	0x5b
	.long	0x45f
	.uleb128 0x14
	.long	.LASF79
	.byte	0xb
	.byte	0x5c
	.long	0x4d
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x3f
	.uleb128 0x8
	.long	.LASF80
	.byte	0x30
	.byte	0xb
	.byte	0x59
	.long	0x4d2
	.uleb128 0x15
	.string	"ref"
	.byte	0xb
	.byte	0x5d
	.long	0x440
	.byte	0
	.uleb128 0x9
	.long	.LASF81
	.byte	0xb
	.byte	0x5e
	.long	0x4d2
	.byte	0x8
	.uleb128 0x9
	.long	.LASF82
	.byte	0xb
	.byte	0x5f
	.long	0x4d8
	.byte	0x10
	.uleb128 0x9
	.long	.LASF83
	.byte	0xb
	.byte	0x60
	.long	0x4d8
	.byte	0x18
	.uleb128 0x9
	.long	.LASF84
	.byte	0xb
	.byte	0x61
	.long	0x4d
	.byte	0x20
	.uleb128 0x9
	.long	.LASF85
	.byte	0xb
	.byte	0x62
	.long	0x4d
	.byte	0x24
	.uleb128 0x9
	.long	.LASF86
	.byte	0xb
	.byte	0x63
	.long	0x4d
	.byte	0x28
	.uleb128 0x9
	.long	.LASF87
	.byte	0xb
	.byte	0x64
	.long	0x4d
	.byte	0x2c
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x435
	.uleb128 0x6
	.byte	0x8
	.long	0x465
	.uleb128 0x2
	.long	.LASF88
	.byte	0xb
	.byte	0x66
	.long	0x4d8
	.uleb128 0x8
	.long	.LASF89
	.byte	0x38
	.byte	0xb
	.byte	0x69
	.long	0x556
	.uleb128 0x9
	.long	.LASF90
	.byte	0xb
	.byte	0x6b
	.long	0x409
	.byte	0
	.uleb128 0x9
	.long	.LASF91
	.byte	0xb
	.byte	0x6e
	.long	0x45f
	.byte	0x8
	.uleb128 0x9
	.long	.LASF92
	.byte	0xb
	.byte	0x71
	.long	0x45f
	.byte	0x10
	.uleb128 0x9
	.long	.LASF93
	.byte	0xb
	.byte	0x74
	.long	0x4d
	.byte	0x18
	.uleb128 0x9
	.long	.LASF94
	.byte	0xb
	.byte	0x77
	.long	0x4d
	.byte	0x1c
	.uleb128 0x9
	.long	.LASF95
	.byte	0xb
	.byte	0x7a
	.long	0x4d8
	.byte	0x20
	.uleb128 0x9
	.long	.LASF96
	.byte	0xb
	.byte	0x7d
	.long	0x556
	.byte	0x28
	.uleb128 0x9
	.long	.LASF97
	.byte	0xb
	.byte	0x7e
	.long	0x556
	.byte	0x30
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x4e9
	.uleb128 0x10
	.long	.LASF98
	.byte	0xb
	.byte	0x80
	.long	0x556
	.uleb128 0x10
	.long	.LASF99
	.byte	0xb
	.byte	0x8c
	.long	0x4d
	.uleb128 0x10
	.long	.LASF100
	.byte	0xb
	.byte	0xa5
	.long	0x86
	.uleb128 0x10
	.long	.LASF101
	.byte	0xb
	.byte	0xb2
	.long	0x588
	.uleb128 0x6
	.byte	0x8
	.long	0x3fe
	.uleb128 0x16
	.long	0x57d
	.byte	0x1
	.byte	0x5
	.uleb128 0x9
	.byte	0x3
	.quad	Hugmem
	.uleb128 0x16
	.long	0x572
	.byte	0x1
	.byte	0x6
	.uleb128 0x9
	.byte	0x3
	.quad	sp_start
	.uleb128 0xc
	.long	0x4de
	.long	0x5c0
	.uleb128 0xd
	.long	0x38
	.byte	0x3f
	.byte	0
	.uleb128 0x17
	.long	.LASF102
	.byte	0x1
	.byte	0x10
	.long	0x5b0
	.uleb128 0x9
	.byte	0x3
	.quad	usedpools
	.uleb128 0x16
	.long	0x55c
	.byte	0x1
	.byte	0x1c
	.uleb128 0x9
	.byte	0x3
	.quad	arenas
	.uleb128 0x16
	.long	0x567
	.byte	0x1
	.byte	0x1e
	.uleb128 0x9
	.byte	0x3
	.quad	maxarenas
	.uleb128 0x17
	.long	.LASF103
	.byte	0x1
	.byte	0x20
	.long	0x556
	.uleb128 0x9
	.byte	0x3
	.quad	unused_arena_objects
	.uleb128 0x17
	.long	.LASF104
	.byte	0x1
	.byte	0x23
	.long	0x556
	.uleb128 0x9
	.byte	0x3
	.quad	usable_arenas
	.uleb128 0x17
	.long	.LASF105
	.byte	0x1
	.byte	0x29
	.long	0x2d
	.uleb128 0x9
	.byte	0x3
	.quad	narenas_currently_allocated
	.uleb128 0x18
	.long	.LASF109
	.byte	0x1
	.value	0x1d3
	.quad	.LFB11
	.quad	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.long	0x662
	.uleb128 0x19
	.string	"p"
	.byte	0x1
	.value	0x1d3
	.long	0x86
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x1a
	.long	.LASF107
	.byte	0x1
	.value	0x1bf
	.long	0x86
	.quad	.LFB10
	.quad	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.long	0x6b0
	.uleb128 0x19
	.string	"p"
	.byte	0x1
	.value	0x1bf
	.long	0x86
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1b
	.long	.LASF106
	.byte	0x1
	.value	0x1bf
	.long	0x2d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1c
	.string	"new"
	.byte	0x1
	.value	0x1cb
	.long	0x86
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x1d
	.long	.LASF128
	.byte	0x1
	.value	0x1b2
	.quad	.LFB9
	.quad	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.long	0x6ee
	.uleb128 0x1e
	.quad	.LBB5
	.quad	.LBE5-.LBB5
	.uleb128 0x1c
	.string	"i"
	.byte	0x1
	.value	0x1b5
	.long	0x62
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.byte	0
	.uleb128 0x1a
	.long	.LASF108
	.byte	0x1
	.value	0x1a7
	.long	0x86
	.quad	.LFB8
	.quad	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.long	0x72f
	.uleb128 0x1b
	.long	.LASF106
	.byte	0x1
	.value	0x1a7
	.long	0x2d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1c
	.string	"hdr"
	.byte	0x1
	.value	0x1a9
	.long	0x4d2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x18
	.long	.LASF110
	.byte	0x1
	.value	0x12e
	.quad	.LFB7
	.quad	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.long	0x7dd
	.uleb128 0x19
	.string	"p"
	.byte	0x1
	.value	0x12e
	.long	0x4d2
	.uleb128 0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x1f
	.long	.LASF111
	.byte	0x1
	.value	0x130
	.long	0x4de
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1f
	.long	.LASF112
	.byte	0x1
	.value	0x131
	.long	0x4d2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x1f
	.long	.LASF69
	.byte	0x1
	.value	0x132
	.long	0x4de
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1f
	.long	.LASF113
	.byte	0x1
	.value	0x132
	.long	0x4de
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1f
	.long	.LASF68
	.byte	0x1
	.value	0x133
	.long	0x4d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x20
	.long	.LASF115
	.long	0x7ed
	.uleb128 0x9
	.byte	0x3
	.quad	__PRETTY_FUNCTION__.3311
	.uleb128 0x21
	.long	.Ldebug_ranges0+0
	.uleb128 0x1c
	.string	"ao"
	.byte	0x1
	.value	0x148
	.long	0x556
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x1c
	.string	"nf"
	.byte	0x1
	.value	0x149
	.long	0x4d
	.uleb128 0x3
	.byte	0x91
	.sleb128 -68
	.byte	0
	.byte	0
	.uleb128 0xc
	.long	0x95
	.long	0x7ed
	.uleb128 0xd
	.long	0x38
	.byte	0x4
	.byte	0
	.uleb128 0x7
	.long	0x7dd
	.uleb128 0x22
	.long	.LASF114
	.byte	0x1
	.byte	0x7a
	.long	0x86
	.quad	.LFB6
	.quad	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.long	0x8aa
	.uleb128 0x23
	.long	.LASF106
	.byte	0x1
	.byte	0x7a
	.long	0x2d
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x24
	.string	"bp"
	.byte	0x1
	.byte	0x7c
	.long	0x4d2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x25
	.long	.LASF111
	.byte	0x1
	.byte	0x7e
	.long	0x4de
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x25
	.long	.LASF69
	.byte	0x1
	.byte	0x7f
	.long	0x4de
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x25
	.long	.LASF68
	.byte	0x1
	.byte	0x80
	.long	0x4d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x26
	.long	.LASF116
	.byte	0x1
	.byte	0xb5
	.quad	.L23
	.uleb128 0x20
	.long	.LASF115
	.long	0x8ba
	.uleb128 0x9
	.byte	0x3
	.quad	__PRETTY_FUNCTION__.3299
	.uleb128 0x27
	.long	.LASF117
	.byte	0x1
	.value	0x121
	.quad	.L22
	.uleb128 0x26
	.long	.LASF118
	.byte	0x1
	.byte	0xe2
	.quad	.L35
	.uleb128 0x1c
	.string	"ret"
	.byte	0x1
	.value	0x125
	.long	0x4d2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.byte	0
	.uleb128 0xc
	.long	0x95
	.long	0x8ba
	.uleb128 0xd
	.long	0x38
	.byte	0x6
	.byte	0
	.uleb128 0x7
	.long	0x8aa
	.uleb128 0x22
	.long	.LASF119
	.byte	0x1
	.byte	0x2f
	.long	0x556
	.quad	.LFB5
	.quad	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.long	0x94a
	.uleb128 0x25
	.long	.LASF120
	.byte	0x1
	.byte	0x31
	.long	0x556
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x25
	.long	.LASF121
	.byte	0x1
	.byte	0x32
	.long	0x4d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x20
	.long	.LASF115
	.long	0x95a
	.uleb128 0x9
	.byte	0x3
	.quad	__PRETTY_FUNCTION__.3287
	.uleb128 0x1e
	.quad	.LBB2
	.quad	.LBE2-.LBB2
	.uleb128 0x24
	.string	"i"
	.byte	0x1
	.byte	0x36
	.long	0x4d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x25
	.long	.LASF122
	.byte	0x1
	.byte	0x37
	.long	0x4d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x25
	.long	.LASF106
	.byte	0x1
	.byte	0x38
	.long	0x2d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.byte	0
	.uleb128 0xc
	.long	0x95
	.long	0x95a
	.uleb128 0xd
	.long	0x38
	.byte	0x9
	.byte	0
	.uleb128 0x7
	.long	0x94a
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x13
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x34
	.byte	0
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0xa
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0xa
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x11
	.uleb128 0x1
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.quad	.LBB3-.Ltext0
	.quad	.LBE3-.Ltext0
	.quad	.LBB4-.Ltext0
	.quad	.LBE4-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF128:
	.string	"gc_init"
.LASF30:
	.string	"_shortbuf"
.LASF126:
	.string	"_IO_lock_t"
.LASF50:
	.string	"stderr"
.LASF19:
	.string	"_IO_buf_end"
.LASF59:
	.string	"optopt"
.LASF75:
	.string	"flags"
.LASF107:
	.string	"gc_realloc"
.LASF17:
	.string	"_IO_write_end"
.LASF3:
	.string	"unsigned int"
.LASF69:
	.string	"next"
.LASF100:
	.string	"sp_start"
.LASF89:
	.string	"arena_object"
.LASF11:
	.string	"_flags"
.LASF124:
	.string	"/home/xiaodo/c++/colang/src/gc/gc.c"
.LASF23:
	.string	"_markers"
.LASF113:
	.string	"prev"
.LASF91:
	.string	"first_address"
.LASF62:
	.string	"__timezone"
.LASF88:
	.string	"poolp"
.LASF71:
	.string	"list"
.LASF122:
	.string	"numarenas"
.LASF125:
	.string	"/home/xiaodo/c++/colang/tests/src/gc"
.LASF44:
	.string	"_pos"
.LASF49:
	.string	"stdout"
.LASF22:
	.string	"_IO_save_end"
.LASF58:
	.string	"opterr"
.LASF79:
	.string	"count"
.LASF54:
	.string	"long long unsigned int"
.LASF82:
	.string	"nextpool"
.LASF108:
	.string	"gc_malloc"
.LASF52:
	.string	"sys_errlist"
.LASF21:
	.string	"_IO_backup_base"
.LASF32:
	.string	"_offset"
.LASF51:
	.string	"sys_nerr"
.LASF67:
	.string	"value"
.LASF25:
	.string	"_fileno"
.LASF92:
	.string	"pool_address"
.LASF7:
	.string	"size_t"
.LASF14:
	.string	"_IO_read_base"
.LASF48:
	.string	"stdin"
.LASF42:
	.string	"_next"
.LASF103:
	.string	"unused_arena_objects"
.LASF95:
	.string	"freepools"
.LASF10:
	.string	"char"
.LASF86:
	.string	"nextoffset"
.LASF38:
	.string	"_mode"
.LASF61:
	.string	"__daylight"
.LASF63:
	.string	"tzname"
.LASF41:
	.string	"_IO_marker"
.LASF102:
	.string	"usedpools"
.LASF12:
	.string	"_IO_read_ptr"
.LASF119:
	.string	"new_arena"
.LASF85:
	.string	"szidx"
.LASF96:
	.string	"nextarena"
.LASF15:
	.string	"_IO_write_base"
.LASF45:
	.string	"_IO_2_1_stdin_"
.LASF53:
	.string	"long long int"
.LASF46:
	.string	"_IO_2_1_stdout_"
.LASF20:
	.string	"_IO_save_base"
.LASF70:
	.string	"ListNode"
.LASF117:
	.string	"redirect"
.LASF123:
	.string	"GNU C11 7.5.0 -mtune=generic -march=x86-64 -g -fno-builtin"
.LASF106:
	.string	"nbytes"
.LASF68:
	.string	"size"
.LASF120:
	.string	"arenaobj"
.LASF57:
	.string	"optind"
.LASF78:
	.string	"_padding"
.LASF33:
	.string	"__pad1"
.LASF34:
	.string	"__pad2"
.LASF35:
	.string	"__pad3"
.LASF36:
	.string	"__pad4"
.LASF37:
	.string	"__pad5"
.LASF111:
	.string	"pool"
.LASF29:
	.string	"_vtable_offset"
.LASF121:
	.string	"excess"
.LASF56:
	.string	"optarg"
.LASF87:
	.string	"maxnextoffset"
.LASF65:
	.string	"timezone"
.LASF101:
	.string	"Hugmem"
.LASF72:
	.string	"root"
.LASF13:
	.string	"_IO_read_end"
.LASF74:
	.string	"Co_uintptr_t"
.LASF5:
	.string	"short int"
.LASF6:
	.string	"long int"
.LASF112:
	.string	"lastfree"
.LASF97:
	.string	"prevarena"
.LASF83:
	.string	"prevpool"
.LASF93:
	.string	"nfreepools"
.LASF73:
	.string	"List"
.LASF55:
	.string	"__environ"
.LASF77:
	.string	"block"
.LASF127:
	.string	"_IO_FILE_plus"
.LASF118:
	.string	"init_pool"
.LASF31:
	.string	"_lock"
.LASF0:
	.string	"long unsigned int"
.LASF90:
	.string	"address"
.LASF27:
	.string	"_old_offset"
.LASF40:
	.string	"_IO_FILE"
.LASF105:
	.string	"narenas_currently_allocated"
.LASF99:
	.string	"maxarenas"
.LASF66:
	.string	"link_list"
.LASF1:
	.string	"unsigned char"
.LASF60:
	.string	"__tzname"
.LASF43:
	.string	"_sbuf"
.LASF16:
	.string	"_IO_write_ptr"
.LASF114:
	.string	"Malloc"
.LASF116:
	.string	"expend_pool"
.LASF76:
	.string	"addr"
.LASF80:
	.string	"pool_header"
.LASF64:
	.string	"daylight"
.LASF110:
	.string	"Free"
.LASF8:
	.string	"__off_t"
.LASF98:
	.string	"arenas"
.LASF4:
	.string	"signed char"
.LASF2:
	.string	"short unsigned int"
.LASF115:
	.string	"__PRETTY_FUNCTION__"
.LASF94:
	.string	"ntotalpools"
.LASF81:
	.string	"freeblock"
.LASF24:
	.string	"_chain"
.LASF109:
	.string	"gc_free"
.LASF26:
	.string	"_flags2"
.LASF104:
	.string	"usable_arenas"
.LASF28:
	.string	"_cur_column"
.LASF47:
	.string	"_IO_2_1_stderr_"
.LASF9:
	.string	"__off64_t"
.LASF39:
	.string	"_unused2"
.LASF18:
	.string	"_IO_buf_base"
.LASF84:
	.string	"arenaindex"
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
