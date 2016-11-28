/**
 * @brief Header file for OptimalPrePumpEff class
 *
 * This contains the prototypes of OptimalPrePumpEff calculator including getters and setters for the important fields.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
//
// Created by Mishra, Subhankar on 10/17/16.
//

#ifndef AMO_LIBRARY_OPTIMALPREPUMPEFF_H
#define AMO_LIBRARY_OPTIMALPREPUMPEFF_H

#include "../Pump.h"

class OptimalPrePumpEff {
public:
    OptimalPrePumpEff(Pump::Style style, double achievableEfficiency, double flowRate) :
            style_(style), achievableEfficiency_(achievableEfficiency), flowRate_(flowRate) {};

    double calculate();

private:
    double achievableEfficiency_;
    Pump::Style style_;
    double flowRate_;
    double pumpEfficiency = 0.0;
};


#endif //AMO_LIBRARY_OPTIMALPREPUMPEFF_H
