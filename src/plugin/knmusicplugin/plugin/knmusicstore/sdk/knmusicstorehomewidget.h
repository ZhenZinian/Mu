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

#ifndef KNMUSICSTOREHOMEWIDGET_H
#define KNMUSICSTOREHOMEWIDGET_H

#include <QList>

#include "knmusicstorepanel.h"

class QBoxLayout;
class QLabel;
class KNMusicStoreAlbumList;
class KNMusicStoreBackend;
/*!
 * \brief The KNMusicStoreHomeWidget class is used to show the homepage image
 * and song information from the backend.
 */
class KNMusicStoreHomeWidget : public KNMusicStorePanel
{
    Q_OBJECT
public:
    /*!
     * \brief Construct a KNMusicStoreHomeWidget widget.
     * \param parent The parent widget pointer.
     */
    explicit KNMusicStoreHomeWidget(QWidget *parent = 0);

signals:
    /*!
     * \brief When the data is updated, this signal is emitted to reset the
     * position.
     */
    void requireResetPosition();

public slots:
    /*!
     * \brief Reimplemented from KNMusicStorePanel::setBackend().
     */
    void setBackend(KNMusicStoreBackend *backend) Q_DECL_OVERRIDE;

private slots:
    void retranslate();
    void updateListTitle();

private:
    enum HomePageBlocks
    {
        NewMusicBlock,
        HotTracksBlock,
        HomePageBlockCount
    };
    QList<QLabel *> m_listNames;
    QLabel *m_blockTitle[HomePageBlockCount];
    KNMusicStoreAlbumList *m_newMusicList, *m_hotTracks;
    KNMusicStoreBackend *m_backend;
    QBoxLayout *m_listLayout;
    int m_widgetHeight;
};

#endif // KNMUSICSTOREHOMEWIDGET_H
