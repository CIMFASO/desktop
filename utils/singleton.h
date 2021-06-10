#ifndef SINGLETON_H
#define SINGLETON_H

template <class T>
class Singleton {
    public:
    static T& Instance()  {
        static T _instance;
        return _instance;
    }
    private:  Singleton();
    ~Singleton();
    Singleton(const Singleton &);
    Singleton& operator=(const Singleton &);
};

#endif // SINGLETON_H
