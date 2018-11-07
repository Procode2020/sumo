/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2018 German Aerospace Center (DLR) and others.
// This program and the accompanying materials
// are made available under the terms of the Eclipse Public License v2.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v20.html
// SPDX-License-Identifier: EPL-2.0
/****************************************************************************/
/// @file    GNETAZFrame.h
/// @author  Pablo Alvarez Lopez
/// @date    Oct 2018
/// @version $Id$
///
// The Widget for add TAZ elements
/****************************************************************************/
#ifndef GNETAZFrame_h
#define GNETAZFrame_h


// ===========================================================================
// included modules
// ===========================================================================
#include "GNEFrame.h"

// ===========================================================================
// class definitions
// ===========================================================================
/**
 * @class GNETAZFrame
 * The Widget for setting internal attributes of TAZ elements
 */
class GNETAZFrame : public GNEFrame {

public:
    // ===========================================================================
    // class TAZCurrent
    // ===========================================================================

    class TAZCurrent : protected FXGroupBox {

    public:
        /// @brief struct for edges and the source/sink colors
        struct TAZEdge {
            /// @brief constructor
            TAZEdge(GNEEdge* _edge, GNEAdditional *_TAZSource, GNEAdditional *_TAZSink);
            
            /// @brief destructor (needed because RGBColors has to be deleted)
            ~TAZEdge();

            /// @brief update colors
            void updateColors();

            /// @brief TAZ edge
            GNEEdge* edge;

            /// @brief source TAZ
            GNEAdditional *TAZSource;

            /// @brif sink TAZ
            GNEAdditional *TAZSink;

            /// @brief color by source [0-9]
            int sourceColor;

            /// @brief color by sink [0-9]
            int sinkColor;

            /// @brief color by source + sink [0-9]
            int sourcePlusSinkColor;

            /// @brief color by source - sink [0-9]
            int sourceMinusSinkColor;
        };

        /// @brief constructor
        TAZCurrent(GNETAZFrame* TAZFrameParent);

        /// @brief destructor
        ~TAZCurrent();

        /// @brief set current TAZ
        void setTAZ(GNETAZ* TAZCurrent);

        /// @brief get current TAZ
        GNETAZ* getTAZ() const;

        /// @brief check if given edge belongs to current TAZ
        bool isTAZEdge(GNEEdge* edge) const;

        /// @brief get current net edges
        const std::vector<GNEEdge*> &getNetEdges() const;

        /// @brief get TAZEdges
        const std::vector<TAZCurrent::TAZEdge> &getTAZEdges() const;

        /// @brief refresh TAZEdges
        void refreshTAZEdges();

    protected:
        /// @brief add TAZChild
        void addTAZChild(GNEAdditional *additional);

    private:
        /// @brief pointer to TAZ Frame
        GNETAZFrame* myTAZFrameParent;

        /// @brief current TAZ
        GNETAZ* myTAZCurrent;

        /// @brief vector with pointers to edges (it's used to avoid slowdowns during Source/Sinks manipulations)
        std::vector<GNEEdge*> myNetEdges;

        /// @brief vector with TAZ's edges
        std::vector<TAZEdge> myTAZEdges;

        /// @brief Label for current TAZ
        FXLabel* myTAZCurrentLabel;
    };

    // ===========================================================================
    // class TAZCommonStatistics
    // ===========================================================================

    class TAZCommonStatistics : protected FXGroupBox {

    public:
        /// @brief constructor
        TAZCommonStatistics(GNETAZFrame* TAZFrameParent);

        /// @brief destructor
        ~TAZCommonStatistics();

        /// @brief show TAZ Common Statistics Modul
        void showTAZCommonStatisticsModul();

        /// @brief hide TAZ Common Statistics Modul
        void hideTAZCommonStatisticsModul();

        /// @brief update Statistics label
        void updateStatistics();

    private:
        /// @brief pointer to TAZFrame parent
        GNETAZFrame* myTAZFrameParent;

        /// @brief Statistics labels
        FXLabel *myStatisticsLabel;
    };

    // ===========================================================================
    // class TAZSaveChanges
    // ===========================================================================

    class TAZSaveChanges : protected FXGroupBox {
        /// @brief FOX-declaration
        FXDECLARE(GNETAZFrame::TAZSaveChanges)

    public:
        /// @brief constructor
        TAZSaveChanges(GNETAZFrame* TAZFrameParent);

        /// @brief destructor
        ~TAZSaveChanges();

        /// @brief show TAZ Save Changes Modul
        void showTAZSaveChangesModul();

        /// @brief hide TAZ Save Changes Modul
        void hideTAZSaveChangesModul();

        /// @brief enable buttons save and cancel changes (And begin Undo List)
        void enableButtonsAndBeginUndoList();

        /// @name FOX-callbacks
        /// @{
        /// @brief Called when the user press the button save changes
        long onCmdSaveChanges(FXObject*, FXSelector, void*);

        /// @brief Called when the user press the button cancel changes
        long onCmdCancelChanges(FXObject*, FXSelector, void*);
        /// @}

