QT     += core gui widgets multimedia concurrent
CONFIG += c++latest
CONFIG -= debug_and_release debug_and_release_target qml_debug

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

INCLUDEPATH += src src/rpgmmv src/events src/models \
                src/ui src/ui/tabs src/ui/events src/ui/tools src/ui/dialogs src/ui/widgets
OBJECTS_DIR = obj
MOC_DIR = moc
UI_DIR = ui

SOURCES += \
    src/events/base_command.cpp \
    src/events/command_111.cpp \
    src/events/command_000.cpp \
    src/events/command_101.cpp \
    src/events/command_102.cpp \
    src/events/command_122.cpp \
    src/events/command_comment.cpp \
    src/events/command_line.cpp \
    src/events/command_simple.cpp \
    src/events/command_sound.cpp \
    src/events/command_unknown.cpp \
    src/events/command_wait.cpp \
    src/events/parameters_strings.cpp \
    src/main.cpp \
    src/models/animations_model.cpp \
    src/models/base_model.cpp \
    src/models/common_events_model.cpp \
    src/models/event_content_list_model.cpp \
    src/models/event_content_selection_model.cpp \
    src/models/item_effects_model.cpp \
    src/models/items_model.cpp \
    src/models/map_event_pages_model.cpp \
    src/models/map_events_model.cpp \
    src/models/map_info_model.cpp \
    src/rpgmmv/database.cpp \
    src/rpgmmv/effect.cpp \
    src/rpgmmv/event.cpp \
    src/rpgmmv/item.cpp \
    src/rpgmmv/json_stuff.cpp \
    src/rpgmmz/system_mz.cpp \
    src/ui/events/command_dialog.cpp \
    src/ui/events/conditional_branch_dialog.cpp \
    src/ui/events/create_command_dialog.cpp \
    src/ui/events/command_text_dialog.cpp \
    src/ui/events/play_sound_dialog.cpp \
    src/ui/events/wait_dialog.cpp \
    src/ui/dialogs/change_maximum_dialog.cpp \
    src/ui/dialogs/games_list_dialog.cpp \
    src/ui/dialogs/icon_picker_dialog.cpp \
    src/ui/dialogs/item_effect_dialog.cpp \
    src/ui/dialogs/simple_chooser_dialog.cpp \
    src/ui/menu.cpp \
    src/ui/tile_map.cpp \
    src/ui/tools/map_event_tool.cpp \
    src/ui/tools/tile_paint_tool.cpp \
    src/ui/tools/tile_picker_tool.cpp \
    src/ui/settings.cpp \
    src/ui/tabs/animations_tab.cpp \
    src/ui/tabs/armors_tab.cpp \
    src/ui/tabs/common_events_tab.cpp \
    src/ui/tabs/items_tab.cpp \
    src/ui/tabs/map_event_page.cpp \
    src/ui/tabs/map_events_tab.cpp \
    src/ui/tabs/map_tab.cpp \
    src/ui/tabs/types_tab.cpp \
    src/ui/tabs/weapons_tab.cpp \
    src/ui/widgets/attrib_combo_box.cpp \
    src/ui/widgets/clickable_label.cpp \
    src/ui/widgets/directory_list_view.cpp \
    src/ui/widgets/icon_widget.cpp \
    src/ui/widgets/selector_button.cpp \
    src/ui/command_factory.cpp \
    src/ui/data_mapper.cpp \
    src/ui/event_content_list.cpp \
    src/ui/images.cpp \
    src/ui/base_table.cpp \
    src/ui/icon_picker_view.cpp \
    src/ui/main_window.cpp \
    src/ui/map_view.cpp \
    src/ui/tile_picker_view.cpp

