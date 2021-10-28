#!/usr/bin/env bash

FIREFOX_PROFILE='/home/ari/.mozilla/firefox/3s4h1qq0.default-release'

if [[ "$USER" != "ari" ]];
then
    exit 255
fi

echo "[?] Are you sure that you want to update the dotfiles?"
read -p "=== [ press enter to continue  ] ===" _

rm -rf dotfiles list
mkdir -p list
mkdir -p dotfiles{,/bin,/shells/bash,/suckless,/etc,/etc/firefox,/custom,/programming/VScodium,/core,/linux,/portage,/qbittorrent,/editors/vim,/fix}


from=(
    '/home/ari/.bashrc'
    '/home/ari/.profile'
    '/home/ari/.bash_profile'

    '/home/ari/.config'

    '/home/ari/.dwm'
    '/home/ari/Suckless'

    '/home/ari/.gtkrc-2.0'
    '/home/ari/Pictures/wallpaper.png'

    "$FIREFOX_PROFILE/prefs.js"
    "$FIREFOX_PROFILE/extensions.json"
    "$FIREFOX_PROFILE/extension-settings.json"
    "$FIREFOX_PROFILE/extension-preferences.json"
    "$FIREFOX_PROFILE/extensions"
    "$FIREFOX_PROFILE/features"
    "$FIREFOX_PROFILE/addons.json"
    "$FIREFOX_PROFILE/search.json.mozlz4"

    '/home/ari/.icons'

    '/home/ari/.scripts'

    '/home/ari/.vim'
    '/home/ari/.vimrc'
    '/home/ari/.vsnip'

    '/home/ari/.config/VSCodium/User/snippets'
    '/home/ari/.config/VSCodium/product.json'

    '/home/ari/.xinitrc'
    '/home/ari/.xprofile'
    '/etc/bash_git'
    '/etc/default/grub'
    '/etc/hosts'
    '/etc/dracut.conf'
    '/etc/dracut.conf.d'
    '/etc/sudoers'
    '/etc/X11/xorg.conf.d/20-intel-graphics.conf'
    '/etc/rc.conf'
    '/etc/modprobe.d/kernel_unfreeze_rtw.conf'
    '/etc/conf.d'
    '/etc/profile'
    '/etc/profile.env'
    '/etc/bash_completion.d'
    '/etc/gnupg'

    '/etc/portage'

    '/usr/src/linux/.config'

    '/usr/share/themes/mumble-dark.qbtheme'

    '/usr/local/src/yafetch'

    '/home/ari/Documents/wpa_cli_fix/doc.tex'
    '/home/ari/Documents/new_kernel_gentoo/doc.md'
)

to=(
    'dotfiles/shells/bash'
    'dotfiles/shells/bash'
    'dotfiles/shells/bash'

    'dotfiles/config'

    'dotfiles/suckless'
    'dotfiles/suckless'

    'dotfiles/etc'
    'dotfiles/etc'

    'dotfiles/etc/firefox'
    'dotfiles/etc/firefox'
    'dotfiles/etc/firefox'
    'dotfiles/etc/firefox'
    'dotfiles/etc/firefox'
    'dotfiles/etc/firefox'
    'dotfiles/etc/firefox'
    'dotfiles/etc/firefox'

    'dotfiles/icons'

    'dotfiles/custom'

    'dotfiles/editors/vim'
    'dotfiles/editors/vim'
    'dotfiles/editors/vim'

    'dotfiles/programming/VScodium'
    'dotfiles/programming/VScodium'

    'dotfiles/core'
    'dotfiles/core'
    'dotfiles/core'
    'dotfiles/core'
    'dotfiles/core'
    'dotfiles/core'
    'dotfiles/core'
    'dotfiles/core'
    'dotfiles/core'
    'dotfiles/core'
    'dotfiles/core'
    'dotfiles/core'
    'dotfiles/core'
    'dotfiles/core'
    'dotfiles/core'
    'dotfiles/core'

    'dotfiles/portage'

    'dotfiles/linux'

    'dotfiles/qbittorrent'

    'dotfiles/bin'

    'dotfiles/fix/wpa_cli_fix.tex'
    'dotfiles/fix/gentoo_new_kernel.md'
)


for i in "${!from[@]}";
do
    sudo cp -rfv "${from[$i]}" "${to[$i]}"
    echo "${from[$i]} -> ${to[$i]}" >> list/location.list
done


ls -lA /usr/local/src > list/src.list

find /usr/local/bin -type l -exec ls -lA {} +

sudo find /root -type l -exec ls -lA {} + | tee list/root_symlinks.list

cp /var/lib/portage/world list/package.list
q qlist -I > list/package_full.list

uname -r > list/kernel.release
rc-update > list/openrc_services.sysvinit.list

python3 -m jupyter nbextension list 2>/dev/null > list/jupyter_entensions.list
python3 -m pip list | awk '{ print $1 }' | tail -n +3 > list/pip_modules.list


sudo chown -R ari:ari dotfiles
rm -rfv dotfiles/config/asciinema dotfiles/editors/vim/.vim/undodir dotfiles/config/keepassxc dotfiles/config/VSCodium dotfiles/config/VirtualBox dotfiles/config/transmission/dht.dat dotfiles/config/dconf

sed -i '/PHONE/d' dotfiles/config/tg/conf.py

