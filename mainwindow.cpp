#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <deque>
#include "algo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    curent_flag = !curent_flag;
    ApplyIterator();
    curent_flag = !curent_flag;
    std::random_device rd;
    std::mt19937 rand(rd());
    SetRandomGen(rand);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetRandomGen(const std::mt19937 &random_gen)
{
    random_gen_ = random_gen;
}

void MainWindow::ApplyModel() {
    // Реализуйте этот метод.
    if (deque_model_.items.empty()){
        ui->btn_pop_back->setDisabled(true);
        ui->btn_erase->setDisabled(true);
        ui->btn_pop_front->setDisabled(true);
        ui->list_widget->clear();
        ui->list_widget->addItem("end");
        deque_model_.iterator = deque_model_.items.begin();
        ui->txt_size->setText(QString::number(deque_model_.items.size()));
        return;
    }else{
        ui->btn_pop_back->setDisabled(false);
        ui->btn_erase->setDisabled(false);
        ui->btn_pop_front->setDisabled(false);
    }
    auto preserve_iter = deque_model_.iterator;
    ui->list_widget->clear();
    int counter=0;
    for (std::string text : deque_model_.items){
        ui->list_widget->addItem(QString::number(counter++) + ": " + QString::fromStdString(text));
    }
    ui->txt_size->setText(QString::number(deque_model_.items.size()));
    ui->list_widget->addItem("end");
    deque_model_.iterator = preserve_iter;
}

void MainWindow::ApplyIterator()
{
    if(deque_model_.items.end() == deque_model_.iterator){
        ui->pb_edit->setDisabled(true);
        ui->btn_erase->setDisabled(true);
        ui->btn_dec_iterator->setDisabled(true);
        if(deque_model_.items.end() == deque_model_.items.begin()){
        ui->btn_inc_iterator->setDisabled(true);
        }else{
            ui->btn_inc_iterator->setDisabled(false);
        }
        ui->txt_elem_content->setText("");
        int dist = std::distance(deque_model_.items.begin(), deque_model_.iterator);
        ui->list_widget->setCurrentRow(dist);
        return;
    }else if(deque_model_.items.begin() == deque_model_.iterator){
        ui->btn_inc_iterator->setDisabled(true);
        ui->pb_edit->setDisabled(false);
        ui->btn_erase->setDisabled(false);
        ui->btn_dec_iterator->setDisabled(false);
    }else{
        ui->pb_edit->setDisabled(false);
        ui->btn_erase->setDisabled(false);
        ui->btn_dec_iterator->setDisabled(false);
        ui->btn_inc_iterator->setDisabled(false);
    }
    if(deque_model_.items.empty()){
        ui->txt_elem_content->setText("");
        return;
    }
    int dist = std::distance(deque_model_.items.begin(), deque_model_.iterator);
    ui->list_widget->setCurrentRow(dist);
    ui->txt_elem_content->setText(QString::fromStdString(*deque_model_.iterator));
}

void MainWindow::on_btn_pop_back_clicked()
{
    curent_flag = !curent_flag;
    deque_model_.items.pop_back();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
    curent_flag = !curent_flag;
}


