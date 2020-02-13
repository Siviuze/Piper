#include "Scene.h"
#include "Node.h"

#include <QDebug>

#include <QPainter>
#include <QBrush>
#include <QKeyEvent>

namespace piper
{
    Scene::Scene (QObject* parent)
        : QGraphicsScene(parent)
    {
        //setSceneRect(QRectF()); // disallow auto shrink
    }

    void Scene::drawBackground(QPainter* painter, QRectF const& rect) 
    {    
        QBrush brush(Qt::SolidPattern);
        brush.setColor({40, 40, 40}),
        painter->fillRect(rect, brush);
        
        QPen pen;
        pen.setColor({100, 100, 100});
        pen.setWidth(2);
        painter->setPen(pen);
        
        constexpr int gridSize = 20;
        qreal left = int(rect.left()) - (int(rect.left()) % gridSize);
        qreal top = int(rect.top()) - (int(rect.top()) % gridSize);
        QVector<QPointF> points;
        for (qreal x = left; x < rect.right(); x += gridSize)
        {
            for (qreal y = top; y < rect.bottom(); y += gridSize)
            {
                points.append(QPointF(x,y));
            }
        }
        
        painter->drawPoints(points.data(), points.size());
    }

    void Scene::keyReleaseEvent(QKeyEvent* keyEvent) 
    {
        if (keyEvent->key() == Qt::Key::Key_Delete)
        {
            for (auto& item : selectedItems())
            {
                removeItem(item);
                delete item;
            }
        }
    }
    
    void Scene::changeStageColor(QString const& stage, QColor const& color)
    {
        for (auto& item : Node::items())
        {
            if (item->stage() == stage)
            {
                item->setBackgroundColor(color);
            }
        }
    }
}