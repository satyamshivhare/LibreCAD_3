#ifndef UNDOMANAGERIMPL_H
#define UNDOMANAGERIMPL_H

#include <QStack>

#include "cad/const.h"

#include "cad/document/abstractdocument.h"
#include "cad/document/undomanager.h"
#include "cad/events/commitprocessevent.h"
#include "cad/operations/undoable.h"

namespace lc {

    /**
     * UndoManagerImpl manages a stack of operations and allows for
     * undo or re-do operations that where done on a canvas
     * @param maximumUndoLevels
     */
    class UndoManagerImpl: public UndoManager {
            Q_OBJECT
        public:
            UndoManagerImpl(AbstractDocument* document, int maximumUndoLevels);

            /*!
             * \brief redo an operation.
             * \sa lc::Undoable
             * \sa lc::UndoManager
             * \sa lc::UndoManagerImpl
             */
            virtual void redo();
            /*!
             * \brief undo an operation.
             * \sa lc::Undoable
             * \sa lc::UndoManager
             * \sa lc::UndoManagerImpl
             */
            virtual void undo();

            /*!
             * \brief Check if undo can be done
             * \sa lc::Undoable
             * \sa lc::UndoManager
             * \sa lc::UndoManagerImpl
             * \return
             */
            virtual bool canUndo() const;
            /*!
             * \brief Check if redo can be done
             * \sa lc::Undoable
             * \sa lc::UndoManager
             * \sa lc::UndoManagerImpl
             * \return
             */
            virtual bool canRedo() const;

            /*!
             * \brief Clears the Undo/Redo stack.
             * \sa lc::Undoable
             * \sa lc::UndoManager
             * \sa lc::UndoManagerImpl
             * \return
             */
            virtual void removeUndoables();

        private:
            /*!
             * \brief returns the document
             * \return document
             * \sa lc::AbstractDocument
             */
            virtual AbstractDocument* document() const {
                return _document;
            }
            AbstractDocument* _document;

        private:
            QList <shared_ptr<operation::Undoable> > _unDoables; /*!< Undo list */
            QStack <shared_ptr<operation::Undoable> > _reDoables; /*!< Redo stack */
            const int _maximumUndoLevels; /*!< Maximum undo level */

        public slots:
            void on_CommitProcessEvent(const lc::CommitProcessEvent& event);


    };

}

#endif // UNDOMANAGERIMPL_H