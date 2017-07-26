
Software platform dependent optimization.

In bottlenecks, optimization techniques that are dependent both on the programming language and on the software platform, but independent on the hardware platform are applied. For example,

- compiler options,

- pragma compiler directives,

- language extensions,

- non-standard libraries,

- direct calls to the operating system are exploited.

If this makes the program fast enough, the optimization stage is complete.

Linux kernel tuning

	* page cache (kernel) lock contention
	* power management tuning in BIOS & OS
	* mapped file access faults & safepoints
	* Out-of-the box Linux has come bad defaults
	* Page cache: vm.minfreekbytes [needs > 1GB]
	* Transparent Huge Pages (THP) [should be turned off]
	* Swappines [should be set to 0]
	* zoneclaiminfo [should be set to 0]

