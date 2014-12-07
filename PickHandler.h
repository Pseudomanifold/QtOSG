#ifndef PickHandler_h__
#define PickHandler_h__

#include <osgGA/GUIEventHandler>

class PickHandler : public osgGA::GUIEventHandler
{
public:
  virtual ~PickHandler();

  virtual bool handle( const osgGA::GUIEventAdapter&  ea,
                             osgGA::GUIActionAdapter& aa );

};

#endif
