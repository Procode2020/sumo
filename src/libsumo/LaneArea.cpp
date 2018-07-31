/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2012-2018 German Aerospace Center (DLR) and others.
// This program and the accompanying materials
// are made available under the terms of the Eclipse Public License v2.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v20.html
// SPDX-License-Identifier: EPL-2.0
/****************************************************************************/
/// @file    LaneArea.cpp
/// @author  Daniel Krajzewicz
/// @author  Mario Krumnow
/// @author  Jakob Erdmann
/// @author  Michael Behrisch
/// @date    30.05.2012
/// @version $Id$
///
// C++ TraCI client API implementation
/****************************************************************************/


// ===========================================================================
// included modules
// ===========================================================================
#include <config.h>

#include <microsim/output/MSDetectorControl.h>
#include <microsim/output/MSE2Collector.h>
#include <microsim/MSNet.h>
#include <traci-server/TraCIConstants.h>
#include "LaneArea.h"


namespace libsumo {
// ===========================================================================
// static member initializations
// ===========================================================================
SubscriptionResults LaneArea::mySubscriptionResults;
ContextSubscriptionResults LaneArea::myContextSubscriptionResults;


// ===========================================================================
// static member definitions
// ===========================================================================
std::vector<std::string>
LaneArea::getIDList() {
    std::vector<std::string> ids;
    MSNet::getInstance()->getDetectorControl().getTypedDetectors(SUMO_TAG_LANE_AREA_DETECTOR).insertIDs(ids);
    return ids;
}


int
LaneArea::getIDCount() {
    std::vector<std::string> ids;
    return (int)MSNet::getInstance()->getDetectorControl().getTypedDetectors(SUMO_TAG_LANE_AREA_DETECTOR).size();
}


int
LaneArea::getJamLengthVehicle(const std::string& detID) {
    return getDetector(detID)->getCurrentJamLengthInVehicles();
}


double
LaneArea::getJamLengthMeters(const std::string& detID) {
    return getDetector(detID)->getCurrentJamLengthInMeters();
}


double
LaneArea::getLastStepMeanSpeed(const std::string& detID) {
    return getDetector(detID)->getCurrentMeanSpeed();
}


std::vector<std::string>
LaneArea::getLastStepVehicleIDs(const std::string& detID) {
    return getDetector(detID)->getCurrentVehicleIDs();
}


double
LaneArea::getLastStepOccupancy(const std::string& detID) {
    return getDetector(detID)->getCurrentOccupancy();
}


double
LaneArea::getPosition(const std::string& detID) {
    return getDetector(detID)->getStartPos();
}


std::string
LaneArea::getLaneID(const std::string& detID) {
    return getDetector(detID)->getLane()->getID();
}


double
LaneArea::getLength(const std::string& detID) {
    const MSE2Collector* const e2 = getDetector(detID);
    return e2->getLength();
}


int
LaneArea::getLastStepVehicleNumber(const std::string& detID) {
    return getDetector(detID)->getCurrentVehicleNumber();
}


int
LaneArea::getLastStepHaltingNumber(const std::string& detID) {
    return getDetector(detID)->getCurrentHaltingNumber();
}


void
LaneArea::subscribe(const std::string& objID, const std::vector<int>& vars, SUMOTime beginTime, SUMOTime endTime) {
    libsumo::Helper::subscribe(CMD_SUBSCRIBE_LANEAREA_VARIABLE, objID, vars, beginTime, endTime);
}


void
LaneArea::subscribeContext(const std::string& objID, int domain, double range, const std::vector<int>& vars, SUMOTime beginTime, SUMOTime endTime) {
    libsumo::Helper::subscribe(CMD_SUBSCRIBE_LANEAREA_CONTEXT, objID, vars, beginTime, endTime, domain, range);
}


const SubscriptionResults
LaneArea::getSubscriptionResults() {
    return mySubscriptionResults;
}


const TraCIResults
LaneArea::getSubscriptionResults(const std::string& objID) {
    return mySubscriptionResults[objID];
}


const ContextSubscriptionResults
LaneArea::getContextSubscriptionResults() {
    return myContextSubscriptionResults;
}


const SubscriptionResults
LaneArea::getContextSubscriptionResults(const std::string& objID) {
    return myContextSubscriptionResults[objID];
}


MSE2Collector*
LaneArea::getDetector(const std::string& id) {
    MSE2Collector* e2 = dynamic_cast<MSE2Collector*>(MSNet::getInstance()->getDetectorControl().getTypedDetectors(SUMO_TAG_LANE_AREA_DETECTOR).get(id));
    if (e2 == 0) {
        throw TraCIException("Lane area detector '" + id + "' is not known");
    }
    return e2;
}


std::shared_ptr<VariableWrapper>
LaneArea::makeWrapper() {
    return std::make_shared<Helper::SubscriptionWrapper>(handleVariable, mySubscriptionResults, myContextSubscriptionResults);
}


bool
LaneArea::handleVariable(const std::string& objID, const int variable, VariableWrapper* wrapper) {
    switch (variable) {
    case ID_LIST:
        return wrapper->wrapStringList(objID, variable, getIDList());
    case ID_COUNT:
        return wrapper->wrapInt(objID, variable, getIDCount());
    default:
        return false;
    }
}


}


/****************************************************************************/
