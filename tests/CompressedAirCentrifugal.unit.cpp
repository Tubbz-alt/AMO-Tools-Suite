#include "catch.hpp"
#include <calculator/util/CompressedAirCentrifugal.h>

TEST_CASE( "Calculate estimated power(kW) consumption and air flow(acfm) for a centrifugal compressors based on control type", "[Power-Flow-Calculations]" ) {
    auto ccBlow = CompressedAirCentrifugal_BlowOff(452.3, 3138, 370.9, 2510);
    auto resBOff = ccBlow.calculateFromPerkW_BlowOff(0.82, 0.6798);
    CHECK(resBOff.kW_Calc == Approx(370.886));
    CHECK(resBOff.C_Calc == Approx(376.788));
    CHECK(resBOff.PerkW == Approx(0.82));
    CHECK(resBOff.C_Per == Approx(0.120073));
    CHECK(resBOff.C_blow == Approx(2133.21));
    CHECK(resBOff.blowPer == Approx(0.6798));
    resBOff = ccBlow.calculateFromPerC_BlowOff(0.01);
    CHECK(resBOff.kW_Calc == Approx(370.9));
    CHECK(resBOff.C_Calc == Approx(31.38));
    CHECK(resBOff.PerkW == Approx(0.820031));
    CHECK(resBOff.C_Per == Approx(0.01));
    CHECK(resBOff.C_blow == Approx(2478.62));
    CHECK(resBOff.blowPer == Approx(0.789873));
    resBOff = ccBlow.calculateFromkWMeasured_BlowOff(370.9, 0.6798);
    CHECK(resBOff.kW_Calc == Approx(370.9));
    CHECK(resBOff.C_Calc == Approx(376.788));
    CHECK(resBOff.PerkW == Approx(0.8200309));
    CHECK(resBOff.C_Per == Approx(0.120073));
    CHECK(resBOff.C_blow == Approx(2133.21));
    CHECK(resBOff.blowPer == Approx(0.6798));
    resBOff = ccBlow.calculateFromCMeasured_BlowOff(31.38);
    CHECK(resBOff.kW_Calc == Approx(370.9));
    CHECK(resBOff.C_Calc == Approx(31.38));
    CHECK(resBOff.PerkW == Approx(0.820031));
    CHECK(resBOff.C_Per == Approx(0.01));
    CHECK(resBOff.C_blow == Approx(2478.62));
    CHECK(resBOff.blowPer == Approx(0.789873));
    resBOff = ccBlow.calculateFromVIPFMeasured_BlowOff(440, 0.02152, 50, 0.6798);
    CHECK(resBOff.kW_Calc == Approx(370.885));
    CHECK(resBOff.C_Calc == Approx(376.788));
    CHECK(resBOff.PerkW == Approx(0.82));
    CHECK(resBOff.C_Per == Approx(0.120073));
    CHECK(resBOff.C_blow == Approx(2133.21));
    CHECK(resBOff.blowPer == Approx(0.6798));

    ccBlow.AdjustDischargePressure({3200, 3138, 2885}, {91, 100, 117}, 100);
    resBOff = ccBlow.calculateFromPerkW_BlowOff(0.82, 0.6798);
    CHECK(resBOff.kW_Calc == Approx(370.886));
    CHECK(resBOff.C_Calc == Approx(376.788));
    CHECK(resBOff.PerkW == Approx(0.82));
    CHECK(resBOff.C_Per == Approx(0.120073));
    CHECK(resBOff.C_blow == Approx(2133.21));
    CHECK(resBOff.blowPer == Approx(0.6798));
    resBOff = ccBlow.calculateFromPerC_BlowOff(0.01);
    CHECK(resBOff.kW_Calc == Approx(370.9));
    CHECK(resBOff.C_Calc == Approx(31.38));
    CHECK(resBOff.PerkW == Approx(0.820031));
    CHECK(resBOff.C_Per == Approx(0.01));
    CHECK(resBOff.C_blow == Approx(2478.62));
    CHECK(resBOff.blowPer == Approx(0.789873));
    resBOff = ccBlow.calculateFromkWMeasured_BlowOff(370.9, 0.6798);
    CHECK(resBOff.kW_Calc == Approx(370.9));
    CHECK(resBOff.C_Calc == Approx(376.788));
    CHECK(resBOff.PerkW == Approx(0.8200309));
    CHECK(resBOff.C_Per == Approx(0.120073));
    CHECK(resBOff.C_blow == Approx(2133.21));
    CHECK(resBOff.blowPer == Approx(0.6798));
    resBOff = ccBlow.calculateFromCMeasured_BlowOff(31.38);
    CHECK(resBOff.kW_Calc == Approx(370.9));
    CHECK(resBOff.C_Calc == Approx(31.38));
    CHECK(resBOff.PerkW == Approx(0.820031));
    CHECK(resBOff.C_Per == Approx(0.01));
    CHECK(resBOff.C_blow == Approx(2478.62));
    CHECK(resBOff.blowPer == Approx(0.789873));
    resBOff = ccBlow.calculateFromVIPFMeasured_BlowOff(440, 0.02152, 50, 0.6798);
    CHECK(resBOff.kW_Calc == Approx(370.885));
    CHECK(resBOff.C_Calc == Approx(376.788));
    CHECK(resBOff.PerkW == Approx(0.82));
    CHECK(resBOff.C_Per == Approx(0.120073));
    CHECK(resBOff.C_blow == Approx(2133.21));
    CHECK(resBOff.blowPer == Approx(0.6798));


    auto cclUL = CompressedAirCentrifugal_LoadUnload(452.3, 3138, 71.3);
    auto resLul = cclUL.calculateFromPerkW(0.36);
    CHECK(resLul.kW_Calc == Approx(162.828));
    CHECK(resLul.C_Calc == Approx(753.12));
    CHECK(resLul.PerkW == Approx(0.36));
    CHECK(resLul.C_Per == Approx(0.24));
    resLul = cclUL.calculateFromPerC(0.24);
    CHECK(resLul.kW_Calc == Approx(162.828));
    CHECK(resLul.C_Calc == Approx(753.12));
    CHECK(resLul.PerkW == Approx(0.36));
    CHECK(resLul.C_Per == Approx(0.24));
    resLul = cclUL.calculateFromkWMeasured(162.828);
    CHECK(resLul.kW_Calc == Approx(162.828));
    CHECK(resLul.C_Calc == Approx(753.12));
    CHECK(resLul.PerkW == Approx(0.36));
    CHECK(resLul.C_Per == Approx(0.24));
    resLul = cclUL.calculateFromCMeasured(753.12);
    CHECK(resLul.kW_Calc == Approx(162.828));
    CHECK(resLul.C_Calc == Approx(753.12));
    CHECK(resLul.PerkW == Approx(0.36));
    CHECK(resLul.C_Per == Approx(0.24));
    resLul = cclUL.calculateFromVIPFMeasured(440,0.00945,50);
    CHECK(resLul.kW_Calc == Approx(162.865));
    CHECK(resLul.C_Calc == Approx(753.12));
    CHECK(resLul.PerkW == Approx(0.3600828));
    CHECK(resLul.C_Per == Approx(0.24));

    cclUL.AdjustDischargePressure({3200, 3138, 2885}, {91, 100, 117}, 100);
    resLul = cclUL.calculateFromPerkW(0.36);
    CHECK(resLul.kW_Calc == Approx(162.828));
    CHECK(resLul.C_Calc == Approx(753.12));
    CHECK(resLul.PerkW == Approx(0.36));
    CHECK(resLul.C_Per == Approx(0.24));
    resLul = cclUL.calculateFromPerC(0.24);
    CHECK(resLul.kW_Calc == Approx(162.828));
    CHECK(resLul.C_Calc == Approx(753.12));
    CHECK(resLul.PerkW == Approx(0.36));
    CHECK(resLul.C_Per == Approx(0.24));
    resLul = cclUL.calculateFromkWMeasured(162.828);
    CHECK(resLul.kW_Calc == Approx(162.828));
    CHECK(resLul.C_Calc == Approx(753.12));
    CHECK(resLul.PerkW == Approx(0.36));
    CHECK(resLul.C_Per == Approx(0.24));
    resLul = cclUL.calculateFromCMeasured(753.12);
    CHECK(resLul.kW_Calc == Approx(162.828));
    CHECK(resLul.C_Calc == Approx(753.12));
    CHECK(resLul.PerkW == Approx(0.36));
    CHECK(resLul.C_Per == Approx(0.24));
    resLul = cclUL.calculateFromVIPFMeasured(440,0.00945,50);
    CHECK(resLul.kW_Calc == Approx(162.865));
    CHECK(resLul.C_Calc == Approx(753.12));
    CHECK(resLul.PerkW == Approx(0.3600828));
    CHECK(resLul.C_Per == Approx(0.24));

    auto ccMuL = CompressedAirCentrifugal_ModulationUnload(452.3, 3138, 71.3, 3005, 411.9, 2731);
    auto resMuL = ccMuL.calculateFromPerkW(0.94);
    CHECK(resMuL.kW_Calc == Approx(425.162));
    CHECK(resMuL.C_Calc == Approx(2820.95));
    CHECK(resMuL.PerkW == Approx(0.94));
    CHECK(resMuL.C_Per == Approx(0.93875));
    resMuL = ccMuL.calculateFromPerC(0.24);
    CHECK(resMuL.kW_Calc == Approx(165.226));
    CHECK(resMuL.C_Calc == Approx(753.12));
    CHECK(resMuL.PerkW == Approx(0.365302));
    CHECK(resMuL.C_Per == Approx(0.24));
    resMuL = ccMuL.calculateFromkWMeasured(425.162);
    CHECK(resMuL.kW_Calc == Approx(425.162));
    CHECK(resMuL.C_Calc == Approx(2820.95));
    CHECK(resMuL.PerkW == Approx(0.94));
    CHECK(resMuL.C_Per == Approx(0.93875));
    resMuL = ccMuL.calculateFromCMeasured(753.12);
    CHECK(resMuL.kW_Calc == Approx(165.226));
    CHECK(resMuL.C_Calc == Approx(753.12));
    CHECK(resMuL.PerkW == Approx(0.365302));
    CHECK(resMuL.C_Per == Approx(0.24));
    resMuL = ccMuL.calculateFromVIPFMeasured(440, 0.02467, 50);
    CHECK(resMuL.kW_Calc == Approx(425.174));
    CHECK(resMuL.C_Calc == Approx(2821.02));
    CHECK(resMuL.PerkW == Approx(0.940026));
    CHECK(resMuL.C_Per == Approx(0.938777));

    ccMuL.AdjustDischargePressure({3200, 3138, 2885}, {91, 100, 117}, 100, 58.23);
    resMuL = ccMuL.calculateFromPerkW(0.94);
    CHECK(resMuL.kW_Calc == Approx(425.162));
    CHECK(resMuL.C_Calc == Approx(2820.95));
    CHECK(resMuL.PerkW == Approx(0.94));
    CHECK(resMuL.C_Per == Approx(0.93875));
    resMuL = ccMuL.calculateFromPerC(0.24);
    CHECK(resMuL.kW_Calc == Approx(165.226));
    CHECK(resMuL.C_Calc == Approx(753.12));
    CHECK(resMuL.PerkW == Approx(0.365302));
    CHECK(resMuL.C_Per == Approx(0.24));
    resMuL = ccMuL.calculateFromkWMeasured(425.162);
    CHECK(resMuL.kW_Calc == Approx(425.162));
    CHECK(resMuL.C_Calc == Approx(2820.95));
    CHECK(resMuL.PerkW == Approx(0.94));
    CHECK(resMuL.C_Per == Approx(0.93875));
    resMuL = ccMuL.calculateFromCMeasured(753.12);
    CHECK(resMuL.kW_Calc == Approx(165.226));
    CHECK(resMuL.C_Calc == Approx(753.12));
    CHECK(resMuL.PerkW == Approx(0.365302));
    CHECK(resMuL.C_Per == Approx(0.24));
    resMuL = ccMuL.calculateFromVIPFMeasured(440, 0.02467, 50);
    CHECK(resMuL.kW_Calc == Approx(425.174));
    CHECK(resMuL.C_Calc == Approx(2821.02));
    CHECK(resMuL.PerkW == Approx(0.940026));
    CHECK(resMuL.C_Per == Approx(0.938777));
}
