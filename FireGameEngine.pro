QT       += core gui opengl xml

greaterThan(QT_MAJOR_VERSION, 4): QT += openglwidgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    3DViewport/AddObject/FGECreateCameraPropertiesForm.cpp \
    3DViewport/Armature/FGEArmatureEdit.cpp \
    3DViewport/Armature/FGEArmatureInteractionForm.cpp \
    3DViewport/Armature/FGEArmatureObject.cpp \
    3DViewport/Armature/FGEArmaturePose.cpp \
    3DViewport/Armature/FGEMenuBarArmatureWeightPainting.cpp \
    3DViewport/Armature/FGEPaintingSkinWeights.cpp \
    3DViewport/Armature/Form/FGEArmatureWeightPaintingForm.cpp \
    3DViewport/Armature/Form/FGEInverseKinematicsForm.cpp \
    3DViewport/Armature/Form/FGEPoseModeForm.cpp \
    3DViewport/Controller/FGEObjectSelectorController.cpp \
    3DViewport/GeneralView/CreateObjects/FGECreateArmaturePropertiesForm.cpp \
    3DViewport/GeneralView/CreateObjects/FGECreateBoxMeshPropertiesForm.cpp \
    3DViewport/GeneralView/CreateObjects/FGECreateCylinderCirclePropertiesForm.cpp \
    3DViewport/MenuBar/FGE3DViewMenuBar.cpp \
    3DViewport/Mesh/Form/DeleteSelectedVEFForm.cpp \
    3DViewport/Mesh/Form/FGEEditMeshForm.cpp \
    3DViewport/Mesh/Form/FGEExtrudeForm.cpp \
    3DViewport/Mesh/Form/FGEFillSelectedVEFForm.cpp \
    3DViewport/Mesh/Form/FGESelectedFaceForm.cpp \
    3DViewport/Modeling/FGEGeometryEditBoxForm.cpp \
    3DViewport/Modeling/FGEGeometryEditCircleForm.cpp \
    3DViewport/Modeling/FGEGeometryEditCylinderForm.cpp \
    3DViewport/Modeling/FGEGeometryEditMeshForm.cpp \
    3DViewport/Modeling/FGEGeometryEditPlaneForm.cpp \
    3DViewport/Modeling/FGEGeometryEditSphereForm.cpp \
    3DViewport/Modeling/FGEModelingInteractionForm.cpp \
    3DViewport/Modeling/FGEObjectEditing.cpp \
    3DViewport/Modeling/FGEObjectModelingCameraForm.cpp \
    3DViewport/Modeling/FGEObjectModelingForm.cpp \
    3DViewport/Modeling/FGEObjectTransformForm.cpp \
    3DViewport/Primitive/Device/FGEArmatureDevice.cpp \
    3DViewport/Primitive/Device/FGECameraDevice.cpp \
    3DViewport/Primitive/Device/FGEMeshRenderer.cpp \
    3DViewport/Primitive/Device/FGEOpenGLSceneRenderer.cpp \
    3DViewport/Primitive/Device/FGESelectionDevice.cpp \
    3DViewport/Primitive/Device/FGESkinDevice.cpp \
    3DViewport/Primitive/Painter/FGEBonePainter.cpp \
    3DViewport/Primitive/Painter/FGEEditModePainter.cpp \
    3DViewport/Primitive/Painter/FGEMaterialPreviewPainter.cpp \
    3DViewport/Primitive/Painter/FGEOutlinePainter.cpp \
    3DViewport/Primitive/Painter/FGEPointPainter.cpp \
    3DViewport/Primitive/Painter/FGESelectionPainter.cpp \
    3DViewport/Primitive/Painter/FGEWeightVertexPainter.cpp \
    3DViewport/Primitive/Painter/FGEWirePainter.cpp \
    Animation/FGEAnimation.cpp \
    Animation/FGEAnimationFrames.cpp \
    CSS/FGEBorder.cpp \
    CSS/FGEInner.cpp \
    Camera/FGECamera.cpp \
    Camera/FGECameraDataCompositionGuidesForm.cpp \
    Camera/FGECameraDataLensPropertyForm.cpp \
    Camera/FGECameraDataPropertiesForm.cpp \
    Camera/FGECameraPainter.cpp \
    Console/FGEConsoleForm.cpp \
    Console/FGEConsoleOpperations.cpp \
    GUI/InteractionContainer/FGEInteractionContainer.cpp \
    GUI/ListWidget/FGEListWidgetStyleAItem.cpp \
    GUI/ListWidget/FGEListWidgetStyleBItem.cpp \
    GUI/ListWidget/FGESimpleListWidget.cpp \
    Geometry/FGEGeo3DContLines.cpp \
    Geometry/FGEMagicUse.cpp \
    NodeShader/FGENodeShader.cpp \
    GLSL/FGEGLSL.cpp \
    GUI/DoubleSlider/FGEDoubleSlider.cpp \
    GUI/ListWidget/FGEListWidget.cpp \
    Geometry/FGE3DGeometryOctahedral.cpp \
    Gizmos/Scale/FGEDrawGizmoAxesScale.cpp \
    Gizmos/Scale/FGEDrawGizmoScale.cpp \
    Grid/FGEGrid.cpp \
    NodeShader/FGENodeShaderItem.cpp \
    Outliner/FGEOutlinerForm.cpp \
    Outliner/FGEStandardItem.cpp \
    Project/FGEProject.cpp \
    RenderTarget/FGEMultisimpleRenderTarget.cpp \
    RenderTarget/FGERenderTarget.cpp \
    Selector/FGEEditMeshSelector.cpp \
    Selector/FGEMeshSelector.cpp \
    Selector/FGESelectionArmature.cpp \
    Selector/FGESelectionArmatureEditable.cpp \
    Selector/FGESelectionArmaturePaintWeight.cpp \
    Selector/FGESelectionArmaturePose.cpp \
    Text/FGEText.cpp \
    TimeLine/CursorLine.cpp \
    TimeLine/FGEAnimationDelegateLIA.cpp \
    TimeLine/FGEAnimationSelectionForm.cpp \
    TimeLine/FGEAnimationTimeLine.cpp \
    TimeLine/FGEAnimationTimeLineApplied.cpp \
    TimeLine/FGEAnimationTimeLineForm.cpp \
    TimeLine/FGEAnimationTreeView.cpp \
    TimeLine/FGEEditKeyframe.cpp \
    TimeLine/FGEHeaderTimeLine.cpp \
    TimeLine/FGEI3DMListWidget.cpp \
    TimeLine/FGEItemTimeLine.cpp \
    TimeLine/FGEItemTreeTimeLine.cpp \
    TimeLine/FGEResizingView.cpp \
    TimeLine/FGETLLineForm.cpp \
    TimeLine/FGETimeLineWidget.cpp \
    TimeLine/Form/FGEAddNewAnimationForm.cpp \
    Tools/FGEColorPick.cpp \
    Tools/FGERandom.cpp \
    Transformation/FGETransformation.cpp \
    View/FGEViewOpperation.cpp \
    main.cpp \
    mainwindow.cpp \
    Gizmos/FGEGizmos.cpp \
    Gizmos/FGEGizmosCenter.cpp \
    Gizmos/FGEGizmosDefinition.cpp \
    Gizmos/FGESubSelectedTransformationMode.cpp \
    Geometry/FGE3DGeometryCircle.cpp \
    Geometry/FGE3DGeometryCone.cpp \
    Geometry/FGE3DGeometryCube.cpp \
    Geometry/FGE3DGeometryCylinder.cpp \
    Geometry/FGE3DGeometryGridLines.cpp \
    Geometry/FGE3DGeometryLine.cpp \
    Geometry/FGE3DGeometryPlane.cpp \
    Geometry/FGE3DGeometrySphere.cpp \
    Geometry/FGE3DGeometryTransformation.cpp \
    Light/FGELight.cpp \
    Tools/FGEConsole.cpp \
    StyleSheet/FGEStyleSheetGui.cpp \
    Gizmos/Rotate/FGEGizmosRotation.cpp \
    Gizmos/Rotate/FGEGizmosRotationItem.cpp \
    Gizmos/Scale/FGEGizmosScaleItem.cpp \
    Gizmos/Translate/FGEGizmosTranslation.cpp \
    Gizmos/Translate/FGEGizmosTranslationItem.cpp \
    Geometry/FGE3DGeometryBox.cpp \
    GUI/PushButton/fgepushbutton.cpp \
    GUI/PushButton/FGELineEdit.cpp \
    GUI/PushButton/FGEDoubleSpinBox.cpp \
    Geometry/fgenormal.cpp \
    Geometry/Extrude/FGEExtrudeLines.cpp \
    Geometry/Fill/FGEFill.cpp \
    Geometry/Delete/FGEDeleteFaces.cpp \
    Objects/TerrainGeneratorForm.cpp \
