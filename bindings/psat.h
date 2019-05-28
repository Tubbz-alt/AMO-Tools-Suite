#ifndef AMO_TOOLS_SUITE_PSAT_BRIDGE_H
#define AMO_TOOLS_SUITE_PSAT_BRIDGE_H

#include <map>
#include <unordered_map>
#include <nan.h>
#include <node.h>
#include <vector>
#include <array>
#include "results/Results.h"
#include "results/InputData.h"
#include "calculator/motor/EstimateFLA.h"
#include "calculator/motor/MotorCurrent.h"
#include "calculator/motor/MotorEfficiency.h"
#include "calculator/motor/MotorPowerFactor.h"
#include "calculator/pump/OptimalPrePumpEff.h"
#include "calculator/pump/OptimalSpecificSpeedCorrection.h"
#include "calculator/pump/OptimalDeviationFactor.h"
#include "calculator/pump/HeadTool.h"

using namespace Nan;
using namespace v8;

//
//// Setup
//
//Isolate* iso;
Local<Object> inp;
Local<Object> r;

double Get(std::string const & nm) {
	Local<String> getName = Nan::New<String>(nm).ToLocalChecked();
	auto rObj = inp->ToObject()->Get(getName);
	if (rObj->IsUndefined()) {
		ThrowTypeError(std::string("Get method in psat.h: " + nm + " not present in object").c_str());
	}
	return rObj->NumberValue();
}

inline void SetR(const std::string &key, double val)
{
    Nan::Set(r, Nan::New<String>(key).ToLocalChecked(), Nan::New<Number>(val));
}

NAN_METHOD(headToolSuctionTank) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    const double specificGravity = Get("specificGravity");
    const double flowRate = Get("flowRate");
    const double suctionPipeDiameter = Get("suctionPipeDiameter");
    const double suctionTankGasOverPressure = Get("suctionTankGasOverPressure");
    const double suctionTankFluidSurfaceElevation = Get("suctionTankFluidSurfaceElevation");
    const double suctionLineLossCoefficients = Get("suctionLineLossCoefficients");
    const double dischargePipeDiameter = Get("dischargePipeDiameter");
    const double dischargeGaugePressure = Get("dischargeGaugePressure");
    const double dischargeGaugeElevation = Get("dischargeGaugeElevation");
    const double dischargeLineLossCoefficients = Get("dischargeLineLossCoefficients");

    ;

    auto rv = HeadToolSuctionTank(specificGravity, flowRate, suctionPipeDiameter, suctionTankGasOverPressure,
        suctionTankFluidSurfaceElevation, suctionLineLossCoefficients, dischargePipeDiameter,
        dischargeGaugePressure, dischargeGaugeElevation, dischargeLineLossCoefficients).calculate();

    SetR("differentialElevationHead", rv.elevationHead);
    SetR("differentialPressureHead", rv.pressureHead);
    SetR("differentialVelocityHead", rv.velocityHeadDifferential);
    SetR("estimatedSuctionFrictionHead", rv.suctionHead);
    SetR("estimatedDischargeFrictionHead", rv.dischargeHead);
    SetR("pumpHead", rv.pumpHead);

    info.GetReturnValue().Set(r);
}

NAN_METHOD(headTool) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    const double specificGravity = Get("specificGravity");
    const double flowRate = Get("flowRate");
    const double suctionPipeDiameter = Get("suctionPipeDiameter");
    const double suctionGaugePressure = Get("suctionGaugePressure");
    const double suctionGaugeElevation = Get("suctionGaugeElevation");
    const double suctionLineLossCoefficients = Get("suctionLineLossCoefficients");
    const double dischargePipeDiameter = Get("dischargePipeDiameter");
    const double dischargeGaugePressure = Get("dischargeGaugePressure");
    const double dischargeGaugeElevation = Get("dischargeGaugeElevation");
    const double dischargeLineLossCoefficients = Get("dischargeLineLossCoefficients");

    auto rv = HeadTool(specificGravity, flowRate, suctionPipeDiameter, suctionGaugePressure,
        suctionGaugeElevation, suctionLineLossCoefficients, dischargePipeDiameter,
        dischargeGaugePressure, dischargeGaugeElevation, dischargeLineLossCoefficients).calculate();

    SetR("differentialElevationHead", rv.elevationHead);
    SetR("differentialPressureHead", rv.pressureHead);
    SetR("differentialVelocityHead", rv.velocityHeadDifferential);
    SetR("estimatedSuctionFrictionHead", rv.suctionHead);
    SetR("estimatedDischargeFrictionHead", rv.dischargeHead);
    SetR("pumpHead", rv.pumpHead);

    info.GetReturnValue().Set(r);
}

// Fields

