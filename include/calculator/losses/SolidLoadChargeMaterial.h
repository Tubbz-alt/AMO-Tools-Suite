/**
 * @file
 * @brief Calculator for total heat of solid load/charge material
 *
 * This contains the inputs for calculating a solid load/charge material's
 * total heat.
 *
 * @author Mark Adams
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */


#ifndef AMO_SUITE_SOLIDLOADCHARGEMATERIAL_H
#define AMO_SUITE_SOLIDLOADCHARGEMATERIAL_H

#include <string>
#include "LoadChargeMaterial.h"

/** Latent heat of evaporation for water is 970 Btu/lb */
#define WATER_EVAPORATION 970.0

/** Heat required temperature is 212.0°F */
#define HEAT_REQUIRED_TEMP 212.0

/**
 * Solid Load Charge Material class
 * Contains all of the properties of a solid load charge material
 * Used to calculate the heat required for a solid load charge material to tbe heated from the inlet temperature to the outlet temperature
 */
class SolidLoadChargeMaterial {
public:

    /**
 * Constructor for the solid load/charge material with all inputs specified.
 * @param thermicReactionType LoadChargeMaterial::ThermicReactionType, Enumerated value for either endothermic or exothermic reactions
 * @param specificHeatSolid double, Average specific heat of the solid material (dry) in Btu/(lb*°F)
 * @param latentHeat double, Latent heat of fusion in Btu/(lb)
 * @param specificHeatLiquid double, Specific heat of liquid from molten material in Btu/(lb*°F)
 * @param meltingPoint double, The melting point of the material in °F
 * @param chargeFeedRate double, Charge (wet)-feed rate in lb/hr
 * @param waterContentCharged double, Water content as charged (%)
 * @param waterContentDischarged double, Water content as discharged (%)
 * @param initialTemperature double, Initial temperature in °F
 * @param dischargeTemperature double, Charge material discharge temperature in °F
 * @param waterVaporDischargeTemperature double, Water vapor discharge temperature in °F
 * @param chargeMelted double, Charge melted (% of dry charge)
 * @param chargeReacted double, Charge Reacted (% of dry charge) in %
 * @param reactionHeat double, Heat of reaction in Btu/lb
 * @param additionalHeat double, Additional heat required in Btu/h
 * */
    SolidLoadChargeMaterial(
            LoadChargeMaterial::ThermicReactionType thermicReactionType,
            double specificHeatSolid,
            double latentHeat,
            double specificHeatLiquid,
            double meltingPoint,
            double chargeFeedRate,
            double waterContentCharged,
            double waterContentDischarged,
            double initialTemperature,
            double dischargeTemperature,
            double waterVaporDischargeTemperature,
            double chargeMelted,
            double chargeReacted,
            double reactionHeat,
            double additionalHeat
    ) : thermicReactionType (thermicReactionType),
        specificHeatSolid(specificHeatSolid),
        latentHeat(latentHeat),
        specificHeatLiquid(specificHeatLiquid),
        meltingPoint(meltingPoint),
        chargeFeedRate(chargeFeedRate),
        waterContentCharged(waterContentCharged / 100.0),
        waterContentDischarged(waterContentDischarged / 100.0),
        initialTemperature(initialTemperature),
        dischargeTemperature(dischargeTemperature),
        waterVaporDischargeTemperature(waterVaporDischargeTemperature),
        chargeMelted(chargeMelted / 100.0),
        chargeReacted(chargeReacted / 100.0),
        reactionHeat(reactionHeat),
        additionalHeat(additionalHeat)
    {}

    SolidLoadChargeMaterial() = default;

    /**
     * Gets the thermic reaction type
     * @return LoadChargeMaterial::ThermicReactionType classification of thermic reaction type
     */
    LoadChargeMaterial::ThermicReactionType getThermicReactionType() const {
        return thermicReactionType;
    }

    /**
     * Sets the thermic reaction type
     * @param thermicReactionType Enumerated value for either endothermic or exothermic reactions
     */
    void setThermicReactionType(LoadChargeMaterial::ThermicReactionType thermicReactionType) {
        this->thermicReactionType = thermicReactionType;
    }

    /**
     * Gets the average specific heat of the solid material(dry)
     * @return double, average specific heat of solid material (dry) in btu/(lb*°F)
     */
    double getSpecificHeatSolid() const {
        return specificHeatSolid;
    }