#    UVEditor/FGEUVEditorForm.cpp \
#    StructData/UVEditor/FGEDataUVEditMesh.cpp \
#    StructData/UVEditor/FGESelectionUVEditMode.cpp \
    StructData/FGEDataStructGeometry.cpp \
    StructData/MeshEditor/FGESelectionEditMode.cpp \
    Grid/FGESquareGrid.cpp \
#    UVEditor/Selection/FGEUVEEditModeSelection.cpp \
#    UVEditor/Primitive/FGEUVERenderDevice.cpp \
#    UVEditor/Primitive/FGEUVECoreRender.cpp \
#    UVEditor/Primitive/FGEUVEOpenGLWidget.cpp \
#    UVEditor/Painter/FGEPointUVPaint.cpp \
#    UVEditor/Painter/FGEWireUVPaint.cpp \
#    UVEditor/Painter/FGEUVEEditMode.cpp \
#    UVEditor/Form/FGEUVEImageForm.cpp \
    ParameterizationMesh/FGEUnwrapMesh.cpp \
    3DViewport/Primitive/FGECoreRenderPrimitive.cpp \
    3DViewport/Primitive/FGECreateCubeModel.cpp \
    3DViewport/Primitive/FGEOpenGLWidget.cpp \
    3DViewport/Primitive/FGEOpenGLWidgetActions.cpp \
    3DViewport/Primitive/FGEPrepareGLBuffer.cpp \
