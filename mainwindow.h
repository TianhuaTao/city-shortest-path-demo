#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "model.h"
#include "mygraphicslineitem.h"
#include "node.h"
#include "road.h"
#include <QMainWindow>
#include <QMap>
#include <mygraphicsview.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    static const int ItemId = 1; //绘图项自定义数据的key
    static const int ItemDesciption = 2; //绘图项自定义数据的key
    static const int MODE_INSERT = 4000;
    static const int MODE_CONNECT = 4001;
    static const int MODE_SELECT = 4002;
    static const int START_POINT = 5000;
    static const int END_POINT = 5001;
    static const int LINES = 6000;

private:
    Ui::MainWindow* ui;
    QGraphicsScene* scene;
    int frontZ = 0;
    int ID = 0;
    int current_mode = MODE_SELECT;
    bool map_is_shown;
    QGraphicsItem* current_selected = nullptr;
    void connect_node(QGraphicsItem* item1, QGraphicsItem* item2);
    QMap<int, QVector<QGraphicsLineItem*>> id_to_lines;
    Model model;
    QPixmap pix_map;
    QGraphicsPixmapItem* pixmapItem;
private slots:

    void on_mouseClicked(QPoint point); //鼠标单击
    void on_mouseMoved(QPoint point);
    //    void on_insertBtn_clicked();
    //    void on_connectBtn_clicked();
    void on_rad_ins_btn_clicked();
    void on_radio_sel_btn_clicked();
    void on_rad_cnc_btn_clicked();
    void on_calculateBtn_clicked();
    void on_slider_valueChanged(int value);
    //    void on_slider_sliderMoved(int position);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_zoom_in_btn_clicked();

    void on_zoom_out_btn_clicked();
    void on_hide_btn_clicked();
    void on_show_btn_clicked();
    void on_speedSlider_valueChanged(int value);
};

#endif // MAINWINDOW_H
