####struct once_flag;

Flag argument type for **call_once**
Object of this type are used as arguments for call_once.

Using the same object on different calls to call_once in different threads causes a single execution if called concurrently.

It is a non-copyable, non-movable, default-constructible class, declared in <mutex> with the following prototype:

```
struct once_flag {
  constexpr once_flag() noexcept;
  once_flag (const once_flag&) = delete;
  once_flag& operator= (const once_flag&) = delete;
};

```
