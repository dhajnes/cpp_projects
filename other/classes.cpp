#include  <string>
#include <iostream>
#include <vector>

class Car {
    public:
        int maxSpeed;
        bool tuned;
        float height;
        std::string engineSound;

        void revEngine(){
            std::cout << engineSound + engineSound;
            if (tuned == true){
                std::cout << "StuTuTuTu";
            }
            std::cout << "\n";
        }
    
};

int main(){
Car corolla;
corolla.maxSpeed = 190;
corolla.tuned = false;
corolla.height = 0.25;
corolla.engineSound = "Brm";

Car miata;
miata.maxSpeed = 230;
miata.height = 0.10;
miata.tuned = true;
miata.engineSound = "Braaap";

corolla.revEngine();
miata.revEngine();


}