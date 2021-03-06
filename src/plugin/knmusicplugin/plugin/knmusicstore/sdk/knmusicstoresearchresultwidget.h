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

#ifndef KNMUSICSTORESEARCHRESULTWIDGET_H
#define KNMUSICSTORESEARCHRESULTWIDGET_H

#include "knmusicstorepanel.h"

class KNAnimeLabelButton;
class KNMusicStoreAlbumTreeView;
class KNMusicStoreBackend;
/*!
 * \brief The KNMusicStoreSearchResultWidget class provide a list to display all
 * the search result from the backend.
 */
class KNMusicStoreSearchResultWidget : public KNMusicStorePanel
{
    Q_OBJECT
public:
    /*!
     * \brief Construct a KNMusicStoreSearchResultWidget widget.
     * \param parent The parent widget.
     */
    explicit KNMusicStoreSearchResultWidget(QWidget *parent = 0);

signals:

public slots:
    /*!
     * \brief Reimplemented from KNMusicStorePanel::setBackend().
     */
    void setBackend(KNMusicStoreBackend *backend) Q_DECL_OVERRIDE;

private slots:
    void retranslate();
    void onActionSearchComplete();

private:
    KNMusicStoreBackend *m_backend;
    KNMusicStoreAlbumTreeView *m_songTreeView;
};

#endif // KNMUSICSTORESEARCHRESULTWIDGET_H
