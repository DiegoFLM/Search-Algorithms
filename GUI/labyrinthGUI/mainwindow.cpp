#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Node.h"
#include "Handler.h"
#include <iostream>
#include <sstream>
#include <fstream>


#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <QDataStream>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QFileInfo>




bool createFile(QString path){
    QFile file(path);
    if ( !file.open(QIODevice::WriteOnly) ){
        qWarning() << file.errorString();
        return false;
    }

    QDataStream stream(&file);

    file.close();
}


void readFile( QString path ){
    QFile file(path);
    if ( !file.open(QIODevice::ReadOnly) ){
        qWarning() << file.errorString();
        return;
    }

    QDataStream stream(&file);

    QString banner;
    stream >> banner;

    qInfo() << "Banner: " << banner;


    file.close();
}

/*
0 si es una casilla libre
1 si es un muro
2 si el punto de inicio
3 si es la nave 1
4 si es la nave 2
5 si es un ítem
6 si es una casilla con aceite
*/


/*
int map[10][10] ={{0, 0, 0, 0, 0, 5, 1, 1, 4, 0},
                    {0, 1, 1, 1, 1, 0, 1, 1, 1, 0},
                    {0, 0, 0, 6, 6, 0, 0, 0, 0, 0},
                    {1, 6, 1, 1, 1, 1, 0, 1, 1, 6},
                    {1, 6, 1, 1, 1, 1, 0, 1, 1, 6},
                    {1, 6, 1, 0, 0, 0, 0, 0, 0, 3},
                    {1, 6, 1, 0, 1, 1, 1, 1, 0, 1},
                    {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 1, 0, 1, 0, 1, 1, 1, 1},
                    {1, 0, 0, 0, 6, 6, 6, 0, 0, 5},
                    };*/

//Declarations
int const L = 10;
int readMap[L][L];

QLabel* labelsList[10][10];


int initialRobotsPosition[2];

int shipsFuel [2]= {10, 20};

