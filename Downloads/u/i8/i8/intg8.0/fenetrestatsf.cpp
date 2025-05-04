#include "fenetrestatsf.h"
#include "ui_fenetrestatsf.h"
#include "formation.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QPixmap>

FenetreStatsF::FenetreStatsF(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FenetreStatsF)
{
    ui->setupUi(this);
    dessinerCamembert();
    connect(ui->btnFermer, &QPushButton::clicked, this, &FenetreStatsF::close);
}

FenetreStatsF::~FenetreStatsF()
{
    delete ui;
}

void FenetreStatsF::dessinerCamembert()
{
    QPixmap pixmap(800, 600);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    QRect rect((pixmap.width() - 300) / 2, 50, 300, 300);

    int nbPrevue = Formation().compterParStatut("Prévue");
    int nbEncours = Formation().compterParStatut("En cours");
    int nbTerminee = Formation().compterParStatut("Terminée");
    int total = nbPrevue + nbEncours + nbTerminee;
    if (total == 0) return;

    int anglePrevue = static_cast<int>(360.0 * nbPrevue / total);
    int angleEncours = static_cast<int>(360.0 * nbEncours / total);
    int angleTerminee = 360 - anglePrevue - angleEncours;

    int startAngle = 0;
    painter.setBrush(Qt::blue);
    painter.drawPie(rect, startAngle * 16, anglePrevue * 16);
    startAngle += anglePrevue;

    painter.setBrush(Qt::green);
    painter.drawPie(rect, startAngle * 16, angleEncours * 16);
    startAngle += angleEncours;

    painter.setBrush(Qt::red);
    painter.drawPie(rect, startAngle * 16, angleTerminee * 16);

    QFont font = painter.font();
    font.setPointSize(14);
    painter.setFont(font);

    painter.setPen(Qt::blue);
    painter.drawText(50, 400, QString("🔵 Prévue : %1").arg(nbPrevue));
    painter.setPen(Qt::green);
    painter.drawText(50, 440, QString("🟢 En cours : %1").arg(nbEncours));
    painter.setPen(Qt::red);
    painter.drawText(50, 480, QString("🔴 Terminée : %1").arg(nbTerminee));

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(pixmap);
    ui->graphicsViewCamembert->setScene(scene);
    ui->graphicsViewCamembert->setSceneRect(pixmap.rect());
}
