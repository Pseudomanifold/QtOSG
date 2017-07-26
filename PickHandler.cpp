#include "PickHandler.h"

#include <osg/io_utils>

#include <osgUtil/IntersectionVisitor>
#include <osgUtil/LineSegmentIntersector>

#include <osgViewer/Viewer>

#include <iostream>

PickHandler::PickHandler( double devicePixelRatio )
  : devicePixelRatio_( devicePixelRatio )
{
}

PickHandler::~PickHandler()
{
}

bool PickHandler::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )
{
  if( ea.getEventType() != osgGA::GUIEventAdapter::RELEASE &&
      ea.getButton()    != osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON )
  {
    return false;
  }

  osgViewer::View* viewer = dynamic_cast<osgViewer::View*>( &aa );

  if( viewer )
  {
    osgUtil::LineSegmentIntersector* intersector
        = new osgUtil::LineSegmentIntersector( osgUtil::Intersector::WINDOW, ea.getX() * devicePixelRatio_, ea.getY() * devicePixelRatio_ );

    osgUtil::IntersectionVisitor iv( intersector );

    osg::Camera* camera = viewer->getCamera();
    if( !camera )
      return false;

    camera->accept( iv );

    if( !intersector->containsIntersections() )
      return false;

    auto intersections = intersector->getIntersections();

    std::cout << "Got " << intersections.size() << " intersections:\n";

    for( auto&& intersection : intersections )
      std::cout << "  - Local intersection point = " << intersection.localIntersectionPoint << "\n";
  }

  return true;
}
