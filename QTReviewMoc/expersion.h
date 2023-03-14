#ifndef EXPERSION_H
#define EXPERSION_H

#include <QObject>

class ExPersion : public QObject
{
    Q_OBJECT

    Q_CLASSINFO("author","hzy");
    Q_CLASSINFO("version", "1.1.1");
    Q_CLASSINFO("info", "QT5 Meta Object and Property Example");

    Q_PROPERTY(int age READ getAge WRITE setAge NOTIFY ageChanged);
    Q_PROPERTY(QString name MEMBER m_name);
    Q_PROPERTY(int score MEMBER m_score);
public:
    explicit ExPersion(QString name, QObject *parent = nullptr);

public:
    int getAge();
    void setAge(int value);

    void incAge();

signals:
    void ageChanged(int value);

private:
    int m_age = 5;
    QString m_name;
    int m_score = 50;
};

#endif // EXPERSION_H