Motor::LineFrequency line() {
    unsigned val = static_cast<unsigned>(Get("line_frequency"));
    return static_cast<Motor::LineFrequency>(val);
}
Motor::EfficiencyClass effCls() {
	unsigned val = static_cast<unsigned>(Get("efficiency_class"));
    return static_cast<Motor::EfficiencyClass>(val);
}
Motor::Drive drive() {
    unsigned val = static_cast<unsigned>(Get("drive"));
    return static_cast<Motor::Drive>(val);
}
Pump::Style style() {
    unsigned val = static_cast<unsigned>(Get("pump_style"));
    return static_cast<Pump::Style>(val);
}
Motor::LoadEstimationMethod  loadEstimationMethod() {
    unsigned val = static_cast<unsigned>(Get("load_estimation_method"));
    return static_cast<Motor::LoadEstimationMethod>(val);
}
Pump::SpecificSpeed speed() {
    unsigned val = static_cast<unsigned>(Get("fixed_speed"));
    return static_cast<Pump::SpecificSpeed>(val);
}

NAN_METHOD(resultsExisting) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    Pump::Style style1 = style();
    Motor::Drive drive1 = drive();
//    Pump::SpecificSpeed fixed_speed = speed();
    double specifiedDriveEfficiency;
    if (drive1 == Motor::Drive::SPECIFIED) {
        specifiedDriveEfficiency = Get("specifiedDriveEfficiency") / 100;
    }
    else {
        specifiedDriveEfficiency = 1;
    }

    Motor::LineFrequency lineFrequency = line();
    Motor::EfficiencyClass efficiencyClass = effCls();

    Motor::LoadEstimationMethod loadEstimationMethod1 = loadEstimationMethod();

    Pump::Input pump(style1, Get("pump_specified") / 100.0, Get("pump_rated_speed"), drive1, 0,
              Get("specific_gravity"), static_cast<int>(Get("stages")), Pump::SpecificSpeed::FIXED_SPEED, specifiedDriveEfficiency);

    Motor motor(lineFrequency, Get("motor_rated_power"), Get("motor_rated_speed"), efficiencyClass, Get("efficiency"),
                Get("motor_rated_voltage"), Get("motor_rated_fla"));

    Pump::FieldData fd(Get("flow_rate"), Get("head"), loadEstimationMethod1, Get("motor_field_power"),
                 Get("motor_field_current"), Get("motor_field_voltage"));

    PSATResult psat(pump, motor, fd, Get("operating_hours"), Get("cost_kw_hour"));
	try {
        auto const & ex = psat.calculateExisting();

        SetR("pump_efficiency",ex.pumpEfficiency * 100);
        SetR("motor_rated_power",ex.motorRatedPower);
        SetR("motor_shaft_power",ex.motorShaftPower);
        SetR("pump_shaft_power",ex.pumpShaftPower);
        SetR("motor_efficiency",ex.motorEfficiency * 100);
        SetR("motor_power_factor",ex.motorPowerFactor * 100);
        SetR("motor_current",ex.motorCurrent);
        SetR("motor_power",ex.motorPower);
        SetR("load_factor",ex.loadFactor);
        SetR("drive_efficiency",ex.driveEfficiency * 100);
        SetR("annual_energy",ex.annualEnergy);
        SetR("annual_cost",ex.annualCost * 1000);
        SetR("annual_savings_potential",psat.getAnnualSavingsPotential() * 1000);
        SetR("optimization_rating",psat.getOptimizationRating());

        info.GetReturnValue().Set(r);
    } catch (std::runtime_error const & e) {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in resultsExisting - psat.h: " + what).c_str());
        info.GetReturnValue().Set(r);
    }
}

