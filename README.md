# Belegpp-Any

[![Last Commit](https://img.shields.io/github/last-commit/belegpp/belegpp-any?style=for-the-badge)](https://github.com/belegpp/belegpp-any/commits)
[![License](https://img.shields.io/github/license/belegpp/belegpp-any?style=for-the-badge)](https://github.com/belegpp/belegpp-any/blob/master/LICENSE)

## What is this?
Belegpp-Any is like std::any but allows for unsafe casts, it provides methods like `is`, `get`, `getUnsafe` and is automatically castable.
I wrote this specifically for belegpp-reflections as std::any didn't fit my needs.

## Example
```cpp
beleg::beleg_any any;
any = 10;
any.is<int>() //-> true;
any.get<int>() //-> 10
any.get<int>() = 5;
any.get<int>() //-> 5;
any = "string";
any.is<const char*>() //-> true
std::cout << any.get<const char*>(); //-> Will print "string".
any.safeGet<int>(); //-> Will throw an exception.
```
Automatic conversion:
```cpp
void test(int a)
{
std::cout << a << std::endl;
}

//...

beleg::beleg_any any = 10;
test(any); //-> Will print 10
```