# Arbitrary Precision Calculator (APC)

## 📌 About the Project

The **Arbitrary Precision Calculator (APC)** is a C-based calculator that performs arithmetic operations on very large integers that cannot be stored in standard C data types such as `int`, `long`, or `long long`.

The project uses a **Doubly Linked List (DLL)** to store each digit separately.

### Supported Operations

- Addition (`+`)
- Subtraction (`-`)
- Multiplication (`*`)
- Division (`/`)
- Positive and negative integers
- Arbitrary-length numbers

---

## 🛠️ Requirements

Before running the project, make sure you have:

- GCC compiler
- Linux / Ubuntu / WSL
- Git (optional, for cloning the repository)

---

## 🔨 Compilation

Compile all C source files using:

```bash
gcc *.c
```

After successful compilation, an executable named `a.out` will be created.

---

## ▶️ How to Run

The program uses **Command Line Arguments**.

### Syntax

```bash
./a.out <number1> <operator> <number2>
```

### Examples

#### Addition

```bash
./a.out 123 + 456
```

#### Addition with Negative Numbers

```bash
./a.out -123 + -222
```

#### Subtraction

```bash
./a.out 500 - 250
```

#### Subtraction with Negative Numbers

```bash
./a.out -123 - -222
```

#### Multiplication

When using `*` in the terminal, escape it:

```bash
./a.out 123 \* 456
```

#### Division

```bash
./a.out 1000 / 10
```

---

## 📌 Sample Output

### Example 1: Addition

Command:

```bash
./a.out -123 + -222
```

Output:

```text
        Arbitrary Precision Calculator

        -123
      + -222
      --------
        -345
```

### Example 2: Addition with Different Signs

Command:

```bash
./a.out -123 + 124
```

Output:

```text
        Arbitrary Precision Calculator

        -123
      + 124
      --------
           1
```

---

## ⚠️ Error Handling

The program validates command-line arguments and checks for invalid input.

Example:

```bash
./a.out 123 % 10
```

Output:

```text
Invalid Arguments
Usage: ./a.out <num1> <operator> <num2>
```

### Division by Zero

```bash
./a.out 100 / 0
```

Output:

```text
ERROR: Division by zero is not possible
Failed to perform division
```

---

## 🧠 How It Works

Each digit of the input number is stored in a node of a doubly linked list.

For example:

```text
123456

HEAD
 ↓
[1] <-> [2] <-> [3] <-> [4] <-> [5] <-> [6]
                                             ↑
                                            TAIL
```

The sign is stored separately from the digit list.

For example:

```text
-123

sign = '-'

DLL:
[1] <-> [2] <-> [3]
```

This allows the arithmetic functions to operate on the magnitude of the numbers while sign handling is performed separately.

---

## 🔧 Main Functions

| Function | Purpose |
|---|---|
| `validate_cla_inputs()` | Validates command-line arguments |
| `isNumber()` | Validates numeric input |
| `signExtraction()` | Extracts input signs |
| `slicing_input_dll()` | Stores digits in DLL |
| `compare_lists()` | Compares two numbers |
| `addition()` | Performs arbitrary precision addition |
| `subtraction()` | Performs arbitrary precision subtraction |
| `multiplication()` | Performs arbitrary precision multiplication |
| `division()` | Performs arbitrary precision division |
| `print_res()` | Displays the formatted result |
| `dl_delete_list()` | Frees allocated DLL memory |

---

## 📂 Project Structure

```text
Arbitrary_Precision_Calculator/
│
├── main.c
├── apc.c
├── apc.h
├── README.md
└── ...
```

---

## 🎯 Learning Outcomes

This project demonstrates practical knowledge of:

- C programming
- Pointers
- Structures
- Doubly Linked Lists
- Dynamic Memory Allocation
- Command Line Arguments
- Arithmetic algorithms
- Carry and borrow handling
- Sign handling
- Memory management
- Debugging
- Git and GitHub

---

## 🚀 Future Improvements

- Modulus (`%`) operation
- Power operation
- Square root
- Decimal number support
- More efficient division algorithm
- Automated test cases
- Improved error handling
- Memory leak testing and optimization

---

## 👨‍💻 Author

**Gaurav Ambolikar**

Electronics and Telecommunication Engineering

---

## 📜 License

This project is created for educational and learning purposes.
