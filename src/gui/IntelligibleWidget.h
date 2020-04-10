#pragma once

#include <QWidget>
#include <QSplitter>
#include <QListView>

#include "gui/widgets/IntelligibleToolBar.h"

#include "core/workers/IwmMongo.h"

namespace IWM
{
    class IntelligibleWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit IntelligibleWidget(QWidget *parent = nullptr);

    private:
        IntelligibleToolBar *const _toolBar;

        QSplitter *const _horizontalSplitter;
        QSplitter *const _verticalSplitter;
    };

} // namespace IWM