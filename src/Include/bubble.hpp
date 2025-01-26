// --------------------------------------------------- //
//                    VirtualMiner-X                   //
//                      bubble.hpp                     //
// (c) 2025 Maqi-x                                     //
// --------------------------------------------------- //

#include <QGraphicsOpacityEffect>
#include <QPainter>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QWidget>

class Bubble : public QWidget {
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

  public:
    QColor color;
    Bubble(const QString &text, const QPoint &startPosition, QWidget *parent = nullptr,
           QColor color = Qt::gray)
        : QWidget(parent), m_opacity((float)1), m_text(text) {
        this->color = color;
        setAttribute(Qt::WA_TransparentForMouseEvents);
        setAttribute(Qt::WA_NoSystemBackground);
        setAttribute(Qt::WA_TranslucentBackground);

        move(startPosition);

        auto *effect = new QGraphicsOpacityEffect(this);
        setGraphicsEffect(effect);

        auto *positionAnimation = new QPropertyAnimation(this, "pos");
        positionAnimation->setDuration(800);
        positionAnimation->setStartValue(startPosition);
        positionAnimation->setEndValue(startPosition +
                                       QPoint(QRandomGenerator::global()->bounded(-50, 50),
                                              QRandomGenerator::global()->bounded(-165, -80)));

        auto *opacityAnimation = new QPropertyAnimation(effect, "opacity");
        opacityAnimation->setDuration(1000);
        opacityAnimation->setStartValue((float)1);
        opacityAnimation->setEndValue((float)0);

        connect(opacityAnimation, &QPropertyAnimation::finished, this, &Bubble::deleteLater);

        positionAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        opacityAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    }

    qreal opacity() const { return m_opacity; }
    void setOpacity(qreal opacity) {
        m_opacity = opacity;
        update();
    }

  protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        color.setAlphaF(m_opacity);
        painter.setBrush(color);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(rect());
        painter.setPen(Qt::white);
        painter.drawText(rect(), Qt::AlignCenter, m_text);
    }

  private:
    qreal m_opacity;
    QString m_text;
};
