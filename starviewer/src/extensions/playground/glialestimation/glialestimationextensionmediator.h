/***************************************************************************
 *   Copyright (C) 2005-2006 by Grup de Gràfics de Girona                  *
 *   http://iiia.udg.es/GGG/index.html?langu=uk                            *
 *                                                                         *
 *   Universitat de Girona                                                 *
 ***************************************************************************/
#ifndef UDGGLIALESTIMATIONEXTENSIONMEDIATOR_H
#define UDGGLIALESTIMATIONEXTENSIONMEDIATOR_H

#include "extensionmediator.h"

#include "installextension.h"
#include "qglialestimationextension.h"

namespace udg {

/**
    @author Grup de Gràfics de Girona  ( GGG ) <vismed@ima.udg.es>
*/
class GlialEstimationExtensionMediator : public ExtensionMediator
{
Q_OBJECT
public:
    GlialEstimationExtensionMediator(QObject *parent = 0);

    ~GlialEstimationExtensionMediator();

    virtual bool initializeExtension(QWidget* extension, const ExtensionContext &extensionContext);

    virtual DisplayableID getExtensionID() const;
};

static InstallExtension<QGlialEstimationExtension, GlialEstimationExtensionMediator> registerGlialEstimationExtension;

}

#endif