#    3DViewport/Primitive/FGERenderDevice.cpp \
    3DViewport/Primitive/FGESelectionRender.cpp \
    3DViewport/Primitive/FGESkeletonAnimation.cpp \
    3DViewport/Primitive/Painter/FGESeamPaint.cpp \
    3DViewport/SculptMesh/FGESculptMesh.cpp \
    3DViewport/SculptMesh/FGESculptMeshItem.cpp \
    3DViewport/SculptMesh/Form/FGESculptModeForm.cpp \
    Main/FGEDockWindows.cpp \
    Main/FGEPopupMenu.cpp \
    3DViewport/Form/FGEGL3DViewportForm.cpp \
    3DViewport/Form/FGEPropertiesObjectForm.cpp \
    3DViewport/GeneralView/CreateObjects/FGECreateCircleMeshPropertiesForm.cpp \
    3DViewport/GeneralView/CreateObjects/FGECreateCylinderMeshPropertiesForm.cpp \
    3DViewport/GeneralView/CreateObjects/FGECreatePlaneMeshPropertiesForm.cpp \
    3DViewport/GeneralView/CreateObjects/FGECreateSphereMeshPropertiesForm.cpp \
    3DViewport/TexturePaint/Form/FGETexturePaintForm.cpp \
    3DViewport/AddObject/FGECreateNewObject.cpp \
    3DViewport/AddObject/FGEListAddMeshForm.cpp \
    3DViewport/DisplayMode/FGEDisplayMode.cpp \
    3DViewport/DisplayMode/FGEDisplayModeForm.cpp \
    3DViewport/SelectionMode/FGESelectionModelsForm.cpp \
    3DViewport/SelectionMode/FGESelectionModels.cpp \
    3DViewport/TransformationType/FGETypesTransformationForm.cpp \
    3DViewport/TransformationType/FGETypesTransformation.cpp \
    3DViewport/GeneralView/CreateObjects/FGEItemCreateNewObject.cpp \
    Main/WidgetClass/FGEWidgetClass.cpp \
    Main/WidgetClass/FGEWidgetClassForm.cpp \
    Widgets/FGESpliteWidget.cpp \
    Widgets/FGESpliteWidgetForm.cpp \
    Widgets/FGETreeWidget.cpp \
    ParameterizationMesh/FGEUVSeparationBySeams.cpp \
#    UVEditor/Primitive/FGEUVEOpenGLWidgetActions.cpp

