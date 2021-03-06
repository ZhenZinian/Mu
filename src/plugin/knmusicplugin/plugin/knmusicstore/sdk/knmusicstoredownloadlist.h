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
#ifndef KNMUSICSTOREDOWNLOADLIST_H
#define KNMUSICSTOREDOWNLOADLIST_H

#include <QWidget>

class QLabel;
class QPropertyAnimation;
class KNOpacityAnimeButton;
class KNMouseUnclickableWidget;
/*!
 * \brief The KNMusicStoreDownloadList class provides a widget which could hold
 * a download list view and download button. This widget will be used on store
 * widget to show the download queue and download states.
 */
class KNMusicStoreDownloadList : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Construct a KNMusicStoreDownloadList widget.
     * \param parent The parent widget.
     */
    explicit KNMusicStoreDownloadList(QWidget *parent = 0);

    /*!
     * \brief Get the download status button.
     * \return The button widget pointer.
     */
    KNOpacityAnimeButton *iconButton();

signals:

public slots:

protected:
    /*!
     * \brief Reimplemented from QWidget::resizeEvent().
     */
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from QWidget::mousePressEvent().
     */
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void retranslate();
    void onActionShowHideDownloadList();
    void onActionChangeOpacity(const QVariant &position);

private:
    inline void updaterAnimeParameter(bool isShown);
    KNOpacityAnimeButton *m_button;
    KNMouseUnclickableWidget *m_container;
    QLabel *m_title;
    QPropertyAnimation *m_showHideAnime;
};

#endif // KNMUSICSTOREDOWNLOADLIST_H
