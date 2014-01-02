#ifndef MainWindow_hh__
#define MainWindow_hh__

#include <QMainWindow>
#include <QMdiArea>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow( QWidget* parent = 0, Qt::WindowFlags flags = 0 );
  ~MainWindow();

private slots:
  void onCreate2DView();
  void onCreate3DView();

private:
  QMdiArea* mdiArea_;
};

#endif
