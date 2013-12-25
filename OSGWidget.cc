#include "OSGWidget.hh"

#include <osg/Camera>

#include <osg/Geode>
#include <osg/Shape>
#include <osg/ShapeDrawable>

#include <osgViewer/View>
#include <osgViewer/ViewerEventHandlers>

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

void OSGWidget::resizeGL(int width, int height)
{
  graphicsWindow_->getEventQueue()->windowResize( this->x(), this->y(), width, height );
  graphicsWindow_->resized( this->x(), this->y(), width, height );
}

void OSGWidget::keyPressEvent(QKeyEvent* event)
{
  graphicsWindow_->getEventQueue()->keyPress( osgGA::GUIEventAdapter::KeySymbol( *event->text().toAscii().data() ) );
}

void OSGWidget::keyReleaseEvent(QKeyEvent* event)
{
  graphicsWindow_->getEventQueue()->keyRelease( osgGA::GUIEventAdapter::KeySymbol( *event->text().toAscii().data() ) );
}
