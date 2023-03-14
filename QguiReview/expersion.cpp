#include "expersion.h"

ExPersion::ExPersion(QString name, QObject *parent) : QObject(parent)
{
     m_name = name;
}

int ExPersion::getAge(){
    return m_age;
}

void ExPersion::setAge(int age){
    m_age = age;
    emit ageChanged(m_age);
}

void ExPersion::incAge(){
    m_age ++;
    emit ageChanged(m_age);
}
