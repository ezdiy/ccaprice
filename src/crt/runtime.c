/* Implement runtime sycalls here */
#include "runtime.h"
#include "inc/stdarg.h"
#include "inc/string.h"

#ifdef __x86_64__
int ccaprice_syscall_error() {
	register int no __asm__("%rcx");
	__asm__ __volatile__ (
		"mov %rax, %rcx\n\t"
		"neg %rcx      \n\t"
	);
	return no;
}
#endif
#ifdef __i386__
int ccaprice_syscall_error() {
	register int no __asm__("%edx");
	__asm__ __volatile__ (
		"mov  %eax, %edx\n\t"
		"negl %edx      \n\t"
	);
	return no;
}
#endif

extern int ccaprice_syscall_core(int, ...); /* syscall :D */
ssize_t write(int fd, const void *buf, size_t count) {
	return ccaprice_syscall_core(SYS_write, fd, buf, count);
}
ssize_t read(int fd, void *buf, size_t count) {
	return ccaprice_syscall_core(SYS_read, fd, buf, count);
}
int open(const char *name, int flags) {
	return ccaprice_syscall_core(SYS_open, name, flags);
}
int close(int fd) {
	return ccaprice_syscall_core(SYS_close, fd);
}
int kill(pid_t pid, int sig) {
	return ccaprice_syscall_core(SYS_kill, pid, sig);
}
int brk(int p) {
	return ccaprice_syscall_core(SYS_brk, p);
}
pid_t getpid() {
	return ccaprice_syscall_core(SYS_getpid);
}
void _exit(int status) {
	ccaprice_syscall_core(SYS_exit, status);
}