HEADERS += \
    3DViewport/AddObject/FGECreateCameraPropertiesForm.h \
    3DViewport/Armature/FGEArmatureEdit.h \
    3DViewport/Armature/FGEArmatureInteractionForm.h \
    3DViewport/Armature/FGEArmatureObject.h \
    3DViewport/Armature/FGEArmaturePose.h \
    3DViewport/Armature/FGEMenuBarArmatureWeightPainting.h \
    3DViewport/Armature/FGEPaintingSkinWeights.h \
    3DViewport/Armature/Form/FGEArmatureWeightPaintingForm.h \
    3DViewport/Armature/Form/FGEInverseKinematicsForm.h \
    3DViewport/Armature/Form/FGEPoseModeForm.h \
    3DViewport/Controller/FGEObjectSelectorController.h \
    3DViewport/Form/FGEGL3DViewportFormUI.h \
    3DViewport/GeneralView/CreateObjects/FGECreateArmaturePropertiesForm.h \
    3DViewport/GeneralView/CreateObjects/FGECreateBoxMeshPropertiesForm.h \
    3DViewport/GeneralView/CreateObjects/FGECreateCylinderCirclePropertiesForm.h \
    3DViewport/MenuBar/FGE3DViewMenuBar.h \
    3DViewport/Mesh/Form/DeleteSelectedVEFForm.h \
    3DViewport/Mesh/Form/FGEEditMeshForm.h \
    3DViewport/Mesh/Form/FGEExtrudeForm.h \
    3DViewport/Mesh/Form/FGEFillSelectedVEFForm.h \
    3DViewport/Mesh/Form/FGESelectedFaceForm.h \
    3DViewport/Modeling/FGEGeometryEditBoxForm.h \
    3DViewport/Modeling/FGEGeometryEditCircleForm.h \
    3DViewport/Modeling/FGEGeometryEditCylinderForm.h \
    3DViewport/Modeling/FGEGeometryEditMeshForm.h \
    3DViewport/Modeling/FGEGeometryEditPlaneForm.h \
    3DViewport/Modeling/FGEGeometryEditSphereForm.h \
    3DViewport/Modeling/FGEModelingInteractionForm.h \
    3DViewport/Modeling/FGEObjectEditing.h \
    3DViewport/Modeling/FGEObjectModelingCameraForm.h \
    3DViewport/Modeling/FGEObjectModelingForm.h \
    3DViewport/Modeling/FGEObjectTransformForm.h \
    3DViewport/Primitive/Device/FGECameraDevice.h \
    3DViewport/Primitive/Device/FGEMeshRenderer.h \
    3DViewport/Primitive/Device/FGEOpenGLSceneRenderer.h \
    3DViewport/Primitive/FGEStateOpperations.h \
    3DViewport/Primitive/Device/FGEArmatureDevice.h \
    3DViewport/Primitive/Device/FGEDrawingManager.h \
    3DViewport/Primitive/Device/FGESelectionDevice.h \
    3DViewport/Primitive/Device/FGESkinDevice.h \
    3DViewport/Primitive/Painter/FGEBonePainter.h \
    3DViewport/Primitive/Painter/FGEEditModePainter.h \
    3DViewport/Primitive/Painter/FGEMaterialPreviewPainter.h \
    3DViewport/Primitive/Painter/FGEOutlinePainter.h \
    3DViewport/Primitive/Painter/FGEPointPainter.h \
    3DViewport/Primitive/Painter/FGESelectionPainter.h \
    3DViewport/Primitive/Painter/FGEWeightVertexPainter.h \
    3DViewport/Primitive/Painter/FGEWirePainter.h \
    Animation/FGEAnimation.h \
    Animation/FGEAnimationFrames.h \
    CSS/FGEBorder.h \
    CSS/FGEInner.h \
    Camera/FGECamera.h \
    Camera/FGECameraDataCompositionGuidesForm.h \
    Camera/FGECameraDataLensPropertyForm.h \
    Camera/FGECameraDataPropertiesForm.h \
    Camera/FGECameraPainter.h \
    Console/FGEConsoleForm.h \
    Console/FGEConsoleOpperations.h \
    Core/FGEDefinition.h \
    Core/FGEShaderEditorTriggerFunction.h \
    Core/FGETriggerFunction.h \
    GUI/InteractionContainer/FGEInteractionContainer.h \
    GUI/ListWidget/FGEListWidgetStyleAItem.h \
    GUI/ListWidget/FGEListWidgetStyleBItem.h \
    GUI/ListWidget/FGESimpleListWidget.h \
    Geometry/FGE3DGeometryItem.h \
    Geometry/FGEGeo3DContLines.h \
    Geometry/FGEMagicUse.h \
    NodeShader/FGENodeShader.h \
    GLSL/FGEGLSL.h \
    GUI/DoubleSlider/FGEDoubleSlider.h \
    GUI/ListWidget/FGEListWidget.h \
    Geometry/FGE3DGeometryOctahedral.h \
    Gizmos/FGEGizmoConstraintAxis.h \
    Gizmos/Scale/FGEDrawGizmoAxesScale.h \
    Gizmos/Scale/FGEDrawGizmoScale.h \
    Gizmos/Scale/FGEGizmoScaleDefinition.h \
    Grid/FGEGrid.h \
    NodeShader/FGENodeShaderItem.h \
    Outliner/FGEOutlinerForm.h \
    Outliner/FGEStandardItem.h \
    Selector/FGEEditMeshSelector.h \
    Selector/FGEMeshSelector.h \
    Selector/FGESelectionArmature.h \
    Selector/FGESelectionArmatureEditable.h \
    Selector/FGESelectionArmaturePaintWeight.h \
    Selector/FGESelectionArmaturePose.h \
    StructData/FGEDataAttribLocation.h \
    StructData/FGEDataCamera.h \
    StructData/FGEDataCenterObjs.h \
    StructData/FGEDataGrid.h \
    StructData/FGEDataImport.h \
    StructData/FGEDataProject.h \
    StructData/FGEDataScreenBuffer.h \
    StructData/FGEDataSelectedArmature.h \
    StructData/FGEDataSelectedNode.h \
    StructData/FGEDataSelection.h \
    StructData/FGEDataStructAnimation.h \
    StructData/FGEDataStructGeometry.h \
    StructData/FGEDataStructMaterial.h \
    StructData/FGEDataStructNode.h \
    StructData/FGEDataStructResource.h \
    StructData/FGEDataStructScene.h \
    StructData/FGEDataStructSkin.h \
    StructData/FGEStructData.h \
    StructData/FGEDataStructArmature.h \
    Project/FGEProject.h \
    RenderTarget/FGEMultisimpleRenderTarget.h \
    RenderTarget/FGERenderTarget.h \
    StructData/Skin/FGEDataBoneInfluance.h \
    StructData/Skin/FGEDataSkin.h \
    StructData/Skin/FGEDataSkinConfiguration.h \
    StructData/Skin/FGEDataSkinLineBuffer.h \
    StructData/Skin/FGEDataSkinPointBuffer.h \
    StructData/Skin/FGEDataSkinPolygonBuffer.h \
    StructData/Skin/FGEDataSkinQuadBuffer.h \
    StructData/Skin/FGEDataSkinTriangleBuffer.h \
    Text/FGEText.h \
    TimeLine/CursorLine.h \
    TimeLine/FGEAnimationDelegateLIA.h \
    TimeLine/FGEAnimationSelectionForm.h \
    TimeLine/FGEAnimationTimeLine.h \
    TimeLine/FGEAnimationTimeLineApplied.h \
    TimeLine/FGEAnimationTimeLineForm.h \
    TimeLine/FGEAnimationTreeView.h \
    TimeLine/FGEEditKeyframe.h \
    TimeLine/FGEHeaderTimeLine.h \
    TimeLine/FGEI3DMListWidget.h \
    TimeLine/FGEItemTimeLine.h \
    TimeLine/FGEItemTreeTimeLine.h \
    TimeLine/FGEResizingView.h \
    TimeLine/FGETLLineForm.h \
    TimeLine/FGETimeLineExtra.h \
    TimeLine/FGETimeLineWidget.h \
    TimeLine/Form/FGEAddNewAnimationForm.h \
    Tools/FGEColorPick.h \
    Tools/FGERandom.h \
    Transformation/FGETransformation.h \
    View/FGEViewOpperation.h \
    mainwindow.h \
    Gizmos/FGEGizmos.h \
    Gizmos/FGEGizmosCenter.h \
    Gizmos/FGEGizmosDefinition.h \
    Gizmos/FGESubSelectedTransformationMode.h \
    Geometry/FGE3DGeometryCircle.h \
    Geometry/FGE3DGeometryCone.h \
    Geometry/FGE3DGeometryCube.h \
    Geometry/FGE3DGeometryCylinder.h \
    Geometry/FGE3DGeometryGridLines.h \
    Geometry/FGE3DGeometryLine.h \
    Geometry/FGE3DGeometryPlane.h \
    Geometry/FGE3DGeometrySphere.h \
    Geometry/FGE3DGeometryTransformation.h \
    Geometry/FGE3DGeometryDefinition.h \
    Light/FGELight.h \
    Tools/FGEConsole.h \
    StyleSheet/FGEStyleSheetGui.h \
    StructData/FGEDataImport.h \
    Gizmos/Rotate/FGEGizmosRotationItem.h \
    Gizmos/Rotate/FGEGizmosRotationItem.h \
    Gizmos/Rotate/FGEGizmosRotation.h \
    Gizmos/Scale/FGEGizmosScaleItem.h \
    Gizmos/Translate/FGEGizmosTranslation.h \
    Gizmos/Translate/FGEGizmosTranslationItem.h \
    Geometry/FGE3DGeometryBox.h \
    GUI/PushButton/fgepushbutton.h \
    GUI/PushButton/FGELineEdit.h \
    GUI/PushButton/FGEDoubleSpinBox.h \
    Geometry/FGENormal.h \
    StructData/FLPData/FGEDataPoints.h \
    StructData/FGEDataSharedDefinition.h \
    StructData/FLPData/FGEDataDataResources.h \
    StructData/FLPData/FGEDataLines.h \
    StructData/FLPData/FGEDataTriangles.h \
    StructData/FLPData/FGEDataQuads.h \
    Geometry/Extrude/FGEExtrudeLines.h \
    Geometry/Fill/FGEFill.h \
    Geometry/Delete/FGEDeleteFaces.h \
    StructData/FLPData/FGEDataPolygons.h \
    Objects/TerrainGeneratorForm.h \
