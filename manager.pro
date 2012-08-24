#-------------------------------------------------
#
# Project created by QtCreator 2012-08-23T11:01:26
#
#-------------------------------------------------

QT       += core gui xml

TARGET = manager
TEMPLATE = app

INCLUDEPATH += constants attributes

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
    Linker.cpp

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
    Linker.h

FORMS    += MainWindow.ui \
    FieldsView.ui \
    MethodsView.ui

OTHER_FILES += \
    resources/jvmconfig/terminator V1.0d.cfg \
    resources/jvmconfig/Terminator.cfg \
    resources/jvmconfig/Spielbrett V1.1.cfg \
    resources/jvmconfig/Spielbrett V1.0d.cfg \
    resources/jvmconfig/LED Cube2.cfg \
    resources/jvmconfig/LedCube.cfg

RESOURCES += \
    manager.qrc
