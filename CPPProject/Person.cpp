//
// Created by 86173 on 2023/7/18.
//

#include "Person.h"

int Person::getAge() const {
    return age;
}

const std::string &Person::getName() const {
    return name;
}

void Person::setAge(int age) {
    Person::age = age;
}

void Person::setName(const std::string &name) {
    Person::name = name;
}

void Person::write() {
    std::cout << "I am writing...";
}

Person::Person(int age, std::string name, Cat cat) {
    setAge(age);
    setName(name);
    setCat(cat);
}

void Person::setCat(const Cat &cat) {
    Person::cat = cat;
}

Cat  Person::getCat() const {
    return cat;
}
