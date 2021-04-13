#pragma once
#include <string>


class SortClass
{
public:
    int key;
    float dmgModifier;
    char classOfForce;
    
    SortClass(int key, float dmgModifier, char classOfForce)
    {
        this->key = key;
        this->dmgModifier = dmgModifier;
        this->classOfForce = classOfForce;
    }
    bool operator< (const SortClass &right) const 
    {
        if(this->key == right.key)
        {
            if(this->dmgModifier == right.dmgModifier)
            {
                return this->classOfForce < right.classOfForce;
            } else return this->dmgModifier < right.dmgModifier;
        } else  return this->key < right.key;
    };
    bool operator> (const SortClass &right) const
    {
        if(this->key == right.key)
        {
            if(this->dmgModifier == right.dmgModifier)
            {
                return this->classOfForce > right.classOfForce;
            } else return this->dmgModifier > right.dmgModifier;
        } else  return this->key > right.key;
    };
    bool operator == (const  SortClass &right) const 
    {
        if(this->key == right.key && this->dmgModifier == right.dmgModifier && this->classOfForce == right.classOfForce) return true;
        else return false;
    };
    bool operator != (const SortClass &right) const 
    {
        if(this->key != right.key || this->dmgModifier != right.dmgModifier || this->classOfForce != right.classOfForce) return false;
        else return true;
    }

};

