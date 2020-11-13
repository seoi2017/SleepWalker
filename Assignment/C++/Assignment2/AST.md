# CS205 Assignment 2 AST Parser
## 功能简介
- 数学表达式解析及运算
- 运算符支持
    - 加法操作符（`+`）
    - 减法操作符（`-`）
    - 乘法操作符（`*`）
    - 整除操作符（`//`）
    - 除法操作符（`/`）
    - 取模操作符（`%`）
- 函数支持
    - 阶乘函数（`Fact(x)`，一元）
    - 幂函数（`Pow(x, y)`，二元）
    - 平方根函数（`Sqrt(x)`，一元）
    - 可拓展其他一元或多元函数
- 指令与变量支持
    - 退出指令（`Quit()`）
    - 清除变量表指令（`(Clear())`）
    - 变量定义与赋值指令（`Var = Num`）
- 其他特性
    - 运算符优先级与括号支持
    - 自动忽略多余空格
    - 多字母变量名支持
    - 信息与错误提示（异常抛出）
    - 变量的表达式赋值支持
- 局限性
    - 变量名与函数名须以大写字母开始，后续字母必须全为小写
    - 不能支持符号计算（带有未知量的表达式计算）
    - 不支持分数计算（不能保证小数的精度）
## 递归文法分析
*注：以下递归分析结构不含变量相关内容，变量相关另行处理*
```
EXP    ->   TERM EXPs
EXPs   ->   + TERM EXPs | 
            - TERM EXPs | 
            NULL
TERM   ->   FACTOR TERMs
TERMs  ->   *  FACTOR TERMs | 
            /  FACTOR TERMs | 
            // FACTOR TERMs | 
            %  FACTOR TERMs
FACTOR ->   ( EXP )            |
            - EXP              |
            NUMBER             |
            Fact ( EXP )       |
            Pow  ( EXP , EXP ) |
            Quit  ( )          |
            Clear ( )
```
优先级等级及其执行顺序：`3 < 2 < 1`

`EXP`：优先级等级3的节点，执行加法

`EXPs`：`EXP`的实现节点，为空时值为0

`TERM`：优先级等级2的节点，执行乘法

`TERMs`：`TERM`的实现节点，为空时值为1

`FACTOR`：优先级等级1的节点，可作为递归终点