bool foundItems[2] = {false, false};
bool drivingShip[2] = {false, false};





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timeLapse = new QTimer(this);
    connect(timeLapse, SIGNAL(timeout()), this, SLOT(onTimeEnd()));


    labelsList[0][0] = ui->label;
    labelsList[0][1] = ui->label_2;
    labelsList[0][2] = ui->label_3;
    labelsList[0][3] = ui->label_4;
    labelsList[0][4] = ui->label_5;
    labelsList[0][5] = ui->label_6;
    labelsList[0][6] = ui->label_7;
    labelsList[0][7] = ui->label_8;
    labelsList[0][8] = ui->label_9;
    labelsList[0][9] = ui->label_10;

    labelsList[1][0] = ui->label_11;
    labelsList[1][1] = ui->label_12;
    labelsList[1][2] = ui->label_13;
    labelsList[1][3] = ui->label_14;
    labelsList[1][4] = ui->label_15;
    labelsList[1][5] = ui->label_16;
    labelsList[1][6] = ui->label_17;
    labelsList[1][7] = ui->label_18;
    labelsList[1][8] = ui->label_19;
    labelsList[1][9] = ui->label_20;

    labelsList[2][0] = ui->label_21;
    labelsList[2][1] = ui->label_22;
    labelsList[2][2] = ui->label_23;
    labelsList[2][3] = ui->label_24;
    labelsList[2][4] = ui->label_25;
    labelsList[2][5] = ui->label_26;
    labelsList[2][6] = ui->label_27;
    labelsList[2][7] = ui->label_28;
    labelsList[2][8] = ui->label_29;
    labelsList[2][9] = ui->label_30;

    labelsList[3][0] = ui->label_31;
    labelsList[3][1] = ui->label_32;
    labelsList[3][2] = ui->label_33;
    labelsList[3][3] = ui->label_34;
    labelsList[3][4] = ui->label_35;
    labelsList[3][5] = ui->label_36;
    labelsList[3][6] = ui->label_37;
    labelsList[3][7] = ui->label_38;
    labelsList[3][8] = ui->label_39;
    labelsList[3][9] = ui->label_40;

    labelsList[4][0] = ui->label_41;
    labelsList[4][1] = ui->label_42;
    labelsList[4][2] = ui->label_43;
    labelsList[4][3] = ui->label_44;
    labelsList[4][4] = ui->label_45;
    labelsList[4][5] = ui->label_46;
    labelsList[4][6] = ui->label_47;
    labelsList[4][7] = ui->label_48;
    labelsList[4][8] = ui->label_49;
    labelsList[4][9] = ui->label_50;

    labelsList[5][0] = ui->label_51;
    labelsList[5][1] = ui->label_52;
    labelsList[5][2] = ui->label_53;
    labelsList[5][3] = ui->label_54;
    labelsList[5][4] = ui->label_55;
    labelsList[5][5] = ui->label_56;
    labelsList[5][6] = ui->label_57;
    labelsList[5][7] = ui->label_58;
    labelsList[5][8] = ui->label_59;
    labelsList[5][9] = ui->label_60;

    labelsList[6][0] = ui->label_61;
    labelsList[6][1] = ui->label_62;
    labelsList[6][2] = ui->label_63;
    labelsList[6][3] = ui->label_64;
    labelsList[6][4] = ui->label_65;
    labelsList[6][5] = ui->label_66;
    labelsList[6][6] = ui->label_67;
    labelsList[6][7] = ui->label_68;
    labelsList[6][8] = ui->label_69;
    labelsList[6][9] = ui->label_70;

    labelsList[7][0] = ui->label_71;
    labelsList[7][1] = ui->label_72;
    labelsList[7][2] = ui->label_73;
    labelsList[7][3] = ui->label_74;
    labelsList[7][4] = ui->label_75;
    labelsList[7][5] = ui->label_76;
    labelsList[7][6] = ui->label_77;
    labelsList[7][7] = ui->label_78;
    labelsList[7][8] = ui->label_79;
    labelsList[7][9] = ui->label_80;

    labelsList[8][0] = ui->label_81;
    labelsList[8][1] = ui->label_82;
    labelsList[8][2] = ui->label_83;
    labelsList[8][3] = ui->label_84;
    labelsList[8][4] = ui->label_85;
    labelsList[8][5] = ui->label_86;
    labelsList[8][6] = ui->label_87;
    labelsList[8][7] = ui->label_88;
    labelsList[8][8] = ui->label_89;
    labelsList[8][9] = ui->label_90;

    labelsList[9][0] = ui->label_91;
    labelsList[9][1] = ui->label_92;
    labelsList[9][2] = ui->label_93;
    labelsList[9][3] = ui->label_94;
    labelsList[9][4] = ui->label_95;
    labelsList[9][5] = ui->label_96;
    labelsList[9][6] = ui->label_97;
    labelsList[9][7] = ui->label_98;
    labelsList[9][8] = ui->label_99;
    labelsList[9][9] = ui->label_100;




    std::string rawPosition;

/*    std::ifstream mapFile;
    mapFile.open("map.txt"//, std::ios::in
                 );  */

    QString qstr;


    QFile qfile_map("/home/diegoflm/Documents/VU/IngSistemas/MateriasYTemas/Semestre6/AI/Project/pCode/Pruebax5.txt");


    qfile_map.open(QIODevice::ReadOnly /*| QIODevice::Text*/);
    //QDataStream in(&qfile_map);
    QTextStream in(&qfile_map);


    //int readMap[L][L];
    readMap[0][0] = 22;

    for (int r = 0; r < 10; r++){
        QString superVar = in.readLine();
        QStringList fields = superVar.split(" ");

        for (int c = 0; c < 10; c++){

            if(fields[c].toInt() == 1){
                labelsList[r][c]
                        ->setPixmap( QPixmap("/home/diegoflm/Documents/VU/IngSistemas/MateriasYTemas/Semestre6/AI/Project/pCode/GUI/labyrinthGUI/BrickWall.png") );

            }else if(fields[c].toInt() == 3 || fields[c].toInt() == 4 ){
                labelsList[r][c]
                        ->setPixmap( QPixmap("/home/diegoflm/Documents/VU/IngSistemas/MateriasYTemas/Semestre6/AI/Project/pCode/GUI/labyrinthGUI/spaceShip.png") );
            }else if(fields[c].toInt() == 6 ){
                labelsList[r][c]
                        ->setPixmap( QPixmap("/home/diegoflm/Documents/VU/IngSistemas/MateriasYTemas/Semestre6/AI/Project/pCode/GUI/labyrinthGUI/lava.png") );
            } else{
                labelsList[r][c]->setText( fields[c] );
            }

            readMap[r][c] = fields[c].toInt();
        }
    }


