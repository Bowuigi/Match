# Match

Simple (and tiny) pattern matching library in POSIX C99 inspired by the Lua string replacement library.

It is all on a single header and C source, just drop it on your project and include it

Description
-----------

Uses syntax similar to Lua string.{find,match,sub,gsub,etc.}, the options are the following:

| Token |   Matches    |
|-------|--------------|
|  %a   |   Anything   |
|  %h   | Alphanumeric |
|  %l   |    Letters   |
|  %n   |    Numbers   |
|  %p   |  Punctuation |
|  %s   |    Spaces    |
|  %u   |   Uppercase  |
|  %x   |   Hex [0-F]  |

If the tokens are in uppercase, then that match would be inverted, for example, %n matches numbers, but %N matches anything but numbers.

If the token doesn't start with % then it is just a normal exact match

If the token is %%, then it matches '%'

If there is a number between the '%' and the token, it is taken as the amount of times to natch it, for example, "%4n" would match four numbers like "1234"
Usage
-----

Although there is a lot of functions on the header file, the only one that you might want to use is Match_String, since the other ones are for expanding the library