NAN_METHOD(resultsModified) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    Pump::Style style1 = style();
    Motor::Drive drive1 = drive();
    Pump::SpecificSpeed fixed_speed = speed();

    double specifiedDriveEfficiency;
    if (drive1 == Motor::Drive::SPECIFIED) {
        specifiedDriveEfficiency = Get("specifiedDriveEfficiency") / 100;
    }
    else {
        specifiedDriveEfficiency = 1;
    }

    Motor::LineFrequency lineFrequency = line();
    Motor::EfficiencyClass efficiencyClass = effCls();

    Motor::LoadEstimationMethod loadEstimationMethod1 = loadEstimationMethod();

    Pump::Input pump(style1, Get("pump_specified") / 100.0, Get("pump_rated_speed"), drive1, Get("kinematic_viscosity"),
              Get("specific_gravity"), static_cast<int>(Get("stages")), fixed_speed, specifiedDriveEfficiency);

    Motor motor(lineFrequency, Get("motor_rated_power"), Get("motor_rated_speed"), efficiencyClass, Get("efficiency"),
                Get("motor_rated_voltage"), Get("motor_rated_fla"), Get("margin"));

    Pump::FieldData fd(Get("flow_rate"), Get("head"), loadEstimationMethod1, Get("motor_field_power"),
                 Get("motor_field_current"), Get("motor_field_voltage"));

    PSATResult psat(pump, motor, fd, Get("operating_hours"), Get("cost_kw_hour"));
    try {
        auto const & mod = psat.calculateModified();

        SetR("pump_efficiency",mod.pumpEfficiency * 100);
        SetR("motor_rated_power",mod.motorRatedPower);
        SetR("motor_shaft_power",mod.motorShaftPower);
        SetR("pump_shaft_power",mod.pumpShaftPower);
        SetR("motor_efficiency",mod.motorEfficiency * 100);
        SetR("motor_power_factor",mod.motorPowerFactor * 100);
        SetR("motor_current",mod.motorCurrent);
        SetR("motor_power",mod.motorPower);
        SetR("load_factor",mod.loadFactor);
        SetR("drive_efficiency",mod.driveEfficiency * 100);
        SetR("annual_energy",mod.annualEnergy);
        SetR("annual_cost",mod.annualCost * 1000);
        SetR("annual_savings_potential",psat.getAnnualSavingsPotential() * 1000);
        SetR("optimization_rating",psat.getOptimizationRating());

        info.GetReturnValue().Set(r);
    } catch (std::runtime_error const & e) {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in resultsModified - psat.h: " + what).c_str());
        info.GetReturnValue().Set(r);
    }
}

NAN_METHOD(estFLA) {
    inp = info[0]->ToObject();
    double motor_rated_power = Get("motor_rated_power");
    double motor_rated_speed = Get("motor_rated_speed");
    Motor::LineFrequency l = line();
    Motor::EfficiencyClass e = effCls();
    double efficiency = Get("efficiency");
    double motor_rated_voltage = Get("motor_rated_voltage");
    EstimateFLA fla(motor_rated_power, motor_rated_speed, l, e, efficiency, motor_rated_voltage);
    fla.calculate();
    info.GetReturnValue().Set(fla.getEstimatedFLA());
}

NAN_METHOD(motorPerformance) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();
    Motor::LineFrequency l = line();
    double motor_rated_speed = Get("motor_rated_speed");
    Motor::EfficiencyClass efficiencyClass = effCls();
    double efficiency = Get("efficiency");
    double motor_rated_power = Get("motor_rated_power");
    double load_factor = Get("load_factor");
	try {
        MotorEfficiency mef(l, motor_rated_speed, efficiencyClass, motor_rated_power);
        double mefVal = mef.calculate(load_factor, efficiency);
        SetR("efficiency", mefVal * 100);
        double motor_rated_voltage = Get("motor_rated_voltage");
        double fla = Get("motor_rated_fla");
        MotorCurrent mc(motor_rated_power, motor_rated_speed, l, efficiencyClass, efficiency, load_factor,
                        motor_rated_voltage);
        double mcVal = mc.calculateCurrent(fla);
        SetR("motor_current", mcVal / fla * 100);

        MotorPowerFactor motorPowerFactor(motor_rated_power, load_factor, mcVal, mefVal, motor_rated_voltage);
        SetR("motor_power_factor", motorPowerFactor.calculate() * 100);
    } catch (std::runtime_error const & e) {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in motorPerformance - psat.h: " + what).c_str());
        info.GetReturnValue().Set(0);
    }

    info.GetReturnValue().Set(r);
}

NAN_METHOD(pumpEfficiency)  {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();
    Pump::Style s = style();
    double flow = Get("flow_rate");
    OptimalPrePumpEff pef(s, flow);
    double v = pef.calculate();
    SetR("average",v);
    double odf = OptimalDeviationFactor(flow).calculate();
    SetR("max",v*odf);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(achievableEfficiency) {
    inp = info[0]->ToObject();
    double specific_speed = Get("specific_speed");
    Pump::Style s = style();
    info.GetReturnValue().Set(OptimalSpecificSpeedCorrection(s, specific_speed).calculate()*100);
}

NAN_METHOD(nema) {
    inp = info[0]->ToObject();
    Motor::LineFrequency l = line();
    double motor_rated_speed = Get("motor_rated_speed");
    Motor::EfficiencyClass efficiencyClass = effCls();
    double efficiency = Get("efficiency");
    double motor_rated_power = Get("motor_rated_power");
    double load_factor = Get("load_factor");
    try {
        info.GetReturnValue().Set(MotorEfficiency(l, motor_rated_speed, efficiencyClass, motor_rated_power).calculate(load_factor, efficiency) * 100);
    } catch (std::runtime_error const & e) {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in nema - psat.h: " + what).c_str());
        info.GetReturnValue().Set(0);
    }
}


#endif //AMO_TOOLS_SUITE_PSAT_BRIDGE_H
