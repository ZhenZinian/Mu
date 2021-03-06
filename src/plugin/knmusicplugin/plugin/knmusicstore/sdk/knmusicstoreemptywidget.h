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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#ifndef KNMUSICSTOREEMPTYWIDGET_H
#define KNMUSICSTOREEMPTYWIDGET_H

#include <QWidget>

class QLabel;
class KNDarkWaitingWheel;
/*!
 * \brief The KNMusicStoreEmptyWidget class provides a state widget for music
 * store to initial the home page. This page will do nothing but display loading
 * and waiting information for music store.
 */
class KNMusicStoreEmptyWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Construct a KNMusicStoreEmptyWidget widget.
     * \param parent The parent widget.
     */
    explicit KNMusicStoreEmptyWidget(QWidget *parent = 0);

signals:

public slots:

protected:
    /*!
     * \brief Reimplemented from QWidget::showEvent().
     */
    void showEvent(QShowEvent *event) Q_DECL_OVERRIDE;

    /*!
     * \brief Reimplemented from QWidget::hideEvent().
     */
    void hideEvent(QHideEvent *event) Q_DECL_OVERRIDE;

private:
    KNDarkWaitingWheel *m_waitingWheel;
    QLabel *m_title;
};

#endif // KNMUSICSTOREEMPTYWIDGET_H
