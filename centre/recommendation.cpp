#include "recommendation.h"
#include "centre.h"

#include <QRegularExpression>
#include <QSet>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QtMath>
#include <algorithm>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextBlock>

RecommendationSystem::RecommendationSystem(QObject *parent) : QObject(parent)
{
    // Load all centres from database
    centre c;
    QSqlQueryModel *model = c.afficher();
    qDebug() << "Number of centres loaded: " << model->rowCount();
    for (int i = 0; i < model->rowCount(); ++i) {
        int id = model->record(i).value("id").toInt();
        qDebug() << "Loaded centre with ID: " << id;
        allCentres.append(centre::read(id));
    }

    initializeTermWeights();
    loadModel();

    // If no model exists, train a new one
    if (idfValues.isEmpty()) {
        trainModel();
    }
}

void RecommendationSystem::initializeTermWeights()
{
    // Define weights for important terms
    termWeights["pool"] = 1.5;
    termWeights["gym"] = 1.5;
    termWeights["sport"] = 1.3;
    termWeights["fitness"] = 1.3;
    termWeights["tennis"] = 1.4;
    termWeights["swim"] = 1.4;
    termWeights["yoga"] = 1.3;
    termWeights["train"] = 1.2;
    termWeights["coach"] = 1.2;
    termWeights["large"] = 1.5;  // Increased weight
    termWeights["big"] = 1.4;    // Increased weight
    termWeights["huge"] = 1.5;   // Added
    termWeights["many"] = 1.3;   // Added
    termWeights["modern"] = 1.2;
    termWeights["new"] = 1.1;
    termWeights["map"] = 2.0;    // Very high weight for exact matches
}

