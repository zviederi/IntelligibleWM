#include "AboutIntelligibleWM.h"

#include <QDialogButtonBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "gui/GuiRegistry.h"

namespace IntelligibleWM
{
    AboutIntelligibleWM::AboutIntelligibleWM(QWidget *parent) : QDialog(parent)
    {
        setWindowIcon(GuiRegistry::instance().intelligibleWMIcon());
        setWindowTitle("About IntelligibleWM");
        setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
        QGridLayout *layout = new QGridLayout(this);
        layout->setSizeConstraint(QLayout::SetFixedSize);

        QString version = PROJECT_NAME_VERSION;

        QString description = QString("<h3>" + version + "</h3>"
                                                        "Intelligible Warehouse Manager"
                                                        "<br/>"
                                                        "The project name " +
                                    version + " </a>"
                                                "<br/>");

        QLabel *copyRightLabel = new QLabel(description);
        copyRightLabel->setWordWrap(true);
        copyRightLabel->setOpenExternalLinks(true);
        copyRightLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);

        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
        QPushButton *closeButton = buttonBox->button(QDialogButtonBox::Close);
        buttonBox->addButton(closeButton, QDialogButtonBox::ButtonRole(QDialogButtonBox::RejectRole | QDialogButtonBox::AcceptRole));
        connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

        QIcon icon = GuiRegistry::instance().intelligibleWMIcon();
        QPixmap iconPixmap = icon.pixmap(128, 128);

        QLabel *logoLabel = new QLabel;
        logoLabel->setPixmap(iconPixmap);
        layout->addWidget(logoLabel, 0, 0, 1, 1);
        layout->addWidget(copyRightLabel, 0, 1, 4, 4);
        layout->addWidget(buttonBox, 4, 0, 1, 5);
    }
} // namespace IntelligibleWM