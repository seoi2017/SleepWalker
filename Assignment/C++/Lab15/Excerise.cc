/*
Environment: C++17
Course: SUSTech_C++
Problem ID: Lab15_Excerise
*/
#include <bits/stdc++.h>
using namespace std;

class Remote;

class Tv
{
    friend class Remote;
private:
    int volume, channel;
    bool isOn;
public:
    Tv() : volume(0), channel(0), isOn(false) {}
    void turnOn();
    void turnOff();
    void toggleRemote(Remote &remote);
    void display();
};

class Remote
{
    friend class Tv;
private:
    int state;
public:
    Remote() : state(0) {}
    void display();
    void setVolume(Tv &tv, const int& volume);
    void setChannel(Tv &tv, const int& channel);
};

void Tv::turnOn()
{
    this->isOn = true;
}

void Tv::turnOff()
{
    this->isOn = false;
}

void Tv::toggleRemote(Remote &remote)
{
    if (this->isOn == false)
    {
        cout << "Warning: The TV is off." << endl;
        return;
    }
    remote.state = (remote.state == 0 ? 1 : 0);
}

void Tv::display()
{
    cout << "Tv is " << (this->isOn ? "on" : "off") << endl;
    cout << "Volume is " << this->volume << endl;
    cout << "Channel is " << this->channel << endl;
}

void Remote::display()
{
    cout << "The state of Remote is ";
    switch (this->state)
    {
    case 0:
        cout << "Normal" << endl;
        break;
    case 1:
        cout << "Interactive" << endl;
        break;
    default:
        cout << "Unknown" << endl;
        break;
    }
}

void Remote::setVolume(Tv &tv, const int& volume)
{
    if (tv.isOn == false)
    {
        cout << "Warning: The TV is off." << endl;
        return;
    }
    tv.volume = volume;
}

void Remote::setChannel(Tv &tv, const int& channel)
{
    if (tv.isOn == false)
    {
        cout << "Warning: The TV is off." << endl;
        return;
    }
    tv.channel = channel;
}

int main()
{
    Remote remote;
    Tv tv;
    
    tv.display();
    remote.display();

    remote.setChannel(tv, 3);
    tv.toggleRemote(remote);

    tv.turnOn();

    tv.toggleRemote(remote);
    remote.setChannel(tv, 3);
    remote.setVolume(tv, 5);

    tv.display();
    remote.display();

    return 0;
}