/*
 *   File name: SelectionModel.cpp
 *   Summary:	Handling of selected items
 *   License:	GPL V2 - See file LICENSE for details.
 *
 *   Author:	Stefan Hundhammer <Stefan.Hundhammer@gmx.de>
 */

#include "SelectionModel.h"
#include "DirTreeModel.h"
#include "DirTree.h"
#include "SignalBlocker.h"
#include "Exception.h"
#include "Logger.h"


using namespace QDirStat;


SelectionModel::SelectionModel( DirTreeModel * dirTreeModel, QObject * parent ):
    QItemSelectionModel( dirTreeModel, parent ),
    _dirTreeModel( dirTreeModel ),
    _currentItem(0),
    _selectedItemsDirty(false)
{
    connect( this, SIGNAL( currentChanged	  ( QModelIndex, QModelIndex ) ),
	     this, SLOT	 ( propagateCurrentChanged( QModelIndex, QModelIndex ) ) );

    connect( this, SIGNAL( selectionChanged	    ( QItemSelection, QItemSelection  ) ),
	     this, SLOT	 ( propagateSelectionChanged( QItemSelection, QItemSelection  ) ) );
}


SelectionModel::~SelectionModel()
{
    // NOP
}


FileInfoSet SelectionModel::selectedItems()
{
    if ( _selectedItemsDirty )
    {
	// Build set of selected items from the selected model indexes

	_selectedItems.clear();

	foreach ( const QModelIndex index, selectedIndexes() )
	{
	    if ( index.isValid() )
	    {
		FileInfo * item = static_cast<FileInfo *>( index.internalPointer() );
		CHECK_MAGIC( item );

		//logDebug() << "Adding " << item << " to selected items" << endl;
		_selectedItems << item;
	    }
	}

	_selectedItemsDirty = false;
    }

    return _selectedItems;
}


void SelectionModel::propagateCurrentChanged( const QModelIndex & newCurrentIndex,
					      const QModelIndex & oldCurrentIndex )
{
    _currentItem = 0;

    if ( newCurrentIndex.isValid() )
    {
	_currentItem = static_cast<FileInfo *>( newCurrentIndex.internalPointer() );
	CHECK_MAGIC( _currentItem );
    }

    FileInfo * oldCurrentItem = 0;

    if ( oldCurrentIndex.isValid() )
    {
	oldCurrentItem = static_cast<FileInfo *>( oldCurrentIndex.internalPointer() );
	CHECK_MAGIC( oldCurrentItem );
    }

    emit currentItemChanged( _currentItem, oldCurrentItem );
}


void SelectionModel::propagateSelectionChanged( const QItemSelection & selected,
						const QItemSelection & deselected )
{
    Q_UNUSED( selected );
    Q_UNUSED( deselected );

    _selectedItemsDirty = true;
    emit selectionChanged();
    emit selectionChanged( selectedItems() );
}


void SelectionModel::selectItem( FileInfo * item )
{
    extendSelection( item,
		     true ); // clear
}


void SelectionModel::extendSelection( FileInfo * item, bool clear )
{
    if ( item )
    {
	QModelIndex index = _dirTreeModel->modelIndex( item, 0 );

	if ( index.isValid() )
	{
	    logDebug() << "Selecting " << item << endl;
	    SelectionFlags flags = Select | Rows;

	    if ( clear )
		flags |= Clear;

	    select( index, flags ); // emits selectionChanged()
	}
    }
    else
    {
	if ( clear )
	    clearSelection(); // emits selectionChanged()
    }
}


void SelectionModel::setCurrentItem( FileInfo * item, bool select )
{
    _currentItem = item;

    if ( item )
    {
	QModelIndex index = _dirTreeModel->modelIndex( item, 0 );

	if ( index.isValid() )
	{
	    logDebug() << "Setting current to " << item << endl;
	    setCurrentIndex( index, select ? ( Current | Select | Rows ) : Current );
	}
    }
    else
    {
	clearCurrentIndex();
    }
}


void SelectionModel::dumpSelectedItems()
{
    logDebug() << "Current item: " << _currentItem << endl;
    logDebug() << selectedItems().size() << " items selected" << endl;

    foreach ( FileInfo * item, selectedItems() )
    {
	logDebug() << "	 Selected: " << item << endl;
    }

    logNewline();
}

