#
# ~/.bash_profile
#

[[ -f ~/.bashrc ]] && . ~/.bashrc

export MAKEOPTS='-j4 -l4'
export PROMPT_COMMAND='ps_one'
export ENV="$HOME/.profile"
export PATH="$PATH:$HOME/.local/bin"
export EDITOR='vim'
export BROWSER='firefox'

# NNN
export NNN_TRASH=1
