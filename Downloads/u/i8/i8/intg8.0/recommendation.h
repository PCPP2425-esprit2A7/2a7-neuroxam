#ifndef RECOMMENDATION_H
#define RECOMMENDATION_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QSet>
#include <QSqlQueryModel>
#include <QRegularExpression>

#include "centre.h"

class RecommendationSystem : public QObject
{
    Q_OBJECT

public:
    explicit RecommendationSystem(QObject *parent = nullptr);
    ~RecommendationSystem() override = default;

    QVector<centre> recommendCentres(const QString &description);
    void trainModel();

private:
    QVector<centre> allCentres;
    QMap<QString, double> idfValues;
    QMap<QString, double> termWeights; // For custom term weighting

    // Enhanced text processing
    QString preprocessText(const QString &text);
    QString stemWord(const QString &word);
    QStringList extractKeywords(const QString &text);

    // Feature extraction
    QMap<QString, double> computeTF(const QString &text);
    QMap<QString, double> extractFeatures(const centre &c);

    // Similarity calculation
    double computeSimilarity(const QMap<QString, double> &queryFeatures,
                             const QMap<QString, double> &centreFeatures);

    // Model persistence
    void loadModel();
    void saveModel();

    // Helper functions
    void initializeTermWeights();
    bool isImportantTerm(const QString &term);
};

#endif // RECOMMENDATION_H
