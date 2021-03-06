#pragma once

#include <cad/meta/layer.h>

#include "cad/const.h"
#include "cad/interface/entitydispatch.h"
#include "cad/geometry/geocoordinate.h"
#include "cad/geometry/geocircle.h"
#include "cad/base/cadentity.h"
#include "cad/vo/entitycoordinate.h"
#include "cad/interface/snapable.h"
#include "cad/interface/splitable.h"
#include <cad/builders/circle.h>

#include <string>
#include <map>

namespace lc {
namespace entity {

class Circle : public std::enable_shared_from_this<Circle>,
    public CADEntity,
    public geo::Circle,
    public Snapable,
    public Splitable {
    friend class builder::CircleBuilder;

public:
    /**
     * @brief Circle, Circle Constructor
     * @param geo::Coordinate center, center of Circle
     * @param double radius, radius of circle
     * @param Layer_CSPtr _layer
     * @param MetaTypes metaTypes
     */
    Circle(const geo::Coordinate &center,
           double radius,
           meta::Layer_CSPtr layer,
           meta::MetaInfo_CSPtr metaInfo = nullptr,
           meta::Block_CSPtr block = nullptr);

    Circle(const Circle_CSPtr& other, bool sameID = false);

public:
    std::vector<EntityCoordinate> snapPoints(const geo::Coordinate &coord, const SimpleSnapConstrain & constrain, double minDistanceToSnap,
            int maxNumberOfSnapPoints) const override;

    geo::Coordinate nearestPointOnPath(const geo::Coordinate &coord) const override;
    geo::Coordinate nearestPointOnEntity(const geo::Coordinate &coord) const override;
    std::vector<CADEntity_CSPtr> splitEntity(const geo::Coordinate& coord) const override;
    lc::geo::Coordinate representingPoint() const override;

public:
    CADEntity_CSPtr move(const geo::Coordinate &offset) const override;
    CADEntity_CSPtr copy(const geo::Coordinate &offset) const override;
    CADEntity_CSPtr rotate(const geo::Coordinate &rotation_center, double rotation_angle) const override;
    CADEntity_CSPtr scale(const geo::Coordinate &scale_center,
                          const geo::Coordinate &scale_factor) const override;
    CADEntity_CSPtr mirror(const geo::Coordinate& axis1,
                           const geo::Coordinate& axis2) const override;
    const geo::Area boundingBox() const override;
    CADEntity_CSPtr modify(meta::Layer_CSPtr layer, meta::MetaInfo_CSPtr metaInfo, meta::Block_CSPtr block) const override;

public:
    void accept(GeoEntityVisitor &v) const override {
        v.visit(*this);
    }

    void dispatch(EntityDispatch &ed) const override {
        ed.visit(shared_from_this());
    }

    PropertiesMap availableProperties() const override;

    CADEntity_CSPtr setProperties(const PropertiesMap& propertiesMap) const override;

private:
    Circle(const builder::CircleBuilder& builder);
};

DECLARE_SHORT_SHARED_PTR(Circle)
}
}
// CIRCLE_H
