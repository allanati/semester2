#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Device {
public:
    virtual void poll() = 0;
    virtual ~Device() {};
};

class ElectricityCounter : public Device {
public:
    void poll() override {
        std::cout << "Electricity Counter: " << name << std::endl;
    }

    void setName(const std::string& name) {
        this->name = name;
    }

private:
    std::string name;
};

class InputBlock : public Device {
private:
    std::string name;

public:
    void poll() override {
        std::cout << "Input Block: " << name << std::endl;
    }

    void setName(const std::string& name) {
        this->name = name;
    }

    ~InputBlock() override {};
};

class HeatingControl : public Device {
private:
    std::string name;

public:
    void poll() override {
        std::cout << "Heating Control: " << name << std::endl;
    }

    void setName(const std::string& name) {
        this->name = name;
    }

    ~HeatingControl() override {};
};

int main() {
    setlocale(LC_ALL, "ru");

    std::ifstream inputFile; // Файл с названиями приборов
    inputFile.open("devices.txt");

    std::vector<Device*> devices;

    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            continue; // Пропускаем пустые строки
        }

        if (line == "Electricity counters") {
            ElectricityCounter* counter = new ElectricityCounter();
            std::getline(inputFile, line);
            counter->setName(line);
            devices.push_back(counter);
        }
        else if (line == "Input blocks") {
            InputBlock* inputBlock = new InputBlock();
            std::getline(inputFile, line);
            inputBlock->setName(line);
            devices.push_back(inputBlock);
        }
        else if (line == "Heating controllers") {
            HeatingControl* heatingControl = new HeatingControl();
            std::getline(inputFile, line);
            heatingControl->setName(line);
            devices.push_back(heatingControl);
        }
        else {
            std::cout << "Unrecognised line" << line << std::endl;
        }
    }

    inputFile.close();

    // Вызываем метод poll для каждого прибора
    for (Device* device : devices) {
        device->poll();
    }

    // Освобождаем память
    for (Device* device : devices) {
         delete device;
    }

    return 0;
}