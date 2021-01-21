.text
.globl sleep
sleep:
     sub    $0x18,%rsp
     mov    %rdi,%rax
     imul   $1000000,%rax,%rax
     mov    %rax,0x20(%rsp)
     mov    %rbp,0x10(%rsp)
     lea    0x10(%rsp),%rbp
     mov    $0x0,%edx
     mov    0x20(%rsp),%eax
     mov    $0xf4240,%ecx
     div    %ecx
     mov    %rax,(%rsp)
     mov    $0x3e8,%eax
     mul    %edx
     mov    %rax,0x8(%rsp)
     mov    $0x0,%edi
     mov    $0x0,%esi
     mov    $0x0,%edx
     mov    $0x0,%r10d
     mov    %rsp,%r8
     mov    $0x0,%r9d
     mov    $0x10e,%eax
     syscall
     mov    0x10(%rsp),%rbp
     add    $0x18,%rsp
     retq
.globl usleep
usleep:
     sub    $0x18,%rsp
     mov    %rdi,0x20(%rsp)
     mov    %rbp,0x10(%rsp)
     lea    0x10(%rsp),%rbp
     mov    $0x0,%edx
     mov    0x20(%rsp),%eax
     mov    $0xf4240,%ecx
     div    %ecx
     mov    %rax,(%rsp)
     mov    $0x3e8,%eax
     mul    %edx
     mov    %rax,0x8(%rsp)
     mov    $0x0,%edi
     mov    $0x0,%esi
     mov    $0x0,%edx
     mov    $0x0,%r10d
     mov    %rsp,%r8
     mov    $0x0,%r9d
     mov    $0x10e,%eax
     syscall
     mov    0x10(%rsp),%rbp
     add    $0x18,%rsp
     retq