    /**
     * Sets the average specific heat of the solid material (dry)
     * @param specificHeatSolid double, average specific heat of the solid material (dry) in btu/(lb*°F)
     */
    void setSpecificHeatSolid(double specificHeatSolid) {
        this->specificHeatSolid = specificHeatSolid;
    }

    /**
     * Gets the latent heat of fusion
     * @return double, latent heat of fusion in btu/lb
     */
    double getLatentHeat() const {
        return latentHeat;
    }

    /**
     * Sets the latent heat of fusion
     * @param latentHeat double, latent heat of fusion in btu/lb
     */
    void setLatentHeat(double latentHeat) {
        this->latentHeat = latentHeat;
    }

    /**
     * Gets the specific heat of liquid from molten material
     * @return double, specific heat of liquid from molten material in btu/(lb*°F)
     */
    double getSpecificHeatLiquid() const {
        return specificHeatLiquid;
    }

    /**
     * Sets the specific heat of liquid from molten material
     * @param specificHeatLiquid double, specific heat of liquid from molten material in btu/(lb*°F)
     */
    void setSpecificHeatLiquid(double specificHeatLiquid) {
        this->specificHeatLiquid = specificHeatLiquid;
    }

    /**
     * Gets the melthing point of the material
     * @return double, melting point of material in °F
     */
    double getMeltingPoint() const {
        return meltingPoint;
    }

    /**
     * Gets the ID of material
     * @return double, ID number of material
     */
    double getID() const {
        return this->id;
    }

    /**
     * Sets the ID of a material
     * @param id int, ID of the material
     */
    void setID(const int id) {
        this->id = id;
    }

    /**
     * Sets the melting point of the material
     * @param meltingPoint double, melthing point of material in °F
     */
    void setMeltingPoint(double meltingPoint) {
        this->meltingPoint = meltingPoint;
    }

    /**
     * Gets the charge (wet)-feed rate
     * @return double, charge (wet)-feed rate in lb/hr
     */
    double getChargeFeedRate() const {
        return chargeFeedRate;
    }

    /**
     * Sets the charge (wet)-feed rate
     * @param chargeFeedRate double, charge (wet)-feed rate in lb/hr
     */
    void setChargeFeedRate(double chargeFeedRate) {
        this->chargeFeedRate = chargeFeedRate;
    }

    /**
     * Gets the water content as charged (%)
     * @return double, % of water content charged
     */
    double getWaterContentCharged() const {
        return waterContentCharged * 100.0;
    }

    /**
     * Sets the water content as charged (%)
     * @param waterContentCharged double, % of water content charged
     * @return nothing
     */
    void setWaterContentCharged(double waterContentCharged) {
        this->waterContentCharged = waterContentCharged / 100.0;
    }

    /**
     * Gets the water content as discharged (%)
     * @return double, % of water content discharged
     */
    double getWaterContentDischarged() const {
        return waterContentDischarged * 100.0;
    }

    /**
     * Sets the water content as discharged (%)
     * @param waterContentDischarged double, % of water content discharged
     */
    void setWaterContentDischarged(double waterContentDischarged) {
        this->waterContentDischarged = waterContentDischarged / 100.0;
    }

    /**
     * Gets the initial temperature
     * @return double, initial temperature in °F
     */
    double getInitialTemperature() const {
        return initialTemperature;
    }

    /**
     * Sets the initial temperature
     * @param initialTemperature double, initial temperature in °F
     */
    void setInitialTemperature(double initialTemperature) {
        this->initialTemperature = initialTemperature;
    }

    /**
     * Gets the charge material discharge temperature
     * @return double, charge material discharge temperature in °F
     */
    double getDischargeTemperature() const {
        return dischargeTemperature;
    }

    /**
     * Sets the charge material discharge temperature
     * @param dischargeTemperature double, charge material discharge temperature in °F
     * @return nothing
     */
    void setDischargeTemperature(double dischargeTemperature) {
        	this->dischargeTemperature = dischargeTemperature;
    }

    /**
     * Gets the water vapor discharge temperature
     * @return double, water vapor discharge temperature in °F
     */
    double getWaterVaporDischargeTemperature() const {
        return waterVaporDischargeTemperature;
    }

    /**
     * Sets the water vapor discharge temperature
     * @param waterVaporDischargeTemperature double, water vapor discharge temperature in °F
     */
    void setWaterVaporDischargeTemperature(double waterVaporDischargeTemperature) {
        this->waterVaporDischargeTemperature = waterVaporDischargeTemperature;
    }

