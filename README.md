# ELang Information

ELang is a simple programming language based on C++.

---

## 1. Syntax

### Variables

Variables are declared using the `id` keyword.

```elang
id x = 3
id y = 4
id z = x + y

x = 5
y = 6
```

### If Statement

Conditional statements use if and are terminated with `end` keyword.


```elang
if (3 == 3 or 3 < 5)
    (...)
end

if ((3 < 5 and 5 > 7) xor (3 > 4 or 5 < 7))
    (...)

else
    (...)
end
```

### Functions

Functions are declared using the `function` keyword.

#### Definition

```elang
function f -> id x
    (...)
end

function g -> id x
    return x
end
```

#### Invocation

Functions are invoked using the `->` operator.

```elang
function func -> id x
    (...)
end

function func2 -> id y
    return y
end

func -> 5
id z = func2 -> 5
```

### Loops

#### While Loop

The `while` loop executes its body while the given condition is true.

```elang
while (5 == 5)
    (...)
end
```

#### Loop

The `loop` statement repeats its body a specified number of times.

```elang
loop (5)
    (...)
end
```

---

## 2. Data Types

### Integer

Represents whole numbers.

```elang
id x = 3
id y = -10
```
### Float

Represents floating-point numbers.

```elang
id pi = 3.14
id e = 2.71
```

### String

Represents text.

```elang
id username = "Admin"
id message = "Hello world!"
```
### Bool

Represents bits(`true`, `false`).

```elang
id is_true = false
is_true = true
```

### List

Represents an ordered collections of values

```elang
id numbers = [1, 2, 3, 4]
id matrix = [[true, false, false, true], [true, false, false, false]]
```

## 3. Operators

### Arithmetic Operators

ELang supports basic arithmetic operators.

| Operator | Description    |
| -------- | -------------- |
| `+`      | Addition       |
| `-`      | Subtraction    |
| `*`      | Multiplication |
| `/`      | Division       |
| `%`      | Modulo         |


```elang
id x = 5
id y = 4

id sum = x + y
id difference = x - y
id mult = x * y
id division = x / y
id remainder = x % y
```

### Comparison Operators

ELang supports basic comparison operators.

| Operator | Description           |
| -------- | --------------------- |
| `==`     | Equal                 |
| `!=`     | Not equal             |
| `>`      | Greater than          |
| `<`      | Less than             |
| `>=`     | Greater than or equal |
| `<=`     | Less than or equal    |

```elang
id x = 4

if (x <= 4)
    (...)
end
```

### Logical Operators

ELang supports basic logical operators.

| Operator | Description  |
| -------- | ------------ |
| `and`    | Logical AND  |
| `or`     | Logical OR   |
| `xor`    | Logical XOR  |
| `nand`   | Logical NAND |

```elang
id x = 3

if (((x < 5 and x > 3) or (x != 10 and x < 0)) xor ((x < 1 or x > 6) nand (x != 5.3 and x >= 65)))
    (...)
end
```

## Built-in Functions

Built-in functions are functions provided by the ELang runtime.

They do not need to be defined by the user.

### output

Displays one or more values.

```elang
id x = 5

output -> "Hello ", "world!"
output -> x + 5
```

### input

Gets input from the user.

```elang
id x = input -> "x: "
id y = input -> "y: "

id sum = x + y
output -> x, " + ", y, " = ", sum
```

### lenght

Gets lenght of the string.

```elang
id text = input -> "Enter a text"
id text_lenght = lenght -> text

output -> text_lenght
```
## Include

The `include` statement loads a library or module.

```elang
include "math"
include "random"
```
