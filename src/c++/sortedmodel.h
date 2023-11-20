#ifndef SORTEDMODEL_H
#define SORTEDMODEL_H

#include <QtCore/QSortFilterProxyModel>

class SortedModel : public QObject
{
    Q_OBJECT
public:
    explicit SortedModel(QObject *parent = nullptr);

signals:

};

#endif // SORTEDMODEL_H