    /**
     * Gets the charge melted (% of dry charge)
     * @return double, charge melted (% of dry charge)
     */
    double getChargeMelted() const {
        return chargeMelted * 100.0;
    }

    /**
     * Sets the charge melted (% of dry charge)
     * @param chargeMelted double, charge melted (% of dry charge)
     */
    void setChargeMelted(double chargeMelted) {
        this->chargeMelted = chargeMelted / 100.0;
    }

    /**
     * Gets the charge reacted
     * @return double, charge reacted (% of dry charge)
     */
    double getChargedReacted() const {
        return chargeReacted * 100.0;
    }

    /**
     * Sets the charged reacted
     * @param chargedReacted double, charge reacted (% of dry charge)
     */
    void setChargedReacted(double chargedReacted) {
        this->chargeReacted = chargedReacted / 100.0;
    }

    /**
     * Gets the reaction heat
     * @return double, reaction heat in btu/lb
     */
    double getReactionHeat() const {
        return reactionHeat;
    }

    /**
     * Sets the reaction heat
     * @param reactionHeat double, reaction heat in btu/lb
     */
    void setReactionHeat(double reactionHeat) {
        this->reactionHeat = reactionHeat;
    }

    /**
     * Gets the additional heat required
     * @return double, additional heat required in btu/hr
     */
    double getAdditionalHeat() const {
        return additionalHeat;
    }

    /**
     * Sets the additional heat required
     * @param additionalHeat double, additional heat required in btu/hr
     */
    void setAdditionalHeat(double additionalHeat) {
        this->additionalHeat = additionalHeat;
    }

    /**
     * Gets the substance
     * @return string, name of substance
     */
    std::string getSubstance() const {
        return substance;
    }

    /**
     * Sets the substance
     * @param substance string, name of substance
     */
    void setSubstance(std::string const & substance) {
        this->substance = substance;
    }

    /**
     * Sets the total heat required
     * @param totalHeat double, total heat required in btu/hr
     */
    void setTotalHeat(double totalHeat) {
        this->totalHeat = totalHeat;
    }


    /**
     * bool operator
     */
    bool operator == (const SolidLoadChargeMaterial& rhs) const
    {
        return specificHeatSolid == rhs.specificHeatSolid &&
                latentHeat == rhs.latentHeat &&
                specificHeatLiquid == rhs.specificHeatLiquid &&
                meltingPoint == rhs.meltingPoint &&
                substance == rhs.substance && id == rhs.id;
    }

    /**
     * bool operature
     */
    bool operator != (const SolidLoadChargeMaterial& rhs) const
    {
        return !(*this == rhs);
    }

    /**
     * Obtain the total heat for the solid charge material in Btu/hr
     * */
    double getTotalHeat();

private:

    // In/Out values
    std::string substance = "Unknown";
    // In values
    LoadChargeMaterial::ThermicReactionType thermicReactionType = LoadChargeMaterial::ThermicReactionType::NONE;
    double specificHeatSolid = 0.0;
    double latentHeat = 0.0;
    double specificHeatLiquid = 0.0;
    double meltingPoint = 0.0;
    double chargeFeedRate = 0.0;
    double waterContentCharged = 0.0;
    double waterContentDischarged = 0.0;
    double initialTemperature = 0.0;
    double dischargeTemperature = 0.0;
    double waterVaporDischargeTemperature = 0.0;
    double chargeMelted = 0.0;
    double chargeReacted = 0.0;
    double reactionHeat = 0.0;
    double additionalHeat = 0.0;
    int id = 0;
    // Out values
    double totalHeat = 0.0;

    friend class SQLite;

    /**
    * Constructor for the solid load/charge material with subset of inputs specified.
    * @param substance string, Name of substance
    * @param specificHeatSolid double, Average specific heat of the solid material (dry) in Btu/(lb*°F)
    * @param latentHeat double, Latent heat of fusion in Btu/(lb)
    * @param specificHeatLiquid double, Specific heat of liquid from molten material in Btu/(lb*°F)
    * @param meltingPoint double, The melting point of the material in °F
    * */
    SolidLoadChargeMaterial(
            std::string substance,
            double specificHeatSolid,
            double latentHeat,
            double specificHeatLiquid,
            double meltingPoint
    ) : substance(std::move(substance)),
        specificHeatSolid(specificHeatSolid),
        latentHeat(latentHeat),
        specificHeatLiquid(specificHeatLiquid),
        meltingPoint(meltingPoint)
    {}

};

#endif //AMO_SUITE_SOLIDLOADCHARGEMATERIAL_H
