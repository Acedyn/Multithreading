#pragma once

namespace ActorModel
{
    class Restaurant;

    class Waiter
    {
    public:
        Waiter(Restaurant* _restaurant);
        
        void operator()();
        
    private:
        void takeOrder();

        Restaurant* restaurant;
        bool isWorking;
    };
}
