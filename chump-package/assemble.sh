# documentation generation (nice)
chuck doc/make-doc.ck

# linux (easiest)
chuck -s build-pkg-linux.ck

# windows
chuck -s build-pkg-win.ck

# mac
sh 1-codesign.sh
chuck -s build-pkg-mac.ck
sh 3-notarize.sh