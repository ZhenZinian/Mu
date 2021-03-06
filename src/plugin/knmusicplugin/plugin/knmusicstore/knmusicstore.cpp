/*
 * Copyright (C) Kreogist Dev Team
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#include <QBoxLayout>
#include <QScrollBar>
#include <QLabel>
#include <QTimer>

//Include infrastructure.
#include "knlocalemanager.h"
#include "kncategorytab.h"
#include "knopacityanimebutton.h"
#include "knhwidgetswitcher.h"
#include "sao/knsaostyle.h"

//Include store sdk.
#include "sdk/knmusicstoreglobal.h"
#include "sdk/knmusicstorecontainer.h"
#include "sdk/knmusicstorehomewidget.h"
#include "sdk/knmusicstorelistwidget.h"
#include "sdk/knmusicstoresearchresultwidget.h"
#include "sdk/knmusicstoresinglesongwidget.h"
#include "sdk/knmusicstoreemptywidget.h"
#include "sdk/knmusicstorebackend.h"
#include "sdk/knmusicstoretitlebar.h"
#include "sdk/knmusicstoredownloadlist.h"

//Include plugins.
#include "plugin/knmusicstorenetease/knmusicstorenetease.h"

#include "knmusicstore.h"

#include <QDebug>

using namespace MusicStoreUtil;

KNMusicStore::KNMusicStore(QWidget *parent) :
    KNMusicStoreBase(parent),
    m_firstFetch(new QTimer),
    m_tab(new KNCategoryTab(this)),
    m_storeGlobal(KNMusicStoreGlobal::initial(this)),
    m_titleBar(new KNMusicStoreTitleBar(this)),
    m_downloadList(new KNMusicStoreDownloadList(this)),
    m_storeSwitcher(new KNMusicStoreContainer(this)),
    m_emptyWidget(new KNMusicStoreEmptyWidget(this)),
    m_backend(nullptr)
{
    //Configure the tab.
    m_tab->setIcon(QIcon(":/plugin/music/category/store.png"));
    //Configure the scroll area.
    m_storeSwitcher->setAlignment(Qt::AlignHCenter);
    m_storeSwitcher->setSizeAdjustPolicy(QScrollArea::AdjustToContents);
    m_storeSwitcher->setFrameStyle(QFrame::NoFrame);
    KNSaoStyle::styleHorizontalScrollBar(
                m_storeSwitcher->horizontalScrollBar());
    KNSaoStyle::styleVerticalScrollBar(m_storeSwitcher->verticalScrollBar());
    //Initial the widgets.
    m_panels[PanelHome]=new KNMusicStoreHomeWidget(this);
    m_panels[PanelSearch]=
            new KNMusicStoreSearchResultWidget(this);
    m_panels[PanelList]=
            new KNMusicStoreListWidget(this);
    m_panels[PanelSong]=
            new KNMusicStoreSingleSongWidget(this);
    //Hide the content widgets.
    for(int i=0; i<StorePanelCount; ++i)
    {
        //Hide the widget.
        m_panels[i]->hide();
        //Link the panel request.
        connect(m_panels[i], &KNMusicStorePanel::startNetworkActivity,
                [=]{m_titleBar->setStatesButton(StateNetwork, true);});
    }
    //Add the bullet widget and add title widget to title bar.
    for(int i=PanelSearch; i<StorePanelCount; ++i)
    {
        //Hide the widget.
        m_titleBar->appendLabel(m_panels[i]->bulletLabel(),
                                m_panels[i]->headerLabel());
    }
    //Set the empty widget.
    m_storeSwitcher->setWidget(m_emptyWidget);
    //Add download list to title bar.
    m_titleBar->appendIcon(m_downloadList->iconButton());
    //Configure the download list.
    m_downloadList->hide();
    m_downloadList->raise();
    m_downloadList->move(0, m_titleBar->height());
    //Configure the title bar.
    m_titleBar->hide();
    m_titleBar->raise();
    //Configure the first fetch.
    m_firstFetch->setInterval(200);
    m_firstFetch->setSingleShot(true);
    connect(m_firstFetch, &QTimer::timeout,
            this, &KNMusicStore::onActionFirstFetch);

    //Initial the layout.
    QBoxLayout *mainLayout=new QBoxLayout(QBoxLayout::TopToBottom, this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
    //Add widget to layout.
    mainLayout->addWidget(m_titleBar);
    mainLayout->addWidget(m_storeSwitcher, 1);

    //Link retranslator.
    knI18n->link(this, &KNMusicStore::retranslate);
    retranslate();
}

KNMusicStore::~KNMusicStore()
{
    //Check first fetch pointer.
    if(m_firstFetch)
    {
        //Remove the first fetch pointer.
        m_firstFetch->deleteLater();
        //Reset the pointer.
        m_firstFetch=nullptr;
    }
}

QAbstractButton *KNMusicStore::tab()
{
    //Give back the tab widget.
    return m_tab;
}

void KNMusicStore::showIndex(KNMusicModel *musicModel,
                             const QModelIndex &index)
{
    //Well, it should be no use here.
    Q_UNUSED(musicModel)
    Q_UNUSED(index)
}

void KNMusicStore::loadPlugins()
{
    //Initial the backend.
    loadBackend(new KNMusicStoreNetease);
}

void KNMusicStore::resizeEvent(QResizeEvent *event)
{
    //Resize the widget.
    KNMusicStoreBase::resizeEvent(event);
    //Update the content size.
    updateContentWidget();
    //Resize the download list.
    m_downloadList->resize(width(), height()-m_titleBar->height());
}

void KNMusicStore::showEvent(QShowEvent *event)
{
    //Show the widget.
    KNMusicStoreBase::showEvent(event);
    //Check the switcher.
    if(m_firstFetch && (!m_firstFetch->isActive()))
    {
        //Start the first fetch.
        m_firstFetch->start();
    }
}

void KNMusicStore::retranslate()
{
    //Update the tab title.
    m_tab->setText(tr("Store"));
}

void KNMusicStore::onActionShowPanel(int category)
{
    //Show the title bar.
    m_titleBar->show();
    //Show the widget.
    showWidget(m_panels[category]);
    //Update the content size.
    updateContentWidget();
    //Hide the network mission.
    m_titleBar->setStatesButton(StateNetwork, false);
    //Reset the navigator.
    m_titleBar->setNavigationLevel(category);
}

void KNMusicStore::onActionFetchHome()
{
    //Set the network activity to start.
    m_titleBar->setStatesButton(StateNetwork, true);
    //Emit the fetch home signal.
    emit requireFetchHome();
}

void KNMusicStore::onActionFirstFetch()
{
    //Disconnect the timer.
    disconnect(m_firstFetch, 0, 0, 0);
    //Remove the first fetch timer.
    m_firstFetch->deleteLater();
    //Reset the first fetch pointer.
    m_firstFetch=nullptr;
    //Fetch the home widget.
    onActionFetchHome();
}

void KNMusicStore::loadBackend(KNMusicStoreBackend *backend)
{
    //Check the backend pointer.
    if(m_backend!=nullptr)
    {
        //Ignore the new backend.
        return;
    }
    //Save the backend.
    m_backend=backend;
    //Check the backend pointer.
    if(m_backend==nullptr)
    {
        //Ignore the backend set.
        return;
    }
    //Change relationship.
    m_backend->setParent(this);
    //Link current signal.
    connect(this, &KNMusicStore::requireFetchHome,
            m_backend, &KNMusicStoreBackend::fetchHomeInfo,
            Qt::QueuedConnection);
    //Set backends to all the widget.
    for(int i=0; i<StorePanelCount; ++i)
    {
        //Set the backend.
        m_panels[i]->setBackend(m_backend);
        //Link the requirement to backend.
        connect(m_panels[i], &KNMusicStorePanel::requireShowHome,
                m_backend, &KNMusicStoreBackend::fetchHomeInfo,
                Qt::QueuedConnection);
        connect(m_panels[i], &KNMusicStorePanel::requireShowAlbum,
                m_backend, &KNMusicStoreBackend::fetchAlbumDetail,
                Qt::QueuedConnection);
        connect(m_panels[i], &KNMusicStorePanel::requireShowSong,
                m_backend, &KNMusicStoreBackend::fetchSongDetail,
                Qt::QueuedConnection);
        connect(m_panels[i], &KNMusicStorePanel::requireSearch,
                m_backend, &KNMusicStoreBackend::fetchSearchResult,
                Qt::QueuedConnection);
    }
    //Link store widget to backend.
    connect(m_titleBar, &KNMusicStoreTitleBar::requireShowHome,
            this, &KNMusicStore::onActionFetchHome,
            Qt::QueuedConnection);
    //Link backend to store widget.
    connect(m_backend, &KNMusicStoreBackend::fetchComplete,
            this, &KNMusicStore::onActionShowPanel,
            Qt::QueuedConnection);
}

inline void KNMusicStore::showWidget(QWidget *widget)
{
    //Take the widget away.
    QWidget *currentWidget=m_storeSwitcher->takeWidget();
    //Check current widget.
    if(currentWidget!=nullptr)
    {
        //Recover the control of the widget.
        currentWidget->setParent(this);
        //Hide the widget.
        currentWidget->hide();
    }
    //Show the home widget.
    widget->show();
    //Set the home widget to be the switcher widget.
    m_storeSwitcher->setWidget(widget);
}

inline void KNMusicStore::updateContentWidget()
{
    //Resize the content widget.
    if(m_storeSwitcher->widget())
    {
        //Resize the switcher.
        m_storeSwitcher->widget()->resize(
                    m_storeSwitcher->widget()->width(),
                    qMax(m_storeSwitcher->sizeHint().height(),
                         m_storeSwitcher->height()-2-
                         (m_storeSwitcher->horizontalScrollBar()->isVisible()?
                              m_storeSwitcher->horizontalScrollBar()->height():
                              0)));
    }
}
