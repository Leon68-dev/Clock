#include <QApplication>
#include "src/MainWindow.h" // ¬казуЇмо шл€х до папки src

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}