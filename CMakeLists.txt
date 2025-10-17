# CMake-Mindestversion festlegen
cmake_minimum_required(VERSION 3.10)

# Projektname definieren
project(Axis2)

# Prüfen, ob das Betriebssystem Windows ist, da MFC verwendet wird
if(NOT WIN32)
    message(FATAL_ERROR "Dieses Projekt verwendet MFC und kann nur unter Windows kompiliert werden.")
endif()

# C++-Standard auf C++17 setzen
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MFC-Unterstützung aktivieren (Verwendung als Shared-DLL)
set(CMAKE_MFC_FLAG 2)

# Include-Verzeichnisse hinzufügen
include_directories(Axis2)

# Quell- und Header-Dateien auflisten
set(SOURCES
    Axis2/AboutDlg.cpp
    Axis2/AccountTab.cpp
    Axis2/Adddestination.cpp
    Axis2/Axis2.cpp
    Axis2/Axis2Dlg.cpp
    Axis2/AxisLog.cpp
    Axis2/AxisThread.cpp
    Axis2/BitmapEx.cpp
    Axis2/BtnST.cpp
    Axis2/ClientInfo.cpp
    Axis2/ColorSelectionDlg.cpp
    Axis2/CommandsTab.cpp
    Axis2/Common.cpp
    Axis2/DockingPage.cpp
    Axis2/DoorWizard.cpp
    Axis2/GeneralTab.cpp
    Axis2/Ini.cpp
    Axis2/ItemTab.cpp
    Axis2/ItemTweakTab.cpp
    Axis2/LauncherTab.cpp
    Axis2/LightWizard.cpp
    Axis2/LogTab.cpp
    Axis2/MiscTab.cpp
    Axis2/MultiView.cpp
    Axis2/PlayerTweakTab.cpp
    Axis2/Profile_DLG.cpp
    Axis2/ProgressBar.cpp
    Axis2/Random.cpp
    Axis2/ReminderTab.cpp
    Axis2/Reminder_DLG.cpp
    Axis2/RemoteConsole.cpp
    Axis2/RemoteConsoleDlg.cpp
    Axis2/RemoteConsoleLoginDlg.cpp
    Axis2/RemoteProfileLoginDlg.cpp
    Axis2/ScriptEditor.cpp
    Axis2/ScriptEditorFrame.cpp
    Axis2/ScriptInfo.cpp
    Axis2/ScriptObjects.cpp
    Axis2/SearchCritDlg.cpp
    Axis2/SettingsDlg.cpp
    Axis2/Settings_General.cpp
    Axis2/Settings_Item.cpp
    Axis2/Settings_OverridePaths.cpp
    Axis2/Settings_Paths.cpp
    Axis2/Settings_Spawn.cpp
    Axis2/Settings_Travel.cpp
    Axis2/SpawnTab.cpp
    Axis2/TabCtrl.cpp
    Axis2/ToolBar.cpp
    Axis2/TravelTab.cpp
    Axis2/UOart.cpp
    Axis2/UOmap.cpp
    Axis2/WorldMap.cpp
    Axis2/stdafx.cpp
)

set(HEADERS
    Axis2/AboutDlg.h
    Axis2/AccountTab.h
    Axis2/Adddestination.h
    Axis2/Axis2.h
    Axis2/Axis2Dlg.h
    Axis2/AxisLog.h
    Axis2/AxisThread.h
    Axis2/BitmapEx.h
    Axis2/BtnST.h
    Axis2/ClientInfo.h
    Axis2/ColorSelectionDlg.h
    Axis2/CommandsTab.h
    Axis2/Common.h
    Axis2/DockingPage.h
    Axis2/DoorWizard.h
    Axis2/GeneralTab.h
    Axis2/Ini.h
    Axis2/ItemTab.h
    Axis2/ItemTweakTab.h
    Axis2/LauncherTab.h
    Axis2/LightWizard.h
    Axis2/LogTab.h
    Axis2/MiscTab.h
    Axis2/Multiview.h
    Axis2/PlayerTweakTab.h
    Axis2/Profile_DLG.h
    Axis2/ProgressBar.h
    Axis2/Random.h
    Axis2/ReminderTab.h
    Axis2/Reminder_DLG.h
    Axis2/RemoteConsole.h
    Axis2/RemoteConsoleDlg.h
    Axis2/RemoteConsoleLoginDlg.h
    Axis2/RemoteProfileLoginDlg.h
    Axis2/ScriptEditor.h
    Axis2/ScriptEditorFrame.h
    Axis2/ScriptInfo.h
    Axis2/ScriptObjects.h
    Axis2/SearchCritDlg.h
    Axis2/SettingsDlg.h
    Axis2/Settings_General.h
    Axis2/Settings_Item.h
    Axis2/Settings_OverridePaths.h
    Axis2/Settings_Paths.h
    Axis2/Settings_Spawn.h
    Axis2/Settings_Travel.h
    Axis2/SpawnTab.h
    Axis2/TabCtrl.h
    Axis2/ToolBar.h
    Axis2/TravelTab.h
    Axis2/UOart.h
    Axis2/UOmap.h
    Axis2/WorldMap.h
    Axis2/resource.h
    Axis2/stdafx.h
)

# Ressourcendatei hinzufügen
set(RESOURCES
    Axis2/Axis2.rc
)

# Ausführbare Datei erstellen
add_executable(Axis2 WIN32 ${SOURCES} ${HEADERS} ${RESOURCES})

# Notwendige Linker-Flags für MFC hinzufügen
if(MSVC)
    target_link_options(Axis2 PRIVATE /SUBSYSTEM:WINDOWS)
endif()

# Precompiled Header-Unterstützung
target_precompile_headers(Axis2 PRIVATE Axis2/stdafx.h)