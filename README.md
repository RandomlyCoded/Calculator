# Calculator
a simple calculator

## Notes about the settings:

- please **do not edit** settings.txt
- enter color codes in the format "rrggbb" in the settings window

## Other useful tips

the formula parser will ignore all whitespaces, line breaks, semicolons and tabulators, so a formula like
```p
  o w   (1
  2, 3)```
will get interpreted as `pow(12, 3)`.
  
due to me being lazy, you need to pass *2 arguments* for every function, even if it takes only 1 argument
I am going to change this behaviour in the future.

the binary functions (or, and, xo, etc.) will directly combine the binary data of the arguments
