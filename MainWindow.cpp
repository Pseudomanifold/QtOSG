#include "MainWindow.h"
#include "OSGWidget.h"

#include <QDebug>
#include <QMdiSubWindow>
#include <QMenuBar>

MainWindow::MainWindow( QWidget* parent, Qt::WindowFlags flags )
  : QMainWindow( parent, flags ),
    mdiArea_( new QMdiArea( this ) )
{
  QMenuBar* menuBar = this->menuBar();

  QMenu* menu = menuBar->addMenu( "Test" );
  menu->addAction( "Create view", this, SLOT( onCreateView() ) );

  this->setCentralWidget( mdiArea_ );
}

MainWindow::~MainWindow()
{
}

void MainWindow::onCreateView()
{
  OSGWidget* osgWidget     = new OSGWidget( this );
  QMdiSubWindow* subWindow = mdiArea_->addSubWindow( osgWidget );

  subWindow->show();
}