/*
    int initialRobotPosition[2] = {2,2};
    int shipsFuel [2]= {10, 20};
    bool foundItems[2] = {false, false};
    bool drivingShip[2] = {false, false};

    Node nod((Node *)nullptr, -1, 0, 0, initialRobotPosition, shipsFuel, foundItems,
            drivingShip);

    nod.setMap(readMap);*/



    //map[10][10];
    //map[9][9] = 8;

    qfile_map.close();





    for (int r = 0; r < 10; r++){
        for (int c = 0; c < 10; c++){
            if ( readMap[r][c] == 2 ){
                initialRobotsPosition[0] = r;
                initialRobotsPosition[1] = c;
            }
        }
    }

    shipsFuel[0] = 10;
    shipsFuel[1] = 20;

}

Node nod((Node *)nullptr, -1, 0, 0, initialRobotsPosition, shipsFuel, foundItems,
        drivingShip);
//Handler hand = Handler(nod);

int var = 0;
std::vector<Node*> victoryVec;

std::vector<std::vector <int>> vicMatrixPositions;

int c = 0;
std::vector <int> lastPosition = {initialRobotsPosition[0],initialRobotsPosition[1]};


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_searchButton_clicked()
{
    for (int row = 0; row < 10; row++){
        for (int col = 0; col < 10; col++){
            if(readMap[row][col] == 1){
                labelsList[row][col]
                        ->setPixmap( QPixmap("/home/diegoflm/Documents/VU/IngSistemas/MateriasYTemas/Semestre6/AI/Project/pCode/GUI/labyrinthGUI/BrickWall.png") );
            }else if( ( readMap[row][col] == 3 ) || ( readMap[row][col] == 4 )){
                labelsList[row][col]
                        ->setPixmap( QPixmap("/home/diegoflm/Documents/VU/IngSistemas/MateriasYTemas/Semestre6/AI/Project/pCode/GUI/labyrinthGUI/spaceShip.png") );
            }else if( readMap[row][col] == 6 ){
                labelsList[row][col]
                        ->setPixmap( QPixmap("/home/diegoflm/Documents/VU/IngSistemas/MateriasYTemas/Semestre6/AI/Project/pCode/GUI/labyrinthGUI/lava.png") );
            }else {
                labelsList[row][col]->setText( QString::number(readMap[row][col]) );
            }
        }
    }



    nod.setMap(readMap);

    Handler hand = Handler(nod);

    auto timePoint1 = std::chrono::high_resolution_clock::now();

    /*
        0 := Breadth first search
        1 := Uniform cost search
        2 := Depth first search
        3 := Greedy search
        4 := A* search
        */
    if (ui->radioButton->isChecked()){ //Breadth First Search
        hand.search(0);
    } else if (ui->radioButton_2->isChecked()){ //Uniform Cost Search
        hand.search(1);
    } else if (ui->radioButton_3->isChecked()){ //Depth First Search
        hand.search(2);
    } else if (ui->radioButton_4->isChecked()){ //Greedy Search
        hand.search(3);
    } else if (ui->radioButton_5->isChecked()){ //A* Search
        hand.search(4);
    }

    auto timePoint2 = std::chrono::high_resolution_clock::now();

    auto timePeriod2 = std::chrono::duration_cast<std::chrono::microseconds>
                        (timePoint2 - timePoint1);

    int integerTime = timePeriod2.count();

    ui->lcdNumber->setDigitCount(8);
    ui->lcdNumber->display( integerTime );

    ui->lcdNumber_2->setDigitCount(3);
    ui->lcdNumber_2->display( hand.getVicWayNode( hand.getVictorySize() - 1 )->getDepth() );

    ui->lcdNumber_3->setDigitCount(3);
    ui->lcdNumber_3->display( hand.getVicWayNode( hand.getVictorySize() - 1 )->getCost() );

    ui->lcdNumber_4->setDigitCount(8);
    ui->lcdNumber_4->display( hand.getNumberOfExpansions() );

    //std::vector<std::vector <int>> vicMatrixPositions;
    c = 0;
    lastPosition = {initialRobotsPosition[0],initialRobotsPosition[1]};

    victoryVec.clear();
    vicMatrixPositions.clear();
    for(int i = 0; i < hand.getVictorySize(); i++){
        victoryVec.push_back(hand.getVicWayNode(i));

        vicMatrixPositions.push_back( {hand.getVicWayNode(i)->getPosition0() ,hand.getVicWayNode(i)->getPosition1()  } );
        //vicMatrixPositions.at(c).at(0) = 5;
    }

    timeLapse->start(200);
}





