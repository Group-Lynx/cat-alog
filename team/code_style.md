# 代码规范

## 目录

- [代码规范](#代码规范)
  - [目录](#目录)
  - [学术规范](#学术规范)
    - [诚信原则](#诚信原则)
    - [求助准则](#求助准则)
  - [风格规范](#风格规范)
    - [缩进规范](#缩进规范)
    - [可读性规范](#可读性规范)
    - [变量规范](#变量规范)
    - [缩写规范](#缩写规范)
  - [实现规范](#实现规范)
    - [函数封装规范](#函数封装规范)
    - [注释规范](#注释规范)
  - [安全规范](#安全规范)
    - [语义安全](#语义安全)
    - [变量安全](#变量安全)
    - [调试安全](#调试安全)
    - [修改安全](#修改安全)
    - [安全例外](#安全例外)

## 学术规范

### 诚信原则

- 禁止使用任何 AI 生成的代码。
- 禁止其它任何违反学术诚信原则的行为。

### 求助准则

- 允许上网搜索、学习他人代码，但仍应遵守学术诚信原则。
- 允许向 AI 寻求帮助，询问已写代码的含义或库函数的功能，但禁止复制任何其生成的任何内容。

## 风格规范

### 缩进规范

- 缩进统一使用空格（<kbd>space</kbd>），每级缩进 4 格。
- 在以下情况下缩进应当增加一级：
  - 用大括号包裹的代码块后；
  - 访问修饰符（`public`、`private`、`protected`）后；
  - `switch` 语句中的 `case`、`default` 后。
- 特殊情况：
  - 访问修饰符（`public`、`private`、`protected`）缩进等级与它所在的大括号相等；
  - `switch` 语句中的 `case`、`default` 缩进等级与 `switch` 相等。

<details>
<summary>缩进规范示例·代码块</summary>

```cpp
int main()
{
    int temp = 0;

    if (temp == 0)
    {
        for (int i = 1; i < 5; i++)
        {
            temp++;
        }
    }
    
    return 0;
}
```

</details>

<details>
<summary>缩进规范示例·类</summary>

```cpp
class Student
{
private:
    unsigned int studentID;
    bool enrolled;

public:
    void Enroll();
}
```

</details>

<details>
<summary>缩进规范示例·<code>switch</code> 语句</summary>

```cpp
switch (enumVariable)
{
case 1:
    /* do something */
    break;
case 2:
    /* do something */
    break;
default:
    /* do something */
    break;
}
```

</details>

### 可读性规范

- 行独占原则：
  - 任何语句应当独占一行；
  - 大括号应当独占一行。
- 空格空行规则：
  - 不同代码块之间应当存在空行。
  - 二元运算符前后应当存在空格，一元运算符应当紧跟操作对象。
  - `.`, `[]`, `->` 等操作符应当紧贴被操作对象。
  - 函数、条件、循环的左括号前应当存在空格。
  - 逗号、分号后如果存在表达式，应当添加空格。
- 其它可读性规则：
  - 长度超过 80 的行应当合理划分、分行书写，相应内容需要对齐。

<details>
<summary>空格空行示例</summary>

```cpp
int ExampleFunction (int argument)
{
    int result = 0；
    int another = 1;

    if (argument == 1)
    {
        result = 1;
    }
    else
    {
        for (int i = 0; i < 10; i++)
        result = argument * 2;
    }

    return result;
}
```

</details>

<details>
<summary>长语句分行示例</summary>

```cpp
for (/* very long expression*/;
     /* very long expression*/;
     /* very long expression*/)
{
    /* do something */
}
```

</details>


### 变量规范

- 变量、函数和表达式宏采用驼峰命名法（CamelCase），使用完整的英语单词命名。变量名首字母小写，函数首字母大写。
- 常量和数值宏采用下划线分割法，使用完整的英语单词命名。全部大写。
- 以下常数应当被定义为常量：
  - 参与数学运算的常数
  - 参与比较运算的常数
  - 不应当被修改的值
- 以下常数应当被定义为宏：
  - 限定长度的常数

<details>
<summary>变量命名规范示例</summary>

```cpp
int studentCount;
int totalScore;

void CalculateScore ();
void EnrollStudent ();

const float PI = 3.14;
const int MAX_SCORE = 300;

#define MAX_LENGTH 10010
```

</details>

### 缩写规范

- 当名称过长时允许缩写。
- 以下变量名允许使用缩写：
  - 临时变量；
  - 循环计数器；
  - 函数参数；
  - 通常以缩写出现的变量；
  - 与保留字冲突的变量名。
- 缩写时应当遵循以下规范：
  - 常用缩写变量名应当保持常用缩写名（`num`、`cnt`、`tmp`）。
  - 允许删去元音字母，谨慎删去辅音字母。
  - 变量的基本读音应被保留。
  - 确保缩写后的变量名仍可识别。

<details>
<summary>命名缩写规范示例</summary>

```cpp
void Function (int src);

for (int idx = 1; idx < 10; idx++)
{
    int tmp = 0;
}
```

</details>

## 实现规范

### 函数封装规范

- 一个函数只应当执行一个功能。如果该函数需求多个功能，应当调用其它的函数来完成。
- 函数需要的所有外部变量应当由参数传递。
- 函数需要的所有变量应当在函数内定义。
- 当返回值为数组或者多个值时，它们应当作为指针参数传递进来，并在函数尾（紧跟在 `return` 前）完成赋值。

<details>
<summary>函数规范示例</summary>

```cpp
int Function (char arg, char *str, int &param)
{
    char *ptr = NULL;
    int value = 0;

    // do something

    str = ptr;
    param = value;
    return 114514;
}
```

</details>

### 注释规范

- 注释位置：
  - 任何函数和方法前需要存在注释。
- 注释要求：
  - 注释必须清晰、简洁。
  - 为避免编码问题，注释应当使用英文。

## 安全规范

### 语义安全

- 涉及操作符优先级的任何表达式，必须以预期的方式用小括号包裹，避免使用默认优先级。
- 操作安全：
  - 禁止操作空指针 `nullptr`，操作指针变量前必须确保非空，必要时要判空；
  - 访问数组时必须确保没有越界，必要时要判界。
- 禁止定义重名变量：
  - 局部作用域变量名必须与其父级作用域的变量名不同；
  - 参数名必须与内部的所有变量名不同。

### 变量安全

- 任何变量在声明时必须被初始化。
- 变量必须承担且仅承担单一职能。
- 临时变量可以例外，但仍应尽量保证安全。

<details>
<summary>变量安全示例</summary>

```cpp
int *ptr = nullptr;
char *ch = malloc(sizeof(char));
```

</details>

### 调试安全

- 禁止为了压行而使用三元运算符（`?:`）。
- 禁止使用逗号表达式（`,`）连接非简单表达式。即使连接，被连接的表达式的数量不能超过 3。
- 禁止使用 `goto` 语句。

### 修改安全

- 任何代码块必须用大括号包裹，即使只有一行。
- 任何非数字常量宏定义必须用小括号包裹。

<details>
<summary>代码块修改安全示例</summary>

```cpp
if (isEnrolled)
{
    // do something
}
else
{
    // do something
}
```

</details>

### 安全例外

- 出于任何情况需要违反安全规则时，应当遵守以下规则：
  - 无论出于任何目的，必须再三思考、保证安全。
  - 在实现处给出简短的注释说明，解释代码行为；
  - 在文件头部注释，指明大致位置，说明该操作的必要性或优秀性。
