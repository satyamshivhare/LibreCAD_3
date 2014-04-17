#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>
#include <QString>

#include "cad/const.h"

#include "layermanager.h"
#include "selectionmanager.h"
#include "cad/geometry/geocoordinate.h"
#include "cad/base/cadentity.h"


namespace lc {

    namespace operation {
        class Operation;
    }

    class AbstractDocument : public QObject {
            Q_OBJECT
        public:
        protected:
            virtual void execute(shared_ptr<operation::Operation> operation) = 0;

            /*!
             * \brief begins an operation
             * \param operation
             */
            virtual void begin(shared_ptr<operation::Operation> operation) = 0;
            /*!
             * \brief commits an operation
             * \param operation
             */
            virtual void commit(shared_ptr<operation::Operation> operation) = 0;
            /*!
             * \brief operationStart Starts the operation.
             * \param operation
             */
            virtual void operationStart(shared_ptr<operation::Operation> operation);
            /*!
             * \brief operationFinnish Finishes the operation.
             * \param operation
             */
            virtual void operationFinnish(shared_ptr<operation::Operation> operation);
            /*!
             * \brief operationProcess process the operation.
             * \param operation
             */
            virtual void operationProcess(shared_ptr<operation::Operation> operation);

        public:
            // I am not to happy yet that this all needs to be public, however currently in a phase to get the proof of concept working
            /*!
             * \brief add an entity to document.
             * \param layerName Name of layer to which entity is to be added
             * \param cadEntity Entity to be added
             */
            virtual void addEntity(const QString& layerName, shared_ptr<const CADEntity> cadEntity) = 0;
            /*!
             * \brief replace an entity present in the document.
             * \param oldEntity Entity which is to be replaced
             * \param newEntity Entity which replaces the older entity.
             */
            virtual void replaceEntity(shared_ptr<const CADEntity> oldEntity, shared_ptr<const CADEntity> newEntity) = 0;
            /*!
             * \brief removes an entity from the document.
             * \param id ID of the entity to be removed.
             */
            virtual void removeEntity(ID_DATATYPE id) = 0;
            virtual void absoleteEntity(shared_ptr<const CADEntity> absoleteEntity) = 0;

            virtual void setLayerManager(shared_ptr<LayerManager> layerManager) = 0;
            virtual shared_ptr<LayerManager> layerManager() const = 0;

        protected:



        public:
            /*!
             * \brief Finds an entity by ID.
             * \param id ID of entity.
             * \return  CADEntity
             */
            virtual shared_ptr<const CADEntity> findEntityByID(ID_DATATYPE id) const = 0;
            virtual QString findEntityLayerByID(ID_DATATYPE id) const = 0;

        public:
            friend class BaseManager;
            friend class lc::operation::Operation;

    };

}

#endif // DOCUMENT_H