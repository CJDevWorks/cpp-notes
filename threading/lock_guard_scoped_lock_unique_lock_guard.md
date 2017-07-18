

why mutex is not movable and copyable? but thread is?

Well... mainly because I don't think they should move. Literally.

In some OS-es a mutex might be modeled as a handle (so you could copy them) but IIRC a pthreads mutex is manipulated in-place. If you are going to relocate that, any threadsafety is going fly right out of the window (how would the other threads know that the mutex had just changed it's memory address...)?

**lock_guard**

why local guard is non copyable and non movaable.

```

```

**Scoped_lock**

```

```

**Difference between lock guard and scoped lock**

Explicit locking and unlocking a mutex with a std::unique_lock<>
As we saw in part 4 of this series, std::lock_guard<> is very strict on lock ownership — it owns the lock from construction to destruction, with no room for manoeuvre. std::unique_lock<> is rather lax in comparison. As well as acquiring a lock in the constructor as for std::lock_guard<>, you can:

construct an instance without an associated mutex at all (with the default constructor);
construct an instance with an associated mutex, but leave the mutex unlocked (with the deferred-locking constructor);
construct an instance that tries to lock a mutex, but leaves it unlocked if the lock failed (with the try-lock constructor);
if you have a mutex that supports locking with a timeout (such as std::timed_mutex) then you can construct an instance that tries to acquire a lock for either a specified time period or until a specified point in time, and leaves the mutex unlocked if the timeout is reached;
lock the associated mutex if the std::unique_lock<> instance doesn't currently own the lock (with the lock() member function);
try and acquire lock the associated mutex if the std::unique_lock<> instance doesn't currently own the lock (possibly with a timeout, if the mutex supports it) (with the try_lock(), try_lock_for() and try_lock_until() member functions);
unlock the associated mutex if the std::unique_lock<> does currently own the lock (with the unlock() member function);
check whether the instance owns the lock (by calling the owns_lock() member function;
release the association of the instance with the mutex, leaving the mutex in whatever state it is currently (locked or unlocked) (with the release() member function); and
transfer ownership between instances, as described above.
As you can see, std::unique_lock<> is quite flexible: it gives you complete control over the underlying mutex, and actually meets all the requirements for a Lockable object itself. You can thus have a std::unique_lock<std::unique_lock<std::mutex>> if you really want to! However, even with all this flexibility it still gives you exception safety: if the lock is held when the object is destroyed, it is released in the destructor.

std::unique_lock<> and condition variables
One place where the flexibility of std::unique_lock<> is used is with std::condition_variable. std::condition_variable provides an implementation of a condition variable, which allows a thread to wait until it has been notified that a certain condition is true. When waiting you must pass in a std::unique_lock<> instance that owns a lock on the mutex protecting the data related to the condition. The condition variable uses the flexibility of std::unique_lock<> to unlock the mutex whilst it is waiting, and then lock it again before returning to the caller. This enables other threads to access the protected data whilst the thread is blocked. I will expand upon this in a later part of the series.


**shared_lock**


**unique_lock**



**boost::upgradable_lock**