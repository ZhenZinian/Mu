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
#include "knlocalemanager.h"

#include "knmusicstoresonglistmodel.h"

KNMusicStoreSongListModel::KNMusicStoreSongListModel(QObject *parent) :
    QAbstractTableModel(parent),
    m_songList(QList<KNMusicStoreUtil::StoreSongItem>())
{
    //Link locale manager.
    knI18n->link(this, &KNMusicStoreSongListModel::retranslate);
    retranslate();
}

void KNMusicStoreSongListModel::clear()
{
    //Check album list is empty first.
    if(m_songList.isEmpty())
    {
        //If it's empty, then we don't need to check.
        return;
    }
    //As the documentation said, called this function first.
    beginRemoveRows(QModelIndex(), 0, m_songList.size()-1);
    //Remove all the data.
    m_songList.clear();
    //As the documentation said, called this after remove rows.
    endRemoveRows();
}

void KNMusicStoreSongListModel::appendItem(
        const KNMusicStoreUtil::StoreSongItem &item)
{
    //Add this sentence before appending.
    beginInsertRows(QModelIndex(),
                    m_songList.size(),
                    m_songList.size());
    //Append data.
    m_songList.append(item);
    //End insert.
    endInsertRows();
}


int KNMusicStoreSongListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    //Model size is equal as the song size.
    return m_songList.size();
}

int KNMusicStoreSongListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    //Column size is fixed.
    return 4;
}

QVariant KNMusicStoreSongListModel::data(const QModelIndex &index, int role) const
{
    //Check valid index first.
    if(!index.isValid())
    {
        //Failed to get the data.
        return QVariant();
    }
    //Give back the accounding to the index.
    const KNMusicStoreUtil::StoreSongItem &item=m_songList.at(index.row());
    //Return the information.
    switch(role)
    {
    case Qt::DisplayRole:
        //Check the column.
        switch(index.column())
        {
        case 0: //0 for index.
            return QString::number(item.index) + "    ";
        case 1: //1 for name.
            return item.name;
        case 2: //2 for duration.
            return item.duration;
        case 3: //3 for artist.
            return item.artist;
        }
    case Qt::SizeHintRole:
        return QSize(0, SongItemHeight);
    case Qt::TextAlignmentRole:
        return index.column()==0?
                    QVariant(Qt::AlignRight | Qt::AlignVCenter):
                    QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    default:
        //Failed for all the else data.
        return QVariant();
    }
}

QVariant KNMusicStoreSongListModel::headerData(int section,
                                            Qt::Orientation orientation,
                                            int role) const
{
    //Check orientation first.
    if(orientation==Qt::Vertical)
    {
        //No data will be provided for vertical header.
        return QVariant();
    }
    //Check section validation.
    if(section<0 || section>3)
    {
        //Invalid for invalid section.
        return QVariant();
    }
    //Check out the data.
    switch(role)
    {
    case Qt::DisplayRole:
        //Give back the title.
        return m_titles[section];
    case Qt::TextAlignmentRole:
        return Qt::AlignVCenter;
    default:
        //Or else, return an invalid data.
        return QVariant();
    }
}

void KNMusicStoreSongListModel::retranslate()
{
    //Update the title text.
    m_titles[1]=tr("Name");
    m_titles[2]=tr("Time");
    m_titles[3]=tr("Artist");
}

QVariant KNMusicStoreSongListModel::songData(int row)
{
    //Check the validation of the index.
    return (row<m_songList.size()) ?
                m_songList.at(row).songData : QVariant();
}
