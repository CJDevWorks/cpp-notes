
```
template <class Fn, class... Args>
  void call_once (once_flag& flag, Fn&& fn, Args&&... args);
```

The function modifies flag, and accesses fn and args to create decay copies of their lvalue or rvalue references. ignoring the value returned by fn.



- Calls fn passing args as arguments, unless another thread has already executed (or is currently executing) a call to call_once with the same flag.

- If another thread is already actively executing a call to call_once with the same flag, it causes a passive execution: Passive executions do not call fn but do not return until the active execution itself has returned, and all visible side effects are synchronized at that point among all concurrent calls to this function with the same flag.

- If an active call to call_once ends by throwing an exception (which is propagated to its calling thread) and passive executions exist, one is selected among these passive executions, and called to be the new active call instead.

- Note that once an active execution has returned, all current passive executions and future calls to call_once (with the same flag) also return without becoming active executions.
