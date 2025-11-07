############### SET UP && RENAME ###############
FILTER_BRANCH_SQUELCH_WARNING=1 \
git filter-branch -f --env-filter '
fix () {
  export GIT_AUTHOR_NAME="<name>" # todo
  export GIT_AUTHOR_EMAIL="<number>+<username>@users.noreply.github.com" # todo
  export GIT_COMMITTER_NAME="$GIT_AUTHOR_NAME"
  export GIT_COMMITTER_EMAIL="$GIT_AUTHOR_EMAIL"
}

match () {
  case "$1" in
    <login-name>@c[123]r[1-9]s[1-9].42prague.com|\
    <login-name>@c[123]r[0-9]s[1-9].42prague.com)  # todo
      return 0 ;;
    *) return 1 ;;
  esac
}

if match "$GIT_AUTHOR_EMAIL"; then
  fix
fi
if match "$GIT_COMMITTER_EMAIL"; then
  fix
fi
' --tag-name-filter cat -- --all

############### PUST ON GIT ###############
git push --force origin main
git push --force --tags

############### CLEAN UP ###############
rm -rf .git/refs/original/  
git reflog expire --expire=now --all
git gc --prune=now --aggressive
