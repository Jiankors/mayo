/****************************************************************************
** Copyright (c) 2018, Fougue Ltd. <http://www.fougue.pro>
** All rights reserved.
** See license at https://github.com/fougue/mayo/blob/master/LICENSE.txt
****************************************************************************/

#pragma once

#include <TopoDS_Face.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>

namespace Mayo {

struct BRepUtils {
    template<typename FUNC>
    static void forEachSubShape(TopExp_Explorer& explorer, FUNC fn);

    template<typename FUNC>
    static void forEachSubShape(
            const TopoDS_Shape& shape, TopAbs_ShapeEnum shapeType, FUNC fn);

    template<typename FUNC>
    static void forEachSubFace(const TopoDS_Shape& shape, FUNC fn);

    static bool moreComplex(TopAbs_ShapeEnum lhs, TopAbs_ShapeEnum rhs);
};



// --
// -- Implementation
// --

template<typename FUNC>
void BRepUtils::forEachSubShape(TopExp_Explorer& explorer, FUNC fn)
{
    while (explorer.More()) {
        fn(explorer.Current());
        explorer.Next();
    }
}

template<typename FUNC>
void BRepUtils::forEachSubShape(
        const TopoDS_Shape& shape, TopAbs_ShapeEnum shapeType, FUNC fn)
{
    BRepUtils::forEachSubShape(TopExp_Explorer(shape, shapeType), std::move(fn));
}

template<typename FUNC>
void BRepUtils::forEachSubFace(const TopoDS_Shape& shape, FUNC fn)
{
    for (TopExp_Explorer expl(shape, TopAbs_FACE); expl.More(); expl.Next())
        fn(TopoDS::Face(expl.Current()));
}

} // namespace Mayo