void MainWindow::onTimeEnd()
{
    timeLapse->setInterval( (ui->doubleSpinBox->value()) * 1000 );

    //c is a counter for steps in the solution way.
    if (c == 0){ //put Terminator face
        labelsList[initialRobotsPosition[0]][initialRobotsPosition[1]]
                ->setPixmap( QPixmap("/home/diegoflm/Documents/VU/IngSistemas/MateriasYTemas/Semestre6/AI/Project/pCode/GUI/labyrinthGUI/terminator.png") );

        c++;
    }else if( c < vicMatrixPositions.size() ){

        if(readMap[vicMatrixPositions.at(c - 1).at(0)][vicMatrixPositions.at(c - 1).at(1)] == 6){
            labelsList[vicMatrixPositions.at(c - 1).at(0)][vicMatrixPositions.at(c - 1).at(1)]
                ->setPixmap( QPixmap("/home/diegoflm/Documents/VU/IngSistemas/MateriasYTemas/Semestre6/AI/Project/pCode/GUI/labyrinthGUI/lava.png") );
        }/*else if(readMap[vicMatrixPositions.at(c - 1).at(0)][vicMatrixPositions.at(c - 1).at(1)] == 3 && (shipsFuel[0] == 10) && !(drivingShip[0])){
            labelsList[vicMatrixPositions.at(c - 1).at(0)][vicMatrixPositions.at(c - 1).at(1)]
                ->setPixmap( QPixmap("/home/diegoflm/Documents/VU/IngSistemas/MateriasYTemas/Semestre6/AI/Project/pCode/GUI/labyrinthGUI/spaceShip.png") );
        }else if(readMap[vicMatrixPositions.at(c - 1).at(0)][vicMatrixPositions.at(c - 1).at(1)] == 4 && (shipsFuel[1] == 20) && !(drivingShip[1])){
            labelsList[vicMatrixPositions.at(c - 1).at(0)][vicMatrixPositions.at(c - 1).at(1)]
                ->setPixmap( QPixmap("/home/diegoflm/Documents/VU/IngSistemas/MateriasYTemas/Semestre6/AI/Project/pCode/GUI/labyrinthGUI/spaceShip.png") );
        }*/else {
            labelsList[vicMatrixPositions.at(c - 1).at(0)][vicMatrixPositions.at(c - 1).at(1)]
                    ->setText( QString::number(readMap[vicMatrixPositions.at(c - 1).at(0)][vicMatrixPositions.at(c - 1).at(1)]) );
        }

        labelsList[vicMatrixPositions.at(c).at(0)][vicMatrixPositions.at(c).at(1)]
                ->setPixmap( QPixmap("/home/diegoflm/Documents/VU/IngSistemas/MateriasYTemas/Semestre6/AI/Project/pCode/GUI/labyrinthGUI/terminator.png") );

        //labelsList[vicMatrixPositions.at(c - 1).at(0)][vicMatrixPositions.at(c - 1).at(1)]->show();
        labelsList[vicMatrixPositions.at(c).at(0)][vicMatrixPositions.at(c).at(1)]->show();
        c++;
    }

}



