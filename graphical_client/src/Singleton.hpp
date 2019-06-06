/*
** EPITECH PROJECT, 2019
** bomberman
** File description:
** Created by abel,
*/

#pragma once

template <class T>
class SingleTon {
public:
    static T &getInstance()
    {
        if (SingleTon<T>::instance == nullptr) {
            SingleTon<T>::instance = new T();
        }
        return *SingleTon<T>::instance;
    };
private:
    static T *instance;
};

template <class T>
T *SingleTon<T>::instance = nullptr;
