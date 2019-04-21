#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsRectItem>
#include <QImage>
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pix_map(":/pic/map.png")
//    , pix_map("/Users/sam/Downloads/nan.jpeg")
{
    ui->setupUi(this);
    setWindowTitle("Demo");
    //        QImage image_map("/Users/sam/Pictures/map.png");

    //    image_map.scaledToHeight(1000);
    scene = new QGraphicsScene(0, 0, 4000, 6000, ui->graphicsView);
    pixmapItem = new QGraphicsPixmapItem(pix_map);
    pixmapItem->setZValue(-1);
    map_is_shown = true;
    scene->addItem(pixmapItem);
    //    QBrush brush(pix_map);
    //    scene->setBackgroundBrush(brush);
    model.setScene(scene);
    model.setOutputBox(ui->outputBox);

    ui->graphicsView->setScene(scene);
    //    ui->graphicsView->setBackgroundBrush(brush);
    ui->graphicsView->setCursor(Qt::CrossCursor); //设置鼠标
    ui->graphicsView->setMouseTracking(true); //
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    ui->radio_sel_btn->setChecked(true);
    ui->slider->setValue(0);
    ui->value_label->setText("0");
    ui->slider->setDisabled(true);
    QObject::connect(ui->graphicsView, SIGNAL(MC(QPoint)), this, SLOT(on_mouseClicked(QPoint)));
    QObject::connect(ui->graphicsView, SIGNAL(MC(QPoint)),
        this, SLOT(on_mouseMoved(QPoint)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connect_node(QGraphicsItem* item1, QGraphicsItem* item2)
{

    Node* node1 = model.mapToNode(item1);
    Node* node2 = model.mapToNode(item2);

    if (node1 && node2)
        model.connect_node(node1, node2);
}

void MainWindow::on_mouseClicked(QPoint point)
{
    QPointF pointScene = ui->graphicsView->mapToScene(point); //转换到Scene坐标
    if (current_mode == MODE_CONNECT) {

        QGraphicsItem* item = nullptr;
        item = scene->itemAt(pointScene, ui->graphicsView->transform()); //获取光标下的绘图项

        if (item && item->type() == QGraphicsPixmapItem::Type && item->type() == QGraphicsLineItem::Type) {
            item = nullptr;
        }
        if (item != nullptr) //有绘图项
        {
            if (current_selected != nullptr) {
                connect_node(current_selected, item);
            }
        }

        current_selected = item;

    } else if (current_mode == MODE_INSERT) {
        Node* node = new Node(pointScene);
        model.addNode(node);
    } else if (current_mode == MODE_SELECT) {
        QGraphicsItem* item = nullptr;
        item = scene->itemAt(pointScene, ui->graphicsView->transform()); //获取光标下的绘图项

        if (item && item->type() == QGraphicsPixmapItem::Type && item->type() == QGraphicsLineItem::Type) {
            item = nullptr;
        }
        current_selected = item;
        Node* n = model.mapToNode(item);
        if (n != nullptr) {
            ui->slider->setDisabled(false);
            ui->slider->setValue(n->getWeight());
            ui->locationLabel->setText(QString("source %1").arg(n->id));
        } else {
            ui->slider->setValue(0);
            ui->slider->setDisabled(true);
            ui->locationLabel->setText(QString("Map"));
        }
    }
}

void MainWindow::on_mouseMoved(QPoint point)
{

    //    QPointF pointScene = ui->graphicsView->mapToScene(point); //转换到Scene坐标
    //    if (current_mode == MODE_CONNECT) {

    //    } else if (current_mode == MODE_INSERT) {

    //    } else if (current_mode == MODE_SELECT) {
    //    }
}

//void MainWindow::on_insertBtn_clicked()
//{
//    current_mode = MODE_INSERT;
//    current_selected = nullptr;
//    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(0, 0, 20, 20);
//    item->setFlags(QGraphicsItem::ItemIsMovable
//        | QGraphicsItem::ItemIsSelectable
//        | QGraphicsItem::ItemIsFocusable);
//    item->setBrush(QBrush(Qt::NoBrush));
//    item->setPos(0, 0);
//    item->setZValue(frontZ++);

//    item->setData(ItemId, ID++);

//    scene->addItem(item);
//    scene->clearSelection();
//}

//void MainWindow::on_connectBtn_clicked()
//{
//    if (current_mode == MODE_CONNECT) {
//        current_mode = MODE_INSERT;
//        current_selected = nullptr;
//    } else
//        current_mode = MODE_CONNECT;
//}

void MainWindow::on_rad_ins_btn_clicked()
{
    current_mode = MODE_INSERT;
    current_selected = nullptr;
    ui->slider->setDisabled(true);
}

void MainWindow::on_radio_sel_btn_clicked()
{
    current_mode = MODE_SELECT;
    current_selected = nullptr;
    ui->slider->setDisabled(true);
}

void MainWindow::on_rad_cnc_btn_clicked()
{
    current_mode = MODE_CONNECT;
    current_selected = nullptr;
    ui->slider->setDisabled(true);
}

void MainWindow::on_calculateBtn_clicked()
{
    model.calculate();
}

void MainWindow::on_slider_valueChanged(int value)
{
    Node* n = model.mapToNode(current_selected);
    if (n) {
        n->setWeight(value);
        ui->value_label->setText(QString::number(value));
    } else {
        ui->value_label->setText(QString::number(0));
    }
}

void MainWindow::on_pushButton_clicked()
{
    model.save_to_file();
}

void MainWindow::on_pushButton_2_clicked()
{
    model.init_from_file();
}

void MainWindow::on_zoom_in_btn_clicked()
{
    double rate = 1 / 0.9;
    ui->graphicsView->scale(rate, rate);
}

void MainWindow::on_zoom_out_btn_clicked()
{
    double rate = 0.9;
    ui->graphicsView->scale(rate, rate);
}

void MainWindow::on_hide_btn_clicked()
{
    if (map_is_shown)
        scene->removeItem(pixmapItem);
    map_is_shown = false;
}

void MainWindow::on_show_btn_clicked()
{
    if (map_is_shown)
        return;
    scene->addItem(pixmapItem);
    map_is_shown = true;
}

void MainWindow::on_speedSlider_valueChanged(int value)
{
    model.setWaitTime(50 - value);
    //    ui->outputBox->append(QString::number(value));
}