void MainWindow::on_btn_push_back_clicked()
{
    curent_flag = !curent_flag;
    deque_model_.items.push_back(ui->txt_elem_content->text().toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
    curent_flag = !curent_flag;
}


void MainWindow::on_btn_clear_clicked()
{
    curent_flag = !curent_flag;
    deque_model_.items.clear();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
    curent_flag = !curent_flag;
}


void MainWindow::on_btn_erase_clicked()
{
    curent_flag = !curent_flag;
    deque_model_.items.erase(deque_model_.iterator);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
    curent_flag = !curent_flag;
}


void MainWindow::on_btn_insert_clicked()
{
    curent_flag = !curent_flag;
    deque_model_.items.insert(deque_model_.iterator, ui->txt_elem_content->text().QString::toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
    curent_flag = !curent_flag;
}


void MainWindow::on_btn_inc_iterator_clicked()
{
    curent_flag = !curent_flag;
    deque_model_.iterator--;
    ApplyIterator();
    curent_flag = !curent_flag;
}


void MainWindow::on_btn_dec_iterator_clicked()
{
    curent_flag = !curent_flag;
    deque_model_.iterator++;
    ApplyIterator();
    curent_flag = !curent_flag;
}


void MainWindow::on_btn_begin_clicked()
{
    curent_flag = !curent_flag;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
    curent_flag = !curent_flag;
}


void MainWindow::on_btn_end_clicked()
{
    curent_flag = !curent_flag;
    deque_model_.iterator = deque_model_.items.end();
    ApplyIterator();
    curent_flag = !curent_flag;
}


void MainWindow::on_pb_edit_clicked()
{
    curent_flag = !curent_flag;
    *deque_model_.iterator = ui->txt_elem_content->text().toStdString();
    ApplyModel();
    ApplyIterator();
    curent_flag = !curent_flag;
}


void MainWindow::on_list_widget_currentRowChanged(int currentRow)
{
    if(curent_flag){
        curent_flag = !curent_flag;
    if(currentRow < 0){
        deque_model_.iterator = deque_model_.items.begin() - currentRow;
    }else if(currentRow == 0){
        deque_model_.iterator = deque_model_.items.begin();
    }else{
        deque_model_.iterator = deque_model_.items.begin() + currentRow;
    }
    ApplyIterator();
    curent_flag = !curent_flag;
    }
}


void MainWindow::on_btn_resize_clicked()
{
    curent_flag = !curent_flag;
    bool ok;
    int res = ui->txt_size->text().toInt(&ok);
    deque_model_.items.resize(res);
    if (ok){
        ApplyModel();
        deque_model_.iterator = deque_model_.items.begin();
        ApplyIterator();
    }
    curent_flag = !curent_flag;
}


void MainWindow::on_pb_find_clicked()
{
    curent_flag = !curent_flag;
    QString text_find = ui->txt_elem_content->text();
    deque_model_.iterator = std::find(deque_model_.items.begin(), deque_model_.items.end(), text_find.toStdString());
    ApplyIterator();
    curent_flag = !curent_flag;
}


void MainWindow::on_pb_count_clicked()
{
    QString text_count = ui->le_count->text();
    int count = std::count(deque_model_.items.begin(), deque_model_.items.end(), text_count.toStdString());
    ui->lbl_count->setText(QString::number(count));
}


void MainWindow::on_pb_min_element_clicked()
{
    curent_flag = !curent_flag;
    deque_model_.iterator = std::min_element(deque_model_.items.begin(), deque_model_.items.end());
    ApplyIterator();
    ApplyIterator();
    curent_flag = !curent_flag;
}


void MainWindow::on_pb_max_element_clicked()
{
    curent_flag = !curent_flag;
    deque_model_.iterator = std::max_element(deque_model_.items.begin(), deque_model_.items.end());
    ApplyIterator();
    ApplyIterator();
    curent_flag = !curent_flag;
}


void MainWindow::on_pb_sort_clicked()
{
    curent_flag = !curent_flag;
    deque_model_.items = MergeSort(deque_model_.items, [](std::string a, std::string b){return a < b;});
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
    curent_flag = !curent_flag;
}


void MainWindow::on_pb_sOrT_clicked()
{
    curent_flag = !curent_flag;
    auto sort = [](std::string a, std::string b){
        for (char &ch : a){
            ch = std::tolower(ch);
        }
        for (char &ch : b){
            ch = std::tolower(ch);
        }
        return a < b;
    };
    deque_model_.items = MergeSort(deque_model_.items, sort);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
    curent_flag = !curent_flag;
}




void MainWindow::on_pb_shuffle_clicked()
{
    curent_flag = !curent_flag;
    std::shuffle(deque_model_.items.begin(), deque_model_.items.end(), random_gen_);
    ApplyModel();
    ApplyIterator();
    curent_flag = !curent_flag;
}


void MainWindow::on_pb_unique_clicked()
{
    curent_flag = !curent_flag;
    if(std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())){
        auto del = std::unique(deque_model_.items.begin(), deque_model_.items.end());
        deque_model_.items.erase(del, deque_model_.items.end());
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
        ApplyIterator();
    }
    curent_flag = !curent_flag;
}


void MainWindow::on_pb_reverse_clicked()
{
    curent_flag = !curent_flag;
    std::reverse(deque_model_.items.begin(), deque_model_.items.end());
    ApplyModel();
    ApplyIterator();
    curent_flag = !curent_flag;
}


void MainWindow::on_pb_tea_clicked()
{
    static std::deque<std::string> tea {
        "Чай Лунцзин",
        "Эрл Грей",
        "Сенча",
        "Пуэр",
        "Дарджилинг",
        "Ассам",
        "Матча",
        "Ганпаудер",
        "Оолонг",
        "Лапсанг Сушонг"
    };
    curent_flag = !curent_flag;
    deque_model_.items = tea;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
    curent_flag = !curent_flag;
}


void MainWindow::on_pb_cakes_clicked()
{
    static std::deque<std::string> cakes {
        "Красный бархат",
        "Наполеон",
        "Медовик",
        "Тирамису",
        "Прага",
        "Чизкейк",
        "Захер",
        "Эстерхази",
        "Морковный торт",
        "Чёрный лес",
    };
    curent_flag = !curent_flag;
    deque_model_.items = cakes;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
    curent_flag = !curent_flag;
}


void MainWindow::on_pb_lower_bound_clicked()
{
    if(!std::is_sorted (deque_model_.items.begin(), deque_model_.items.end())){
        return;
    }

    curent_flag = !curent_flag;

    std::string element = ui->txt_elem_content->text().toStdString();
    deque_model_.iterator = std::lower_bound(deque_model_.items.begin(), deque_model_.items.end(), element);
    ApplyModel();
    ApplyIterator();

    curent_flag = !curent_flag;
}


void MainWindow::on_pb_upper_bound_clicked()
{
    if(!std::is_sorted (deque_model_.items.begin(), deque_model_.items.end())){
        return;
    }

    curent_flag = !curent_flag;

    std::string element = ui->txt_elem_content->text().toStdString();
    deque_model_.iterator = std::upper_bound(deque_model_.items.begin(), deque_model_.items.end(), element);
    ApplyModel();
    ApplyIterator();

    curent_flag = !curent_flag;
}


void MainWindow::on_btn_push_front_clicked()
{
    curent_flag = !curent_flag;
    deque_model_.items.push_front(ui->txt_elem_content->text().toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
    curent_flag = !curent_flag;
}


void MainWindow::on_btn_pop_front_clicked()
{
    curent_flag = !curent_flag;
    deque_model_.items.pop_front();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
    ApplyIterator();
    curent_flag = !curent_flag;
}


