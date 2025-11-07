###################################################################################
############ set up custom keybinding to lock the screen from terminal ############
###################################################################################
KEYBIND_PATH="/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom0/"

gsettings set org.gnome.settings-daemon.plugins.media-keys custom-keybindings \
"['$KEYBIND_PATH']"

gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:$KEYBIND_PATH name 'Lock screen (manual)'
gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:$KEYBIND_PATH command "dm-tool lock"
gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:$KEYBIND_PATH binding '<Super>L'

###################################################################################
# UI alternative is:                                                              #
# Settings -> Keyboard -> Custom Shortcuts -> View and Customize Shortcuts ->     #
# -> Custom Shortcuts (at the bottom) -> '+' -> do the rest                       #
###################################################################################