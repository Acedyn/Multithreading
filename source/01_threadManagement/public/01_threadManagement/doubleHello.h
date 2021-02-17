#pragma once

namespace DoubleHello
{
    void helloFunction();

    class HelloClass
    {
    public:
        void operator()() const;
    };

    void doubleHello();
}
