/**
 * @file
 * @brief Function prototypes for the PSAT and FSAT result fields
 *
 * This contains the prototypes for the PSAT & FSAT results structure
 * including getters and setters for the important fields. Primary
 * importance are methods for calculating the existing, modified and optimal results.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_LIBRARY_RESULTS_H
#define AMO_LIBRARY_RESULTS_H

#include <calculator/motor/MotorShaftPower.h>
#include "FieldData.h"
#include "InputData.h"


class FanResult {
public:
	struct FanInput {
        FanInput(double const fanSpeed, const Motor::Drive drive, const int stages): fanSpeed(fanSpeed), drive(drive)
//                stages(stages)
        {}

        // TODO FanType enum of fan types
        double fanSpeed; // rpm used here?
        Motor::Drive drive;
//        int stages;
    };

	struct FanFieldData {
        FanFieldData(const double measuredPower, const double measuredVoltage, const double measuredAmps, const double flowRate,
                     const double inletPressure, const double outletPressure, const double compressibilityFactor,
                     FieldData::LoadEstimationMethod loadEstimationMethod)
                : measuredPower(measuredPower), measuredVoltage(measuredVoltage), measuredAmps(measuredAmps), flowRate(flowRate),
                  inletPressure(inletPressure), outletPressure(outletPressure), compressibilityFactor(compressibilityFactor),
                  loadEstimationMethod(loadEstimationMethod)
        {}

		double measuredPower, measuredVoltage, measuredAmps;
        double flowRate, inletPressure, outletPressure, compressibilityFactor;

        FieldData::LoadEstimationMethod loadEstimationMethod;

    };

    struct Output {
        Output(const double fanEfficiency, const double motorRatedPower, const double motorShaftPower, const double fanShaftPower,
               const double motorEfficiency, const double motorPowerFactor, const double motorCurrent, const double motorPower,
               const double annualEnergy, const double annualCost, const double estimatedFLA)
                : fanEfficiency(fanEfficiency), motorRatedPower(motorRatedPower), motorShaftPower(motorShaftPower),
                  fanShaftPower(fanShaftPower), motorEfficiency(motorEfficiency), motorPowerFactor(motorPowerFactor),
                  motorCurrent(motorCurrent), motorPower(motorPower), annualEnergy(annualEnergy), annualCost(annualCost),
                  estimatedFLA(estimatedFLA)
        {}

        Output(const MotorShaftPower::Output output, const double fanEfficiency, const double motorRatedPower,
               const double fanShaftPower, const double annualEnergy, const double annualCost, const double estimatedFLA)
                : fanEfficiency(fanEfficiency), motorRatedPower(motorRatedPower), motorShaftPower(output.shaftPower),
                  fanShaftPower(fanShaftPower), motorEfficiency(output.efficiency), motorPowerFactor(output.powerFactor),
                  motorCurrent(output.current), motorPower(output.power), annualEnergy(annualEnergy), annualCost(annualCost),
                  estimatedFLA(estimatedFLA)
        {}

        const double fanEfficiency, motorRatedPower, motorShaftPower, fanShaftPower, motorEfficiency, motorPowerFactor, motorCurrent;
        const double motorPower, annualEnergy, annualCost, estimatedFLA;
    };

    FanResult(FanInput & fanInput, Motor & motor, FanFieldData & fanFieldData, double baselineFanEfficiency,
              double operatingFraction, double unitCost)
            : fanInput(fanInput), motor(motor), fanFieldData(fanFieldData), operatingFraction(operatingFraction),
              unitCost(unitCost), baselineFanEfficiency(baselineFanEfficiency)
    {}

    Output calculateExisting();


private:
    double annualSavingsPotential = 0;
    double optimizationRating = 0;
    // In values
    FanInput fanInput;
    Motor motor;
    FanFieldData fanFieldData;
    double operatingFraction, unitCost;
    double baselineFanEfficiency = 0;
};

/**
 * PSAT Result class
 * Contains all of the final results of the pump calculations.
 * Used to calculate the existing efficiency of the pump and the optimal efficiency of the pump so they can be compared.
 */
class PSATResult {
public:
    /**
     * Constructor
     * @param pump Pump, contains all pump-related calculations, passed by reference
     * @param motor Motor, contains all motor-related calculations, passed by reference
     * @param fieldData FieldData, contains all field data-related calculations, passed by reference
     * @param operatingFraction double, fraction(%) of calendar hours the equipment is operating
     * @param unitCost double, per unit energy cost of electricity in $/kwh
     */
    PSATResult(
        Pump &pump,
        Motor &motor,
        FieldData &fieldData,
        double operatingFraction,
        double unitCost
    ) :
        pump(pump),
        motor(motor),
        fieldData(fieldData),
        operatingFraction(operatingFraction),
        unitCost(unitCost),
        baselinePumpEfficiency(0.0)
    {};

