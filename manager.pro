#-------------------------------------------------
#
# Project created by QtCreator 2012-08-23T11:01:26
#
#-------------------------------------------------

QT       += core gui xml opengl network

TARGET = manager
TEMPLATE = app

INCLUDEPATH += attributes constants struct editors resources
INCLUDEPATH += ../qt3d/painting ../qt3d/global ../qt3d/math3d ../qt3d/api ../qt3d/arrays ../qt3d/effects ../qt3d/geometry ../qt3d/graphicsview ../qt3d/materials ../qt3d/network ../qt3d/scene ../qt3d/surfaces ../qt3d/textures ../qt3d/viewing

LIBS += -L../qt3d-build -Wl,-rpath,../qt3d-build -lqt3d

SOURCES += main.cpp\
        MainWindow.cpp \
    JVMConfig.cpp \
    NativeFunction.cpp \
    JVMClass.cpp \
    constants/ConstantPool.cpp \
    constants/ConstantPoolInfo.cpp \
    constants/ConstantPoolInfo_Fieldref.cpp \
    constants/ConstantPoolInfo_Class.cpp \
    constants/ConstantPoolInfo_Methodref.cpp \
    constants/ConstantPoolInfo_InterfaceMethodref.cpp \
    constants/ConstantPoolInfo_String.cpp \
    constants/ConstantPoolInfo_Integer.cpp \
    constants/ConstantPoolInfo_Float.cpp \
    constants/ConstantPoolInfo_Long.cpp \
    constants/ConstantPoolInfo_Double.cpp \
    constants/ConstantPoolInfo_NameAndType.cpp \
    constants/ConstantPoolInfo_Utf8.cpp \
    Interfaces.cpp \
    Fields.cpp \
    Methods.cpp \
    Field.cpp \
    attributes/Attributes.cpp \
    attributes/AttributesInfo.cpp \
    attributes/AttributesInfo_ConstantValue.cpp \
    attributes/AttributesInfo_Code.cpp \
    attributes/AttributesInfo_Exceptions.cpp \
    attributes/AttributesInfo_InnerClasses.cpp \
    attributes/AttributesInfo_Synthetic.cpp \
    attributes/AttributesInfo_SourceFile.cpp \
    attributes/AttributesInfo_LineNumberTable.cpp \
    attributes/AttributesInfo_LocalVariableTable.cpp \
    attributes/AttributesInfo_Deprecated.cpp \
    attributes/AttributesInfo_StackMapTable.cpp \
    attributes/AttributesInfo_Signature.cpp \
    ExceptionHandler.cpp \
    ExceptionHandlers.cpp \
    Method.cpp \
    constants/ConstantPoolInfo_Dummy.cpp \
    JVMClassModel.cpp \
    JVMClassList.cpp \
    MessageModel.cpp \
    FieldsView.cpp \
    FieldsModel.cpp \
    JavaName.cpp \
    MethodsModel.cpp \
    MethodsView.cpp \
    Linker.cpp \
    struct/Struct_ClassTable.cpp \
    struct/Struct_Class.cpp \
    struct/Struct_CP.cpp \
    struct/Struct_CP_Class.cpp \
    struct/Struct_CP_Double.cpp \
    struct/Struct_CP_Field.cpp \
    struct/Struct_CP_Float.cpp \
    struct/Struct_CP_Integer.cpp \
    struct/Struct_CP_Long.cpp \
    struct/Struct_CP_Method.cpp \
    struct/Struct_CP_Name.cpp \
    struct/Struct_CP_String.cpp \
    struct/Struct_CP_Table.cpp \
    struct/Struct_CP_UTF8.cpp \
    struct/Struct_Exception_Handler_Table.cpp \
    struct/Struct_Exception_Handler.cpp \
    struct/Struct_Exceptions.cpp \
    struct/Struct_Field.cpp \
    struct/Struct_Field_Table.cpp \
    struct/Struct_Method.cpp \
    struct/Struct_Method_Table.cpp \
    constants/ConstantPoolVisitor.cpp \
    struct/Struct.cpp \
    struct/DataWriter.cpp \
    struct/DryRunWriter.cpp \
    ConfigView.cpp \
    NativeInterfaceModel.cpp \
    struct/MemoryWriter.cpp \
    struct/Struct_CP_Dummy.cpp \
    struct/ResolveContext.cpp \
    struct/MemoryMapWriter.cpp \
    editors/Bitmap2DDialog.cpp \
    editors/Bitmap2DView.cpp \
    resources/Bitmap2D.cpp \
    resources/Bitmap3D.cpp \
    editors/Bitmap3DDialog.cpp \
    editors/Bitmap3DRender.cpp \
    editors/Bitmap3DView.cpp