    protected:
        /// @brief FOX needs this
        TAZSaveChanges() {}

    private:
        /// @brief pointer to TAZFrame parent
        GNETAZFrame* myTAZFrameParent;

        /// @field FXButton for save changes in TAZEdges
        FXButton* mySaveChangesButton;

        /// @field FXButton for cancel changes in TAZEdges
        FXButton* myCancelChangesButton;
    };

    // ===========================================================================
    // class TAZEdgesCommonParameters
    // ===========================================================================

    class TAZEdgesCommonParameters : protected FXGroupBox {
        /// @brief FOX-declaration
        FXDECLARE(GNETAZFrame::TAZEdgesCommonParameters)

    public:
        /// @brief constructor
        TAZEdgesCommonParameters(GNETAZFrame* TAZFrameParent);

        /// @brief destructor
        ~TAZEdgesCommonParameters();

        /// @brief show TAZ Edges CommonParameters Modul
        void showTAZEdgesCommonParametersModul();

        /// @brief hide TAZ Edges CommonParameters Modul
        void hideTAZEdgesCommonParametersModul();

        /// @brief get default TAZSource weight
        double getDefaultTAZSourceWeight() const;

        /// @brief default TAZSink weight
        double getDefaultTAZSinkWeight() const;

        /// @brief check if toggle membership is enabled 
        bool getToggleMembership() const;

        /// @name FOX-callbacks
        /// @{
        /// @brief Called when the user press the button save changes
        long onCmdSetDefaultValues(FXObject* obj, FXSelector, void*);
        /// @}

    protected:
        /// @brief FOX needs this
        TAZEdgesCommonParameters() {}

    private:
        /// @brief pointer to TAZFrame parent
        GNETAZFrame* myTAZFrameParent;

        /// @brief CheckButton to enable or disable Toggle edge Membership
        FXCheckButton* myToggleMembership;

        /// @brief CheckButton to enable or disables a default value for new TAZ Sources
        FXCheckButton* myCheckBoxSetDefaultValueTAZSources;

        /// @brief textField to set a default value for TAZ Sources
        FXTextField* myTextFieldDefaultValueTAZSources;

        /// @brief CheckButton to enable or disables a default value for new TAZ Sinks
        FXCheckButton* myCheckBoxSetDefaultValueTAZSinks;

        /// @brief textField to set a default value for TAZ Sinks
        FXTextField* myTextFieldDefaultValueTAZSinks;

        /// @brief default TAZSource weight
        double myDefaultTAZSourceWeight;

        /// @brief default TAZSink weight
        double myDefaultTAZSinkWeight;
    };

    // ===========================================================================
    // class TAZSelectionStatistics
    // ===========================================================================

    class TAZSelectionStatistics : protected FXGroupBox {

    public:
        /// @brief constructor
        TAZSelectionStatistics(GNETAZFrame* TAZFrameParent);

        /// @brief destructor
        ~TAZSelectionStatistics();

        /// @brief show TAZ Selection Statistics Modul
        void showTAZSelectionStatisticsModul();

        /// @brief hide TAZ Selection Statistics Modul
        void hideTAZSelectionStatisticsModul();

        /// @brief add an edge and their TAZ Childs in the list of selected items
        bool selectEdge(const TAZCurrent::TAZEdge &edge);

        /// @brief un select an edge (and their TAZ Childs)
        bool unselectEdge(GNEEdge* edge);

        /// @brief check if an edge is selected
        bool isEdgeSelected(GNEEdge* edge);

        /// @brief clear current TAZ childs
        void clearSelectedEdges();

        /// @brief get map with edge and TAZChilds
        const std::vector<TAZCurrent::TAZEdge> &getEdgeAndTAZChildsSelected() const;

    protected:
        /// @brief update TAZSelectionStatistics
        void updateStatistics();

    private:
        /// @brief pointer to TAZFrame parent
        GNETAZFrame* myTAZFrameParent;

        /// @brief Statistics labels
        FXLabel *myStatisticsLabel;

        /// @brief vector with the current selected edges and their associated childs
        std::vector<TAZCurrent::TAZEdge> myEdgeAndTAZChildsSelected;
    };

    // ===========================================================================
    // class TAZParameters
    // ===========================================================================

    class TAZParameters : protected FXGroupBox {
        /// @brief FOX-declaration
        FXDECLARE(GNETAZFrame::TAZParameters)

    public:
        /// @brief constructor
        TAZParameters(GNETAZFrame* TAZFrameParent);

        /// @brief destructor
        ~TAZParameters();

        /// @brief show TAZ parameters and set the default value of parameters
        void showTAZParametersModul();

        /// @brief hide TAZ parameters
        void hideTAZParametersModul();

        /// @brief check if current parameters are valid
        bool isCurrentParametersValid() const;

        /// @brief check if edges within has to be used after TAZ Creation
        bool isAddEdgesWithinEnabled() const;

        /// @brief get a map with attributes and their values
        std::map<SumoXMLAttr, std::string> getAttributesAndValues() const;

