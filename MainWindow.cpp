#include "MainWindow.h"
#include "OSGWidget.h"

#include <QDebug>
#include <QMenuBar>

MainWindow::MainWindow( QWidget* parent, Qt::WindowFlags flags )
  : QMainWindow( parent, flags ),
    mdiArea_( new QMdiArea( this ) )
{
  QMenuBar* menuBar = this->menuBar();

  menuBar->addAction( "Create 2D view", this, SLOT( onCreate2DView() ) );
  menuBar->addAction( "Create 3D view", this, SLOT( onCreate3DView() ) );

  this->setCentralWidget( mdiArea_ );
}

MainWindow::~MainWindow()
{
}

void MainWindow::onCreate2DView()
{
  OSGWidget* osgWidget     = new OSGWidget( this );
  QMdiSubWindow* subWindow = mdiArea_->addSubWindow( osgWidget );

  subWindow->show();
}

void MainWindow::onCreate3DView()
{
  qDebug() << __PRETTY_FUNCTION__
           << ":"
           << "Not yet implemented";
}
