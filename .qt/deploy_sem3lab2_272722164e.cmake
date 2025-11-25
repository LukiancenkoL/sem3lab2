include("/home/misha/personal/qt-timer/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/sem3lab2-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "/home/misha/personal/qt-timer/sem3lab2"
    GENERATE_QT_CONF
)