#    UVEditor/FGEUVEditorForm.h \
#    UVEditor/FGEUVEditorFormUI.h \
    StructData/FLPData/FGEDataSeams.h \
#    StructData/UVEditor/FGEDataUVEditMesh.h \
#    StructData/UVEditor/FGESelectionUVEditMode.h \
    StructData/MeshEditor/FGESelectionEditMode.h \
    Grid/FGESquareGrid.h \
#    UVEditor/Selection/FGEUVEEditModeSelection.h \
#    UVEditor/Primitive/FGEUVERenderDevice.h \
#    UVEditor/Primitive/FGEUVECoreRender.h \
#    UVEditor/Primitive/FGEUVEOpenGLWidget.h \
#    UVEditor/Painter/FGEPointUVPaint.h \
#    UVEditor/Painter/FGEWireUVPaint.h \
#    UVEditor/Painter/FGEUVEEditMode.h \
#    UVEditor/Form/FGEUVEImageForm.h \
    ParameterizationMesh/FGEUnwrapMesh.h \
    3DViewport/Primitive/FGECoreRenderPrimitive.h \
    3DViewport/Primitive/FGECreateCubeModel.h \
    3DViewport/Primitive/FGEOpenGLWidget.h \
    3DViewport/Primitive/FGEOpenGLWidgetActions.h \
    3DViewport/Primitive/FGEPrepareGLBuffer.h \
#    3DViewport/Primitive/FGERenderDevice.h \
    3DViewport/Primitive/FGESelectionRender.h \
    3DViewport/Primitive/FGESkeletonAnimation.h \
    Core/FGEQGLFunctions.h \
    3DViewport/Primitive/Painter/FGESeamPaint.h \
    3DViewport/SculptMesh/FGESculptItem.h \
    3DViewport/SculptMesh/FGESculptMesh.h \
    3DViewport/SculptMesh/FGESculptMeshItem.h \
    3DViewport/SculptMesh/Form/FGESculptModeForm.h \
    Main/FGEDockWindows.h \
    Main/FGEPopupMenu.h \
    3DViewport/Form/FGEGL3DViewportForm.h \
    3DViewport/Form/FGEPropertiesObjectForm.h \
    3DViewport/GeneralView/CreateObjects/FGECreateCircleMeshPropertiesForm.h \
    3DViewport/GeneralView/CreateObjects/FGECreateCylinderMeshPropertiesForm.h \
    3DViewport/GeneralView/CreateObjects/FGECreatePlaneMeshPropertiesForm.h \
    3DViewport/GeneralView/CreateObjects/FGECreateSphereMeshPropertiesForm.h \
    3DViewport/TexturePaint/Form/FGETexturePaintForm.h \
    3DViewport/AddObject/FGECreateNewObject.h \
    3DViewport/AddObject/FGEListAddMeshForm.h \
    3DViewport/DisplayMode/FGEDisplayMode.h \
    3DViewport/DisplayMode/FGEDisplayModeForm.h \
    3DViewport/SelectionMode/FGESelectionModelsForm.h \
    3DViewport/SelectionMode/FGESelectionModels.h \
    3DViewport/TransformationType/FGETypesTransformationForm.h \
    3DViewport/TransformationType/FGETypesTransformation.h \
    3DViewport/GeneralView/CreateObjects/FGEItemCreateNewObject.h \
    Main/WidgetClass/FGEWidgetClass.h \
    Main/WidgetClass/FGEWidgetClassForm.h \
    Widgets/FGESpliteWidget.h \
    Widgets/FGESpliteWidgetForm.h \
    Widgets/FGETreeWidget.h \
    StructData/FLPData/FGEDataFaceAccess.h \
    ParameterizationMesh/FGEUVSeparationBySeams.h \
#    UVEditor/Primitive/FGEUVEOpenGLWidgetActions.h