        /// @name FOX-callbacks
        /// @{
        /// @brief called when user press the "Color" button
        long onCmdSetColorAttribute(FXObject*, FXSelector, void*);

        /// @brief Called when user set a value
        long onCmdSetAttribute(FXObject*, FXSelector, void*);

        /// @brief Called when help button is pressed
        long onCmdHelp(FXObject*, FXSelector, void*);
        /// @}

    protected:
        /// @brief FOX needs this
        TAZParameters() {}

    private:
        /// @brief pointer to GNETAZFrame parent
        GNETAZFrame* myTAZFrameParent;

        /// @brief Button for open color editor
        FXButton* myColorEditor;

        /// @brief textField to modify the default value of color parameter
        FXTextField* myTextFieldColor;

        /// @brief CheckButton to enable or disable use edges within TAZ after creation
        FXCheckButton* myAddEdgesWithinCheckButton;

        /// @brief button for help
        FXButton* myHelpTAZAttribute;
    };

    // ===========================================================================
    // class TAZEdgesGraphic
    // ===========================================================================

    class TAZEdgesGraphic : protected FXGroupBox {
        /// @brief FOX-declaration
        FXDECLARE(GNETAZFrame::TAZEdgesGraphic)

    public:
        /// @brief constructor
        TAZEdgesGraphic(GNETAZFrame* TAZFrameParent);

        /// @brief destructor
        ~TAZEdgesGraphic();

        /// @brief show TAZ Edges Graphic Modul
        void showTAZEdgesGraphicModul();

        /// @brief hide TAZ Edges Graphic Modul
        void hideTAZEdgesGraphicModul();

        /// @brief update edge colors;
        void updateEdgeColors();

        /// @name FOX-callbacks
        /// @{
        /// @brief Called when the user select one kind of representation
        long onCmdChoosenBy(FXObject* obj, FXSelector, void*);
        /// @}

    protected:
        /// @brief FOX needs this
        TAZEdgesGraphic() {}

    private:
        /// @brief pointer to TAZFrame parent
        GNETAZFrame* myTAZFrameParent;

        /// @brief add radio button "color by source"
        FXRadioButton* myColorBySourceWeight;

        /// @brief add radio button "color by sink"
        FXRadioButton* myColorBySinkWeight;

        /// @brief add radio button "color source + sink"
        FXRadioButton* myColorBySourcePlusSinkWeight;

        /// @brief add radio button "color source - Sink"
        FXRadioButton* myColorBySourceMinusSinkWeight;

        /// @brief vector wit the scale colors
        std::vector<RGBColor> myScaleColors;
    };
    
    /**@brief Constructor
     * @brief parent FXHorizontalFrame in which this GNEFrame is placed
     * @brief viewNet viewNet that uses this GNEFrame
     */
    GNETAZFrame(FXHorizontalFrame* horizontalFrameParent, GNEViewNet* viewNet);

    /// @brief Destructor
    ~GNETAZFrame();

    /// @brief hide TAZ frame
    void hide();

    /**@brief process click over Viewnet
    * @param[in] clickedPosition clicked position over ViewNet
    * @param[in] TAZ clicked TAZ (can be null)
    * @param[in] edge clicked edge (can be null)
    * @return true if something (select TAZ or add edge) was sucefully done
    */
    bool processClick(const Position& clickedPosition, GNETAZ* taz, GNEEdge* edge);

    /// @brief process selection of edges in view net
    void processEdgeSelection(const std::vector<GNEEdge*>& edges);

    /// @brief get drawing mode modul
    DrawingShape* getDrawingShape() const;

    /// @brief get Current TAZ modul
    TAZCurrent* getTAZCurrent() const;

    /// @brief get TAZ Selection Statistics modul
    TAZSelectionStatistics* getTAZSelectionStatistics() const;

protected:
    /**@brief build a shaped element using the drawed shape
     * return true if was sucesfully created
     * @note called when user stop drawing shape
     */
    bool buildShape();
    
    /// @brief add or remove a TAZSource and a TAZSink, or remove it if edge is in the list of TAZ Childs
    bool addOrRemoveTAZMember(GNEEdge *edge);

private:
    /// @brief current TAZ
    TAZCurrent* myTAZCurrent;

    /// @brief TAZ Edges common parameters
    TAZCommonStatistics* myTAZCommonStatistics;

    /// @brief TAZ parameters
    TAZParameters* myTAZParameters;

    /// @brief Netedit parameter
    NeteditAttributes* myNeteditAttributes;

    /// @brief Drawing shape
    DrawingShape* myDrawingShape;

    /// @brief save TAZ Edges
    TAZSaveChanges* myTAZSaveChanges;

    /// @brief TAZ Edges common parameters
    TAZEdgesCommonParameters* myTAZEdgesCommonParameters;

    /// @brief TAZ Edges selection parameters
    TAZSelectionStatistics* myTAZSelectionStatistics;

    /// @brief TAZ Edges Graphic
    TAZEdgesGraphic* myTAZEdgesGraphic;
};


#endif

/****************************************************************************/
