//
// Created by Andrei on 03.09.2023.
//

#ifndef APP1_OBSERVERAUTH_H
#define APP1_OBSERVERAUTH_H

#include <string>

class ObserverAuth {
public:
    virtual void update(const std::string& option, const std::string& option2)=0;
};


#endif //APP1_OBSERVERAUTH_H