FORMS += \
    3DViewport/AddObject/FGECreateCameraPropertiesForm.ui \
    3DViewport/Armature/FGEArmatureInteractionForm.ui \
    3DViewport/Armature/Form/FGEArmatureWeightPaintingForm.ui \
    3DViewport/Armature/Form/FGEInverseKinematicsForm.ui \
    3DViewport/Armature/Form/FGEPoseModeForm.ui \
    3DViewport/GeneralView/CreateObjects/FGECreateArmaturePropertiesForm.ui \
    3DViewport/GeneralView/CreateObjects/FGECreateBoxMeshPropertiesForm.ui \
    3DViewport/GeneralView/CreateObjects/FGECreateCylinderCirclePropertiesForm.ui \
    3DViewport/Mesh/Form/DeleteSelectedVEFForm.ui \
    3DViewport/Mesh/Form/FGEEditMeshForm.ui \
    3DViewport/Mesh/Form/FGEExtrudeForm.ui \
    3DViewport/Mesh/Form/FGEFillSelectedVEFForm.ui \
    3DViewport/Mesh/Form/FGESelectedFaceForm.ui \
    3DViewport/Modeling/FGEGeometryEditBoxForm.ui \
    3DViewport/Modeling/FGEGeometryEditCircleForm.ui \
    3DViewport/Modeling/FGEGeometryEditCylinderForm.ui \
    3DViewport/Modeling/FGEGeometryEditMeshForm.ui \
    3DViewport/Modeling/FGEGeometryEditPlaneForm.ui \
    3DViewport/Modeling/FGEGeometryEditSphereForm.ui \
    3DViewport/Modeling/FGEModelingInteractionForm.ui \
    3DViewport/Modeling/FGEObjectModelingCameraForm.ui \
    3DViewport/Modeling/FGEObjectModelingForm.ui \
    3DViewport/Modeling/FGEObjectTransformForm.ui \
    3DViewport/Object/Form/FGEEditObjectForm.ui \
    Camera/FGECameraDataCompositionGuidesForm.ui \
    Camera/FGECameraDataLensPropertyForm.ui \
    Camera/FGECameraDataPropertiesForm.ui \
    Console/FGEConsoleForm.ui \
    GUI/InteractionContainer/FGEInteractionContainer.ui \
    GUI/ListWidget/FGEListWidgetStyleAItem.ui \
    Outliner/FGEOutlinerForm.ui \
    TimeLine/FGEAnimationSelectionForm.ui \
    TimeLine/FGEAnimationTimeLineForm.ui \
    TimeLine/FGEItemTreeTimeLine.ui \
    TimeLine/FGETLLineForm.ui \
    TimeLine/Form/FGEAddNewAnimationForm.ui \
    Widgets/fgesplitewidgetform.ui \
    mainwindow.ui \
    Selector/FGESelectBoxForm.ui \
    Objects/TerrainGeneratorForm.ui \
#    UVEditor/FGEUVEditorForm.ui \
#    UVEditor/Form/FGEUVEImageForm.ui \
    Main/FGEPopupMenu.ui \
    3DViewport/Form/FGEGL3DViewportForm.ui \
    3DViewport/Form/FGEPropertiesObjectForm.ui \
    3DViewport/GeneralView/CreateObjects/FGECreateCircleMeshPropertiesForm.ui \
    3DViewport/GeneralView/CreateObjects/FGECreateCylinderMeshPropertiesForm.ui \
    3DViewport/GeneralView/CreateObjects/FGECreatePlaneMeshPropertiesForm.ui \
    3DViewport/GeneralView/CreateObjects/FGECreateSphereMeshPropertiesForm.ui \
    3DViewport/SculptMesh/Form/FGESculptModeForm.ui \
    3DViewport/TexturePaint/Form/FGETexturePaintForm.ui \
    3DViewport/AddObject/FGEListAddMeshForm.ui \
    3DViewport/DisplayMode/FGEDisplayModeForm.ui \
    3DViewport/SelectionMode/FGESelectionModelsForm.ui \
    3DViewport/TransformationType/FGETypesTransformationForm.ui \
    Main/WidgetClass/FGEWidgetClassForm.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc \
    StyleSheet/style.qrc