    /**
     * Constructor
     * @param pump Pump, contains all pump-related calculations, passed by reference
     * @param motor Motor, contains all motor-related calculations, passed by reference
     * @param fieldData FieldData, contains all field data-related calculations, passed by reference
     * @param baselinePumpEfficiency double, baseline pump efficiency
     * @param operatingFraction double, fraction(%) of calendar hours the equipment is operating
     * @param unitCost double, per unit energy cost of electricity in $/kwh
     */
    PSATResult(
            Pump &pump,
            Motor &motor,
            FieldData &fieldData,
            double baselinePumpEfficiency,
            double operatingFraction,
            double unitCost
    ) :
            pump(pump),
            motor(motor),
            fieldData(fieldData),
            operatingFraction(operatingFraction),
            unitCost(unitCost),
            baselinePumpEfficiency(baselinePumpEfficiency)
    {};

    /**
     * Result structure captures the same fields for the existing as well as the optimal condition.
     */
    struct result {
        double pumpEfficiency;     ///< Existing: Existing pump efficiency is fluid power added by the pump divided by pump input shaft power.
        ///< Optimal: Optimal pump efficiency is estimated based on the efficiency estimating algorithms contained in Hydraulic Institute Standard HI 1.3-2000, Centrifugal Pump Design and Application.
        double motorRatedPower;    ///< Existing: Existing motor nameplate power (same as Rated power in the Motor input section).
        ///< Optimal: This is the nameplate motor rated power for an optimally sized pump.
        double motorShaftPower;    ///< Existing: This is the estimated motor shaft power for the existing motor. The estimate is based on measured electrical data and PSAT's efficiency estimate for the specified motor size, speed, and class.
        ///< Optimal: This is the motor shaft power requirements for the optimal pump, based on the specified flow rate, head, and specific gravity values, along with the HI 1.3 achievable efficiency algorithms. If a belt drive is specified, associated losses are added to the pump shaft power to determine required motor power. For direct-driven pumps, the pump and motor shaft powers are the same.
        double pumpShaftPower;     ///< Existing: This is the estimated pump shaft power for the existing motor. The estimate is the same as the motor shaft power (above) for direct-driven applications. For belt-driven applications, belt losses are deducted from the motor shaft power to determine pump shaft power.
        ///< Optimal: This is the shaft power requirements for the optimal pump, based on the specified flow rate, head, and specific gravity values, along with the HI 1.3 achievable efficiency algorithms.
        double motorEfficiency;    ///< Existing: This is the estimated efficiency of the existing motor at the existing load.
        ///< Optimal: This is the estimated efficiency for an energy-efficient motor of the size indicated in the optimal motor rated power entry above when operating at the optimal motor shaft power.
        double motorPowerFactor;   ///< Existing: This is the estimated power factor for the existing motor at the existing load. It is based on the measured electrical data and the motor performance characteristic curves for the specified motor.
        ///< Optimal: This is the estimated power factor for an energy-efficient motor of the size indicated in the optimal motor rated power entry above when operating at the optimal motor shaft power (also indicated above).
        double motorCurrent;       ///< Existing: This is the estimated or measured current for the existing motor at the existing load.
        ///< Optimal: This is the estimated current for an energy-efficient motor of the size indicated in the optimal motor rated power entry above when operating at the optimal motor shaft power.
        double motorPower;         ///< Existing: This is the estimated or measured electric power for the existing motor at the existing load.
        ///< Optimal: The estimated electric power for an energy-efficient motor of the size indicated in the optimal motor rated power entry above when operating at the optimal motor shaft power.
        double annualEnergy;       ///< Existing: This is the annual energy consumption at the measured/estimated power level for the existing equipment when operated for the fraction of time indicated by the operating fraction.
        ///< Optimal: The annual energy consumption for an optimized pump driven by an energy-efficient motor, based on the estimated motor power and on the fraction of time the pump is operated indicated by the operating fraction.
        double annualCost;         ///< Existing: This is the existing annual energy cost based on the product of the existing annual energy consumption and the unit operating cost (cents/kwhr) input.
        ///< Optimal: This is the annual energy cost based on the product of the optimal annual energy consumption and the unit operating cost (cents/kwhr) input.
        double estimatedFLA;       ///< Existing: The full load amps are either specified (known) or estimated. This field will hold either one. The estimated full load amps are calculated from the motor voltage, hp, and speed.
    };

    /**
     * Gets the annual savings potential
     * @return double, annual savings potential in $/year
     */
    double getAnnualSavingsPotential() const {
        return annualSavingsPotential;
    }

    /**
     * Gets the optimization rating
     * @return double, optimization rating as %
     */
    double getOptimizationRating() const {
        return optimizationRating;
    }

    /**
     * Gets the existing conditions
     * @return const result, existing conditions
     */
    const result &getExisting() const {
        return existing;
    }

    /**
     * Gets the modified conditions
     * @return const result, modified conditions
     */
    const result &getModified() const {
        return modified;
    }

    /**
     * Gets the optimal conditions
     * @return const result, optimal conditions
     */
    const result &getOptimal() const {
        return optimal;
    }

    /**
     * Calculates existing conditions
     */
    void calculateExisting();

    /**
     * Calculates modified conditions
     */
    void calculateModified();

    /**
     * Calculates optimal conditions
     */
    void calculateOptimal();

private:
    // Out values
    result existing, optimal, modified;
    double annualSavingsPotential = 0.0;
    double optimizationRating = 0.0;
    // In values
    Pump pump;
    Motor motor;
    FieldData fieldData;
    double operatingFraction, unitCost;
    double baselinePumpEfficiency;
};


#endif //AMO_LIBRARY_RESULTS_H
