/**
 * ---------------------------------------------------------------------------------------
 * Author  : Kunal K.
 * Title   : Observer design pattern
 * Purpose : To demonstrate the concepts of design patterns
 * Version : 1.0
 * ---------------------------------------------------------------------------------------
**/

#include <cstddef>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

// observer interface
struct IObserver {
    virtual void notify() const = 0;
    virtual ~IObserver() = default;
};

// concrete observer
class Observer : public IObserver {
    std::size_t _ID;

  public:
    explicit Observer(std::size_t ID) : _ID{ID} {}
    void notify() const override {
        std::cout << "\tObserver " << _ID << " notified!\n";
    }
    std::size_t ID() const { return _ID; }
};

// subject interface
struct ISubject {
    virtual void registerObserver(std::shared_ptr<Observer> spo) = 0;
    virtual void unregisterObserver(std::shared_ptr<Observer> spo) = 0;
    virtual void notifyObservers() const = 0;
    virtual ~ISubject() = default;
};

// concrete subject
class Subject : public ISubject {
    std::map<std::size_t, std::shared_ptr<Observer>> _observers{};

  public:
    void registerObserver(std::shared_ptr<Observer> spo) override {
        _observers[spo->ID()] = spo;
    }
    void unregisterObserver(std::shared_ptr<Observer> spo) override {
        _observers.erase(spo->ID());
    }
    void notifyObservers() const override {
        for (auto& elem : _observers)
            elem.second->notify();
    }
};

int main() {
    // 1 subject
    Subject subject;

    // N observers
    std::size_t N = 4;
    std::vector<std::shared_ptr<Observer>> vobs;
    for (std::size_t i = 0; i < N; ++i)
        vobs.push_back(std::make_shared<Observer>(i));

    // register all of them
    std::cout << "Registering all " << N << " Observers...\n";
    for (std::size_t i = 0; i < vobs.size(); ++i)
        subject.registerObserver(vobs[i]);

    // notify
    std::cout << "Notifying all " << N << " Observers...\n";
    subject.notifyObservers();

    // un-register Observers 1 and 2
    std::cout << "Un-registering Observer 1 and Observer 2...\n";
    subject.unregisterObserver(vobs[1]);
    subject.unregisterObserver(vobs[2]);

    // notify
    std::cout << "Notifying remaining Observers:\n";
    subject.notifyObservers();
}
