#ifndef LITCHINAVIGATOR_H
#define LITCHINAVIGATOR_H

#include <QMainWindow>

#include <QtGui>
#include <QLineEdit>
#include <QShortcut>
#include <QProgressBar>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QVBoxLayout>

#if QT_VERSION >= 0x050000
#include <QtWebKit>
#include <QtWebKitWidgets/QWebView>
#else
#include <QtWebKit/QtWebKit>
#include <QtWebKit/QWebView>
#endif

#include "cookies.h"

class QNetworkCookieJar;

class litchiNavigator : public QMainWindow
{
    Q_OBJECT

    public:
        litchiNavigator();
        virtual ~litchiNavigator();

    private:
        void creerActions();
        void creerMenus();
        void creerBarresOutils();
        void creerBarreEtat();
        void closeEvent(QCloseEvent* event);
        void closeNavigator();
        QWidget* creerOngletPageWeb(QString url = "");
        QWebView* pageActuelle();
        QMenu* menuHistorique;

    private slots:
        void precedente();
        void suivante();
        void accueil();
        void stop();
        void actualiser();

        void chargerHistoriqueDansMenu();
        void afficherElementHistorique(QAction* action);

        void aPropos();
        void nouvelOnglet();
        void fermerOnglet();
        void chargerPage();
        void google();
        void changementOnglet();
        void afficherSearch();
        void TrouverTexte();

        void changementTitre(const QString& titreComplet);
        void changementUrl(const QUrl& url);
        void chargementDebut();
        void chargementEnCours(int pourcentage);
        void chargementTermine();

    private:
        QTabWidget* onglets;

        QShortcut* keyUp;
        QAction* actionNouvelOnglet;
        QAction* actionFermerOnglet;
        QAction* actionQuitter;
        QAction* actionAPropos;
        QAction* actionAProposQt;
        QAction* actionPrecedente;
        QAction* actionSuivante;
        QAction* actionStop;
        QAction* actionActualiser;
        QAction* actionAccueil;
        QAction* actionGo;

        QLineEdit* search;
        QLineEdit* champAdresse;
        QProgressBar* progression;
        QLineEdit* barre;
        QNetworkCookieJar* cookieJar;

    signals :
        void closeWindow();
};


#endif
