#include "litchiNavigator.h"

litchiNavigator::litchiNavigator()
    :cookieJar(new QNetworkCookieJar(this))
{
    keyUp= new QShortcut(this);
    keyUp->setKey(Qt::Key_F);
    creerActions();
    creerMenus();
    creerBarresOutils();
    creerBarreEtat();

    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
    QWebSettings::globalSettings()->setAttribute( QWebSettings::JavascriptEnabled, true);


    /*Creation of tab and generation of new loading page*/
    onglets = new QTabWidget;
    onglets->addTab(creerOngletPageWeb(tr("http://www.google.com")), tr("Google"));
    connect(onglets, SIGNAL(currentChanged(int)), this, SLOT(changementOnglet(int)));
    setCentralWidget(onglets);

    /*Window definition*/
    setFixedSize((this->width())*1.9, (this->height())*1.3);
    setWindowTitle(tr("Litchi"));
    setWindowFlags(Qt::FramelessWindowHint);

}

void litchiNavigator::creerActions()
{
    /*TODO : Move picture folder */
    actionNouvelOnglet = new QAction(tr("&Nouvel onglet"), this);
    actionNouvelOnglet->setShortcut(tr("Ctrl+T"));
    connect(actionNouvelOnglet, SIGNAL(triggered()), this, SLOT(nouvelOnglet()));
    actionFermerOnglet = new QAction(tr("&Fermer l'onglet"), this);
    actionFermerOnglet->setShortcut(tr("Ctrl+W"));
    connect(actionFermerOnglet, SIGNAL(triggered()), this, SLOT(fermerOnglet()));
    actionQuitter = new QAction(tr("&Quitter"), this);
    actionQuitter->setShortcut(tr("Ctrl+Q"));
    //connect(actionQuitter, SIGNAL(triggered()),this->close());

    actionPrecedente = new QAction(QIcon(":/QNavigator/back"), tr("&Precedente"), this);
    actionPrecedente->setShortcut(QKeySequence::Back);
    connect(actionPrecedente, SIGNAL(triggered()), this, SLOT(precedente()));
    actionSuivante = new QAction(QIcon(":/QNavigator/next"), tr("&Suivante"), this);
    actionSuivante->setShortcut(QKeySequence::Forward);
    connect(actionSuivante, SIGNAL(triggered()), this, SLOT(suivante()));
    actionStop = new QAction(QIcon(":/QNavigator/stop"), tr("S&top"), this);
    connect(actionStop, SIGNAL(triggered()), this, SLOT(stop()));
    actionActualiser = new QAction(QIcon(":/QNavigator/refresh"), tr("&Actualiser"), this);
    actionActualiser->setShortcut(QKeySequence::Refresh);
    connect(actionActualiser, SIGNAL(triggered()), this, SLOT(actualiser()));
    actionAccueil = new QAction(QIcon(":/QNavigator/home"), tr("A&ccueil"), this);
    connect(actionAccueil, SIGNAL(triggered()), this, SLOT(accueil()));
    actionGo = new QAction(QIcon(":/QNavigator/go"), tr("A&ller �"), this);
    connect(actionGo, SIGNAL(triggered()), this, SLOT(chargerPage()));

    actionAPropos = new QAction(tr("&A propos..."), this);
    connect(actionAPropos, SIGNAL(triggered()), this, SLOT(aPropos()));
    actionAPropos->setShortcut(QKeySequence::HelpContents);
    actionAProposQt = new QAction(tr("A propos de &Qt..."), this);
    connect(actionAProposQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void litchiNavigator::creerMenus()
{
    QMenu *menuFichier = menuBar()->addMenu(tr("&Fichier"));

    menuFichier->addAction(actionNouvelOnglet);
    menuFichier->addAction(actionFermerOnglet);
    menuFichier->addSeparator();
    menuFichier->addAction(actionQuitter);

    QMenu *menuNavigation = menuBar()->addMenu(tr("&Navigation"));

    menuNavigation->addAction(actionPrecedente);
    menuNavigation->addAction(actionSuivante);
    menuNavigation->addAction(actionStop);
    menuNavigation->addAction(actionActualiser);
    menuNavigation->addAction(actionAccueil);


    menuHistorique = menuBar()->addMenu(tr("&Historique"));
    connect(menuHistorique, SIGNAL(aboutToShow()),
    this, SLOT(chargerHistoriqueDansMenu()));
    connect(menuHistorique, SIGNAL(triggered(QAction*)),
    this, SLOT(afficherElementHistorique(QAction*)));

    QMenu *menuAide = menuBar()->addMenu(tr("&?"));

    menuAide->addAction(actionAPropos);
    menuAide->addAction(actionAProposQt);
}

void litchiNavigator::creerBarresOutils()
{
    champAdresse = new QLineEdit;
    barre = new QLineEdit;

    connect(champAdresse, SIGNAL(returnPressed()), this, SLOT(chargerPage()));
    connect(barre,SIGNAL(returnPressed()),this,SLOT(google()));
    QToolBar *toolBarNavigation = addToolBar(tr("Navigation"));

    toolBarNavigation->addAction(actionPrecedente);
    toolBarNavigation->addAction(actionSuivante);
    toolBarNavigation->addAction(actionStop);
    toolBarNavigation->addAction(actionActualiser);
    toolBarNavigation->addAction(actionAccueil);
    toolBarNavigation->addWidget(champAdresse);
    toolBarNavigation->addAction(actionGo);

}

void litchiNavigator::creerBarreEtat()
{
    progression = new QProgressBar(this);
    search = new QLineEdit;
    progression->setVisible(false);
    search->setVisible(false);
    progression->setMaximumHeight(14);
    statusBar()->addWidget(progression, 1);
    statusBar()->addWidget(search, 2);
    QObject::connect(keyUp, SIGNAL(activated()),this, SLOT(afficherSearch()));
    connect(search,SIGNAL(returnPressed()),this,SLOT(TrouverTexte()));
}

void litchiNavigator::closeEvent(QCloseEvent *event)
{
    event->accept();
}

/*Slots*/

void litchiNavigator::precedente()
{
    pageActuelle()->back();
}

void litchiNavigator::suivante()
{
    pageActuelle()->forward();
}

void litchiNavigator::accueil()
{
    pageActuelle()->load(QUrl(tr("http://www.google.com")));
}

void litchiNavigator::stop()
{
    pageActuelle()->stop();
}

void litchiNavigator::actualiser()
{
    pageActuelle()->reload();
}


void litchiNavigator::aPropos()
{
    QMessageBox::information(this, tr("A propos..."), tr("The LitchiNavigator is developped by the Ingesup TRSE in case in the Litchi Console project. Based on Webkit"));
}

void litchiNavigator::nouvelOnglet()
{
    pageActuelle()->page()->networkAccessManager()->setCookieJar(cookieJar);
    int indexNouvelOnglet = onglets->addTab(creerOngletPageWeb(), tr("(New Page)"));
    onglets->setCurrentIndex(indexNouvelOnglet);

    champAdresse->setText("");
    champAdresse->setFocus(Qt::OtherFocusReason);
}

void litchiNavigator::fermerOnglet()
{
    /*We can't let the last tab beiing closed, QTabWidget will not work in this case*/
    if (onglets->count() > 1)
    {
        onglets->removeTab(onglets->currentIndex());
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("You need only one tab !"));
    }
}

void litchiNavigator::chargerPage()
{
    QString url = champAdresse->text();

    /*We add http in the address' bar if it's not here*/
    if (url.left(7) != "http://"&&url.left(8) != "https://")
    {
        url = "http://" + url;
        champAdresse->setText(url);
    }

    pageActuelle()->load(QUrl(url));
}

void litchiNavigator::google()
{
    QString url = "http://www.google.fr/search?q="+barre->text();

     /*We add http in the address' bar if it's not here*/
    if (url.left(7) != "http://"&&url.left(8) != "https://")
    {
        url = "http://" + url;
        champAdresse->setText(url);
    }

    pageActuelle()->load(QUrl(url));
}

void litchiNavigator::changementOnglet()
{
    changementTitre(pageActuelle()->title());
    changementUrl(pageActuelle()->url());
}


void litchiNavigator::changementTitre(const QString & titreComplet)
{
    QString titreCourt = titreComplet;

    /*We truncate the title to avoid too long tab*/
    if (titreComplet.size() > 40)
    {
        titreCourt = titreComplet.left(40) + "...";
    }

    onglets->setTabText(onglets->currentIndex(), titreCourt);
}

void litchiNavigator::changementUrl(const QUrl & url)
{
    if (url.toString() != tr("html/page_blanche.html"))
    {
        champAdresse->setText(url.toString());
    }
}

void litchiNavigator::chargementDebut()
{
    progression->setVisible(true);
}

void litchiNavigator::chargementEnCours(int pourcentage)
{
    progression->setValue(pourcentage);
}

void litchiNavigator::chargementTermine()
{
    progression->setVisible(false);
    statusBar()->showMessage(tr("Finish"), 2000);
}



/* Other methodes */


QWidget *litchiNavigator::creerOngletPageWeb(QString url)
{
    QWidget *pageOnglet = new QWidget;
    QWebView *pageWeb = new QWebView;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(pageWeb);
    pageOnglet->setLayout(layout);

    if (url.isEmpty())
    {
        pageWeb->load(QUrl(tr("html/page_blanche.html")));
    }
    else
    {
        if (url.left(7) != "http://"&&url.left(8) != "https://")
        {
            url = "http://" + url;
        }
        pageWeb->load(QUrl(url));
    }

    /* Slot creation */
    connect(pageWeb, SIGNAL(titleChanged(QString)), this, SLOT(changementTitre(QString)));
    connect(pageWeb, SIGNAL(urlChanged(QUrl)), this, SLOT(changementUrl(QUrl)));
    connect(pageWeb, SIGNAL(loadStarted()), this, SLOT(chargementDebut()));
    connect(pageWeb, SIGNAL(loadProgress(int)), this, SLOT(chargementEnCours(int)));
    connect(pageWeb, SIGNAL(loadFinished(bool)), this, SLOT(chargementTermine(bool)));

    return pageOnglet;
}

QWebView *litchiNavigator::pageActuelle()
{
    return onglets->currentWidget()->findChild<QWebView *>();
}

void litchiNavigator::afficherSearch()
{
    search->setVisible(true);
}

void litchiNavigator::TrouverTexte()
{
    search->setVisible(false);
    pageActuelle()->findText(search->text(),QWebPage::HighlightAllOccurrences);
}

void litchiNavigator::chargerHistoriqueDansMenu()
{
    /* Erase all the menu's contents*/
    menuHistorique->clear();

    /* To avoid a crash */
    if (!pageActuelle())
        return;

    const QList<QWebHistoryItem> liste = pageActuelle()->page()->history()->items();

    /* Page's index actually displayed*/
    int indexActuel = pageActuelle()->page()->history()->currentItemIndex();

    /* Limit the display to 10 lastest web sites in the back history */
    int debut = qMax(indexActuel - 10, 0);
    /* and 5 newest in the next history*/
    int fin = qMin(indexActuel + 5, liste.size());

    for(int i = debut; i < fin; ++i )
    {
        QWebHistoryItem item = liste[i];
        /* We'll try to put the page's title in menu's text */
        QString titre = item.title();
        /* If the title is empty, we use the url */
        if (titre.isEmpty())
            titre = item.url().toString();

        QAction *action = menuHistorique->addAction(item.icon(), titre);
        action->setData(i);

        if(i == indexActuel)
        {
            QFont font = action->font();
            font.setBold(true);
            action->setFont(font);
        }
    }
}

void litchiNavigator::afficherElementHistorique(QAction* action)
{
    QWebHistory *history =pageActuelle()->page()->history();
    bool ok = false;
    int index = action->data().toInt(&ok);
    if (ok)
    {
        history->goToItem(history->itemAt(index));
    }
}

litchiNavigator::~litchiNavigator()
{
    delete actionNouvelOnglet;
    delete actionFermerOnglet;
    delete actionQuitter;
    delete actionPrecedente;
    delete actionSuivante;
    delete actionStop;
    delete actionActualiser;
    delete actionAccueil;
    delete actionGo;
    delete actionAPropos;
    delete actionAProposQt;

    delete champAdresse;
    delete barre;
    delete progression;
    delete search;

    delete onglets;
    delete keyUp;
    delete cookieJar;
}
