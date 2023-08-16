//
// Created by 86173 on 2023/7/18.
//

#ifndef CPPPROJECT_PERSON_H
#define CPPPROJECT_PERSON_H

#include<iostream>
#include "Cat.h"

class Person{
public:
    Person(int age, std::string name, Cat cat);

    void setCat(const Cat &cat);

    Cat cat;

    int getAge() const;

    const std::string &getName() const;

    void setAge(int age);

    void setName(const std::string &name);

    void write();

    Cat  getCat() const;

private:
    int age;
    std::string name;
};
#endif //CPPPROJECT_PERSON_H
