/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2012-2018 German Aerospace Center (DLR) and others.
// This program and the accompanying materials
// are made available under the terms of the Eclipse Public License v2.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v20.html
// SPDX-License-Identifier: EPL-2.0
/****************************************************************************/
/// @file    Route.h
/// @author  Daniel Krajzewicz
/// @author  Mario Krumnow
/// @author  Michael Behrisch
/// @date    30.05.2012
/// @version $Id$
///
// C++ TraCI client API implementation
/****************************************************************************/
#ifndef Route_h
#define Route_h


// ===========================================================================
// included modules
// ===========================================================================
#include <config.h>

#include <vector>
#include <libsumo/TraCIDefs.h>


// ===========================================================================
// class declarations
// ===========================================================================
class MSRoute;
namespace libsumo {
    class VariableWrapper;
}


// ===========================================================================
// class definitions
// ===========================================================================
/**
 * @class Route
 * @brief C++ TraCI client API implementation
 */
namespace libsumo {
class Route {
public:

    static std::vector<std::string> getIDList();
    static int getIDCount();
    static std::vector<std::string> getEdges(const std::string& routeID);
    static std::string getParameter(const std::string& routeID, const std::string& param);

    static void add(const std::string& routeID, const std::vector<std::string>& edgeIDs);
    static void setParameter(const std::string& routeID, const std::string& key, const std::string& value); // not needed so far

    static void subscribe(const std::string& objID, const std::vector<int>& vars = std::vector<int>(), SUMOTime beginTime = 0, SUMOTime endTime = ((2 ^ 31) - 1));
    static void subscribeContext(const std::string& objID, int domain, double range, const std::vector<int>& vars = std::vector<int>(), SUMOTime beginTime = 0, SUMOTime endTime = ((2 ^ 31) - 1));
    static const SubscriptionResults getSubscriptionResults();
    static const TraCIResults getSubscriptionResults(const std::string& objID);
    static const ContextSubscriptionResults getContextSubscriptionResults();
    static const SubscriptionResults getContextSubscriptionResults(const std::string& objID);

    static std::shared_ptr<VariableWrapper> makeWrapper();

    static bool handleVariable(const std::string& objID, const int variable, VariableWrapper* wrapper);

private:
    static const MSRoute* getRoute(const std::string& id);

private:
    static SubscriptionResults mySubscriptionResults;
    static ContextSubscriptionResults myContextSubscriptionResults;

    /// @brief invalidated standard constructor
    Route() = delete;
};


}


#endif

/****************************************************************************/