DISTFILES += \
    Logo/large logo.png \
    Logo/logo.png \
    Logo/logo.svg \
    Shader/Bone/bone.frag \
    Shader/Bone/bone.vert \
    Shader/EditMode/Black.frag \
    Shader/EditMode/Black.vert \
    Shader/EditMode/Points.frag \
    Shader/EditMode/Points.vert \
    Shader/Gizmos/Rotation/GizmosAxe.frag \
    Shader/Gizmos/Rotation/GizmosAxe.vert \
    Shader/Gizmos/Rotation/GizmosInner.frag \
    Shader/Gizmos/Rotation/GizmosInner.vert \
    Shader/Gizmos/Rotation/GizmosOuter.frag \
    Shader/Gizmos/Rotation/GizmosOuter.vert \
    Shader/Gizmos/Rotation/GizmosRotation.frag \
    Shader/Gizmos/Rotation/GizmosRotation.vert \
    Shader/Gizmos/Rotation/GizmosSelectedAxe.frag \
    Shader/Gizmos/Rotation/GizmosSelectedAxe.vert \
    Shader/Gizmos/Rotation/GizmosSelectedOuter.frag \
    Shader/Gizmos/Rotation/GizmosSelectedOuter.vert \
    Shader/Gizmos/Rotation/GizmosSimpleAxeRotation.frag \
    Shader/Gizmos/Rotation/GizmosSimpleAxeRotation.vert \
    Shader/Gizmos/ScaleShader/ScaleSphere.frag \
    Shader/Gizmos/ScaleShader/ScaleSphere.vert \
    Shader/Gizmos/TranslationShader/GizmosPointCenter.frag \
    Shader/Gizmos/TranslationShader/GizmosPointCenter.vert \
    Shader/Gizmos/TranslationShader/GizmosTranslationLine.frag \
    Shader/Gizmos/TranslationShader/GizmosTranslationLine.vert \
    Shader/Grid/Axe.frag \
    Shader/Grid/Axe.vert \
    Shader/Grid/fragment.frag \
    Shader/Grid/vertex.vert \
    Shader/Model/1.frag \
    Shader/Model/1.vert \
    Shader/Model/MaterialPreview/MaterialPreview.frag \
    Shader/Model/MaterialPreview/MaterialPreview.vert \
    Shader/Model/MaterialPreview/_VEC3_VERTEX_VEC3_NORMAL_VEC2_TEXCOORD.frag \
    Shader/Model/MaterialPreview/_VEC3_VERTEX_VEC3_NORMAL_VEC2_TEXCOORD.vert \
    Shader/Model/MaterialPreview/_VEC3_VERTEX_VEC3_NORMAL_VEC2_TEXCOORD_VEC4_JOINTS_VEC4_WIGHTS.frag \
    Shader/Model/MaterialPreview/_VEC3_VERTEX_VEC3_NORMAL_VEC2_TEXCOORD_VEC4_JOINTS_VEC4_WIGHTS.vert \
    Shader/Model/Point/Point.frag \
    Shader/Model/Point/Point.vert \
    Shader/Model/Selection/Selection.frag \
    Shader/Model/Selection/Selection.vert \
    Shader/Model/Selection/_VEC3_VERTEX_VEC3_NORMAL_VEC2_TEXCOORD.frag \
    Shader/Model/Selection/_VEC3_VERTEX_VEC3_NORMAL_VEC2_TEXCOORD.vert \
    Shader/Model/Selection/_VEC3_VERTEX_VEC3_NORMAL_VEC2_TEXCOORD_VEC4_JOINTS_VEC4_WIGHTS.frag \
    Shader/Model/Selection/_VEC3_VERTEX_VEC3_NORMAL_VEC2_TEXCOORD_VEC4_JOINTS_VEC4_WIGHTS.vert \
    Shader/Model/WeightVertex/WeightVertex.frag \
    Shader/Model/WeightVertex/WeightVertex.vert \
    Shader/Model/WeightVertex/_VEC3_VERTEX_VEC3_WEIGHTS.frag \
    Shader/Model/WeightVertex/_VEC3_VERTEX_VEC3_WEIGHTS.vert \
    Shader/Model/Wire/Frag.frag \
    Shader/Model/Wire/Vert.vert \
    Shader/Model/Wire/_VEC3_VERTEX_VEC3_NORMAL_VEC2_TEXCOORD_VEC4_JOINTS_VEC4_WIGHTS.frag \
    Shader/Model/Wire/_VEC3_VERTEX_VEC3_NORMAL_VEC2_TEXCOORD_VEC4_JOINTS_VEC4_WIGHTS.vert \
    Shader/Primitive/Painter/Wire.frag \
    Shader/Primitive/Painter/Wire.vert \
    Shader/Selector/selectBox.frag \
    Shader/Selector/selectBox.vert \
    Shader/Selector/select_model_bn.frag \
    Shader/Selector/select_model_bn.vert \
    Shader/SimpleRender/Simple.frag \
    Shader/SimpleRender/Simple.vert \
    Shader/Viewer/SelectAxeViwer.frag \
    Shader/Viewer/SelectAxeViwer.vert \
    StyleSheet/style.st \
    Shader/Scene/FragmentShaderSelection.frag \
    Shader/Scene/VertexShaderSelection.vert \
    Shader/Primitive/anim_model.frag \
    Shader/Primitive/anim_model.vert \
    Shader/Primitive/geo_model.frag \
    Shader/Primitive/geo_model.vert \
    Shader/Gizmos/Rotation/GizmosVLinesFragmentShader.sh \
    Shader/Gizmos/Rotation/GizmosVLinesVertexShader.sh \
    Shader/Gizmos/RotationShder/GizmosRotationAxeFragmentShader.sh \
    Shader/Gizmos/RotationShder/GizmosRotationAxeLinesFragmentShader.sh \
    Shader/Gizmos/RotationShder/GizmosRotationAxeLinesVertexShader.sh \
    Shader/Gizmos/RotationShder/GizmosRotationAxeVertexShader.sh \
    Shader/Gizmos/RotationShder/GizmosRotationCenterFragmentShader.sh \
    Shader/Gizmos/RotationShder/GizmosRotationCenterVertexShader.sh \
    Shader/Gizmos/RotationShder/GizmosRotationFragmentShader.sh \
    Shader/Gizmos/RotationShder/GizmosRotationSelectionAxeFragmentShader.sh \
    Shader/Gizmos/RotationShder/GizmosRotationSelectionAxeVertexShader.sh \
    Shader/Gizmos/RotationShder/GizmosRotationSelectionCenterFragmentShader.sh \
    Shader/Gizmos/RotationShder/GizmosRotationSelectionCenterVertexShader.sh \
    Shader/Gizmos/RotationShder/GizmosRotationSelectionWFragmentShader.sh \
    Shader/Gizmos/RotationShder/GizmosRotationSelectionWVertexShader.sh \
    Shader/Gizmos/RotationShder/GizmosRotationVertexShader.sh \
    Shader/Gizmos/RotationShder/GizmosRotationWFragmentShader.sh \
    Shader/Gizmos/RotationShder/GizmosRotationWVertexShader.sh \
    Shader/Gizmos/TranslationShader/New Folder/GizmosTranslationFragmentShader.sh \
    Shader/Gizmos/TranslationShader/New Folder/GizmosTranslationFragmentShaderCone.sh \
    Shader/Gizmos/TranslationShader/New Folder/GizmosTranslationSelectionFragmentShader.sh \
    Shader/Gizmos/TranslationShader/New Folder/GizmosTranslationSelectionVertexShader.sh \
    Shader/Gizmos/TranslationShader/New Folder/GizmosTranslationVertexShader.sh \
    Shader/Gizmos/TranslationShader/New Folder/GizmosTranslationVertexShaderCone.sh \
    Shader/Gizmos/TranslationShader/GizmosTranslationFragmentShader.sh \
    Shader/Gizmos/TranslationShader/GizmosTranslationFragmentShaderSelection.sh \
    Shader/Gizmos/TranslationShader/GizmosTranslationNoViewVertexShader.sh \
    Shader/Gizmos/TranslationShader/GizmosTranslationVertexShader.sh \
    Shader/Gizmos/TranslationShader/GizmosTranslationVertexShaderSelection.sh \
    Shader/Gizmos/Rotation/GizmosAngle.frag \
    Shader/Gizmos/Rotation/GizmosAngleW.frag \
    Shader/Gizmos/Rotation/GizmosSimpleRotation.frag \
    Shader/Gizmos/TranslationShader/translation_grid.frag \
    Shader/Gizmos/Rotation/GizmosAngle.vert \
    Shader/Gizmos/Rotation/GizmosAngleW.vert \
    Shader/Gizmos/Rotation/GizmosSimpleRotation.vert \
    Shader/Gizmos/TranslationShader/translation_grid.vert \
    Shader/Screen/FragmentShader.frag \
    Shader/Screen/VertexShader.vert \
    Shader/Screen/OutlinePostprocessing.frag \
    Shader/Screen/OutlinePostprocessing.vert \
    Shader/Screen/WhiteObject.fragment \
    Shader/Screen/WhiteObject.vertex \
    Shader/Gizmos/ScaleShader/New Folder/GizmosTranslationFragmentShader.sh \
    Shader/Gizmos/ScaleShader/New Folder/GizmosTranslationFragmentShaderCone.sh \
    Shader/Gizmos/ScaleShader/New Folder/GizmosTranslationSelectionFragmentShader.sh \
    Shader/Gizmos/ScaleShader/New Folder/GizmosTranslationSelectionVertexShader.sh \
    Shader/Gizmos/ScaleShader/New Folder/GizmosTranslationVertexShader.sh \
    Shader/Gizmos/ScaleShader/New Folder/GizmosTranslationVertexShaderCone.sh \
    Shader/Gizmos/ScaleShader/Scale_grid.frag \
    Shader/Gizmos/ScaleShader/Scale_grid.vert \
    Shader/Gizmos/ScaleShader/GizmosScale.vert \
    Shader/Gizmos/ScaleShader/GizmosScale.frag \
    Shader/Gizmos/ScaleShader/GizmosScaleNoView.vert \
    Shader/Gizmos/ScaleShader/GizmosScaleSelection.vert \
    Shader/Gizmos/ScaleShader/GizmosScaleSelection.frag \
    Shader/Gizmos/ScaleShader/GizmosScaleLine.frag \
    Shader/Gizmos/ScaleShader/GizmosScaleLine.vert \
    Shader/Model/Outline/_VEC3_VERTEX_VEC3_NORMAL_VEC2_TEXCOORD_VEC4_JOINTS_VEC4_WIGHTS.frag \
    Shader/Model/Outline/_VEC3_VERTEX_VEC3_NORMAL_VEC2_TEXCOORD.frag \
    Shader/Model/Outline/_VEC3_VERTEX_VEC3_NORMAL_VEC2_TEXCOORD_VEC4_JOINTS_VEC4_WIGHTS.vert \
    Shader/Model/Outline/_VEC3_VERTEX_VEC3_NORMAL_VEC2_TEXCOORD.vert \
    Shader/Model/PointEditMode/_VEC3_VERTEX_VEC3_NORMAL_VEC2_TEXCOORD_VEC4_JOINTS_VEC4_WIGHTS.frag \
    Shader/Model/PointEditMode/_VEC3_VERTEX_VEC3_NORMAL_VEC2_TEXCOORD.frag \
    Shader/Model/PointEditMode/_VEC3_VERTEX_VEC3_NORMAL_VEC2_TEXCOORD_VEC4_JOINTS_VEC4_WIGHTS.vert \
    Shader/Model/PointEditMode/_VEC3_VERTEX_VEC3_NORMAL_VEC2_TEXCOORD.vert \
    Shader/CreateObjects/plane.vert \
    Shader/CreateObjects/plane.frag \
    Shader/Model/Wire/_VEC3_VERTEX_VEC3_COLOR.vert \
    Shader/Model/Wire/_VEC3_VERTEX_VEC3_COLOR.frag \
    Shader/Model/Point/_VEC3_VERTEX_VEC3_COLOR.frag \
    Shader/Model/Point/_VEC3_VERTEX_VEC3_NORMAL_VEC2_TEXCOORD_VEC4_JOINTS_VEC4_WIGHTS.frag \
    Shader/Model/Point/_VEC3_VERTEX_VEC3_COLOR.vert \
    Shader/Model/Point/_VEC3_VERTEX_VEC3_NORMAL_VEC2_TEXCOORD_VEC4_JOINTS_VEC4_WIGHTS.vert \
    Shader/Sculpt/GizmoSculpt.frag \
    Shader/Sculpt/GizmoSculpt.vert \
#    Shader/UVEditor/UV.frag \
#    Shader/UVEditor/UV.vert \
#    Shader/Grid/SquareGrid.vert \
#    Shader/Grid/SquareGrid.frag \
#    Shader/UVEditor/UVPoint.vert \
#    Shader/UVEditor/UVPoint.frag \
#    Shader/UVEditor/Background.vert \
#    Shader/UVEditor/Background.frag



unix|win32: LIBS += -lfreetype
unix|win32: LIBS += -lftgl
unix|win32: LIBS += -ligl
