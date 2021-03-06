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

#ifndef KNMAINWINDOWHEADERBASE_H
#define KNMAINWINDOWHEADERBASE_H

#include "knmousesensewidget.h"

class KNCategoryPlugin;
/*!
 * \brief The KNMainWindowHeaderBase class is a port class of the main window
 * header. You can build all kinds of header from this function.
 */
class KNMainWindowHeaderBase : public KNMouseSenseWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Construct KNMainWindowHeaderBase with a give parent.
     * \param parent The parent widget of the header widget.
     */
    KNMainWindowHeaderBase(QWidget *parent = 0): KNMouseSenseWidget(parent){}

    /*!
     * \brief Add a widget to header. There may be many widgets will be added to
     * header, so the header widget should provide a layout or a stacked widget
     * to store these widgets. You'd better to use a box layout.
     * \param widget The widget pointer.
     * \param stretch The widget stretch parameter.
     * \param alignment The widget prefer alignment.
     */
    virtual void addHeaderWidget(QWidget *widget,
                                 int stretch=0,
                                 Qt::Alignment alignment=0)=0;

    /*!
     * \brief Add notification button widget to header widget.
     * \param widget The button widget pointer.
     */
    virtual void addNotificationButton(QWidget *widget)=0;

    /*!
     * \brief Set the category plugin. It is used to update the button caption.
     * \param plugin The category plugin.
     */
    virtual void setCategoryPlugin(KNCategoryPlugin *plugin)=0;

signals:
    /*!
     * \brief This signal will be used, when the user ask to show the preference
     * panel.
     */
    void requireShowPreference();
};

#endif // KNMAINWINDOWHEADERBASE_H
