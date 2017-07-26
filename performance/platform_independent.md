Platform independent optimization. In bottlenecks, optimization techniques that are
dependent on the programming language and its standard library, but independent both
on the software platform and on the hardware platform are applied. For example, in operations are used instead of floating point operations, or the more appropriate container
                                                                                   class is chosen among the ones available in the standard library. If this makes the program
                                                                                   fast enough, the optimization stage is complete.



	* Look at memory usage, look at branching penalties, Look at function call overhead, look at pipeline utilisation.

	* Look at virtual function calls, excessive callstack depth, etc. A common cause for bad performance is the erroneous belief that base classes must be virtual.


	* Be careful of excessive allocation/deallocation. If it’s performance critical, don’t call into the runtime.


	* Avoid copy constructors. If it can be a const reference, make it one.

	* Remove unnecessary branches



Cache friendly data structures

	* Data structures that are contained within a single cache-line are more efficient.
	* Use appropriate containers (e.g. prefer reserved std::vector than std::list).
	* Organize your data to avoid alignment holes (sorting your struct members by decreasing size is one way).
	* Don’t neglect the cache in data structure and algorithm design.
	* Use smaller data types
	* Beware of the standard dynamic memory allocator, which may introduce holes and spread your data around in memory as it warms up.
	* Make sure all adjacent data is actually used in the hot loops. Otherwise, consider breaking up data structures into hot and cold components, so that the hot loops use hot data.
	* Avoid algorithms and datastructures that exhibit irregular access patterns, and favor linear data structures.
	* Know and exploit the implicit structure of data.

Write cache friendly code

	* Place related data close in memory to allow efficient caching – the principle of locality
	* Understand how cache lines work
	* Use appropriate data structures
	* Avoid unpredictable branches
	* Avoid virtual functions
	* Avoid false sharing problem
	* When context switch happens the processor involved is likely to lose the data in its caches.
	* Try to have regular access pattern that will let hardware prefetcher to work efficiently.
	* Start addressing what is called temporal locality
	* Merge loops that touch the same data (loop fusion), and employing rewriting techniques known as tiling or blocking

Following those rules will minimize numer of page faults (caused by thrashing) – latency killer.



IPC shared memory for the aboslute lowest latency between our trading processes.


CPU shielding/processor affinity,

IRQ balance,

splitting order entry nics,

**market data nics etc**

40G InfiniBand
• Available since 2009, creates large L2, low latency, high throughput networks
with RDMA,  bypassing TCP stacks
• Compatible with existing TCP/IP socket programs with IPoIB
• Extensive and well proven management capabilities
• TCP bypass
• InfiniBand Verbs/RDMA, RoCEE or iWARP are main contenders and share
common API’s

Initially just InfiniBand but now RDMA Ethernet with RoCEE and iWARP
• InfiniBand - just treat it like a TCP/IP socket
• Running IP over InfiniBand (IPoIB)
• Full support of all IP protocols and multicast
• Pre-load SDP to bypass TCP/IP stack for TCP sessions
• For optimal performance need to change API’s to use zcopy and RDMA
transfer direct between Application memory spaces.  Several API's of
varying degrees of complexity and performance provide this
• Reliable Datagram Sockets (RDS) – Used by Oracle for RAC
• Direct Access Programming Library (DAPL) – used by IBM for DB2
• Libibverbs – fastest access, near native access to HW VERBS – used by
Websphere LLM, TIBCO FTL, Millenium IT, IBM GFS
• Able to support both ping-pong and pub-sub Use cases

hardware based ticker planet which our servers subscribe to for market data via infiniband by passing the TCP stack using RDMA “Remote direct memory access”.


**Multi Cast**


**TLB**
