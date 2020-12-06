/*
Environment: C++17
Course: SUSTech_C++
Problem ID: Lab11_Excerise1
*/
#include <bits/stdc++.h>
using namespace std;
class Stock
{
private:
    const char* defaultName = "No name";
    char *company;
    long shares;
    double share_val;
    double total_val;
    void set_tot()
    {
        this->total_val = this->shares * this->share_val;
    }
public:
    Stock() : shares(0), total_val(0), share_val(0)
    {
        this->company = new char[strlen(this->defaultName)];
        memcpy(this->company, this->defaultName, sizeof(this->defaultName));
    }
    Stock(const char* name, const long& shares, const double& share_val) : shares(shares), share_val(share_val)
    {
        this->company = new char[strlen(name)];
        memcpy(this->company, name, sizeof(name));
        this->set_tot();
    }
    ~Stock()
    {
        delete this->company;
    }
    void buy(const long& num, const double& price)
    {
        // Useless
    }
    void sell(const long& num, const double& price)
    {
        // Useless
    }
    void update(const double& price)
    {
        // Useless
    }
    friend ostream& operator<<(ostream& os, const Stock& stock);
};

ostream& operator<<(ostream& os, const Stock& stock)
{
    os << "Company name: " << stock.company << endl;
    os << "Shares: " << stock.shares << endl;
    os << "Value of shares: " << stock.share_val << endl;
    os << "Total value: " << stock.total_val << endl;
    return os;
}

int main()
{
    Stock _1;
    Stock _2("Something", 1, 1.0);
    Stock *_3 = new Stock;
    Stock *_4 = new Stock("Nothing", 2, 2.0);
    cout << _1 << _2 << *_3 << *_4 << endl;
    delete _3, _4;
    return 0;
}