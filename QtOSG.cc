#include "OSGWidget.hh"

#include <QApplication>

int main( int argc, char** argv )
{
  QApplication application( argc, argv );

  OSGWidget* widget = new OSGWidget( 0 );
  widget->show();

  return( application.exec() );
}
