#pragma once

#include "cad/const.h"
#include "cad/interface/entitydispatch.h"

#include "cad/primitive/dimension.h"
#include "cad/base/cadentity.h"
#include "cad/vo/entitycoordinate.h"
#include "cad/math/lcmath.h"
#include <cad/primitive/point.h>
#include "cad/interface/draggable.h"
#include <cad/builders/dimdiametric.h>

namespace lc {
namespace entity {
class DimDiametric : public std::enable_shared_from_this<DimDiametric>, public CADEntity, public Dimension, virtual public Visitable, public Draggable {
    friend class lc::builder::DimDiametricBuilder;
public:
    /**
    * @brief DimDiametric
    * @param Dimension dimension
    * @param double leader
    * @param Layer_CSPtr layer
    * @param MetaTypes_CSPtr metaTypes
    */
    DimDiametric(geo::Coordinate definitionPoint,
                 geo::Coordinate middleOfText,
                 TextConst::AttachmentPoint attachmentPoint,
                 double angle,
                 double lineSpacingFactor,
                 TextConst::LineSpacingStyle lineSpacingStyle,
                 std::string explicitValue,
                 geo::Coordinate definitionPoint2,
                 double leader,
                 meta::Layer_CSPtr layer,
                 meta::MetaInfo_CSPtr metaInfo = nullptr,
                 meta::Block_CSPtr block = nullptr
                );

    DimDiametric(const DimDiametric_CSPtr& other, bool sameID = false);

private:
    DimDiametric(const lc::builder::DimDiametricBuilder& builder);

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

    double leader() const;

    geo::Coordinate definitionPoint2() const;  // Where definitionPoint is an edge, definitionPoint2 specifies the opposite edge. The mid point would be the center point.

protected:
    const double _leader;
    const geo::Coordinate _definitionPoint2;
public:
    void accept(GeoEntityVisitor &v) const override {
        v.visit(*this);
    }

    void dispatch(EntityDispatch &ed) const override {
        ed.visit(shared_from_this());
    }

public:
    std::map<unsigned int, lc::geo::Coordinate> dragPoints() const override;
    CADEntity_CSPtr setDragPoints(std::map<unsigned int, lc::geo::Coordinate> dragPoints) const override;

    PropertiesMap availableProperties() const override;

    CADEntity_CSPtr setProperties(const PropertiesMap& propertiesMap) const override;
};

DECLARE_SHORT_SHARED_PTR(DimDiametric)
}
}
