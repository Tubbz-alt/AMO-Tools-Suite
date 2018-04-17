/**
 * @file
 * @brief Contains the implementation of the flash tank calculator for steam systems.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "ssmt/FlashTank.h"

FlashTank::FlashTank(const double inletWaterPressure, const SteamProperties::ThermodynamicQuantity quantityType,
          const double quantityValue, const double inletWaterMassFlow, const double tankPressure)
		: inletWaterPressure(inletWaterPressure), quantityValue(quantityValue), inletWaterMassFlow(inletWaterMassFlow),
		  tankPressure(tankPressure), quantityType(quantityType)
{
	calculateProperties();
}

void FlashTank::calculateProperties() {
	// here do this
	auto sp =  SteamProperties(inletWaterPressure, quantityType, quantityValue).calculate();
	inletWaterProperties["massFlow"] = inletWaterMassFlow;
	inletWaterProperties["energyFlow"] = inletWaterMassFlow * inletWaterProperties.at("specificEnthalpy") / 1000;


    inletWaterProperties = SteamProperties(inletWaterPressure, quantityType, quantityValue).calculate();
	inletWaterProperties["massFlow"] = inletWaterMassFlow;
	inletWaterProperties["energyFlow"] = inletWaterMassFlow * inletWaterProperties.at("specificEnthalpy") / 1000;

//	if (quantityType == SteamProperties::ThermodynamicQuantity::QUALITY) inletWaterProperties["quality"] = quantityValue;
//	else inletWaterProperties["quality"] = 0;


	outletSaturatedProperties = SaturatedProperties(tankPressure, SaturatedTemperature(tankPressure).calculate()).calculate();
    outletSaturatedProperties["liquidMassFlow"] = inletWaterMassFlow
                                                  * (inletWaterProperties.at("specificEnthalpy")
                                                     - outletSaturatedProperties.at("gasSpecificEnthalpy"))
                                                  / (outletSaturatedProperties.at("liquidSpecificEnthalpy")
                                                     - outletSaturatedProperties.at("gasSpecificEnthalpy"));

    outletSaturatedProperties["gasMassFlow"] = inletWaterMassFlow - outletSaturatedProperties.at("liquidMassFlow");
	outletSaturatedProperties["gasQuality"] = 1;

    outletSaturatedProperties["gasEnergyFlow"] = outletSaturatedProperties.at("gasMassFlow")
                                                 * outletSaturatedProperties.at("gasSpecificEnthalpy") / 1000;

    outletSaturatedProperties["liquidEnergyFlow"] = outletSaturatedProperties.at("liquidMassFlow")
                                                    * outletSaturatedProperties.at("liquidSpecificEnthalpy") / 1000;
	outletSaturatedProperties["liquidQuality"] = 0;
}

double FlashTank::getInletWaterPressure() const { return inletWaterPressure; }

double FlashTank::getQuantityValue() const { return quantityValue; }

double FlashTank::getInletWaterMassFlow() const { return inletWaterMassFlow; }

double FlashTank::getTankPressure() const { return tankPressure; }

SteamProperties::ThermodynamicQuantity FlashTank::getQuantityType() const { return quantityType; }

void FlashTank::setInletWaterPressure(double inletWaterPressure) {
	this->inletWaterPressure = inletWaterPressure;
	calculateProperties();
}

void FlashTank::setQuantityValue(double quantityValue) {
	this->quantityValue = quantityValue;
	calculateProperties();
}

void FlashTank::setInletWaterMassFlow(double inletWaterMassFlow) {
	this->inletWaterMassFlow = inletWaterMassFlow;
	calculateProperties();
}

void FlashTank::setTankPressure(double tankPressure) {
	this->tankPressure = tankPressure;
	calculateProperties();
}

void FlashTank::setQuantityType(SteamProperties::ThermodynamicQuantity quantityType) {
	this->quantityType = quantityType;
	calculateProperties();
}