QVector<centre> RecommendationSystem::recommendCentres(const QString &description)
{
    qDebug() << "Processing description: " << description;

    // Enhanced text processing
    QString processedDesc = preprocessText(description);
    QStringList keywords = extractKeywords(processedDesc);
    qDebug() << "Extracted keywords: " << keywords;

    // Check for exact match requirements
    bool requiresExactMatch = false;
    QString exactMatchTerm;
    if (processedDesc.contains("map")) {
        requiresExactMatch = true;
        exactMatchTerm = "map";
    }

    // Compute query features with enhanced weighting
    QMap<QString, double> queryFeatures = computeTF(processedDesc);

    // Apply IDF weights and custom term weights
    for (auto it = queryFeatures.begin(); it != queryFeatures.end(); ++it) {
        if (idfValues.contains(it.key())) {
            it.value() *= idfValues[it.key()];
        }
        if (termWeights.contains(it.key())) {
            it.value() *= termWeights[it.key()];
        }
    }

    // Detect special features from query
    bool wantsLargeCapacity = processedDesc.contains("large") || processedDesc.contains("big") ||
                              processedDesc.contains("huge") || processedDesc.contains("many") ||
                              processedDesc.contains("capacity");
    bool wantsModern = processedDesc.contains("modern") || processedDesc.contains("new") ||
                       processedDesc.contains("renovated");
    bool wantsSports = processedDesc.contains("sport") || processedDesc.contains("fitness") ||
                       processedDesc.contains("gym") || processedDesc.contains("pool");

    QVector<QPair<double, centre>> scoredCentres;
    for (const centre &c : allCentres) {
        // Skip if exact match is required but not found
        if (requiresExactMatch && !c.getFacilities().toLower().contains(exactMatchTerm)) {
            continue;
        }

        // Extract enhanced features from centre
        QMap<QString, double> centreFeatures = extractFeatures(c);

        // Compute similarity with boosted terms
        double similarity = computeSimilarity(queryFeatures, centreFeatures);

        // Skip if similarity is too low (unless we have other strong matches)
        if (similarity < 0.1 && !wantsLargeCapacity && !wantsModern && !wantsSports) {
            continue;
        }

        // Capacity scoring - more aggressive for large capacity requests
        double capacityScore = 0.0;
        if (wantsLargeCapacity) {
            // Only consider centers with capacity > 1000 as "large"
            if (c.getCapacite() > 1000) {
                capacityScore = qMin(1.0, c.getCapacite() / 100000.0);
            } else {
                // Penalize small centers when large capacity is requested
                similarity *= 0.2; // Strong penalty
                capacityScore = -0.5; // Negative score for small centers when large is requested
            }
        }

        // Modern facility bonus
        double modernScore = 0.0;
        if (wantsModern && (c.getFacilities().contains("modern") ||
                            c.getFacilities().contains("new"))) {
            modernScore = 0.5;
        }

        // Sports facility bonus
        double sportsScore = 0.0;
        if (wantsSports && (c.getFacilities().contains("sport") ||
                            c.getFacilities().contains("fitness") ||
                            c.getFacilities().contains("gym") ||
                            c.getFacilities().contains("pool"))) {
            sportsScore = 0.5;
        }

        // Status bonus (prefer open centers)
        double statusScore = c.getStatus() == 1 ? 0.2 : 0.0;

        // Combine scores with dynamic weighting
        double capacityWeight = wantsLargeCapacity ? 0.6 : 0.1;
        double similarityWeight = requiresExactMatch ? 0.3 : 0.5;
        double finalScore = (similarity * similarityWeight) +
                            (capacityScore * capacityWeight) +
                            (modernScore * 0.1) +
                            (sportsScore * 0.1) +
                            statusScore;

        // Only add to recommendations if meets minimum requirements
        if (!wantsLargeCapacity || c.getCapacite() > 1000) {
            scoredCentres.append(qMakePair(finalScore, c));
        }
    }

    // Sort by score
    std::sort(scoredCentres.begin(), scoredCentres.end(),
              [](const QPair<double, centre> &a, const QPair<double, centre> &b) {
                  // If scores are equal, prefer higher capacity
                  if (qFuzzyCompare(a.first, b.first)) {
                      return a.second.getCapacite() > b.second.getCapacite();
                  }
                  return a.first > b.first;
              });

    // Return top 5 recommendations
    QVector<centre> recommendations;
    int count = qMin(5, scoredCentres.size());
    for (int i = 0; i < count; ++i) {
        recommendations.append(scoredCentres[i].second);
        qDebug() << "Recommendation score:" << scoredCentres[i].first
                 << "Capacity:" << scoredCentres[i].second.getCapacite();
    }

    return recommendations;
}

// [Rest of the implementation remains the same as in your original file]
QMap<QString, double> RecommendationSystem::extractFeatures(const centre &c)
{
    QString text = preprocessText(c.getNom() + " " + c.getAdresse() + " " + c.getFacilities());
    QMap<QString, double> features = computeTF(text);

    // Apply IDF weights and custom term weights
    for (auto it = features.begin(); it != features.end(); ++it) {
        if (idfValues.contains(it.key())) {
            it.value() *= idfValues[it.key()];
        }
        if (termWeights.contains(it.key())) {
            it.value() *= termWeights[it.key()];
        }
    }

    return features;
}

void RecommendationSystem::trainModel()
{
    QMap<QString, int> docFreq;
    int totalDocs = allCentres.size();

    for (const centre &c : allCentres) {
        QString text = preprocessText(c.getNom() + " " + c.getAdresse() + " " + c.getFacilities());
        QMap<QString, double> tf = computeTF(text);
        for (const QString &term : tf.keys()) {
            docFreq[term]++;
        }
    }

    // Calculate IDF with smoothing
    for (auto it = docFreq.begin(); it != docFreq.end(); ++it) {
        idfValues[it.key()] = log((totalDocs + 1) / (1.0 + it.value())) + 1;
    }

    saveModel();
}

