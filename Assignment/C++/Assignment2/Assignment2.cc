/*
Environment: C++11
Course: SUSTech_C++
Problem ID: Assignment_2
*/
#include <bits/stdc++.h>
#define PRECISION 16 // 小数除法最大精度
#define EPS BigNum("0.0000000001")
using namespace std;
class SCCError : public exception // 异常总类
{
private:
    string message;

public:
    SCCError(const string &str)
    {
        this->message = "[Error Detected] " + str;
    }
    string getMessage()
    {
        return this->message;
    }
};
class BigNum // 高精度数字类
{
private:
    string integer;
    string decimal;
    bool isMinus;
    inline bool isDecZero() // 判断小数部分是否为零
    {
        for (char i : this->decimal)
            if (i != '0')
                return false;
        return true;
    }
    inline void removeZero() // 首尾去零
    {
        this->integer.erase(0, this->integer.find_first_not_of('0'));
        reverse(this->decimal.begin(), this->decimal.end());
        this->decimal.erase(0, this->decimal.find_first_not_of('0'));
        reverse(this->decimal.begin(), this->decimal.end());
    }
    inline void fitZero(BigNum &x, BigNum &y) // 补零对齐
    {
        int intDigitX = x.integer.length();
        int intDigitY = y.integer.length();
        int decDigitX = x.decimal.length();
        int decDigitY = y.decimal.length();
        int maxIntDigit = max(intDigitX, intDigitY);
        int maxDecDigit = max(decDigitX, decDigitY);
        if (intDigitX < maxIntDigit)
            x.integer = string(maxIntDigit - intDigitX, '0') + x.integer;
        if (intDigitY < maxIntDigit)
            y.integer = string(maxIntDigit - intDigitY, '0') + y.integer;
        if (decDigitX < maxDecDigit)
            x.decimal += string(maxDecDigit - decDigitX, '0');
        if (decDigitY < maxDecDigit)
            y.decimal += string(maxDecDigit - decDigitY, '0');
    }
    inline string combine() // 无符号字串拼接
    {
        return this->integer + this->decimal;
    }
    inline BigNum getAbs()
    {
        BigNum result = (*this);
        result.isMinus = false;
        return result;
    }
    inline BigNum getSqrt()
    {
        BigNum val = (*this);
        BigNum left = BigNum("0"), right = val;
        BigNum mid = (left + right) / BigNum("2");
        while (mid.decimal.length() < PRECISION)
        {
            if ((mid * mid) > val)
                right = mid;
            else
                left = mid;
            mid = (left + right) / BigNum("2");
        }
        return mid;
    }
    inline BigNum getFloatPower(const BigNum &x)
    {
        BigNum base = BigNum("0.5"), ans = BigNum("1");
        BigNum power = x, val = this->getSqrt();
        while (power.getAbs() > EPS)
        {
            if (power >= base)
            {
                ans *= val;
                power -= base;
            }
            base *= base;
            val = val.getSqrt();
        }
        return ans;
    }

protected:
    inline void setValue(const BigNum &x) // 仅用于变量类赋值用
    {
        this->operator=(x);
    }
    inline BigNum getValue() // 仅用于变量类取值用
    {
        return (*this);
    }

public:
    BigNum()
    {
        this->isMinus = false;
        this->integer.clear();
        this->decimal.clear();
    }
    BigNum(const string &str)
    {
        *this = str;
    }
    BigNum operator=(const BigNum &x)
    {
        this->decimal = x.decimal;
        this->integer = x.integer;
        this->isMinus = x.isMinus;
        return *this;
    }
    BigNum operator=(const string &str)
    {
        if (str[0] == '-')
            this->isMinus = true;
        else
            this->isMinus = false;
        string::size_type dpos = str.find('.');
        int eps = this->isMinus ? 1 : 0;
        if (dpos == string::npos)
            this->integer = str.substr(eps);
        else
        {
            this->integer = string(str, eps, dpos - eps);
            this->decimal = string(str, dpos + 1, str.length() - (dpos + 1));
        }
        this->removeZero();
        return *this;
    }
    // 逻辑运算
    bool operator>(const BigNum &x) const
    {
        bool minusT = this->isMinus;
        bool minusX = x.isMinus;
        if (minusT ^ minusX)
            return minusX;
        if (minusT == true) // 如果两个负数比较，则去负号后反比
        {
            BigNum a = *this, b = x;
            a.isMinus = b.isMinus = false;
            return a < b;
        }
        int lenT = this->integer.length();
        int lenX = x.integer.length();
        if (lenX != lenT)
            return lenT > lenX;
        int intC = this->integer.compare(x.integer);
        if (intC != 0)
            return intC > 0;
        int lenD = min(this->decimal.length(), x.decimal.length());
        for (register int i = 0; i < lenD; ++i)
            if (this->decimal[i] != x.decimal[i])
                return this->decimal[i] > x.decimal[i];
        return this->decimal.length() > x.decimal.length();
    }
    bool operator<(const BigNum &x) const
    {
        bool minusT = this->isMinus;
        bool minusX = x.isMinus;
        if (minusT ^ minusX)
            return minusT;
        if (minusT == true) // 如果两个负数比较，则去负号后反比
        {
            BigNum a = *this, b = x;
            a.isMinus = b.isMinus = false;
            return a > b;
        }
        int lenT = this->integer.length();
        int lenX = x.integer.length();
        if (lenX != lenT)
            return lenT < lenX;
        int intC = this->integer.compare(x.integer);
        if (intC != 0)
            return intC < 0;
        int lenD = min(this->decimal.length(), x.decimal.length());
        for (register int i = 0; i < lenD; ++i)
            if (this->decimal[i] != x.decimal[i])
                return this->decimal[i] < x.decimal[i];
        return this->decimal.length() < x.decimal.length();
    }
    bool operator<=(const BigNum &x) const
    {
        return !this->operator>(x);
    }
    bool operator>=(const BigNum &x) const
    {
        return !this->operator<(x);
    }
    bool operator==(const BigNum &x) const
    {
        return !this->operator<(x) && !this->operator>(x);
    }
    bool operator!=(const BigNum &x) const
    {
        return !this->operator==(x);
    }
    // 四则运算
    BigNum operator+(const BigNum &x)
    {
        bool minusT = this->isMinus;
        bool minusX = x.isMinus;
        if (minusT == true && minusX == false) // 仅有一个是负数
        {
            BigNum y = *this, z = x;
            y.isMinus = false;
            return z - y;
        }
        else if (minusT == false && minusX == true)
        {
            BigNum y = x;
            y.isMinus = false;
            return this->operator-(y);
        }
        BigNum result = *this, temp = x;
        this->fitZero(result, temp);
        int decDigit = result.decimal.length();
        string valX = result.combine();
        string valY = temp.combine();
        int lenStr = valX.length();
        reverse(valX.begin(), valX.end()); // 逆序方便进位
        reverse(valY.begin(), valY.end());
        int toF = 0; // 进位指数
        for (register int i = 0, sum = 0; i < lenStr; ++i)
        {
            sum = (valX[i] - '0') + (valY[i] - '0') + toF;
            valX[i] = sum % 10 + '0';
            toF = sum / 10;
        }
        if (toF != 0)
        {
            valX += (toF % 10 + '0'); // 由于已经逆序，在后面添加即可
            toF /= 10;
        }
        valX = valX.substr(0, decDigit) + '.' + valX.substr(decDigit);
        if (minusT == true)
            valX += '-';
        reverse(valX.begin(), valX.end());
        return BigNum(valX);
    }
    BigNum operator-(const BigNum &x)
    {
        bool minusT = this->isMinus;
        bool minusX = x.isMinus;
        if (minusX == true)
        {
            BigNum y = x;
            y.isMinus = false;
            return this->operator+(y);
        }
        else if (minusT == true)
        {
            BigNum y = *this, z = x;
            y.isMinus = false;
            BigNum ans = y + z;
            ans.isMinus = true;
            return ans;
        }
        else if (this->operator<(x) == true)
        {
            BigNum y = x, z = (*this);
            BigNum ans = y - z;
            ans.isMinus = true;
            return ans;
        }
        // 以上三步保证必定是大减小
        BigNum result = *this, temp = x;
        this->fitZero(result, temp);
        int decDigit = result.decimal.length();
        string valX = result.combine();
        string valY = temp.combine();
        int lenStr = valX.length();
        reverse(valX.begin(), valX.end());
        reverse(valY.begin(), valY.end());
        for (register int i = 0, sub = 0; i < lenStr; ++i)
        {
            if (valX[i] < valY[i]) // 需要借位
            {
                for (register int j = 1; true; ++j)
                    if (valX[i + j] == 0) // 不能借位
                    {
                        valX[i + j] = '9';
                        continue;
                    }
                    else
                    {
                        valX[i + j] = valX[i + j] - 1; // 即便是字符型，也可以减去一
                        break;
                    }
                valX[i] = valX[i] - valY[i] + 10 + '0';
            }
            else
                valX[i] = valX[i] - valY[i] + '0';
        }
        valX = valX.substr(0, decDigit) + '.' + valX.substr(decDigit);
        reverse(valX.begin(), valX.end());
        return BigNum(valX);
    }
    BigNum operator*(const BigNum &x)
    {
        bool minus = (this->isMinus ^ x.isMinus);
        BigNum result = *this, temp = x;
        this->fitZero(result, temp);
        int decDigit = result.decimal.length();
        string valX = result.combine();
        string valY = temp.combine();
        int lenStr = valX.length();
        reverse(valX.begin(), valX.end());
        reverse(valY.begin(), valY.end());
        result = BigNum();
        for (register int i = 0, mul = 0; i < lenStr; ++i)
        {
            string valT;
            mul = 0;
            for (register int j = 0; j < lenStr; ++j)
            {
                mul += (valX[i] - '0') * (valY[j] - '0');
                valT += mul % 10 + '0';
                mul /= 10;
            }
            while (mul != 0)
            {
                valT += mul % 10 + '0';
                mul /= 10;
            }
            valT = string(i, '0') + valT;
            reverse(valT.begin(), valT.end());
            result += BigNum(valT);
        }
        valX = string(decDigit * 2, '0') + result.integer;
        reverse(valX.begin(), valX.end());
        valX = valX.substr(0, decDigit * 2) + '.' + valX.substr(decDigit * 2);
        if (minus == true)
            valX += '-';
        reverse(valX.begin(), valX.end());
        return BigNum(valX);
    }
    BigNum operator/(const BigNum &x) // 小数点后至多延伸10位的精确除法
    {
        BigNum y = *this, z = x;
        int decDigitT = this->decimal.length();
        int decDigitX = x.decimal.length();
        bool minus = (this->isMinus ^ x.isMinus);
        y.integer += (y.decimal + string(PRECISION, '0'));
        z.integer += z.decimal;
        y.decimal.clear(), y.isMinus = false; // 清除负数标记，以免死循环
        z.decimal.clear(), z.isMinus = false;
        string valX = (y % z).first;
        reverse(valX.begin(), valX.end());
        valX = valX.substr(0, decDigitT - decDigitX + PRECISION) + '.' + valX.substr(decDigitT - decDigitX + PRECISION);
        if (minus == true)
            valX += '-';
        reverse(valX.begin(), valX.end());
        return BigNum(valX);
    }
    pair<string, BigNum> operator%(const BigNum &x) // 整除与余数（仅限整数）
    {
        if (this->decimal.length() > 0 || x.decimal.length() > 0)
            throw SCCError("The parameters of the divisible and modulus operations cannot be float.");
        if (x == BigNum("0"))
            throw SCCError("The dividend/modulus cannot be zero.");
        bool minus = (this->isMinus ^ x.isMinus);
        string valX = this->combine(), valY, ans;
        BigNum temp = x;
        temp.isMinus = false; // 清除负数标记，以免死循环
        int lenStr = valX.length();
        for (register int i = 0, div = 0; i < lenStr; ++i, div = 0)
        {
            BigNum t = string(valX, 0, i + 1);
            while (temp <= t)
            {
                t -= temp; // 如果temp是负数，这里会死循环
                ++div;
            }
            if (div == 0)
            {
                ans += '0';
                continue;
            }
            valY = t.toString();
            valX.replace(0, i + 1, i + 1, '0');
            valX.replace(i + 1 - valY.length(), valY.length(), valY);
            ans += (div + '0');
        }
        if (minus == true)
            ans = '-' + ans, valX = '-' + valX;
        return make_pair(ans, BigNum(valX));
    }
    BigNum operator^(const BigNum &x) // 快速幂（可计算小数幂、负数幂）
    {
        if (this->isMinus == true && x.decimal.length() > 0) // 负数不可开根
            throw SCCError("Negative Numbers are not supported for float powers.");
        BigNum result = BigNum("1"), base = (*this), power = BigNum(x.integer);
        while (power > BigNum("0"))
        {
            if ((power % BigNum("2")).second == BigNum("1"))
                result *= base;
            power /= BigNum("2");
            base *= base;
        }
        BigNum temp = x;
        temp.integer.clear(), temp.isMinus = false;
        result *= this->getFloatPower(temp);
        if (x.isMinus == true)
            return BigNum("1") / result;
        else
            return result;
    }
    BigNum operator+=(const BigNum &x)
    {
        return *this = this->operator+(x);
    }
    BigNum operator-=(const BigNum &x)
    {
        return *this = this->operator-(x);
    }
    BigNum operator*=(const BigNum &x)
    {
        return *this = this->operator*(x);
    }
    BigNum operator/=(const BigNum &x) // 整除自除
    {
        return *this = BigNum(this->operator%(x).first);
    }
    BigNum operator%=(const BigNum &x) // 自模
    {
        return *this = this->operator%(x).second;
    }
    BigNum operator^=(const BigNum &x)
    {
        return *this = this->operator^(x);
    }
    // 输出
    string toString()
    {
        string result;
        if (this->isMinus)
            result = '-';
        this->integer.size() > 0 ? result += this->integer : result += '0';
        if (this->isDecZero() == false)
            result = result + "." + this->decimal;
        return result;
    }
};
map<string, BigNum> varLibrary; // 变量表
enum NodeType
{
    Unknown,
    OperAdd,
    OperSub,
    OperMul,
    OperDivI,
    OperDiv,
    OperMod,
    SelfMinus,
    FuncPow,
    FuncSqrt,
    FuncQuit,  // 退出
    FuncClear, // 清除所有变量并终止当前运算
    FuncFact,  // 阶乘
    Number,
};
struct ASTNode
{
private:
    NodeType type;
    BigNum *value;
    ASTNode *leftChild, *rightChild;

public:
    ASTNode()
    {
        this->type = Unknown;
        this->value = new BigNum("0");
        this->leftChild = nullptr;
        this->rightChild = nullptr;
    }
    ASTNode(NodeType type, BigNum *value, ASTNode *lc, ASTNode *rc)
    {
        this->type = type;
        this->value = value;
        this->leftChild = lc;
        this->rightChild = rc;
    }
    NodeType getType()
    {
        return this->type;
    }
    void setType(NodeType type)
    {
        this->type = type;
    }
    BigNum *getValue()
    {
        return this->value;
    }
    void setValue(BigNum value)
    {
        this->value = new BigNum(value);
    }
    ASTNode *getLeftChild()
    {
        return this->leftChild;
    }
    void setLeftChild(ASTNode *lc)
    {
        this->leftChild = lc;
    }
    ASTNode *getRightChild()
    {
        return this->rightChild;
    }
    void setRightChild(ASTNode *rc)
    {
        this->rightChild = rc;
    }
};
class Parser
{
private:
    enum TokenType
    {
        Error,
        Add,
        Sub,
        Mul,
        DivI,
        Div,
        Mod,
        Pow,
        Sqrt,
        Fact,
        Open,
        Comma,
        Close,
        Quit,
        Clear,
        Num,
        EOL,
    };
    struct Token
    {
        TokenType type;
        BigNum *value;
        Token()
        {
            this->type = Error;
            this->value = new BigNum("0");
        }
    };
    string::iterator crtPos;
    string scanStr;
    Token crtToken;
    ASTNode *root;
    ASTNode *expression()
    {
        ASTNode *node = this->term();
        ASTNode *nodeE = this->expressionE();
        return new ASTNode(OperAdd, nullptr, node, nodeE);
    }
    ASTNode *expressionE()
    {
        ASTNode *node = nullptr, *nodeE = nullptr;
        switch (this->crtToken.type)
        {
        case Add:
            this->getNextToken();
            node = this->term();
            nodeE = this->expressionE();
            return new ASTNode(OperAdd, nullptr, node, nodeE);
        case Sub:
            this->getNextToken();
            node = this->term();
            nodeE = this->expressionE();
            return new ASTNode(OperSub, nullptr, node, nodeE);
        default:
            return new ASTNode(Number, new BigNum("0"), node, nodeE);
        }
    }
    ASTNode *term()
    {
        ASTNode *nodeF = this->factor();
        ASTNode *nodeT = this->termT();
        return new ASTNode(OperMul, nullptr, nodeF, nodeT);
    }
    ASTNode *termT()
    {
        ASTNode *nodeT = nullptr, *nodeE = nullptr;
        switch (this->crtToken.type)
        {
        case Mul:
            this->getNextToken();
            nodeT = this->factor();
            nodeE = this->termT();
            return new ASTNode(OperMul, nullptr, nodeT, nodeE);
        case DivI:
            this->getNextToken();
            nodeT = this->factor();
            nodeE = this->termT();
            return new ASTNode(OperDivI, nullptr, nodeT, nodeE);
        case Div:
            this->getNextToken();
            nodeT = this->factor();
            nodeE = this->termT();
            return new ASTNode(OperDiv, nullptr, nodeT, nodeE);
        case Mod:
            this->getNextToken();
            nodeT = this->factor();
            nodeE = this->termT();
            return new ASTNode(OperMod, nullptr, nodeT, nodeE);
        default:
            return new ASTNode(Number, new BigNum("1"), nodeT, nodeE);
        }
    }
    ASTNode *factor()
    {
        ASTNode *node = nullptr, *nodeF = nullptr;
        BigNum *value;
        switch (this->crtToken.type)
        {
        case Open:
            this->getNextToken();
            node = this->expression();
            this->match(")");
            return node;
        case Sub:
            this->getNextToken();
            node = this->factor();
            return new ASTNode(SelfMinus, nullptr, node, nullptr);
        case Num:
            value = this->crtToken.value;
            this->getNextToken();
            return new ASTNode(Number, value, node, nullptr);
        case Sqrt:
            this->getNextToken();
            node = this->expression();
            this->match(")");
            return new ASTNode(FuncSqrt, nullptr, node, nullptr);
        case Fact:
            this->getNextToken();
            node = this->expression();
            this->match(")");
            return new ASTNode(FuncFact, nullptr, node, nullptr);
        case Pow:
            this->getNextToken();
            node = this->expression();
            this->match(",");
            nodeF = this->expression();
            this->match(")");
            return new ASTNode(FuncPow, nullptr, node, nodeF);
        case Quit:
            this->getNextToken();
            this->match(")");
            return new ASTNode(FuncQuit, nullptr, node, nullptr);
        case Clear:
            this->getNextToken();
            this->match(")");
            return new ASTNode(FuncClear, nullptr, node, nullptr);
        default:
            throw SCCError("Parse expression error.");
        }
    }
    inline void match(string obj)
    {
        int position = (this->crtPos - 1) - this->scanStr.begin();
        if (this->scanStr.find(obj, position) == position)
            this->getNextToken();
        else
            throw SCCError("The required symbol for the expression was not retrieved.");
    }
    inline void skipSpace()
    {
        while (*this->crtPos == ' ')
            ++this->crtPos;
    }
    inline void getNextToken()
    {
        this->skipSpace();
        this->crtToken.value = new BigNum("0");
        if (this->crtPos == this->scanStr.end())
        {
            this->crtToken.type = EOL;
            return;
        }
        if (isdigit(*this->crtPos))
        {
            this->crtToken.type = Num;
            this->crtToken.value = this->getNumber();
            return;
        }
        this->crtToken.type = Error;
        switch (*this->crtPos)
        {
        case '+':
            this->crtToken.type = Add;
            break;
        case '-':
            this->crtToken.type = Sub;
            break;
        case '*':
            this->crtToken.type = Mul;
            break;
        case '/':
            if (*(this->crtPos + 1) == '/')
            {
                this->crtToken.type = DivI;
                ++this->crtPos;
            }
            else
                this->crtToken.type = Div;
            break;
        case '%':
            this->crtToken.type = Mod;
            break;
        case '(':
            this->crtToken.type = Open;
            break;
        case ',':
            this->crtToken.type = Comma;
        case ')':
            this->crtToken.type = Close;
            break;
        case 'c':
            if (this->scanStr.substr(this->crtPos - this->scanStr.begin(), 6) == "clear(")
            {
                this->crtToken.type = Clear;
                this->crtPos += 5; // 下面还有+1，合计+6
            }
            break;
        case 's':
            if (this->scanStr.substr(this->crtPos - this->scanStr.begin(), 5) == "sqrt(")
            {
                this->crtToken.type = Sqrt;
                this->crtPos += 4; // 下面还有+1，合计+5
            }
            break;
        case 'f':
            if (this->scanStr.substr(this->crtPos - this->scanStr.begin(), 5) == "fact(")
            {
                this->crtToken.type = Fact;
                this->crtPos += 4; // 下面还有+1，合计+5
            }
            break;
        case 'q':
            if (this->scanStr.substr(this->crtPos - this->scanStr.begin(), 5) == "quit(")
            {
                this->crtToken.type = Quit;
                this->crtPos += 4; // 下面还有+1，合计+5
            }
            break;
        case 'p':
            if (this->scanStr.substr(this->crtPos - this->scanStr.begin(), 4) == "pow(")
            {
                this->crtToken.type = Pow;
                this->crtPos += 3; // 下面还有+1，合计+4
            }
            break;
        default:
            if ((*this->crtPos >= 'A') && (*this->crtPos <= 'Z'))
            {
                this->crtToken.type = Num;
                this->crtToken.value = this->getVarNum();
                return;
            }
            break;
        }
        if (this->crtToken.type != Error)
            ++this->crtPos;
        else
            throw SCCError("Symbols that cannot be resolved were detected.");
    }
    inline BigNum *getNumber()
    {
        this->skipSpace();
        int begin = this->crtPos - this->scanStr.begin();
        while (isdigit(*this->crtPos))
            ++this->crtPos;
        if (*this->crtPos == '.')
            ++this->crtPos;
        while (isdigit(*this->crtPos))
            ++this->crtPos;
        int end = this->crtPos - this->scanStr.begin();
        if (end - begin == 0)
            throw SCCError("Operational parameter missing.");
        return new BigNum(this->scanStr.substr(begin, end - begin));
    }
    inline BigNum *getVarNum()
    {
        this->skipSpace();
        int begin = this->crtPos - this->scanStr.begin();
        ++this->crtPos; // 隔过大写变量首字母
        while ((*this->crtPos >= 'a') && (*this->crtPos <= 'z'))
            ++this->crtPos;
        int end = this->crtPos - this->scanStr.begin();
        string varName = this->scanStr.substr(begin, end - begin);
        if (varLibrary.find(varName) == varLibrary.end())
            throw SCCError(string("Undefined variable name: " + varName));
        else
            return new BigNum(varLibrary[varName]);
    }
    BigNum calculate(ASTNode *node)
    {
        if (node == nullptr)
            throw SCCError("Execution statement error.");
        switch (node->getType())
        {
        case Number:
            return *(node->getValue());
        case SelfMinus:
            return BigNum("-1") * this->calculate(node->getLeftChild());
        case FuncSqrt:
            return (this->calculate(node->getLeftChild()) ^ BigNum("0.5"));
        case FuncFact:
        {
            BigNum ans = BigNum("1"), edge = this->calculate(node->getLeftChild());
            for (BigNum i = BigNum("1"); i <= edge; i += BigNum("1"))
                ans *= i;
            return ans;
        }
        case FuncPow:
            return (this->calculate(node->getLeftChild())) ^ (this->calculate(node->getRightChild()));
        case FuncQuit:
        {
            cout << "[Info] End process." << endl;
            exit(0);
        }
        case FuncClear:
        {
            varLibrary.clear();
            cout << "[Info] All stored variables have been cleared." << endl;
            throw SCCError("Terminating the calculation.");
        }
        case Unknown:
            throw SCCError("Execution statement error.");
        default:
            BigNum valX = this->calculate(node->getLeftChild());
            BigNum valY = this->calculate(node->getRightChild());
            switch (node->getType())
            {
            case OperAdd:
                return valX + valY;
            case OperSub:
                return valY - valX;
            case OperMul:
                if (node->getRightChild()->getType() == OperDivI)
                    return BigNum((valX % valY).first);
                else if (node->getRightChild()->getType() == OperMod)
                    return (valX % valY).second;
                else
                    return valX * valY;
            case OperDivI:
                return valX * valY;
            case OperDiv:
                return valY / valX;
            case OperMod:
                return valX * valY;
            default:
                throw SCCError("Illegal operator.");
            }
        }
        throw SCCError("Execution statement error.");
    }

public:
    Parser(string str) : root(nullptr)
    {
        this->scanStr = str;
        this->crtPos = this->scanStr.begin();
        this->crtToken = Token();
    }
    void analysis()
    {
        this->getNextToken();
        this->root = this->expression();
    }
    BigNum getResult()
    {
        return this->calculate(this->root);
    }
};
inline void assignment(string oper)
{
    string varName = oper.substr(0, oper.find_first_of("="));
    bool firstChr = true, fail = false;
    string var;
    for (char i : varName)
    {
        if (i == ' ')
            continue;
        if (i >= 'A' && i <= 'Z')
        {
            if (firstChr == true)
            {
                var += i;
                firstChr = false;
            }
            else
            {
                fail = true;
                break;
            }
        }
        else if (i >= 'a' && i <= 'z')
        {
            if (firstChr == false)
                var += i;
            else
            {
                fail = true;
                break;
            }
        }
        else
        {
            fail = true;
            break;
        }
    }
    if (fail == true)
    {
        cout << "[Error Detected] Invalid variable name." << endl;
        return;
    }
    Parser *scanner = new Parser(oper.substr(oper.find_first_of("=") + 1));
    BigNum newVal;
    try
    {
        scanner->analysis();
        newVal = scanner->getResult();
    }
    catch (SCCError &e)
    {
        cout << e.getMessage() << endl;
    }
    if (varLibrary.find(var) != varLibrary.end())
        cout << "[Info] Updated variable: " << var << ", the new value is: " << newVal.toString() << endl;
    else
        cout << "[Info] Updated variable: " << var << ", the value is: " << newVal.toString() << endl;
    varLibrary[var] = newVal;
}
int main()
{
    string input;
    Parser *scanner;
    ios::sync_with_stdio(false);
    while (true)
    {
        cout << ">>> ";
        getline(cin, input);
        if (input.find_first_of("=") != string::npos)
        {
            assignment(input);
            continue;
        }
        scanner = new Parser(input);
        string result;
        try
        {
            scanner->analysis();
            result = scanner->getResult().toString();
            cout << result << endl;
        }
        catch (SCCError &e)
        {
            cout << e.getMessage() << endl;
        }
        delete scanner;
    }
    return 0;
}