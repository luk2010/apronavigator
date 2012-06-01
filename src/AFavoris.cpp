#include "fenNav.h"
#include "datafile.h"

AFavoris::AFavoris(QWidget *parent) : QWidget(parent)
{
    fav = loadFavoris();
    if (fav.count() == 0)
    {QMessageBox::warning(0,tr("Erreur"),tr("Impossiblede charger les favoris !"));}

    QVBoxLayout* vLayout = new QVBoxLayout;
    setLayout(vLayout);

    list = new QTreeWidget;
    list->headerItem()->setText(0,tr("Nom"));
    list->headerItem()->setText(1,tr("Url"));
    list->setAnimated(true);
    list->setColumnCount(2);
    for (int i = 0; i < fav.count(); i++)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem;
        item->setText(0,fav[i].title);
        item->setText(1,fav[i].url);
        item->setIcon(0,QWebSettings::iconForUrl(QUrl(fav[i].url)));
        list->addTopLevelItem(item);
    }
    vLayout->addWidget(list);
    QHBoxLayout* hLayout = new QHBoxLayout;
    vLayout->addLayout(hLayout);
    QPushButton* addFav = new QPushButton(tr("Ajouter"));
        addFav->setIcon(QIcon("icones/favoris_plus.png"));
    QPushButton* delFav = new QPushButton(tr("Supprimer"));
        delFav->setIcon(QIcon("icones/favoris_moins.png"));
    hLayout->addStretch();
    hLayout->addWidget(addFav);
    hLayout->addWidget(delFav);

    QHBoxLayout* hLayout2 = new QHBoxLayout;
    vLayout->addLayout(hLayout2);
    name = new QLineEdit;
    hLayout2->addWidget(name);
    name->setPlaceholderText(tr("Nom..."));
    url = new QLineEdit;
    hLayout2->addWidget(url);
    url->setPlaceholderText(tr("URL..."));
    validateFav = new QPushButton("");
    hLayout2->addWidget(validateFav);
    validateFav->setIcon(QIcon("icones/valid.png"));
    validateFav->setMaximumWidth(32);
    validateFav->setToolTip(tr("Valider le favori"));

    name->setVisible(false);
    url->setVisible(false);
    validateFav->setVisible(false);

    connect(addFav,SIGNAL(clicked()),this,SLOT(createNewFavoris()));
    connect(delFav,SIGNAL(clicked()),this,SLOT(deleteFavoris()));
    connect(validateFav,SIGNAL(clicked()),this,SLOT(confirmNewFav()));
}

QList<FavoriElement> AFavoris::loadFavoris()
{
    DataFile dataFile;
    if(!dataFile.isValid())
    {
        QMessageBox::warning(this, "Error", "Le fichier de donnee est corrompue !");
        dataFile.rebuildData();
        dataFile.save();
    }

    QDomElement favorisElement = dataFile.getFavoris();
    if(favorisElement.isNull())
    {
        QMessageBox::warning(this, "Error", "Impossible de toruver le noeud \"<favoris>\" !");
        return QList<FavoriElement>();
    }

    QList <FavoriElement> listeElement;
    QDomElement element = favorisElement.firstChildElement("adresse");
    while (!element.isNull())
    {
        FavoriElement newElement;
        newElement.title = element.attribute("title","");
        newElement.url   = element.attribute("url","");
        listeElement.prepend(newElement);

        element = element.nextSiblingElement("adresse");
    }

    return listeElement;
}

void AFavoris::createNewFavoris()
{
    name->setVisible(!name->isVisible());
    url->setVisible(!url->isVisible());
    validateFav->setVisible(!validateFav->isVisible());
}

void AFavoris::deleteFavoris()
{
    itemSelected = list->currentItem();
    if (itemSelected == NULL)
    {
        QMessageBox::warning(0,tr("Erreur"),tr("Aucun favori sélectionné !"));
        return;
    }

    DataFile dataFile;
    if(!dataFile.isValid())
    {
        QMessageBox::warning(this, "Error", "Le fichier de donnee est corrompue !");
        dataFile.rebuildData();
        dataFile.save();
    }

    QDomElement favorisElement = dataFile.getFavoris();
    if(favorisElement.isNull())
    {
        QMessageBox::warning(this, "Error", "Impossible de toruver le noeud \"<favoris>\" !");
    }

    QDomElement element = favorisElement.firstChildElement("adresse");
    while (!element.isNull())
    {
        if (element.attribute("title") == itemSelected->text(0))
        {
            if (element.attribute("url") == itemSelected->text(1));
            {
                favorisElement.removeChild(element);
                break;
            }
        }
        element = element.nextSiblingElement("adresse");
    }

    dataFile.save();

    list->takeTopLevelItem(list->indexOfTopLevelItem(itemSelected));
    delete itemSelected;
    emit reloadTabBar();
}

void AFavoris::changeSelectedItem(QTreeWidgetItem* current,QTreeWidgetItem* previous)
{
    itemSelected = current;
}

void AFavoris::createList()
{
    list->clear();

    fav = loadFavoris();
    if (fav.count() == 0)
    {QMessageBox::warning(0,tr("Erreur"),tr("Impossiblede charger les favoris !"));
    return;}

    for (int i = 0; i < fav.count(); i++)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem;
        item->setText(0,fav[i].title);
        item->setText(1,fav[i].url);
        item->setIcon(0,QWebSettings::iconForUrl(QUrl(fav[i].url)));
        list->addTopLevelItem(item);
    }
}

void AFavoris::confirmNewFav()
{
    if (name->text().isEmpty())
    {
        QMessageBox::information(0,tr("Attention"),tr("Vous n'avez pas donné de nom à votre favoris !"));
        return;
    }
    else if (url->text().isEmpty())
    {
        QMessageBox::information(0,tr("Attention"),tr("Vous n'avez pas donné l'URL de votre favoris !"));
        return;
    }

    addNewFavoris(name->text(),url->text());
    emit reloadTabBar();
    return createList();
}

void AFavoris::addNewFavoris(const QString& name,const QString& url)
{
    DataFile dataFile;
    if(!dataFile.isValid())
    {
        QMessageBox::warning(NULL, "Error", "Le fichier de donnee est corrompue !");
        dataFile.rebuildData();
        dataFile.save();
    }

    QDomElement favorisElement = dataFile.getFavoris();
    if(favorisElement.isNull())
    {
        QMessageBox::warning(NULL, "Error", "Impossible de toruver le noeud \"<favoris>\" !");
    }

    QDomElement newElement = dataFile.getDocument().createElement("adresse");
    newElement.setAttribute("title",name);
    newElement.setAttribute("url",url);
    favorisElement.appendChild(newElement);

    dataFile.save();
}