HEADERS += \
    src/accessor.hpp \
    src/events/command_111.hpp \
    src/events/base_command.hpp \
    src/events/command_000.hpp \
    src/events/command_101.hpp \
    src/events/command_102.hpp \
    src/events/command_122.hpp \
    src/events/command_comment.hpp \
    src/events/command_line.hpp \
    src/events/command_simple.hpp \
    src/events/command_sound.hpp \
    src/events/command_unknown.hpp \
    src/events/command_wait.hpp \
    src/events/json_value.hpp \
    src/events/parameters_strings.hpp \
    src/models/animations_model.hpp \
    src/models/base_model.hpp \
    src/models/common_events_model.hpp \
    src/models/event_content_list_model.hpp \
    src/models/event_content_selection_model.hpp \
    src/models/item_effects_model.hpp \
    src/models/items_model.hpp \
    src/models/map_event_pages_model.hpp \
    src/models/map_events_model.hpp \
    src/models/map_info_model.hpp \
    src/rpgmmv/actor.hpp \
    src/rpgmmv/animation.hpp \
    src/rpgmmv/armor.hpp \
    src/rpgmmv/class.hpp \
    src/rpgmmv/damage.hpp \
    src/rpgmmv/database.hpp \
    src/rpgmmv/effect.hpp \
    src/rpgmmv/enemy.hpp \
    src/rpgmmv/event.hpp \
    src/rpgmmv/image.hpp \
    src/rpgmmv/item.hpp \
    src/rpgmmv/json_qstring.hpp \
    src/rpgmmv/json_stuff.hpp \
    src/rpgmmv/map.hpp \
    src/rpgmmv/map_event.hpp \
    src/rpgmmv/map_info.hpp \
    src/rpgmmv/skill.hpp \
    src/rpgmmv/sound.hpp \
    src/rpgmmv/state.hpp \
    src/rpgmmv/system.hpp \
    src/rpgmmv/tileset.hpp \
    src/rpgmmv/trait.hpp \
    src/rpgmmv/troop.hpp \
    src/rpgmmv/weapon.hpp \
    src/rpgmmz/system_mz.hpp \
    src/ui/dialogs/games_list_dialog.hpp \
    src/ui/dialogs/change_maximum_dialog.hpp \
    src/ui/dialogs/icon_picker_dialog.hpp \
    src/ui/dialogs/simple_chooser_dialog.hpp \
    src/ui/dialogs/item_effect_dialog.hpp \
    src/ui/events/command_dialog.hpp \
    src/ui/events/conditional_branch_dialog.hpp \
    src/ui/events/play_sound_dialog.hpp \
    src/ui/events/create_command_dialog.hpp \
    src/ui/events/command_text_dialog.hpp \
    src/ui/events/wait_dialog.hpp \
    src/ui/menu.hpp \
    src/ui/tabs/animations_tab.hpp \
    src/ui/tabs/armors_tab.hpp \
    src/ui/tabs/base_tab.hpp \
    src/ui/tabs/common_events_tab.hpp \
    src/ui/tabs/items_tab.hpp \
    src/ui/tabs/map_event_page.hpp \
    src/ui/tabs/map_events_tab.hpp \
    src/ui/tabs/map_tab.hpp \
    src/ui/tabs/types_tab.hpp \
    src/ui/tabs/weapons_tab.hpp \
    src/ui/tile_map.hpp \
    src/ui/tools/map_event_tool.hpp \
    src/ui/tools/map_view_tool.hpp \
    src/ui/tools/tile_paint_tool.hpp \
    src/ui/tools/tile_picker_tool.hpp \
    src/ui/widgets/attrib_combo_box.hpp \
    src/ui/widgets/directory_list_view.hpp \
    src/ui/widgets/icon_widget.hpp \
    src/ui/widgets/selector_button.hpp \
    src/ui/widgets/clickable_label.hpp \
    src/ui/command_factory.hpp \
    src/ui/data_mapper.hpp \
    src/ui/event_content_list.hpp \
    src/ui/images.hpp \
    src/ui/base_table.hpp \
    src/ui/icon_picker_view.hpp \
    src/ui/main_window.hpp \
    src/ui/map_view.hpp \
    src/ui/settings.hpp \
    src/ui/tile_picker_view.hpp

FORMS += \
    src/ui/dialogs/change_maximum_dialog.ui \
    src/ui/dialogs/games_list_dialog.ui \
    src/ui/dialogs/icon_picker_dialog.ui \
    src/ui/dialogs/item_effect_dialog.ui \
    src/ui/dialogs/simple_chooser_dialog.ui \
    src/ui/events/command_text_dialog.ui \
    src/ui/events/conditional_branch_dialog.ui \
    src/ui/events/create_command_dialog.ui \
    src/ui/events/play_sound_dialog.ui \
    src/ui/events/wait_dialog.ui \
    src/ui/main_window.ui \
    src/ui/tabs/animations_tab.ui \
    src/ui/tabs/armors_tab.ui \
    src/ui/tabs/common_events_tab.ui \
    src/ui/tabs/items_tab.ui \
    src/ui/tabs/map_event_page.ui \
    src/ui/tabs/map_events_tab.ui \
    src/ui/tabs/map_tab.ui \
    src/ui/tabs/types_tab.ui \
    src/ui/tabs/weapons_tab.ui \
    src/ui/widgets/icon_widget.ui

TRANSLATIONS +=

RESOURCES += \
    assets/icons.qrc