HEADERS  += MainWindow.h \
    JVMConfig.h \
    NativeFunction.h \
    JVMClass.h \
    constants/ConstantPool.h \
    constants/ConstantPoolInfo.h \
    constants/ConstantPoolInfo_Fieldref.h \
    constants/ConstantPoolInfo_Class.h \
    constants/ConstantPoolInfo_Methodref.h \
    constants/ConstantPoolInfo_InterfaceMethodref.h \
    constants/ConstantPoolInfo_String.h \
    constants/ConstantPoolInfo_Integer.h \
    constants/ConstantPoolInfo_Float.h \
    constants/ConstantPoolInfo_Long.h \
    constants/ConstantPoolInfo_Double.h \
    constants/ConstantPoolInfo_NameAndType.h \
    constants/ConstantPoolInfo_Utf8.h \
    Interfaces.h \
    Fields.h \
    Methods.h \
    Field.h \
    attributes/Attributes.h \
    attributes/AttributesInfo.h \
    attributes/AttributesInfo_ConstantValue.h \
    attributes/AttributesInfo_Code.h \
    attributes/AttributesInfo_Exceptions.h \
    attributes/AttributesInfo_InnerClasses.h \
    attributes/AttributesInfo_Synthetic.h \
    attributes/AttributesInfo_SourceFile.h \
    attributes/AttributesInfo_LineNumberTable.h \
    attributes/AttributesInfo_LocalVariableTable.h \
    attributes/AttributesInfo_Deprecated.h \
    attributes/AttributesInfo_StackMapTable.h \
    attributes/AttributesInfo_Signature.h \
    ExceptionHandler.h \
    ExceptionHandlers.h \
    Method.h \
    constants/ConstantPoolInfo_Dummy.h \
    JVMClassModel.h \
    JVMClassList.h \
    MessageModel.h \
    FieldsView.h \
    FieldsModel.h \
    JavaName.h \
    MethodsModel.h \
    MethodsView.h \
    Linker.h \
    struct/Struct_ClassTable.h \
    struct/Struct_Class.h \
    struct/Struct_CP.h \
    struct/Struct_CP_Class.h \
    struct/Struct_CP_Double.h \
    struct/Struct_CP_Field.h \
    struct/Struct_CP_Float.h \
    struct/Struct_CP_Integer.h \
    struct/Struct_CP_Long.h \
    struct/Struct_CP_Method.h \
    struct/Struct_CP_Name.h \
    struct/Struct_CP_String.h \
    struct/Struct_CP_Table.h \
    struct/Struct_CP_UTF8.h \
    struct/Struct_Exception_Handler_Table.h \
    struct/Struct_Exception_Handler.h \
    struct/Struct_Exceptions.h \
    struct/Struct_Field.h \
    struct/Struct_Field_Table.h \
    struct/Struct_Method.h \
    struct/Struct_Method_Table.h \
    constants/ConstantPoolVisitor.h \
    struct/Struct.h \
    struct/DataWriter.h \
    struct/DryRunWriter.h \
    ConfigView.h \
    NativeInterfaceModel.h \
    struct/MemoryWriter.h \
    struct/Struct_CP_Dummy.h \
    struct/ResolveContext.h \
    struct/MemoryMapWriter.h \
    editors/Bitmap2DDialog.h \
    editors/Bitmap2DView.h \
    resources/Bitmap2D.h \
    resources/Bitmap3D.h \
    editors/Bitmap3DDialog.h \
    editors/Bitmap3DRender.h \
    editors/Bitmap3DView.h

FORMS    += MainWindow.ui \
    FieldsView.ui \
    MethodsView.ui \
    ConfigView.ui \
    editors/Bitmap2DDialog.ui \
    editors/Bitmap3DDialog.ui \
    editors/Bitmap3DView.ui

OTHER_FILES += \
    data/jvmconfig/terminator V1.0d.cfg \
    data/jvmconfig/Terminator.cfg \
    data/jvmconfig/Spielbrett V1.1.cfg \
    data/jvmconfig/Spielbrett V1.0d.cfg \
    data/jvmconfig/LED Cube2.cfg \
    data/jvmconfig/LedCube.cfg

RESOURCES += \
    manager.qrc
