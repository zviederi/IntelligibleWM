#include "IntelligibleWidget.h"

#include <QVBoxLayout>

#include <mongocxx/logger.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/database.hpp>

namespace IWM
{
    IntelligibleWidget::IntelligibleWidget(QWidget *parent) : QWidget(parent),
        _toolBar(new IntelligibleToolBar(this)),
        _horizontalSplitter(new QSplitter(this)),
        _verticalSplitter(new QSplitter(this))
    {
        std::cout << "IntelligibleWidget" << "\n";
         _toolBar->setVisible(true);

        _horizontalSplitter->setOrientation(Qt::Horizontal);
        _horizontalSplitter->setHandleWidth(1);
        _horizontalSplitter->setContentsMargins(0, 0, 0, 0);

        int hStep = this->width() / 10;
        QList<int> hSizes;
        hSizes << hStep << (hStep*100);
        _horizontalSplitter->setSizes(hSizes);

        _verticalSplitter->setOrientation(Qt::Vertical);
        _verticalSplitter->setHandleWidth(1);
        _verticalSplitter->setContentsMargins(0, 0, 0, 0);
        _verticalSplitter->addWidget(_horizontalSplitter);

        QList<int> vSizes;
        vSizes << width() << width();
        _verticalSplitter->setSizes(vSizes);

        QVBoxLayout *layout = new QVBoxLayout();
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(_toolBar, 0);
        layout->setSpacing(0);
        layout->addWidget(_verticalSplitter, 1);
        setLayout(layout);

        // IwmMongo *test = new IwmMongo(this);
        IwmMongo test;
        mongocxx::client *conn  = test.connection();
        auto db = conn->database("dellper");
        auto collections = db.list_collections();
       
        for (auto&& collection : collections) {
            std::cout << "Database: " <<  collection["name"].get_utf8().value.to_string() << "\n";
        }
                
    }
} // namespace IWM