cmake_minimum_required(VERSION 3.16)

project(FHEditor VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Multimedia)
qt_standard_project_setup()

qt_add_executable(FHEditor
    src/events/command_230.cpp
    src/events/command_000.cpp
    src/events/command_101.cpp
    src/events/command_102.cpp
    src/events/command_122.cpp
    src/events/command_250.cpp
    src/events/command_353.cpp
    src/events/command_401.cpp
    src/events/command_404.cpp
    src/events/command_unknown.cpp
    src/models/base_model.cpp
    src/models/common_events_model.cpp
    src/models/event_content_list_model.cpp
    src/models/event_content_selection_model.cpp
    src/models/items_model.cpp
    src/models/map_event_pages_model.cpp
    src/models/map_events_model.cpp
    src/models/map_info_model.cpp
    src/rpgmmv/database.cpp
    src/rpgmmv/effect.cpp
    src/rpgmmv/json_stuff.cpp
    src/rpgmmz/system_mz.cpp
    src/ui/dialogs/games_list_dialog.cpp
    src/ui/events/command_dialog.cpp
    src/ui/events/create_command_dialog.cpp
    src/ui/events/command_text_dialog.cpp
    src/ui/dialogs/change_maximum_dialog.cpp
    src/ui/dialogs/icon_picker_dialog.cpp
    src/ui/dialogs/item_effect_dialog.cpp
    src/ui/dialogs/simple_chooser_dialog.cpp
    src/ui/events/play_sound_dialog.cpp
    src/ui/settings.cpp
    src/ui/tabs/armors_tab.cpp
    src/ui/tabs/common_events_tab.cpp
    src/ui/tabs/items_tab.cpp
    src/ui/tabs/map_event_page.cpp
    src/ui/tabs/map_events_tab.cpp
    src/ui/tabs/map_tab.cpp
    src/ui/tabs/types_tab.cpp
    src/ui/tabs/weapons_tab.cpp
    src/ui/widgets/attrib_combo_box.cpp
    src/ui/widgets/clickable_label.cpp
    src/ui/widgets/selector_button.cpp
    src/ui/command_factory.cpp
    src/ui/data_mapper.cpp
    src/ui/event_content_list.cpp
    src/ui/images.cpp
    src/ui/base_table.cpp
    src/ui/icon_picker_view.cpp
    src/ui/main_window.cpp
    src/ui/map_view.cpp
    src/ui/tile_picker_view.cpp
    src/ui/tilemap.cpp
    src/main.cpp

	src/ui/dialogs/change_maximum_dialog.ui
    src/ui/dialogs/games_list_dialog.ui
    src/ui/dialogs/icon_picker_dialog.ui
    src/ui/dialogs/item_effect_dialog.ui
    src/ui/dialogs/simple_chooser_dialog.ui
    src/ui/events/command_text_dialog.ui
    src/ui/events/create_command_dialog.ui
    src/ui/events/play_sound_dialog.ui
    src/ui/main_window.ui
    src/ui/tabs/armors_tab.ui
    src/ui/tabs/common_events_tab.ui
    src/ui/tabs/items_tab.ui
    src/ui/tabs/map_event_page.ui
    src/ui/tabs/map_events_tab.ui
    src/ui/tabs/map_tab.ui
    src/ui/tabs/types_tab.ui
    src/ui/tabs/weapons_tab.ui
)

target_include_directories(FHEditor PRIVATE src src/rpgmmv src/events src/models src/ui src/ui/tabs src/ui/events src/ui/dialogs src/ui/widgets)
target_link_libraries(FHEditor PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Multimedia)
