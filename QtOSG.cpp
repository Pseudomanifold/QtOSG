#include "MainWindow.h"

#include <QApplication>
#include <QSurfaceFormat>

int main( int argc, char** argv )
{
  QApplication application( argc, argv );

  QSurfaceFormat format;
  format.setVersion(2, 1);
  format.setProfile( QSurfaceFormat::CompatibilityProfile );

  QSurfaceFormat::setDefaultFormat(format);

  MainWindow mainWindow;
  mainWindow.show();

  return( application.exec() );
}