QMap<QString, double> RecommendationSystem::computeTF(const QString &text)
{
    QMap<QString, double> termFreq;
    QStringList terms = text.split(' ', Qt::SkipEmptyParts);
    int totalTerms = terms.size();

    for (const QString &term : terms) {
        QString stemmed = stemWord(term);
        if (!stemmed.isEmpty() && isImportantTerm(stemmed)) {
            termFreq[stemmed]++;
        }
    }

    // Normalize
    if (totalTerms > 0) {
        for (auto it = termFreq.begin(); it != termFreq.end(); ++it) {
            it.value() /= totalTerms;
        }
    }

    return termFreq;
}

double RecommendationSystem::computeSimilarity(const QMap<QString, double> &vec1,
                                               const QMap<QString, double> &vec2)
{
    double dotProduct = 0.0;
    double norm1 = 0.0;
    double norm2 = 0.0;

    QSet<QString> allTerms;
    for (const QString &term : vec1.keys()) allTerms.insert(term);
    for (const QString &term : vec2.keys()) allTerms.insert(term);

    for (const QString &term : allTerms) {
        double v1 = vec1.value(term, 0.0);
        double v2 = vec2.value(term, 0.0);
        dotProduct += v1 * v2;
        norm1 += v1 * v1;
        norm2 += v2 * v2;
    }

    if (norm1 == 0 || norm2 == 0) return 0.0;
    return dotProduct / (sqrt(norm1) * sqrt(norm2));
}

QString RecommendationSystem::preprocessText(const QString &text)
{
    // Convert to lowercase
    QString processed = text.toLower();

    // Remove special characters except spaces and hyphens
    processed.remove(QRegularExpression("[^a-z0-9\\s-]"));

    // Expand contractions
    processed.replace("won't", "will not");
    processed.replace("can't", "can not");
    processed.replace("n't", " not");
    processed.replace("'re", " are");
    processed.replace("'s", " is");
    processed.replace("'d", " would");
    processed.replace("'ll", " will");
    processed.replace("'t", " not");
    processed.replace("'ve", " have");
    processed.replace("'m", " am");

    // Remove extra whitespace
    processed = processed.simplified();

    return processed;
}

QString RecommendationSystem::stemWord(const QString &word)
{
    // Simple stemming - improve this with a proper stemmer if needed
    if (word.endsWith("ing")) {
        return word.left(word.length() - 3);
    }
    if (word.endsWith("es")) {
        return word.left(word.length() - 2);
    }
    if (word.endsWith("s")) {
        return word.left(word.length() - 1);
    }
    return word;
}

QStringList RecommendationSystem::extractKeywords(const QString &text)
{
    QStringList stopWords = {"the", "and", "of", "in", "to", "a", "is", "for", "on", "with",
                             "it", "as", "at", "be", "this", "that", "by", "from"};
    QSet<QString> stopSet(stopWords.begin(), stopWords.end());

    QStringList words = text.split(' ', Qt::SkipEmptyParts);
    QStringList keywords;

    for (const QString &word : words) {
        QString stemmed = stemWord(word);
        if (!stemmed.isEmpty() && !stopSet.contains(word) && word.length() > 2) {
            keywords.append(stemmed);
        }
    }

    return keywords;
}

bool RecommendationSystem::isImportantTerm(const QString &term)
{
    // Skip single characters and numbers
    if (term.length() <= 1 || term.toInt() > 0) {
        return false;
    }

    // Skip common unimportant terms
    QStringList unimportant = {"center", "centre", "place", "location", "facility", "building"};
    if (unimportant.contains(term)) {
        return false;
    }

    return true;
}

void RecommendationSystem::loadModel()
{
    QFile file("tfidf_model.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open model file for reading - will train new model";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split('\t');
        if (parts.size() == 2) {
            idfValues[parts[0]] = parts[1].toDouble();
        }
    }
    file.close();
}

void RecommendationSystem::saveModel()
{
    QFile file("tfidf_model.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open model file for writing";
        return;
    }

    QTextStream out(&file);
    for (auto it = idfValues.begin(); it != idfValues.end(); ++it) {
        out << it.key() << "\t" << it.value() << "\n";
    }
    file.close();
}
