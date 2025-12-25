#include<iostream>
using namespace std;
class Target {
public:
    virtual~Target() = default;
    virtual void Request() const = 0;
};
class Adaptee {
public:
    void specificRequest() const
    {
        cout << "Adaptee SpecificRequest\n ";
    }
};
class Adapter :public Target {
private:
    Adaptee* adaptee;
public:
    Adapter(Adaptee* a) :adaptee(a) {}
    void Request() const override {
        cout << "Adapter: Translating Request() → SpecificRequest().\n";
        adaptee->specificRequest();
    }
};
void Clientcode(Target* target)
{
    target->Request();
}
int main()
{
    Adaptee* adaptee = new Adaptee();
    Target* adapter = new Adapter(adaptee);
    cout << "Client: I only understand Target interface:\n";
    Clientcode(adapter);


    delete adaptee;
    delete adapter;
    return 0;
}
