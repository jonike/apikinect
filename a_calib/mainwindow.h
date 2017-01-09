/*
 * Copyright (c) 2017  Gabriel Alzamora.
 *
 * This code is licensed to you under the terms of the
 * GNU General Public License. See LICENSE file for the
 * text of the license, or the following URL:
 * https://www.gnu.org/licenses/gpl.html
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "maincalib.h"

class QGraphicsScene;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void go(int kindex);
    void stop(int kindex);
    void rb_video_toggled(bool checked);

public slots:
    void paintVideo();
    void paintDepth();
    void paintIR();

private slots:
    void init();
    void putKcombo();
    void initConnects();
    void format();
    //gui slots
    void on_combo_activated(int index);
    void on_pb_go_clicked();

private:
    Ui::MainWindow *ui;
    MainCalib *calib;
    QGraphicsScene *scene;
    QImage *img;
    int comboIndex;
    uint16_t depth_mm[2048];
};

#endif // MAINWINDOW_H
