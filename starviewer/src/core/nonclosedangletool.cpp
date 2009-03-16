/***************************************************************************
 *   Copyright (C) 2005-2007 by Grup de Gràfics de Girona                  *
 *   http://iiia.udg.es/GGG/index.html?langu=uk                            *
 *                                                                         *
 *   Universitat de Girona                                                 *
 ***************************************************************************/
#include "nonclosedangletool.h"
#include "q2dviewer.h"
#include "logging.h"
#include "drawer.h"
#include "drawerline.h"
#include "drawertext.h"
#include "mathtools.h"
//vtk
#include <vtkRenderWindowInteractor.h>
#include <vtkCommand.h>

namespace udg {

NonClosedAngleTool::NonClosedAngleTool( QViewer *viewer, QObject *parent )
 : Tool(viewer, parent)
{
    m_toolName = "NonClosedAngleTool";
    m_hasSharedData = false;

    m_2DViewer = qobject_cast<Q2DViewer *>( viewer );
    if( !m_2DViewer )
        DEBUG_LOG(QString("El casting no ha funcionat!!! És possible que viewer no sigui un Q2DViewer!!!-> ")+ viewer->metaObject()->className() );

    m_firstLine = NULL;
    m_secondLine = NULL;
    m_state = NONE;
    m_lineState = NO_POINTS;
}

NonClosedAngleTool::~NonClosedAngleTool()
{
    if ( m_state != NONE )
    {
        if ( m_firstLine )
            delete m_firstLine;
        if ( m_secondLine )
            delete m_secondLine;
    }
}

void NonClosedAngleTool::handleEvent( long unsigned eventID )
{
    switch( eventID )
    {
        case vtkCommand::LeftButtonPressEvent:

            if( m_2DViewer->getInput() )
            {
                if ( m_2DViewer->getInteractor()->GetRepeatCount() == 0 )
                {
                    this->annotateLinePoints();

                    if ( m_state == SECOND_LINE_FIXED )
                    {
                        computeAngle();
                        //Acabem les línies
                        m_firstLine = NULL;
                        m_secondLine = NULL;

                        //Restaurem m_state
                        m_state = NONE;
                    }

                    m_2DViewer->getDrawer()->refresh();
                }
            }
        break;

        case vtkCommand::MouseMoveEvent:

            if( m_firstLine && m_state == NONE )
                this->simulateLine(m_firstLine);
            else if ( m_secondLine && m_state == FIRST_LINE_FIXED )
                this->simulateLine(m_secondLine);

            m_2DViewer->getDrawer()->refresh();

        break;
    }
}

void NonClosedAngleTool::annotateLinePoints()
{
    DrawerLine *line;

    //creem primera o segona línies
    if ( ( m_state == NONE && m_lineState == NO_POINTS ) ||
        ( m_state == FIRST_LINE_FIXED && m_lineState == NO_POINTS ) )
        line = new DrawerLine;
    else if ( m_state == NONE )
        line = m_firstLine;
    else
        line = m_secondLine;

    double position[4];
    double computed[3];

    //capturem l'event de clic esquerre
    int *xy = m_2DViewer->getEventPosition();

    m_2DViewer->computeDisplayToWorld( m_2DViewer->getRenderer() , xy[0], xy[1], 0, position );
    computed[0] = position[0];
    computed[1] = position[1];
    computed[2] = position[2];

    //afegim el punt
    if( m_lineState == NO_POINTS )
    {
        line->setFirstPoint( computed );
        line->setSecondPoint( computed );
        m_lineState = FIRST_POINT;

        if ( m_state == NONE )
            m_firstLine = line;
        else
            m_secondLine = line;

        m_2DViewer->getDrawer()->draw( line , m_2DViewer->getView(), m_2DViewer->getCurrentSlice() );
    }
    else
    {
        line->setSecondPoint( computed );

        line->update( DrawerPrimitive::VTKRepresentation );

        m_lineState = NO_POINTS;

        if ( m_state == NONE )
            m_state = FIRST_LINE_FIXED;
        else
            m_state = SECOND_LINE_FIXED;
    }
}

void NonClosedAngleTool::simulateLine(DrawerLine *line)
{
    double position[4];
    double computed[3];

    //capturem l'event de clic esquerre
    int *xy = m_2DViewer->getEventPosition();

    m_2DViewer->computeDisplayToWorld( m_2DViewer->getRenderer() , xy[0], xy[1], 0, position );
    computed[0] = position[0];
    computed[1] = position[1];
    computed[2] = position[2];

    line->setSecondPoint( computed );

    //Actualitzem viewer
    line->update( DrawerPrimitive::VTKRepresentation );
}

void NonClosedAngleTool::computeAngle()
{
    if ( !m_middleLine )
    {
        m_middleLine = new DrawerLine;
    }
    m_middleLine->setLinePattern(DrawerPrimitive::DiscontinuousLinePattern);

    double *p1 = m_firstLine->getFirstPoint();
    double *p2 = m_firstLine->getSecondPoint();
    double *p3 = m_secondLine->getFirstPoint();
    double *p4 = m_secondLine->getSecondPoint();

    double *vd1, *vd2;

    double *intersection;
    int state;

    intersection = MathTools::intersectionPoint3DLines(p1,p2,p3,p4,state);

    double dist1, dist2, dist3, dist4;
    dist1 = MathTools::getDistance3D(intersection, p1);
    dist2 = MathTools::getDistance3D(intersection, p2);
    dist3 = MathTools::getDistance3D(intersection, p3);
    dist4 = MathTools::getDistance3D(intersection, p4);

    if ( dist1 <= dist2 )
    {
        if ( dist3 <= dist4 )
        {
            vd1 = MathTools::directorVector( p1, intersection );
            vd2 = MathTools::directorVector( p3, intersection );
            m_middleLine->setFirstPoint(p1);
            m_middleLine->setSecondPoint(p3);
        }
        else
        {
            vd1 = MathTools::directorVector( p1, intersection );
            vd2 = MathTools::directorVector( p4, intersection );
            m_middleLine->setFirstPoint(p1);
            m_middleLine->setSecondPoint(p4);
        }
    }
    else
    {
        if ( dist3 <= dist4 )
        {
            vd1 = MathTools::directorVector( p2, intersection );
            vd2 = MathTools::directorVector( p3, intersection );
            m_middleLine->setFirstPoint(p2);
            m_middleLine->setSecondPoint(p3);
        }
        else
        {
            vd1 = MathTools::directorVector( p2, intersection );
            vd2 = MathTools::directorVector( p4, intersection );
            m_middleLine->setFirstPoint(p2);
            m_middleLine->setSecondPoint(p4);
        }
    }

    //dibuixem la línia auxiliar
    m_2DViewer->getDrawer()->draw( m_middleLine , m_2DViewer->getView(), m_2DViewer->getCurrentSlice() );

    for (int i = 0; i < 3; i++)
    {
        if ( fabs( vd1[i] ) < 0.0001 )
            vd1[i] = 0.0;

        if ( fabs( vd2[i] ) < 0.0001 )
            vd2[i] = 0.0;
    }

    double angle = MathTools::angleInDegrees( vd1, vd2 );

    DrawerText * text = new DrawerText;

    if ( state == MathTools::PARALLEL )
        text->setText( tr("0.0 degrees") );
    else if ( state == MathTools::SKEW )   //Won't occur
        text->setText( tr("Skew lines.") );
    else
        text->setText( tr("%1 degrees").arg( angle,0,'f',1) );


    textPosition( m_middleLine->getFirstPoint(), m_middleLine->getSecondPoint(), text );

    text->update( DrawerPrimitive::VTKRepresentation );
    m_2DViewer->getDrawer()->draw( text , m_2DViewer->getView(), m_2DViewer->getCurrentSlice() );
    m_2DViewer->getDrawer()->refresh();

    m_middleLine = NULL;
}

void NonClosedAngleTool::textPosition( double *p1, double *p2, DrawerText *angleText )
{
    double position[3];
    int horizontalCoord, verticalCoord;

    switch( m_2DViewer->getView() )
    {
        case Q2DViewer::Axial:
            horizontalCoord = 0;
            verticalCoord = 1;
            break;

        case Q2DViewer::Sagital:
            horizontalCoord = 1;
            verticalCoord = 2;
            break;

        case Q2DViewer::Coronal:
            horizontalCoord = 0;
            verticalCoord = 2;
            break;
    }

    position[horizontalCoord] = ( p1[horizontalCoord] + p2[horizontalCoord] ) / 2.0;
    position[verticalCoord] = ( p1[verticalCoord] + p2[verticalCoord] ) / 2.0;

    angleText->setAttatchmentPoint(position);

}

}
