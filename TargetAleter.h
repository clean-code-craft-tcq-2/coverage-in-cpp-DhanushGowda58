#ifndef COVERAGE_IN_CPP_Dhanush_TARGETALETER_H
#define COVERAGE_IN_CPP_Dhanush_TARGETALETER_H

#include "BreachTypeAlert.h"
#include "typewise-alert.h"

class ITargetAlert{
public:
    virtual AlertNecessity sendToTarget(BreachType breachType) = 0;
};

class TargetAlert{
    ITargetAlert *targetAlert;
public:
    TargetAlert(ITargetAlert *targetAlert1): targetAlert(targetAlert1){}
    ~TargetAlert(){
        delete targetAlert;
    }

    AlertStatus alertTheTarget(BreachType breachType){
        if (targetAlert->sendToTarget(breachType) == ALERT_NOT_REQUIRED)
            return ALERT_NOT_SENT;
        return ALERT_SENT;
    }
};

class ControllerAlert: public ITargetAlert{
public:
    AlertNecessity sendToTarget(BreachType breachType){
        const unsigned short header = 0xfeed;
        std::cout<< header << ", " << breachType << std::endl;
        return ALERT_NOT_REQUIRED;
    }
};

class EmailAlert:public ITargetAlert{
public:
    AlertNecessity sendToTarget(BreachType breachType){
        std::string recipient = "a.b@c.com";
        BreachAlert *alert;
        if (breachType == TOO_LOW) {
            alert = new BreachAlert(new LowBreachType);
            alert->outputAlert(recipient);
            return ALERT_REQUIRED;
        }
        if(breachType == TOO_HIGH){
            alert = new BreachAlert(new HighBreachType);
            alert->outputAlert(recipient);
            return ALERT_REQUIRED;
        }
//        alert = new BreachAlert(new NormalBreachType);
//        alert->outputAlert(recipient);
        return ALERT_NOT_REQUIRED;
    }
};

#endif
