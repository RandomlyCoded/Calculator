# Calculator
a simple calculator

## Notes about the settings

- enter color codes in the format "rrggbb" in the settings window

## Other useful tips

The formula parser will ignore all whitespaces, line breaks, semicolons and tabulators, so a formula like
```
p
  o w;   (1
  2, 3)
```
will get interpreted as `pow(12, 3)`.

There is also no difference between `sqrt` and `SqRt`.
  
Due to me being lazy, you need to pass *2 arguments* for every function, even if it takes only 1 argument.
I am going to change this behaviour in the future.

Also, you **can't** write `1 + 2`, since the parser can't find the function "1+2" and returns NaN.
Write `add(1, 2)` instead.

the binary functions (or, and, xor, etc.) will directly combine the binary data of the arguments
