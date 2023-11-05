#ifndef FGEFILL_H
#define FGEFILL_H


#include <StructData/FGEDataStructGeometry.h>
#include <StructData/FGEDataStructNode.h>
#include <Geometry/FGEMagicUse.h>

class FGETreeLineItem{
    public:
    FGEDataLineItem *line;
    uint a, b;

};

class FGETreeLineBranch{
    public:
    QVector<FGETreeLineItem> lines;
};

class FGEDataTreeLines{
    public:
    FGEDataTreeLines(){
        loop = true;
    }

    void addNewBranch(){
        FGETreeLineBranch branch;
        branchs.push_back(branch);
    }
    void appendLineToBranch(FGETreeLineItem &il){
        if(branchs.size()==0){
            FGETreeLineBranch branch;
            branchs.push_back(branch);
        }

        branchs[branchs.size()-1].lines.push_back(il);
    }

    QVector<FGETreeLineBranch> branchs;
    bool loop;
};

class FGEFill
{
public:
    FGEFill();
    void fillFace(OpenGLFunctions *f, FGEDataNode *node, QString msg, bool error);
    void fillEdge(OpenGLFunctions *f, FGEDataNode* node);
    void fillFace2(OpenGLFunctions *f, FGEDataNode* node, QString msg, bool error);

    FGEFillListItemsMagicUse *first, *last;

private:
    FGEDataLineItem* _popTipLines(QVector<FGEDataLineItem *> &temp_line);
    FGEDataLineItem* _popLineLines(QVector<FGEDataLineItem*> &temp_line, FGEDataLineItem*line);
    void _swapItemMagicUse(FGEFillItemMagicUse *p);
    void _invertList(FGEFillListItemsMagicUse *item_list);
    bool orderList(QVector<FGEDataLineItem*> &lines, QVector<QPair<uint, uint>> &oln);
    bool orderListFromTip(QVector<FGEDataLineItem*> &lines, uint bt, uint et, QVector<QPair<uint, uint>> &oln);
    bool prepareTips(QVector<FGEDataLineItem*> &lines, QVector<QPair<uint, uint>> &tips);

    bool _createBraches(QVector<FGEDataLineItem*> &lines, FGEDataTreeLines *tr_ln, bool &loop);


    FGEDataTriangleItem * _createTriangle(FGEDataMesh *data_mesh, uint a, uint b, uint c, FGEDataVectorf3* pd, FGEDataVectorf3 *nfd, FGEDataVectorf2 *uvvd, FGESelectionEditMode *se);
    FGEDataQuadItem * _createQuad(FGEDataMesh *data_mesh, uint a, uint b, uint c, uint d, FGEDataVectorf3* pd, FGEDataVectorf3 *nfd, FGEDataVectorf2 *uvvd, FGESelectionEditMode *se);
    FGEDataPolygonItem * _createPolygon(FGEDataMesh *data_mesh, QVector<uint> &pos, FGEDataVectorf3* pd, FGEDataVectorf3 *nfd, FGEDataVectorf2 *uvvd, FGESelectionEditMode *se);
    void _createLine(FGEDataMesh *data_mesh, uint a, uint b, FGEDataVectorf3 *cfd, FGESelectionEditMode *se);
    bool _isLoop(QVector<FGETreeLineItem> &lines);
};

#endif // FGEFILL_H
