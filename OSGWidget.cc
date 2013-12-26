#include "OSGWidget.hh"

#include <osg/Camera>

#include <osg/Geode>
#include <osg/Shape>
#include <osg/ShapeDrawable>

#include <osgGA/EventQueue>

#include <osgViewer/View>
#include <osgViewer/ViewerEventHandlers>

#include <stdexcept>

OSGWidget::OSGWidget( QWidget* parent,
                      const QGLWidget* shareWidget,
                      Qt::WindowFlags f )
  : QGLWidget( parent,
               shareWidget,
               f ),
    graphicsWindow_( new osgViewer::GraphicsWindowEmbedded( this->x(), this->y(),
                                                            this->width(), this->height() ) ),
    viewer_( new osgViewer::CompositeViewer )
{
  osg::Sphere* sphere    = new osg::Sphere( osg::Vec3( 0.f, 0.f, 0.f ), 0.25f );
  osg::ShapeDrawable* sd = new osg::ShapeDrawable( sphere );
  sd->setColor( osg::Vec4( 1.f, 0.f, 0.f, 1.f ) );

  osg::Geode* geode = new osg::Geode;
  geode->addDrawable( sd );

  osg::Camera* camera = new osg::Camera;
  camera->setViewport( 0, 0, this->width(), this->height() );
  camera->setClearColor( osg::Vec4( 0.f, 0.f, 1.f, 1.f ) );
  camera->setProjectionMatrixAsOrtho2D( -1.0, 1.0, -1.0, 1.0 );
  camera->setGraphicsContext( graphicsWindow_ );

  osgViewer::View* view = new osgViewer::View;
  view->setCamera( camera );
  view->setSceneData( geode );
  view->addEventHandler( new osgViewer::StatsHandler );

  viewer_->addView( view );
  viewer_->setThreadingModel( osgViewer::CompositeViewer::SingleThreaded );
}

OSGWidget::~OSGWidget()
{
}

void OSGWidget::paintGL()
{
  viewer_->frame();
}

void OSGWidget::resizeGL( int width, int height )
{
  this->getEventQueue()->windowResize( this->x(), this->y(), width, height );
  graphicsWindow_->resized( this->x(), this->y(), width, height );
}

void OSGWidget::keyPressEvent( QKeyEvent* event )
{
  QString keyString   = event->text();
  const char* keyData = keyString.toAscii().data();

  this->getEventQueue()->keyPress( osgGA::GUIEventAdapter::KeySymbol( *keyData ) );
}

void OSGWidget::keyReleaseEvent( QKeyEvent* event )
{
  QString keyString   = event->text();
  const char* keyData = keyString.toAscii().data();

  this->getEventQueue()->keyRelease( osgGA::GUIEventAdapter::KeySymbol( *keyData ) );
}

void OSGWidget::mouseMoveEvent( QMouseEvent* event )
{
  this->getEventQueue()->mouseMotion( static_cast<float>( event->x() ),
                                      static_cast<float>( event->y() ) );
}

void OSGWidget::mousePressEvent( QMouseEvent* event )
{
  // 1 = left mouse button
  // 2 = middle mouse button
  // 3 = right mouse button

  unsigned int button = 0;

  switch( event->button() )
  {
  case Qt::LeftButton:
    button = 1;
    break;

  case Qt::MiddleButton:
    button = 2;
    break;

  case Qt::RightButton:
    button = 3;
    break;

  default:
    break;
  }

  this->getEventQueue()->mouseButtonPress( static_cast<float>( event->x() ),
                                           static_cast<float>( event->y() ),
                                           button );
}

void OSGWidget::mouseReleaseEvent(QMouseEvent* event)
{
  // 1 = left mouse button
  // 2 = middle mouse button
  // 3 = right mouse button

  unsigned int button = 0;

  switch( event->button() )
  {
  case Qt::LeftButton:
    button = 1;
    break;

  case Qt::MiddleButton:
    button = 2;
    break;

  case Qt::RightButton:
    button = 3;
    break;

  default:
    break;
  }

  this->getEventQueue()->mouseButtonRelease( static_cast<float>( event->x() ),
                                             static_cast<float>( event->y() ),
                                             button );
}

osgGA::EventQueue* OSGWidget::getEventQueue() const
{
  osgGA::EventQueue* eventQueue = graphicsWindow_->getEventQueue();

  if( eventQueue )
    return( eventQueue );
  else
    throw( std::runtime_error( "Unable to obtain valid event queue") );
}
